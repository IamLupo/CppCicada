#include <transformer/Vigenere.h>

#include <algorithm>

#include <core.h>
#include <core/ProcessedText.h>

VigenereTransformer::VigenereTransformer(const std::string_view& key, const std::vector<size_t>& interrupt_indices)
		: _interrupt_indices(interrupt_indices)
{
	this->_key = core::to_rune_indices(key).value_or(std::vector<uint8_t>({}));
}

void VigenereTransformer::transform(ProcessedText& pt)
{
	auto& rune_indices = pt.rune_indices();
	int interups = 0;

	for(size_t i = 0; i < rune_indices.size(); i++)
	{
		if(std::find(this->_interrupt_indices.begin(), this->_interrupt_indices.end(), i) == _interrupt_indices.end())
		{
			uint8_t key = this->_key[(i - interups) % this->_key.size()];
		
			rune_indices[i] = (29 + rune_indices[i] - key) % 29;
		}
		else
		{
			interups++;
		}
	}
}
