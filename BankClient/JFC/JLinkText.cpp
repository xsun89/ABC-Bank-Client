#include "JLinkText.h"

using namespace JFC;
JLinkText::JLinkText()
	: JWindow(0,0,0,0), text_(std::string())
{
	SetCanFocus(true);
}

JLinkText::JLinkText(SHORT x, SHORT y, SHORT width, SHORT height, std::string& text, JWindow* parent /* = jApp->Root() */)
					 :JWindow(x, y, width, height, parent),
					 text_(text)
{
	SetCanFocus(true);
}

JLinkText::~JLinkText(void)
{

}

void JLinkText::Draw()
{
	if(IsCurrent())
	{
		SetTextColor(FCOLOR_RED | COMMON_LVB_UNDERSCORE);
		jApp->HideCursor();
		DrawText(0, 0, std::string("-> ") + text_);
	}else
	{
		SetTextColor(FCOLOR_BLUE);
		DrawText(0, 0, text_ + std::string("   "));
	}
}
