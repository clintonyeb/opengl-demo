// Function prototypes

void myKeyboardFunc( unsigned char key, int x, int y );
void mySpecialKeyFunc( int key, int x, int y );

void updateScene( void );

void initRendering();
void resizeWindow(int w, int h);

void KeyUp();
void KeyDown();
void KeyLeft();
void KeyRight();
void ResetAnimation();
void ZeroRotation();
void ShadeModelToggle();
void FillModeToggle();
void QuadTriangleToggle();
void WrapMore();
void WrapLess();
void NumPerWrapMore();
void NumPerWrapLess();

// Torus specific routines.
void putVert(float i, float j);


