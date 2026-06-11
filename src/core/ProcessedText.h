#ifndef PROCESSED_TEXT_H
#define PROCESSED_TEXT_H

#include <string>
#include <vector>
#include <cstdint>

class ProcessedText
{
	private:
		std::string_view     _content;
		std::vector<uint8_t> _rune_indices;
		bool                 _unsolved;
	
	public:
		ProcessedText();
		ProcessedText(size_t page_index);
		ProcessedText(const std::string_view& content, const std::vector<uint8_t>& rune_indices);
		~ProcessedText();

		void SetSolved()   { this->_unsolved = false; }
		void SetUnsolved() { this->_unsolved = true;  }

		std::vector<uint8_t>& rune_indices()
		{
			return _rune_indices;
		}

		const std::vector<uint8_t>& rune_indices() const
		{
			return _rune_indices;
		}

		std::string get_latin_text();
};

#endif // PROCESSED_TEXT_H
