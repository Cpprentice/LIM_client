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

void TCPClient::SetNicklist(wxListBox* _nicklist)
{
	conn->SetNicklist(_nicklist);
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
		msg = msg.substr(0, size);
		msg += "\n";
		//msg[msg.size()-1] = '\n';
		//msg += "\0";
		chatbox->AppendText(msg);
	}
	else if( item == "logon")
	{
		wxTextAttr def = chatbox->GetDefaultStyle();
		wxTextAttr temp;
		//temp.SetFlags(wxTEXT_ATTR_FONT_ITALIC);
		temp.SetFont(*wxITALIC_FONT);

		//wxTextAttr temp(*wxGREEN, wxNullColour, *wxITALIC_FONT);
		chatbox->SetDefaultStyle(temp);
		//chatbox->SetDefaultStyle(wxTextAttr(*wxGREEN, wxNullColour, *wxITALIC_FONT));

		wxString msg = data;
		msg = msg.substr(0, size);
		msg += "\n";
		chatbox->AppendText(msg);
		UpdateNicklist();

		chatbox->SetDefaultStyle(def);
	}
	else if( item == "logoff")
	{
		wxTextAttr def = chatbox->GetDefaultStyle();
		wxTextAttr temp;
		//temp.SetFlags(wxTEXT_ATTR_FONT_ITALIC);
		temp.SetFont(*wxITALIC_FONT);
		chatbox->SetDefaultStyle(temp);

		wxString msg = data;
		msg = msg.substr(0, size);
		msg += "\n";
		chatbox->AppendText(msg);
		UpdateNicklist();

		chatbox->SetDefaultStyle(def);
	}

	return true;
}

void TCPConnection::SetChatbox(wxTextCtrl* _chatbox)
{
	chatbox = _chatbox;
}

void TCPConnection::SetNicklist(wxListBox* _nicklist)
{
	nicklist = _nicklist;
}

void TCPConnection::UpdateNicklist()
{
	nicklist->Clear();
	//int anz = 0;
	wxString nicks = Request("nicklist", 0);
	wxString next = "";
	for( size_t n = 0; n < nicks.size(); n++)
	{
		if( nicks[n] == '\n')
		{
			nicklist->Append(next);
			next.Clear();
		}
		else
		{
			next += nicks[n];
		}
	}
	if( next != "")nicklist->Append(next);
	next.Clear();
}
