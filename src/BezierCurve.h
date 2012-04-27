/**
 * File: BezierCurve.h
 * Author: Guilherme Gonçalves Schardong
 * Definition of the BezierCurve class.
 * File created on 05 August 2011, 12:28
 */

#ifndef __BEZIERCURVE_H__
#define __BEZIERCURVE_H__

#include <vector>
#include <cmath>
#include <CoreMath/Vector4.hpp>

#include "main.h"

class BezierCurve
{
private:
  int m_degree;
  std::vector<CoreMath::Vector4> m_controlPoints;
  std::vector<CoreMath::Vector4> m_renderPoints;

  double fatorial(int n)
  {
    if(n <= 1)
      return 1;
    return n * fatorial(n - 1);
  }

  double C(int n, int i)
  {
    return fatorial(n) / (fatorial(i) * fatorial(n - i));
  }

  double B(int i, int n, double u)
  {
    return C(n, i) * pow(u, i) * pow(1 - u, n - i);
  }
public:
  BezierCurve(int degree);
  ~BezierCurve();

  std::vector<CoreMath::Vector4> getContolPoints()
  {
    return m_controlPoints;
  }

  inline void setControlPoints(std::vector<CoreMath::Vector4> controlPoints)
  {
    m_controlPoints = controlPoints;
  }

  void generateCurve();
  void render();
};

#endif /* __BEZIERCURVE_H__ */
