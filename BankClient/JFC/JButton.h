#ifndef _JBUTTON_H_
#define _JBUTTON_H_
#include "JWindow.h"
namespace JFC
{
class JButton : public JWindow
{
public:
	JButton();
	JButton(SHORT x, SHORT y, SHORT width, SHORT height, const std::string& text=std::string(), JWindow* parent=jApp->Root());
	virtual void Draw();
	~JButton();
private:
	std::string text_;
};
}

#endif
