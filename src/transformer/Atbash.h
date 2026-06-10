#ifndef TRANSFORMER_ATBASH_H
#define TRANSFORMER_ATBASH_H

#include <core/Transformer.h>

class AtbashTransformer : public Transformer
{
	public:
		void transform(ProcessedText& pt) override;
};

#endif // TRANSFORMER_ATBASH_H