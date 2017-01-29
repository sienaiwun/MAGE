//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh_loader.hpp"
#include "logging\error.hpp"
#include "file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT LoadMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer) {

		const wstring extension = GetFileExtension(fname);
		
		if (extension == L"obj" || extension == L"OBJ") {
			return LoadOBJMeshFromFile(fname, vertex_buffer, index_buffer);
		}
		
		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}

	HRESULT LoadMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"obj" || extension == L"OBJ") {
			return LoadOBJMeshFromFile(fname, vertex_buffer);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}