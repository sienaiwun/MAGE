#include "stdafx.h"
#include <windows.h>

#include "core\engine.hpp"

using namespace mage;

class TestState : public State {
	virtual void Update(double elapsed_time) {
		UNUSED(elapsed_time);

		if (g_engine->GetInputManager().GetKeyboard().GetKeyPress(DIK_Q)) {
			//PostQuitMessage(0);

			VariableScript s(L"script_test.mage", L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/script/");
			s.ExportScript(L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/script/output.mage");
		}
	};
};

void StateSetup() {
	g_engine->GetStateManager().AddState(new TestState(), true);
}

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
	EngineSetup setup(hinstance, L"Engine Control Test", StateSetup);

	// Create the engine, then run it.
	g_engine = new Engine(setup);

	//Renderer *renderer = g_engine->GetRenderer();
	//Model model(renderer->GetDevice(), "cube.obj", "C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/model/");
	//model.BindBuffers(renderer->GetDeviceContext());

	g_engine->Run(nCmdShow);
	delete g_engine;

	return 0;
}

