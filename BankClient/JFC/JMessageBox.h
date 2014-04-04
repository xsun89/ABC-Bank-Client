#ifndef _JMESSAGE_BOX_H_
#define _JMESSAGE_BOX_H_

#include "JWindow.h"
#include "JButton.h"
#include <string>
#include <vector>

namespace JFC
{

class JMessageBox
{
public:
	static int Show(const std::string& title, const std::string& text, 
		std::vector<std::string>& buttons);
};

class JMessageBoxImpl : public JWindow
{
public:
	JMessageBoxImpl(SHORT x, SHORT y, SHORT width, SHORT height,
		const std::string& title, const std::string& text, 
		std::vector<std::string>& buttons, SHORT btnDistance,
		int lines, JWindow* parent=jApp->Root());
	virtual ~JMessageBoxImpl();

	virtual void Draw();

	int Exec();

private:
	const std::string& title_;
	const std::string& text_;
	int lines_;
	short btnDistance_;
	std::vector<JButton*> btns_;
};
}
#endif

