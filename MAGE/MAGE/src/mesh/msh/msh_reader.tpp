#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_tokens.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename VertexT, typename IndexT >
	MSHReader< VertexT, IndexT >::MSHReader(
		vector< VertexT > &vertices, vector< IndexT > &indices)
		: BigEndianBinaryReader(), m_vertices(vertices), m_indices(indices) {}

	template< typename VertexT, typename IndexT >
	MSHReader< VertexT, IndexT >::MSHReader(MSHReader &&reader) = default;

	template< typename VertexT, typename IndexT >
	MSHReader< VertexT, IndexT >::~MSHReader() = default;

	template< typename VertexT, typename IndexT >
	void MSHReader< VertexT, IndexT >::Read() {

		if (!IsHeaderValid()) {
			throw FormattedException("%ls: invalid mesh header.", GetFilename().c_str());
		}

		const uint32_t nb_vertices = ReadValue< uint32_t >();
		const uint32_t nb_indices  = ReadValue< uint32_t >();
		
		const VertexT *vertices = ReadValueArray< VertexT >(nb_vertices);
		m_vertices.assign(vertices, vertices + nb_vertices);

		const IndexT *indices   = ReadValueArray< IndexT >(nb_indices);
		m_indices.assign(indices, indices + nb_indices);
	}

	template< typename VertexT, typename IndexT >
	bool MSHReader< VertexT, IndexT >::IsHeaderValid() {
		const char *magic = MAGE_MSH_MAGIC;
		while (*magic != L'\0') {
			if (ReadValue< uint8_t >() != *magic) {
				return false;
			}
			++magic;
		}
		return true;
	}
}