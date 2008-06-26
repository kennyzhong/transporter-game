#include "transporter/visual/visualSystem.h"

Window* Window::create()
{
#ifdef WIN32
	return (Window*)ObjectFactory<Win32Window>::getInstance()->create();
#endif
}

Window* Window::create( u32 w,u32 h )
{
#ifdef WIN32
	Window* newWindow = (Window*)ObjectFactory<Win32Window>::getInstance()->create();
	newWindow->width  = w;
	newWindow->height = h;
	return newWindow;
#endif
}

Window* Window::create( u32 x,u32 y,u32 w,u32 h )
{
#ifdef WIN32
	Window* newWindow = (Window*)ObjectFactory<Win32Window>::getInstance()->create();
	newWindow->width  = w;
	newWindow->height = h;
	newWindow->posX = x;
	newWindow->posY = y;
	return newWindow;
#endif
}

Window* Window::create( str titlestr )
{
#ifdef WIN32
	Window* newWindow = (Window*)ObjectFactory<Win32Window>::getInstance()->create();
	newWindow->title = titlestr;
	return newWindow;
#endif
}

Window* Window::create( str titlestr,u32 w,u32 h )
{
#ifdef WIN32
	Window* newWindow = (Window*)ObjectFactory<Win32Window>::getInstance()->create();
	newWindow->width  = w;
	newWindow->height = h;
	newWindow->title  = titlestr;
	return newWindow;
#endif
}

Window* Window::create( str titlestr,u32 x,u32 y,u32 w,u32 h )
{
#ifdef WIN32
	Window* newWindow = (Window*)ObjectFactory<Win32Window>::getInstance()->create();
	newWindow->width  = w;
	newWindow->height = h;
	newWindow->posX = x;
	newWindow->posY = y;
	newWindow->title = titlestr;
	return newWindow;
#endif
}

u32 Window::getWidth()
{
	return width;
}

u32 Window::getHeight()
{
	return height;
}

str Window::getTitle()
{
	return title;
}

u32 Window::getPositionX()
{
	return posX;
}

u32 Window::getPositionY()
{
	return posY;
}

void Window::getPosition( OUT u32& x,OUT u32& y )
{
	x = posX;
	y = posY;
}

bit Window::isMinimized()
{
	return minimized;
}

bit Window::isVisible()
{
	return visible;
}

Window::~Window()
{

}

Window::Window( u32 cid,u32 id ) : Object(cid,id)
{
	title = "window";
	posX  = Window::defaultPosX;
	posY  = Window::defaultPosY;
	width = Window::defaultWidth;
	height= Window::defaultHeight;
	visible = false;
	minimized = false;
}
