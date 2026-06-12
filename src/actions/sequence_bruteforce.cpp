#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

#include <version.h>
#include <core.h>
#include <pages.h>
#include <actions.h>
#include <util/oeis.h>
#include <util/screen.h>
#include <core/ProcessedText.h>
#include <transformer/Sequence.h>
#include <transformer/Shift.h>

std::mutex  mutex_result;

static constexpr std::array words =
{
    std::string_view(" VOID "),
    std::string_view(" FORM "),
    std::string_view(" TRVTH "),
    std::string_view(" CABAL "),
    std::string_view(" WITHIN "),
    std::string_view(" IS "),
    std::string_view(" THE "),
    std::string_view(" AND "),
    std::string_view(" A "),
    std::string_view(" WE "),
    std::string_view(" I "),
    std::string_view(" HE "),
    std::string_view(" SHE "),
    std::string_view(" IT "),
    std::string_view(" STVDY "),
    std::string_view(" MASTER "),
    std::string_view(" STVDENT "),
    std::string_view(" FOLLOW "),
    std::string_view(" FIND "),
    std::string_view(" YOVR "),
    std::string_view("PILGRIM"),
    std::string_view("SHADOWS"),
    std::string_view("AETHEREAL"),
    std::string_view("BVFFERS"),
    std::string_view("CARNAL"),
    std::string_view("OBSCVRA"),
    std::string_view("MOBIVS"),
    std::string_view("ANALOG"),
    std::string_view("MOVRNFVL")
};

int found_words(const std::string& text)
{
	int found = 0;

	for (auto word : words)
		if (text.find(word) != std::string_view::npos)
			found++;
	
	return found;
}

void check_sequence(const std::vector<uint8_t>& sequence, const std::vector<size_t>& interrupt_indices, size_t page_index)
{
	// Make transformer
	std::unique_ptr<Transformer> tf = std::make_unique<transformer::Sequence>(sequence, interrupt_indices);
	std::unique_ptr<Transformer> tf2 = std::make_unique<transformer::Shift>(28, interrupt_indices);

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
		
		std::cout << "decrypted_text: " << util::screen::highlight_words(decrypted_text, words) << std::endl;

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

				if(start % 5000 == 0)
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

void sequence_bruteforce()
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

