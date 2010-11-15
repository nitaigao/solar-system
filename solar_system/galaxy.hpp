#include <deque>
#include "raw_texture.hpp"
#include "planet.hpp"

class Galaxy
{

public:

  Galaxy() { };

  void update(float delta)
  {
     for(Planet::PlanetList::iterator p = planets.begin(); p != planets.end(); ++p)
     {
       (*p).add_time(delta * time_modifier_);
     }     
  }

  void time(int modifier)
  {
    time_modifier_ = modifier;
  }

  void render()
  {
    glPushMatrix(); // scene

      render_sun();
         
      for(Planet::PlanetList::iterator p = planets.begin(); p != planets.end(); ++p)
      {
        (*p).render();
      }

    glPopMatrix(); // end scene
  }

  void init()
  {
    stars_texture = RawTexture::from_file(512, 512, "textures/stars.raw");
    sun_texture = RawTexture::from_file(1024, 512, "textures/sunmap.raw");

    Planet mercury = Planet("mercury", 9, 87.96, 58.7, 0.8);
    planets.push_back(mercury);

    Planet venus = Planet("venus", 17, 224.68, 243, 1.9);
    planets.push_back(venus);

    Planet earth = Planet("earth", 23, 365.26, 1, 2);
    Planet moon = Planet("moon", 3, 100000000000000, 0, 0.12); // infinate moon orbit
    earth.add_child(moon);
    planets.push_back(earth);

    Planet mars = Planet("mars", 35, 686.98, 1.026, 1);
    planets.push_back(mars);

    Planet jupiter = Planet("jupiter", 120,  11.862 * 365, 9.84 / 24.0, 21.6 * 0.2);
    planets.push_back(jupiter);

    Planet saturn = Planet("saturn", 221, 29.456 * 365, 10.2 / 24.0, 18 * 0.2); 
    planets.push_back(saturn);

    Planet uranus = Planet("uranus", 444, 84.07 * 365, 17.9 / 24.0, 7.3);
    planets.push_back(uranus);

    Planet neptune = Planet("neptune", 696, 164.81 * 365, 19.1 / 24.0, 7);
    planets.push_back(neptune);

    Planet pluto = Planet("pluto", 914, 247.7 * 365, 6.39 / 24.0, 0.5);
    planets.push_back(pluto);

    for(Planet::PlanetList::iterator p = planets.begin(); p != planets.end(); ++p)
    {
      (*p).init();
    }
  }

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

    glTranslatef(0.0, 0.0, 1000.0);

    glBindTexture(GL_TEXTURE_2D, stars_texture);
    glVertexPointer(3, GL_FLOAT, 0, star_verts);
    glTexCoordPointer(2, GL_FLOAT, 0, texture_coords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glRotatef(90, 1.0, 0.0, 0.0);
    //  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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
    glBindTexture(GL_TEXTURE_2D, sun_texture);

    gluSphere(sun, 1, 100, 100); 

    gluDeleteQuadric(sun); 
    glDisable(GL_TEXTURE_2D);

    glPopAttrib();
    glPopMatrix();
  }

private:
  
  std::deque<Planet> planets;

  GLuint stars_texture;
  GLuint sun_texture;
  int time_modifier_;

};
