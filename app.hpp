#ifndef APP_HPP
#define APP_HPP

#include <wx/wx.h>

class Timer;
class App : public wxApp
{
	public:
		bool OnInit();
	private:
		Timer* t;
};

#endif
