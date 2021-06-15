/* FILE NAME: globe.h
 * PROGRAMMER: BZ6
 * DATE: 15.06.2021
 * PURPOSE: Declaration file.
 */

#ifndef __globe_h_
#define __globe_h_

#include <windows.h>
#include "timer.h"

/* Global definitions */
#define GRID_H 30
#define GRID_W 50
#define pi 3.14159265358979323846

/* Global struct */
typedef DOUBLE DBL;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

/* Forward declaration */
VOID GlobeSet( INT w, INT h );
VOID GlobeDraw( HDC hDC, DBL Size );
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
VEC RotateZ( DBL Angle, VEC V );
VEC RotateX( DBL Angle, VEC V );
VEC RotateY( DBL Angle, VEC V );

#endif /* __globe_h_ */

/* END OF 'globe.h' FILE*/