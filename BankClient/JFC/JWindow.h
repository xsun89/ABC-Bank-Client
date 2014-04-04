#ifndef _JWINDOW_H_
#define _JWINDOW_H_
#include "JApplication.h"
#include "JWindowBase.h"
#include <vector>

namespace JFC
{

class JEvent;
class JWindow : public JWindowBase
{
public:
	JWindow();
	JWindow(SHORT x, SHORT y, SHORT width, SHORT height, JWindow* parent=jApp->Root());
	virtual ~JWindow();

	virtual void OnKeyEvent(JEvent* e);
	virtual void Draw();
	void Show();
	void SetCurrent();
	bool IsCurrent();
	void SetCanFocus(bool canFocus) { canFocus_ = canFocus; }
	void AddChild(JWindow* win);
	void DelChild(JWindow* win);

	JWindow* FindFirst();
	JWindow* FindLast();
	JWindow* FindPrev(JWindow* win);
	JWindow* FindNext(JWindow* win);
protected:
	JWindow* parent_;
	std::vector<JWindow*> childs_;
	bool canFocus_;
};

}
#endif
