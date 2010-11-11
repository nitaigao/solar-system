#include <gl.h>
#include <glu.h>
#include <glut.h>

#include <iostream>

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0.0, 0.0, -3.0);

  static int year = 0;
  year -= 1 % 2048;

  static int day = 0.0f;
  day -= 1 % 2048;

  glPushMatrix();
  glRotatef(-year, 0.0f, 1.0f, 0.0f);
  glutWireSphere(1, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glRotatef(year, 0.0, 1.0, 0.0);
  glTranslatef(2.0, 0.0, 0.0);
  glRotatef(day, 0.0f, 1.0f, 0.0f);
  glutWireSphere(0.1, 10, 10);

  glPushMatrix(); // moon

  glRotatef((-day * 5), 0.0f, 1.0f, 0.0f);
  glTranslatef(0.2, 0.0, 0.0);
  glutWireSphere(0.01, 10, 10);

  glPopMatrix();
  glPopMatrix();



  glutSwapBuffers();
  glutPostRedisplay();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 200.0);
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  gluLookAt (0.0, 0.0, 5.0, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);        
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

  glClearColor(1.00, 0.0, 0.0, 0.0);
 
  std::clog << "running" << std::endl;

  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutMainLoop();

  std::clog << "closing" << std::endl;
}
