#include <gl.h>
#include <glu.h>
#include <glut.h>

#include <iostream>

#include <string>
#include <deque>

GLuint textures[5];

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

void load_texture(GLuint* texture, int size, const std::string& filename)
{
  char* tex_data = load_file(filename);

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, size, size, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
  delete[] tex_data;
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 0.0, 0.0, 1.0);

  glPushMatrix(); // scene

  static GLfloat box_vertices[] = {   1.0,  1.0, 0.0,
                                      1.0, -1.0, 0.0, 
                                     -1.0,  1.0, 0.0,
                                     -1.0, -1.0, 0.0 };

  static GLfloat stars_vertices[] = {   100.0,  100.0, 0.0,
                                        100.0, -100.0, 0.0, 
                                       -100.0,  100.0, 0.0,
                                       -100.0, -100.0, 0.0 };


  static GLfloat texture_coords[] = { 0.0, 0.0,
                                      100.0, 0.0,
                                      100.0, 100.0,
                                      0.0, 100.0 };

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat[]){1.0, 1.0, 1.0, 0.0});

  glTranslatef(0.0, 0.0, 100.0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  // glBindTexture(GL_TEXTURE_2D, textures[0]);
  // glTexCoordPointer(2, GL_FLOAT, 0, texture_coords);
  // glVertexPointer(3, GL_FLOAT, 0, box_vertices);
  // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glTexCoordPointer(2, GL_FLOAT, 0, texture_coords);
  glVertexPointer(3, GL_FLOAT, 0, stars_vertices);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_TEXTURE_2D);
  
  glPopMatrix(); // end scene

  glutSwapBuffers();
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 'q') 
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
  gluLookAt (0.0, 0, -5, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);        
}

void data()
{  
  load_texture(&textures[0], 512, "/Users/nk/Desktop/stars.raw");
  load_texture(&textures[1], 512, "/Users/nk/Desktop/stars.raw");
}

int main(int argc, char** argv)
{
  std::clog << "starting" << std::endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
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
