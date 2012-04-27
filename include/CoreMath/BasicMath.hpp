/**
 * File: BasicMath.hpp
 * Author: Guilherme Goncalves Schardong
 * File created on December 29, 2011, 19:09
 */

#ifndef __BASICMATH_HPP__
#define __BASICMATH_HPP__

#include "stdafx.hpp"
#include "Scalar.hpp"

namespace CoreMath
{

/**
 * Standard constants.
 */
static const Scalar PI = (Scalar) 3.14159265358979323846264338327950288419716939937510;
static const Scalar DEGRADRATIO = (Scalar) 0.01745329251994329576923690768489;

/**
 * Basic trigonometric functions.
 */
inline Scalar Sine(Scalar x) { return std::sin(x); }
inline Scalar Cosine(Scalar x) { return std::cos(x); }
inline Scalar Tangent(Scalar x) { return std::tan(x); }
inline Scalar ArcSine(Scalar x) { return std::asin(x); }
inline Scalar ArcCosine(Scalar x) { return std::acos(x); }
inline Scalar ArcTangent(Scalar x) { return std::atan(x); }
inline Scalar Secant(Scalar x) { return 1 / Sine(x); }
inline Scalar Cosecant(Scalar x) { return 1 / Cosine(x); }
inline Scalar Cotangent(Scalar x) { return 1 / Tangent(x); }

/**
 * Angle convertions.
 */
inline Scalar DegToRad(Scalar x) { return DEGRADRATIO * x; }
inline Scalar RadToDeg(Scalar x) { return x / DEGRADRATIO; }

/**
 * Power functions.
 */
inline Scalar SquareRoot(Scalar x) { return std::sqrt(x); }
inline Scalar Power(Scalar x, Scalar y) { return std::pow(x, y); }

/**
 * Misc. functions.
 */
inline Scalar Abs(Scalar x) { return std::fabs(x); }
inline Scalar Floor(Scalar x) { return std::floor(x); }
inline Scalar Ceil(Scalar x) { return std::ceil(x); }

}

#endif /* __BASICMATH_HPP__ */
