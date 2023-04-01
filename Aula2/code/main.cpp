#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>


float dispX = 0;
float dispY = 0;
float dispZ = 0;

float angle = 1;


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


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	glPolygonMode(GL_FRONT,GL_LINE);

	// put axis drawing in here

	glBegin(GL_LINES);
	// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
	// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();


	// put the geometric transformations here
	glTranslatef(dispX,dispY,dispZ);

	glRotatef(angle,0,1,0);

	// put pyramid drawing instructions here
	glBegin(GL_TRIANGLES);
	    glVertex3f(2.0f, 0.0f, 2.0f);
	    glVertex3f(2.0f, 0.0f, -2.0f);
	    glVertex3f(-2.0f, 0.0f, -2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	    glVertex3f(-2.0f, 0.0f, -2.0f);
	    glVertex3f(-2.0f, 0.0f, 2.0f);
	    glVertex3f(2.0f, 0.0f, 2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	    glVertex3f(2.0f, 0.0f, 2.0f);
	    glVertex3f(0.0f, 3.0f, 0.0f);
	    glVertex3f(-2.0f, 0.0f, 2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	    glVertex3f(2.0f, 0.0f, -2.0f);
	    glVertex3f(0.0f, 3.0f, 0.0f);
	    glVertex3f(2.0f, 0.0f, 2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	    glVertex3f(-2.0f, 0.0f, -2.0f);
	    glVertex3f(0.0f, 3.0f, 0.0f);
	    glVertex3f(2.0f, 0.0f, 2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	    glVertex3f(2.0f, 0.0f, -2.0f);
	    glVertex3f(0.0f, 3.0f, 0.0f);
	    glVertex3f(-2.0f, 0.0f, -2.0f);
	glEnd();

	// End of frame
	glutSwapBuffers();
}


// write function to process keyboard events
void keyboard_process(unsigned char key, int x, int y){
	if (key == 'a') {
		dispX-=0.1;
	}
	else if (key == 'd') {
		dispX+=0.1;
	}
	else if (key == 'w') {
		dispY+=0.1;
	}
	else if (key == 's') {
		dispY-=0.1;
	}
	else if (key == 'r') {
		angle+=1;
	}


	glutPostRedisplay();
}



int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks

	glutKeyboardFunc(keyboard_process);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
