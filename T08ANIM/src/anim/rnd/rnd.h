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

  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} bz6PRIM;

/* Forward declaration */
VOID BZ6_RndInit( HWND hWnd );
VOID BZ6_RndClose( VOID );
VOID BZ6_RndProjSet( VOID );
VOID BZ6_RndResize( INT W, INT H );
VOID BZ6_RndCopyFrame( HDC hDC );
VOID BZ6_RndCamSet( VEC Loc, VEC At, VEC Up );
VOID BZ6_RndStart( VOID );
VOID BZ6_RndEnd( VOID );

/* Forward declaration primitive functiones */
BOOL BZ6_RndPrimCreate( bz6PRIM *Pr, INT NoofV, INT NoofI );
VOID BZ6_RndPrimFree( bz6PRIM *Pr );
VOID BZ6_RndPrimDraw( bz6PRIM *Pr, MATR World );

VOID BZ6_RndPrimCreateSphere( bz6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );

#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */