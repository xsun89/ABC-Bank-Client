#ifndef _LOGIN_FORM_H_
#define _LOGIN_FORM_H_
#include "../JFC/JForm.h"
#include "../JFC/JButton.h"
#include "../JFC/JLabel.h"
#include "../JFC/JEdit.h"

using namespace JFC;

namespace UI
{
class LoginForm : public JForm
{
public:
	LoginForm(SHORT x, SHORT y, SHORT width, SHORT height,
		JWindow* parent = jApp->Root());
	~LoginForm();

	virtual void Draw();
	virtual void OnKeyEvent(JEvent* e);

private:
	void DrawBorder();
	void Login();
	void ReSet();
	void Exit();
	JButton* btnLogin_;
	JButton* btnExit_;
	JEdit* editUser_;
	JEdit* editPass_;

	JLabel* lblUser_;
	JLabel* lblUserTip_;
	JLabel* lblPass_;
	JLabel* lblPassTip_;
};

}

#endif