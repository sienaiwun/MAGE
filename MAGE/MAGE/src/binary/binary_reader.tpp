#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ValueT >
	inline const ValueT &BigEndianBinaryReader::ReadValue() {
		return *ReadValueArray< ValueT >(1);
	}

	template< typename ValueT >
	const ValueT *BigEndianBinaryReader::ReadValueArray(size_t count) {
		const uint8_t *new_pos = m_pos + sizeof(ValueT) * count;
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no %llu values found.", GetFilename().c_str(), count);
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no %llu values found.", GetFilename().c_str(), count);
		}

		const ValueT *result = BytesBigEndianToValue< ValueT >(m_pos);
		m_pos = new_pos;
		return result;
	}
}