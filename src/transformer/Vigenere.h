#ifndef TRANSFORMER_VIGENERE_H
#define TRANSFORMER_VIGENERE_H

#include <core/types.h>
#include <transformer/Transformer.h>

namespace transformer
{
	class Vigenere : public Transformer
	{
		private:
			core::RuneIndices          _key;
			core::RuneInterruptIndices _interrupt_indices;

		public:
			Vigenere(const core::RuneLatin& key, const core::RuneInterruptIndices& interrupt_indices);
			
			void transform(ProcessedText& pt) override;
	};

} // namespace transformer

#endif // TRANSFORMER_VIGENERE_H
