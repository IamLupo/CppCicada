#ifndef TRANSFORMER_TOTIENT_H
#define TRANSFORMER_TOTIENT_H

#include <core/types.h>
#include <transformer/Transformer.h>

namespace transformer
{
	class Totient : public Transformer
	{
		private:
			core::RuneInterruptIndices _interrupt_indices;

		public:
			Totient(const core::RuneInterruptIndices& interrupt_indices);
			
			void transform(ProcessedText& pt) override;
	};

} // namespace transformer

#endif // TRANSFORMER_TOTIENT_H
