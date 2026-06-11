#include <iostream>
#include <memory>
#include <thread>

#include <version.h>
#include <core.h>
#include <pages.h>
#include <util/screen.h>
#include <math/prime.h>
#include <math/totient.h>
#include <core/ProcessedText.h>
#include <transformer/Atbash.h>

void test_runes()
{
	std::cout << core::RUNE_TABLE[1].rune << std::endl;
	std::cout << core::RUNE_TABLE[1].latin << std::endl;
	std::cout << +core::RUNE_TABLE[1].prime << std::endl;

	std::cout << core::to_rune("V").value_or("?") << std::endl;
	std::cout << core::to_rune("LOL").value_or("?") << std::endl;
	std::cout << core::unsafe::to_rune("V") << std::endl;
}

void test_pages()
{
	for(int page_index = 0; page_index < G_PAGES_CONTENT.size(); ++page_index)
	{
		auto images = G_PAGES_IMAGES[page_index];
		auto interupters = G_PAGES_INTERUPTERS[page_index];
		auto rune_indices = G_PAGES_RUNE_INDICES[page_index];
		
		std::cout << "page_index: " << +page_index << std::endl;
		if(images.size() >= 2)
			std::cout << "images: " << *images.begin() << " till " << *(--images.end()) << std::endl;
		else
			std::cout << "images: " << *images.begin() << std::endl;
		
		std::cout << "interupters: ";
		for(auto interupter : interupters)
			std::cout << interupter << ", ";
		std::cout << std::endl;

		std::cout << "runes: [";
		for(auto rune_index : rune_indices)
			std::cout << core::RUNE_TABLE[rune_index].rune << ", ";
		std::cout << "]" << std::endl;
		
		std::cout << "content: " << G_PAGES_CONTENT[page_index] << std::endl;
	}
}

void test_processed_text()
{
	ProcessedText pt1(2);
	ProcessedText pt2(4);

	std::cout << pt1.get_latin_text() << std::endl;
	std::cout << pt2.get_latin_text() << std::endl;
}

void test_transformer()
{
	for (int page_index = 0; page_index < G_PAGES_IMAGES.size(); page_index++)
	{
		auto& images = G_PAGES_IMAGES[page_index];
		auto& transformers = G_PAGES_TRANSFORMERS[page_index];
		
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

void test_latin()
{
	std::string runes;
	std::vector<uint8_t> rune_indices;

	std::cout << "core::to_runes(\"RING\").value_or(\"\")" << std::endl;

	runes = core::to_runes("RING").value_or("");
	std::cout << "runes: " << runes << std::endl;

	rune_indices = core::to_rune_indices(runes).value_or(std::vector<uint8_t>({}));
	std::cout << rune_indices.size() << std::endl;
	
}

void test_math()
{
	std::cout << "primes: ";
	for (auto p : math::primes_1000)
	{
		std::cout << p << ", ";
	}
	std::cout << "\n";

	std::cout << "primes_totient: ";
	for (auto p : math::primes_totient_1000)
	{
		std::cout << p << ", ";
	}
	std::cout << "\n";
}

void test_speed()
{
	for (int page_index = 0; page_index < G_PAGES_IMAGES.size(); page_index++)
	{
		auto& images = G_PAGES_IMAGES[page_index];
		auto& transformers = G_PAGES_TRANSFORMERS[page_index];
		
		ProcessedText pt(page_index);

		for (const std::unique_ptr<Transformer>& tf : transformers)
			tf->transform(pt);
		
		std::string text = pt.get_latin_text();
	}
}

void test_singlethread()
{
	for(int i = 0; i < 100000; i++)
	{
		test_speed();
	}
}

void test_multithread()
{
	std::vector<std::thread> threads;
	
	for(int i = 0; i < 10; i++)
	{
		threads.emplace_back([&]()
		{
			for(int i = 0; i < 10000; i++)
			{
				test_speed();
			}
		});
	}

	for(auto& t : threads)
		t.join();
}

int main()
{
	/* Initialize */
	core::initialize();
	pages::initialize();
	
	//test_runes();	
	//test_pages();
	//test_processed_text();
	//test_transformer();
	//test_latin();
	//test_math();
	//test_singlethread();
	test_multithread();
}
