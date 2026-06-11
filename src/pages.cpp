#include <core.h>
#include <pages.h>
#include <util/utf8.h>
#include <transformer/Transformer.h>
#include <transformer/Atbash.h>
#include <transformer/Vigenere.h>
#include <transformer/Shift.h>
#include <transformer/Totient.h>

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
			size_t len = util::utf8_char_length(static_cast<unsigned char>(text[i]));

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
		G_PAGES_TRANSFORMERS[page_index].clear();
	}

	G_PAGES_TRANSFORMERS[0].push_back(std::make_unique<transformer::Atbash>());

	G_PAGES_TRANSFORMERS[1].push_back(
		std::make_unique<transformer::Vigenere>(
			"DIVINITY", // DIVINITY = ᛞᛁᚢᛁᚾᛁᛏᚣ
			std::vector<size_t>{ 48, 74, 84, 132, 159, 160, 250, 421, 443, 465, 514 }
	));

	G_PAGES_TRANSFORMERS[3].push_back(std::make_unique<transformer::Atbash>());
	G_PAGES_TRANSFORMERS[3].push_back(std::make_unique<transformer::Shift>(
			3, std::vector<size_t>({})
	));

	G_PAGES_TRANSFORMERS[5].push_back(
		std::make_unique<transformer::Vigenere>(
			// "CIRCVMFERENCE", // CIRCVMFERENCE = ᚳᛁᚱᚳᚢᛗᚠᛖᚱᛖᚾᚳᛖ
			"FIRFVMFERENFE", // FIRFVMFERENFE = ᚠᛁᚱᚠᚢᛗᚠᛖᚱᛖᚾᚠᛖ
			std::vector<size_t>{ 49, 58 }
	));
	
	G_PAGES_TRANSFORMERS[7].push_back(std::make_unique<UnsolvedTransformer>());
	G_PAGES_TRANSFORMERS[8].push_back(std::make_unique<UnsolvedTransformer>());
	G_PAGES_TRANSFORMERS[9].push_back(std::make_unique<UnsolvedTransformer>());
	G_PAGES_TRANSFORMERS[10].push_back(std::make_unique<UnsolvedTransformer>());
	G_PAGES_TRANSFORMERS[11].push_back(std::make_unique<UnsolvedTransformer>());
	G_PAGES_TRANSFORMERS[12].push_back(std::make_unique<UnsolvedTransformer>());
	G_PAGES_TRANSFORMERS[13].push_back(std::make_unique<UnsolvedTransformer>());
	G_PAGES_TRANSFORMERS[14].push_back(std::make_unique<UnsolvedTransformer>());
	G_PAGES_TRANSFORMERS[15].push_back(std::make_unique<UnsolvedTransformer>());

	G_PAGES_TRANSFORMERS[16].push_back(
		std::make_unique<transformer::Totient>(
			std::vector<size_t>{ 56 }
	));
}

} // namespace pages
