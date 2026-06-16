#ifndef CORE_PROCESSED_TEXT_H
#define CORE_PROCESSED_TEXT_H

#include <string>
#include <vector>
#include <cstdint>

#include <core/types.h>
#include <pages.h>

class ProcessedText
{
	private:
		core::PageContent _content;
		core::RuneIndices  _rune_indices;
		bool               _unsolved;
	
	public:
		ProcessedText();
		ProcessedText(size_t page_index);
		ProcessedText(const core::PageContent content, const core::RuneIndices& rune_indices);
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

#endif // CORE_PROCESSED_TEXT_H
