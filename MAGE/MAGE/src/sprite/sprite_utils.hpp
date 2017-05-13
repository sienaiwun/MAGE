#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Converts the given @c RECT (left, top, right, bottom) 
	 to a @c XMVECTOR (left, top, right, bottom).

	 @param[in]		rect
					A reference to the rectangle.
	 @return		A @c XMVECTOR  (left, top, right, bottom) representing 
					the given @c RECT (left, top, right, bottom).
	 */
	inline const XMVECTOR XMVectorLeftTopRightBottom(const RECT &rect) noexcept {
		const XMVECTOR v = XMLoadInt4(reinterpret_cast<const uint32_t *>(&rect));
		return XMConvertVectorIntToFloat(v, 0);
	}

	/**
	 Converts the given @c RECT (left, top, right, bottom)
	 to a @c XMVECTOR (left, top, width, height).

	 @param[in]		rect
					A reference to the rectangle.
	 @return		A @c XMVECTOR  (left, top, width, height) representing
					the given @c RECT (left, top, right, bottom).
	 */
	inline const XMVECTOR XMVectorLeftTopWidthHeight(const RECT &rect) noexcept {
		const XMVECTOR v = XMVectorLeftTopRightBottom(rect);
		return v - XMVectorPermute< 0, 1, 4, 5 >(XMVectorZero(), v);

	}

	/**
	 Returns the viewport transform for the given device context and rotation mode.

	 @pre			@a device_context is not equal to @c nullptr.
	 @param[in]		device_context
					A pointer to the device context.
	 @param[in]		rotation_mode
					The rotation mode.
	 @return		The viewport transform for 
					the given device context and rotation mode.
	 @throws		FormattedException
					A viewport needs to be set.
	 */
	const XMMATRIX GetViewportTransform(ID3D11DeviceContext *device_context, DXGI_MODE_ROTATION rotation_mode);

	/**
	 Returns the viewport transform for the given device context and rotation mode.

	 @pre			@a device_context is not equal to @c nullptr.
	 @pre			@a viewport is not equal to @c nullptr.
	 @param[in]		device_context
					A pointer to the device context.
	 @param[in]		rotation_mode
					The rotation mode.
	 @param[out]	viewport
					A pointer to the viewport.
	 @return		The viewport transform for
					the given device context and rotation mode.
	 @throws		FormattedException
					A viewport needs to be set.
	 */
	const XMMATRIX GetViewportTransform(ID3D11DeviceContext *device_context, DXGI_MODE_ROTATION rotation_mode, D3D11_VIEWPORT *viewport);
	
	/**
	 Returns the viewport transform for the viewport and rotation mode.

	 @param[in]		viewport
					A reference to the viewport.
	 @param[in]		rotation_mode
					The rotation mode.
	 @return		The viewport transform for
					the given viewport and rotation mode.
	 */
	const XMMATRIX GetViewportTransform(const D3D11_VIEWPORT &viewport, DXGI_MODE_ROTATION rotation_mode) noexcept;

	/**
	 Returns the size of the given 2D texture.
		
	 @pre			@a texture is not equal to @c nullptr.
	 @param[in]		texture
					A pointer the (texture) shader resource view.
	 @return		The size of the given 2D texture as a
					@c XMVECTOR (width, height, width, height).
	 @throws		FormattedException
					The resource of the given shader resource view
					must be convertible to a @c ID3D11Texture2D.
	 */
	const XMVECTOR GetTexture2DSize(ID3D11ShaderResourceView *texture);
}