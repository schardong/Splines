/**
 * File: BSplineSurface.cpp
 * Author: Guilherme Gonçalves Schardong
 * Implemantation of the BSpline surface.
 * File created on 08 August 2011, 18:27
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "BSplineSurface.h"

BSplineSurface::BSplineSurface(int _m, int _n, int degreeU, int degreeV) : m(_m), n(_n), m_degreeU(degreeU), m_degreeV(degreeV) {
    m_knotVectorU = new double[m + m_degreeU + 1];
    m_knotVectorV = new double[n + m_degreeV + 1];
    for(int i = 0; i < m + degreeU + 1; i++)
        m_knotVectorU[i] = (double) i;
    for(int i = 0; i < n + degreeV + 1; i++)
        m_knotVectorV[i] = (double) i;
    m_weights = (double**) malloc((m + 1) * sizeof(double*));
    for(int i = 0; i < m + 1; i++)
        m_weights[i] = (double*) malloc((n + 1) * sizeof(double));
    memset(m_color, 0, 4 * sizeof(double));
}

BSplineSurface::~BSplineSurface() {
    m = n = 0;
    m_degreeU = m_degreeV = 0;
    m_controlPoints.clear();
    m_renderPoints.clear();
    for(int i = 0; i < m + 1; i++)
        free(m_weights[i]);
    free(m_weights);
    delete[] m_knotVectorU;
    delete[] m_knotVectorV;
}

void BSplineSurface::generateSurface() {
    if(m_renderPoints.empty() == false)
        m_renderPoints.clear();
    for(int segmentU = 0; segmentU <= m; segmentU++) {
        for(int segmentV = 0; segmentV <= n; segmentV++) {
            for(double u = m_knotVectorU[segmentU]; u <= m_knotVectorU[segmentU + 1]; u += INC) {
                for(double v = m_knotVectorV[segmentV]; u <= m_knotVectorV[segmentV + 1]; v += INC) {
                }
            }
        }
    }
}

void BSplineSurface::render() {
    //Render the control polygon.
    glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
    //Render the curve.
    glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    //Render the control points.
    glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
}
