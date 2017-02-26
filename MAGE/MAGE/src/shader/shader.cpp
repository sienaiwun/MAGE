//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shading.hpp"
#include "shader\shader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VertexShader::VertexShader(const RenderingDevice &device, const wstring &fname, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource(fname) {

		const HRESULT result_shader = InitializeShader(device, input_element_desc, nb_input_elements);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
			return;
		}
	}

	HRESULT VertexShader::InitializeShader(const RenderingDevice &device, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Compile the vertex shader.
		ComPtr< ID3DBlob > vertex_shader_blob;
		const HRESULT result_vertex_shader_blob = D3DReadFileToBlob(GetFilename().c_str(), vertex_shader_blob.GetAddressOf());
		if (FAILED(result_vertex_shader_blob)) {
			Error("D3DReadFileToBlob failed: %ld.", result_vertex_shader_blob);
			return result_vertex_shader_blob;
		}

		// Create the vertex shader.
		const HRESULT result_vertex_shader = device.CreateVertexShader(m_vertex_shader.ReleaseAndGetAddressOf(), vertex_shader_blob);
		if (FAILED(result_vertex_shader)) {
			Error("Vertex shader creation failed: %ld.", result_vertex_shader);
			return result_vertex_shader;
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = device.CreateVertexInputLayout(m_vertex_layout.ReleaseAndGetAddressOf(), vertex_shader_blob, input_element_desc, (UINT)nb_input_elements);
		if (FAILED(result_vertex_input_layout)) {
			Error("Vertex input layout creation failed: %ld.", result_vertex_input_layout);
			return result_vertex_input_layout;
		}

		return S_OK;
	}

	PixelShader::PixelShader(const RenderingDevice &device, const wstring &fname)
		: Resource(fname) {

		const HRESULT result_shader = InitializeShader(device);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
			return;
		}
	}

	HRESULT PixelShader::InitializeShader(const RenderingDevice &device) {

		// Compile the pixel shader.
		ComPtr< ID3DBlob > pixel_shader_blob;
		const HRESULT result_pixel_shader_blob = D3DReadFileToBlob(GetFilename().c_str(), pixel_shader_blob.GetAddressOf());
		if (FAILED(result_pixel_shader_blob)) {
			Error("D3DReadFileToBlob failed: %ld.", result_pixel_shader_blob);
			return result_pixel_shader_blob;
		}

		// Create the pixel shader.
		const HRESULT result_pixel_layout = device.CreatePixelShader(m_pixel_shader.ReleaseAndGetAddressOf(), pixel_shader_blob);
		if (FAILED(result_pixel_layout)) {
			Error("Pixel shader creation failed: %ld.", result_pixel_layout);
			return result_pixel_layout;
		}

		return S_OK;
	}
}