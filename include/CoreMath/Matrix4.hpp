/**
 * File:   Matrix4.h
 * Author: Guilherme Goncalves Schardong
 *
 * File created on December 18, 2010, 12:47 PM
 */

#ifndef __MATRIX4_HPP__
#define __MATRIX4_HPP__

#include <assert.h>
#include "stdafx.hpp"
#include "Scalar.hpp"
#include "Vector4.hpp"

namespace CoreMath {

class Matrix4 {
protected:
  Scalar m[16];
public:
  Matrix4();
  Matrix4(const Matrix4& rhs);
  virtual ~Matrix4();

  /**
   * loadIdentity: Changes the matrix to the Identity.
   */
  void loadIdentity();

  /**
   * transpose: Transposes the caller matrix. This method alters the
   * matrix.
   */
  void transpose();

  /**
   * operator[]: Returns a pointer to a line of the matrix to be
   * accessed.
   * @i: The index of the line.
   * @returns: The pointer to a line of the matrix.
   */
  inline Scalar* operator [](int i) const
  {
    return (Scalar*)m + i * 4;
  }

  /**
   * operator <<: Assigns the matrix to an ostream.
   * @returns: The stream containing the matrix data.
   */
  inline friend std::ostream& operator <<(std::ostream& _stream, const Matrix4& rhs)
  {
    for(int i = 0, j = 0; i < 16; i++, j++)
    {
      if(j > 3)
      {
        _stream << "\n";
        j = 0;
      }
      _stream << rhs.m[i] << " ";
    }
    return _stream;
  }

  /**
   * getData: Returns a pointer to the memory containing the matrix
   * values.
   * @returns: A pointer to the matrix.
   */
  inline Scalar* getData()
  {
    return m;
  }

  /**
   * getLine: Returns a line of the matrix as a vector.
   * @line: The line to be returned.
   * @returns: A Vector4 containing the line of the matrix.
   */
  inline Vector4 getLine(const int line)
  {
    assert(line >= 0 && line < 4);
    return Vector4((*this)[line][0], (*this)[line][1], (*this)[line][2], (*this)[line][3]);
  }

  /**
   * getColumn: Returns a column of the matrix as a vector.
   * @column: The column to be returned.
   * @returns: A Vector4 containing the column of the matrix.
   */
  inline Vector4 getColumn(const int column)
  {
    assert(column >= 0 && column < 4);
    return Vector4((*this)[0][column], (*this)[1][column], (*this)[2][column], (*this)[3][column]);
  }

  /**
   * setLine: Sets an entire line to the values contained in the vector.
   * @line: The index of the line to be set.
   * @lineContent: The vector containing the new values of the line.
   */
  inline void setLine(const int line, Vector4 lineContent)
  {
    assert(line >= 0 && line < 4);
    for(int i = 0; i < 4; i++)
      (*this)[line][i] = lineContent[i];
  }

  /**
   * setColumn: Sets an entire column to the values contained in the vector.
   * @column: The index of the column to be set.
   * @columnContent: The vector containing the new values of the column.
   */
  inline void setColumn(const int column, Vector4 columnContent)
  {
    assert(column >= 0 && column < 4);
    for(int i = 0; i < 4; i++)
      (*this)[i][column] = columnContent[i];
  }

  /**
   * operator =: Assignment operator.
   * @rhs - The source matrix.
   * @returns - The destination matrix.
   */
  Matrix4& operator =(const Matrix4& rhs);

  /**
   * operator +: Sum of matrices.
   * @rhs: The matrix to be added.
   * @returns: The matrix containing the sum of *this and rhs.
   */
  Matrix4 operator +(const Matrix4& rhs);
  
  /**
   * operator -: Difference of matrices.
   * @rhs: The matrix to be subtracted.
   * @returns: The result of *this - rhs.
   */
  Matrix4 operator -(const Matrix4& rhs);

  /**
   * operator -: Computes the conjugate of the matrix
   * @returns: The conjugated matrix.
   */
  Matrix4& operator -();

