#pragma once

/**
 A class of renderers.
 */
namespace mage {

	class Renderer {

	friend class Engine;
	friend LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		
		/**
		 Checks whether this renderer is loaded.

		 @return		@c true if this renderer is loaded.
						@c false otherwise.
		 */
		bool IsLoaded() const {
			return m_loaded;
		}

		/**
		 Check whether this renderer renders in windowed mode.

		 @return		@c true if this renderer renders in windowed mode.
						@c false otherwise.
		*/
		bool IsWindowed() const {
			return m_windowed;
		}

		/**
		 Check whether this renderer renders in full screen mode.

		 @return		@c true if this renderer renders in full screen mode.
						@c false otherwise.
		 */
		bool IsFullScreen() const {
			return !m_windowed;
		}

	protected:

		/**
		 Constructs a renderer.

		 @param[in]		The main window handle.
		 */
		Renderer(HWND hwindow);

		/**
		 Destructs this renderer.
		 */
		virtual ~Renderer();

		/**
		 Initializes the D3D11 device of this renderer.

		 @return		A success/error value.
		 */
		HRESULT InitDevice();

		/**
		 Renders the current frame.

		 @param[in]		elapsed_time
						The elapsed time since the previous frame.
		 */
		void Render(double elapsed_time);

		/**
		 Switches the mode of this renderer. 
		 Windowed mode is switched to full screen mode and vice versa.
		 */
		void SwitchMode();

		/**
		 Main window handle of this renderer.
		 */
		HWND m_hwindow;

		/**
		 Flag indicating wether this renderer is loaded.
		 */
		bool m_loaded;

		/**
		 Flag indicating wether this renderer uses full screen (@c false) or windowed mode (c true).
		 */
		bool m_windowed;

		D3D_DRIVER_TYPE           m_driver_type;
		D3D_FEATURE_LEVEL		  m_feature_level;
		ID3D11Device2            *m_device2;
		ID3D11DeviceContext2     *m_device_context2;
		IDXGISwapChain2          *m_swap_chain2;
		ID3D11RenderTargetView   *m_render_target_view;
		ID3D11Texture2D          *m_depth_stencil;
		ID3D11DepthStencilView   *m_depth_stencil_view;
	};

}