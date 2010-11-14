#include <gl.h>
#include <glu.h>
#include <glut.h>

#include <iostream>

#include <string>
#include <deque>

void render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  glutSolidSphere(1.0, 20, 16);

  GLfloat material_specular[] = { 1.0, 0.0, 0.0, 1.0 };
  GLfloat material_shininess[] = { 50.0 };
  GLfloat light_position[] = { 0.0, 0.0, -2.0, 1.0 };

  GLfloat light0_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };

  glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
  
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

  GLfloat light1_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat light1_position[] = { 1.0, 1.0, 1.0 };
  GLfloat light1_spot_direction[] = { -1.0, -1.0, -1.0 };
  
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,  light1_spot_direction);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);

  glPopMatrix();
  
  glutSwapBuffers();
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 'a') 
  {
    exit(0);
  }
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 10000000000000000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0.0, 0, 5, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);        
}

void data()
{  

}

int main(int argc, char** argv)
{
  std::clog << "starting" << std::endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Import");

  std::clog << "init" << std::endl;

  glClearColor(0.00, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);


  data();
 
  std::clog << "running" << std::endl;

  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  //  glutFullScreen();
  glutMainLoop();

  std::clog << "closing" << std::endl;
}
