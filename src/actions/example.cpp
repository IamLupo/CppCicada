#include <iostream>
#include <memory>
#include <thread>
#include <string>

#include <version.h>
#include <core.h>
#include <pages.h>
#include <util/screen.h>
#include <math/prime.h>
#include <math/totient.h>
#include <core/ProcessedText.h>
#include <transformer/Sequence.h>
#include <transformer/Shift.h>

void test_runes()
{
	std::cout << core::runes[1].rune << std::endl;
	std::cout << core::runes[1].latin << std::endl;
	std::cout << +core::runes[1].prime << std::endl;

	std::cout << core::to_rune("V").value_or("?") << std::endl;
	std::cout << core::to_rune("LOL").value_or("?") << std::endl;
	std::cout << core::unsafe::to_rune("V") << std::endl;
}

void test_pages()
{
	for(size_t page_index = 0; page_index < pages::content.size(); ++page_index)
	{
		const auto& images = pages::images[page_index];
		const auto& interupters = pages::interupters[page_index];
		const auto& rune_indices = pages::rune_indices[page_index];
		
		std::cout << "page_index: " << +page_index << std::endl;
		if(images.size() >= 2)
			std::cout << "images: " << *images.begin() << " till " << *(--images.end()) << std::endl;
		else
			std::cout << "images: " << *images.begin() << std::endl;
		
		std::cout << "interupters: ";
		for(const auto interupter : interupters)
			std::cout << interupter << ", ";
		std::cout << std::endl;

		std::cout << "runes: [";
		for(const auto rune_index : rune_indices)
			std::cout << core::runes[rune_index].rune << ", ";
		std::cout << "]" << std::endl;
		
		std::cout << "content: " << pages::content[page_index] << std::endl;
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
	for (const auto p : math::primes_1000)
	{
		std::cout << p << ", ";
	}
	std::cout << "\n";

	std::cout << "primes_totient: ";
	for (const auto p : math::prime_totients_1000)
	{
		std::cout << p << ", ";
	}
	std::cout << "\n";
}

void test_speed()
{
	for (size_t page_index = 0; page_index < pages::images.size(); page_index++)
	{
		const auto& images = pages::images[page_index];
		const auto& transformers = pages::transformers[page_index];
		
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
		threads.emplace_back([&]() {
			for(int i = 0; i < 10000; i++)
			{
				test_speed();
			}
		});
	}

	for(auto& t : threads)
	{
		t.join();
	}
}

void test_sequence()
{
	// Convert sequence to uint8_t
	std::vector<uint8_t> sequence;
	for (const auto p : math::prime_totients_1000)
	{
		sequence.push_back(static_cast<uint8_t>(p % 29));
	}

	// Make transformer
	const std::vector<size_t> interrupt_indices = { 56 };
	std::unique_ptr<Transformer> tf = std::make_unique<transformer::Sequence>(sequence, interrupt_indices);
	
	// Create text processor
	ProcessedText pt(16);

	// Transform the cipher text
	tf->transform(pt);

	// Show result
	std::cout << pt.get_latin_text() << std::endl;

	// Herpy derpy derpppppp =D
	util::screen::wait_for_enter();
}
