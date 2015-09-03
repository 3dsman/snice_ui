
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
//#include "tgafile.h"
#include "UI_image.h"
#include "widget/label.h"
#include "widget/text_box.h"
#include "widget/slider.h"
#include "widget/progress.h"
#include "widget/sub_menu.h"
#include "widget/menu.h"
#include "widget/color_display.h"
#include "widget/color_select_display.h"
#include "widget/color_band.h"
#include "widget/slided_panel.h"
#include "widget/file_selector.h"
#include "dialog/color_picker.h"



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
#define 	SNICEUI_KEY_UNKNOWN   -1
#define 	SNICEUI_KEY_SPACE   32
#define 	SNICEUI_KEY_APOSTROPHE   39 /* ' */
#define 	SNICEUI_KEY_COMMA   44 /* , */
#define 	SNICEUI_KEY_MINUS   45 /* - */
#define 	SNICEUI_KEY_PERIOD   46 /* . */
#define 	SNICEUI_KEY_SLASH   47 /* / */
#define 	SNICEUI_KEY_0   48
#define 	SNICEUI_KEY_1   49
#define 	SNICEUI_KEY_2   50
#define 	SNICEUI_KEY_3   51
#define 	SNICEUI_KEY_4   52
#define 	SNICEUI_KEY_5   53
#define 	SNICEUI_KEY_6   54
#define 	SNICEUI_KEY_7   55
#define 	SNICEUI_KEY_8   56
#define 	SNICEUI_KEY_9   57
#define 	SNICEUI_KEY_SEMICOLON   59 /* ; */
#define 	SNICEUI_KEY_EQUAL   61 /* = */
#define 	SNICEUI_KEY_A   65
#define 	SNICEUI_KEY_B   66
#define 	SNICEUI_KEY_C   67
#define 	SNICEUI_KEY_D   68
#define 	SNICEUI_KEY_E   69
#define 	SNICEUI_KEY_F   70
#define 	SNICEUI_KEY_G   71
#define 	SNICEUI_KEY_H   72
#define 	SNICEUI_KEY_I   73
#define 	SNICEUI_KEY_J   74
#define 	SNICEUI_KEY_K   75
#define 	SNICEUI_KEY_L   76
#define 	SNICEUI_KEY_M   77
#define 	SNICEUI_KEY_N   78
#define 	SNICEUI_KEY_O   79
#define 	SNICEUI_KEY_P   80
#define 	SNICEUI_KEY_Q   81
#define 	SNICEUI_KEY_R   82
#define 	SNICEUI_KEY_S   83
#define 	SNICEUI_KEY_T   84
#define 	SNICEUI_KEY_U   85
#define 	SNICEUI_KEY_V   86
#define 	SNICEUI_KEY_W   87
#define 	SNICEUI_KEY_X   88
#define 	SNICEUI_KEY_Y   89
#define 	SNICEUI_KEY_Z   90
#define 	SNICEUI_KEY_LEFT_BRACKET   91 /* [ */
#define 	SNICEUI_KEY_BACKSLASH   92 /* \ */
#define 	SNICEUI_KEY_RIGHT_BRACKET   93 /* ] */
#define 	SNICEUI_KEY_GRAVE_ACCENT   96 /* ` */
#define 	SNICEUI_KEY_WORLD_1   161 /* non-US #1 */
#define 	SNICEUI_KEY_WORLD_2   162 /* non-US #2 */
#define 	SNICEUI_KEY_ESCAPE   256
#define 	SNICEUI_KEY_ENTER   257
#define 	SNICEUI_KEY_TAB   258
#define 	SNICEUI_KEY_BACKSPACE   259
#define 	SNICEUI_KEY_INSERT   260
#define 	SNICEUI_KEY_DELETE   261
#define 	SNICEUI_KEY_RIGHT   262
#define 	SNICEUI_KEY_LEFT   263
#define 	SNICEUI_KEY_DOWN   264
#define 	SNICEUI_KEY_UP   265
#define 	SNICEUI_KEY_PAGE_UP   266
#define 	SNICEUI_KEY_PAGE_DOWN   267
#define 	SNICEUI_KEY_HOME   268
#define 	SNICEUI_KEY_END   269
#define 	SNICEUI_KEY_CAPS_LOCK   280
#define 	SNICEUI_KEY_SCROLL_LOCK   281
#define 	SNICEUI_KEY_NUM_LOCK   282
#define 	SNICEUI_KEY_PRINT_SCREEN   283
#define 	SNICEUI_KEY_PAUSE   284
#define 	SNICEUI_KEY_F1   290
#define 	SNICEUI_KEY_F2   291
#define 	SNICEUI_KEY_F3   292
#define 	SNICEUI_KEY_F4   293
#define 	SNICEUI_KEY_F5   294
#define 	SNICEUI_KEY_F6   295
#define 	SNICEUI_KEY_F7   296
#define 	SNICEUI_KEY_F8   297
#define 	SNICEUI_KEY_F9   298
#define 	SNICEUI_KEY_F10   299
#define 	SNICEUI_KEY_F11   300
#define 	SNICEUI_KEY_F12   301
#define 	SNICEUI_KEY_F13   302
#define 	SNICEUI_KEY_F14   303
#define 	SNICEUI_KEY_F15   304
#define 	SNICEUI_KEY_F16   305
#define 	SNICEUI_KEY_F17   306
#define 	SNICEUI_KEY_F18   307
#define 	SNICEUI_KEY_F19   308
#define 	SNICEUI_KEY_F20   309
#define 	SNICEUI_KEY_F21   310
#define 	SNICEUI_KEY_F22   311
#define 	SNICEUI_KEY_F23   312
#define 	SNICEUI_KEY_F24   313
#define 	SNICEUI_KEY_F25   314
#define 	SNICEUI_KEY_KP_0   320
#define 	SNICEUI_KEY_KP_1   321
#define 	SNICEUI_KEY_KP_2   322
#define 	SNICEUI_KEY_KP_3   323
#define 	SNICEUI_KEY_KP_4   324
#define 	SNICEUI_KEY_KP_5   325
#define 	SNICEUI_KEY_KP_6   326
#define 	SNICEUI_KEY_KP_7   327
#define 	SNICEUI_KEY_KP_8   328
#define 	SNICEUI_KEY_KP_9   329
#define 	SNICEUI_KEY_KP_DECIMAL   330
#define 	SNICEUI_KEY_KP_DIVIDE   331
#define 	SNICEUI_KEY_KP_MULTIPLY   332
#define 	SNICEUI_KEY_KP_SUBTRACT   333
#define 	SNICEUI_KEY_KP_ADD   334
#define 	SNICEUI_KEY_KP_ENTER   335
#define 	SNICEUI_KEY_KP_EQUAL   336
#define 	SNICEUI_KEY_LEFT_SHIFT   340
#define 	SNICEUI_KEY_LEFT_CONTROL   341
#define 	SNICEUI_KEY_LEFT_ALT   342
#define 	SNICEUI_KEY_LEFT_SUPER   343
#define 	SNICEUI_KEY_RIGHT_SHIFT   344
#define 	SNICEUI_KEY_RIGHT_CONTROL   345
#define 	SNICEUI_KEY_RIGHT_ALT   346
#define 	SNICEUI_KEY_RIGHT_SUPER   347
#define 	SNICEUI_KEY_MENU   348
#define 	SNICEUI_KEY_LAST   SNICEUI_KEY_MENU

/**	\brief define return minimal value  beetween X an Y*/
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
/**	\brief define return maximal value  beetween X an Y*/
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

#define PI 3.14159265358979323846
#define DEG2RAD(DEG)((DEG)*((PI)/(180.0)))

enum color {RED, GREEN, BLUE, ALPHA};
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
	void CharPressed(unsigned int character);

};


//GLvoid BuildFont(GLvoid);
//GLvoid KillFont(GLvoid);
int InitSniceUI();
//void DrawCursor();


#endif //_SNICE_UI_H_

// End of file snice_UI.h
