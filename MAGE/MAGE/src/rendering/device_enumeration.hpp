#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A device enumeration.
	 */
	class DeviceEnumeration {

	friend class Engine;
	friend INT_PTR CALLBACK SettingsDialogProcDelegate(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	public:

		/**
		 Returns the adapter.

		 @return		A pointer to the adapter.
		 */
		IDXGIAdapter2 *GetAdapter() const {
			return m_adapter;
		}

		/**
		 Returns the output.

		 @return		A pointer to the output.
		 */
		IDXGIOutput2 *GetOutput() const {
			return m_output;
		}

		/**
		 Returns the selected display mode by the user.

		 @return		A pointer to the selected display mode.
		 */
		const DXGI_MODE_DESC1 *GetDisplayMode() const {
			return m_selected_diplay_mode;
		}
		
		/**
		 Checks whether the application should run in windowed mode.

		 @return		@c true if the application should run in windowed mode.
						@c false otherwise.
		 */
		bool IsWindowed() const {
			return m_windowed;
		}

		/**
		 Checks whether the application should run in full screen mode.

		 @return		@c true if the application should run in full screen mode.
						@c false otherwise.
		 */
		bool IsFullScreen() const {
			return !m_windowed;
		}

		/**
		 Checks whether v-sync should be enabled.

		 @return		@c true if v-sync should be enabled.
						@c false otherwise.
		 */
		bool IsVSynced() const {
			return m_vsync;
		}

	protected:

		/**
		 Constructs a device enumeration.
		 */
		DeviceEnumeration();

		/**
		 Destructs this device enumeration.
		 */
		virtual ~DeviceEnumeration();

		/**
		 Initializes the adapter and the output of this device enumeration.

		 @return		A success/error value.
		 */
		HRESULT InitializeAdapterAndOutput();

		/**
		 Uninitializes the adapter and the output of this device enumeration.

		 @return		A success/error value.
		 */
		HRESULT UninitializeAdapterAndOutput();

		/**
		 Initializes the display modes of this device enumeration.

		 @return		A success/error value.
		 */
		HRESULT InitializeDisplayModes();

		/**
		 Enumerates the available display modes on the adapter output of
		 the physical adapter with the most dedicated video memory.

		 @return		A success/error value.
		 */
		HRESULT Enumerate();

		/**
		 Engine-defined callback function used with the CreateDialog
		 for device enumeration.

		 @param[in]		hwndDlg
						A handle to the dialog box.
		 @param[in]		uMsg
						The message.
		 @param[in]		wParam
						Additional message-specific information.
		 @param[in]		lParam
						Additional message-specific information.
		 @return		@c true if @a uMsg is processed.
						@c false otherwise.
		 */
		INT_PTR SettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
		/**
		 A pointer to the adapter (or video card).
		 */
		IDXGIAdapter2 *m_adapter;

		/**
		 A pointer to the output.
		 */
		IDXGIOutput2 *m_output;

		/**
		 A pointer to the script which stores the device configuration.
		 */
		VariableScript *m_settings_script;
		
		/**
		 The linked list of enumerated display modes.
		 */
		list< DXGI_MODE_DESC1 > m_display_modes;
		
		/**
		 A pointer to the selected display mode by the user.
		 */										
		const DXGI_MODE_DESC1 *m_selected_diplay_mode;
		
		/**
		 Flag indicating whether the application should run in windowed mode.
		 */
		bool m_windowed;
		
		/**
		 Flag indicating whether v-sync should be enabled.
		 */
		bool m_vsync;
	};

	/**
	 A (global) pointer to the device enumeration.
	 */
	extern DeviceEnumeration *g_device_enumeration;
}