#include "BankSession.h"
#include "Client.h"
#include "../Public/Exception.h"
#include "../Public/StringUtil.h"

#include <iostream>

BankSession::BankSession() : socket_(new Socket), errorCode_(0)
{
	socket_->Create();
	if(!socket_->Connect(
		"127.0.0.1",
		8888)
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
	ret = socket_->RecvN(buffer_, sizeof(buffer_));
	if(ret == 0)
		throw Exception("Server is off line");
	else if(ret != sizeof(ResponseHead))
		throw Exception("Data parkage wrong");

	uint16 cmd = Endian::NetworkToHost16(responsePack_->head.cmd);
	uint16 len = Endian::NetworkToHost16(responsePack_->head.len);

	responsePack_->head.cmd = cmd;
	responsePack_->head.len = len;

	if(len == 0)
		return;

	ret = socket_->RecvN(responsePack_->buf, len);
	if(ret == 0)
		throw Exception("Server is off line");
	else if(ret != sizeof(ResponseHead))
		throw Exception("Data parkage wrong");
}