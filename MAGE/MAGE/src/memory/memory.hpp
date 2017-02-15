#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include <memory>
namespace mage {

	template < typename T >
	using UniquePtr = std::unique_ptr< T >;

	using std::make_unique;

	template < typename T >
	using SharedPtr = std::shared_ptr< T >;
}

#include <wrl.h>
namespace mage {

	template < typename T >
	using ComPtr = Microsoft::WRL::ComPtr< T >;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#ifndef MAGE_POINTER_SIZE
#if defined(__amd64__) || defined(_M_X64)
#define MAGE_POINTER_SIZE 8
#elif defined(__i386__) || defined(_M_IX86)
#define MAGE_POINTER_SIZE 4
#endif
#endif

// Memory management macros
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p) = nullptr; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p) = nullptr; } }

// Supresses C4100: unreferenced formal parameter
#define UNUSED(param) (void)(param)

#pragma endregion