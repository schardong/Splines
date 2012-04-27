/**
 * File: BSplineSurface.h
 * Author: Guilherme Gonçalves Schardong
 * Definition of the BSpline surface.
 * File created on 08 August 2011, 18:27
 */

#ifndef __BSPLINESURFACE_H__
#define __BSPLINESURFACE_H__

#include <vector>
#include <cstring>
#include <CoreMath/Vector4.hpp>

#include "main.h"
#include "BSplineCurve.h"

class BSplineSurface {
private:
    int m, n;
    int m_degreeU, m_degreeV;
    double* m_knotVectorU, *m_knotVectorV;
    double** m_weights;
    std::vector<std::vector<CoreMath::Vector4> > m_controlPoints;
    std::vector<CoreMath::Vector4> m_renderPoints;
    double m_color[4];

    /**
     * B - B-Spline blending function.
     * @returns: The Influence of the control point given the paramenter.
     * @i: i-th control point.
     * @n: Degree of the curve.
     * @u: Parameter.
     * @knotVector: The knot vector to be used.
     */
    double B(int i/*i-th patch*/, int n/*degree*/, double u/*paramater*/, double* knotVector) {
        if(n == 0) {
            if(u >= knotVector[i] && u < knotVector[i + 1])
                return 1.0;
            return 0.0;
        }
        double f = 0.0;
        double g = 0.0;
        if(knotVector[i + n] - knotVector[i] != 0)
            f = (u - knotVector[i]) / (knotVector[i + n] - knotVector[i]);
        if(knotVector[i + n + 1] - knotVector[i + 1] != 0)
            g = (knotVector[i + n + 1] - u) / (knotVector[i + n + 1] - knotVector[i + 1]);
        return f * B(i, n - 1, u, knotVector) + g * B(i + 1, n - 1, u, knotVector);
    }
public:
    BSplineSurface(int _m, int _n, int degreeU, int degreeV);
    ~BSplineSurface();

    inline std::vector<std::vector<CoreMath::Vector4> > getControlPoints() {
        return m_controlPoints;
    }

    inline double* getKnotVector(int index) {
        if(index == 0)
            return m_knotVectorU;
        return m_knotVectorV;
    }

    inline double** getWeights() {
        return m_weights;
    }

    inline void setControlPoints(std::vector<std::vector<CoreMath::Vector4> > controlPoints) {
        if(!controlPoints.empty())
            m_controlPoints = controlPoints;
    }

    inline void setKnotVector(int index, double* knots) {
        if(knots != NULL) {
            if(index == 0)
                memcpy(m_knotVectorU, knots, (m + m_degreeU + 1) * sizeof(double));
            else
                memcpy(m_knotVectorV, knots, (n + m_degreeV + 1) * sizeof(double));
        }
    }

    inline void setWeights(double** weights) {
        if(weights != NULL)
            memcpy(m_weights, weights, (m + 1) * (n + 1) * sizeof(double));
    }

    inline void setColor(double r, double g, double b, double a) {
        m_color[0] = r;
        m_color[1] = g;
        m_color[2] = b;
        m_color[3] = a;
    }

    void generateSurface();
    void render();
};

#endif // __BSPLINESURFACE_H__
