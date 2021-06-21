/* FILE NAME: mth.h
 * PROGRAMMER: BZ6
 * DATE: 15.06.2021
 * PURPOSE: 3D math implementation module.
 */

#ifndef __mth_h_
#define __mth_h_

#include <math.h>

#include <windows.h>

/* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180))
#define Degree2Radian(a) D2R(a)

/* Matrixes multiplies */
#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr(A, B), C)
#define MatrMulMatr4(A, B, C, D) MatrMulMatr(MatrMulMatr(MatrMulMatr(A, B), C), D)
#define MatrMulMatr5(A, B, C, D, E) MatrMulMatr(MatrMulMatr(MatrMulMatr(MatrMulMatr(A, B), C), D), E)

/* Vector with 1 parametrs */
#define VecSet1(A) VecSet(A, A, A)

/* Base float type */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Vector type */
typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;

/* Matrix type */
typedef struct tagMATR
{
  FLT A[4][4];
} MATR;

static MATR UnitMatrix =
{                  
  {                
    {1, 0, 0, 0},  
    {0, 1, 0, 0},  
    {0, 0, 1, 0},  
    {0, 0, 0, 1}   
  }                
};

/* Vector initialization function.
 * ARGUMENTS:NONE;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */

/* Vector initialization function.
 * ARGUMENTS:
 *   - coordinates to vector:
 *       FLT X, Y, Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
} /* End of 'VecSet' function */

/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Sub two vectors function.
 * ARGUMENTS:
 *   - vectors to be sub:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Div two vectors function.
 * ARGUMENTS:
 *   - vectors to be div:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X / V2.X, V1.Y / V2.Y, V1.Z / V2.Z);
} /* End of 'VecDivVec' function */

/* Mul vector by number function.
 * ARGUMENTS:
 *   - vectors to be mul:
 *       VEC V;
 *   - number to mul:
 *       FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulNum( VEC V, FLT N )
{
  return VecSet(V.X * N, V.Y * N, V.Z * N);
} /* End of 'VecMulNum' function */

/* Div vector by number function.
 * ARGUMENTS:
 *   - vector to be div:
 *       VEC V;
 *   - number to mul:
 *       FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC V, FLT N )
{
  return VecSet(V.X / N, V.Y / N, V.Z / N);
} /* End of 'VecDivNum' function */

/* Dot multiply two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (FLT) dot product.
 */
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Cross multiply two vectors function.
 * ARGUMENTS:
 *   - vectors to be mul:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */

/* Negative vector function.
 * ARGUMENTS:
 *   - vector to be negative:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* Length in square vector function.
 * ARGUMENTS:
 *   - vector to be lengthed:
 *       VEC V;
 * RETURNS:
 *   (FLT) length in square vector.
 */
__inline FLT VecLen2( VEC V )
{
  return VecDotVec(V, V);
} /* End of 'VecLen2' function */

/* Length vector function.
 * ARGUMENTS:
 *   - vector to be lengthed:
 *       VEC V;
 * RETURNS:
 *   (FLT) length vector.
 */
__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrtf(len);
} /* End of 'VecLen' function */

/* Normalized vector function.
 * ARGUMENTS:
 *   - vector to be normalized:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrtf(len));
} /* End of 'VecNormalize' function */

/* Matrix initialization function.
 * ARGUMENTS:
 *   - numbers for matrix:
 *       FLT A00, A01, A02, A03, A10, A11, A12, A13,
 *           A20, A21, A22, A23, A30, A31, A32, A33;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrSet( FLT A00, FLT A01, FLT A02, FLT A03,
                       FLT A10, FLT A11, FLT A12, FLT A13,
                       FLT A20, FLT A21, FLT A22, FLT A23,
                       FLT A30, FLT A31, FLT A32, FLT A33 )
{
  MATR r =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33}
    }
  };

  return r;
} /* End of 'MatrSet' function */

/* Matrix translate function.
 * ARGUMENTS:
 *   - vector to be translate in matrix:
 *       VEC V;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrTranslate( VEC V )
{
  return MatrSet(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 V.X, V.Y, V.Z, 1);
} /* End of 'MatrTranslate' function */

/* Matrix scale function.
 * ARGUMENTS:
 *   - vector to be scale in matrix:
 *       VEC V;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrScale( VEC V )
{
  return MatrSet(V.Y, 0, 0, 0,
                 0, V.Y, 0, 0,
                 0, 0, V.Z, 0,
                 0, 0, 0, 1);
} /* End of 'MatrScale' function */

