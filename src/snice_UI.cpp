

#include "snice_UI.h"
#include "include/glfw.h"

Snice_UI::Snice_UI(int w, int h, unsigned char fps)
{
    width = w;
    height = h;
    viewport = new Viewport(0,0,width,height);
    spf = 1/(double)fps;

}

Snice_UI::~Snice_UI()
{
    if (viewport){delete viewport;};
}

void Snice_UI::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
	viewport->Draw();
	/*
    t = glfwGetTime();
    glfwSleep(spf - (t - t0 ));
    t0 = glfwGetTime();
    */
}

Viewport* Snice_UI::GetViewport()
{
    return viewport;
}

void Snice_UI::Resize( int w, int h )
{
    width = w;
    height = h;
    if (height==0){ height=1; }// Prevent A Divide By Zero
	viewport->Resize(0,0,width,height);
}

void Snice_UI::MouseMove( int x, int y )
{
    y = height-y;
	viewport->OnMouseMove(x, y, mouseX, mouseY);
    mouseX = x;
    mouseY = y;
}

void Snice_UI::MouseButton( int button, int action )
{
	// if mouse button is pressed
    if (action == SNICEUI_PRESS )
	{
		switch (button)
		{
			// Left mouse button is pressed
			case SNICEUI_MOUSE_BUTTON_LEFT:
				viewport->OnLButtonDown(mouseX, mouseY);
				break;

			// Right mouse button is pressed
			case SNICEUI_MOUSE_BUTTON_RIGHT:
				viewport->OnRButtonDown(mouseX, mouseY);
				break;
		}
	}
	// If mouse button is released
	else
	{
		switch (button)
		{
			// Left mouse button is released
			case SNICEUI_MOUSE_BUTTON_LEFT:
				viewport->OnLButtonUp(mouseX, mouseY);
				break;

			// Right mouse button is released
			case SNICEUI_MOUSE_BUTTON_RIGHT:
				viewport->OnRButtonUp(mouseX, mouseY);
				break;
		}

	}

}


void Snice_UI::KeyPressed( int button, int action)
{
    viewport->OnKeyPressed(button);
}

void Snice_UI::CharPressed( int character, int action)
{
    if( action == SNICEUI_PRESS )
	{
		viewport->OnCharPressed(character);
	}
}

Texture textures[20];	// Storage For Textures
GLuint base;				// Base Display List For The Font

//////////////////////////////////////////////////
// BuildFont(GLvoid).
// Build Our Font Display List
//////////////////////////////////////////////////
/*
GLvoid BuildFont(GLvoid)									// Build Our Font Display List
{
	base=glGenLists(256);									// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, textures[0].texID);		// Select Our Font Texture
	for (int loop1=0; loop1<256; ++loop1)					// Loop Through All 256 Lists
	{
		float cx = float(loop1%16)/16.0f;					// X Position Of Current Character
		float cy = float(loop1/16)/16.0f;					// Y Position Of Current Character


		glNewList(base+loop1,GL_COMPILE);					// Start Building A List
			glBegin(GL_QUADS);								// Use A Quad For Each Character
				glTexCoord2f(cx,1.0f-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2d(0,16);							// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,16);							// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);	// Texture Coord (Top Right)
				glVertex2i(16,0);							// Vertex Coord (Top Right)
				glTexCoord2f(cx,1.0f-cy-0.001f);			// Texture Coord (Top Left)
				glVertex2i(0,0);							// Vertex Coord (Top Left)
			glEnd();										// Done Building Our Quad (Character)
			glTranslated(CHARLENGTH,0,0);					// Move To The Right Of The Character
		glEndList();										// Done Building The Display List
	}														// Loop Until All 256 Are Built
}*/

//////////////////////////////////////////////////
// KillFont(GLvoid).
// Delete The Font From Memory
//////////////////////////////////////////////////
/*GLvoid KillFont(GLvoid)									// Delete The Font From Memory
{
	glDeleteLists(base,256);							// Delete All 256 Display Lists
}*/

