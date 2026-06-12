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

std::string highlight_words(std::string text, std::span<const std::string_view> words)
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

}