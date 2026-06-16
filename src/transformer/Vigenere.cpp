#include <algorithm>

#include <core.h>
#include <core/ProcessedText.h>
#include <transformer/Vigenere.h>

namespace transformer
{

Vigenere::Vigenere(const core::RuneLatin& key, const core::RuneInterruptIndices& interrupt_indices)
		: _interrupt_indices(interrupt_indices)
{
	core::Runes runes = core::to_runes(key).value_or("");

	this->_key = core::to_rune_indices(runes).value_or(core::RuneIndices({}));
}

void Vigenere::transform(ProcessedText& pt)
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

} // namespace transformer
