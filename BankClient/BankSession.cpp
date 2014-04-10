#include "BankSession.h"
#include "Client.h"
#include "../Public/Exception.h"
#include "../Public/StringUtil.h"

#include <iostream>

BankSession::BankSession() : socket_(new Socket), errorCode_(0)
{
	socket_->Create();
	if(!socket_->Connect(
		Singleton<Client>::Instance().GetServerIp().c_str(),
		Singleton<Client>::Instance().GetPort())
		)
		throw Exception("Connection Failed");
	responsePack_ = (ResponsePack*)buffer_;
}

BankSession::~BankSession()
{

}

void BankSession::Send(const char* buf, size_t len)
{
	socket_->SendN(buf, len);
}

void BankSession::Clear()
{
	request_.clear();
	response_.clear();
	errorCode_ = 0;
}

void BankSession::SetAttribute(const string& k, const string& v)
{
	request_[k] = v;
}

const string& BankSession::GetAttribute(const string& k)
{
	return request_[k];
}

void BankSession::Recv()
{
	int ret;
	ret = socket_->RecvN(buffer_, sizeof(ResponseHead));
	if(ret == 0)
		throw Exception("Server is off line");
	else if(ret != sizeof(ResponseHead))
		throw Exception("Data package wrong 1");

	uint16 cmd = Endian::NetworkToHost16(responsePack_->head.cmd);
	uint16 len = Endian::NetworkToHost16(responsePack_->head.len);

	if(len == 0)
		return;

	ret = socket_->RecvN(responsePack_->buf, len);
	if(ret == 0)
		throw Exception("Server is off line");
	else if(ret != len)
		throw Exception("Data package wrong 2");

	unsigned char hash[16];
	MD5 md5;
	md5.MD5Make(hash, (unsigned char const*)buffer_, sizeof(ResponseHead) + len -8);
	for (int i=0; i<8; ++i)
	{
		hash[i] = hash[i] ^ hash[i+8];
		hash[i] = hash[i] ^ ((cmd >> (i%2)) & 0xff);
	}
	if (memcmp(hash, buffer_+sizeof(ResponseHead)+len-8, 8))
	{
		throw Exception("Wrong data package");
	}

	responsePack_->head.cmd = cmd;
	responsePack_->head.len = len;
}