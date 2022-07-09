#include"pch.h"
#include "RfTextLayout.h"
#include"RfWriteFactory.h"
#define WRITE_FACTORY ((IDWriteFactory*)RfWriteFactory::n_factory)
#define WRITE_FORMAT ((IDWriteTextFormat*)txtStyle.Native())

RfTextLayout::RfTextLayout(const wchar_t* txt, RfTextStyle txtStyle, float boxWidth, float boxHeight)
{
	info.style = txtStyle;
	auto format = WRITE_FORMAT;
	IDWriteTextLayout* lll = nullptr;
	WRITE_FACTORY->CreateTextLayout(
		txt,
		lstrlenW(txt),
		format,
		boxWidth,
		boxHeight,
		&lll
	);
	if (lll) {
		info.n_layout = lll;
	}
	if (boxWidth == 0 || boxHeight == 0) {
		auto ss = GetSize();
		lll->SetMaxWidth(ss.width);
		lll->SetMaxHeight(ss.height);
	}
	if (format)format->Release();
}
#define WRITE_LAYOUT ((IDWriteTextLayout*)info.n_layout)
RfTextLayout::~RfTextLayout()
{
	if (WRITE_LAYOUT)WRITE_LAYOUT->Release();
}

RfSize RfTextLayout::GetSize()
{
	DWRITE_TEXT_METRICS m{};
	WRITE_LAYOUT->GetMetrics(&m);

	return RfSize(m.widthIncludingTrailingWhitespace,m.height);
}
