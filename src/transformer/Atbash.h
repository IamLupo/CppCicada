#ifndef TRANSFORMER_ATBASH_H
#define TRANSFORMER_ATBASH_H

#include <transformer/Transformer.h>

namespace transformer
{
	class Atbash : public Transformer
	{
		public:
			void transform(ProcessedText& pt) override;
	};

} // namespace transformer

#endif // TRANSFORMER_ATBASH_H