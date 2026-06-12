#include <algorithm>

#include <core.h>
#include <core/ProcessedText.h>
#include <transformer/Sequence.h>

namespace transformer
{

Sequence::Sequence(const std::vector<uint8_t>& sequence, const std::vector<size_t>& interrupt_indices)
		: _sequence(sequence), _interrupt_indices(interrupt_indices)
{
	
}

void Sequence::transform(ProcessedText& pt)
{
	auto& rune_indices = pt.rune_indices();
	int interups = 0;
	size_t sequence_size = this->_sequence.size();

	for(size_t i = 0; i < rune_indices.size(); i++)
	{
		if(std::find(this->_interrupt_indices.begin(), this->_interrupt_indices.end(), i) == _interrupt_indices.end())
		{
			uint8_t key = this->_sequence[(i - interups) % sequence_size] % 29;
			
			rune_indices[i] = (29 + rune_indices[i] - key) % 29;
		}
		else
		{
			interups++;
		}
	}
}

} // namespace transformer
