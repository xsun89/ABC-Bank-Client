#include "JButton.h"

using namespace JFC;
JButton::JButton()
	: JWindow(0, 0, 0, 0, 0), text_(std::string())
{
}

JButton::JButton(SHORT x, SHORT y, SHORT width, SHORT height, const std::string& text/* =std::string() */, JWindow* parent/* =jApp->Root() */)
	: JWindow(x, y, width, height, parent), text_(text)
{
	SetCanFocus(true);
}
JButton::~JButton(void)
{
	SetCanFocus(true);
}

void JButton::Draw()
{
	if(IsCurrent())
	{
		SetTextColor(FCOLOR_WHITE);
		SetBkColor(BCOLOR_RED);
		//jApp->HideCursor();
	}else{
		SetTextColor(FCOLOR_BLUE);
		SetBkColor(BCOLOR_GRAY);
	}

	JRECT rect = {0, 0, Width() - 1, Height() -1};

	FillRect(rect);

	DrawText(text_);
}

