#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <DXGI1_3.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io/graphics_settings.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the number of bits per pixel of the given format.

	 @return		The number of bits per pixel of the given format.
	 */
	size_t BitsPerPixel(DXGI_FORMAT format);

	/** 
	 The allowable pixel formats. 
	 */
	const DXGI_FORMAT allowed_pixel_formats[] = {
		DXGI_FORMAT_B5G5R5A1_UNORM,	   // A four-component,  16-bit unsigned-normalized-integer format that supports 5  bits for each color channel and 1-bit alpha.
		DXGI_FORMAT_B5G6R5_UNORM,	   // A three-component, 16-bit unsigned-normalized-integer format that supports 5  bits for blue, 6 bits for green, and 5 bits for red.
		DXGI_FORMAT_B8G8R8X8_UNORM,	   // A four-component,  32-bit unsigned-normalized-integer format that supports 8  bits for each color channel and 8 bits unused.
		DXGI_FORMAT_B8G8R8A8_UNORM,    // A four-component,  32-bit unsigned-normalized-integer format that supports 8  bits for each color channel and 8-bit alpha.
		DXGI_FORMAT_R10G10B10A2_UNORM, // A four-component,  32-bit unsigned-normalized-integer format that supports 10 bits for each color and 2 bits for alpha.
	};

	/**
	 A display mode.
	 */
	struct DisplayMode {

		/**
		 The display mode descriptor of this display mode.
		 */
		DXGI_MODE_DESC1 mode;
		
#define MAGE_DISPLAYMODE_BPP_COUNT 8

		/**
		 The colour depth expressed as a character string for the display mode.
		 */
		wchar_t bpp[MAGE_DISPLAYMODE_BPP_COUNT];
	};

	/**
	 A device enumeration.
	 */
	class DeviceEnumeration {
	
	public:

		/**
		 Constructs a device enumeration.
		 */
		DeviceEnumeration() {}

		/**
		 Destructs this device enumeration.
		 */
		virtual ~DeviceEnumeration() {}

		/**
		 Enumerates the available display modes on the adapter output of
		 the physical adapter with the most dedicated video memory.
		 */
		INT_PTR Enumerate();

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
		 */
		INT_PTR SettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

		/**
		 Returns the selected display mode by the user.

		 @return		A pointer to the selected display mode.
		 */
		const DXGI_MODE_DESC1 *GetSelectedDisplayMode() const {
			return &m_selected_diplay_mode;
		}
		
		/**
		 Check whether the application should run in windowed mode.

		 @return		@c true if the application should run in windowed mode.
						@c false otherwise.
		 */
		bool IsWindowed() const {
			return m_windowed;
		}

		/**
		 Check whether v-sync should be enabled.

		 @return		@c true if v-sync should be enabled.
						@c false otherwise.
		 */
		bool IsVSynced() const {
			return m_vsync;
		}

	private:
		
		/**
		 A poinbter to the adapter (or video card).
		 */
		IDXGIAdapter2 *m_adapter;

		/**
		 A pointer to the script which stores the device configuration.
		 */
		VariableScript *m_settings_script;
		
		/**
		 The linked list of enumerated display modes.
		 */
		list< DisplayMode > m_display_modes;
		
		/**
		 The selected display mode by the user.
		 */										
		DXGI_MODE_DESC1 m_selected_diplay_mode;
		
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