  /**
   * operator *: Matrix product.
   * @rhs: The matrix to be multiplicated.
   * @returns: The resulting matrix of *this * rhs.
   */
  Matrix4 operator *(const Matrix4& rhs);

  /**
   * operator *: Product of a matrix by a vector.
   * @rhs: The vector to be multiplicated.
   * @returns: The resulting vector of *this * rhs.
   */
  Vector4 operator *(Vector4& rhs);

  /**
   * operator ==: Test wheter the matrices are the same.
   * @rhs: The matrix to be tested.
   * @returns: true if the matrices are the same or false otherwise.
   */
  bool operator ==(const Matrix4& rhs);

  /**
   * operator !=: Test wheter the matrices are different
   * @rhs: The matrix to be tested.
   * @returns: true if the matrices are different or false otherwise.
   */
  bool operator !=(const Matrix4& rhs);
};

/**
 * rotate: Creates an arbitrary axis rotation matrix of "angle" 
 * degrees around the "axis" axis.
 * @angle: The angle of rotation in degrees.
 * @axis: The axis of rotation. It doesn't need to be normalized.
 * @returns: The arbitrary axis rotation matrix.
 */
Matrix4 rotate(Scalar angle, Vector4 axis);

/**
 * translate: Creates a translation matrix and returns it.
 * @x: The amount of translation on the x axis.
 * @y: The amount of translation on the y axis.
 * @z: The amount of translation on the z axis.
 * @returns: The translation matrix.
 */
Matrix4 translate(Scalar x, Scalar y, Scalar z);

/**
 * scale: Creates a scale matrix and returns it.
 * @sx: The amount of scaling on the x axis.
 * @sy: The amount of scaling on the y axis.
 * @sz: The amount of scaling on the z axis.
 * @returns: The scale matrix.
 */
Matrix4 scale(Scalar sx, Scalar sy, Scalar sz);

/**
 * perspective: Creates a perspective projection matrix. Its similar
 * to the gluPerspective function.
 * @fovy: The field of view angle in degrees.
 * @aspectRatio: The aspect ratio of the window (width / height).
 * @near: The distance fo the viewer from the near plane.
 * @far: The distance fo the viewer from the far plane.
 * @returns: The perspective projection matrix.
 */
Matrix4 perspective(Scalar fovy, Scalar aspectRatio, Scalar near, Scalar far);

/**
 * frustum: Creates a frustum transform matrix. It is made to transform
 * the view frustum to the homogenized view cube. It is similar to the
 * glFrustum function.
 * @left: The coordinate of the left plane on the near plane.
 * @right: The coordinate of the right plane on the near plane.
 * @bottom: The coordinate of the bottom plane on the near plane.
 * @up: The coordinate of the up plane on the near plane.
 * @near: The distance fo the viewer from the near plane.
 * @far: The distance fo the viewer from the far plane.
 * @returns: The frustum transform matrix.
 */
Matrix4 frustum(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far);

/**
 * ortho: Creates an orthogonal projection matrix to be applied to
 * the points on the scene.
 * @left: The coordinate of the left plane on the near plane.
 * @right: The coordinate of the right plane on the near plane.
 * @bottom: The coordinate of the bottom plane on the near plane.
 * @up: The coordinate of the up plane on the near plane.
 * @near: The distance fo the viewer from the near plane.
 * @far: The distance fo the viewer from the far plane.
 * @returns: The orthogonal transform matrix.
 */
Matrix4 ortho(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far);

/**
 * lookAt: Positions the viewver given it's coordinates, the viewing
 * point and the orientation of the viewer.
 * @eyeX, @eyeY, @eyeZ: The coordinates of the viewer.
 * @centerX, @centerY, @centerZ: The viewing point, where the viewer is
 * looking.
 * @upX, @upY, @upZ: The orientation of the viewer.
 * @returns: The camera transform matrix to be applied to the points
 * of the scene.
 */
Matrix4 lookAt(Scalar eyeX, Scalar eyeY, Scalar eyeZ, Scalar centerX, Scalar centerY, Scalar centerZ, Scalar upX, Scalar upY, Scalar upZ);

}

#endif /* __MATRIX4_HPP__ */
