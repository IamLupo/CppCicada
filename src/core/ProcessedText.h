#ifndef PROCESSED_TEXT_H
#define PROCESSED_TEXT_H

#include <string>

#include <core/types.h>

class ProcessedText
{
	private:
		core::PageContent _content;
		core::RuneIndices _rune_indices;
		bool              _unsolved;
	
	public:
		ProcessedText();
		ProcessedText(core::PageIndex page_index);
		ProcessedText(const core::PageContent& content, const core::RuneIndices& rune_indices);
		~ProcessedText();

		void SetSolved()   { this->_unsolved = false; }
		void SetUnsolved() { this->_unsolved = true;  }

		core::RuneIndices& rune_indices()
		{
			return _rune_indices;
		}

		const core::RuneIndices& rune_indices() const
		{
			return _rune_indices;
		}

		std::string get_latin_text(size_t target = -1);
};

#endif // PROCESSED_TEXT_H
