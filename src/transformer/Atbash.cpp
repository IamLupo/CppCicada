#include <transformer/Atbash.h>

#include <core/ProcessedText.h>

void AtbashTransformer::transform(ProcessedText& pt)
{
	auto& indices = pt.rune_indices();

	for (auto& i : indices)
	{
		i = 28 - i; // example mutation
	}
}
