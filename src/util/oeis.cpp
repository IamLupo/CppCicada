#include <util/oeis.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

namespace util::oeis
{

static uint8_t mod29_from_string(const std::string& s)
{
	bool negative = false;
	size_t i = 0;

	if (s[i] == '-')
	{
		negative = true;
		i++;
	}

	int value = 0;

	for (; i < s.size(); i++)
	{
		char c = s[i];
		if (c < '0' || c > '9')
			continue;

		value = (value * 10 + (c - '0')) % 29;
	}

	if (negative)
		value = (29 - value) % 29;

	return static_cast<uint8_t>(value);
}

static inline std::string trim(const std::string& s)
{
	size_t start = 0;
	while (start < s.size() && std::isspace(s[start])) start++;

	size_t end = s.size();
	while (end > start && std::isspace(s[end - 1])) end--;

	return s.substr(start, end - start);
}

void make_map(const std::string& file_path, UInt8Map& map)
{
	std::ifstream fs(file_path);

	if (!fs.is_open())
		return;

	std::string line;

	while (std::getline(fs, line))
	{
		if (line.empty())
			continue;

		// split at first comma
		size_t pos = line.find(',');

		if (pos == std::string::npos)
			continue;

		std::string key = trim(line.substr(0, pos));
		std::string rest = line.substr(pos + 1);

		StrSeq values;
		std::stringstream ss(rest);
		std::string item;

		while (std::getline(ss, item, ','))
		{
			item = trim(item);

			if (!item.empty())
				values.push_back(item);
		}
		
		UInt8Seq out;
		for(const auto& value : values)
		{
			out.push_back(mod29_from_string(value));
		}

		map[key] = std::move(out);
	}
}

} // namespace util::oeis
