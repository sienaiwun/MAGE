//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <windows.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory_arena.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	MemoryArena::~MemoryArena() {
		FreeAligned(GetCurrentBlockPtr());
		for (const pair< size_t, char * > &block : m_used_blocks) {
			FreeAligned(block.second);
		}
		for (const pair< size_t, char * > &block : m_available_blocks) {
			FreeAligned(block.second);
		}
	}

	size_t MemoryArena::GetTotalBlockSize() const {
		size_t size = GetCurrentBlockSize();
		for (const pair< size_t, char * > &block : m_used_blocks) {
			size += block.first;
		}
		for (const pair< size_t, char * > &block : m_available_blocks) {
			size += block.first;
		}
		return size;
	}

	void MemoryArena::Reset() {
		m_current_block_pos = 0;
		m_current_block = pair< size_t, char * >(0, nullptr);
		m_available_blocks.splice(m_available_blocks.begin(), m_used_blocks);
	}

	void *MemoryArena::Alloc(size_t size) {
		// Round up size to minimum machine alignment
		size = ((size + 15) & (~15));

		if (m_current_block_pos + size > GetCurrentBlockSize()) {
			// Store current block (if existing) as used block.
			if (GetCurrentBlockPtr()) {
				m_used_blocks.push_back(m_current_block);
			}

			// Fetch new block from available blocks.
			for (list< pair< size_t, char * > >::iterator it = m_available_blocks.begin(); it != m_available_blocks.end(); ++it) {
				if (it->first >= size) {
					m_current_block = *it;
					m_available_blocks.erase(it);
					break;
				}
			}

			if (!GetCurrentBlockPtr()) {
				// Allocate new block.
				const size_t alloc_size = max(size, GetBlockSize());
				char *alloc_ptr = AllocAligned< char >(alloc_size);
				m_current_block = pair< size_t, char * >(alloc_size, alloc_ptr);
			}

			m_current_block_pos = 0;
		}

		void *ptr = GetCurrentBlockPtr() + m_current_block_pos;
		m_current_block_pos += size;
		return ptr;
	}
}