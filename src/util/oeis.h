
#ifndef UTIL_OEIS_H
#define UTIL_OEIS_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>

namespace util::oeis
{
	// Type definitions
	typedef std::vector<std::string> StrSeq;
	typedef std::vector<uint8_t> UInt8Seq;

	typedef std::map<std::string, UInt8Seq> UInt8Map;

	// The largest sequence in oeis is 348 values.
	const size_t max_sequence = 348;

	// Functions
	void make_map(const std::string& file_path, UInt8Map& map);

} // namespace util::oeis

#endif // UTIL_OEIS_H