/* Matrix scale function.
 * ARGUMENTS:
 *   - matrix to be transpose:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrTranspose( MATR M )
{
  return MatrSet(M.A[0][0], M.A[1][0], M.A[2][0], M.A[3][0],
                 M.A[0][1], M.A[1][1], M.A[2][1], M.A[3][1],
                 M.A[0][2], M.A[1][2], M.A[2][2], M.A[3][2],
                 M.A[0][3], M.A[1][3], M.A[2][3], M.A[3][3]);
} /* End of 'MatrTranspose' function */

/* Rotate by X function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  return MatrSet(1, 0, 0, 0,
                 0, c, s, 0,
                 0, -s, c, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateX' function */

/* Rotate by Y function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  return MatrSet(c, 0, -s, 0,
                 0, 1, 0, 0,
                 s, 0, c, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateY' function */

/* Rotate by Z function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  return MatrSet(c, s, 0, 0,
                 -s, c, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateZ' function */

/* Rotate by V function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 *   - vector rotated by:
 *       VEC V;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotate( FLT AngleInDegree, VEC V )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  VEC A = VecNormalize(V);

  return MatrSet(c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - A.Y * s, 0,
                 A.Y * A.X * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Y * A.Z * (1 - c) + A.X * s, 0,
                 A.X * A.Z * (1 - c) + A.Y * s, A.Y * A.Z * (1 - c) - A.X * s, c + A.Z * A.Z * (1 - c), 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotate' function */

/* Matrixes miltiply function.
 * ARGUMENTS:
 *   - matrixes to be mul:
 *       MATR M1, M2;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  return MatrSet(M1.A[0][0] * M2.A[0][0] + M1.A[0][1] * M2.A[1][0] + M1.A[0][2] * M2.A[2][0] + M1.A[0][3] * M2.A[3][0], 
                 M1.A[0][0] * M2.A[0][1] + M1.A[0][1] * M2.A[1][1] + M1.A[0][2] * M2.A[2][1] + M1.A[0][3] * M2.A[3][1], 
                 M1.A[0][0] * M2.A[0][2] + M1.A[0][1] * M2.A[1][2] + M1.A[0][2] * M2.A[2][2] + M1.A[0][3] * M2.A[3][2], 
                 M1.A[0][0] * M2.A[0][3] + M1.A[0][1] * M2.A[1][3] + M1.A[0][2] * M2.A[2][3] + M1.A[0][3] * M2.A[3][3],

                 M1.A[1][0] * M2.A[0][0] + M1.A[1][1] * M2.A[1][0] + M1.A[1][2] * M2.A[2][0] + M1.A[1][3] * M2.A[3][0], 
                 M1.A[1][0] * M2.A[0][1] + M1.A[1][1] * M2.A[1][1] + M1.A[1][2] * M2.A[2][1] + M1.A[1][3] * M2.A[3][1], 
                 M1.A[1][0] * M2.A[0][2] + M1.A[1][1] * M2.A[1][2] + M1.A[1][2] * M2.A[2][2] + M1.A[1][3] * M2.A[3][2], 
                 M1.A[1][0] * M2.A[0][3] + M1.A[1][1] * M2.A[1][3] + M1.A[1][2] * M2.A[2][3] + M1.A[1][3] * M2.A[3][3],

                 M1.A[2][0] * M2.A[0][0] + M1.A[2][1] * M2.A[1][0] + M1.A[2][2] * M2.A[2][0] + M1.A[2][3] * M2.A[3][0], 
                 M1.A[2][0] * M2.A[0][1] + M1.A[2][1] * M2.A[1][1] + M1.A[2][2] * M2.A[2][1] + M1.A[2][3] * M2.A[3][1], 
                 M1.A[2][0] * M2.A[0][2] + M1.A[2][1] * M2.A[1][2] + M1.A[2][2] * M2.A[2][2] + M1.A[2][3] * M2.A[3][2], 
                 M1.A[2][0] * M2.A[0][3] + M1.A[2][1] * M2.A[1][3] + M1.A[2][2] * M2.A[2][3] + M1.A[2][3] * M2.A[3][3],

                 M1.A[3][0] * M2.A[0][0] + M1.A[3][1] * M2.A[1][0] + M1.A[3][2] * M2.A[2][0] + M1.A[3][3] * M2.A[3][0], 
                 M1.A[3][0] * M2.A[0][1] + M1.A[3][1] * M2.A[1][1] + M1.A[3][2] * M2.A[2][1] + M1.A[3][3] * M2.A[3][1], 
                 M1.A[3][0] * M2.A[0][2] + M1.A[3][1] * M2.A[1][2] + M1.A[3][2] * M2.A[2][2] + M1.A[3][3] * M2.A[3][2], 
                 M1.A[3][0] * M2.A[0][3] + M1.A[3][1] * M2.A[1][3] + M1.A[3][2] * M2.A[2][3] + M1.A[3][3] * M2.A[3][3]);
} /* End of 'MatrMulMatr' function */

