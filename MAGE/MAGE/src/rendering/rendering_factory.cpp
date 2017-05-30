//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Blend states
	//-------------------------------------------------------------------------

	HRESULT CreateBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state, D3D11_BLEND src_blend, D3D11_BLEND dest_blend) {
		D3D11_BLEND_DESC desc = {};
		desc.RenderTarget[0].BlendEnable           = (src_blend != D3D11_BLEND_ONE) || (dest_blend != D3D11_BLEND_ZERO);
		desc.RenderTarget[0].SrcBlend              = src_blend;
		desc.RenderTarget[0].SrcBlendAlpha         = src_blend;
		desc.RenderTarget[0].DestBlend             = dest_blend;
		desc.RenderTarget[0].DestBlendAlpha        = dest_blend;
		desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return device->CreateBlendState(&desc, blend_state);
	}
	HRESULT CreateOpaqueBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state) {
		return CreateBlendState(device, blend_state, D3D11_BLEND_ONE, D3D11_BLEND_ZERO);
	}
	HRESULT CreateAlphaBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state) {
		return CreateBlendState(device, blend_state, D3D11_BLEND_ONE, D3D11_BLEND_INV_SRC_ALPHA);
	}
	HRESULT CreateAdditiveBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state) {
		return CreateBlendState(device, blend_state, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE);
	}
	HRESULT CreateNonPremultipliedBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state) {
		return CreateBlendState(device, blend_state, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA);
	}

	//-------------------------------------------------------------------------
	// Depth stencil states
	//-------------------------------------------------------------------------

	HRESULT CreateDepthStencilState(ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state, bool enable, bool write_enable) {
		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable                  = enable;
		desc.DepthWriteMask               = write_enable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc                    = D3D11_COMPARISON_LESS_EQUAL;
		desc.StencilEnable                = false;
		desc.StencilReadMask              = D3D11_DEFAULT_STENCIL_READ_MASK;
		desc.StencilWriteMask             = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		desc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
		desc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace                     = desc.FrontFace;

		return device->CreateDepthStencilState(&desc, depth_stencil_state);
	}
	HRESULT CreateDepthNoneDepthStencilState(ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state) {
		return CreateDepthStencilState(device, depth_stencil_state, false, false);
	}
	HRESULT CreateDepthDefaultDepthStencilState(ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state) {
		return CreateDepthStencilState(device, depth_stencil_state, true, true);
	}
	HRESULT CreateDepthReadDepthStencilState(ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state) {
		return CreateDepthStencilState(device, depth_stencil_state, true, false);
	}

	//-------------------------------------------------------------------------
	// Rasterizer states
	//-------------------------------------------------------------------------

	HRESULT CreateRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state, D3D11_CULL_MODE cull_mode, D3D11_FILL_MODE fill_mode) {
		D3D11_RASTERIZER_DESC desc = {};
		desc.CullMode          = cull_mode;
		desc.FillMode          = fill_mode;
		desc.DepthClipEnable   = true;
		desc.MultisampleEnable = true;

		return device->CreateRasterizerState(&desc, rasterizer_state);
	}
	HRESULT CreateCullNoneRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state) {
		return CreateRasterizerState(device, rasterizer_state, D3D11_CULL_NONE, D3D11_FILL_SOLID);
	}
	HRESULT CreateCullClockwiseRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state) {
		return CreateRasterizerState(device, rasterizer_state, D3D11_CULL_FRONT, D3D11_FILL_SOLID);
	}
	HRESULT CreateCullCounterClockwiseRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state) {
		return CreateRasterizerState(device, rasterizer_state, D3D11_CULL_BACK, D3D11_FILL_SOLID);
	}
	HRESULT CreateWireframeRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state) {
		return CreateRasterizerState(device, rasterizer_state, D3D11_CULL_NONE, D3D11_FILL_WIREFRAME);
	}

	//-------------------------------------------------------------------------
	// Sampler states
	//-------------------------------------------------------------------------

	HRESULT CreateSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_mode) {
		D3D11_SAMPLER_DESC desc = {};
		desc.Filter         = filter;
		desc.AddressU       = address_mode;
		desc.AddressV       = address_mode;
		desc.AddressW       = address_mode;
		desc.MaxAnisotropy  = (device->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? D3D11_MAX_MAXANISOTROPY : 2;
		desc.MaxLOD         = D3D11_FLOAT32_MAX;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		return device->CreateSamplerState(&desc, sampler_state);
	}
	HRESULT CreatePointWrapSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state) {
		return CreateSamplerState(device, sampler_state, D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
	}
	HRESULT CreatePointClampSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state) {
		return CreateSamplerState(device, sampler_state, D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_CLAMP);
	}
	HRESULT CreateLinearWrapSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state) {
		return CreateSamplerState(device, sampler_state, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
	}
	HRESULT CreateLinearClampSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state) {
		return CreateSamplerState(device, sampler_state, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP);
	}
	HRESULT CreateAnisotropicWrapSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state) {
		return CreateSamplerState(device, sampler_state, D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_WRAP);
	}
	HRESULT CreateAnisotropicClampSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state) {
		return CreateSamplerState(device, sampler_state, D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_CLAMP);
	}
}