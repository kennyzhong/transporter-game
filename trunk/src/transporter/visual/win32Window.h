#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H
#include "transporter/visual/visualSystem.h"

class Win32Window : public Window
{
friend class ObjectFactory<Win32Window>;
friend class Window;
protected : Win32Window(u32 classId,u32 objectId);
			~Win32Window();
			void buildWindow();
			void destroyWindow();
			void setDCFormat();
			static LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			HWND wndHandle;
			HDC hdc;
			HINSTANCE hInstance;
			str wndClassName;
public    : void setWidth(IN u32 w);
			void setHeight(IN u32 h);
			void setTitle(str titlestr);
			void setPosition(u32 x,u32 y);
			void setPositionX(u32 x);
			void setPositionY(u32 y);
			u32 getClientWidth();
			u32 getClientHeight();
			void hide();
			void show();
			void minimize();
			void maximize();
			void restore();
			void repaint();
			void* getHandle();
			hmath::v2 getCursorPos();
};
#endif