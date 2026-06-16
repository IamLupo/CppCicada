#ifndef TRANSFORMER_SHIFT_H
#define TRANSFORMER_SHIFT_H

#include <core/types.h>
#include <transformer/Transformer.h>

namespace transformer
{
	class Shift : public Transformer
	{
		private:
			uint8_t                    _shift;
			core::RuneInterruptIndices _interrupt_indices;
		
		public:
			Shift(uint8_t shift, const core::RuneInterruptIndices& interrupt_indices);

			void transform(ProcessedText& pt) override;
	};

} // namespace transformer

#endif // TRANSFORMER_SHIFT_H