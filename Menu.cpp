#include "Menu.hpp"

/*----------------------------------------------------------------------------------------
*	Global Variables
*/

/*
*	rename the structure from "struct Mouse" to just "Mouse"
*/
typedef struct Mouse Mouse;
/*
*	\brief witch menu is open
*	N = No Menu
*	M = Main Menu
*	L = Load-Menu
*	S = Save-Menu
*	H = Highscore
*/
char loadedMenu = 'N';

/*
*	Create a global mouse structure to hold the mouse information.
*/
Mouse TheMouse = { 0,0,0,0,0 };

/*
*	Variables to hold the current size of the window.
*/
int winw = ::GetSystemMetrics(SM_CXSCREEN);
int winh = ::GetSystemMetrics(SM_CYSCREEN);

/*----------------------------------------------------------------------------------------
*	Button Stuff
*/

/*
*	We will define a function pointer type. ButtonCallback is a pointer to a function that
*	looks a bit like this :
*
*	void func() {
*	}
*/
typedef void(*ButtonCallback)();
typedef struct Button Button;



/*----------------------------------------------------------------------------------------
*	Calls the continue-method to load the last played game
*/
void ContinueMainMenu(){
	printf("Continue the last played game\n");
}

/*----------------------------------------------------------------------------------------
*	Calls the method-to save the actual game.
*	Do nothing if no game loaded.
*/
void SaveMainMenu(){
	callSaveMenu();
}

/*----------------------------------------------------------------------------------------
*	Calls the method to choose a posible Save-Game and starts a new game.
*/
void NewMainMenu()
{
	printf("Start a new game\n");
}

/*----------------------------------------------------------------------------------------
*	Calls the mehtod to choose one of the Save-Games and loads it
*/
void LoadMainMenu()
{
	callLoadMenu();
}

/*----------------------------------------------------------------------------------------
*	Calls the method to show the Highscores
*/
void HighMainMenu()
{
	callHighscores();
}

/*----------------------------------------------------------------------------------------
*	Quits the Game. No save before!
*/
void ExitMainMenu()
{
	glutDestroyWindow(glutGetWindow());
	exit(0);
}

/*----------------------------------------------------------------------------------------
*	Cancels the action and calls the mainmenu
*/
void BackToMainMenu()
{
	callMainMenu();
}

/*
*	Calculates the width of the Button
*/
int calcW() {
	return ((winw / 100) * 10);
}

/*
*	Calculates the hight of the Button
*/
int calcH() {
	return ((winh / 100) * 10);
}

/*
*	Calculates the X-Coord for the Button
*/
int calcX() {
	return ((winw / 2) - (calcW() / 2));
}

/*
*	Calculates the Y-Coord for the Button
*	\param before		-	the y-coord of the button before
*/
int calcY(int before) {
	int basehight = 10;
	return ((winh / 100) * 10) + basehight + before;
}

/*
*	Method for Save
*	\param saveslot		-	number of the saveslot
*/
void save(int saveslot) {
	cout << "Save in slot " << saveslot << "\n";
}

/*
*	Calls the saveMethod for the first button
*/
void save1() {
	save(1);
}

/*
*	Calls the saveMethod for the second button
*/
void save2() {
	save(2);
}

/*
*	Calls the saveMethod for the third button
*/
void save3() {
	save(3);
}

/*
*	Method for load a game
*	\param saveslot		-	number of the saveslot
*/
void load(int saveslot) {
	cout << "Load save from slot " << saveslot << "\n";
}

/*
*	Calls the loadMethod for the first button
*/
void load1() {
	load(1);
}

/*
*	Calls the laodMethod for the second button
*/
void load2() {
	load(2);
}

/*
*	Calls the laodMethod for the third button
*/
void load3() {
	load(3);
}

/*----------------------------------------------------------------------------------------
*	Buttons for the Main-Menu
*/
Button ContinueBtn = { calcX(), calcY(0), calcW(), calcH(), 0,0, (char*)"Continue", ContinueMainMenu };
Button NewBtn = { calcX(), calcY(ContinueBtn.y), calcW(), calcH(), 0,0, (char*)"New", NewMainMenu };
Button SaveBtn = { calcX(), calcY(NewBtn.y), calcW(), calcH(), 0,0, (char*)"Save", SaveMainMenu };
Button LoadBtn = { calcX(), calcY(SaveBtn.y), calcW(), calcH(), 0,0, (char*)"Load", LoadMainMenu };
Button HighBtn = { calcX(), calcY(LoadBtn.y), calcW(), calcH(), 0,0, (char*)"Highscore", HighMainMenu };
Button ExitBtn = { calcX(), calcY(HighBtn.y), calcW(), calcH(), 0,0, (char*)"Exit", ExitMainMenu };

