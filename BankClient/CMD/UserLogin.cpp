#include "UserLogin.h"

#include "../../Public/Logging.h"
#include "../../Public/JUtil.h"

using namespace PUBLIC;
using namespace CMD;

void UserLogin::Execute(BankSession& session)
{
	JOutStream jos;

	uint16 cmd = CMD_LOGIN;
	jos<<cmd;

	size_t lengthPos = jos.Length();
	jos.Skip(2);

	string name = session.GetAttribute("name");
	jos<<name;

	string pass = session.GetAttribute("pass");
	jos<<pass;

	size_t length = jos.Length();
	jos.Reposition(lengthPos);
	jos<<static_cast<uint16>(length - sizeof(RequestHead));

	session.Send(jos.Data(), length);	// 发送请求包
	session.Recv();	// 接收应答包
	JInStream jis((const char*)session.GetResponsePack(), session.GetResponsePack()->head.len+sizeof(ResponseHead));
	// 跳过cmd、len
	jis.Skip(4);
	uint16 cnt;
	uint16 seq;
	int16 error_code;
	jis>>cnt>>seq>>error_code;

	char error_msg[31];
	jis.ReadBytes(error_msg, 30);

	session.SetErrorCode(error_code);
	session.SetErrorMsg(error_msg);
}


