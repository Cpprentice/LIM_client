#include "chatframe.hpp"


Chatframe::Chatframe(wxString _nick, TCPClient* _client) : wxFrame(0, wxID_ANY, "LIM Client")
{
	SetBackgroundColour(wxColour(227,229,234));
	client = _client;
	nick = _nick;

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH  );
	//m_textCtrl1->Enable( false );

	bSizer2->Add( m_textCtrl1, 1, wxEXPAND|wxTOP|wxLEFT, 5 );

	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer2->Add( m_textCtrl2, 0, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	m_textCtrl2->SetFocus();

	bSizer1->Add( bSizer2, 3, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_listBox1 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0|wxVSCROLL|wxTE_READONLY  );
	m_listBox1->SetBackgroundColour( wxColour( 234, 232, 151 ) );
	//m_listBox1->Enable( false );

	bSizer4->Add( m_listBox1, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_button1 = new wxButton( this, wxID_ANY, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	bSizer3->Add( bSizer4, 3, wxEXPAND, 5 );

	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );

	this->SetSizer( bSizer1 );
	this->Layout();

	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Chatframe::OnSend ), NULL, this );
	m_textCtrl2->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Chatframe::OnSend ), NULL, this );
	client->SetChatbox(m_textCtrl1);
	client->SetNicklist(m_listBox1);
}

Chatframe::~Chatframe()
{
	delete client;
}

void Chatframe::OnSend(wxCommandEvent& event)
{
	/*wxString content = m_textCtrl1->GetValue();
	content += m_textCtrl2->GetValue() + "\n";
	m_textCtrl1->ChangeValue(content);*/



	if( m_textCtrl2->GetValue() != "")
	{
		wxString msg = "[";
		msg += wxDateTime::Now().FormatTime() + "] " + nick + ":  " + m_textCtrl2->GetValue();
		client->GetConn()->Poke("message", (wxChar*)(msg.c_str()),msg.size());
		/*m_textCtrl1->AppendText("[");
		m_textCtrl1->AppendText(wxDateTime::Now().FormatTime());
		m_textCtrl1->AppendText("] ");
		m_textCtrl1->AppendText(nick);
		m_textCtrl1->AppendText(":  ");
		m_textCtrl1->AppendText(m_textCtrl2->GetValue());
		m_textCtrl1->AppendText("\n");*/
	}


	//wxMessageBox(m_textCtrl2->GetValue(), "Message");
	m_textCtrl2->Clear();
	//event.Skip();
}

void Chatframe::UpdateNicklist()
{

}

NickDialog::NickDialog(wxString* ptr) : wxDialog(0, wxID_ANY, "Enter your Nickname")
{
	SetClientSize(250, 50);
	nick = ptr;
	wxBoxSizer* sizer;
	sizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	sizer->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	name = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER  );

	sizer->Add( name, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	name->SetFocus();
	wxButton* m_button2 = new wxButton( this, wxID_ANY, wxT("Enter"), wxDefaultPosition, wxDefaultSize, 0 );
	sizer->Add( m_button2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	this->SetSizer( sizer );

	name->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( NickDialog::OnEnter ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NickDialog::OnEnter ), NULL, this );
}

NickDialog::~NickDialog()
{
	if( !wxFile::Exists("lim.ini"))
	{
		wxCommandEvent event;
		OnEnter(event);
	}
	GetSizer()->Clear(true);
}

void NickDialog::OnEnter(wxCommandEvent& event)
{
	if( name->GetValue() != wxEmptyString)
	{
		*nick = name->GetValue();
		wxFile ini("lim.ini", wxFile::write);
		ini.Write(name->GetValue().c_str(), name->GetValue().size());
		ini.Close();
	}
	Close();
}

LoadDialog::LoadDialog(wxString name) : wxDialog(0, wxID_ANY, "Connecting...", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE&(~wxCLOSE_BOX))
{
	SetClientSize(200, 200);
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxStaticText* m_staticText1 = new wxStaticText( this, wxID_ANY, wxString::Format("Welcome %s\nConnecting to Server", name.c_str()), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxImage::AddHandler(new wxGIFHandler);
	ani = new wxAnimationCtrl( this, wxID_ANY, wxNullAnimation, wxDefaultPosition, wxDefaultSize, wxAC_DEFAULT_STYLE );
	ani->LoadFile("loading_radar_postaa_round.gif");
	ani->Play();
	bSizer1->Add( ani, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	this->SetSizer( bSizer1 );
}

LoadDialog::~LoadDialog()
{
	GetSizer()->Clear(true);
}

Thread::Thread(TCPClient* _client, LoadDialog* _dlg, Chatframe* _f)
{
	client = _client;
	dlg = _dlg;
	frame = _f;
}

void* Thread::Entry(void)
{

	client->Connect();
	if( client->GetConn() == 0)
	{
		dlg->Close();
		wxMessageBox("Connection failed!", "Error");
		return 0;
	}


	//frame->SetIcon(wxICON(aaaa));

	frame->Show();
	dlg->Close();
	//Sleep(500);
	//wxMessageBox("Jetzt bin ich im Thread", "info");

	//dlg->Show();
	/*client->Connect();
	if( client->GetConn() == 0)
	{
		wxMessageBox("Connection Failed", "Error");
		dlg->EndModal(-1);
	}
	else
		dlg->EndModal(0);
*/
	return 0;
}

void Timer::Notify()
{


	Thread* t = new Thread(client, d, f);
	t->Create();
	t->Run();

	return;
}

Timer::Timer(Chatframe* _f, LoadDialog* _d, TCPClient* _client)
{
	d = _d;
	f = _f;
	client = _client;
}
