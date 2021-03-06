#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	DataT *MemoryArena::Alloc(size_t count, bool initialization) {
		// Allocation
		DataT * const ptr = static_cast< DataT * >(Alloc(count * sizeof(DataT)));

		if (!ptr) {
			// The allocation failed.
			return nullptr;
		}

		// Initialization
		if (initialization) {
			for (size_t i = 0; i < count; ++i) {
				new (&ptr[i]) DataT();
			}
		}

		return ptr;
	}
}