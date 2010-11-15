#include <gl.h>
#include <glu.h>
#include <glut.h>

#include <string>
#include <deque>
#include <map>
#include <sys/time.h>

#include "raw_texture.hpp"

int speed = 5;
#include "planet.hpp"

int zoom = 0;
int rotation = 0;
int pedestal = 0;
int pitch = 0;

void render_stars()
{
  GLfloat star_verts[] = {  2000.0,  2000.0, 0.0,
                            2000.0, -2000.0, 0.0,
                           -2000.0,  2000.0, 0.0,
                            -2000.0, -2000.0, 0.0 };

  GLfloat texture_coords[] = { 0.0, 0.0,
                               1000.0, 0.0,
                               1000.0, 1000.0,
                               0.0, 1000.0 };

  glPushMatrix(); 
     
    glDisable(GL_LIGHTING);
   
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTranslatef(0.0, 0.0, 10.0);
   
    glBindTexture(GL_TEXTURE_2D, textures_map["stars"]);
    glVertexPointer(3, GL_FLOAT, 0, star_verts);
    glTexCoordPointer(2, GL_FLOAT, 0, texture_coords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glRotatef(90, 1.0, 0.0, 0.0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D); 

    glEnable(GL_LIGHTING);

  glPopMatrix();

}

void render_sun()
{
  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glEnable(GL_TEXTURE_2D);  

  GLUquadric *sun = gluNewQuadric();

  gluQuadricTexture(sun, GL_TRUE); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);    
  glBindTexture(GL_TEXTURE_2D, textures_map["sun"]);

  gluSphere(sun, 1, 100, 100); 

  gluDeleteQuadric(sun); 
  glDisable(GL_TEXTURE_2D);

  glPopAttrib();
  glPopMatrix();
}

#include "clock.hpp"
ClockT clockt;

#include "galaxy.hpp"
Galaxy galaxy;

void render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

    glPushMatrix();
      GLfloat sun_light_position0[] = { 0.0, 0.0, 0.0, 1.0 };
      glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position0);
    glPopMatrix();

    render_stars();

    glTranslatef(0, pedestal, -zoom);
    glRotatef(rotation, 0.0, 1.0, 0.0);
    glRotatef(pitch, 1.0, 0.0, 0.0);

    render_sun();

    galaxy.update(clockt.delta());
    galaxy.render();
   
  glPopMatrix();

  glutSwapBuffers();
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 'w')
  {
    zoom += 1;
  }

  if (key == 's')
  {
    zoom -= 1;
  }

  if (key == 'a')
  {
    rotation += 1;
  }

  if (key == 'd')
  {
    rotation -= 1;
  }

  if (key == 'e')
  {
    pedestal += 1;
  }

  if (key == 'q')
  {
    pedestal -= 1;
  }

  if (key == 'r')
  {
    pitch += 1;
  }

  if (key == 'f')
  {
    pitch -= 1;
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
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 10000000000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0, 50, -50.01, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);         
}

void data()
{  
  textures_map["stars"] = RawTexture::from_file(512, 512, "textures/stars.raw");
  textures_map["sun"] = RawTexture::from_file(1024, 512, "textures/sunmap.raw");
 
  galaxy.init();
}

void init()
{
  glClearColor(0.00, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  
  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);  
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv)
{
  std::clog << "starting" << std::endl;

  clockt.init();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_MULTISAMPLE);
  glutInitWindowSize(1280, 800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Import");

  std::clog << "init" << std::endl;

  init();
  data();
 
  std::clog << "running" << std::endl;

  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutFullScreen();
  glutMainLoop();

  std::clog << "closing" << std::endl;

  return 0;
}
