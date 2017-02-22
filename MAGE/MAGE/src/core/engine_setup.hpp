#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_APPLICATION_NAME L"Application"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of engine setups.
	 */
	struct EngineSetup {

	public:

		/**
		 Destructs this engine setup.
		 */
		virtual ~EngineSetup() = default;

		/**
		 Returns the name of the application.

		 @return		A reference to the name of the application.
		 */
		const wstring &GetApplicationName() const {
			return m_name;
		}

		/**
		 Returns the application instance handle of the application.

		 @return		The application instance handle of the application.
		 */
		HINSTANCE GetApplicationHinstance() const {
			return m_hinstance;
		}
	
		/**
		 Creates the first scene of the application.

		 @return		A pointer to the first scene of the application.
		 */
		virtual SharedPtr< Scene > CreateScene() const = 0;

	protected:

		/**
		 Constructs an engine setup.

		 @param[in]		hinstance
						The application instance handle of the application.
		 @param[in]		name
						A reference to the name of the application.
		 */
		EngineSetup(HINSTANCE hinstance = nullptr, const wstring &name = MAGE_DEFAULT_APPLICATION_NAME)
			: m_hinstance(hinstance), m_name(name) {}

		/**
		 Constructs an engine setup from the given engine setup.

		 @param[in]		setup
						A reference to the engine setup.
		 */
		EngineSetup(const EngineSetup &setup) = default;

	private:

		/**
		 Copies the given engine setup to this engine setup.

		 @param[in]		setup
						A reference to the engine setup to copy from.
		 @return		A reference to the copy of the given engine setup
						(i.e. this engine setup).
		 */
		EngineSetup &operator=(const EngineSetup &setup) = delete;

		/**
		 Application instance handle.
		 */
		HINSTANCE m_hinstance;

		/**
		 Name of the application.
		 */
		const wstring m_name;
	};
}