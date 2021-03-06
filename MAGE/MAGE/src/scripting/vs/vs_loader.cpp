//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\vs\vs_loader.hpp"
#include "scripting\vs\vs_reader.hpp"
#include "scripting\vs\vs_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	void ImportVSFromFile(const wstring &fname, vector< Variable > &variable_buffer) {
		VSReader reader(variable_buffer);
		reader.ReadFromFile(fname);
	}

	void ExportVSToFile(const wstring &fname, const vector< Variable > &variable_buffer) {
		VSWriter writer(variable_buffer);
		writer.WriteToFile(fname);
	}
}