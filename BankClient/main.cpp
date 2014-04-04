#include "JFC/JButton.h"
#include "UI/LoginForm.h"
#include "UI/MainMenuForm.h"
#include "UI/FormManager.h"
#include "../Public/Singleton.h"
#include "Client.h"

using namespace JFC;
using namespace UI;
using namespace PUBLIC;

int main()
{
	JApplication app;
	Singleton<Client>::Instance();
	JForm* form = Singleton<FormManager>::Instance().Get("LoginForm");
	form->Show();
	return app.Exec();
}
