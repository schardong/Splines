/**
 * File: BezierCurve.cpp
 * Author: Guilherme Gonçalves Schardong
 * Implementation of the Bezier Curve class.
 * File created on 05 August 2011, 12:28
 */

#include <iostream>
#include <cstring>
#include <GL/glfw.h>
#include <GL/gl.h>

#include "BezierCurve.h"

BezierCurve::BezierCurve(int degree) : m_degree(degree) {}

BezierCurve::~BezierCurve()
{
  m_degree = 0;
  m_controlPoints.clear();
  m_renderPoints.clear();
}

void BezierCurve::generateCurve()
{
  for(double u = 0.0; u <= 1.0; u += INC) {
    double acc_x = 0.0;
    double acc_y = 0.0;
    for(int i = 0; i <= DEGREE; i++) {
      acc_x += m_controlPoints[i][0] * B(i, DEGREE, u);
      acc_y += m_controlPoints[i][1] * B(i, DEGREE, u);
    }
    m_renderPoints.push_back(CoreMath::Vector4(acc_x, acc_y, 0.0));
  }
}

void BezierCurve::render()
{
  //Render the curve.
  glColor4f(0.5, 0.0, 0.7, 0.0);
  glBegin(GL_LINES);
  for(unsigned int i = 1; i < m_renderPoints.size(); i++) {
    glVertex2f(m_renderPoints[i][0], m_renderPoints[i][1]);
    glVertex2f(m_renderPoints[i - 1][0], m_renderPoints[i - 1][1]);
  }
  glEnd();
}