/* Matrix miltiply vector function.
 * ARGUMENTS:
 *   - vector to be mul:
 *       VEC V; 
 *   - matrixe to be mul:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulMatr( VEC V, MATR M ) 
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w, 
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
} /* End of 'VecMulMatr' function */

/* Transformed point vector function.
 * ARGUMENTS:
 *   - point vector to be transformed:
 *       VEC V; 
 *   - matrixe transform:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC PointTransform( VEC V, MATR M ) 
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0], 
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
} /* End of 'PointTransform' function */

/* Transformed vector function.
 * ARGUMENTS:
 *   - vector to be transformed:
 *       VEC V; 
 *   - matrix transform:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VectorTransform( VEC V, MATR M ) 
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0], 
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
} /* End of 'VectorTransform' function */

/* Determinant of matrix 3x3 function.
 * ARGUMENTS:
 *   - numbers in matrix 3x3:
 *       FLT A11, A12, A13,
 *           A21, A22, A23,
 *           A31, A32, A33;
 * RETURNS:
 *   (FLT) determinant of matrix 3x3.
 */
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Determinant of matrix function.
 * ARGUMENTS:
 *   - matrix to be calculated determinent:
 *       MATR M;
 * RETURNS:
 *   (FLT) determinant of matrix.
 */
__inline FLT MatrDeterm( MATR M )
{
  return
    +M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                               M.A[2][1], M.A[2][2], M.A[2][3],
                               M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    +M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                               M.A[2][0], M.A[2][1], M.A[2][3],
                               M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
} /* End of 'MatrDeterm' function */

/* Inverse matrix of matrix function.
 * ARGUMENTS:
 *   - matrix to be inverse:
 *       MATR M;
 * RETURNS:
 *   (MATR) inverse matrix of matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  FLT det = MatrDeterm(M);

  if (det == 0)
    return MatrIdentity();

  /* build adjoint matrix */
  return MatrSet(MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                               M.A[2][1], M.A[2][2], M.A[2][3],
                               M.A[3][1], M.A[3][2], M.A[3][3]) / det, 
                 -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                                M.A[2][1], M.A[2][2], M.A[2][3],
                                M.A[3][1], M.A[3][2], M.A[3][3]) / det, 
                 MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                               M.A[1][1], M.A[1][2], M.A[1][3],
                               M.A[3][1], M.A[3][2], M.A[3][3]) / det, 
                 -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                                M.A[1][1], M.A[1][2], M.A[1][3],
                                M.A[2][1], M.A[2][2], M.A[2][3]) / det,

                 -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                                M.A[2][0], M.A[2][2], M.A[2][3],
                                M.A[3][0], M.A[3][2], M.A[3][3]) / det, 
                 MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) / det, 
                 -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                                M.A[1][0], M.A[1][2], M.A[1][3],
                                M.A[3][0], M.A[3][2], M.A[3][3]) / det, 
                 MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                               M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3]) / det,

                 MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                               M.A[2][0], M.A[2][1], M.A[2][3],
                               M.A[3][0], M.A[3][1], M.A[3][3]) / det, 
                 -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                                M.A[2][0], M.A[2][1], M.A[2][3],
                                M.A[3][0], M.A[3][1], M.A[3][3]) / det, 
                 MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                               M.A[1][0], M.A[1][1], M.A[1][3],
                               M.A[3][0], M.A[3][1], M.A[3][3]) / det, 
                 -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                                M.A[1][0], M.A[1][1], M.A[1][3],
                                M.A[2][0], M.A[2][1], M.A[2][3]) / det,

                 -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                                M.A[2][0], M.A[2][1], M.A[2][2],
                                M.A[3][0], M.A[3][1], M.A[3][2]) / det, 
                 MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]) / det, 
                 -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                                M.A[1][0], M.A[1][1], M.A[1][2],
                                M.A[3][0], M.A[3][1], M.A[3][2]) / det, 
                 MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                               M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2]) / det);
} /* End of 'MatrInverse' function */

/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));

  return MatrSet(Right.X, Up.X, -Dir.X, 0, 
                 Right.Y, Up.Y, -Dir.Y, 0, 
                 Right.Z, Up.Z, -Dir.Z, 0,
                 -VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1);
} /* End of 'MatrView' function */

/* Matrix frustum projection setup function.
 * ARGUMENTS:
 *   - frustum parametres:
 *       VDBL l, r, b, t, n, f;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrFrustum( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f )
{
  return MatrSet(2 * n /(r - l), 0, 0, 0, 
                 0, 2 * n /(t - b), 0, 0, 
                (r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1,
                 0, 0, -2 * n * f /(f - n), 0);
} /* End of 'MatrFrustum' function */


#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */
