#include <algorithm>

#include <transformer/Shift.h>
#include <core/ProcessedText.h>

namespace transformer
{

Shift::Shift(uint8_t shift, const std::vector<size_t>& interrupt_indices)
		: _shift(shift), _interrupt_indices(interrupt_indices)
{
	
}

void Shift::transform(ProcessedText& pt)
{
	auto& rune_indices = pt.rune_indices();

	for(size_t i = 0; i < rune_indices.size(); i++)
	{
		if(std::find(this->_interrupt_indices.begin(), this->_interrupt_indices.end(), i) == _interrupt_indices.end())
		{
			rune_indices[i] = (rune_indices[i] + this->_shift) % 29;
		}
	}
}

} // namespace transformer
