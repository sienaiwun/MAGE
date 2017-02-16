//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\mtl_loader.hpp"
#include "material\mtl_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportMTLMaterialFromFile(const wstring &fname, vector< Material > &material_buffer) {
		MTLReader parser(material_buffer);
		return parser.ReadFromFile(fname);
	}
}