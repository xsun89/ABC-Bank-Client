#ifndef _FORMMANAGER_H_
#define _FORMMANAGER_H_
#include <string>
#include <map>

#include "../JFC/JForm.h"
#include "../../Public/Singleton.h"
using namespace PUBLIC;
using namespace JFC;
namespace UI
{

class FormManager
{
	friend class Singleton<FormManager>;
public:
	void Add(const std::string& name, JForm* form)
	{
		forms_[name] = form;
	}

	JForm* Get(const std::string& name)
	{
		return forms_[name];
	}
private:
	std::map<std::string, JForm*> forms_;
	FormManager();
	~FormManager();
};

}
#endif
