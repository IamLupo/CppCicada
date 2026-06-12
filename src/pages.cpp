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
	for (size_t page_index = 0; page_index < pages::content.size(); ++page_index)
	{
		std::vector<size_t> interupters;
		std::vector<uint8_t> rune_indices;

		size_t rune_index = 0;
		
		std::string_view text = pages::content[page_index];

		for (size_t i = 0; i < text.size();)
		{
			size_t len = util::utf8::char_length(static_cast<unsigned char>(text[i]));

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
		pages::interupters[page_index] = interupters;
		pages::rune_indices[page_index] = rune_indices;
		pages::transformers[page_index].clear();
	}

	pages::transformers[0].push_back(std::make_unique<transformer::Atbash>());

	pages::transformers[1].push_back(
		std::make_unique<transformer::Vigenere>(
			"DIVINITY", // DIVINITY = ᛞᛁᚢᛁᚾᛁᛏᚣ
			std::vector<size_t>{ 48, 74, 84, 132, 159, 160, 250, 421, 443, 465, 514 }
	));

	pages::transformers[3].push_back(std::make_unique<transformer::Atbash>());
	pages::transformers[3].push_back(std::make_unique<transformer::Shift>(
			3, std::vector<size_t>({})
	));

	pages::transformers[5].push_back(
		std::make_unique<transformer::Vigenere>(
			// "CIRCVMFERENCE", // CIRCVMFERENCE = ᚳᛁᚱᚳᚢᛗᚠᛖᚱᛖᚾᚳᛖ
			"FIRFVMFERENFE", // FIRFVMFERENFE = ᚠᛁᚱᚠᚢᛗᚠᛖᚱᛖᚾᚠᛖ
			std::vector<size_t>{ 49, 58 }
	));
	
	pages::transformers[7].push_back(std::make_unique<UnsolvedTransformer>());
	pages::transformers[8].push_back(std::make_unique<UnsolvedTransformer>());
	pages::transformers[9].push_back(std::make_unique<UnsolvedTransformer>());
	pages::transformers[10].push_back(std::make_unique<UnsolvedTransformer>());
	pages::transformers[11].push_back(std::make_unique<UnsolvedTransformer>());
	pages::transformers[12].push_back(std::make_unique<UnsolvedTransformer>());
	pages::transformers[13].push_back(std::make_unique<UnsolvedTransformer>());
	pages::transformers[14].push_back(std::make_unique<UnsolvedTransformer>());
	pages::transformers[15].push_back(std::make_unique<UnsolvedTransformer>());

	pages::transformers[16].push_back(
		std::make_unique<transformer::Totient>(
			std::vector<size_t>{ 56 }
	));
}

} // namespace pages
