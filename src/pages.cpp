#include <core.h>
#include <pages.h>
#include <utf8.h>
#include <core/Transformer.h>
#include <transformer/Atbash.h>
#include <transformer/Vigenere.h>
#include <transformer/Shift.h>

namespace pages
{

void initialize()
{
	// Initialize pages
	for (size_t page_index = 0; page_index < G_PAGES_CONTENT.size(); ++page_index)
	{
		std::vector<size_t> interupters;
		std::vector<uint8_t> rune_indices;

		size_t rune_index = 0;
		
		std::string_view text = G_PAGES_CONTENT[page_index];

		for (size_t i = 0; i < text.size();)
		{
			size_t len = utf8_char_length(static_cast<unsigned char>(text[i]));

			std::string_view rune = text.substr(i, len);
			std::string_view latin = core::to_latin(rune).value_or("?");
			
			if(latin != "?")
			{
				rune_indices.push_back(core::rune_to_index[rune]);
				
				if(rune == "ᚠ")
					interupters.push_back(rune_index);

				rune_index++;
			}

			i += len;
		}
		
		// Save results
		G_PAGES_INTERUPTERS[page_index] = interupters;
		G_PAGES_RUNE_INDICES[page_index] = rune_indices;
	}

	// Set solutions order
	for(int page_index = 6; page_index >= 0; page_index--)
	{
		G_PAGES_TRANSFORMERS[page_index].clear();
	}

	// Set solutions transformers
	G_PAGES_TRANSFORMERS[0].push_back(std::make_unique<AtbashTransformer>());

	G_PAGES_TRANSFORMERS[1].push_back(
		std::make_unique<VigenereTransformer>(
			"DIVINITY", // DIVINITY = ᛞᛁᚢᛁᚾᛁᛏᚣ
			std::vector<size_t>{ 48, 74, 84, 132, 159, 160, 250, 421, 443, 465, 514 }
	));
	
	G_PAGES_TRANSFORMERS[3].push_back(std::make_unique<AtbashTransformer>());
	G_PAGES_TRANSFORMERS[3].push_back(std::make_unique<ShiftTransformer>(
			3, std::vector<size_t>({})
	));

	G_PAGES_TRANSFORMERS[5].push_back(
		std::make_unique<VigenereTransformer>(
			// "CIRCVMFERENCE", // CIRCVMFERENCE = ᚳᛁᚱᚳᚢᛗᚠᛖᚱᛖᚾᚳᛖ
			"FIRFVMFERENFE", // FIRFVMFERENFE = ᚠᛁᚱᚠᚢᛗᚠᛖᚱᛖᚾᚠᛖ
			std::vector<size_t>{ 49, 58 }
	));
}

} // namespace pages
