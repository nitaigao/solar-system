class Camera
{

public:

  Camera() { };

  void pitch(float amount)
  {
    pitch_ += amount;
  }

  void rotate(float amount)
  {
    rotation_ += amount;
  }

  void zoom(float amount)
  {
    zoom_ += amount;
  }

  void strafe(float amount)
  {
    strafe_ += amount;
  }

  void pedestal(float amount)
  {
    pedestal_ += amount;
  }

  void render()
  {
    glTranslatef(strafe_, pedestal_, -zoom_);
    glRotatef(rotation_, 0.0, 1.0, 0.0);
    glRotatef(pitch_, 1.0, 0.0, 0.0);
  }

  private:

  int zoom_;
  int rotation_;
  int pedestal_;
  int pitch_;
  int strafe_;

};
