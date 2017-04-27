#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\targetver.hpp"

#include "rendering\renderer.hpp"
#include "input\input_manager.hpp"
#include "ui\main_window.hpp"
#include "resource\resource_factory.hpp"
#include "timer\timer.hpp"

#include "core\loadable.hpp"
#include "core\engine_setup.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of engines.
	 */
	class Engine final : public Loadable {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an engine from the given engine setup.

		 @param[in]		setup
						A reference to an engine setup.
		 @throws		FormattedException
						Failed to initialize the engine.
		 */
		explicit Engine(const EngineSetup &setup);

		/**
		 Constructs an engine from the given engine.

		 @param[in]		engine
						A reference to the engine to copy.
		 */
		Engine(const Engine &engine) = delete;

		/**
		 Constructs an engine by moving the given engine.

		 @param[in]		engine
						A reference to the engine to move.
		 */
		Engine(Engine &&engine) = default;

		/**
		 Destructs this engine.
		 */
		virtual ~Engine();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine to copy.
		 @return		A reference to the copy of the given engine
						(i.e. this engine).
		 */
		Engine &operator=(const Engine &engine) = delete;

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine to move.
		 @return		A reference to the moved engine
						(i.e. this engine).
		 */
		Engine &operator=(Engine &&engine) = delete;

		/**
		 Runs this engine.

		 @param[in]		nCmdShow
						Controls how the engine window is to be shown.
		 */
		void Run(int nCmdShow = SW_NORMAL);

		//---------------------------------------------------------------------
		// Member Methods: Window System
		//---------------------------------------------------------------------

		/**
		 Returns the main window of this engine.
		 
		 @return		@c nullptr if this engine is not properly setup.
		 @return		A pointer to the main window of this engine.
		 */
		const MainWindow *GetMainWindow() const {
			return m_main_window.get();
		}
		
		/**
		 Sets the deactive flag of this engine to the given value.

		 @param[in]		deactive
						The new value for the deactive flag.	
		 */
		void SetDeactiveFlag(bool deactive);

		//---------------------------------------------------------------------
		// Member Methods: Rendering System
		//---------------------------------------------------------------------

		/**
		 Returns the renderer of this engine.

		 @return		@c nullptr if this engine is not properly setup.
		 @return		A pointer to the renderer of this engine.
		 */
		const Renderer *GetRenderer() const {
			return m_renderer.get();
		}

		/**
		 Sets the mode switch flag of this engine to the given value.

		 @param[in]		mode_switch
						The new value for the mode switch flag.
		 */
		void SetModeSwitchFlag(bool mode_switch) {
			m_mode_switch = mode_switch;
		}

		//---------------------------------------------------------------------
		// Member Methods: Input System
		//---------------------------------------------------------------------

		/**
		 Returns the input manager of this engine.

		 @return		@c nullptr if this engine is not properly setup.
		 @return		A pointer to the input manager of this engine.
		 */
		const InputManager *GetInputManager() const {
			return m_input_manager.get();
		}

		//---------------------------------------------------------------------
		// Member Methods: Resource System
		//---------------------------------------------------------------------

		/**
		 Returns the resource factory of this engine.

		 @return		@c nullptr if this engine is not properly setup.
		 @return		A pointer to the resource factory of this engine.
		 */
		ResourceFactory *GetResourceFactory() const {
			return m_resource_factory.get();
		}

		//---------------------------------------------------------------------
		// Member Methods: Scene
		//---------------------------------------------------------------------

		/**
		 Sets the scene of this engine to the given scene.

		 @return		A pointer to the scene to set.
		 */
		void SetScene(SharedPtr< Scene > scene);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the different systems of this engine.

		 @param[in]		setup
						A reference to an engine setup.
		 @throws		FormattedException
						Failed to initialize at least one of
						the different systems of this engine.
		 */
		void InitializeSystems(const EngineSetup &setup);

		//---------------------------------------------------------------------
		// Member Variables: Window System
		//---------------------------------------------------------------------

		/**
		 A pointer to the main window of this engine. 
		 */
		UniquePtr< MainWindow > m_main_window;

		/** 
		 Flag indicating whether the application is active or not.
		 */
		bool m_deactive;

		//---------------------------------------------------------------------
		// Member Variables: Rendering System
		//---------------------------------------------------------------------

		/**
		 A pointer to the renderer of this engine.
		 */
		UniquePtr< Renderer > m_renderer;

		/**
		 Flag indicating whether the application should switch between
		 full screen and windowed mode.
		 */
		bool m_mode_switch;

		//---------------------------------------------------------------------
		// Member Variables: Input System
		//---------------------------------------------------------------------

		/**
		 A pointer to the input manager of this engine.
		 */
		UniquePtr< InputManager > m_input_manager;

		//---------------------------------------------------------------------
		// Member Variables: Resource System
		//---------------------------------------------------------------------

		/**
		 A pointer to the resource factory of this engine.
		 */
		UniquePtr< ResourceFactory > m_resource_factory;

		//---------------------------------------------------------------------
		// Member Variables: Scene
		//---------------------------------------------------------------------

		/**
		 A pointer to the current scene of this engine.
		 */
		SharedPtr< Scene > m_scene;

		//---------------------------------------------------------------------
		// Member Variables: Timer
		//---------------------------------------------------------------------

		/**
		 A pointer to the timer of this engine.
		 */
		UniquePtr< Timer > m_timer;
	};

	/**
	 A pointer to the engine used by the user.
	 */
	extern Engine *g_engine;
}
