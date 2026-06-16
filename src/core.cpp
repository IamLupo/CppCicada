#include <iostream>
#include <map>

#include <core.h>
#include <util/utf8.h>

namespace core
{
void initialize()
{
	for (size_t i = 0; i < core::runes.size(); ++i)
	{
		rune_to_index[core::runes[i].rune] = i;
		latin_to_index[core::runes[i].latin] = i;
	}
}

std::optional<RuneLatinView> to_latin(const Rune& rune)
{
	auto it = rune_to_index.find(rune);

	if (it == rune_to_index.end())
		return std::nullopt;

	return core::runes[it->second].latin;
}

std::optional<RuneLatinView> to_latin(RuneView rune)
{
	auto it = rune_to_index.find(rune);

	if (it == rune_to_index.end())
		return std::nullopt;

	return core::runes[it->second].latin;
}

std::optional<RuneView> to_rune(const RuneLatin& latin)
{
	auto it = latin_to_index.find(latin);

	if (it == latin_to_index.end())
		return std::nullopt;

	return core::runes[it->second].rune;
}

std::optional<RuneView> to_rune(RuneLatinView latin)
{
	auto it = latin_to_index.find(latin);

	if (it == latin_to_index.end())
		return std::nullopt;

	return core::runes[it->second].rune;
}

std::optional<RunePrime> to_prime(const Rune& rune)
{
	auto it = rune_to_index.find(rune);

	if (it == rune_to_index.end())
		return std::nullopt;

	return core::runes[it->second].prime;
}

std::optional<RunePrime> to_prime(RuneView rune)
{
	auto it = rune_to_index.find(rune);

	if (it == rune_to_index.end())
		return std::nullopt;

	return core::runes[it->second].prime;
}

std::optional<RuneIndices> to_rune_indices(const Runes& runes, bool ignore_no_runes)
{
	core::RuneIndices rune_indices;

	// Iterate through all content
	for (size_t i = 0; i < runes.size();)
	{
		// Calculate length of utf8 bytes
		size_t len = util::utf8::char_length(static_cast<unsigned char>(runes[i]));

		// Read the utf8 character
		std::string rune = runes.substr(i, len);

		auto it = core::rune_to_index.find(rune);
		if (it == core::rune_to_index.end())
			return std::nullopt;

		rune_indices.push_back(it->second);

		i += len;
	}

	return rune_indices;
}

std::optional<Runes> to_runes(const std::string& text)
{
	Runes runes = text;
	
	for (const auto& [pattern, replacement] : core::latin_to_runes)
	{
		size_t pos = 0;

		while ((pos = runes.find(pattern, pos)) != std::string::npos)
		{
			runes.replace(pos, pattern.size(), replacement);
			pos += replacement.size(); // length of replacement
		}
	}

	return runes;
}

std::string to_latins(const Runes& runes)
{
	std::string latins;

	// Iterate through all content
	for (size_t i = 0; i < runes.size();)
	{
		// Calculate length of utf8 bytes
		size_t len = util::utf8::char_length(static_cast<unsigned char>(runes[i]));

		// Read the utf8 character
		std::string rune = runes.substr(i, len);
		
		latins += core::to_latin(rune).value_or("?");
		
		i += len;
	}

	return latins;
}

} // namespace core