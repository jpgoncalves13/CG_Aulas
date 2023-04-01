#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

float rc = 10, ri = 30, r = 50;
float time = 0;


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawTree(){
	float ang = M_PI / 2;
	glRotatef(ang, 1, 0, 0);
	glutSolidCone(2, 10, 10, 10);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();


	// put code to draw scene in here
	time += 0.1;

	glColor3f(255.0f, 0.0f, 102.0f);
	glutSolidTorus(1, 3, 30, 30);


	glColor3f(0.0f, 102.0f, 255.0f);
	for(int i = 0; i < 8; i++){
		glPushMatrix();
		glRotatef(i*45.0 - time*2, 0, 1, 0);
		glTranslatef(rc, 2, 0);
		glutSolidTeapot(2);
		glPopMatrix();
	}

	glColor3f(255.0f, 0.0f, 0.0f);
	for(int i = 0; i < 16; i++){
		glPushMatrix();
		glRotatef(i*22.5 + time*2, 0, 1, 0);
		glTranslatef(0 , 2, ri);
		glutSolidTeapot(2);
		glPopMatrix();

	}

	srand(1);


	for(int i = 0; i < 200; i++){
		glColor3f(0.0f, 153.0f, 0.0f);
		float x;
		x = (float) rand() / RAND_MAX;
		x = x*200 - 100;

		float z;
		z = (float) rand() / RAND_MAX;
		z = z*200 - 100;

		while(pow(x,2) + pow(z,2) < pow(r,2)){
			x = (float) rand() / RAND_MAX;
			x = x*200 - 100;

			z = (float) rand() / RAND_MAX;
			z = z*200 - 100;
		}

		glPushMatrix();
		glTranslatef(x, 2, z);
		glRotatef(-90.0f, 1, 0, 0);

		glutSolidCone(2, 10, 10, 10);
		glPopMatrix();

		glColor3f(204.0f, 102.0f, 0.0f);
		glPushMatrix();
		glTranslatef(x, 0, z);
		glRotatef(-90.0f, 1, 0, 0);

		glutSolidCone(1, 5, 10, 10);
		glPopMatrix();

	}


	glColor3f(255.0f, 255.0f, 255.0f);



	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

	srand(1);

// Required callback registry
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
