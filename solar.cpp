#include <gl.h>
#include <glu.h>
#include <glut.h>

#include <iostream>

#include <string>
#include <deque>

class Planet
{

  std::string name_;
  float distance_from_sun_;
  float year_length_;
  float day_length_;
  float diameter_;
  float year_time_;
  float day_time_;

public:

  Planet(const std::string& name, float distance_from_sun, float year_length, float day_length, float diameter)
    : name_(name)
    , distance_from_sun_(distance_from_sun)
    , year_length_(year_length)
    , day_length_(day_length)
    , diameter_(diameter)
  {

  }

  inline float distance_from_sun() { return distance_from_sun_; };
  inline float diameter() { return diameter_; };
  inline float year_length() { return year_length_; };
  
  inline void add_year_time(float time) { year_time_ += time; year_time_ = (year_time_ > year_length_) ? 0 : year_time_; };
  inline float year_position() { return year_time_ / year_length_; };
  
  inline void add_day_time(float time) { day_time_ += time; day_time_ = (day_time_ > day_length_) ? 0 : day_time_; };
  inline float day_position() { return day_time_ / day_length_; };
};

typedef std::deque<Planet> PlanetList;

PlanetList planets;

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  //glLoadIdentity();

  glTranslatef(0.0, 0.0, -200.0);

  static float time = 0.01;

  glPushMatrix(); // sun
  glutWireSphere(1.39198, 16, 16);
  glPopMatrix();

  for(PlanetList::iterator i = planets.begin(); i != planets.end(); ++i)
  {
    (*i).add_day_time(time);
    (*i).add_year_time(time);
    glPushMatrix();
    glRotatef((*i).year_position() * 360, 0.0, 1.0, 0.0); // year rotation
    glTranslatef((*i).distance_from_sun(), 0.0, 0.0); // distance from sun
    glRotated((*i).day_position() * 360, 0.0, 1.0, 0.0); // day rotation
    glutWireSphere((*i).diameter(), 16, 16);
    glPopMatrix();
  }

  glPopMatrix();

  glutSwapBuffers();
  glutPostRedisplay();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 1000.0);
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  gluLookAt (0.0, 200.0, 200.0, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);        
}

void data()
{  
  // (const std::string& name, float distance_from_sun, float year_length, float day_length, float diameter)
  Planet mercury = Planet("Mercury", 57.9, 87.96, 58.7, 4.878);
  planets.push_back(mercury);

  Planet venus = Planet("Venus", 108.2, 224.68, 243, 12.104);
  planets.push_back(venus);

  Planet earth = Planet("Earth", 149.6, 365.26, 1.0 / 24.0, 12.756);
  planets.push_back(earth);

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

  data();
 
  std::clog << "running" << std::endl;

  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutMainLoop();

  std::clog << "closing" << std::endl;
}
