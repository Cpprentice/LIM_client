#include "tcp.hpp"

wxConnectionBase* TCPClient::OnMakeConnection()
{
	return new TCPConnection;
}

TCPClient::TCPClient(wxString _nick)
{
	nick = _nick;
}

TCPClient::~TCPClient()
{
	if( conn != 0)conn->Disconnect();
	delete conn;
}

void TCPClient::SetChatbox(wxTextCtrl* _chatbox)
{
	conn->SetChatbox(_chatbox);
}

TCPConnection* TCPClient::GetConn()
{
	return conn;
}

wxConnectionBase* TCPClient::Connect()
{
	wxString topic = "Logon";
	topic += nick;
	conn = (TCPConnection*)MakeConnection("192.168.178.254", "11111", topic.c_str());
	return conn;
}

bool TCPConnection::OnAdvise(const wxString& topic, const wxString& item, char* data, int size, wxIPCFormat format)
{
	if( item == "message")
	{
		wxString msg = data;
		msg += "\n";
		//msg[msg.size()-1] = '\n';
		//msg += "\0";
		chatbox->AppendText(msg);
	}

	return true;
}

void TCPConnection::SetChatbox(wxTextCtrl* _chatbox)
{
	chatbox = _chatbox;
}
