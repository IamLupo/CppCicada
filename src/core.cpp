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

std::optional<std::string_view> to_latin(std::string_view rune)
{
	auto it = rune_to_index.find(rune);

	if (it == rune_to_index.end())
		return std::nullopt;

	return core::runes[it->second].latin;
}

std::optional<std::string_view> to_rune(std::string_view latin)
{
	auto it = latin_to_index.find(latin);

	if (it == latin_to_index.end())
		return std::nullopt;

	return core::runes[it->second].rune;
}

std::optional<uint8_t> to_prime(std::string_view rune)
{
	auto it = rune_to_index.find(rune);

	if (it == rune_to_index.end())
		return std::nullopt;

	return core::runes[it->second].prime;
}

std::optional<std::string> to_runes(std::string_view text)
{
	std::string runes = std::string(text);
	
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

std::optional<std::vector<uint8_t>> to_rune_indices(const std::string& runes)
{
	std::vector<uint8_t> rune_indices;

	// Iterate through all content
	for (size_t i = 0; i < runes.size();)
	{
		// Calculate length of utf8 bytes
		size_t len = util::utf8_char_length(static_cast<unsigned char>(runes[i]));

		// Read the utf8 character
		std::string_view rune = runes.substr(i, len);

		auto it = core::rune_to_index.find(rune);
		if (it == core::rune_to_index.end())
			return std::nullopt;

		rune_indices.push_back(it->second);

		i += len;
	}

	return rune_indices;
}

} // namespace core