#ifndef TRANSFORMER_SHIFT_H
#define TRANSFORMER_SHIFT_H

#include <transformer/Transformer.h>

namespace transformer
{
	class Shift : public Transformer
	{
		private:
			uint8_t             _shift;
			std::vector<size_t> _interrupt_indices;
		
		public:
			Shift(uint8_t shift, const std::vector<size_t>& interrupt_indices);

			void transform(ProcessedText& pt) override;
	};

} // namespace transformer

#endif // TRANSFORMER_SHIFT_H