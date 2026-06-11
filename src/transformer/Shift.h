#ifndef TRANSFORMER_SHIFT_H
#define TRANSFORMER_SHIFT_H

#include <core/Transformer.h>

class ShiftTransformer : public Transformer
{
	private:
		uint8_t             _shift;
		std::vector<size_t> _interrupt_indices;
	
	public:
		ShiftTransformer(uint8_t shift, const std::vector<size_t>& interrupt_indices);

		void transform(ProcessedText& pt) override;
};

#endif // TRANSFORMER_SHIFT_H