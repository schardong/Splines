/**
 * File:   Vector4.h
 * Author: Guilherme Goncalves Schardong
 *
 * File created on December 18, 2010, 13:45 PM
 */

#ifndef __VECTOR4_HPP__
#define __VECTOR4_HPP__

#include "stdafx.hpp"
#include "Scalar.hpp"

namespace CoreMath
{

class Vector4
{
protected:
  Scalar m[4];
public:
  Vector4(Scalar x = 0.0, Scalar y = 0.0, Scalar z = 0.0, Scalar w = 1.0);
  Vector4(const Vector4& rhs);
  virtual ~Vector4();

  /**
   * norm: Returns the norm of the vector.
   * @returns: The norm of teh vector.
   */
  Scalar norm();

  /**
   * normalize: Normalizes the vector. Note: It modifies the caller,
   * so save its contents first.
   */
  void normalize();

  /**
   * normalized: Returns a normalized version of the caller vector.
   * It does not modify the caller.
   * @returns: A normalized vector.
   */
  Vector4 normalized();

  /**
   * operator[]: Access operator.
   * @returns: The element at a given position.
   */
  inline Scalar& operator [](unsigned int i)
  {
    return m[i];
  }

  /**
   * operator <<: Assigns the vector to an ostream.
   * @returns: The stream containing the vector.
   */
  inline friend std::ostream& operator <<(std::ostream& _stream, const Vector4& rhs)
  {
    _stream << rhs.m[0] << " " << rhs.m[1] << " " << rhs.m[2] << " " << rhs.m[3];
    return _stream;
  }

  /**
   * operator =: Assignment operator.
   * @rhs - The source vector.
   * @returns - The destination vector.
   */
  Vector4& operator =(const Vector4& rhs);

  /**
   * operator +: Sum of vectors.
   * @rhs: The vector to be added.
   * @returns: The vector containing the sum of *this and rhs.
   */
  Vector4 operator +(Vector4& rhs);

  /**
   * operator -: Difference of vectors.
   * @rhs: The vector to be subtracted.
   * @returns: The result of *this - rhs.
   */
  Vector4 operator -(Vector4& rhs);

  /**
   * operator -: Computes the conjugate of the vector
   * @returns: The conjugated vector.
   */
  Vector4& operator -();

  /**
   * operator *: Scalar product.
   * @rhs: The second vector.
   * @returns: The scalar product between the caller and rhs.
   */
  Scalar operator *(Vector4& rhs);

  /**
   * operator *: Component wise product of a vector by a scalar.
   * @rhs: The scalar.
   * @returns: The result of *this * rhs.
   */
  Vector4 operator *(const Scalar rhs);

  /**
   * operator ^: Vector product.
   * @rhs: The second vector.
   * @returns: The vector product between the caller and rhs.
   */
  Vector4 operator ^(Vector4& rhs);

  /**
   * operator ==: Test wheter the vectors are the same.
   * @rhs: The vector to be tested.
   * @returns: true if the vectors are the same or false otherwise.
   */
  bool operator ==(Vector4& rhs);

  /**
   * operator !=: Test wheter the vectors are different
   * @rhs: The vector to be tested.
   * @returns: true if the vectors are different or false otherwise.
   */
  bool operator !=(Vector4& rhs);
};

}

#endif /* __VECTOR4_HPP__ */