/*----------------------------------------------------------------------------------------
*	Buttons for the Save-Menu
*/
Button Save1 = { (((winw / 100) * 33) + 10 + 0), (winh / 2), calcW(), calcH(), 0,0, (char*)"Save 1", save1 };
Button Save2 = { (Save1.w + Save1.x + ((winw / 100) * 3)), (winh / 2), calcW(), calcH(), 0,0, (char*)"Save 2", save2 };
Button Save3 = { (Save2.w + Save2.x + ((winw / 100) * 3)), (winh / 2), calcW(), calcH(), 0,0, (char*)"Save 3", save3 };
Button CancelSave = { calcX(), (winh-((winw / 100) * 10)), calcW(), calcH(), 0,0, (char*)"Cancel", BackToMainMenu };

/*----------------------------------------------------------------------------------------
*	Buttons for the Load-Menu
*/
Button Load1 = { (((winw / 100) * 33) + 10 + 0), (winh / 2), calcW(), calcH(), 0,0, (char*)"Load 1", load1 };
Button Load2 = { (Load1.w + Load1.x + ((winw / 100) * 3)), (winh / 2), calcW(), calcH(), 0,0, (char*)"Load 2", load2 };
Button Load3 = { (Load2.w + Load2.x + ((winw / 100) * 3)), (winh / 2), calcW(), calcH(), 0,0, (char*)"Load 3", load3 };
Button CancelLoad = { calcX(), (winh - ((winw / 100) * 10)), calcW(), calcH(), 0,0, (char*)"Cancel", BackToMainMenu };

/*----------------------------------------------------------------------------------------
*	Buttons for the Highscore-Menu
*/
Button CancelHighscore = { calcX(), (winh - ((winw / 100) * 10)), calcW(), calcH(), 0,0, (char*)"Back", BackToMainMenu };


/*----------------------------------------------------------------------------------------
*	\brief	This function draws a text string to the screen using glut bitmap fonts.
*	\param	font	-	the font to use. it can be one of the following :
*					GLUT_BITMAP_9_BY_15
*					GLUT_BITMAP_8_BY_13
*					GLUT_BITMAP_TIMES_ROMAN_10
*					GLUT_BITMAP_TIMES_ROMAN_24
*					GLUT_BITMAP_HELVETICA_10
*					GLUT_BITMAP_HELVETICA_12
*					GLUT_BITMAP_HELVETICA_18
*
*	\param	text	-	the text string to output
*	\param	x		-	the x co-ordinate
*	\param	y		-	the y co-ordinate
*/
void Font(void *font, char *text, int x, int y)
{
	glRasterPos2i(x, y);

	while (*text != '\0')
	{
		glutBitmapCharacter(font, *text);
		++text;
	}
}


