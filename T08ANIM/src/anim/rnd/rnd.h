/* FILE NAME: rnd.h
 * PROGRAMMER: BZ6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation rendering declaration module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "../../def.h"



/* Global rendering data */
extern HWND BZ6_hRndWnd;                 /* Work window handle */
extern HDC BZ6_hRndDCFrame;              /* Work window memory device context  */
extern HBITMAP BZ6_hRndBmFrame;          /* Work window background bitmap handle */
extern INT BZ6_RndFrameW, BZ6_RndFrameH; /* Work window size */

extern DBL
  BZ6_RndProjSize,     /* Project plane fit square */
  BZ6_RndProjDist,     /* Distance to project plane from viewer (near) */
  BZ6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  BZ6_RndMatrView, /* View coordinate system matrix */
  BZ6_RndMatrProj, /* Projection coordinate system matrix */
  BZ6_RndMatrVP;   /* Stored (View * Proj) matrix */

/* Vertex type */
typedef struct tagbz6VERTEX
{
  VEC P;  /* Vertex position */
} bz6VERTEX;

/* Primitive type */
typedef struct tagbz6PRIM
{
  bz6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh � by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} bz6PRIM;

/* Forward declaration */

/* Rendering initialization function.
 * ARGUMENTS:
 *   - window handle:
 *      HWND hWnd;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndInit( HWND hWnd );

/* Rendering close function.
 * ARGUMENTS:
 *   NONE;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndClose( VOID );

/* Rendering projection set function.
 * ARGUMENTS:
 *   NONE;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndProjSet( VOID );

/* Rendering iresize function.
 * ARGUMENTS:
 *   - window size:
 *      INT W, H;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndResize( INT W, INT H );

/* Rendering copy frame function.
 * ARGUMENTS:
 *   - window handle discreaptor:
 *      HDC hDC;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndCopyFrame( HDC hDC );

/* Rendering look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndCamSet( VEC Loc, VEC At, VEC Up );

/* Rendering start function.
 * ARGUMENTS:
 *   NONE;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndStart( VOID );

/* Rendering end function.
 * ARGUMENTS:
 *   NONE;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndEnd( VOID );

/* Forward declaration primitive functiones */

/* Rendering create primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 *   - numbers of vertexes and indexes:
 *       INT NoofV, NoofI
 * RETURNS:
 *   (BOOL) TRUE if complete, FALSE if not complete.
 */
BOOL BZ6_RndPrimCreate( bz6PRIM *Pr, INT NoofV, INT NoofI );

/* Rendering free primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndPrimFree( bz6PRIM *Pr );

/* Rendering draw primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 *   - matrix of transformation primitive:
 *       MATR World;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndPrimDraw( bz6PRIM *Pr, MATR World );

/* Rendering draw sphere function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 *   - location:
 *       VEC C;
 *   - radius:
 *       DBL R;
 *   - size:
 *       INT SplitW, SplitH;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndPrimCreateSphere( bz6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );

/* Create grid function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 *   - size:
 *       INT GridW, GridH;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndPrimCreateGrid( bz6PRIM *Pr, INT GridW, INT GridH );

/* Rendering draw torus function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 *   - location:
 *       VEC C;
 *   - radiuses small and big:
 *       DBL r, R;
 *   - size:
 *       INT SplitW, SplitH;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndPrimCreateTorus( bz6PRIM *Pr, VEC C, DBL r, DBL R, INT SplitW, INT SplitH );

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       bz6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL BZ6_RndPrimLoad( bz6PRIM *Pr, CHAR *FileName );

/* Rendering draw base function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 *   - location:
 *       VEC Position;
 *   - plane direction:
 *       VEC DirectionWeird, DirectionHeight;
 *   - size of base:
 *       DBL BaseWeird, BaseHeight;
 *   - size:
 *       INT SplitW, SplitH;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndPrimCreateBase( bz6PRIM *Pr, VEC Position, VEC DirectionWeird, VEC DirectionHeight, DBL BaseWeird, DBL BaseHeight, INT SplitW, INT SplitH );

#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */