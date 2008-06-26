#include "transporter/visual/visualSystem.h"

Win32Window::Win32Window( u32 classId,u32 objectId )
	:Window(classId, objectId )
{
	static int counter;
	wndClassName = "Win32Window"+IntToStr(counter++);
	hInstance = GetModuleHandle(NULL);
	wndHandle = NULL;
	buildWindow();
}

void Win32Window::setWidth( IN u32 w )
{
	width = w;
	MoveWindow(wndHandle,posX,posY,width,height,true);
}

void Win32Window::setHeight( IN u32 h )
{
	height = h;
	MoveWindow(wndHandle,posX,posY,width,height,true);
}

void Win32Window::setTitle( str titlestr )
{
	SetWindowText(wndHandle,titlestr.c_str());
}

void Win32Window::setPosition( u32 x,u32 y )
{

}

void Win32Window::setPositionX( u32 x )
{

}

void Win32Window::setPositionY( u32 y )
{

}

void Win32Window::hide()
{

}

void Win32Window::show()
{

}

void Win32Window::minimize()
{

}

void Win32Window::maximize()
{

}

void Win32Window::restore()
{

}

LRESULT CALLBACK Win32Window::wndproc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static Win32Window* self;
	switch(message)
	{
	case WM_CREATE  :{
						CREATESTRUCT* info = (CREATESTRUCT*)lParam;
						self = (Win32Window*)info->lpCreateParams;
						break;
					 }
	case WM_SIZE    :{
						self->width = LOWORD(lParam);
						self->height= HIWORD(lParam);
						self->onResized(self);
						break;
					 }
	case WM_MOVE    :{
						self->posX = LOWORD(lParam);
						self->posY = HIWORD(lParam);
						self->onMoved(self);
						break;
					 }
	case WM_PAINT   :{
						self->onPaint(self);
						SwapBuffers(self->hdc);
						break;
					 }
	case WM_QUIT    :
	case WM_CLOSE   :{
						self->onClose(self);
						break;
					 }
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}
void Win32Window::buildWindow()
{
	WNDCLASS _wndclass;
	_wndclass.cbClsExtra    = 0;
	_wndclass.cbWndExtra    = 0;
	_wndclass.hbrBackground = NULL;
	_wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
	_wndclass.hIcon         = NULL;//LoadIcon (NULL, IDI_APPLICATION);
	_wndclass.hInstance     = hInstance;
	_wndclass.lpfnWndProc   = wndproc;
	_wndclass.lpszClassName = wndClassName.c_str();
	_wndclass.lpszMenuName  = NULL;
	_wndclass.style         = CS_OWNDC; //CS_HREDRAW | CS_VREDRAW | ;			  

	if( RegisterClass(&_wndclass) )
	{
		wndHandle = CreateWindowEx( 0 ,
			wndClassName.c_str(),title.c_str(),
			WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,				
			posX,posY,width,height,NULL,NULL,hInstance,this);	
		hdc = GetDC(wndHandle);			
		setDCFormat();			
	}	
}

void Win32Window::destroyWindow()
{
	if(wndHandle != NULL)
	{
		onDestroy(this);
		DestroyWindow(wndHandle);
		UnregisterClass(wndClassName.c_str(),hInstance);
		wndHandle = NULL;
	}	
}

Win32Window::~Win32Window()
{
	destroyWindow();
}

void Win32Window::setDCFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,32,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		16,
		0,0,0,0,0,0,0
	};
	
	i32 pixelFormat = ChoosePixelFormat(hdc,&pfd);
	SetPixelFormat(hdc,pixelFormat,&pfd);
}

void Win32Window::repaint()
{
	onPaint(this);
	SwapBuffers(hdc);
}

void* Win32Window::getHandle()
{
	return wndHandle;
}

hmath::v2 Win32Window::getCursorPos()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(wndHandle,&point);
	return hmath::v2(point.x,point.y);
}

u32 Win32Window::getClientWidth()
{
	RECT rect;
	GetClientRect(wndHandle,&rect);
	return rect.right;
}

u32 Win32Window::getClientHeight()
{
	RECT rect;
	GetClientRect(wndHandle,&rect);
	return rect.bottom;
}
