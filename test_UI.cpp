
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snice_UI.h"
#include "test_UI.h"
#include <GLFW/glfw3.h>

using namespace std;


/**	\brief lenth of a character in pixel.*/
//#define CHARLENGTH 7

/////////////////////////////////////////////
// General Variables
/////////////////////////////////////////////

//bool FastComputer; // Boolean for drawing shadows under objects

//Prefs* pPrefs;

//N_Container* pRootContainer;
//N_Container* pCurContainer;
Snice_UI* pSnice_UI;
Viewport* pViewport;
W_button* pValid;
W_button* pUnvalid;
W_button* ppouet;
W_button* progressToggle;
W_textbox* textbox;
W_slider* slider;
W_progress* progress;
W_colorSelectdisplay* color_display;

UI_window* pwind;
W_subMenu* submenu;
W_subMenu* submenu2;
W_menu* menu;

bool active = true;		// Window Active Flag Set To TRUE By Default
bool fullscreen = false;	// Fullscreen Flag Set To Not Fullscreen Mode By Default

GLFWwindow* my_window;

//Texture textures[20];	// Storage For Textures
//GLuint base;				// Base Display List For The Font
bool keys[320];			// Array Used For The Keyboard Routine


//////////////////////////////////////////////////
// List of functions.
// Main functions for SNICE program
//////////////////////////////////////////////////
void test(W_button* caller)
{
    caller->SetPressed(true);
};

void test2(W_button* caller)
{
    caller->SetPressed(false);
};

void test3(W_button* caller)
{
    caller->killMe = true;
};

void buttonHa(W_button* caller)
{
    progress->SetAction(!progress->GetAction());
};


void test4(W_button* caller)
{
    caller->SetPressed( !caller->IsPressed());
    textbox->SetWidth(150);
};
void testwin(UI_window* caller)
{
    pValid->SetName( "ca marche");
};

void viewport_resize(UI_base* caller, int w, int h)
{
    if(pValid) pValid->SetPosX(w-150);
};

void textboxContent(W_textbox* caller, string content)
{
    if(pValid) pValid->SetName( content);
};

void sliderValue(W_slider* caller, float value, bool realtime)
{
    if(textbox) textbox->SetPosX( (int)value);
};

void pickOption(W_subMenu* caller, unsigned char option)
{
    if((caller)&&(pValid)) pValid->SetName( caller->GetString());
};
//////////////////////////////////////////////////
// init(int argc, char *argv[]).
// Initialise the system and process special args
//////////////////////////////////////////////////
static void init(int argc, char * argv[])
{

	cout<<"ui_interface\n";
	cout<<"Copyleft 2014 by Sebastien Tricoire\n\n";

	// Process the special args
	for ( int i = 1; i < argc; ++i )
		{
		if ((strcmp(argv[i], "-info")==0) || (strcmp(argv[i], "-i")==0))
			{
			cout<<"GL_RENDERER   = "<< glGetString(GL_RENDERER)<<"\n";
			cout<<"GL_VERSION    = "<< glGetString(GL_VERSION)<<"\n";
			cout<<"GL_VENDOR     = "<< glGetString(GL_VENDOR)<<"\n";
			cout<<"GL_EXTENSIONS = "<< glGetString(GL_EXTENSIONS)<<"\n";
			}
		}

	// Set OpenGL and GLFW variables
    //glfwSetWindowTitle("TEST_UI");	// Set title
    //glfwEnable( GLFW_KEY_REPEAT );	// Authorise key repeat

    create_interface();

    glfwSwapInterval( 0 );			// Disable vertical sync (on cards that support it)
}

void create_interface()
{


    pSnice_UI = new Snice_UI(800,600,50);

    pViewport = pSnice_UI->GetViewport();
	//pViewport = new Viewport(0,0,640,480);
	pViewport->OnResize(viewport_resize);

    pwind = new UI_window(100, 350, 500, 250, "test");

	pViewport->AddChild(pwind);

	pwind->OnClose(testwin);

	progress = new W_progress(100,-90,150,20,"hihi");
	pwind->AddChild(progress);
	progress->SetAction(true);
	progress->SetSpeed(-0.1);

	pValid = new W_button(490,100, 120,20, "COOL");
	pViewport->AddChild(pValid);
	//pValid->OnMouseOver(test);
	//pValid->OnMouseOut(test2);
	pValid->OnClick(test4);

	pUnvalid = new W_button(250,-100, 120,20, "PAS COOL");
	pwind->AddChild(pUnvalid);
	pUnvalid->OnMouseOver(test2);
	pUnvalid->OnMouseOut(test);

	ppouet = new W_button(100,-110, 50,20, "Ha");
	pwind->AddChild(ppouet);
	ppouet->OnMouseOver(test3);

	progressToggle = new W_button(150,-110, 50,20, "toggle");
	pwind->AddChild(progressToggle);
	progressToggle->OnClick(buttonHa);

	textbox = new W_textbox(100,50, 150,20, "tutu","titi");
	pViewport->AddChild(textbox);
	textbox->OnSetContent(textboxContent);

	slider = new W_slider(100, -60, 150, 20, "Ha", 120, 100, 200, 0);
	pwind->AddChild(slider);
	slider->OnSetValue(sliderValue);
	//pViewport->AddChild(slider);

	submenu2 = new W_subMenu(100,10,100);
	submenu2->AddOption("aaaaa");
	submenu2->AddOption("bbbbb");
	submenu2->AddOption("ccccc");
	submenu2->OnPickOption(pickOption);

	submenu = new W_subMenu(200,100, 100);
    submenu->AddOption("ddddd");
	submenu->AddOption("eeeee", submenu2);
	submenu->AddOption("fffff");
	submenu->OnPickOption(pickOption);

	menu = new W_menu(110,100, 150,20, "menu");
	menu->AddOption("ggggg", submenu);
	menu->AddOption("hhhhh");
	menu->AddOption("iiiii");
	menu->OnPickOption(pickOption);
	pViewport->AddChild(menu);

    color_display = new W_colorSelectdisplay(400,300, 150,150,HUE,0.2, 0.5, 0.8);
	pViewport->AddChild(color_display);
}


