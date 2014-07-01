
#ifndef _SNICE_UI_H_
#define _SNICE_UI_H_

//#include "include/glfw.h"
#if defined(__APPLE_CC__)
 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
#else
 #include <GL/gl.h>
 #include <GL/glu.h>
#endif

#include "viewport.h"
#include "UI_window.h"
#include "widget/button.h"
#include "mylist.h"
#include "tgafile.h"
#include "widget/label.h"
#include "widget/text_box.h"
#include "widget/slider.h"
#include "widget/progress.h"
#include "widget/sub_menu.h"
#include "widget/menu.h"


// Key and button state/action definitions
#define SNICEUI_RELEASE            0
#define SNICEUI_PRESS              1
#define SNICEUI_MOUSE_BUTTON_LEFT   0
#define SNICEUI_MOUSE_BUTTON_RIGHT  1
#define SNICEUI_MOUSE_BUTTON_MIDDLE 2

// Keyboard key definitions: 8-bit ISO-8859-1 (Latin 1) encoding is used
// for printable keys (such as A-Z, 0-9 etc), and values above 256
// represent special (non-printable) keys (e.g. F1, Page Up etc).
// Thanks to GLFW for theses definition.
#define SNICEUI_KEY_UNKNOWN      -1
#define SNICEUI_KEY_SPACE        32
#define SNICEUI_KEY_SPECIAL      256
#define SNICEUI_KEY_ESC          (SNICEUI_KEY_SPECIAL+1)
#define SNICEUI_KEY_F1           (SNICEUI_KEY_SPECIAL+2)
#define SNICEUI_KEY_F2           (SNICEUI_KEY_SPECIAL+3)
#define SNICEUI_KEY_F3           (SNICEUI_KEY_SPECIAL+4)
#define SNICEUI_KEY_F4           (SNICEUI_KEY_SPECIAL+5)
#define SNICEUI_KEY_F5           (SNICEUI_KEY_SPECIAL+6)
#define SNICEUI_KEY_F6           (SNICEUI_KEY_SPECIAL+7)
#define SNICEUI_KEY_F7           (SNICEUI_KEY_SPECIAL+8)
#define SNICEUI_KEY_F8           (SNICEUI_KEY_SPECIAL+9)
#define SNICEUI_KEY_F9           (SNICEUI_KEY_SPECIAL+10)
#define SNICEUI_KEY_F10          (SNICEUI_KEY_SPECIAL+11)
#define SNICEUI_KEY_F11          (SNICEUI_KEY_SPECIAL+12)
#define SNICEUI_KEY_F12          (SNICEUI_KEY_SPECIAL+13)
#define SNICEUI_KEY_F13          (SNICEUI_KEY_SPECIAL+14)
#define SNICEUI_KEY_F14          (SNICEUI_KEY_SPECIAL+15)
#define SNICEUI_KEY_F15          (SNICEUI_KEY_SPECIAL+16)
#define SNICEUI_KEY_F16          (SNICEUI_KEY_SPECIAL+17)
#define SNICEUI_KEY_F17          (SNICEUI_KEY_SPECIAL+18)
#define SNICEUI_KEY_F18          (SNICEUI_KEY_SPECIAL+19)
#define SNICEUI_KEY_F19          (SNICEUI_KEY_SPECIAL+20)
#define SNICEUI_KEY_F20          (SNICEUI_KEY_SPECIAL+21)
#define SNICEUI_KEY_F21          (SNICEUI_KEY_SPECIAL+22)
#define SNICEUI_KEY_F22          (SNICEUI_KEY_SPECIAL+23)
#define SNICEUI_KEY_F23          (SNICEUI_KEY_SPECIAL+24)
#define SNICEUI_KEY_F24          (SNICEUI_KEY_SPECIAL+25)
#define SNICEUI_KEY_F25          (SNICEUI_KEY_SPECIAL+26)
#define SNICEUI_KEY_UP           (SNICEUI_KEY_SPECIAL+27)
#define SNICEUI_KEY_DOWN         (SNICEUI_KEY_SPECIAL+28)
#define SNICEUI_KEY_LEFT         (SNICEUI_KEY_SPECIAL+29)
#define SNICEUI_KEY_RIGHT        (SNICEUI_KEY_SPECIAL+30)
#define SNICEUI_KEY_LSHIFT       (SNICEUI_KEY_SPECIAL+31)
#define SNICEUI_KEY_RSHIFT       (SNICEUI_KEY_SPECIAL+32)
#define SNICEUI_KEY_LCTRL        (SNICEUI_KEY_SPECIAL+33)
#define SNICEUI_KEY_RCTRL        (SNICEUI_KEY_SPECIAL+34)
#define SNICEUI_KEY_LALT         (SNICEUI_KEY_SPECIAL+35)
#define SNICEUI_KEY_RALT         (SNICEUI_KEY_SPECIAL+36)
#define SNICEUI_KEY_TAB          (SNICEUI_KEY_SPECIAL+37)
#define SNICEUI_KEY_ENTER        (SNICEUI_KEY_SPECIAL+38)
#define SNICEUI_KEY_BACKSPACE    (SNICEUI_KEY_SPECIAL+39)
#define SNICEUI_KEY_INSERT       (SNICEUI_KEY_SPECIAL+40)
#define SNICEUI_KEY_DEL          (SNICEUI_KEY_SPECIAL+41)
#define SNICEUI_KEY_PAGEUP       (SNICEUI_KEY_SPECIAL+42)
#define SNICEUI_KEY_PAGEDOWN     (SNICEUI_KEY_SPECIAL+43)
#define SNICEUI_KEY_HOME         (SNICEUI_KEY_SPECIAL+44)
#define SNICEUI_KEY_END          (SNICEUI_KEY_SPECIAL+45)
#define SNICEUI_KEY_KP_0         (SNICEUI_KEY_SPECIAL+46)
#define SNICEUI_KEY_KP_1         (SNICEUI_KEY_SPECIAL+47)
#define SNICEUI_KEY_KP_2         (SNICEUI_KEY_SPECIAL+48)
#define SNICEUI_KEY_KP_3         (SNICEUI_KEY_SPECIAL+49)
#define SNICEUI_KEY_KP_4         (SNICEUI_KEY_SPECIAL+50)
#define SNICEUI_KEY_KP_5         (SNICEUI_KEY_SPECIAL+51)
#define SNICEUI_KEY_KP_6         (SNICEUI_KEY_SPECIAL+52)
#define SNICEUI_KEY_KP_7         (SNICEUI_KEY_SPECIAL+53)
#define SNICEUI_KEY_KP_8         (SNICEUI_KEY_SPECIAL+54)
#define SNICEUI_KEY_KP_9         (SNICEUI_KEY_SPECIAL+55)
#define SNICEUI_KEY_KP_DIVIDE    (SNICEUI_KEY_SPECIAL+56)
#define SNICEUI_KEY_KP_MULTIPLY  (SNICEUI_KEY_SPECIAL+57)
#define SNICEUI_KEY_KP_SUBTRACT  (SNICEUI_KEY_SPECIAL+58)
#define SNICEUI_KEY_KP_ADD       (SNICEUI_KEY_SPECIAL+59)
#define SNICEUI_KEY_KP_DECIMAL   (SNICEUI_KEY_SPECIAL+60)
#define SNICEUI_KEY_KP_EQUAL     (SNICEUI_KEY_SPECIAL+61)
#define SNICEUI_KEY_KP_ENTER     (SNICEUI_KEY_SPECIAL+62)
#define SNICEUI_KEY_LAST         SNICEUI_KEY_KP_ENTER

/**	\brief define return minimal value  beetween X an Y*/
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
/**	\brief define return maximal value  beetween X an Y*/
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

//extern Texture textures[20];	// Storage For Textures
//extern GLuint base;				// Base Display List For The Font

class Snice_UI
{

protected:
	int mouseX; /**< \brief  Horizontal mouse position*/
	int mouseY; /**< \brief  Vertical mouse position*/

	int width;
    int height;

     double  t, t0, spf;

	Viewport* viewport; /**< \brief Origin viewport*/

public:

	Snice_UI(int w, int h, unsigned char fps);

	virtual ~Snice_UI();

	/** \brief funtion to draw the user interface*/
	void Draw();

	Viewport* GetViewport();

	void Resize( int w, int h );

	void MouseMove( int x, int y );

	void MouseButton( int button, int action);
	void KeyPressed( int button, int action);
	void CharPressed( int character, int action);

};


//GLvoid BuildFont(GLvoid);
//GLvoid KillFont(GLvoid);
int InitSniceUI();
void DrawCursor();


#endif //_SNICE_UI_H_

// End of file snice_UI.h
