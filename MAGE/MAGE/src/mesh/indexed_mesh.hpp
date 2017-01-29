#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of indexed meshes.
	 */
	class IndexedMesh : Mesh {

	public:

		/**
		 Constructs an indexed mesh.

		 @param[in]		device
						A pointer to an D3D11 device.
		 @param[in]		name
						A reference to the name of the mesh.
		 @param[in]		path
						A reference to the path of the mesh.
		 */
		IndexedMesh(ComPtr< ID3D11Device2 > device, const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);

		/**
		Destructs this indexed mesh.
		*/
		virtual ~IndexedMesh() {}

		size_t GetNbVertices() const {
			return m_nb_vertices;
		}

		virtual HRESULT BindBuffers(ComPtr< ID3D11DeviceContext2 > device_context) const override;

		virtual HRESULT Draw(ComPtr< ID3D11DeviceContext2 > device_context) const override;

	protected:

		HRESULT InitializeBuffers(ComPtr< ID3D11Device2 > device);

		HRESULT SetupVertexBuffer(ComPtr< ID3D11Device2 > device, const Vertex *vertices, size_t nb_vertices);

		HRESULT SetupIndexBuffer(ComPtr< ID3D11Device2 > device, const uint32_t *indices, size_t nb_indices);

		size_t m_nb_vertices;

		ComPtr< ID3D11Buffer > m_vertex_buffer;
		ComPtr< ID3D11Buffer > m_index_buffer;

	private:

		/**
		 Constructs an indexed mesh from the given indexed mesh.

		 @param[in]		indexed_mesh
						A reference to the indexed mesh.
		 */
		IndexedMesh(const IndexedMesh &indexed_mesh) = delete;

		/**
		 Copies the given indexed mesh to this indexed mesh.

		 @param[in]		indexed_mesh
						A reference to the indexed mesh to copy from.
		 @return		A reference to the copy of the given indexed mesh
						(i.e. this indexed mesh).
		 */
		IndexedMesh &operator=(const IndexedMesh &indexed_mesh) = delete;
	};
}