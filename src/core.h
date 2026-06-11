#ifndef CORE_H
#define CORE_H

#include <array>
#include <string_view>
#include <cstdint>
#include <unordered_map>
#include <optional>
#include <vector>
#include <string>
 
namespace core
{
	struct RuneEntry
	{
		std::string_view rune;
		std::string_view latin;
		uint8_t prime;
	};

	struct CharMap
	{
		char key;
		std::string_view value;
	};

	inline constexpr std::array<CharMap, 8> G_PUNCT = {{
		{'.', ".\n"},
		{'-', " "},
		{'%', "\n\n"},
		{'/', ""},
		{'&', "\n"},
		{'\n', ""},
		{'*', "'"},
		{'#', "\""}
	}};

	inline constexpr std::array<RuneEntry, 29> RUNE_TABLE = {{
		{"ᚠ", "F", 2},
		{"ᚢ", "V", 3},
		{"ᚦ", "TH", 5},
		{"ᚩ", "O", 7},
		{"ᚱ", "R", 11},
		{"ᚳ", "C", 13},
		{"ᚷ", "G", 17},
		{"ᚹ", "W", 19},
		{"ᚻ", "H", 23},
		{"ᚾ", "N", 29},
		{"ᛁ", "I", 31},
		{"ᛄ", "J", 37},
		{"ᛇ", "EO", 41},
		{"ᛈ", "P", 43},
		{"ᛉ", "X", 47},
		{"ᛋ", "S", 53},
		{"ᛏ", "T", 59},
		{"ᛒ", "B", 61},
		{"ᛖ", "E", 67},
		{"ᛗ", "M", 71},
		{"ᛚ", "L", 73},
		{"ᛝ", "NG", 79},
		{"ᛟ", "OE", 83},
		{"ᛞ", "D", 89},
		{"ᚪ", "A", 97},
		{"ᚫ", "AE", 101},
		{"ᚣ", "Y", 103},
		{"ᛡ", "IA", 107},
		{"ᛠ", "EA", 109}
	}};

	inline std::unordered_map<std::string_view, size_t> rune_to_index;
	inline std::unordered_map<std::string_view, size_t> latin_to_index;

	inline const std::vector<std::pair<std::string, std::string>> latin_to_runes = {
		// Latin values that are the same rune
		{ "ING", "NG"  },	// BEING       -> BENG
		{ "ION", "IAN" },	// INSTRUCTION -> INSTRVCTIAN
		{ "QU",  "CW"  },	// QUESTION    -> QWESTIAN
		{ "K",   "C"   },	// BOOC        -> BOOK
		{ "U",   "V"   },	// OUR         -> OVR
		{ "Z",   "S"   },	// 
		{ "Q",   "C"   },	// 
		
		// Double latin values
		{"TH", "ᚦ"},
		{"EO", "ᛇ"},
		{"NG", "ᛝ"},
		{"OE", "ᛟ"},
		{"AE", "ᚫ"},
		{"IA", "ᛡ"},
		{"EA", "ᛠ"},

		// Single latin values
		{"F", "ᚠ"},
		{"V", "ᚢ"},
		{"O", "ᚩ"},
		{"R", "ᚱ"},
		{"C", "ᚳ"},
		{"G", "ᚷ"},
		{"W", "ᚹ"},
		{"H", "ᚻ"},
		{"N", "ᚾ"},
		{"I", "ᛁ"},
		{"J", "ᛄ"},
		{"P", "ᛈ"},
		{"X", "ᛉ"},
		{"S", "ᛋ"},
		{"T", "ᛏ"},
		{"B", "ᛒ"},
		{"E", "ᛖ"},
		{"M", "ᛗ"},
		{"L", "ᛚ"},
		{"D", "ᛞ"},
		{"A", "ᚪ"},
		{"Y", "ᚣ"}
	};

	// Functions
	void initialize();

	std::optional<std::string_view> to_latin(std::string_view rune);
	std::optional<std::string_view> to_rune(std::string_view latin);
	std::optional<uint8_t> to_prime(std::string_view rune);

	std::optional<std::vector<uint8_t>> to_rune_indices(const std::string& runes);
	std::optional<std::string> to_runes(std::string_view text);

	namespace unsafe
	{
		inline std::string_view to_latin(std::string_view rune)
		{
			return RUNE_TABLE[rune_to_index[rune]].latin;
		}

		inline std::string_view to_rune(std::string_view latin)
		{
			return RUNE_TABLE[latin_to_index[latin]].rune;
		}

		inline uint8_t to_prime(std::string_view rune)
		{
			return RUNE_TABLE[rune_to_index[rune]].prime;
		}

		constexpr std::optional<std::string_view> punct_map(std::string_view sv)
		{
			if (sv.size() != 1)
				return std::nullopt;

			char c = sv[0];
			
			for (const auto& p : G_PUNCT)
			{
				if (p.key == c)
					return p.value;
			}
			
			return std::nullopt;
		}
	} // namespace unsafe
} // namespace core

#endif // CORE_H