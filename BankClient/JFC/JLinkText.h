#ifndef _JLINKTEXT_H_
#define _JLINKTEXT_H_

#include <string>
#include "JWindow.h"

namespace JFC
{

class JLinkText : public JWindow
{
public:
	JLinkText();
	JLinkText(SHORT x, SHORT y, SHORT width, SHORT height, 
		std::string& text = std::string(), JWindow* parent = jApp->Root());
	virtual ~JLinkText();
	virtual void Draw();


private:
	std::string& text_;
};

}


#endif
