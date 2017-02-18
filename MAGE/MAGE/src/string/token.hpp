#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_DELIMITERS " \t\n\r"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	enum TokenResult {
		valid_token,
		no_token,
		invalid_token
	};

	//-------------------------------------------------------------------------
	// String Conversion Utilities
	//-------------------------------------------------------------------------

	TokenResult StringToBool(const char *str, bool &result);
	TokenResult StringToInt8(const char *str, int8_t &result);
	TokenResult StringToUInt8(const char *str, uint8_t &result);
	TokenResult StringToInt16(const char *str, int16_t &result);
	TokenResult StringToUInt16(const char *str, uint16_t &result);
	TokenResult StringToInt32(const char *str, int32_t &result);
	TokenResult StringToUInt32(const char *str, uint32_t &result);
	TokenResult StringToInt64(const char *str, int64_t &result);
	TokenResult StringToUInt64(const char *str, uint64_t &result);
	TokenResult StringToFloat(const char *str, float &result);
	TokenResult StringToDouble(const char *str, double &result);

	TokenResult StringToBool(const char *begin, const char *end, bool &result);
	TokenResult StringToInt8(const char *begin, const char *end, int8_t &result);
	TokenResult StringToUInt8(const char *begin, const char *end, uint8_t &result);
	TokenResult StringToInt16(const char *begin, const char *end, int16_t &result);
	TokenResult StringToUInt16(const char *begin, const char *end, uint16_t &result);
	TokenResult StringToInt32(const char *begin, const char *end, int32_t &result);
	TokenResult StringToUInt32(const char *begin, const char *end, uint32_t &result);
	TokenResult StringToInt64(const char *begin, const char *end, int64_t &result);
	TokenResult StringToUInt64(const char *begin, const char *end, uint64_t &result);
	TokenResult StringToFloat(const char *begin, const char *end, float &result);
	TokenResult StringToDouble(const char *begin, const char *end, double &result);

	TokenResult StringPrefixToInt8(const char *str, int8_t &result);
	TokenResult StringPrefixToUInt8(const char *str, uint8_t &result);
	TokenResult StringPrefixToInt16(const char *str, int16_t &result);
	TokenResult StringPrefixToUInt16(const char *str, uint16_t &result);
	TokenResult StringPrefixToInt32(const char *str, int32_t &result);
	TokenResult StringPrefixToUInt32(const char *str, uint32_t &result);
	TokenResult StringPrefixToInt64(const char *str, int64_t &result);
	TokenResult StringPrefixToUInt64(const char *str, uint64_t &result);
	TokenResult StringPrefixToFloat(const char *str, float &result);
	TokenResult StringPrefixToDouble(const char *str, double &result);

	//-------------------------------------------------------------------------
	// Parsing Utilities
	//-------------------------------------------------------------------------

	TokenResult ReadChars(char *str, char **context, char **result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadString(char *str, char **context, string &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadQuotedString(char *str, char **context, string &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadBool(char *str, char **context, bool &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadInt8(char *str, char **context, int8_t &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadUInt8(char *str, char **context, uint8_t &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadInt16(char *str, char **context, int16_t &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadUInt16(char *str, char **context, uint16_t &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadInt32(char *str, char **context, int32_t &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadUInt32(char *str, char **context, uint32_t &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadInt64(char *str, char **context, int64_t &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadUInt64(char *str, char **context, uint64_t &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadFloat(char *str, char **context, float &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadDouble(char *str, char **context, double &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);

	TokenResult HasChars(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasString(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasQuotedString(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasBool(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasInt8(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasUInt8(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasInt16(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasUInt16(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasInt32(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasUInt32(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasInt64(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasUInt64(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasFloat(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasDouble(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);

	char *SkipDelimiters(char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	const char *SkipDelimiters(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	char *GotoDelimiters(char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	const char *GotoDelimiters(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
}