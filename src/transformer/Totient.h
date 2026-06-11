#ifndef TRANSFORMER_TOTIENT_H
#define TRANSFORMER_TOTIENT_H

#include <transformer/Transformer.h>

namespace transformer
{
	class Totient : public Transformer
	{
		private:
			std::vector<size_t>  _interrupt_indices;

		public:
			Totient(const std::vector<size_t>& interrupt_indices);
			
			void transform(ProcessedText& pt) override;
	};

} // namespace transformer

#endif // TRANSFORMER_TOTIENT_H
