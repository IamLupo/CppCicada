#include <core/ProcessedText.h>

#include <core.h>
#include <pages.h>
#include <utf8.h>

#include <core/Transformer.h>

ProcessedText::ProcessedText()
{

}

ProcessedText::ProcessedText(size_t page_index)
{
	this->_content = G_PAGES_CONTENT[page_index];
	this->_rune_indices = G_PAGES_RUNE_INDICES[page_index]; 
}

ProcessedText::ProcessedText(const std::string_view& content, const std::vector<uint8_t>& rune_indices)
		: _content(content), _rune_indices(rune_indices)
{

}

ProcessedText::~ProcessedText()
{

}

std::string ProcessedText::get_latin_text()
{
	size_t rune_pos = 0;
	std::string s;

	// Iterate through all content
	for (size_t i = 0; i < this->_content.size();)
	{
		// Calculate length of utf8 bytes
		size_t len = utf8_char_length(static_cast<unsigned char>(this->_content[i]));

		// Read the utf8 character
		std::string_view c = this->_content.substr(i, len);
		
		// Check character is rune that can transelate to latin
		if(core::to_latin(c).value_or("?") != "?")
		{
			// Get rune index
			size_t rune_index = this->_rune_indices[rune_pos];

			// Save the latin in result
			s += core::RUNE_TABLE[rune_index].latin;

			// Next rune position
			rune_pos++;
		}
		else
			// Convert any special character
			s += core::unsafe::punct_map(c).value_or(c);
		
		i += len;
	}

	return s;
}

