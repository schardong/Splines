/**
 * File: BSplineCurve.cpp
 * Author: Guilherme Gonçalves Schardong
 * Implementation of the BSplineCurve class.
 * File created on 05 August 2011, 12:28
 */

#include <iostream>
#include <cstring>
#include <GL/glfw.h>
#include <GL/gl.h>

#include "BSplineCurve.h"

BSplineCurve::BSplineCurve(int _m, int degree) : m(_m), m_degree(degree)
{
  m_knotVector = new double[m + degree + 1];
  m_weights = new double[m + 1];
  for(int i = 0; i < m + degree + 1; i++)
    m_knotVector[i] = (double) i;
  for(int i = 0; i < m + 1; i++)
    m_weights[i] = 1.0;
  memset(m_color, 0, 4 * sizeof(double));
}

BSplineCurve::~BSplineCurve()
{
  m = 0;
  m_degree = 0;
  m_controlPoints.clear();
  m_renderPoints.clear();
  delete[] m_knotVector;
  delete[] m_weights;
}

void BSplineCurve::generateCurve()
{
  if(m_renderPoints.empty() == false)
    m_renderPoints.clear();
  for(int curveSegment = m_degree; curveSegment <= m; curveSegment++) { //para cada segmento de curva.
    for(double u = m_knotVector[curveSegment]; u <= m_knotVector[curveSegment + 1]; u += INC) { //para cada nó pertencente a curva.
      double acc_x = 0.0;
      double acc_y = 0.0;
      double acc_z = 0.0;
      double r = 0.0; //Fator de normalizacao dos pesos. Eh 1 se todos os pesos forem 1.
      for(int i = curveSegment - m_degree; i <= curveSegment; i++) { //para cada ponto de controle que influencia esse segmento.
	acc_x += m_controlPoints[i][0] * m_weights[i] * B(i, m_degree, u);
	acc_y += m_controlPoints[i][1] * m_weights[i] * B(i, m_degree, u);
	acc_z += m_controlPoints[i][2] * m_weights[i] * B(i, m_degree, u);
	r += m_weights[i] * B(i, m_degree, u);
      }
      m_renderPoints.push_back(CoreMath::Vector4(acc_x / r, acc_y / r, acc_z / r));
    }
  }
}

void BSplineCurve::render()
{
  //Render the control polygon.
  glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
  glBegin(GL_LINES);
  for(unsigned int i = 1; i < m_controlPoints.size(); i++) {
    glVertex2f(m_controlPoints[i][0], m_controlPoints[i][1]);
    glVertex2f(m_controlPoints[i - 1][0], m_controlPoints[i - 1][1]);
  }
  glEnd();
  //Render the curve.
  glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
  glBegin(GL_LINES);
  for(unsigned int i = 1; i < m_renderPoints.size(); i++) {
    glVertex2f(m_renderPoints[i][0], m_renderPoints[i][1]);
    glVertex2f(m_renderPoints[i - 1][0], m_renderPoints[i - 1][1]);
  }
  glEnd();
  //Render the control points.
  glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
  glBegin(GL_POINTS);
  for(unsigned int i = 0; i < m_controlPoints.size(); i++)
    glVertex2f(m_controlPoints[i][0], m_controlPoints[i][1]);
  glEnd();
}
