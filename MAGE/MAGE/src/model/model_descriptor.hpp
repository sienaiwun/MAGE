#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_loader.hpp"
#include "mesh\mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class ModelDescriptor : public FileResource {

	public:

		template < typename VertexT >
		ModelDescriptor(ID3D11Device2 &device, const wstring &fname,
			const MeshDescriptor< VertexT > &desc = MeshDescriptor< VertexT >());
		virtual ~ModelDescriptor() {
			m_materials.clear();
			m_model_parts.clear();
		}

		SharedPtr< Mesh > GetMesh() const {
			return m_mesh;
		}
		vector< Material >::const_iterator MaterialsBegin() const {
			return m_materials.cbegin();
		}
		vector< Material >::const_iterator MaterialsEnd() const {
			return m_materials.cend();
		}
		vector< ModelPart >::const_iterator ModelPartsBegin() const {
			return m_model_parts.cbegin();
		}
		vector< ModelPart >::const_iterator ModelPartsEnd() const {
			return m_model_parts.cend();
		}

	private:

		ModelDescriptor(const ModelDescriptor &desc) = delete;
		ModelDescriptor &operator=(const ModelDescriptor &desc) = delete;

		SharedPtr< Mesh > m_mesh;
		vector< Material > m_materials;
		vector< ModelPart > m_model_parts;
	};

	template < typename VertexT >
	SharedPtr< ModelDescriptor > CreateModelDescriptor(const wstring &fname, const MeshDescriptor< VertexT > &desc);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_descriptor.tpp"

#pragma endregion