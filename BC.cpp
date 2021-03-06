// Lab3.cpp : Defines the entry point for the console application.
//

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "Wheel.h"
using namespace std;

#define PI			3.1415926

int		screenWidth = 600;
int		screenHeight = 600;
bool	bWireFrame = false;
//camera
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;
float upVector_X, upVector_Y, upVector_Z;
float nX, nY, nZ;
float vX, vY, vZ;
float uX, uY, uZ;
float zoomValue;
bool	b4View = false;


Wheel TyrePart1;
Wheel TyrePart2;
Wheel TyrePart3;
Wheel RimPart1;
Wheel RimPart2;
Wheel RimPart3;
Mesh Cl;
void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}
void calculateNUV() {
	//n=eye-lookAtt
	nX = camera_X - lookAt_X;
	nY = camera_Y - lookAt_Y;
	nZ = camera_Z - lookAt_Z;
	float nD = sqrt(nX*nX + nY * nY + nZ * nZ);
	//u=up*n
	uX = upVector_Y * nZ - upVector_Z * nY;
	uY = upVector_Z * nX - upVector_X * nZ;
	uZ = upVector_X * nY - upVector_Y * nX;
	float uD = sqrt(uX*uX + uY * uY + uZ * uZ);
	//v=n*u
	vX = nY * uZ - nZ * uY;
	vY = nZ * uX - nX * uZ;
	vZ = nX * uY - nY * uX;
	float vD = sqrt(vX*vX + vY * vY + vZ * vZ);
	//Chuan hoa
	nX /= nD;nY /= nD;nZ /= nD;
	uX /= uD;uY /= uD;uZ /= uD;
	vX /= nD;vY /= nD;vZ /= nD;
}
//color
float qaRed[] = { 1.0,0.0,0.0,1.0 };
float qaGreen[] = { 0.0,1.0,0.0,1.0 };
float qaBlue[] = { 0.0,0.0,1.0,1.0 };
float qaYellow[] = { 1.0,1.0,0.0,1.0 };
float qaBlack[] = { 0.0,0.0,0.0,1.0 };
float qaWhite[] = { 1.0,1.0,1.0,1.0 };
float qaPupple[] = { 1.0,0.0,1.0,1.0 };
float qaGray[] = { 0.5,0.5,0.5,1.0 };
float qaTyre[] = { 0.2,0.2,0.2,1.0 };
float qaGray2[] = { 0.95,0.95,0.95,1.0 };
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		bWireFrame = !bWireFrame;
		break;
	case '2':
	
		break;
	case '3':
		
		break;
	case '4':
	
		break;
	case 'w':case 'W':

		break;
	case 'a':case 'A':

		break;
	case 's':case 'S':

		break;
	case 'd':case 'D':

		break;
	case 'v':case 'V':
		b4View = !b4View;
		break;


		break;
	}
	glutPostRedisplay();
}
void OnSpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN){
		calculateNUV();
		camera_X += -vX;
		camera_Y += -vY;
		camera_Z += -vZ;
		lookAt_X += -vX;
		lookAt_Y += -vY;
		lookAt_Z += -vZ;
	}
	else if (key == GLUT_KEY_UP){
		calculateNUV();
		camera_X += vX;
		camera_Y += vY;
		camera_Z += vZ;
		lookAt_X += vX;
		lookAt_Y += vY;
		lookAt_Z += vZ;
	}
	else if (key == GLUT_KEY_LEFT) {
		calculateNUV();
		camera_X += -uX;
		camera_Y += -uY;
		camera_Z += -uZ;
		lookAt_X += -uX;
		lookAt_Y += -uY;
		lookAt_Z += -uZ;
	}
	else if (key == GLUT_KEY_RIGHT) {
		calculateNUV();
		camera_X += uX;
		camera_Y += uY;
		camera_Z += uZ;
		lookAt_X += uX;
		lookAt_Y += uY;
		lookAt_Z += uZ;
	}
	glutPostRedisplay();
}
void OnMouseClick(int button, int state, int x, int y)
{
	if (button == 3 && state == GLUT_DOWN)
	{
		zoomValue -= 0.2;
		glutPostRedisplay();
	}
	if (button == 4 && state == GLUT_DOWN)
	{
		zoomValue += 0.2;
		glutPostRedisplay();
	}
}
void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);//x
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);//y
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);//z
	glVertex3f(0, 0, 4);
	glEnd();
}

