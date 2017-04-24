#include "stdafx.h"

#include "script\fps_input_controller_script.hpp"
#include "script\stats_script.hpp"
#include "script\wireframe_script.hpp"

using namespace mage;

class TestScript final : public BehaviorScript {

public:

	TestScript(SharedPtr< Model > model)
		: BehaviorScript(), m_model(model) {}
	TestScript(const TestScript &script) = delete;
	TestScript(TestScript &&script) = default;
	virtual ~TestScript() = default;
	TestScript &operator=(const TestScript &script) = delete;
	TestScript &operator=(TestScript &&script) = delete;

	virtual void Update(double delta_time) override {
		m_model->GetTransform()->AddRotationY((float)delta_time);

		if (g_engine->GetInputManager()->GetKeyboard()->GetKeyPress(DIK_F2)) {
			//PostQuitMessage(0);
			VariableScript s(L"assets/scripts/script_test.vs");
			s.ExportScript(L"assets/scripts/output.vs");
		}
	}

private:
	
	SharedPtr< Model > m_model;
};

class TestScene final : public Scene {

public:

	TestScene()
		: Scene("testscene") {}
	TestScene(const TestScene &scene) = delete;
	TestScene(TestScene &&scene) = delete;
	virtual ~TestScene() = default;
	TestScene &operator=(const TestScene &scene) = delete;
	TestScene &operator=(TestScene &&scene) = delete;

private:

	virtual void Load() override {

		//---------------------------------------------------------------------
		// Camera
		//---------------------------------------------------------------------
		SharedPtr< Camera > camera = CreatePerspectiveCamera("camera");
		camera->GetTransform()->SetTranslation(0.0f, 2.0f, 0.0f);
		SetCamera(camera);
		

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc_sponza = CreateModelDescriptor(L"assets/models/sponza/sponza.mdl", mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_sphere = CreateModelDescriptor(L"assets/models/sphere/sphere.mdl", mesh_desc);
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		SharedPtr< Model > model_sponza(new Model("sponza", *model_desc_sponza));
		model_sponza->GetTransform()->SetScale(10.0f);
		GetWorld()->AddModel(model_sponza);
		SharedPtr< Model > model_sphere(new Model("sphere", *model_desc_sphere));
		model_sphere->GetTransform()->AddTranslationY(0.5f);
		GetWorld()->AddModel(model_sphere);


		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		SharedPtr< OmniLight > omni_light(new OmniLight("omnilight", RGBSpectrum(1.0f, 1.0f, 1.0f)));
		omni_light->GetTransform()->SetTranslationY(2.0f);
		omni_light->SetDistanceFalloff(0.0f, 2.0f);
		GetWorld()->AddLight(omni_light);
		SharedPtr< SpotLight > spot_light(new SpotLight("spotlight", RGBSpectrum(1.0f, 1.0f, 1.0f)));
		spot_light->GetTransform()->SetTranslation(0.0f, 2.0f, 0.0f);
		spot_light->SetDistanceFalloff(0.0f, 3.0f);
		GetWorld()->AddLight(spot_light);


		//---------------------------------------------------------------------
		// Texture
		//---------------------------------------------------------------------
		SharedPtr< Texture > texture_logo = CreateTexture(L"assets/sprites/mage.dds");
		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		SharedPtr< SpriteImage > logo(new SpriteImage("logo", texture_logo));
		logo->GetTransform()->SetScale(0.25f, 0.25f);
		logo->GetTransform()->SetNormalizedTranslation(0.90f, 0.88f);
		GetWorld()->AddSprite(logo);


		//---------------------------------------------------------------------
		// Font
		//---------------------------------------------------------------------
		SharedPtr< SpriteFont > font = CreateFont(L"assets/fonts/consolas.spritefont", SpriteFontDescriptor());
		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		SharedPtr< SpriteText > text(new NormalSpriteText("text", font));
		GetWorld()->AddSprite(text);


		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		//SharedPtr< BehaviorScript > script(new TestScript(model_teapot));
		//AddScript(script);
		
		SharedPtr< BehaviorScript > controller_script(new FPSInputControllerScript(camera->GetTransform()));
		AddScript(controller_script);

		SharedPtr< BehaviorScript > controller_script2(new FPSInputControllerScript(spot_light->GetTransform()));
		AddScript(controller_script2);


		SharedPtr< BehaviorScript > stats_script(new StatsScript(text));
		AddScript(stats_script);
		SharedPtr< BehaviorScript > wireframe_script(new WireframeScript());
		AddScript(wireframe_script);
	}
};

struct TestSetup : public EngineSetup {

	TestSetup(HINSTANCE hinstance = nullptr, const wstring &name = MAGE_DEFAULT_APPLICATION_NAME)
		: EngineSetup(hinstance, name) {}
	virtual ~TestSetup() = default;

	virtual SharedPtr< Scene > CreateScene() const override {
		return SharedPtr< Scene >(new TestScene());
	}
};

/**
 The user-provided entry point for MAGE.

 @param[in]		hinstance
				A handle to the current instance of the application.
 @param[in]		hPrevInstance
				A handle to the previous instance of the application.
				This parameter is always @c nullptr.
 @param[in]		lpCmdLine
				The command line for the application, excluding the program name.
 @param[in]		nCmdShow
				Controls how the window is to be shown.
 @return		If the function succeeds, terminating when it receives a WM_QUIT message, 
				it returns the exit value contained in that message's @c wParam parameter. 
				If the function terminates before entering the message loop, it returns 0.
 */
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int nCmdShow) {

	// Create the engine setup structure.
	TestSetup setup(hinstance, L"Engine Control Test");

	// Create the engine, then run it.
	g_engine = new Engine(setup);
	g_engine->Run(nCmdShow);
	SAFE_DELETE(g_engine);

	return 0;
}
