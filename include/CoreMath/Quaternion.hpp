/**
 * File: Quaternion.hpp
 * Author: Guilherme Gonçalves Schardong
 * File created on December 29, 2011, 19:08
 */

#ifndef __QUATERINON_HPP__
#define __QUATERINON_HPP__

#include "stdafx.hpp"
#include "Scalar.hpp"

namespace CoreMath
{

class Quaternion
{
protected:
  Scalar m[4];
public:
  Quaternion(Scalar _w = 0.0, Scalar _x = 0.0, Scalar _y = 0.0, Scalar _z = 0.0);
  Quaternion(const Quaternion& rhs);
  virtual ~Quaternion(void);

  /**
   * norm: Calculates the norm of the quaternion. SquareRoot(m[0] * m[0] + m[1] * m[1] + m[2] * m[2] + m[3] * m[3])
   * @return: The norm of the quaternion.
   */
  Scalar norm();

  /**
   * normalize: Normalize the quaternion.
   */
  void normalize();

  /**
   * normalized: Returns a normalized version of the caller quaternion.
   * It does not modify the caller.
   * @returns: A normalized quaternion.
   */
  Quaternion normalized();

  /**
   * loadIdentity: Makes m[0] = 1 and m[1] = m[2] = m[3] = 0.
   */
  void loadIdentity();

  /**
   * operator[]: Access operator.
   * @returns: The element at a given position.
   */
  inline Scalar& operator[](int i)
  {
    return m[i];
  }

  /**
   * operator <<: Assigns the quaternion to an ostream.
   * @returns: The stream containing the quaternion.
   */
  inline friend std::ostream& operator <<(std::ostream& _stream, const Quaternion& rhs)
  {
    _stream << rhs.m[0] << " ";
    if(rhs.m[1] >= 0)
      _stream << "+";
    _stream << rhs.m[1] << "i ";
    if(rhs.m[2] >= 0)
      _stream << "+";
    _stream << rhs.m[2] << "j ";
    if(rhs.m[3] >= 0)
      _stream << "+";
    _stream << rhs.m[3];
    return _stream;
  }

  /**
   * operator =: Assignment operator.
   * @rhs - The source quaternion.
   * @returns - The destination quaternion.
   */
  Quaternion& operator =(const Quaternion& rhs);

  /**
   * operator +: Sum of quaternions.
   * @rhs: The quaternion to be added.
   * @returns: The quaternion containing the sum of *this and rhs.
   */
  Quaternion operator +(const Quaternion& rhs);
  
  /**
   * operator -: Difference of quaternions.
   * @rhs: The quaternion to be subtracted.
   * @returns: The result of *this - rhs.
   */
  Quaternion operator -(Quaternion& rhs);

  /**
   * operator -: Computes the conjugate of the quaternion
   * @returns: The conjugated quaternion.
   */
  Quaternion& operator -();

  /**
   * operator *: Quaternion product.
   * @rhs: The quaternion to bem multiplicated.
   * @returns: The resulting quaternion of *this * rhs.
   */
  Quaternion operator *(Quaternion& rhs);

  /**
   * operator *: Component wise product of a quaternion by a scalar.
   * @rhs: The scalar.
   * @returns: The result of *this * rhs.
   */
  Quaternion operator *(Scalar rhs);

  /**
   * operator /: Quaternion division.
   * @rhs: The quaternion to serve as denominator.
   * @returns: The resulting quaternion *this / rhs.
   */
  Quaternion operator /(Quaternion& rhs);

  /**
   * operator /: Component wise division of a quaternion by a scalar.
   * @rhs: The scalar to serve as denominator.
   * @returns: The resulting quaternion of *this / rhs.
   */
  Quaternion operator /(Scalar rhs);

  /**
   * operator ==: Test wheter the quaternions are the same.
   * @rhs: The quaternion to be tested.
   * @returns: true if the quaternions are the same or false otherwise.
   */
  bool operator ==(Quaternion& rhs);

  /**
   * operator !=: Test wheter the quaternions are different
   * @rhs: The quaternion to be tested.
   * @returns: true if the quaternions are different or false otherwise.
   */
  bool operator !=(Quaternion& rhs);
};

/**
 * dot: Computes the dot product between two quaternions.
 * @q1: The first quaternion.
 * @q2: The second quaternion.
 * @returns: The dot product between q1 and q2.
 */
Scalar dot(Quaternion q1, Quaternion q2);

/**
 * lerp - Linear interpolation: Computes the linear interpolation
 * between q1 and q2 given the parameter t.
 * @q1: The first quaternion. Must be normalized.
 * @q2: The second quaternion. Must be normalized.
 * @t: The parameter. Must be between 0 and 1.
 */
Quaternion lerp(Quaternion q1, Quaternion q2, const Scalar t);

/**
 * slerp - Spherical linear interpolation: Computes the spherical
 * linear interpolation between q1 and q2 given the parameter t.
 * @q1: The first quaternion. Must be normalized.
 * @q2: The second quaternion. Must be normalized.
 * @t: The parameter. Must be between 0 and 1.
 */
Quaternion slerp(Quaternion q1, Quaternion q2, const Scalar t);

}

#endif /* __QUATERNION_HPP__ */