////////////////////////////////////////
// InitGL(GLvoid).
// Initialise the OpenGL Library
////////////////////////////////////////
int InitGL()
{
    if(!InitSniceUI()){return false;};

	glShadeModel(GL_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glDisable(GL_DEPTH_TEST);					// Disables Depth Testing

	return true;
}

//////////////////////////////////////////////////
// ProcessReshape( int width, int height ).
// Process new window size
//////////////////////////////////////////////////
void ProcessReshape(GLFWwindow* wind, int width, int height )
{
	// Get window size (may be different than the requested size)
	glfwGetWindowSize(my_window, &width, &height );//glfwGetWindowSize( &width, &height );
	pSnice_UI->Resize(width, height);

}

//////////////////////////////////////////////////
// ProcessMouseButton( int button, int action ).
// Process Mouse Button
//////////////////////////////////////////////////
void ProcessMouseButton(GLFWwindow* wind, int button, int action, int mods)
{
    pSnice_UI->MouseButton(button, action );
}

//////////////////////////////////////////////////
// ProcessMousePos( int x, int y ).
// Process Mouse Position
//////////////////////////////////////////////////
void ProcessMousePos(GLFWwindow* wind, double x, double y)
{
    pSnice_UI->MouseMove(x,y);
}

//////////////////////////////////////////////////
// ProcessKey( int key, int action ).
// Process the keys from the keyboard
//////////////////////////////////////////////////
void ProcessKey(GLFWwindow* wind, int key, int scancode, int action, int mods)
{
    if( action == GLFW_RELEASE )
    {
		keys[key]=false;
        return;
    }
	keys[key]=(action == GLFW_PRESS);

	pSnice_UI->KeyPressed(key,action);
}

//////////////////////////////////////////////////
// ProcessChar( int key, int action ).
// Process the keys from the keyboard
//////////////////////////////////////////////////
void ProcessChar(GLFWwindow* wind,  unsigned int character )
{
    pSnice_UI->CharPressed(character);
}

//////////////////////////////////////////////////
// main(int argc, char *argv[]).
// Main function and program entry
//////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    // Init GLFW
    glfwInit();
    my_window = glfwCreateWindow(800, 600,"test_ui",NULL,NULL);

    	// Open a OpenGL window
	if (!my_window)
	{
		// if error -> exit
		printf("Error : impossible to open OpenGL window !");
		glfwTerminate();
		return 0;
	}
    glfwMakeContextCurrent(my_window);

	// Initialise the OpenGL stuff
	if (!InitGL())
	{
		printf("Error : Initialization Failed !");
        glfwTerminate();
        return 0;
	}
    // Initialise the system and process special args
    init(argc, argv);

    // Set callback functions
    glfwSetWindowSizeCallback( my_window, ProcessReshape );// Called in case the window size change
    //glfwSetFramebufferSizeCallback( my_window, ProcessReshape);
    glfwSetKeyCallback( my_window, ProcessKey );			// Called in case a keyboard key is pressed
	glfwSetCharCallback( my_window, ProcessChar );			// Called in case a keyboard key is pressed
	glfwSetMouseButtonCallback( my_window, ProcessMouseButton );	// Called in case a mouse button is pressed
	glfwSetCursorPosCallback( my_window, ProcessMousePos );			// Called in case the mouse is moved
	//glfwSetMousePosCallback( pSnice_UI->MouseMove );			// Called in case the mouse is moved

    // Main loop
    while ( !glfwWindowShouldClose(my_window ) )
	{
        pSnice_UI->Draw();

        glfwSwapBuffers(my_window);

        //process the events (keyboard, mouse,...)
        glfwPollEvents();

        //break;
	}
    // Close window and terminate GLFW
	if (pSnice_UI){delete pSnice_UI;pSnice_UI = NULL;}
    glfwDestroyWindow(my_window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    // Exit program
    return 0;
}

// end of snice.cpp
