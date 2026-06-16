#include <transformer/Transformer.h>
#include <core/ProcessedText.h>

void UnsolvedTransformer::transform(ProcessedText& pt)
{
	pt.SetUnsolved();
}
