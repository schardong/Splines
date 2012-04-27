#include <iostream>
#include <vector>
#include <cstdlib>
#include <GL/glfw.h>
#include <GL/gl.h>
#include <CoreMath/Vector4.hpp>

#include "main.h"
#include "BezierCurve.h"
#include "BSplineCurve.h"
#include "BSplineSurface.h"

/**
 * References:
 * WATT, Alan, "3D Computer Graphics", 2nd Edition, 1993, pg 163 - 207.
 * http://mathworld.wolfram.com/B-Spline.html
 * http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-basis.html
 * http://en.wikipedia.org/wiki/Non-uniform_rational_B-spline
 * http://www.rhino3d.com/nurbs.htm
 * http://www.mactech.com/articles/develop/issue_25/schneider.html
 * http://cse.taylor.edu/~btoll/s99/424/res/ucdavis/CAGDNotes/Deboor-Cox-Calculation/Deboor-Cox-Calculation.html
 */

void initGL(int w, int h);
void initCurves();
void cbRender();
void cbReshape(int w, int h);
void cbKeyDown(int key, int action);
void cleanup();
void mainLoop();

BSplineCurve* bs = NULL;  //Standard b-spline.
BSplineCurve* bw = NULL;  //Rational b-spline (modified weights).
BSplineCurve* bk = NULL;  //Non-uniform b-spline (modified knot vector).
BSplineCurve* bb = NULL;  //Non-uniform rational b-spline (NURBS, both of the above).

int runlevel;
int g_desiredFPS = 30;

int main(int argc, char** argv)
{
  initGL(WIDTH, HEIGHT);
  initCurves();

  // BSplineSurface *s = new BSplineSurface(5, 5, 3, 3);
  // s->generateSurface();
  // delete s;

  mainLoop();
  return 0;
}

void initCurves()
{
  std::vector<CoreMath::Vector4> p;

  p.push_back(CoreMath::Vector4(100, 300, 0));
  p.push_back(CoreMath::Vector4(200, 200, 0));
  p.push_back(CoreMath::Vector4(400, 200, 0));
  p.push_back(CoreMath::Vector4(500, 400, 0));


  p.push_back(CoreMath::Vector4(700, 300, 0));
  p.push_back(CoreMath::Vector4(500, 100, 0));

  double knots[] = {0, 0, 0, 0, 1, 2, 3, 3, 3, 3};
  double weights[] = {1, 1, 5, 1, 6, 1};

  bs = new BSplineCurve(5, DEGREE);
  bs->setControlPoints(p);
  bs->generateCurve();
  bs->setColor(1, 0, 0, 0);

  bk = new BSplineCurve(5, DEGREE);
  bk->setControlPoints(p);
  bk->setKnotVector(knots);
  bk->generateCurve();
  bk->setColor(0, 0, 0, 0);

  bw = new BSplineCurve(5, DEGREE);
  bw->setControlPoints(p);
  bw->setWeights(weights);
  bw->generateCurve();
  bw->setColor(0, 0.7, 0, 0);

  bb = new BSplineCurve(5, DEGREE);
  bb->setControlPoints(p);
  bb->setKnotVector(knots);
  bb->setWeights(weights);
  bb->generateCurve();
  bb->setColor(0, 0, 0.9, 0);
}

void initGL(int w, int h)
{
  if(glfwInit() == GL_FALSE) {
    std::cerr << "ERROR: Failed to initialize GLFW." << std::endl;
    exit(1);
  }

  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, CTX_VERSION_MAJOR);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, CTX_VERSION_MINOR);

  if(CTX_VERSION_MAJOR >= 3) {
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  }

  if(glfwOpenWindow(WIDTH, HEIGHT, 0, 0, 0, 0, 8, 0, GLFW_WINDOW) == GL_FALSE) {
    std::cerr << "ERROR: Failed to open a GLFW window." << std::endl;
    exit(1);
  }

  glfwSetWindowTitle("Splines demo");
 
  /*if(CTX_VERSION_MAJOR >= 3) {
    if(gl3wInit()) {
      std::cerr << "ERROR: " << gl3wGetError() << std::endl;
      exit(1);
    }
    if(!gl3wIsSupported(CTX_VERSION_MAJOR, CTX_VERSION_MINOR)) {
      std::cerr << "ERROR: OpenGL " << CTX_VERSION_MAJOR << "." << CTX_VERSION_MINOR << " is not supported." << std::endl;
      exit(1);
    }
    }*/

  std::cout << "INFO: OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "INFO: OpenGL context renderer:" << glGetString(GL_RENDERER) << std::endl;
  std::cout << "INFO: OpenGL context vendor: " << glGetString(GL_VENDOR) << std::endl;
  if(CTX_VERSION_MAJOR >= 2)
    std::cout << "INFO: OpenGL shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glViewport(0, 0, WIDTH, HEIGHT);

  glPointSize(4.0);

  glfwSetKeyCallback(cbKeyDown);
  glfwSetWindowSizeCallback(cbReshape);
  runlevel = 1;
}

void cbRender()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WIDTH, 0, HEIGHT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if(bs != NULL) bs->render();
  if(bk != NULL) bk->render();
  if(bw != NULL) bw->render();
  if(bb != NULL) bb->render();

  glfwSwapBuffers();
}

void cbReshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void cbKeyDown(int key, int action)
{
  if(action == GLFW_PRESS) {
    switch(key) {
    case GLFW_KEY_ESC:
      runlevel = 0;
      break;
    }
  }
}

void cleanup()
{
  if(bs != NULL) delete bs;
  if(bk != NULL) delete bk;
  if(bw != NULL) delete bw;
  if(bb != NULL) delete bb;
  glfwTerminate();
  exit(0);
}

void mainLoop()
{
  double oldTime = glfwGetTime();
  while(1 && runlevel != 0) {
    double currTime = glfwGetTime();
    if(currTime - oldTime < 1 / g_desiredFPS)
      glfwSleep(currTime - oldTime);

    cbRender();
    glfwPollEvents();
    oldTime = currTime;
  }
  cleanup();
}
