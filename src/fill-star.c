// gcc -lGL -lGLU -lGLEW -lglut -I./include src/star.c -o output/star

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h> // OpenGL Graphics Utility Library
#include "sample-draw.h"

// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void)
{
    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(1.0, 1.0, 1.0); // white
    glVertex2f(1.5, 1.5);
    glVertex2f(1.2, 1.8);
    glColor3f(1.0, 1.0, 0.0); // red
    glVertex2f(1.5, 2.5);
    glVertex2f(1.8, 1.8);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(2.5, 2.2);
    glVertex2f(2.0, 1.5);
    glColor3f(0.0, 1.0, 0.0); // white
    glVertex2f(2.5, 0.7);
    glVertex2f(1.5, 1.3);
    glColor3f(1.0, 0.0, 0.0); // white
    glVertex2f(0.5, 0.7);
    glVertex2f(1.0, 1.5);
    glColor3f(1.0, 0.0, 1.0); // white
    glVertex2f(0.5, 2.2);
    glVertex2f(1.2, 1.8);

    glEnd();

    // Flush the pipeline.  (Not usually necessary.)
    glFlush();
}

// Initialize OpenGL's rendering modes
void initRendering()
{

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Uncomment out the first block of code below, and then the second block,
    //		to see how they affect line and point drawing.
    /*
	// The following commands should cause points and line to be drawn larger
	//	than a single pixel width.
	glPointSize(8);
	glLineWidth(5);
*/

    /*
	// The following commands should induce OpenGL to create round points and 
	//	antialias points and lines.  (This is implementation dependent unfortunately).
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias the lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/
}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
    double scale, center;
    double windowXmin, windowXmax, windowYmin, windowYmax;

    // Define the portion of the window used for OpenGL rendering.
    glViewport(0, 0, w, h); // View port uses whole window

    // Set up the projection view matrix: orthographic projection
    // Determine the min and max values for x and y that should appear in the window.
    // The complication is that the aspect ratio of the window may not match the
    //		aspect ratio of the scene we want to view.
    w = (w == 0) ? 1 : w;
    h = (h == 0) ? 1 : h;
    if ((Xmax - Xmin) / w < (Ymax - Ymin) / h)
    {
        scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
        center = (Xmax + Xmin) / 2;
        windowXmin = center - (center - Xmin) * scale;
        windowXmax = center + (Xmax - center) * scale;
        windowYmin = Ymin;
        windowYmax = Ymax;
    }
    else
    {
        scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
        center = (Ymax + Ymin) / 2;
        windowYmin = center - (center - Ymin) * scale;
        windowYmax = center + (Ymax - center) * scale;
        windowXmin = Xmin;
        windowXmax = Xmax;
    }

    // Now that we know the max & min values for x & y that should be visible in the window,
    //		we set up the orthographic projection.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);
}

// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    // The image is not animated so single buffering is OK.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    // Window position (from top corner), and size (width and height)
    glutInitWindowPosition(20, 60);
    glutInitWindowSize(360, 360);
    glutCreateWindow("SimpleDraw - Press space bar to toggle images");

    // Initialize OpenGL as we like it..
    initRendering();

    // Set up the callback function for resizing windows
    glutReshapeFunc(resizeWindow);

    // Call this for background processing
    // glutIdleFunc( myIdleFunction );

    // call this whenever window needs redrawing
    glutDisplayFunc(drawScene);

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return (0); // This line is never reached.
}
