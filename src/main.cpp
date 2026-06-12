#include <iostream>

#include <version.h>
#include <core.h>
#include <pages.h>
#include <actions.h>
#include <transformer/Transformer.h>
#include <util/screen.h>
#include <core/ProcessedText.h>

void show_solved_pages()
{
	for (size_t page_index = 0; page_index < pages::images.size(); page_index++)
	{
		const auto& images = pages::images[page_index];
		const auto& transformers = pages::transformers[page_index];
		
		util::screen::clear();

		std::cout << "page_index: " << page_index << std::endl;
		if(images.size() >= 2)
			std::cout << "images: " << *images.begin() << " till " << *(--images.end()) << std::endl;
		else
			std::cout << "images: " << *images.begin() << std::endl;

		ProcessedText pt(page_index);

		for (const std::unique_ptr<Transformer>& tf : transformers)
			tf->transform(pt);
		
		std::cout << pt.get_latin_text() << std::endl;

		util::screen::wait_for_enter();
	}
}

int main()
{
	/* Initialize */
	core::initialize();
	pages::initialize();

	//show_solved_pages();

	sequence_bruteforce();
}
