/**
 * File: BSplineCurve.h
 * Author: Guilherme Gonçalves Schardong
 * Definition of the BSplineCurve class.
 * File created on 05 August 2011, 12:28
 */

#ifndef __BSPLINECURVE_H__
#define __BSPLINECURVE_H__

#include <vector>
#include <cstring>
#include <CoreMath/Vector4.hpp>

#include "main.h"

class BSplineCurve {
private:
  int m;
  int m_degree;
  double* m_knotVector;
  double* m_weights;
  std::vector<CoreMath::Vector4> m_controlPoints;
  std::vector<CoreMath::Vector4> m_renderPoints;
  double m_color[4];

  /**
   * B - B-Spline blending function.
   * @returns: The Influence of the control point given the paramenter.
   * @i: i-th control point.
   * @n: Degree of the curve.
   * @u: Parameter.
   */
  double B(int i/*i-th patch*/, int n/*degree*/, double u/*paramater*/)
  {
    if(n == 0) {
      if(u >= m_knotVector[i] && u < m_knotVector[i + 1])
	return 1.0;
      return 0.0;
    }
    double f = 0.0;
    double g = 0.0;
    if(m_knotVector[i + n] - m_knotVector[i] != 0)
      f = (u - m_knotVector[i]) / (m_knotVector[i + n] - m_knotVector[i]);
    if(m_knotVector[i + n + 1] - m_knotVector[i + 1] != 0)
      g = (m_knotVector[i + n + 1] - u) / (m_knotVector[i + n + 1] - m_knotVector[i + 1]);
    return f * B(i, n - 1, u) + g * B(i + 1, n - 1, u);
  }
public:
  BSplineCurve(int _m, int degree);
  ~BSplineCurve();

  inline std::vector<CoreMath::Vector4> getControlPoints()
  {
    return m_controlPoints;
  }

  inline double* getKnotVector()
  {
    return m_knotVector;
  }
  
  inline double* getWeights()
  {
    return m_weights;
  }
  
  inline void setControlPoints(std::vector<CoreMath::Vector4> controlPoints)
  {
    if(!controlPoints.empty())
      m_controlPoints = controlPoints;
  }

  inline void setKnotVector(double* knots)
  {
    if(knots != NULL)
      memcpy(m_knotVector, knots, (m + m_degree + 1) * sizeof(double));
  }

  inline void setWeights(double* weights)
  {
    if(weights != NULL)
      memcpy(m_weights, weights, (m + 1) * sizeof(double));
  }

  inline void setColor(double r, double g, double b, double a)
  {
    m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
    m_color[3] = a;
  }

  void generateCurve();
  void render();
};

#endif /* __BSPLINECURVE_H__ */