////////////////////////////////////////
// InitSniceUI(GLvoid).
// Initialise the OpenGL Library
////////////////////////////////////////
int InitSniceUI()
{
    /*
	//if (!LoadTGA(&textures[0],"Data/Fontanti.tga"))			{return false;}
	if (!LoadTGA(&textures[1],"Data/shadow.tga"))			{return false;}
//	if (!LoadTGA(&textures[2],"Data/input.tga"))			{return false;}
//	if (!LoadTGA(&textures[3],"Data/output.tga"))			{return false;}
//	if (!LoadTGA(&textures[4],"Data/inputtriangle.tga"))	{return false;}
//	if (!LoadTGA(&textures[5],"Data/outputtriangle.tga"))	{return false;}
//	if (!LoadTGA(&textures[6],"Data/inputsquare.tga"))		{return false;}
//	if (!LoadTGA(&textures[7],"Data/outputsquare.tga"))		{return false;}

//	if (!LoadTGA(&textures[8],"Data/slider.tga"))			{return false;}
//	if (!LoadTGA(&textures[9],"Data/buttons.tga"))			{return false;}
//	if (!LoadTGA(&textures[10],"Data/specularbig.tga"))		{return false;}
	if (!LoadTGA(&textures[11],"Data/progress.tga"))		{return false;}
	if (!LoadTGA(&textures[12],"Data/cursor.tga"))			{return false;}
//	if (!LoadTGA(&textures[13],"Data/butpress.tga"))		{return false;}
*/
/*	if (!LoadTGA(&textures[14],"Data/inputImg.tga"))		{return false;}
	if (!LoadTGA(&textures[15],"Data/outputImg.tga"))		{return false;}
	if (!LoadTGA(&textures[16],"Data/inputAlpha.tga"))		{return false;}
	if (!LoadTGA(&textures[17],"Data/outputAlpha.tga"))		{return false;}
	if (!LoadTGA(&textures[18],"Data/inputMatrix.tga"))		{return false;}
	if (!LoadTGA(&textures[19],"Data/outputMatrix.tga"))	{return false;}
*/
	//ATTENTION mettre a jour la taille du tableau de texture quand on en rajoute
	//CAUTION don't forget to increase the texture array's size when you add new texture
/*
	for (int loop=0; loop<20; ++loop)						// Loop Through Both Textures
	{
		// Typical Texture Generation Using Data From The TGA ( CHANGE )
		glGenTextures(1, &textures[loop].texID);				// Create The Texture
		glBindTexture(GL_TEXTURE_2D, textures[loop].texID);

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		if (loop == 10 || loop == 11)
		{
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[loop].width, textures[loop].height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[loop].imageData);

		if (textures[loop].imageData)						// If Texture Image Exists
		{
			free(textures[loop].imageData);					// Free The Texture Image Memory
		}
	}
	*/
	UI_base::InitTextures();
	// Built the System font
	//BuildFont();

	return true;
}

////////////////////////////////////////
// DrawCursor().
// Draw the cursor
////////////////////////////////////////
void DrawCursor()
{
	// color the cursor
	// glColor4f(1.0f,0.9f,0.6f,1.0f);

	// glColor4f(1.0f,1.0f,1.0f,1.0f);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// if dragging, change the shape of the cursor
	//if(NodalView->bConnecting) glBindTexture(GL_TEXTURE_2D, textures[2*pConnectionStartNode->GetOutputType(iConnectionStartOutputNumber)+1].texID);
	// otherwise display the normal cursor
	// else glBindTexture(GL_TEXTURE_2D, textures[4].texID);
	//else glBindTexture(GL_TEXTURE_2D, textures[12].texID);
	glBindTexture(GL_TEXTURE_2D, textures[12].texID);

	// if it's over a compatible input, fit the cursor in the input
	// int cursorsize = 6;
	/*int cursorsize = 8;

	// draw the cursor
	glTranslated(iMousePosx, iMousePosy, 0);

	glBegin(GL_QUADS);
	if (NodalView->bConnecting)
	{
		cursorsize = 6;

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex2d(-cursorsize*1.5f,cursorsize);
			glTexCoord2f(1.0f,0.0f);
			glVertex2d(cursorsize*0.5f,cursorsize);
			glTexCoord2f(1.0f,1.0f);
			glVertex2d(cursorsize*0.5f,-cursorsize);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2d(-cursorsize*1.5f,-cursorsize);
		glEnd();
	}

	else
	{
		glColor4f(1.0f,1.0f,1.0f,1.0f);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f);
			glVertex2d(0,0);
			glTexCoord2f(1.0f,1.0f);
			glVertex2d(cursorsize*2,0);
			glTexCoord2f(1.0f,0.0f);
			glVertex2d(cursorsize*2,-cursorsize*2);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2d(0,-cursorsize*2);
		glEnd();
	}

	// glRotatef(-rotation,0.0f,0.0f,1.0f);
	glTranslated(-iMousePosx, -iMousePosy, 0);
*/
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
