#include <algorithm>

#include <core.h>
#include <core/ProcessedText.h>
#include <math/totient.h>
#include <transformer/Totient.h>

namespace transformer
{

Totient::Totient(const std::vector<size_t>& interrupt_indices)
		: _interrupt_indices(interrupt_indices)
{
	
}

void Totient::transform(ProcessedText& pt)
{
	auto& rune_indices = pt.rune_indices();
	int interups = 0;

	for(size_t i = 0; i < rune_indices.size(); i++)
	{
		if(std::find(this->_interrupt_indices.begin(), this->_interrupt_indices.end(), i) == _interrupt_indices.end())
		{
			uint8_t key = math::primes_totient_1000[(i - interups) % math::total_primes_totient] % 29;
			
			rune_indices[i] = (29 + rune_indices[i] - key) % 29;
		}
		else
		{
			interups++;
		}
	}
}

} // namespace transformer
