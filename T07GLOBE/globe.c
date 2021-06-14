
#include <math.h>
#include "globe.h"

#define pi 3.14159265358979323846

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
  DBL tetha = 0, phi = 0;

  WINw = w;
  WINh = h;

  for (i = 0; i < GRID_H; i++, tetha += pi / (GRID_H - 1))
    for (j = 0; j < GRID_W; j++, phi += 2 * pi / GRID_W)
    {
      Globe[i][j].x = sin(tetha) * sin(phi);
      Globe[i][j].y = cos(tetha);
      Globe[i][j].z = sin(tetha) * cos(phi);
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
  static VEC pnts[GRID_H][GRID_W];
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      pnts[i][j].x = Globe[i][j].x * Size;
      pnts[i][j].y = Globe[i][j].y * Size;
      pnts[i][j].z = Globe[i][j].z * Size;
    }
  for (i = 0; i < GRID_H; i++)
  {
    MoveToEx(hDC, WINw / 2 + pnts[i][0].x, WINh / 2 - pnts[i][0].y, NULL);
    for (j = 1; j < GRID_W; j++)
      LineTo(hDC, WINw / 2 + pnts[i][j].x, WINh / 2 - pnts[i][j].y);
  } 
  for (j = 0; j < GRID_W; j++)
  {
    MoveToEx(hDC, WINw / 2 + pnts[0][j].x, WINh / 2 - pnts[0][j].y, NULL);
    for (i = 1; i < GRID_H; i++)
      LineTo(hDC, WINw / 2 + pnts[i][j].x, WINh / 2 - pnts[i][j].y);
  }
} /* End of 'GlobeDraw' function */