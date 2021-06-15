/* FILE NAME: mth.h
 * PROGRAMMER: BZ6
 * DATE: 15.06.2021
 * PURPOSE: 3D math implementation module.
 */

#ifndef __mth_h_
#define __mth_h_

#include <math.h>

/* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Base float type */
typedef double DBL;
typedef double FLT;

/* Vector type */
typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

/* Matrix type */
typedef struct tagMATR
{
  DBL A[4][4];
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
 *       DBL X, Y, Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
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
 *       DBL N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulNum( VEC V, DBL N )
{
  return VecSet(V.X * N, V.Y * N, V.Z * N);
} /* End of 'VecMulNum' function */

/* Div vector by number function.
 * ARGUMENTS:
 *   - vector to be div:
 *       VEC V;
 *   - number to mul:
 *       DBL N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC V, DBL N )
{
  return VecSet(V.X / N, V.Y / N, V.Z / N);
} /* End of 'VecDivNum' function */

/* Dot multiply two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDotVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X * V2.X, V1.Y * V2.Y, V1.Z * V2.Z);
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
 *   (DBL) length in square vector.
 */
__inline DBL VecLen2( VEC V )
{
  return VecCrossVec(V, V);
} /* End of 'VecLen2' function */

/* Length vector function.
 * ARGUMENTS:
 *   - vector to be lengthed:
 *       VEC V;
 * RETURNS:
 *   (DBL) length vector.
 */
__inline DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
} /* End of 'VecLen' function */

/* Normalized vector function.
 * ARGUMENTS:
 *   - vector to be negative:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
} /* End of 'VecNormalize' function */

/* Matrix initialization function.
 * ARGUMENTS:
 *   - numbers for matrix:
 *       DBL A00, A01, A02, A03, A10, A11, A12, A13,
 *           A20, A21, A22, A23, A30, A31, A32, A33;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrSet( DBL A00, DBL A01, DBL A02, DBL A03,
                       DBL A10, DBL A11, DBL A12, DBL A13,
                       DBL A20, DBL A21, DBL A22, DBL A23,
                       DBL A30, DBL A31, DBL A32, DBL A33 )
{
  MATR r =
  {
    {
      {DBL A00, DBL A01, DBL A02, DBL A03},
      {DBL A10, DBL A11, DBL A12, DBL A13},
      {DBL A20, DBL A21, DBL A22, DBL A23},
      {DBL A30, DBL A31, DBL A32, DBL A33}
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
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  return MatrSet(1, 0, 0, 0,
                 0, c, s, 0,
                 0, -s, c, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateX' function */

/* Rotate by Y function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  return MatrSet(c, 0, -s, 0,
                 0, 1, 0, 0,
                 s, 0, c, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateY' function */

/* Rotate by Z function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  return MatrSet(c, s, 0, 0,
                 -s, c, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateZ' function */

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */
