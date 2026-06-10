#ifndef TRANSFORMER_VIGENERE_H
#define TRANSFORMER_VIGENERE_H

#include <core/Transformer.h>

class VigenereTransformer : public Transformer
{
	private:
		std::vector<uint8_t> _key;
		std::vector<size_t>  _interrupt_indices;

	public:
		VigenereTransformer(const std::string_view& key, const std::vector<size_t>& interrupt_indices);
		
		void transform(ProcessedText& pt) override;
};

#endif // TRANSFORMER_VIGENERE_H
