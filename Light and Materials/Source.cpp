#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include <gl/glew.h>
#include <gl/glut.h>
#include <GL/GL.h> 
#pragma comment(lib, "glew32.lib")

using namespace std;

// Inital angle
GLfloat angle = 0.0;
// 20 miliseconds for update.
int updateInterval = 20;
// Ambient material
GLfloat material_Ka[4] = { 0.0, 0, 0, 0 };
// Diffuse material
GLfloat material_Kd[4] = { 0.7, 0.7, 0.7, 1.0 };
// Specular material
GLfloat material_Ks[4] = { 0.7, 0.7, 0.7, 1.0 };
// Emissive material
GLfloat material_Ke[4] = { 0.0, 0.0, 0.0, 0.0 };
// Specular light
GLfloat light_Ks[4] = { 0.7, 0.7, 0.7, 1.0 };
// Ambient light
GLfloat light_Ka[4] = { 0.0, 0.0, 0.0, 1.0 };
// Diffuse light
GLfloat light_Kd[4] = { 0.3, 0.3, 0.3, 1.0 };
// Set shininess
GLfloat mShininess[1] = { 64 };
// Set string texts
string mSText, lKa0Text, lKa1Text, lKa2Text, lKd0Text, lKd1Text, lKd2Text, lKs0Text, lKs1Text, lKs2Text;
string iText, mKa0Text, mKa1Text, mKa2Text, mKd0Text, mKd1Text, mKd2Text, mKs0Text, mKs1Text, mKs2Text, mKe0Text, mKe1Text, mKe2Text;
// Set parameter position
int i = 0;
// Set leftTextPos and rightTextPos
int leftTextPos, rightTextPos;
// Event switch
bool lA = false, lD = false, lS = false;
bool mA = false, mD = false, mS = false, mE = false;

