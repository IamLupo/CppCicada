#ifndef TRANSFORMER_H
#define TRANSFORMER_H

class ProcessedText;

class Transformer
{
	public:
		virtual ~Transformer() = default;

		virtual void transform(ProcessedText& pt) = 0;
};

class UnsolvedTransformer : public Transformer
{
	public:
		void transform(ProcessedText& pt) override;
};

#endif // TRANSFORMER_H
