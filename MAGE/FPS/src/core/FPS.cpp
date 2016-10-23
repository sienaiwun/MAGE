#include "stdafx.h"
#include <windows.h>

#include "core\engine.hpp"

using namespace mage;

class TestState : public State {
	virtual void Update(double elapsed_time) {
		if (g_engine->GetInput()->GetKeyPress(DIK_Q)) {
			PostQuitMessage(0);
		}
	};
};

void StateSetup() {
	g_engine->GetStateManager()->AddState(new TestState(), true);
}

/**
The user-provided entry point for MAGE.

 @param[in]		hinstance
				A handle to the current instance of the application.
 @param[in]		hPrevInstance
				A handle to the previous instance of the application.
				This parameter is always NULL.
 @param[in]		lpCmdLine
				The command line for the application, excluding the program name.
 @param[in]		nCmdShow
				Controls how the window is to be shown.
 @return		If the function succeeds, terminating when it receives a WM_QUIT message, 
				it returns the exit value contained in that message's @c wParam parameter. 
				If the function terminates before entering the message loop, it returns 0.
 */
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {

	// Create the engine setup structure.
	EngineSetup setup;
	setup.m_hinstance = hinstance;
	setup.m_name = L"Engine Control Test";
	setup.StateSetup = StateSetup;

	// Create the engine, then run it.
	new Engine(&setup);
	g_engine->Run();

	return true;
}

