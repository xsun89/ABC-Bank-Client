#include <algorithm>
#include "JWindow.h"
#include "JEvent.h"


using namespace JFC;
JWindow::JWindow()
	: parent_(0),
	  canFocus_(false)
{
}

JWindow::JWindow(SHORT x, SHORT y, SHORT width, SHORT height, JWindow* parent)
	: JWindowBase(x, y, width, height),
		parent_(parent),
		canFocus_(false)
{
	if(parent_)
	{
		parent_->AddChild(this);
	}

}
JWindow::~JWindow()
{
	if(parent_)
	{
		parent_->DelChild(this);
	}
}

void JWindow::OnKeyEvent(JEvent* e)
{
	if(!e->IsDone())
	{
		if(parent_)
		{
			parent_->OnKeyEvent(e);
		}
	}
}

void JWindow::Draw()
{
	SetTextColor(FCOLOR_BLACK);
	SetBkColor(BCOLOR_WHITE);
	JRECT rect = { 0, 0, Width() -1, Height() -1 };
	FillRect(rect);
}

void JWindow::Show()
{
	SetCurrent();
	Draw();
	Refresh();
}

void JWindow::SetCurrent()
{
	if(IsCurrent())
		return;
	if (canFocus_)
		jApp->SetCurrent(this);	else	{		std::vector<JWindow*>::const_iterator it;		for (it=childs_.begin(); it!=childs_.end(); ++it)
		{
			if ((*it)->IsCurrent())
				break;
		}		if(it == childs_.end())		{			JWindow* win = FindFirst();			if(win)			{				jApp->SetCurrent(win);			}else			{				jApp->SetCurrent(this);			}		}	}
}
bool JWindow::IsCurrent()
{
	return this == jApp->GetCurrent();
}
void JWindow::AddChild(JWindow* win)
{
	childs_.push_back(win);
}
void JWindow::DelChild(JWindow* win)
{
	childs_.erase(std::remove(childs_.begin(), childs_.end(), win), childs_.end());
}

JWindow* JWindow::FindFirst()
{
	JWindow* p = NULL;
	std::vector<JWindow*>::const_iterator it;
	for (it=childs_.begin(); it != childs_.end(); ++it)
	{
		if((*it)->canFocus_)
		{
			p = *it;
			break;
		}
	}

	return p;
}
JWindow* JWindow::FindLast()
{
	JWindow* p = NULL;
	std::vector<JWindow*>::const_reverse_iterator rit;
	for (rit=childs_.rbegin(); rit != childs_.rend(); ++rit)
	{
		if((*rit)->canFocus_)
		{
			p = *rit;
			break;
		}
	}

	return p;
}
JWindow* JWindow::FindPrev(JWindow* win)
{
	JWindow* p = 0;
	std::vector<JWindow*>::const_reverse_iterator rit;
	rit = std::find(childs_.rbegin(), childs_.rend(), win);
	if(rit == childs_.rend())
		return NULL;

	if(*rit == FindFirst())
		p = FindLast();
	else
	{
		++rit;
		for (; rit != childs_.rend(); ++rit)
		{
			if((*rit)->canFocus_)
			{
				p = *rit;
				break;
			}
		}
	}

	return p;
}
JWindow* JWindow::FindNext(JWindow* win)
{
	JWindow* p = 0;
	std::vector<JWindow*>::const_iterator it;
	it = std::find(childs_.begin(), childs_.end(), win);
	if(it == childs_.end())
		return NULL;

	if(*it == FindLast())
		p = FindFirst();
	else
	{
		++it;
		for (; it != childs_.end(); ++it)
		{
			if((*it)->canFocus_)
			{
				p = *it;
				break;
			}
		}
	}

	return p;
}