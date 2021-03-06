#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	inline void BigEndianBinaryWriter::WriteValue(const DataT &data) {
		WriteValueArray(&data, 1);
	}

	template< typename DataT >
	inline void BigEndianBinaryWriter::WriteValueArray(const DataT *data, size_t count) {
		Assert(data);
		
		const size_t count_written = fwrite(data, sizeof(DataT), count, m_file_stream.get());
		if (count != count_written) {
			throw FormattedException("%ls: could not write all data to file.", GetFilename().c_str());
		}
	}
}