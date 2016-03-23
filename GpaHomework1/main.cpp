#include <glew.h> // glew.h must be included before gl.h/glu.h/freeglut.h
#include <freeglut.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include<math.h>
using namespace std;
#define MENU_TIMER_START 1//Index for menu
#define MENU_TIMER_STOP 2
#define MENU_ACTION_JUMP 3
#define MENU_ACTION_WALK 4
#define MENU_ACTION_STATIC 5
#define MENU_EXIT 6
#define ACTION_STATIC 1//Index for action
#define ACTION_WALK 2
#define ACTION_JUMP 3

GLubyte timerCount = 0;//Time settings
bool timer_enabled = true;
unsigned int timerSpeed = 100;
//Action settings
GLshort actionStatus = ACTION_STATIC;

GLdouble ortho2DSize = 1;
GLfloat objectRotateStepAngle = 1;//Step size for every move 
GLfloat objectMoveStepSize = 0.05f;
GLfloat cameraMoveStepSize = 0.05f;
GLfloat cameraTopBorder = 1.5f;//Border of the camera
GLfloat cameraBottomBorder = -1.5f;
GLfloat cameraLeftBorder = -1.0f;
GLfloat cameraRightBorder = 1.0f;
GLfloat objectLeftRightAngleBorder = 360.0f;
GLfloat objectTopBottomAngleBorder = 360.0f;//Border of the object
GLfloat objectFrontBorder = 2.0f;
GLfloat objectBehindBorder = 0.0f;

GLfloat objectPositionX = 0.0f;//Position of the object.
GLfloat objectPositionY = 0.0f;
GLfloat objectPositionZ = 0.0f;
GLfloat objectTopBottomAngle = 0.0f;
GLfloat objectLeftRightAngle = 0.0f;//The angle of the object.
GLdouble eyeX = 0.0;//The position of the camera.
GLdouble eyeY = 0.0;
GLdouble eyeZ = 1.0;
GLdouble centerX = 0.0;//The target of the camera.
GLdouble centerY = 0.0;
GLdouble centerZ = 0.0;
GLdouble upX = 0.0;//The direction of the top-direction of the camera..
GLdouble upY = 1.0;
GLdouble upZ = 0.0;


// Print OpenGL context related information.
void dumpInfo(void) {
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
//////////////////////////////////////////////
//Main robot function
////////////////////////////////////////////
int objectStatus = 1;
//黄铜1，翡翠2
int lightStatus = 1;
//Light:方向光1 点光源2 探照光3

void figure() {
	//Set light
	if (lightStatus == 1) {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		cout << "light1" << endl;
		GLfloat lightPosition[] = { -1.0, 1.0, 1.0, 0.0 };   // w=0.0

		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		GLfloat lightAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat lightSpecular[] = { 0.5, 0.5, 0.5, 1.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	} else if(lightStatus == 2){
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT2);
		cout << "light2" << endl;
		GLfloat diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient0[] = { 0.25, 0.25, 0.25, 1.0 };
		GLfloat specular0[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light0_pos[] = { -1.0, 1.0, 1,0, 1.0 };
		GLfloat a = 0.8;
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, light0_pos);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, a);
	} else {
		cout << "light 3" << endl;	
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT2);
		glShadeModel(GL_SMOOTH);
		GLfloat lightAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat lightSpecular[] = { 0.5, 0.5, 0.5, 1.0 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular);
		GLfloat lightPosition[] = { -1.0, 1.0, 1.0, 1.0 };   // w不为0
		glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);
		GLfloat lightDirection[] = { 1.0, -1.0, 0.0 };
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDirection);  // 聚光灯主轴方向  spot direction
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);   // cutoff角度  spot cutoff

	}

	if (objectStatus == 1) {
		cout << "bronze" << endl;
		//Brone
		GLfloat bronzeAmbient[] = { 0.2125f,0.1275f,0.054f};
		GLfloat bronzeDiffuse[] = {0.714f,0.4284f,0.18144f};
		GLfloat bronzeSpecular[] = { 0.393548f,0.271906f,0.166721f};
		GLfloat bronzeShiness =  0.2f ;
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpecular);
		glMaterialf(GL_FRONT, GL_SHININESS, bronzeShiness);
		glutSolidSphere(0.4f, 64, 64);
	} else {
		cout << "green" << endl;
		//Green
		GLfloat emeraldAmbient[] = { 0.0215f,0.1745f,0.0215f };
		GLfloat emeraldDiffuse[] = { 0.07568f,0.61424f,0.07568f };
		GLfloat emeraldSpecular[] = { 0.633f,0.727811f,0.633f };
		GLfloat emeraldShiness =  0.6 ;
		glMaterialfv(GL_FRONT, GL_AMBIENT, emeraldAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, emeraldDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, emeraldSpecular);
		glMaterialf(GL_FRONT, GL_SHININESS, emeraldShiness);
		glutSolidSphere(0.4f, 64, 64);
	}
}







