#include <gl.h>
#include <glu.h>
#include <glut.h>

#include "clock.hpp"
ClockT clockt;

#include "galaxy.hpp"
Galaxy galaxy;

#include "camera.hpp"
Camera camera;

int time_offset = 0;

void render()
{
  galaxy.time(time_offset);
  galaxy.update(clockt.delta());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GLfloat sun_light_position0[] = { 0.0, 0.0, 0.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position0);

  galaxy.render_stars();

  glPushMatrix();

  camera.render();
  galaxy.render();
  
  glPopMatrix();

  glutSwapBuffers();
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 'w')
  {
    camera.zoom(1);
  }

  if (key == 's')
  {
    camera.zoom(-1);
  }

  if (key == 'a')
  {
    camera.rotate(-1);
  }

  if (key == 'd')
  {
    camera.rotate(1);
  }

  if (key == 'e')
  {
    camera.strafe(1);
  }

  if (key == 'q')
  {
    camera.strafe(-1);
  }

  if (key == 'r')
  {
    camera.pitch(1);
  }

  if (key == 'f')
  {
    camera.pitch(-1);
  }

  if (key == 'z')
  {
    time_offset -= 10;
  }

  if (key == 'x')
  {
    time_offset += 10;
  }

  if (key == 27)
  {
    exit(0);
  }
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 1000000000000000000000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0, 0, -10.01, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);         
}

void init()
{
  glClearColor(0.00, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);  
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);

  clockt.init();
  galaxy.init();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DEPTH);
  glutInitWindowSize(1280, 800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Import");

  init();

  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutFullScreen();

  glutMainLoop();

  return 0;
}
