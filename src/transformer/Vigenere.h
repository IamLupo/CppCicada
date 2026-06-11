#ifndef TRANSFORMER_VIGENERE_H
#define TRANSFORMER_VIGENERE_H

#include <transformer/Transformer.h>

namespace transformer
{
	class Vigenere : public Transformer
	{
		private:
			std::vector<uint8_t> _key;
			std::vector<size_t>  _interrupt_indices;

		public:
			Vigenere(const std::string_view& key, const std::vector<size_t>& interrupt_indices);
			
			void transform(ProcessedText& pt) override;
	};

} // namespace transformer

#endif // TRANSFORMER_VIGENERE_H