/*----------------------------------------------------------------------------------------
*	\brief	This function is used to see if a mouse click or event is within a button
*			client area.
*	\param	b	-	a pointer to the button to test
*	\param	x	-	the x coord to test
*	\param	y	-	the y-coord to test
*/
int ButtonClickTest(Button* b, int x, int y)
{
	if (b)
	{
		/*
		*	If clicked within button area, then return true
		*/
		if (x > b->x      &&
			x < b->x + b->w &&
			y > b->y      &&
			y < b->y + b->h) {
			return 1;
		}
	}

	/*
	*	otherwise false.
	*/
	return 0;
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void ButtonRelease(Button *b, int x, int y)
{
	if (b)
	{
		/*
		*	If the mouse button was pressed within the button area
		*	as well as being released on the button.....
		*/
		if (ButtonClickTest(b, x, y))
			//&& ButtonClickTest(b, TheMouse.xpress, TheMouse.ypress))	<-- funktioniert nicht immer
		{
			/*
			*	Then if a callback function has been set, call it.
			*/
			if (b->callbackFunction) {
				b->callbackFunction();
			}
		}

		/*
		*	Set state back to zero.
		*/
		b->state = 0;
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void ButtonPress(Button *b, int x, int y)
{
	if (b)
	{
		/*
		*	if the mouse click was within the buttons client area,
		*	set the state to true.
		*/
		if (ButtonClickTest(b, x, y))
		{
			b->state = 1;
		}
	}
}


/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void ButtonPassive(Button *b, int x, int y)
{
	if (b)
	{
		/*
		*	if the mouse moved over the control
		*/
		if (ButtonClickTest(b, x, y))
		{
			/*
			*	If the cursor has just arrived over the control, set the highlighted flag
			*	and force a redraw. The screen will not be redrawn again until the mouse
			*	is no longer over this control
			*/
			if (b->highlighted == 0) {
				b->highlighted = 1;
				glutPostRedisplay();
			}
		}
		else

			/*
			*	If the cursor is no longer over the control, then if the control
			*	is highlighted (ie, the mouse has JUST moved off the control) then
			*	we set the highlighting back to false, and force a redraw.
			*/
			if (b->highlighted == 1)
			{
				b->highlighted = 0;
				glutPostRedisplay();
			}
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to draw.
*/
void ButtonDraw(Button *b)
{
	int fontx;
	int fonty;

	if (b)
	{
		/*
		*	We will indicate that the mouse cursor is over the button by changing its
		*	colour.
		*/
		if (b->highlighted)
			glColor3f(0.7f, 0.7f, 0.8f);
		else
			glColor3f(0.6f, 0.6f, 0.6f);

		/*
		*	draw background for the button.
		*/
		glBegin(GL_QUADS);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		/*
		*	Draw an outline around the button with width 3
		*/
		glLineWidth(3);

		/*
		*	The colours for the outline are reversed when the button.
		*/
		if (b->state)
			glColor3f(0.4f, 0.4f, 0.4f);
		else
			glColor3f(0.8f, 0.8f, 0.8f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x + b->w, b->y);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glEnd();

		if (b->state)
			glColor3f(0.8f, 0.8f, 0.8f);
		else
			glColor3f(0.4f, 0.4f, 0.4f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		glLineWidth(1);


		/*
		*	Calculate the x and y coords for the text string in order to center it.
		*/
		fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char *)b->label)) / 2;
		fonty = b->y + (b->h + 10) / 2;

		/*
		*	if the button is pressed, make it look as though the string has been pushed
		*	down. It's just a visual thing to help with the overall look....
		*/
		if (b->state) {
			fontx += 2;
			fonty += 2;
		}

		/*
		*	If the cursor is currently over the button we offset the text string and draw a shadow
		*/
		if (b->highlighted)
		{
			glColor3f(0, 0, 0);
			Font(GLUT_BITMAP_HELVETICA_12, b->label, fontx, fonty);
			fontx--;
			fonty--;
		}

		glColor3f(1, 1, 1);
		Font(GLUT_BITMAP_HELVETICA_12, b->label, fontx, fonty);
	}
}

/*----------------------------------------------------------------------------------------
*	This function will be used to draw the 3D scene
*/
void Draw3D()
{
	gluLookAt(0, 1, 5, 0, 0, 0, 0, 1, 0);
	glutSolidTeapot(1);
}

/*----------------------------------------------------------------------------------------
*	This function will be used to draw an overlay over the 3D scene.
*	This will be used to draw our fonts, buttons etc......
*/
void Draw2D()
{
	switch (loadedMenu) {
		case 'M':
			ButtonDraw(&ContinueBtn);
			ButtonDraw(&NewBtn);
			ButtonDraw(&SaveBtn);
			ButtonDraw(&LoadBtn);
			ButtonDraw(&HighBtn);
			ButtonDraw(&ExitBtn);
			break;
		case 'L':
			ButtonDraw(&Load1);
			ButtonDraw(&Load2);
			ButtonDraw(&Load3);
			ButtonDraw(&CancelLoad);
			break;
		case 'S':
			ButtonDraw(&Save1);
			ButtonDraw(&Save2);
			ButtonDraw(&Save3);
			ButtonDraw(&CancelSave);
			break;
		case 'H':
			ButtonDraw(&CancelHighscore);
			break;
	}
}

/*----------------------------------------------------------------------------------------
*	This is the main display callback function. It sets up the drawing for
*	The 3D scene first then calls the Draw3D() function. After that it switches to
*	an orthographic projection and calls Draw2D().
*/
void Draw(){
	/*
	*	Clear the background
	*/
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);

	/*
	*	Enable lighting and the z-buffer
	*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	/*
	*	Set perspective viewing transformation
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (winh == 0) ? (1) : ((float)winw / winh), 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	*	Draw the 3D elements in the scene
	*/
	//Draw3D();

	/*
	*	Disable depth test and lighting for 2D elements
	*/
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	/*
	*	Set the orthographic viewing transformation
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winw, winh, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	*	Draw the 2D overlay
	*/
	Draw2D();

	/*
	*	Bring the back buffer to the front and vice-versa.
	*/
	glutSwapBuffers();
}


/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever a mouse button is pressed or released
*	\param	button	-	GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, or GLUT_MIDDLE_BUTTON
*	\param	state	-	GLUT_UP or GLUT_DOWN depending on whether the mouse was released
*						or pressed respectivly.
*	\param	x		-	the x-coord of the mouse cursor.
*	\param	y		-	the y-coord of the mouse cursor.
*/
void MouseButton(int button, int state, int x, int y)
{
	if (loadedMenu != 'N') {
		/*
		*	update the mouse position
		*/
		TheMouse.x = x;
		TheMouse.y = y;

		/*
		*	has the button been pressed or released?
		*/
		if (state == GLUT_DOWN)
		{
			/*
			*	This holds the location of the first mouse click
			*/
			if (!(TheMouse.lmb || TheMouse.mmb || TheMouse.rmb)) {
				TheMouse.xpress = x;
				TheMouse.ypress = y;
			}

			/*
			*	Which button was pressed?
			*/
			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				TheMouse.lmb = 1;
				switch(loadedMenu) {
					case 'M':
						ButtonPress(&ContinueBtn, x, y);
						ButtonPress(&NewBtn, x, y);
						ButtonPress(&SaveBtn, x, y);
						ButtonPress(&LoadBtn, x, y);
						ButtonPress(&HighBtn, x, y);
						ButtonPress(&ExitBtn, x, y);
						break;
					case 'L':
						ButtonPress(&Load1, x, y);
						ButtonPress(&Load2, x, y);
						ButtonPress(&Load3, x, y);
						ButtonPress(&CancelLoad, x, y);
						break;
					case 'S':
						ButtonPress(&Save1, x, y);
						ButtonPress(&Save2, x, y);
						ButtonPress(&Save3, x, y);
						ButtonPress(&CancelSave, x, y);
						break;
					case 'H':
						ButtonPress(&CancelHighscore, x, y);
						break;
				}
			case GLUT_MIDDLE_BUTTON:
				TheMouse.mmb = 1;
				break;
			case GLUT_RIGHT_BUTTON:
				TheMouse.rmb = 1;
				break;
			}
		}
		else
		{
			/*
			*	Which button was released?
			*/
			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				TheMouse.lmb = 0;
				switch (loadedMenu) {
					case 'M':
						ButtonRelease(&ContinueBtn, x, y);
						ButtonRelease(&NewBtn, x, y);
						ButtonRelease(&SaveBtn, x, y);
						ButtonRelease(&LoadBtn, x, y);
						ButtonRelease(&HighBtn, x, y);
						ButtonRelease(&ExitBtn, x, y);
						break;
					case 'L':
						ButtonRelease(&Load1, x, y);
						ButtonRelease(&Load2, x, y);
						ButtonRelease(&Load3, x, y);
						ButtonRelease(&CancelLoad, x, y);
						break;
					case 'S':
						ButtonRelease(&Save1, x, y);
						ButtonRelease(&Save2, x, y);
						ButtonRelease(&Save3, x, y);
						ButtonRelease(&CancelSave, x, y);
						break;
					case 'H':
						ButtonRelease(&CancelHighscore, x, y);
						break;
				}
				break;
			case GLUT_MIDDLE_BUTTON:
				TheMouse.mmb = 0;
				break;
			case GLUT_RIGHT_BUTTON:
				TheMouse.rmb = 0;
				break;
			}
		}
	}
	
	/*
	*	Force a redraw of the screen. If we later want interactions with the mouse
	*	and the 3D scene, we will need to redraw the changes.
	*/
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever the mouse cursor is moved AND A BUTTON IS HELD.
*	\param	x	-	the new x-coord of the mouse cursor.
*	\param	y	-	the new y-coord of the mouse cursor.
*/
void MouseMotion(int x, int y)
{
	if (loadedMenu != 'N') {
		/*
		*	Calculate how much the mouse actually moved
		*/
		int dx = x - TheMouse.x;
		int dy = y - TheMouse.y;

		/*
		*	update the mouse position
		*/
		TheMouse.x = x;
		TheMouse.y = y;


		/*
		*	Check MyButton to see if we should highlight it cos the mouse is over it
		*/
		switch (loadedMenu) {
		case 'M':
			ButtonPassive(&ContinueBtn, x, y);
			ButtonPassive(&NewBtn, x, y);
			ButtonPassive(&SaveBtn, x, y);
			ButtonPassive(&LoadBtn, x, y);
			ButtonPassive(&HighBtn, x, y);
			ButtonPassive(&ExitBtn, x, y);
			break;
		case 'S':
			ButtonPassive(&Save1, x, y);
			ButtonPassive(&Save2, x, y);
			ButtonPassive(&Save3, x, y);
			ButtonPassive(&CancelSave, x, y);
			break;
		case 'L':
			ButtonPassive(&Load1, x, y);
			ButtonPassive(&Load2, x, y);
			ButtonPassive(&Load3, x, y);
			ButtonPassive(&CancelLoad, x, y);
			break;
		case 'H':
			ButtonPassive(&CancelHighscore, x, y);
			break;
		}

		/*
		*	Force a redraw of the screen
		*/
		glutPostRedisplay();
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever the mouse cursor is moved AND NO BUTTONS ARE HELD.
*	\param	x	-	the new x-coord of the mouse cursor.
*	\param	y	-	the new y-coord of the mouse cursor.
*/
void MousePassiveMotion(int x, int y)
{
	if (loadedMenu != 'N') {
		/*
		*	Calculate how much the mouse actually moved
		*/
		int dx = x - TheMouse.x;
		int dy = y - TheMouse.y;

		/*
		*	update the mouse position
		*/
		TheMouse.x = x;
		TheMouse.y = y;

		/*
		*	Check MyButton to see if we should highlight it cos the mouse is over it
		*/
		switch (loadedMenu) {
		case 'M':
			ButtonPassive(&ContinueBtn, x, y);
			ButtonPassive(&NewBtn, x, y);
			ButtonPassive(&SaveBtn, x, y);
			ButtonPassive(&LoadBtn, x, y);
			ButtonPassive(&HighBtn, x, y);
			ButtonPassive(&ExitBtn, x, y);
			break;
		case 'S':
			ButtonPassive(&Save1, x, y);
			ButtonPassive(&Save2, x, y);
			ButtonPassive(&Save3, x, y);
			ButtonPassive(&CancelSave, x, y);
			break;
		case 'L':
			ButtonPassive(&Load1, x, y);
			ButtonPassive(&Load2, x, y);
			ButtonPassive(&Load3, x, y);
			ButtonPassive(&CancelLoad, x, y);
			break;
		case 'H':
			ButtonPassive(&CancelHighscore, x, y);
			break;
		}

		/*
		*	Note that I'm not using a glutPostRedisplay() call here. The passive motion function
		*	is called at a very high frequency. We really don't want much processing to occur here.
		*	Redrawing the screen every time the mouse moves is a bit excessive. Later on we
		*	will look at a way to solve this problem and force a redraw only when needed.
		*/
	}
}

/*----------------------------------------------------------------------------------------
*
*/
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(1.0, 0.0, 0.0, 1.0);//clear red
	glutSwapBuffers();
}

bool closeMainMenu() {
	if (loadedMenu == 'M'){
		loadedMenu = 'N';
		glewInit();
		glutDisplayFunc(renderScene);
		glutPostRedisplay();
		return false;
	}
	else {
		return true;
	}
}

void callMenu() {
	if (loadedMenu != 'N') {
		glutDisplayFunc(Draw);
		glutMouseFunc(MouseButton);
		glutMotionFunc(MouseMotion);
		glutPassiveMotionFunc(MousePassiveMotion);
		/*
		*	Force a redraw of the screen
		*	else the menu will shown at a mouseclick
		*/
		glutPostRedisplay();
	}
}

void closeSubMenu() {
	loadedMenu = 'M';
	callMenu();
}

bool callMainMenu() {
	if (loadedMenu != 'M') {
		loadedMenu = 'M';
		callMenu();
		return true;
	}
	else {
		return false;
	}
	
}

void callLoadMenu() {
	loadedMenu = 'L';
	callMenu();
}

void callSaveMenu() {
	loadedMenu = 'S';
	callMenu();
}

void callHighscores() {
	loadedMenu = 'H';
	callMenu();
}
