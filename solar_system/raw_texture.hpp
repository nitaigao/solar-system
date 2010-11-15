#include <gl.h>
#include <glu.h>
#include <glut.h>
#include <iostream>
#include <string>

class RawTexture
{

public:

  static GLint from_file(int width, int height, const std::string& filename)
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

private:

  static char* load_file(const std::string& filename)
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
};
