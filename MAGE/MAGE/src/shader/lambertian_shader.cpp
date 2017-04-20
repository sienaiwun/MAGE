//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "rendering\rendering_factory.hpp"
#include "shader\lambertian_shader.hpp"
#include "shader\cso\lambertian_PS.hpp"
#include "shader\cso\lambertian_VS.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LambertianVertexShader
	//-------------------------------------------------------------------------

	LambertianVertexShader::LambertianVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: VertexShader(device, device_context, MAGE_GUID_LAMBERTIAN_VS, g_lambertian_vs, sizeof(g_lambertian_vs),
			VertexPositionNormalTexture::input_element_desc, VertexPositionNormalTexture::nb_input_elements) {

		const HRESULT result_transform_buffer_create = CreateConstantBuffer< TransformBuffer >(m_device, m_transform_buffer.ReleaseAndGetAddressOf());
		if (FAILED(result_transform_buffer_create)) {
			Error("Transformation constant buffer creation failed: %08X.", result_transform_buffer_create);
			return;
		}
	}

	void LambertianVertexShader::PrepareShading(const Material &material, const World &world, const TransformBuffer &transform_buffer) const {
		UNUSED(world);
		UNUSED(material);
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->UpdateSubresource(m_transform_buffer.Get(), 0, nullptr, &transform_buffer, 0, 0);
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		m_device_context->VSSetConstantBuffers(0, 1, m_transform_buffer.GetAddressOf());
	}

	//-------------------------------------------------------------------------
	// LambertianPixelShader
	//-------------------------------------------------------------------------

	LambertianPixelShader::LambertianPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: PixelShader(device, device_context, MAGE_GUID_LAMBERTIAN_PS, g_lambertian_ps, sizeof(g_lambertian_ps)) {

		const HRESULT result_material_buffer_create = CreateConstantBuffer< MaterialBuffer >(m_device, m_material_buffer.ReleaseAndGetAddressOf());
		if (FAILED(result_material_buffer_create)) {
			Error("Material constant buffer creation failed: %08X.", result_material_buffer_create);
			return;
		}
	}

	void LambertianPixelShader::PrepareShading(const Material &material, const World &world) const {
		UNUSED(world);

		const MaterialBuffer material_buffer = material.GetBuffer();
		m_device_context->UpdateSubresource(m_material_buffer.Get(), 0, nullptr, &material_buffer, 0, 0);
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		m_device_context->PSSetConstantBuffers(1, 1, m_material_buffer.GetAddressOf());

		// TODO
		if (material.m_diffuse_reflectivity_texture) {
			m_device_context->PSSetShaderResources(0, 1, material.m_diffuse_reflectivity_texture->GetTextureResourceViewAddress());
		}
	}

	//-------------------------------------------------------------------------
	// Combined Lambertian Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateLambertianShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		ResourceFactory *factory = GetResourceFactory();
		SharedPtr< VertexShader > vs = factory->CreateLambertianVertexShader(device, device_context);
		SharedPtr< PixelShader >  ps = factory->CreateLambertianPixelShader(device, device_context);
		return CombinedShader(vs, ps);
	}
}