// draw text function
void drawText(string text, int x, int y) {
	glWindowPos2d(x, y);
	// display each letter by using bitmap
	for (int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text.data()[i]);
	}
}
// Light function
void light(void) {
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
}
// Initialization
void init(void) {
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// Light rendering
	light();
	// Materials rendering
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
}
// Display function
void display(void) {
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -5);
	// Set rotation
	glRotatef(angle, 1, 1, 1);
	// Glut teapot size is 1.5
	glutSolidTeapot(1.5);
	glColor3f(0.0, 1.0, 0.0);
	// Draw shininess text
	drawText("The shininess is: " + mSText, leftTextPos, 750);
	// Draw light text
	drawText("Light Ambient is: Ka = { " + lKa0Text + ", " + lKa1Text + ", " + lKa2Text + " }", leftTextPos, 730);
	drawText("Light Diffuse is: Kd = { " + lKd0Text + ", " + lKd1Text + ", " + lKd2Text + " }", leftTextPos, 710);
	drawText("Light Specular is: Ks = { " + lKs0Text + ", " + lKs1Text + ", " + lKs2Text + " }", leftTextPos, 690);
	// Draw material text
	drawText("Material Ambient is: Ka = { " + mKa0Text + ", " + mKa1Text + ", " + mKa2Text + " }", leftTextPos, 670);
	drawText("Material Diffuse is: Kd = { " + mKd0Text + ", " + mKd1Text + ", " + mKd2Text + " }", leftTextPos, 650);
	drawText("Material Specular is: Ks = { " + mKs0Text + ", " + mKs1Text + ", " + mKs2Text + " }", leftTextPos, 630);
	drawText("Material Emissive is: Ke = { " + mKe0Text + ", " + mKe1Text + ", " + mKe2Text + " }", leftTextPos, 610);
	// Parameter position
	glColor3f(1.0, 1.0, 0.0);
	drawText("Parameter position is: " + iText, rightTextPos, 690);
	glColor3f(0.0, 1.0, 0.0);
	// Show current parameter position
	drawText("Current Selection is: ", rightTextPos, 750);
	// Show instructions
	glColor3f(1.0, 0.0, 0.0);
	drawText("WELCOME TO ZELIN'S PROGRAM!", leftTextPos, 150);
	drawText("For modifying values, please right click on the screen and make a selection.", leftTextPos, 110);
	drawText("UP/DOWN can change values for parameters, while LEFT/RIGHT represents the positions of parameters.", leftTextPos, 90);
	drawText("version 1.0.1", 1080, 5);
	glColor3f(1.0, 0.0, 1.0);
	// Event choose
	if (lA) {
		drawText("Light Ambient is: Ka = { " + lKa0Text + ", " + lKa1Text + ", " + lKa2Text + " }", rightTextPos, 710);
	}
	else if (lS) {
		drawText("Light Specular is: Ks = { " + lKs0Text + ", " + lKs1Text + ", " + lKs2Text + " }", rightTextPos, 710);
	}
	else if (lD) {
		drawText("Light Diffuse is: Kd = { " + lKd0Text + ", " + lKd1Text + ", " + lKd2Text + " }", rightTextPos, 710);
	}
	else if (mA) {
		drawText("Material Ambient is: Ka = { " + mKa0Text + ", " + mKa1Text + ", " + mKa2Text + " }", rightTextPos, 710);
	}
	else if (mD) {
		drawText("Material Diffuse is: Kd = { " + mKd0Text + ", " + mKd1Text + ", " + mKd2Text + " }", rightTextPos, 710);
	}
	else if (mS) {
		drawText("Material Specular is: Ks = { " + mKs0Text + ", " + mKs1Text + ", " + mKs2Text + " }", rightTextPos, 710);
	}
	else if (mE) {
		drawText("Material Emissive is: Ke = { " + mKe0Text + ", " + mKe1Text + ", " + mKe2Text + " }", rightTextPos, 710);
	}
	// Don't wait
	glFlush();
	// Swap buffers
	glutSwapBuffers();
}
// Reshape function
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
// Keyboard function
void keyboard(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		// Logic control
		if (mA == true) {
			material_Ka[i] += 0.10;
			if (material_Ka[i] >= 1) {
				material_Ka[i] = 1;
			}
		}
		else if (mD == true) {
			material_Kd[i] += 0.10;
			if (material_Kd[i] >= 1) {
				material_Kd[i] = 1;
			}
		}
		else if (mS == true) {
			material_Ks[i] += 0.10;
			if (material_Ks[i] >= 1) {
				material_Ks[i] = 1;
			}
		}
		else if (mE == true) {
			material_Ke[i] += 0.10;
			if (material_Ke[i] >= 1) {
				material_Ke[i] = 1;
			}
		}
		else if (lA == true) {
			light_Ka[i] += 0.10;
			if (light_Ka[i] >= 1) {
				light_Ka[i] = 1;
			}
		}
		else if (lD == true) {
			light_Kd[i] += 0.10;
			if (light_Kd[i] >= 1) {
				light_Kd[i] = 1;
			}
		}
		else if (lS == true) {
			light_Ks[i] += 0.10;
			if (light_Ks[i] >= 1) {
				light_Ks[i] = 1;
			}
		}
		break;
	case GLUT_KEY_DOWN:
		// Logic control
		if (mA == true) {
			material_Ka[i] -= 0.10;
			if (material_Ka[i] < 0.1) {
				material_Ka[i] = 0;
			}
		}
		else if (mD == true) {
			material_Kd[i] -= 0.10;
			if (material_Kd[i] < 0.1) {
				material_Kd[i] = 0;
			}
		}
		else if (mS == true) {
			material_Ks[i] -= 0.10;
			if (material_Ks[i] < 0.1) {
				material_Ks[i] = 0;
			}
		}
		else if (mE == true) {
			material_Ke[i] -= 0.10;
			if (material_Ke[i] < 0.1) {
				material_Ke[i] = 0;
			}
		}
		else if (lA == true) {
			light_Ka[i] -= 0.10;
			if (light_Ka[i] < 0.1) {
				light_Ka[i] = 0;
			}
		}
		else if (lD == true) {
			light_Kd[i] -= 0.10;
			if (light_Kd[i] < 0.1) {
				light_Kd[i] = 0;
			}
		}
		else if (lS == true) {
			light_Ks[i] -= 0.10;
			if (light_Ks[i] < 0.1) {
				light_Ks[i] = 0;
			}
		}
		break;
	case GLUT_KEY_LEFT:
		// Position control
		i -= 1;
		if (i <= 0) {
			i = 0;
		}
		break;
	case GLUT_KEY_RIGHT:
		// Position control
		i += 1;
		if (i >= 2) {
			i = 2;
		}
		break;
	}
}
// file menu Function
void lightMenuFunc(int id)
{
	// switch files
	switch (id)
	{
	case 1:
		lA = true;
		lS = false;
		lD = false;
		mA = false;
		mD = false;
		mS = false;
		mE = false;
		break;
	case 2:
		lS = true;
		lA = false;
		lD = false;
		mA = false;
		mD = false;
		mS = false;
		mE = false;
		break;
	case 3:
		lD = true;
		lA = false;
		lS = false;
		mA = false;
		mD = false;
		mS = false;
		mE = false;
		break;
	}
}
// Materials menu function
void materialMenuFunc(int id) {
	switch (id)
	{
	case 1:
		mA = true;
		mD = false;
		mS = false;
		mE = false;
		lD = false;
		lA = false;
		lS = false;
		break;
	case 2:
		mS = true;
		mD = false;
		mA = false;
		mE = false;
		lD = false;
		lA = false;
		lS = false;
		break;
	case 3:
		mD = true;
		mA = false;
		mS = false;
		mE = false;
		lD = false;
		lA = false;
		lS = false;
		break;
	case 4:
		mE = true;
		mD = false;
		mS = false;
		mA = false;
		lD = false;
		lA = false;
		lS = false;
		break;
	}
}
// Shininess menu function
void shininessMenuFunc(int id) {
	switch (id)
	{
	case 1:
		// Blank material
		mShininess[0] = 0;
		break;
	case 2:
		// Shiny material
		mShininess[0] = 128;
		break;
	}
}
// Exit menu function
void exitMenuFunc(int id) {
	switch (id)
	{
	case 1:
		exit(0);
		break;
	}
}
// Create menu
void createMenu()
{
	int exitMenu, lightSubMenu, materialSubMenu, shininessSubMenu;
	// Light submenu
	lightSubMenu = glutCreateMenu(lightMenuFunc);
	glutAddMenuEntry("Ambient Light", 1);
	glutAddMenuEntry("Specular Light", 2);
	glutAddMenuEntry("Diffuse Light", 3);
	// Material submenu
	materialSubMenu = glutCreateMenu(materialMenuFunc);
	glutAddMenuEntry("Ambient Material", 1);
	glutAddMenuEntry("Specular Material", 2);
	glutAddMenuEntry("Diffuse Material", 3);
	glutAddMenuEntry("Emissive Material", 4);
	// Shininess submenu
	shininessSubMenu = glutCreateMenu(shininessMenuFunc);
	glutAddMenuEntry("Blank Material", 1);
	glutAddMenuEntry("Shiny Material", 2);
	// Exit menu
	exitMenu = glutCreateMenu(exitMenuFunc);
	// Display menus
	glutAddSubMenu("Light Source", lightSubMenu);
	glutAddSubMenu("Materials Source", materialSubMenu);
	glutAddSubMenu("Shininess", shininessSubMenu);
	glutAddMenuEntry("Exit", 1);
	// Attach to right mouse click
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
// Convert numbers to strings
void convertNum() {
	// Shininess
	ostringstream convert;   // stream used for the conversion
	convert << mShininess[0];      // insert the textual representation of 'Number' in the characters in the stream
	mSText = convert.str();
	convert.str("");
	convert.clear();
	// Light Ka
	convert << light_Ka[0];      // insert the textual representation of 'Number' in the characters in the stream
	lKa0Text = convert.str();
	convert.str("");
	convert.clear();
	convert << light_Ka[1];      // insert the textual representation of 'Number' in the characters in the stream
	lKa1Text = convert.str();
	convert.str("");
	convert.clear();
	convert << light_Ka[2];      // insert the textual representation of 'Number' in the characters in the stream
	lKa2Text = convert.str();
	convert.str("");
	convert.clear();
	// Light Ks
	convert << light_Ks[0];      // insert the textual representation of 'Number' in the characters in the stream
	lKs0Text = convert.str();
	convert.str("");
	convert.clear();
	convert << light_Ks[1];      // insert the textual representation of 'Number' in the characters in the stream
	lKs1Text = convert.str();
	convert.str("");
	convert.clear();
	convert << light_Ks[2];      // insert the textual representation of 'Number' in the characters in the stream
	lKs2Text = convert.str();
	convert.str("");
	convert.clear();
	// Light Kd
	convert << light_Kd[0];      // insert the textual representation of 'Number' in the characters in the stream
	lKd0Text = convert.str();
	convert.str("");
	convert.clear();
	convert << light_Kd[1];      // insert the textual representation of 'Number' in the characters in the stream
	lKd1Text = convert.str();
	convert.str("");
	convert.clear();
	convert << light_Kd[2];      // insert the textual representation of 'Number' in the characters in the stream
	lKd2Text = convert.str();
	convert.str("");
	convert.clear();

	// Material Ka
	convert << material_Ka[0];      // insert the textual representation of 'Number' in the characters in the stream
	mKa0Text = convert.str();
	convert.str("");
	convert.clear();
	convert << material_Ka[1];      // insert the textual representation of 'Number' in the characters in the stream
	mKa1Text = convert.str();
	convert.str("");
	convert.clear();
	convert << material_Ka[2];      // insert the textual representation of 'Number' in the characters in the stream
	mKa2Text = convert.str();
	convert.str("");
	convert.clear();
	// Material Ks
	convert << material_Ks[0];
	mKs0Text = convert.str();
	convert.str("");
	convert.clear();
	convert << material_Ks[1];      // insert the textual representation of 'Number' in the characters in the stream
	mKs1Text = convert.str();
	convert.str("");
	convert.clear();
	convert << material_Ks[2];      // insert the textual representation of 'Number' in the characters in the stream
	mKs2Text = convert.str();
	convert.str("");
	convert.clear();
	// Material Kd
	convert << material_Kd[0];
	mKd0Text = convert.str();
	convert.str("");
	convert.clear();
	convert << material_Kd[1];      // insert the textual representation of 'Number' in the characters in the stream
	mKd1Text = convert.str();
	convert.str("");
	convert.clear();
	convert << material_Kd[2];      // insert the textual representation of 'Number' in the characters in the stream
	mKd2Text = convert.str();
	convert.str("");
	convert.clear();
	// Material Ke
	convert << material_Ke[0];
	mKe0Text = convert.str();
	convert.str("");
	convert.clear();
	convert << material_Ke[1];      // insert the textual representation of 'Number' in the characters in the stream
	mKe1Text = convert.str();
	convert.str("");
	convert.clear();
	convert << material_Ke[2];      // insert the textual representation of 'Number' in the characters in the stream
	mKe2Text = convert.str();
	convert.str("");
	convert.clear();
	convert << i + 1;      // insert the textual representation of 'Number' in the characters in the stream
	iText = convert.str();
	convert.str("");
	convert.clear();
}
// Update event
void update() {
	angle += 1;
	convertNum();
	// Light rendering
	light();
	// Materials rendering
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);

}
// Set a timer
void timer(int miliseconds)
{
	// Update function
	update();
	// Set a timer
	glutTimerFunc(updateInterval, timer, updateInterval);
	// Redisplay
	glutPostRedisplay();
}
// Main function
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(100, 100);
	leftTextPos = 25, rightTextPos = 800;
	glutCreateWindow("Zelin's OpenGL Lighting & Materials");
	// Initialize
	init();
	// Create menu
	createMenu();
	glutDisplayFunc(display);
	// set special function for arrow keys
	glutSpecialFunc(keyboard);
	glutReshapeFunc(reshape);
	// Update time.
	glutTimerFunc(0, timer, updateInterval);
	glutMainLoop();
	return 0;
}