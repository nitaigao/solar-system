#include <gl.h>
#include <glu.h>
#include <glut.h>

#include <iostream>

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  static float z = 0.0;
  z -= 0.001;

  std::clog << z << std::endl;
          
  GLfloat vertices[] = {    1,              -1,  0, 
                           -0.999999821186, -1,  1.78814e-7, 
                            0.999999642372,  1, -5.96046e-7, 
                           -1,               1,  3.57628e-7 };

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices); 
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);

  glFlush();
  glutPostRedisplay();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0,  // left, right 
            -1.0, 1.0,  // top, bottom
            1.5, 20.0); // near, far
  glMatrixMode(GL_MODELVIEW);
            
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
