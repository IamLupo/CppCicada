#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <transformer/Transformer.h>
#include <transformer/Vigenere.h>

#include <core.h>
#include <pages.h>
#include <util/string.h>
#include <util/screen.h>

std::mutex  mutex_result;

static void read_words(const std::string& file_path, std::vector<std::string>& list)
{
	std::ifstream fs(file_path);

	if (!fs.is_open())
		return;

	std::string line;

	while (std::getline(fs, line))
	{
		if(line.empty())
			continue;
		
		if(!util::string::contains_special_chars(line))
		{
			std::string word = util::string::to_upper(line);
			
			std::string runes = core::to_runes(word).value_or("");
			std::string latin = core::to_latins(runes);
			
			//std::cout << word << " -> " << runes << " -> " << latin << std::endl;

			list.push_back(word);
		}
	}
}

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

static int found_words(const std::string& text)
{
	int found = 0;

	for (auto word : words)
		if (text.find(word) != std::string_view::npos)
			found++;
	
	return found;
}

void check_vigenere(const std::string& key, const std::vector<size_t>& interrupt_indices, size_t page_index)
{
	// Make transformer
	transformer::Vigenere tf = transformer::Vigenere(key, interrupt_indices);

	// Create text processor
	ProcessedText pt(page_index);

	// Transform the cipher text
	tf.transform(pt);
	
	// Show result
	std::string decrypted_text = pt.get_latin_text(150);

	if(found_words(decrypted_text) >= 4)
	{
		std::lock_guard<std::mutex> guard(mutex_result);
		
		std::cout << "decrypted_text: " << util::screen::highlight_words(decrypted_text, words, false) << std::endl;
		
		std::cout << "page_index: " << page_index << std::endl;

		std::cout << "found words: ";
		for (auto word : words)
			if (decrypted_text.find(word) != std::string_view::npos)
				std::cout << word << ", ";
		std::cout << std::endl;
		
		std::cout << "key: " << key << std::endl;
		
		std::cout << "interrupt_indices: ";
		for(const auto v : interrupt_indices)
			std::cout << v << ", ";
		std::cout << std::endl;
		
		// Herpy derpy derpppppp =D
		//util::screen::wait_for_enter();

		std::cout << "-----------------------------" << std::endl;
	}
}

static std::vector<size_t> get_interrupt_indices(size_t page_index)
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

void check_vigenere(const std::string& key)
{
	//for (size_t page_index = 1; page_index < 2; ++page_index)
	//for (size_t page_index = 5; page_index < 6; ++page_index)
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
			check_vigenere(key, interrupt_indices, page_index);
		}
	}
}

std::string patch_key(const std::string& key)
{
	std::string new_key = "";
	std::string runes = core::to_runes(key).value_or("");
	std::vector<uint8_t> rune_indices = core::to_rune_indices(runes).value_or(std::vector<uint8_t>({}));

	if(rune_indices.size() > 0)
	{
		uint8_t first_rune_index = rune_indices[0];
		
		for(int i = 0; i < rune_indices.size(); i++)
		{
			if(rune_indices[i] == first_rune_index)
				new_key += core::runes[0].latin;
			else
				new_key += core::runes[rune_indices[i]].latin;
		}
	}

	return new_key;
}

void check_all_vigenere(const std::vector<std::string>& work)
{
    constexpr size_t THREAD_COUNT = 10;

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

                check_vigenere(work[i]);

				//check_vigenere(patch_key(work[i]));
            }
        });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }
}

void vigenere_bruteforce()
{
	std::vector<std::string> list;

	read_words("../data/english_wordlist.txt", list);

	check_all_vigenere(list);
}
