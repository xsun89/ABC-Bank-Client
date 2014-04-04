#ifndef _TRANSACTIONMANAGER_H_
#define _TRANSACTIONMANAGER_H_
#include <map>
#include <string>
#include "../Public/JUtil.h"
#include "CMD/Transaction.h"
#include "../Public/Singleton.h"
#include "BankSession.h"
using namespace CMD;
using namespace PUBLIC;

class TransactionManager
{
	friend class Singleton<TransactionManager>;
public:
	bool DoAction(BankSession& session);
private:
	std::map<uint16, Transaction*> m_actions; 
	TransactionManager();
	TransactionManager(const TransactionManager& rhs);
	~TransactionManager();
};
#endif