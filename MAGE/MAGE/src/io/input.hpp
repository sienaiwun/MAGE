#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <dinput.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of inputs.
	 */
	class Input {

	public:

		/**
		 Constructs an input for the given window handle.

		 @param[in]		hwindow
						The handle of the parent window.
		 */
		Input(HWND hwindow);

		/**
		 Destructs this input.
		 */
		virtual ~Input() {
			m_di->Release();
			m_keyboard->Release();
			m_mouse->Release();
		}

		/**
		 Updates the state of both the keyboard and mouse device of this input.
		 */
		void Update();

		/**
		 Checks whether the given key is pressed.

		 @tparam		include_press_stamp
						Consistent presses will return false when including the press stamp.
		 @param[in]		key
						The key.
		 @return		@c true if the given key is pressed.
						@c false otherwise.
		 */
		template < bool include_press_stamp >
		bool GetKeyPress(char key) {
			if ((m_key_state[key] & 0x80) == false) {
				return false;
			}

			const bool pressed = (include_press_stamp && (m_key_press_stamp[key] == m_press_stamp - 1 || m_key_press_stamp[key] == m_press_stamp)) ? false : true;

			m_key_press_stamp[key] = m_press_stamp;

			return pressed;
		}

		/**
		 Checks whether the given mouse button is pressed.

		 @tparam		include_press_stamp
						Consistent presses will return false when including the press stamp.
		 @param[in]		mouse_button
						The mouse button.
		 @return		@c true if the given mouse button is pressed.
						@c false otherwise.
		 */
		template < bool include_press_stamp >
		bool GetMouseButtonPress(char mouse_button) {
			if ((m_mouse_state.rgbButtons[mouse_button] & 0x80) == false) {
				return false;
			}

			const bool pressed = (include_press_stamp && (m_mouse_button_press_stamp[mouse_button] == m_press_stamp - 1 || m_mouse_button_press_stamp[mouse_button] == m_press_stamp)) ? false : true;

			m_mouse_button_press_stamp[mouse_button] = m_press_stamp;

			return pressed;
		}

		/**
		 Returns the horizontal position of the mouse.

		 @return		The horizontal position of the mouse.
		 */
		long GetPosX() const {
			return m_mouse_position.x;
		}

		/**
		 Returns the vertical position of the mouse.

		 @return		The vertical position of the mouse.
		 */
		long GetPosY() const {
			return m_mouse_position.y;
		}

		/**
		 Returns the change in the mouse's horizontal coordinate.

		 @return		The change in the mouse's horizontal coordinate.
		 */
		long GetDeltaX() const {
			return m_mouse_state.lX;
		}

		/**
		 Returns the change in the mouse's vertical coordinate.

		 @return		The change in the mouse's vertical coordinate.
		 */
		long GetDeltaY() const {
			return m_mouse_state.lY;
		}

		/**
		 Returns the change in the mouse's scroll wheel.

		 @return		The change in the mouse's mouse's scroll wheel.
		*/
		long GetDeltaWheel() const {
			return m_mouse_state.lZ;
		}

	private:

		/**
		 The handle of the parent window.
		 */
		HWND m_hwindow;

		/**
		 The DirectInput object.

		 The methods of the IDirectInput8 interface are used to enumerate,
		 create, and retrieve the status of Microsoft DirectInput device.
		 */
		IDirectInput8 *m_di;

		/**
		 The current press stamp (incremented every frame).
		 */
		uint64_t m_press_stamp;

		/**
		 The DirectInput keyboard device.

		 The methods of the IDirectInputDevice8 interface are used to gain and release access
		 to Microsoft DirectInput devices, manage device properties and information, set behavior,
		 perform initialization, create and play force-feedback effects, and invoke a device's control panel.
		 */
		IDirectInputDevice8 *m_keyboard;

		/**
		 State of the keys.
		 */
		char m_key_state[256];

		/**
		 Stamps the keys pressed in the last frame.
		 */
		uint64_t m_key_press_stamp[256];

		/**
		 DirectInput mouse device.

		 The methods of the IDirectInputDevice8 interface are used to gain and release access
		 to Microsoft DirectInput devices, manage device properties and information, set behavior,
		 perform initialization, create and play force-feedback effects, and invoke a device's control panel.
		 */
		IDirectInputDevice8 *m_mouse;

		/**
		 State of the mouse buttons.

		 Describes the state of a mouse device that has up to four buttons,
		 or another device that is being accessed as if it were a mouse device.
		 */
		DIMOUSESTATE m_mouse_state;

		/**
		 Stamps the mouse buttons pressed in the last frame.
		 */
		uint64_t m_mouse_button_press_stamp[3];

		/**
		 The position of the mouse cursor on the screen.
		 */
		POINT m_mouse_position;
	};
}