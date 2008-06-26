#ifndef WINDOW_H
#define WINDOW_H
#include "transporter/visual/visualSystem.h"

class Window : public Object
{
protected : Window(u32 cid,u32 id);
			virtual ~Window();
			u32 posX;
			u32 posY;
			u32 width;
			u32 height;
			bit visible;
			bit minimized;
			str title;
public    : static Window* create();
			static Window* create(u32 w,u32 h);
			static Window* create(u32 x,u32 y,u32 w,u32 h);
			static Window* create(str titlestr);
			static Window* create(str titlestr,u32 w,u32 h);
			static Window* create(str titlestr,u32 x,u32 y,u32 w,u32 h);			
			
			u32 getWidth();
			u32 getHeight();
			str getTitle();
			u32 getPositionX();
			u32 getPositionY();
			bit isMinimized();
			bit isVisible();
			void getPosition(OUT u32& x,OUT u32& y);

			virtual void setWidth(IN u32 w) = 0;
			virtual void setHeight(IN u32 h) = 0;
			virtual u32 getClientWidth() = 0;
			virtual u32 getClientHeight() = 0;
			virtual void setTitle(str titlestr) = 0;			
			virtual void setPosition(u32 x,u32 y) = 0;
			virtual void setPositionX(u32 x) = 0;
			virtual void setPositionY(u32 y) = 0;						
			virtual void repaint() = 0;
			virtual void hide() = 0;
			virtual void show() = 0;
			virtual void minimize() = 0;
			virtual void maximize() = 0;
			virtual void restore() = 0;			
			virtual void* getHandle() = 0;
			virtual hmath::v2 getCursorPos() = 0;

			Event<Window*> onResized;
			Event<Window*> onMoved;
			Event<Window*> onClose;
			Event<Window*> onDestroy;
			Event<Window*> onVisibility;
			Event<Window*> onPaint;

			static const u32 defaultWidth = 640;
			static const u32 defaultHeight = 480;
			static const u32 defaultPosX = 0;
			static const u32 defaultPosY = 0;
};
#endif