#include <core.h>

namespace core
{
void initialize()
{
	for (size_t i = 0; i < RUNE_TABLE.size(); ++i)
	{
		rune_to_index[RUNE_TABLE[i].rune] = i;
		latin_to_index[RUNE_TABLE[i].latin] = i;
	}
}

std::optional<std::string_view> to_latin(std::string_view rune)
{
	auto it = rune_to_index.find(rune);
	if (it == rune_to_index.end())
		return std::nullopt;

	return RUNE_TABLE[it->second].latin;
}

std::optional<std::vector<uint8_t>> to_rune_indices(std::string_view text)
{
	std::vector<uint8_t> rune_indices;

	for(auto& s : text)
	{
		std::string_view key(&s, 1);

		auto it = latin_to_index.find(key);

		if (it == latin_to_index.end())
			return std::nullopt;

		rune_indices.push_back(it->second);
	}

	return rune_indices;
}

std::optional<std::string_view> to_rune(std::string_view latin)
{
	auto it = latin_to_index.find(latin);
	if (it == latin_to_index.end())
		return std::nullopt;

	return RUNE_TABLE[it->second].rune;
}

std::optional<uint8_t> to_prime(std::string_view rune)
{
	auto it = rune_to_index.find(rune);
	if (it == rune_to_index.end())
		return std::nullopt;

	return RUNE_TABLE[it->second].prime;
}

} // namespace core