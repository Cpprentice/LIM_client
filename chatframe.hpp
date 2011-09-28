#ifndef CHATFRAME_HPP
#define CHATFRAME_HPP

#include <wx/wx.h>
#include <wx/file.h>

#include <wx/animate.h>
#include "tcp.hpp"

class Chatframe : public wxFrame
{
	public:
		Chatframe(wxString _nick, TCPClient* _client);
		~Chatframe();
		bool running;

		void UpdateNicklist();
	private:
		wxTextCtrl* m_textCtrl1;
		wxTextCtrl* m_textCtrl2;
		wxListBox* m_listBox1;
		wxButton* m_button1;

		// Virtual event handlers, overide them in your derived class
		void OnSend( wxCommandEvent& event );

		TCPClient* client;
		wxString nick;
};

class NickDialog : public wxDialog
{
	public:
		NickDialog(wxString*);
		~NickDialog();
	private:
		wxTextCtrl* name;
		void OnEnter(wxCommandEvent& event);
		wxString* nick;
};

class LoadDialog : public wxDialog
{
	public:
		LoadDialog(wxString);
		~LoadDialog();
	private:
		wxAnimationCtrl* ani;
};

class Thread : public wxThread
{
	public:
		Thread(TCPClient* _client, LoadDialog* _dlg, Chatframe* _f);
		void* Entry(void);
	private:
		TCPClient* client;
		LoadDialog* dlg;
		Chatframe* frame;
};

class Timer : public wxTimer
{
	public:
		Timer(Chatframe*, LoadDialog*, TCPClient*);
		void Notify();
	private:
		Chatframe* f;
		LoadDialog* d;
		TCPClient* client;
};

#endif
