#include <deque>

class Galaxy
{

public:

  Galaxy() { };

  void update(float delta)
  {
     for(Planet::PlanetList::iterator p = planets.begin(); p != planets.end(); ++p)
     {
       (*p).add_time(delta);
     }     
  }

  void render()
  {
    glPushMatrix(); // scene
         
      for(Planet::PlanetList::iterator p = planets.begin(); p != planets.end(); ++p)
      {
        (*p).render();
      }

    glPopMatrix(); // end scene
  }

  void init()
  {
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

private:
  
  std::deque<Planet> planets;

};
