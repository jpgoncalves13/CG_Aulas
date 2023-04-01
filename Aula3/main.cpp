#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alpha = 0;
float beta = 0;
float raio = 1;

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


void drawCylinder(float radius, float height, int slices) {

float x = (2*M_PI) / slices;

float h = height/2;

	for(int i = 0; i < slices; i++){
		glBegin(GL_TRIANGLES);
			//base de cima
			glVertex3f(0,h,0);
			glVertex3f(sin(x*i)*radius,h,cos(x*i)*radius);
			glVertex3f(sin(x*(i+1))*radius,h,cos(x*(i+1)*radius));

			//faces
			glVertex3f(radius*sin(x*i),h,radius*cos(x*i));
			glVertex3f(radius*sin(x*i),-h,radius*cos(x*i));
			glVertex3f(radius*sin(x*(i+1)),-h,radius*cos(x*(i+1)));

			glVertex3f(radius*sin(x*(i+1)),-h,radius*cos(x*(i+1)));
			glVertex3f(radius*sin(x*(i+1)),h,radius*cos(x*(i+1)));
			glVertex3f(radius*sin(x*i),h,radius*cos(x*i));

			//base de baixo
			glVertex3f(0,-h,0);
			glVertex3f(sin(x*(i+1))*radius,-h,cos(x*(i+1)*radius));
			glVertex3f(sin(x*i)*radius,-h,cos(x*i)*radius);

		glEnd();
	}

}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	float px = raio * cos(beta) * sin(alpha);
	float py = raio * sin(beta);
	float pz = raio * cos(beta) * cos(alfa);

	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawCylinder(1,5,20);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

	if (c == '+') {
		raio+=0.1;
	}
	else if (c == '-'){
		raio-=0.1;
	}

}


void processSpecialKeys(int key, int xx, int yy) {

	if (key == GLUT_KEY_LEFT) {
		alfa -= M_PI/10;
	}
	else if (key == GLUT_KEY_RIGHT) {
		alfa += M_PI/10
	}
	else if (key == GLUT_KEY_UP) {
		beta += M_PI/10;
	}
	else if (key == GLUT_KEY_DOWN) {
		beta -= M_PI/10;
	}

}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glPolygonMode(GL_FRONT, GL_LINE);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
