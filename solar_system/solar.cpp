#include <gl.h>
#include <glu.h>
#include <glut.h>

#include <iostream>

#include <string>
#include <deque>

int planet_scale = 1;
int distance_scale = 1;

class Planet
{  
public:

  typedef std::deque<Planet> PlanetList;

  Planet(unsigned int distance_from_parent, float year_length, float day_length, float diameter)
    : distance_from_parent_(distance_from_parent)
    , year_length_(year_length)
    , day_length_(day_length)
    , diameter_(diameter)
    , time_(0)
  {

  }  

  inline void add_child(const Planet& moon) { children_.push_back(moon); };

  inline void add_time(float time) 
  { 
    
    time_ += time; 
    if (time_ >= year_length_)
    {
      time_ = 0;
    }

    for(Planet::PlanetList::iterator m = children_.begin(); m != children_.end(); ++m)
    {
      (*m).add_time(time);
    }
  };

  inline float year_position() { return (((time_ / year_length_) * 100) * 360) / 100.0; };
  inline float day_position() { return  (((time_ / day_length_ ) * 100) * 360) / 100.0; };

  inline void render(float time)
  {
    add_time(time);

    glPushMatrix(); // planet
    glRotatef(year_position(), 0.0, 1.0, 0.0); // planet year rotation
    glTranslatef(distance_from_parent_ * distance_scale, 0.0, 0.0); // planet distance from sun

    for(PlanetList::iterator m = children_.begin(); m != children_.end(); ++m)
    {
       (*m).render(time);
    }

    glRotatef(day_position() * 0.01, 0.0, 1.0, 0.0); // planet day rotation
    glutWireSphere(diameter_ * planet_scale, 16, 16);

    glPopMatrix(); // end planet
  };

private:

  unsigned int distance_from_parent_;
  float year_length_;
  float day_length_;
  float diameter_;
  float time_;
  float day_time_;
  Planet::PlanetList children_;

};

Planet::PlanetList planets;

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix(); // scene
  
  static float time = 1;
  static float earth_time = 0.0;;
  earth_time += time;

  if (earth_time > 365)
  {
    earth_time = 0;
    std::clog << "year" << std::endl;
  }
  
  glPushMatrix(); // sun
  glutWireSphere(215 * 0.03/*planet_scale*/, 16, 16);
  glPopMatrix(); // end sun

  glPushMatrix();

  for(Planet::PlanetList::iterator p = planets.begin(); p != planets.end(); ++p)
  {
    (*p).render(time);
  }

  glPopMatrix();

  glPopMatrix(); // end scene

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
  gluLookAt (0.0, 1000, 20, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);        
}

void data()
{  
  Planet mercury = Planet(9, 87.96, 58.7, 0.8);
  planets.push_back(mercury);

  Planet venus = Planet(17, 224.68, 243, 1.9);
  planets.push_back(venus);

  Planet earth = Planet(23, 365.26, 1, 2);
  Planet moon = Planet(3, 365, 1, 0.12);
  earth.add_child(moon);
  planets.push_back(earth);

  Planet mars = Planet(35, 686.98, 1.026, 1);
  planets.push_back(mars);

  Planet jupiter = Planet(120,  11.862 * 365, 9.84 / 24.0, 21.6 * 0.2);
  planets.push_back(jupiter);

  Planet saturn = Planet(221, 29.456 * 365, 10.2 / 24.0, 18 * 0.2); 
  planets.push_back(saturn);

  Planet uranus = Planet(444, 84.07 * 365, 17.9 / 24.0, 7.3);
  planets.push_back(uranus);

  Planet neptune = Planet(696, 164.81 * 365, 19.1 / 24.0, 7);
  planets.push_back(neptune);

  Planet pluto = Planet(914, 247.7 * 365, 6.39 / 24.0, 0.5);
  planets.push_back(pluto);
}

int main(int argc, char** argv)
{
  std::clog << "starting" << std::endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1280, 800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Import");

  std::clog << "init" << std::endl;

  glClearColor(0.00, 0.0, 0.0, 0.0);

  data();
 
  std::clog << "running" << std::endl;

  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutFullScreen();
  glutMainLoop();

  std::clog << "closing" << std::endl;
}
