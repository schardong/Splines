/**
 * File: Scalar.hpp
 * Author: Guilherme Gonçalves Schardong
 * Defines the basic scalar number types.
 * File created on March 20, 2012, 10:04
 */

#ifndef __SCALAR_HPP__
#define __SCALAR_HPP__

#include "stdafx.hpp"

namespace CoreMath
{

#ifdef USE_DOUBLE_PRECISION
  typedef double Scalar;
#else
  typedef float Scalar;
#endif /* USE_DOUBLE_PRECISION */

}

#endif /* __SCALAR_HPP__ */
