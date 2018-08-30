#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <GL/glut.h> // OpenGL Graphics Utility Library
#include "WrapTorus.h"

// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

GLenum runMode = GL_TRUE;

// Variables controlling the animation
float RotX = 0.0;					// Rotational position around x-axis
float RotY = 0.0;					// Rotational position around y-axis
float RotIncrementX = 0.0;			// Rotational increment, x-axis
float RotIncrementY = 0.0;			// Rotational increment, y-axis
const float RotIncFactor = 1.5;		// Factor change in rotation rate per key stroke

// glutKeyboardFunc is called below to set this function to handle
//		all "normal" ascii key presses.
// Only space bar and escape key have an effect.
void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
		runMode = !runMode;
		break;
	case 's':
		runMode = GL_TRUE;
		updateScene();
		runMode = GL_FALSE;
		break;
	case 27:	// Escape key
		exit(1);
	case 'r':	// Reset the animation (resets everything)
		ResetAnimation();
		break;
	case '0':	// Zero the rotation rates
		ZeroRotation();
		break;
    }
}

void mySpecialKeyFunc( int key, int x, int y ) 
{
	switch ( key ) {
	case GLUT_KEY_UP:		
		// Either increase upward rotation, or slow downward rotation
		KeyUp();
		break;
	case GLUT_KEY_DOWN:
		// Either increase downward rotation, or slow upward rotation
		KeyDown();
		break;
	case GLUT_KEY_LEFT:
		// Either increase left rotation, or slow down rightward rotation.
		KeyLeft();
		break;
	case GLUT_KEY_RIGHT:
		// Either increase right rotation, or slow down leftward rotation.
		KeyRight();
		break;
	}
}

/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
     
void drawScene(void)
{
    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUAD_STRIP);
    
	 // front
    glColor3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(2.0, 1.0, 1.0);
	glVertex3f(1.0, 2.0, 1.0);
    glVertex3f(2.0, 2.0, 1.0);

	// top
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, 2.0, 0.0);
    glVertex3f(2.0, 2.0, 0.0);

	// back
    glColor3f(0.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(2.0, 1.0, 0.0);
    
    glEnd();

	glBegin(GL_QUAD_STRIP);


    // right
    glColor3f(1.0, 0.0, 1.0);
	glVertex3f(2.0, 2.0, 0.0);
    glVertex3f(2.0, 2.0, 1.0);
	glVertex3f(2.0, 1.0, 0.0);
    glVertex3f(2.0, 1.0, 1.0);

	// bottom
    glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);

	// left
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 2.0, 0.0);
	glVertex3f(1.0, 2.0, 1.0);

	glEnd();

    // Flush the pipeline.  (Not usually necessary.)
    glFlush();
}

void updateScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();	

	if ( runMode ) {
		RotY += RotIncrementY;
		if ( fabs(RotY)>360.0 ) {
			RotY -= 360.0*((int)(RotY/360.0));
		}
		RotX += RotIncrementX;
		if ( fabs(RotX)>360.0f ) {
			RotX -= 360.0*((int)(RotX/360.0));
		}
	}

	// Set the orientation.
	glRotatef( RotX, 1.0, 0.0, 0.0);
	glRotatef( RotY, 0.0, 1.0, 0.0);

	drawScene();

    glPopMatrix();
    glutSwapBuffers();
}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
	glShadeModel( GL_FLAT );
}

void KeyUp() {
    if ( RotIncrementX == 0.0 ) {
		RotIncrementX = -0.1;		// Initially, one-tenth degree rotation per update
	}
	else if ( RotIncrementX < 0.0) {
		RotIncrementX *= RotIncFactor;
	}
	else {
		RotIncrementX /= RotIncFactor;
	}	
}

void KeyDown() {
    if ( RotIncrementX == 0.0 ) {
		RotIncrementX = 0.1;		// Initially, one-tenth degree rotation per update
	}
	else if ( RotIncrementX > 0.0) {
		RotIncrementX *= RotIncFactor;
	}
	else {
		RotIncrementX /= RotIncFactor;
	}	
}

void KeyLeft() {
    if ( RotIncrementY == 0.0 ) {
		RotIncrementY = -0.1;		// Initially, one-tenth degree rotation per update
	}
	else if ( RotIncrementY < 0.0) {
		RotIncrementY *= RotIncFactor;
	}
	else {
		RotIncrementY /= RotIncFactor;
	}	
}

void KeyRight()
{
    if ( RotIncrementY == 0.0 ) {
		RotIncrementY = 0.1;		// Initially, one-tenth degree rotation per update
	}
	else if ( RotIncrementY > 0.0) {
		RotIncrementY *= RotIncFactor;
	}
	else {
		RotIncrementY /= RotIncFactor;
	}	
}


// Resets position and sets rotation rate back to zero.
void ResetAnimation() {
	RotX = RotY = RotIncrementX = RotIncrementY = 0.0;
}

// Sets rotation rates back to zero.
void ZeroRotation() {
	RotIncrementX = RotIncrementY = 0.0;
}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
    float aspectRatio;
	glViewport( 0, 0, w, h );	// View port uses whole window
	h = (h == 0) ? 1 : h;
	aspectRatio = (float)w/(float)h;

	// Set up the projection view matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 30.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	// Move system 8 units away to be able to view from the origin.
	glTranslatef(0.0, 0.0, -8.0);

	// Tilt system 15 degrees downward in order to view from above 
	//   the xy-plane.
	glRotatef(15.0, 1.0,0.0,0.0);	 
}

// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    // The image is not animated so single buffering is OK.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Window position (from top corner), and size (width and height)
    glutInitWindowPosition(20, 60);
    glutInitWindowSize(360, 360);
    glutCreateWindow("SimpleDraw - Press space bar to toggle images");

    glCullFace(GL_BACK);

    // Initialize OpenGL as we like it..
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(myKeyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

    // Set up the callback function for resizing windows
    glutReshapeFunc(resizeWindow);

    // Call this for background processing
    glutIdleFunc( updateScene );

    // call this whenever window needs redrawing
    glutDisplayFunc(updateScene);

    fprintf(stdout, "Escape button to quit.\n");

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return (0); // This line is never reached.
}
