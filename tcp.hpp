#ifndef CLIENT_TCP_HPP
#define CLIENT_TCP_HPP

#include <wx/wx.h>
#include <wx/sckipc.h>

class TCPConnection : public wxTCPConnection
{
	public:
		bool OnAdvise(const wxString&, const wxString&, char*, int, wxIPCFormat);
		void SetChatbox(wxTextCtrl*);
		void SetNicklist(wxListBox*);
		void UpdateNicklist();
	private:
		wxTextCtrl* chatbox;
		wxListBox* nicklist;
};

class TCPClient : public wxTCPClient
{
	public:
		wxConnectionBase* OnMakeConnection();
		wxConnectionBase* Connect();
		TCPClient(wxString _nick);
		void SetChatbox(wxTextCtrl*);
		void SetNicklist(wxListBox*);
		~TCPClient();
		TCPConnection* GetConn();


	private:
		TCPConnection* conn;
		wxString nick;
};

#endif
