#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj\obj_tokens.hpp"
#include "string\string_utils.hpp"
#include "logging\error.hpp"
#include "file\file_utils.hpp"
#include "mesh\vertex.hpp"
#include "material\material_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT OBJReader< VertexT >::Preprocess() {
		if (!m_model_output.vertex_buffer.empty()) {
			Error("%ls: vertex buffer must be empty.", GetFilename().c_str());
			return E_FAIL;
		}
		if (!m_model_output.index_buffer.empty()) {
			Error("%ls: index buffer must be empty.", GetFilename().c_str());
			return E_FAIL;
		}

		// Begin current group.
		m_model_output.StartModelPart(MAGE_MODEL_PART_DEFAULT_CHILD);

		return S_OK;
	}

	template < typename VertexT >
	HRESULT OBJReader< VertexT >::Postprocess() {
		// End current group.
		m_model_output.EndModelPart();

		return S_OK;
	}

	template < typename VertexT >
	HRESULT OBJReader< VertexT >::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_OBJ_COMMENT_CHAR) {
			return S_OK;
		}

		if (str_equals(token, MAGE_OBJ_MATERIAL_LIBRARY_TOKEN)) {
			ReadOBJMaterialLibrary();
		}
		else if (str_equals(token, MAGE_OBJ_MATERIAL_USE_TOKEN)) {
			ReadOBJMaterialUse();
		}
		else if (str_equals(token, MAGE_OBJ_GROUP_TOKEN)) {
			ReadOBJGroup();
		}
		else if (str_equals(token, MAGE_OBJ_OBJECT_TOKEN)) {
			ReadOBJObject();
		}
		else if (str_equals(token, MAGE_OBJ_VERTEX_TOKEN)) {
			ReadOBJVertex();
		}
		else if (str_equals(token, MAGE_OBJ_TEXTURE_TOKEN)) {
			ReadOBJVertexTexture();
		}
		else if (str_equals(token, MAGE_OBJ_NORMAL_TOKEN)) {
			ReadOBJVertexNormal();
		}
		else if (str_equals(token, MAGE_OBJ_FACE_TOKEN)) {
			ReadOBJTriangleFace();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		ReadLineRemaining();

		return S_OK;
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJMaterialLibrary() {
		const wstring mtl_path = mage::GetPathName(GetFilename());
		const wstring mtl_name = str_convert(ReadString());
		const wstring mtl_fname = mage::GetFilename(mtl_path, mtl_name);

		const HRESULT result = ImportMaterialFromFile(mtl_fname, m_model_output.material_buffer);
		if (FAILED(result)) {
			Error("%ls: line %u: %ls could not be loaded.", GetFilename().c_str(), GetCurrentLineNumber(), mtl_fname.c_str());
		}
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJMaterialUse() {
		const string mtl_name = ReadString();
		m_model_output.SetMaterial(mtl_name);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJGroup() {
		const string child = ReadString();
		if (child == MAGE_MODEL_PART_DEFAULT_CHILD) {
			if (!m_model_output.index_buffer.empty()) {
				Error("%ls: line %u: default child name can only be explicitly defined before all face definitions.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return;
		}
		if (m_model_output.HasModelPart(child)) {
			Error("%ls: line %u: child name redefinition: %s.", GetFilename().c_str(), GetCurrentLineNumber(), child.c_str());
			return;
		}
		
		const string parent = HasString() ? ReadString() : MAGE_MODEL_PART_DEFAULT_PARENT;
		
		m_model_output.EndModelPart();
		m_model_output.StartModelPart(child, parent);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJObject() {}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertex() {
		const Point3 vertex = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexCoordinates()) :
			ReadOBJVertexCoordinates();

		m_vertex_coordinates.push_back(vertex);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertexTexture() {
		const UV texture = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexTextureCoordinates()) :
			ReadOBJVertexTextureCoordinates();

		m_vertex_texture_coordinates.push_back(texture);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertexNormal() {
		const Normal3 normal = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexNormalCoordinates()) :
			ReadOBJVertexNormalCoordinates();
		const XMVECTOR v = XMLoadFloat3(&normal);
		const XMVECTOR normal_v = XMVector3Normalize(v);
		XMLoadFloat3(&normal);

		m_vertex_normal_coordinates.push_back(normal);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJTriangleFace() {
		vector< uint32_t > indices;
		while (indices.size() < 3 || HasString()) {
			const XMUINT3 vertex_indices = ReadOBJVertexIndices();

			const map< XMUINT3, uint32_t >::const_iterator it = m_mapping.find(vertex_indices);
			if (it != m_mapping.cend()) {
				indices.push_back(it->second);
			}
			else {
				const uint32_t index = (uint32_t)m_model_output.vertex_buffer.size();
				indices.push_back(index);
				m_model_output.vertex_buffer.push_back(ConstructVertex(vertex_indices));
				m_mapping[vertex_indices] = index;
			}
		}

		if (m_mesh_desc.ClockwiseOrder()) {
			for (size_t i = 1; i < indices.size() - 1; ++i) {
				m_model_output.index_buffer.push_back(indices[0]);
				m_model_output.index_buffer.push_back(indices[i + 1]);
				m_model_output.index_buffer.push_back(indices[i]);
			}
		}
		else {
			for (size_t i = 1; i < indices.size() - 1; ++i) {
				m_model_output.index_buffer.push_back(indices[0]);
				m_model_output.index_buffer.push_back(indices[i]);
				m_model_output.index_buffer.push_back(indices[i + 1]);
			}
		}
	}

	template < typename VertexT >
	Point3 OBJReader< VertexT >::ReadOBJVertexCoordinates() {
		return (Point3)ReadFloat3();
	}

	template < typename VertexT >
	Normal3 OBJReader< VertexT >::ReadOBJVertexNormalCoordinates() {
		return (Normal3)ReadFloat3();
	}

	template < typename VertexT >
	UV OBJReader< VertexT >::ReadOBJVertexTextureCoordinates() {
		return (UV)ReadFloat2();
	}

	template < typename VertexT >
	XMUINT3 OBJReader< VertexT >::ReadOBJVertexIndices() {
		const char *token = ReadChars();

		uint32_t vertex_index = 0;
		uint32_t texture_index = 0;
		uint32_t normal_index = 0;

		if (str_contains(token, "//")) {
			// v1//vn1
			const char *index_end = strchr(token, '/');
			if (StringToUInt32(token, index_end, vertex_index) == invalid_token) {
				Error("%ls: line %u: invalid vertex index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
			if (StringToUInt32(index_end + 2, normal_index) == invalid_token) {
				Error("%ls: line %u: invalid normal index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
		}
		else if (str_contains(token, '/')) {
			// v1/vt1 or v1/vt1/vn1
			const char *index_end = strchr(token, '/');
			if (StringToUInt32(token, index_end, vertex_index) == invalid_token) {
				Error("%ls: line %u: invalid vertex index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
			
			if (str_contains(index_end + 1, '/')) {
				const char *texture_end = strchr(index_end + 1, '/');
				if (StringToUInt32(index_end + 1, texture_end, texture_index) == invalid_token) {
					Error("%ls: line %u: invalid texture index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
				}
				if (StringToUInt32(texture_end + 1, normal_index) == invalid_token) {
					Error("%ls: line %u: invalid normal index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
				}
			}
			else if (StringToUInt32(index_end + 1, texture_index) == invalid_token) {
				Error("%ls: line %u: invalid texture index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
		}
		else if (StringToUInt32(token, vertex_index) == invalid_token) {
			Error("%ls: line %u: invalid vertex index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		return XMUINT3(vertex_index, texture_index, normal_index);
	}

	template < typename VertexT >
	VertexT OBJReader< VertexT >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexT vertex;
		if (vertex_indices.x) {
			vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.y) {
			vertex.tex = m_vertex_texture_coordinates[vertex_indices.y - 1];
		}
		if (vertex_indices.z) {
			vertex.n = m_vertex_normal_coordinates[vertex_indices.z - 1];
		}
		return vertex;
	}

	template <>
	inline VertexPosition OBJReader< VertexPosition >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPosition vertex;
		if (vertex_indices.x) {
			vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
		}
		return vertex;
	}

	template <>
	inline VertexPositionNormal OBJReader< VertexPositionNormal >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPositionNormal vertex;
		if (vertex_indices.x) {
			vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.z) {
			vertex.n = m_vertex_normal_coordinates[vertex_indices.z - 1];
		}
		return vertex;
	}

	template <>
	inline VertexPositionTexture OBJReader< VertexPositionTexture >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPositionTexture vertex;
		if (vertex_indices.x) {
			vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.y) {
			vertex.tex = m_vertex_texture_coordinates[vertex_indices.y - 1];
		}
		return vertex;
	}
}