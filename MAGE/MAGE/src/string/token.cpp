//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\token.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Complete String
	//-------------------------------------------------------------------------
#pragma region

	TokenResult StringToBool(const char *str, bool &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		if (str_equals(str, "true")) {
			result = true;
			return TokenResult::Valid;
		}
		
		result = false;
		return (str_equals(str, "false")) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToInt8(const char *str, int8_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< int8_t >(strtol(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToUInt8(const char *str, uint8_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< uint8_t >(strtoul(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToInt16(const char *str, int16_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< int16_t >(strtol(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToUInt16(const char *str, uint16_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< uint16_t >(strtoul(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}

	TokenResult StringToInt32(const char *str, int32_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< int32_t >(strtol(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToUInt32(const char *str, uint32_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< uint32_t >(strtoul(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToInt64(const char *str, int64_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< int64_t >(strtoll(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToUInt64(const char *str, uint64_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< uint64_t >(strtoull(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToFloat(const char *str, float &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToDouble(const char *str, double &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Substring
	//-------------------------------------------------------------------------
#pragma region

	TokenResult StringToBool(const char *begin, const char *end, bool &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		if (end - begin == 4) {
			if ((*begin != 't') || 
				(*(begin + 1) != 'r') || 
				(*(begin + 2) != 'u') || 
				(*(begin + 3) != 'e')) {
				result = false;
				return TokenResult::Invalid;
			}

			result = true;
			return TokenResult::Valid;
		} 
		
		if (end - begin == 5) {
			if ((*begin != 'f') ||
				(*(begin + 1) != 'a') ||
				(*(begin + 2) != 'l') ||
				(*(begin + 3) != 's') ||
				(*(begin + 4) != 'e')) {
				result = false;
				return TokenResult::Invalid;
			}

			result = false;
			return TokenResult::Valid;
		}
		
		result = false;
		return TokenResult::Invalid;
	}
	
	TokenResult StringToInt8(const char *begin, const char *end, int8_t &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< int8_t >(strtol(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToUInt8(const char *begin, const char *end, uint8_t &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< uint8_t >(strtoul(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToInt16(const char *begin, const char *end, int16_t &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< int16_t >(strtol(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToUInt16(const char *begin, const char *end, uint16_t &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< uint16_t >(strtoul(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToInt32(const char *begin, const char *end, int32_t &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< int32_t >(strtol(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToUInt32(const char *begin, const char *end, uint32_t &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< uint32_t >(strtoul(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToInt64(const char *begin, const char *end, int64_t &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< int64_t >(strtoll(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToUInt64(const char *begin, const char *end, uint64_t &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< uint64_t >(strtoull(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToFloat(const char *begin, const char *end, float &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = strtof(begin, &inner_context);
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToDouble(const char *begin, const char *end, double &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = strtod(begin, &inner_context);
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: String Prefix
	//-------------------------------------------------------------------------
#pragma region

	TokenResult StringPrefixToInt8(const char *str, int8_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< int8_t >(strtol(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToUInt8(const char *str, uint8_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< uint8_t >(strtoul(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToInt16(const char *str, int16_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< int16_t >(strtol(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToUInt16(const char *str, uint16_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< uint16_t >(strtoul(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToInt32(const char *str, int32_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< int32_t >(strtol(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToUInt32(const char *str, uint32_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< uint32_t>(strtoul(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToInt64(const char *str, int64_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< int64_t >(strtoll(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToUInt64(const char *str, uint64_t &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< uint64_t >(strtoull(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToFloat(const char *str, float &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToDouble(const char *str, double &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Reading
	//-------------------------------------------------------------------------
#pragma region

	TokenResult ReadChars(char *str, char **context, char **result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(result);
		Assert(delimiters);
		
		*result = strtok_s(str, delimiters, context);
		if (!result) {
			return TokenResult::None;
		}

		return TokenResult::Valid;
	}
	
	TokenResult ReadString(char *str, char **context, string &result, const char *delimiters) {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return TokenResult::None;
		}
		
		result = token;

		return TokenResult::Valid;
	}
	
	TokenResult ReadQuotedString(char *str, char **context, string &result, const char *delimiters) {
		Assert(str || context);
		Assert(delimiters);
		
		char *start = (str) ? SkipDelimiters(str, delimiters) : SkipDelimiters(*context, delimiters);
		if (!start) {
			return TokenResult::None;
		}

		char *first_quote = str_escape_first(start, '"');
		if (!first_quote) {
			return TokenResult::Invalid;
		}
		char *last_quote = str_escape_first(first_quote + 1, '"');
		if (!last_quote) {
			return TokenResult::Invalid;
		}

		if (!str_contains(delimiters, *(last_quote + 1))) {
			return TokenResult::Invalid;
		}

		*last_quote = '\0';
		result = first_quote + 1;
		*context = last_quote + 1;
		return TokenResult::Valid;
	}
	
	TokenResult ReadBool(char *str, char **context, bool &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToBool(token, result);
	}
	
	TokenResult ReadInt8(char *str, char **context, int8_t &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt8(token, result);
	}
	
	TokenResult ReadUInt8(char *str, char **context, uint8_t &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToUInt8(token, result);
	}
	
	TokenResult ReadInt16(char *str, char **context, int16_t &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt16(token, result);
	}
	
	TokenResult ReadUInt16(char *str, char **context, uint16_t &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToUInt16(token, result);
	}
	
	TokenResult ReadInt32(char *str, char **context, int32_t &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt32(token, result);
	}
	
	TokenResult ReadUInt32(char *str, char **context, uint32_t &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToUInt32(token, result);
	}
	
	TokenResult ReadInt64(char *str, char **context, int64_t &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt64(token, result);
	}
	
	TokenResult ReadUInt64(char *str, char **context, uint64_t &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToUInt64(token, result);
	}
	
	TokenResult ReadFloat(char *str, char **context, float &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToFloat(token, result);
	}
	
	TokenResult ReadDouble(char *str, char **context, double &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToDouble(token, result);
	}
	
	TokenResult ReadFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}
		
		return TokenResult::Valid;
	}
	
	TokenResult ReadFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}

		const TokenResult token_result_z = ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != TokenResult::Valid) {
			return token_result_z;
		}

		return TokenResult::Valid;
	}
	
	TokenResult ReadFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}

		const TokenResult token_result_z = ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != TokenResult::Valid) {
			return token_result_z;
		}

		const TokenResult token_result_w = ReadFloat(str, context, result.w, delimiters);
		if (token_result_w != TokenResult::Valid) {
			return token_result_w;
		}

		return TokenResult::Valid;
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Peaking
	//-------------------------------------------------------------------------
#pragma region

	TokenResult HasChars(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		return (start) ? TokenResult::Valid : TokenResult::None;
	}
	
	TokenResult HasString(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);

		return HasChars(str, delimiters);
	}
	
	TokenResult HasQuotedString(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		
		const char *first_quote = str_escape_first(start, '"');
		if (!first_quote) {
			return TokenResult::Invalid;
		}
		const char *last_quote = str_escape_first(first_quote + 1, '"');
		if (!last_quote) {
			return TokenResult::Invalid;
		}
		
		return str_contains(delimiters, *(last_quote + 1)) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult HasBool(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		bool result;
		return StringToBool(start, end, result);
	}
	
	TokenResult HasInt8(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int8_t result;
		return StringToInt8(start, end, result);
	}
	
	TokenResult HasUInt8(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		uint8_t result;
		return StringToUInt8(start, end, result);
	}
	
	TokenResult HasInt16(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int16_t result;
		return StringToInt16(start, end, result);
	}
	
	TokenResult HasUInt16(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		uint16_t result;
		return StringToUInt16(start, end, result);
	}
	
	TokenResult HasInt32(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int32_t result;
		return StringToInt32(start, end, result);
	}
	
	TokenResult HasUInt32(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		uint32_t result;
		return StringToUInt32(start, end, result);
	}
	
	TokenResult HasInt64(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int64_t result;
		return StringToInt64(start, end, result);
	}
	
	TokenResult HasUInt64(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		uint64_t result;
		return StringToUInt64(start, end, result);
	}
	
	TokenResult HasFloat(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		float result;
		return StringToFloat(start, end, result);
	}
	
	TokenResult HasDouble(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		double result;
		return StringToDouble(start, end, result);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Advancing
	//-------------------------------------------------------------------------
#pragma region

	char *SkipDelimiters(char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);

		while (*str != '\0' && str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}
	
	const char *SkipDelimiters(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		while (*str != '\0' && str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}
	
	char *GotoDelimiters(char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}
	
	const char *GotoDelimiters(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}

#pragma endregion
}