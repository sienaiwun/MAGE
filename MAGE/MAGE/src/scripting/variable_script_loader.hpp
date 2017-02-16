#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\collection.hpp" 
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the variables from the file with the given filename.

	 @param[in]		fname
					A reference to the filename.
	 @param[in,out]	variable_buffer
					A reference to a vector containing the variables.
	 @return		A success/error value.
	 */
	HRESULT ImportVariableScriptFromFile(const wstring &fname, vector< Variable * > &variable_buffer);

	/**
	 Exports the given variables to the file with the given filename.

	 @param[in]		fname
					A reference to the filename.
	 @param[in]		variable_buffer
					A reference to a vector containing the variables.
	 @return		A success/error value.
	 */
	HRESULT ExportVariableScriptToFile(const wstring &fname, const vector< Variable * > &variable_buffer);
}