#include "app.hpp"
#include "chatframe.hpp"
#include "tcp.hpp"

#include <wx/file.h>

DECLARE_APP(App);
IMPLEMENT_APP(App);

bool App::OnInit()
{
	/*
	#ifdef wxUSE_UNICODE
	wxMessageBox(wxString::Format("Is defined %i", wxUSE_UNICODE), "info");
	#endif*/

	/**Check for Nickname**/
	wxString nick = wxEmptyString;
	if( wxFile::Exists("lim.ini"))
	{
		wxFile ini("lim.ini", wxFile::read);
		if( ini.IsOpened())
		{
			size_t len_left = 0;
			char* input;
			while( len_left == 0)
			{
				input = new char[20];
				memset(input, 0, 20);
				len_left = 20 - ini.Read(input, 20);
				if( len_left != ~0u)///No Error
				{
					nick += input;
				}
				delete[] input;
			}
			ini.Close();
		}
	}


	if( nick == wxEmptyString)
	{
		NickDialog* dlg = new NickDialog(&nick);
		//dlg->SetIcon(wxICON(aaaa));
		dlg->ShowModal();
		delete dlg;
	}

	if( nick == wxEmptyString)
	{
		wxMessageBox("Not a valid name!", "Error");
		return false;
	}


	//LoadDialog* loader = new LoadDialog(nick);
	//loader->Show();

	TCPClient* client = new TCPClient(nick);
	client->Connect();

	Chatframe* frame = new Chatframe(nick, client);
	//frame->SetIcon(wxICON(aaaa));
	frame->Show();
	//t = new Timer(frame, loader, client);
	//t->Start(10, false);

	return true;
}
