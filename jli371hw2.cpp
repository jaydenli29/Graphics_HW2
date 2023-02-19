#include <iostream>
#include <cmath>
#define GL_SILENCE_DEPRECATION

using namespace std;

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.1415926

// Global variables:
static int nv = 20;
static int degree = 0;
static int cx = -45, cy = 35, cz = 0;

static int MainWindow, MenuWindow; // Window identifiers.
int isRed=1;  //1 is true
int isBlue=1;

void drawCircle()
{
    float r = 3;  // Radius of the button

        // draw circle
        glColor3f(0.0, 0.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= nv; i++)
        {
            glVertex3f(r * cos((float)(i) / nv * 2 * PI) + cx,
                r * sin((float)(i) / nv * 2 * PI) + cy, cz);
        }
        glEnd();
}

// Routine to draw a bitmap character string
void writeBitmapString(void* font, const char* string)
{
    const char* c;
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

// Drawing routine for first window.
void drawSceneMainWindow(void)
{
   // Choose window.
   glutSetWindow(MainWindow);

   glClear(GL_COLOR_BUFFER_BIT);

    
  if(isRed)
   glColor3f(1.0, 0.0, 0.0);
  else glColor3f(0,1,0);//green
   glBegin(GL_POLYGON);
      glVertex3f(10.0, 10.0, 0.0);
      glVertex3f(40.0, 10.0, 0.0);
      glVertex3f(40.0, 40.0, 0.0);
      glVertex3f(10.0, 40.0, 0.0);
   glEnd();

   glFlush();
}

// Drawing routine for second window.
void drawSceneMenuWindow(void)
{
   // Choose window.
   glutSetWindow(MenuWindow);

   glClear(GL_COLOR_BUFFER_BIT);

    
   drawCircle();
    
   glFlush();
}

// Initialization routine for first window.
void setupRedSquareWindow(void)
{
   // White background.
   glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Initialization routine for second window.
void setupBlueSquareWindow(void)
{
   // Green background.
   glClearColor(0.0, 1.0, 0.0, 0.0);
}

// Reshape routine for first window.
void resizeMainWindow(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Aspect ratio matches the window.
   glOrtho(0.0, 50.0, 0.0, 100.0, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Reshape routine for second window.
void resizeMenuWindow(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine shared by both windows.
void keyInput(unsigned char key, int x, int y)
{
   switch(key)
   {
      case 27:
         exit(0);
         break;
    
      default:
         break;
   }
}


// Mouse callback routine.
void MainMouseControl(int button, int state, int x, int y)
{
    int xWorld, yWorld;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        
            isRed=!isRed;
    
        glutPostRedisplay();
    }
}

void MenuMouseControl(int button, int state, int x, int y)
{
    int xWorld, yWorld;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xWorld=x/5;
        yWorld=(500-y)/5;
        cout<<x<<"  "<<y<<endl;
        cout<<xWorld<<"  "<<yWorld<<endl<<endl;
        if (xWorld>=30 && xWorld<=40 && yWorld>=50 && yWorld<=60)
            isBlue=!isBlue;
        
        glutPostRedisplay();
    }
}
// Main routine.
int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   
   // First top-level window definition.
   glutInitWindowSize(800, 800);
   glutInitWindowPosition(1000, 100);

   // Create the first window and return id.
   MainWindow = glutCreateWindow("Main window");

   // Initialization, display, and other routines of the first window.
   setupRedSquareWindow();
   glutDisplayFunc(drawSceneMainWindow);
   glutReshapeFunc(resizeMainWindow);
   glutMouseFunc(MainMouseControl);
    glutKeyboardFunc(keyInput); // Routine is shared by both windows.

   
   // Second top-level window definition.
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(20, 100);
   
   // Create the second window and return id.
   MenuWindow = glutCreateWindow("Menu window");

   // Initialization, display, and other routines of the second window.
   setupBlueSquareWindow();
   glutDisplayFunc(drawSceneMenuWindow);
   glutReshapeFunc(resizeMenuWindow);
   glutMouseFunc(MenuMouseControl);
    glutKeyboardFunc(keyInput); // Routine is shared by both windows.

    
   glutMainLoop();

   return 0;
}
