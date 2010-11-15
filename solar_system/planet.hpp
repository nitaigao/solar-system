class Planet
{  
public:

  typedef std::deque<Planet> PlanetList;

  Planet(const std::string& name, unsigned int distance_from_parent, float year_length, float day_length, float diameter)
    : distance_from_parent_(distance_from_parent)
    , year_length_(year_length)
    , day_length_(day_length)
    , diameter_(diameter)
    , time_(0)
    , name_(name)
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

  inline void render(float delta_time)
  {
    glPushMatrix(); // planet
    glPushAttrib(GL_ALL_ATTRIB_BITS);
      add_time(delta_time);
    
      glRotatef(year_position() * 1, 0.0, 1.0, 0.0); // planet year rotation
      glTranslatef(0.0, 0.0, distance_from_parent_); // planet distance from sun

      for(Planet::PlanetList::iterator p = children_.begin(); p != children_.end(); ++p)
      {
        (*p).render(delta_time);
      }

      glEnable(GL_TEXTURE_2D);  

      GLUquadric *planet = gluNewQuadric();

      gluQuadricTexture(planet, GL_TRUE); 
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);    
      glBindTexture(GL_TEXTURE_2D, textures_map[name_]);

      gluSphere(planet, diameter_, 100, 100); 

      gluDeleteQuadric(planet); 
      glDisable(GL_TEXTURE_2D);
      
      glPopAttrib();
    glPopMatrix(); // end planet
  };

private:

  unsigned int distance_from_parent_;
  float year_length_;
  float day_length_;
  float diameter_;
  float time_;
  float day_time_;
  std::string name_;
  Planet::PlanetList children_;

};

Planet::PlanetList planets;
