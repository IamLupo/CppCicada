#ifndef TRANSFORMER_SEQUENCE_H
#define TRANSFORMER_SEQUENCE_H

#include <core/types.h>
#include <transformer/Transformer.h>

namespace transformer
{
	class Sequence : public Transformer
	{
		private:
			const std::vector<uint8_t>&        _sequence;
			const core::RuneInterruptIndices&  _interrupt_indices;

		public:
			Sequence(const std::vector<uint8_t>& sequence, const core::RuneInterruptIndices& interrupt_indices);

			void transform(ProcessedText& pt) override;
	};

} // namespace transformer

#endif // TRANSFORMER_SEQUENCE_H