void drawTyrePart2() {
	glPushMatrix();
	glTranslatef(-0.75 +0.35/ 2, 0, 0);
	int n = 96;
	float phi = 2*PI / n;
	for (int i=0;i < n;i++) {
		glPushMatrix();
		glTranslatef(0, 3 * cos(i*phi), 3 * sin(i*phi));
		glRotatef(i * 360.f / n, 1, 0, 0);
		if (bWireFrame) TyrePart2.DrawWireframe();
		TyrePart2.Draw();
		glTranslatef(0.35/2+0.02+0.38/2, 0, 0);
		if (bWireFrame) TyrePart3.DrawWireframe();
		TyrePart3.Draw();
		glPopMatrix();
	}
	glPopMatrix();
}
void drawRimPart2() {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	for (int i = 0; i < 4; i++) {
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
		if (bWireFrame) RimPart2.DrawWireframe();
		RimPart2.Draw();
		glScalef(1, 1, -1);
		if (bWireFrame) RimPart2.DrawWireframe();
		RimPart2.Draw();
		glPopMatrix();
	}
	glPopMatrix();
	//
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	for (int i = 0; i < 4; i++) {
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		if (bWireFrame) RimPart3.DrawWireframe();
		RimPart3.Draw();
		glScalef(1, 1, -1);
		if (bWireFrame) RimPart3.DrawWireframe();
		RimPart3.Draw();
		glPopMatrix();
	}
	glPopMatrix();
}
void drawRimPart1() {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	if (bWireFrame) RimPart1.DrawWireframe();
	RimPart1.Draw();

	glPopMatrix();
}
void drawTyrePart1() {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	if (bWireFrame) TyrePart1.DrawWireframe();
	TyrePart1.Draw();
	glPopMatrix();
}
void drawHaftWheel() {
	glPushMatrix();
	//Setup Material
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	//Draw
	drawTyrePart1();
	//Setup Material
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	//Draw
	drawTyrePart2();
	//Setup Material
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	//Draw
	drawRimPart1();
	glPopMatrix();
}
void drawWheel() {
	drawHaftWheel();
	glPushMatrix();
	glScalef(-1, 1, 1);
	drawHaftWheel();
	glPopMatrix();
	//Setup Material
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	//Draw
	drawRimPart2();
}
void draw() {
	drawAxis();
	glPushMatrix();
	glTranslatef(-5, 0, 0);
	drawWheel();
	glTranslatef(10, 0, 0);
	glScalef(-1.0, 1.0, 1.0);
	drawWheel();
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	if (bWireFrame) Cl.DrawWireframe();
	else Cl.Draw();
	glPopMatrix();

}
void myDisplay()
{
	float	fHalfSize = zoomValue;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (!b4View)
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, upVector_X, upVector_Y, upVector_Z);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, screenWidth, screenHeight);
		draw();
		glFlush();
		glutSwapBuffers();
	}
	else {
		{
			glPushMatrix();
			gluLookAt(camera_X, camera_Y, camera_Z, 0, 1, 0, 0, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, screenHeight / 2, screenWidth / 2, screenHeight / 2);
			draw();
			glPopMatrix();
			//
			glPushMatrix();
			glViewport(0, 0, screenWidth / 2, screenHeight / 2);
			gluLookAt(0, 10, 0, 0, 1, 0, 0, 0, 1);
			draw();
			glPopMatrix();
			//
			glPushMatrix();
			gluLookAt(0, 4, 10, 0, 1, 0, 0, 1, 0);
			glViewport(screenWidth / 2, screenHeight / 2, screenWidth / 2, screenHeight / 2);
			draw();
			glPopMatrix();
			//
			glPushMatrix();
			gluLookAt(10, 4, 0, 0, 1, 0, 0, 1, 0);
			glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight / 2);
			draw();
			glPopMatrix();
			glFlush();
			glutSwapBuffers();

		}
	}
}


void myInit()
{
	//
	camera_X = 2.0f;
	camera_Y = 0.5f;
	camera_Z = 0.0f;
	lookAt_X = 0.0f;
	lookAt_Y = 0.5f;
	camera_Z = 0.0f;
	upVector_X = 0.0f;
	upVector_Y = 1.0f;
	upVector_Z = 0.0f;
	zoomValue = 5.0f;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	//Lighting setup
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//Set light intensity and color
	float qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
	float qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };
	float qaSpecularLight[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	//Set the light position
	float qaLightPosition[] = { 10.0, 2.0, 10.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	//


}

int _tmain(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("BC"); // open the screen window
	//
	int nX = 4;
	//create
	TyrePart1.CreateTyrePart1(3,2,0.75,0.8, nX);
	TyrePart2.CreateTyrePart2(0.35, 0.05, 0.15);
	TyrePart3.CreateTyrePart3(0.38, 0.05, 0.15);
	RimPart1.CreateRimPart1(2, 1.8, 0.75, nX);
	RimPart2.CreateRimPart2(1.8,0.5,0.3, nX);
	RimPart3.CreateRimPart2(1.8, 0.5, 0.0, nX);
	Cl.CreateCylinder(32* nX, 10, 0.4);
	//cal normvector
	TyrePart1.CalculateFacesNorm();
	TyrePart2.CalculateFacesNorm();
	TyrePart3.CalculateFacesNorm();
	RimPart1.CalculateFacesNorm();
	RimPart2.CalculateFacesNorm();
	RimPart3.CalculateFacesNorm();
	Cl.CalculateFacesNorm();
	//
	myInit();
	glutSpecialFunc(OnSpecialKey);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(OnMouseClick);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}

