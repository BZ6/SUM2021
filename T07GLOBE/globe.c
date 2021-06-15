/* FILE NAME: globe.c
 * PROGRAMMER: BZ6
 * DATE: 15.06.2021
 * PURPOSE: Function file.
 */

#include <math.h>
#include <time.h>
#include "globe.h"

/* Global data */
static VEC Globe[GRID_H][GRID_W];
static INT WINw, WINh;

/* The fill globe function.
 * ARGUMENTS:
 *   - radius of globe:
 *       DBL R;
 * RETURNS:
 *   VOID.
 */
VOID GlobeSet( INT w, INT h)
{
  INT i, j; 
  DBL tetha, phi;

  WINw = w;
  WINh = h;

  for (i = 0, tetha = 0; i < GRID_H; i++, tetha += pi / (GRID_H - 1))
    for (j = 0, phi = 0; j < GRID_W; j++, phi += 2 * pi / (GRID_W - 1))
    {
      Globe[i][j].X = sin(tetha) * sin(phi);
      Globe[i][j].Y = cos(tetha);
      Globe[i][j].Z = sin(tetha) * cos(phi);
    }
} /* End of 'GlobeSet' function */

/* The draw globe function.
 * ARGUMENTS:
 *   - handle descriptor:
 *       HDC hDC;
 *   - coordinates of center:
 *       DBL Xc, Yc;
 *   - size of ellipse:
 *       DBL Size;
 * RETURNS:
 *   VOID.
 */
VOID GlobeDraw( HDC hDC, DBL Size )
{
  INT i, j, r = WINw > WINh ? WINh : WINw;
  static POINT pnts[GRID_H][GRID_W];

  /* Project globe */
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      VEC p = Globe[i][j];

      p = RotateZ(45 * GLB_Time, p);
      p = RotateY(90 * GLB_Time, p);
      p = RotateX(135 * GLB_Time, p);

      pnts[i][j].x = (LONG)(WINw / 2 + p.X * r * 0.49);
      pnts[i][j].y = (LONG)(WINh / 2 - p.Y * r * 0.49);
    } 

  /* Draw globe */
  for (i = 0; i < GRID_H - 1; i++)
    for (j = 0; j < GRID_W - 1; j++)
    {
      POINT p[4];

      p[0].x = pnts[i][j].x,         p[0].y = pnts[i][j].y;
      p[1].x = pnts[i][j + 1].x,     p[1].y = pnts[i][j + 1].y;
      p[2].x = pnts[i + 1][j + 1].x, p[2].y = pnts[i + 1][j + 1].y;
      p[3].x = pnts[i + 1][j].x,     p[3].y = pnts[i + 1][j].y;

      /* Trivial reject */
      if ((p[0].x - p[1].x) * (p[0].y + p[1].y) +
          (p[1].x - p[2].x) * (p[1].y + p[2].y) +
          (p[2].x - p[3].x) * (p[2].y + p[3].y) +
          (p[3].x - p[0].x) * (p[3].y + p[0].y) <= 0)
        continue;

      Polygon(hDC, p, 4);
    }
} /* End of 'GlobeDraw' function */

/* The rotate of Z globe function.
 * ARGUMENTS:
 *   - vector:
 *       VEC;
 *   - angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   - vector:
 *       VEC.
 */
VEC RotateZ( DBL Angle, VEC V )
{
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
  VEC pnts;

  pnts.X = V.X * co + V.Y * si;
  pnts.Y = V.X * si - V.Y * co;
  pnts.Z = V.Z;
  return pnts;
} /* End of 'RotateZ' function */

/* The rotate of X globe function.
 * ARGUMENTS:
 *   - vector:
 *       VEC;
 *   - angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   - vector:
 *       VEC.
 */
VEC RotateX( DBL Angle, VEC V )
{
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
  VEC pnts;

  pnts.Y = V.Y * co + V.Z * si;
  pnts.Z = V.Y * si - V.Z * co;
  pnts.X = V.X;
  return pnts;
} /* End of 'RotateX' function */

/* The rotate of Y globe function.
 * ARGUMENTS:
 *   - vector:
 *       VEC;
 *   - angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   - vector:
 *       VEC.
 */
VEC RotateY( DBL Angle, VEC V )
{
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
  VEC pnts;

  pnts.Z = V.Z * co + V.X * si;
  pnts.X = V.Z * si - V.X * co;
  pnts.Y = V.Y;
  return pnts;
} /* End of 'RotateY' function */

/* END OF 'globe.c' FILE*/