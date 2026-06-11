#ifndef TRANSFORMER_TOTIENT_H
#define TRANSFORMER_TOTIENT_H

#include <core/Transformer.h>

class TotientTransformer : public Transformer
{
	private:
		std::vector<size_t>  _interrupt_indices;

	public:
		TotientTransformer(const std::vector<size_t>& interrupt_indices);
		
		void transform(ProcessedText& pt) override;
};

#endif // TRANSFORMER_TOTIENT_H
