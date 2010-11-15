#include <gl.h>
#include <glu.h>
#include <glut.h>

#include <iostream>

#include <string>
#include <deque>
#include <map>
#include <sys/time.h>

GLuint textures[5];
std::map<std::string, GLuint> textures_map;

char* load_file(const std::string& filename)
{
  FILE *file = fopen(filename.c_str(), "rb");
 
  fseek (file , 0 , SEEK_END);
  unsigned int data_size  = ftell (file);
  rewind (file);

  char* data = new char[data_size];
  fread(data, data_size, 1, file);

  fclose(file);
  return data;
}

GLint load_texture(int width, int height, const std::string& filename)
{
  char* tex_data = load_file(filename);

  GLuint texture;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
  delete[] tex_data;
  return texture;
}


#include "planet.hpp"

typedef long long int64;
static struct timeval start_time;

void init_time() {
  gettimeofday(&start_time, NULL);
}

int64 get_time() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (int64) (t.tv_sec - start_time.tv_sec) * 1000000 + (t.tv_usec - start_time.tv_usec);
}

int zoom = 0;
int rotation = 0;
int pedestal = 0;
int pitch = 0;
int64 last_time = 0;

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

void render()
{
  int64 start_time = get_time();
  float delta_time = (start_time - last_time) / 1000000.0;
  last_time = start_time;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

    glPushMatrix();
      GLfloat sun_light_position0[] = { 0.0, 0.0, 0.0, 1.0 };
      glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position0);
    glPopMatrix();

    render_stars();

    glTranslatef(0, pedestal, -zoom);//-zoom, -zoom);
    glRotatef(rotation, 0.0, 1.0, 0.0);
    glRotatef(pitch, 1.0, 0.0, 0.0);

    render_sun();
   
    glPushMatrix(); // scene

        for(Planet::PlanetList::iterator p = planets.begin(); p != planets.end(); ++p)
        {
              (*p).render(delta_time);
        }

    glPopMatrix(); // end scene

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
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 10000000000000000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0.0, 100, -0.001, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);       
  
}

void data()
{  
  textures_map["stars"] = load_texture(512, 512, "/Users/nk/Desktop/stars.raw");
  textures_map["sun"] = load_texture(1024, 512, "/Users/nk/Desktop/sunmap.raw");
  textures_map["mercury"] = load_texture(1024, 512, "/Users/nk/Desktop/mercurymap.raw");
  textures_map["venus"] = load_texture(1024, 512, "/Users/nk/Desktop/venusmap.raw");

  Planet mercury = Planet("mercury", 9, 87.96, 58.7, 0.8);
  planets.push_back(mercury);

  Planet venus = Planet("venus", 17, 224.68, 243, 1.9);
  planets.push_back(venus);

  Planet earth = Planet("mercury", 23, 365.26, 1, 2);
  Planet moon = Planet("moon", 3, 100000000000000, 0, 0.12); // infinate moon orbit
  earth.add_child(moon);
  planets.push_back(earth);

  Planet mars = Planet("mercury", 35, 686.98, 1.026, 1);
  planets.push_back(mars);

  Planet jupiter = Planet("mercury", 120,  11.862 * 365, 9.84 / 24.0, 21.6 * 0.2);
  planets.push_back(jupiter);

  Planet saturn = Planet("mercury", 221, 29.456 * 365, 10.2 / 24.0, 18 * 0.2); 
  planets.push_back(saturn);

  Planet uranus = Planet("mercury", 444, 84.07 * 365, 17.9 / 24.0, 7.3);
  planets.push_back(uranus);

  Planet neptune = Planet("mercury", 696, 164.81 * 365, 19.1 / 24.0, 7);
  planets.push_back(neptune);

  Planet pluto = Planet("mercury", 914, 247.7 * 365, 6.39 / 24.0, 0.5);
  planets.push_back(pluto);
}

void init()
{
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

  init_time();
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_MULTISAMPLE);
  glutInitWindowSize(1280, 800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Import");

  std::clog << "init" << std::endl;

  glClearColor(0.00, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);

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
