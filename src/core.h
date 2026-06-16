#ifndef CORE_H
#define CORE_H

#include <array>
#include <unordered_map>
#include <optional>
#include <string>
 
#include <core/types.h>

namespace core
{
	struct RuneEntry
	{
		RuneView rune;
		RuneLatinView latin;
		RunePrime prime;
	};

	struct CharMap
	{
		char key;
		std::string_view value;
	};

	inline constexpr std::array<CharMap, 8> punctuation = {{
		{'.', ".\n"},
		{'-', " "},
		{'%', "\n\n"},
		{'/', ""},
		{'&', "\n"},
		{'\n', ""},
		{'*', "'"},
		{'#', "\""}
	}};

	inline constexpr std::array<RuneEntry, 29> runes = {{
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

	inline std::unordered_map<RuneView, RuneIndex> rune_to_index;
	inline std::unordered_map<RuneLatinView, RuneIndex> latin_to_index;

	inline const std::vector<std::pair<RuneLatinView, RuneView>> latin_to_runes = {
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

	std::optional<RuneLatinView> to_latin(const Rune& rune);
	std::optional<RuneLatinView> to_latin(RuneView rune);

	std::optional<RuneView> to_rune(const RuneLatin& latin);
	std::optional<RuneView> to_rune(RuneLatinView latin);
	
	std::optional<RunePrime> to_prime(const Rune& rune);
	std::optional<RunePrime> to_prime(RuneView rune);

	std::optional<RuneIndices> to_rune_indices(const Runes& runes, bool ignore_no_runes = false);
	std::optional<Runes> to_runes(const std::string& text);
	std::string to_latins(const Runes& runes);

	namespace unsafe
	{
		inline core::RuneLatinView to_latin(const core::Rune& rune)
		{
			return core::runes[rune_to_index[rune]].latin;
		}

		inline core::RuneView to_rune(const core::RuneLatin& latin)
		{
			return core::runes[latin_to_index[latin]].rune;
		}

		inline core::RunePrime to_prime(const core::Rune& rune)
		{
			return core::runes[rune_to_index[rune]].prime;
		}

		constexpr std::optional<std::string_view> punct_map(std::string_view sv)
		{
			if (sv.size() != 1)
				return std::nullopt;

			char c = sv[0];
			
			for (const auto& p : core::punctuation)
			{
				if (p.key == c)
					return p.value;
			}
			
			return std::nullopt;
		}
	
	} // namespace unsafe
} // namespace core

#endif // CORE_H