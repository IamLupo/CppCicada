#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <string>
#include <vector>
#include <cstdint>

class ProcessedText;

class Transformer
{
	//private:
	public:
		virtual ~Transformer() = default;

		virtual void transform(ProcessedText& pt) = 0;
};

#endif // TRANSFORMER_H
