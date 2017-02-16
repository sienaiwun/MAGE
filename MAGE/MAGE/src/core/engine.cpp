//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"
#include "version.hpp"
#include "logging\error.hpp"
#include "logging\logging.hpp"
#include "logging\timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Globals
	//-------------------------------------------------------------------------
	LoggingConfiguration g_logging_configuration;
	Engine *g_engine = nullptr;

	//-------------------------------------------------------------------------
	// Engine
	//-------------------------------------------------------------------------
	
	Engine::Engine(const EngineSetup &setup) 
		: Loadable(), m_deactive(false), m_mode_switch(false) {

		// Store a pointer to the engine in a global variable for easy access.
		SAFE_DELETE(g_engine);
		g_engine = this;

		// Attach a console.
		const HRESULT result_console = InitializeConsole();
		if (FAILED(result_console)) {
			Error("Console initialization failed: %ld.", result_console);
			return;
		}
		PrintConsoleHeader();

		// Initialize the different engine systems.
		const HRESULT result_system = InitializeSystems(setup);
		if (FAILED(result_system)) {
			Error("Systems initialization failed: %ld.", result_system);
			return;
		}

		// Initializes the COM library for use by the calling thread 
		// and sets the thread's concurrency model to multithreaded concurrency.
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		// The engine is fully loaded and ready to go.
		SetLoaded();
	}

	Engine::~Engine() {

		// Uninitialize the COM.
		if (IsLoaded()) {
			CoUninitialize();
		}
	}

	HRESULT Engine::InitializeSystems(const EngineSetup &setup) {
		// Enumerate the devices.
		SAFE_DELETE(g_device_enumeration);
		g_device_enumeration = new DeviceEnumeration();
		const HRESULT result_enumerate = g_device_enumeration->Enumerate();
		if (FAILED(result_enumerate)) {
			Error("Device enumeration setup failed: %ld", result_enumerate);
			return E_FAIL;
		}

		const LONG width  = (LONG)g_device_enumeration->GetDisplayMode()->Width;
		const LONG height = (LONG)g_device_enumeration->GetDisplayMode()->Height;
		
		// Initialize the window System.
		m_main_window = make_unique< MainWindow >(setup.GetApplicationHinstance(), setup.GetApplicationName(), width, height);
		if (!m_main_window->IsLoaded()) {
			Error("Window creation failed.");
			return E_FAIL;
		}

		// Initialize the rendering system.
		m_renderer = make_unique< Renderer >(m_main_window->GetHandle());
		if (!m_renderer->IsLoaded()) {
			Error("Renderer creation failed.");
			return E_FAIL;
		}
		
		// Initialize the input manager.
		m_input_manager = make_unique< InputManager >(m_main_window->GetHandle());
		if (!m_input_manager->IsLoaded()) {
			Error("Input manager creation failed.");
			return E_FAIL;
		}
		
		// Initialize the state manager.
		m_state_manager	= make_unique< StateManager >();
		// Sets up the states.
		setup.SetupApplicationStates();

		return S_OK;
	}

	void Engine::Run(int nCmdShow) {
		// Ensure the engine is loaded.
		if (!IsLoaded()) {
			Error("Game loop can not be started because the engine is not loaded.");
			return;
		}

		m_main_window->Show(nCmdShow);

		// Handle startup in fullscreen mode.
		if (g_device_enumeration->IsFullScreen()) {
			m_renderer->SwitchMode(true);
		}

		Timer timer;
		timer.Start();

		// Enter the message loop.
		MSG msg;
		SecureZeroMemory(&msg, sizeof(MSG));
		while (msg.message != WM_QUIT) {
			// Retrieves messages for any window that belongs to the current thread
			// without performing range filtering. Furthermore messages are removed
			// after processing.
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				// Translates virtual-key messages into character messages.
				TranslateMessage(&msg);
				// Dispatches a message to a window procedure.
				DispatchMessage(&msg);
			}
			else if (!m_deactive) {
				// Calculate the elapsed time.
				const double elapsed_time = timer.Time();
				timer.Restart();

				// Update the input manager.
				m_input_manager->Update();
				// Handle forced exit.
				if (m_input_manager->GetKeyboard().GetKeyPress(DIK_F1)) {
					PostQuitMessage(0);
					continue;
				}

				// Handle switch between full screen and windowed mode.
				const bool lost_mode = m_renderer->LostMode();
				if (m_mode_switch || lost_mode) {
					m_renderer->SwitchMode(!lost_mode);
					m_mode_switch = false;
					continue;
				}

				m_renderer->StartFrame();
				m_state_manager->Update(elapsed_time);
				m_renderer->EndFrame();
			}
		}
	}
}