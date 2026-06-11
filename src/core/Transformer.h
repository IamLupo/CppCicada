#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <string>
#include <vector>
#include <cstdint>

#include <core/ProcessedText.h>

class Transformer
{
	public:
		virtual ~Transformer() = default;

		virtual void transform(ProcessedText& pt) = 0;
};

class UnsolvedTransformer : public Transformer
{
	public:
		void transform(ProcessedText& pt) override
		{
			pt.SetUnsolved();
		};
};

#endif // TRANSFORMER_H
