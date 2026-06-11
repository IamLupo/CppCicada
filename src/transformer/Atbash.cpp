#include <transformer/Atbash.h>

#include <core/ProcessedText.h>

namespace transformer
{

void Atbash::transform(ProcessedText& pt)
{
	auto& indices = pt.rune_indices();

	for (auto& i : indices)
	{
		i = 28 - i; // example mutation
	}
}

} // namespace transformer
