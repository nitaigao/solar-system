#include <gl.h>
#include <glu.h>
#include <glut.h>
#include <stdio.h>
#include <string>
#include <iostream>

/*public*/
int printOglError(const char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

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

void render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  glutSolidCube(1.0);

  // GLfloat vertices[] = {  1.0,  1.0, 0.0,
  //                          1.0, -1.0, 0.0,
  //                         -1.0,  1.0, 0.0,
  //                         -1.0, -1.0, 0.0 };


  // glEnableClientState(GL_VERTEX_ARRAY);
  // glVertexPointer(3, GL_FLOAT, 0, vertices);
  // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  // glDisableClientState(GL_VERTEX_ARRAY);

  glPopMatrix();

  GLfloat light_position[] = { 0.0, 0.0, 10.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glutSwapBuffers();
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{

}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0, 0.0, -10, 
             0.0, 0.0, 0.0, 
             0.0, 1.0, 0.0);         
}

void compile_shader(GLuint shader)
{
  glCompileShader(shader);
  printOpenGLError();

  GLint compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled) {
    std::cerr << "shader compilation fail" << std::endl;
  }
}

void load_shader(const char *vert, const char *frag)
{
  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vert_shader, 1, &vert, NULL);
  glShaderSource(frag_shader, 1, &frag, NULL);

  compile_shader(vert_shader);
  compile_shader(frag_shader);

  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vert_shader);
  glAttachShader(shader_program, frag_shader);

  glLinkProgram(shader_program);
  printOpenGLError();

  GLint linked;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &linked);

  if (!linked) {
    std::clog << "shader link fail" << std::endl;
  }

  glUseProgram(shader_program);
}

void init()
{
  char* vert_shader = load_file("shader.vert");
  char* frag_shader = load_file("shader.frag");

  load_shader(vert_shader, frag_shader);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); 

  glClearColor(0.00, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_MULTISAMPLE);
  glutInitWindowSize(1280, 800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Import");

  init();

  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutFullScreen();

  glutMainLoop();

  return 0;
}
