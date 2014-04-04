#ifndef _JAPPLICATION_H_
#define _JAPPLICTIION_H_

namespace JFC
{
class JWindow;

class JApplication
{
public:
	JApplication();
	~JApplication();
	void ShowCursor() const;
	void HideCursor() const;
	static JApplication* Instance() { return self_; }
	JWindow* GetCurrent() const { return current_; }
	void SetCurrent(JWindow* win) { current_ = win; }
	JWindow* Root() const { return root_; }
	int Exec();
private:
	static JApplication* self_;
	JWindow* current_;
	JWindow* root_;
};

#define jApp JApplication::Instance() 

}

#endif


