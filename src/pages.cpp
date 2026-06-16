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
	for (core::PageIndex page_index = 0; page_index < pages::content.size(); ++page_index)
	{
		core::RuneInterruptIndices interrupters;
		core::RuneIndices rune_indices;

		core::RunePosition rune_position = 0;
		
		core::PageContent content = pages::content[page_index];

		for (size_t i = 0; i < content.size();)
		{
			size_t len = util::utf8::char_length(static_cast<unsigned char>(content[i]));

			core::RuneView rune = content.substr(i, len);
			core::RuneLatinView latin = core::to_latin(rune).value_or("?");
			
			if(latin != "?")
			{
				rune_indices.push_back(core::rune_to_index[rune]);
				
				if(rune == "ᚠ")
					interrupters.push_back(rune_position);

				rune_position++;
			}

			i += len;
		}
		
		// Save results
		pages::interrupters[page_index] = interrupters;
		pages::rune_indices[page_index] = rune_indices;
		pages::transformers[page_index].clear();
	}

	pages::transformers[0].push_back(std::make_unique<transformer::Atbash>());

	pages::transformers[1].push_back(
		std::make_unique<transformer::Vigenere>(
			"DIVINITY", // DIVINITY = ᛞᛁᚢᛁᚾᛁᛏᚣ
			core::RuneInterruptIndices{ 48, 74, 84, 132, 159, 160, 250, 421, 443, 465, 514 }
	));

	pages::transformers[3].push_back(std::make_unique<transformer::Atbash>());
	pages::transformers[3].push_back(std::make_unique<transformer::Shift>(
			3, core::RuneInterruptIndices({})
	));

	pages::transformers[5].push_back(
		std::make_unique<transformer::Vigenere>(
			// "CIRCVMFERENCE", // CIRCVMFERENCE = ᚳᛁᚱᚳᚢᛗᚠᛖᚱᛖᚾᚳᛖ
			"FIRFVMFERENFE", // FIRFVMFERENFE = ᚠᛁᚱᚠᚢᛗᚠᛖᚱᛖᚾᚠᛖ
			core::RuneInterruptIndices{ 49, 58 }
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
			core::RuneInterruptIndices{ 56 }
	));
}

core::RuneInterruptIndices get_max_interrupt_indices(core::PageIndex page_index, size_t max)
{
	core::RuneInterruptIndices interrupt_indices;

	const auto& interrupters = pages::interrupters[page_index];

	for(auto v : interrupters)
	{
		if(v >= max)
			break;
		
		interrupt_indices.push_back(v);
	}

	return interrupt_indices;
}

} // namespace pages
