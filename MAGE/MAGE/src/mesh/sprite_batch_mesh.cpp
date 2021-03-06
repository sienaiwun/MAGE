//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\sprite_batch_mesh.hpp"
#include "mesh\vertex.hpp"
#include "rendering\rendering_factory.hpp"
#include "collection\collection.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteBatchMesh::SpriteBatchMesh()
		: SpriteBatchMesh(GetRenderingDevice(), GetRenderingDeviceContext()) {}

	SpriteBatchMesh::SpriteBatchMesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
	 : Mesh(device, device_context, sizeof(VertexPositionColorTexture), 
		 DXGI_FORMAT_R16_UINT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {

		SetupVertexBuffer();
		SetupIndexBuffer();	
	}

	SpriteBatchMesh::SpriteBatchMesh(SpriteBatchMesh &&sprite_batch_mesh) = default;

	SpriteBatchMesh::~SpriteBatchMesh() = default;

	void SpriteBatchMesh::SetupVertexBuffer() {
		const HRESULT result_vertex_buffer = CreateDynamicVertexBuffer< VertexPositionColorTexture >(m_device, m_vertex_buffer.ReleaseAndGetAddressOf(), nullptr, MaxVerticesPerBatch());
		if (FAILED(result_vertex_buffer)) {
			throw FormattedException("Vertex buffer creation failed: %08X.", result_vertex_buffer);
		}
	}

	void SpriteBatchMesh::SetupIndexBuffer() {
		static_assert(MaxVerticesPerBatch() < USHRT_MAX, "s_max_sprites_per_batch too large for 16-bit indices.");

		// Create indices.
		vector< uint16_t > indices;
		indices.reserve(MaxIndicesPerBatch());
		for (uint16_t i = 0; i < MaxVerticesPerBatch(); i += s_vertices_per_sprite) {
			// First triangle
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
			// Second triangle
			indices.push_back(i + 1);
			indices.push_back(i + 3);
			indices.push_back(i + 2);
		}

		const HRESULT result_index_buffer = CreateStaticIndexBuffer< uint16_t >(m_device, m_index_buffer.ReleaseAndGetAddressOf(), indices.data(), indices.size());
		if (FAILED(result_index_buffer)) {
			throw FormattedException("Index buffer creation failed: %08X.", result_index_buffer);
		}

		SetNumberOfIndices(indices.size());
	}

	HRESULT SpriteBatchMesh::MapVertexBuffer(D3D11_MAP map_type, D3D11_MAPPED_SUBRESOURCE *mapped_buffer) {
		Assert(mapped_buffer);

		return m_device_context->Map(m_vertex_buffer.Get(), 0, map_type, 0, mapped_buffer);
	}

	void SpriteBatchMesh::UnmapVertexBuffer() {
		m_device_context->Unmap(m_vertex_buffer.Get(), 0);
	}
}