//////////////////////////////////////////////
//Callback functions
/////////////////////////////////////////////
// GLUT callback. Called to draw the scene.
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	//glTranslatef(objectPositionX, objectPositionY, objectPositionZ);
	//glRotatef(objectLeftRightAngle, 0.0f, 1.0f, 0.0f);
	//glRotatef(objectTopBottomAngle, 1.0f, 0.0f, 0.0f);
	figure();
	glutSwapBuffers();
}
void My_Reshape(int width, int height) {
	glViewport(0, 0, width, height);
	float viewportAspect = (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0, viewportAspect, 0.1, 10);
	gluOrtho2D(-ortho2DSize * viewportAspect, ortho2DSize * viewportAspect, -ortho2DSize, ortho2DSize);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}
//Callback function for timer function
void My_Timer(int val) {
	timerCount++;
	/////
	glutPostRedisplay();
	if (timer_enabled) {
		cout << "Timer running" << endl;
		if (actionStatus == ACTION_STATIC) {
			cout << "[Tip] Status: action static" << endl;
			//actionStatic();
		}
		else if (actionStatus == ACTION_WALK) {
			cout << "[Tip] Status: action walk." << endl;
			//actionWalk();
		}
		else if (actionStatus == ACTION_JUMP) {
			cout << "[Tip] Status: action transformation" << endl;
			//actionJump();
		}
		else {
			cout << "[Error] I guess something wrong with the action status." << endl;
		}
		glutTimerFunc(timerSpeed, My_Timer, val);
	}
	else {
		glutTimerFunc(timerSpeed, My_Timer, val);
		cout << "Timer stopped" << endl;
	}
}
//Mouse callback function
void My_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case 3://When I roll towards.
		if (state == GLUT_UP) {
			if (objectPositionZ < objectFrontBorder) {
				objectPositionZ += objectMoveStepSize;
				cout << "[Tip] Object Position-Z is:" << objectPositionZ << endl;
			}
			else {
				cout << "[Tip] Object Position-Z max." << endl;
			}
			glutPostRedisplay();
		}
		break;
	case 4://When I roll back.
		if (state == GLUT_UP) {
			if (objectPositionZ > objectBehindBorder) {
				objectPositionZ -= objectMoveStepSize;
				cout << "[Tip] Object Position-Z is:" << objectPositionZ << endl;
			}
			else {
				cout << "[Tip] Object Position-Z min." << endl;
			}
			glutPostRedisplay();
		}
		break;
	}
}
//Normal keyboard press function
void My_Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		objectStatus = 1;
		glutPostRedisplay();
		break;
	case 'd':
		objectStatus = 2;
		glutPostRedisplay();
		break;
	case 'q':
		lightStatus = 1;
		glutPostRedisplay();
		break;
	case 'w':
		lightStatus = 2;
		glutPostRedisplay();
		break;
	case 'e':
		lightStatus = 3;
		glutPostRedisplay();
		break;
	case 's':
		break;
	default:
		printf("[Error]Other normal key is pressed at (%d, %d)\n", x, y);
		break;
	}
}
//Special Ket pressed/
void My_SpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:
		if (eyeY > cameraBottomBorder) {
			eyeY -= cameraMoveStepSize;
			cout << "[Tip] Camera position eyeY has changed to:" << eyeY << endl;
		}
		else {
			cout << "[Tip] Camera position eyeY min." << endl;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		if (eyeY < cameraTopBorder) {
			eyeY += cameraMoveStepSize;
			cout << "[Tip] Camera position eyeY has changed to:" << eyeY << endl;
		}
		else {
			cout << "[Tip] Camera position eyeY max." << endl;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		if (eyeX > cameraLeftBorder) {
			eyeX -= cameraMoveStepSize;
			cout << "[Tip] Camera position eyeX has changed to:" << eyeX << endl;
		}
		else {
			cout << "[Tip] Camera position eyeX min." << endl;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (eyeX < cameraRightBorder) {
			eyeX += cameraMoveStepSize;
			cout << "[Tip] Camera position eyeX has changed to:" << eyeX << endl;
		}
		else {
			cout << "[Tip] Camera position eyeX man" << endl;
		}
		glutPostRedisplay();
		break;

	default:
		printf("[Error] Other special key is pressed at (%d, %d)\n", x, y);
		break;
	}
}



////////////////////////////////////////////////////
// Initialize GLUT and GLEW, then create a window.
///////////////////////////////////////////////////
int initGlutGlewCreateWindow(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glewInit();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Graghic Program Application Homework-1:An Animated Robot.");// You cannot use OpenGL functions before this line; The OpenGL context must be created first by glutCreateWindow()!
	dumpInfo();
	return 0;
}
////////////////////////////////////
// Initialize OpenGL states.
////////////////////////////////////
int initOpenglStates() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//Set depth test.
	glEnable(GL_DEPTH_TEST);
	return 0;
}
////////////////////////
// Create a menu and bind it to mouse right button.
////////////////////////////
void My_Menu(int id) {
	switch (id) {
	case MENU_EXIT:
		exit(0);
		break;
	case MENU_ACTION_STATIC:
		//robotStatusReset();
		actionStatus = ACTION_STATIC;
		cout << "[Tip] Action mode --- Static" << endl;
		break;
	case MENU_ACTION_WALK:
		//robotStatusReset();
		actionStatus = ACTION_WALK;
		cout << "[Tip] Action mode --- Walk" << endl;
		break;
	case MENU_ACTION_JUMP:
		//robotStatusReset();
		actionStatus = ACTION_JUMP;
		cout << "[Tip] Action mode --- Jump" << endl;
		break;
	case MENU_TIMER_STOP:
		timer_enabled = false;
		cout << "[Tip] Timer Stopped" << endl;
		break;
	case MENU_TIMER_START:
		timer_enabled = true;
		cout << "[Tip] Timer started." << endl;
		break;
	default:
		cout << "[Error] Something wrong about the menu" << endl;
		break;
	}
}
//The menu of the robot.
int createMenuForFrame() {
	int menuMain = glutCreateMenu(My_Menu);
	int menu_timer = glutCreateMenu(My_Menu);
	glutSetMenu(menuMain);
	glutAddMenuEntry("Timer start", MENU_TIMER_START);
	glutAddMenuEntry("Timer stop", MENU_TIMER_STOP);
	glutAddMenuEntry("Action transformation", MENU_ACTION_JUMP);
	glutAddMenuEntry("Action walk", MENU_ACTION_WALK);
	glutAddMenuEntry("Action static", MENU_ACTION_STATIC);
	glutAddMenuEntry("Exit", MENU_EXIT);
	glutSetMenu(menuMain);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	return 0;
}
////////////////////////////
// Register GLUT callback functions.
///////////////////////////////
int registerCallbackFunctions() {
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutMouseFunc(My_Mouse);
	glutKeyboardFunc(My_Keyboard);
	glutSpecialFunc(My_SpecialKeys);
	glutTimerFunc(timerSpeed, My_Timer, 0);
	return 0;
}
//Lanuncher of the robot.
int main(int argc, char *argv[]) {
	// Initialize GLUT and GLEW, then create a window.
	initGlutGlewCreateWindow(argc, argv);
	// Initialize OpenGL states.
	initOpenglStates();
	// Create a menu and bind it to mouse right button.
	createMenuForFrame();
	// Register GLUT callback functions.
	registerCallbackFunctions();
	// Enter main event loop.Loop the upward following function again and again.
	glutMainLoop();
	return 0;
}