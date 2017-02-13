#pragma once

//-----------------------------------------------------------------------------
// System Defines
//-----------------------------------------------------------------------------
#pragma region

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <string>
namespace mage {
	using std::wstring;
}

#include <d3d11_2.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "resource\resource.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class PixelShader : Resource {

	public:

		PixelShader(ComPtr< ID3D11Device2 > device, const wstring &fname);
		virtual ~PixelShader() {}
		
		void Update(ComPtr< ID3D11DeviceContext2 > device_context);

	protected:

		HRESULT InitializeShader(ComPtr< ID3D11Device2 > device);

		ComPtr< ID3D11PixelShader > m_pixel_shader;

	private:

		PixelShader(const PixelShader &pixel_shader) = delete;
		PixelShader &operator=(const PixelShader &pixel_shader) = delete;
	};
}