#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include <vector>
#include <cstdint>
#include <string_view>
#include <memory>

class Transformer;

namespace core
{
	typedef uint8_t                RuneIndex;
	typedef std::vector<RuneIndex> RuneIndices;
	typedef size_t                 RunePosition;

	typedef std::string               Rune;
	typedef std::string_view          RuneView;
	typedef std::string               Runes;
	typedef std::string_view          RunesView;
	typedef std::string               RuneLatin;
	typedef std::string_view          RuneLatinView;
	typedef std::vector<RuneLatin>    RuneLatinList;
	typedef uint8_t                   RunePrime;
	typedef std::vector<RunePosition> RuneInterruptIndices;

	typedef uint8_t                     PageIndex;
	typedef std::string_view            PageContent;
	typedef std::string_view            PageImage;
	typedef std::vector<PageImage>      PageImageGroup;
	typedef std::vector<PageImageGroup> PageImageGroups;

	typedef std::unique_ptr<Transformer> Transformer_ptr;
	typedef std::vector<Transformer_ptr> Transformers_ptr;
}

#endif // CORE_PROCESSED_TEXT_H