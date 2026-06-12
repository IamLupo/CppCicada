#include <core.h>
#include <pages.h>
#include <util/utf8.h>
#include <core/ProcessedText.h>
#include <transformer/Transformer.h>

ProcessedText::ProcessedText()
		: _unsolved(false)
{
}

ProcessedText::ProcessedText(size_t page_index)
		: _unsolved(false)
{
	this->_content = pages::content[page_index];
	this->_rune_indices = pages::rune_indices[page_index]; 
}

ProcessedText::ProcessedText(const std::string_view& content, const std::vector<uint8_t>& rune_indices)
		: _unsolved(false), _content(content), _rune_indices(rune_indices)
{

}

ProcessedText::~ProcessedText()
{

}

std::string ProcessedText::get_latin_text(size_t target)
{
	if(this->_unsolved)
		return "<unsolved>";
	
	size_t rune_pos = 0;
	std::string s;

	// Iterate through all content
	for (size_t i = 0; i < this->_content.size();)
	{
		// Calculate length of utf8 bytes
		size_t len = util::utf8::char_length(static_cast<unsigned char>(this->_content[i]));

		// Read the utf8 character
		std::string_view c = this->_content.substr(i, len);
		
		// Check character is rune that can transelate to latin
		if(core::to_latin(c).value_or("?") != "?")
		{
			// Get rune index
			size_t rune_index = this->_rune_indices[rune_pos];

			// Save the latin in result
			s += core::runes[rune_index].latin;

			// Next rune position
			rune_pos++;

			if(target != -1 && rune_pos > target)
			{
				return s;
			}
		}
		else
			// Convert any special character
			s += core::unsafe::punct_map(c).value_or(c);
		
		i += len;
	}

	return s;
}

