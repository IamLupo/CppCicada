#include <limits>
#include <cstdlib>
#include <iostream>

#include <util/screen.h>

namespace util::screen
{
void clear()
{
#ifdef _WIN32
    int r = std::system("cls");
#else
    int r = std::system("clear");
#endif
}

void wait_for_enter()
{
    std::cout << "Press Enter to continue...";

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string highlight_words(const std::string& text, std::span<const std::string_view> words, bool is_console)
{
	std::string new_text = text;

	for (const auto& w : words)
	{
		size_t pos = 0;

		while ((pos = text.find(w, pos)) != std::string::npos)
		{
			if(is_console)
			{
				new_text.replace(pos, w.size(),
					std::string(GREEN) + std::string(w) + std::string(RESET));
				pos += sizeof(GREEN) + sizeof(RESET); // crude but works
			}
			else
			{
				new_text.replace(pos, w.size(),
					"[" + std::string(w) + "]");
				pos += 2;
			}
		}
	}

	return new_text;
}

}