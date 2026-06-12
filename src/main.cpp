#include <iostream>
#include <memory>
#include <thread>
#include <string>

#include <version.h>
#include <core.h>
#include <pages.h>
#include <util/oeis.h>
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
	for (const auto p : math::primes_totient_1000)
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
	for (const auto p : math::primes_totient_1000)
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

static constexpr std::string_view words[] =
{
	" VOID ",
	" FORM ",
	" TRVTH ",
	" CABAL ",
	" WITHIN ",
	" IS ",
	" THE ",
	" AND ",
	" A ",
	" WE ",
	" I ",
	" HE ",
	" SHE ",
	" IT ",
	" STVDY ",
	" MASTER ",
	" STVDENT ",
	" FOLLOW ",
	" FIND ",
	" YOVR ",
    "PILGRIM",
	"SHADOWS",
	"AETHEREAL",
	"BVFFERS",
	"CARNAL",
	"OBSCVRA",
	"MOBIVS",
	"ANALOG",
	"MOVRNFVL"
};

std::string highlight_words(std::string text)
{
	for (const auto& w : words)
	{
		size_t pos = 0;

		while ((pos = text.find(w, pos)) != std::string::npos)
		{
			text.replace(pos, w.size(),
				std::string(GREEN) + std::string(w) + std::string(RESET));

			pos += sizeof(GREEN) + sizeof(RESET); // crude but works
		}
	}

	return text;
}

int found_words(const std::string& text)
{
	int found = 0;

	for (auto word : words)
		if (text.find(word) != std::string_view::npos)
			found++;
	
	return found;
}

#include <mutex>

std::mutex  mutex_result;

void check_sequence(const std::vector<uint8_t>& sequence, const std::vector<size_t>& interrupt_indices, size_t page_index)
{
	// Make transformer
	std::unique_ptr<Transformer> tf = std::make_unique<transformer::Sequence>(sequence, interrupt_indices);
	std::unique_ptr<Transformer> tf2 = std::make_unique<transformer::Shift>(22, interrupt_indices);

	// Create text processor
	ProcessedText pt(page_index);

	// Transform the cipher text
	tf->transform(pt);
	tf2->transform(pt);
	
	// Show result
	std::string decrypted_text = pt.get_latin_text(150);

	if(found_words(decrypted_text) >= 4)
	{
		std::lock_guard<std::mutex> guard(mutex_result);
		
		std::cout << "decrypted_text: " << highlight_words(decrypted_text) << std::endl;

		std::cout << "page_index: " << page_index << std::endl;

		std::cout << "found words: ";
		for (auto word : words)
			if (decrypted_text.find(word) != std::string_view::npos)
				std::cout << word << ", ";
		std::cout << std::endl;
		
		std::cout << "sequence: ";
		for(const auto v : sequence)
			std::cout << +v << ", ";
		std::cout << std::endl;
		
		std::cout << "interrupt_indices: ";
		for(const auto v : interrupt_indices)
			std::cout << v << ", ";
		std::cout << std::endl;
		
		// Herpy derpy derpppppp =D
		//util::screen::wait_for_enter();

		std::cout << "-----------------------------" << std::endl;
	}
}

std::vector<size_t> get_interrupt_indices(size_t page_index)
{
	std::vector<size_t> interrupt_indices;

	const auto& interupters = pages::interupters[page_index];

	for(auto v : interupters)
	{
		if(v >= 100)
			break;
		
		interrupt_indices.push_back(v);
	}

	return interrupt_indices;
}

void check_sequence(const std::vector<uint8_t>& sequence)
{
	for (size_t page_index = 7; page_index < 16; ++page_index)
	{
		auto all_interrupt_indices = get_interrupt_indices(page_index);
		const size_t n = all_interrupt_indices.size();

		for (uint32_t mask = 0; mask < (1u << n); ++mask)
		{
			std::vector<size_t> interrupt_indices;

			interrupt_indices.reserve(n);

			for (size_t i = 0; i < n; ++i)
			{
				if (mask & (1u << i))
				{
					interrupt_indices.push_back(all_interrupt_indices[i]);
				}
			}

			// Process this subset immediately.
			check_sequence(sequence, interrupt_indices, page_index);
		}
	}
}

void check_all_sequences(const util::oeis::UInt8Map& uint8_map)
{
    constexpr size_t THREAD_COUNT = 10;

    // Create a flat list of pointers/references to the sequences.
    std::vector<const util::oeis::UInt8Seq*> work;
    work.reserve(uint8_map.size());

    for (const auto& [sequence_id, sequence] : uint8_map)
    {
        work.push_back(&sequence);
    }

    const size_t total = work.size();
    const size_t chunk_size = (total + THREAD_COUNT - 1) / THREAD_COUNT;

    std::vector<std::thread> threads;

    for (size_t t = 0; t < THREAD_COUNT; ++t)
    {
        const size_t begin = t * chunk_size;
        const size_t end = std::min(begin + chunk_size, total);

        if (begin >= end)
            break;

        threads.emplace_back([&, t, begin, end]()
        {
			thread_local int thread_index = t;

            for (size_t i = begin; i < end; ++i)
            {
				int start = i - begin;
				int target = end - begin;

				if(start % 500 == 0)
				{
					std::lock_guard<std::mutex> guard(mutex_result);
					std::cout << "Thread " << thread_index << " worked done " << start << "/" << target << std::endl;  
				}

                check_sequence(*work[i]);
            }
        });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }
}

void test_oeis()
{
	util::oeis::UInt8Map uint8_map;
	
	// Read oeis.txt file and convert to map
	util::oeis::make_map("../data/oeis.txt", uint8_map);

	std::cout << "uint8_map: " << uint8_map.size() << std::endl;

	//util::screen::wait_for_enter();

	// Basic example
	//check_sequence(uint8_map["A006093"], {}, 16);

	/*
	// Iterate all sequences
	for (const auto& [sequence_id, sequence] : uint8_map)
	{
		std::cout << sequence_id << " - " << sequence.size() << std::endl;
		
		// Force to send the results to the screen. Else it will have 1 GB of output data in memory xD
		//std::cout << std::flush;

		check_sequence(sequence);
	}
	*/

	check_all_sequences(uint8_map);
}

int main()
{
	/* Initialize */
	core::initialize();
	pages::initialize();
	
	//test_runes();	
	//test_pages();
	//test_processed_text();
	//test_latin();
	//test_math();
	
	//test_transformer();
	
	//test_singlethread();
	//test_multithread();

	//test_sequence();
	test_oeis();
}
