/* FILE NAME: rndprim.c
 * PROGRAMMER: BZ6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation rendering primitive module.
 */

#include <string.h>
#include "rnd.h"

/* Rendering create primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 *   - numbers of vertexes and indexes:
 *       INT NoofV, NoofI
 * RETURNS:
 *   (BOOL) TRUE if complete, FALSE if not complete.
 */
BOOL BZ6_RndPrimCreate( bz6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(bz6PRIM));
  size = sizeof(bz6VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);

  return TRUE;
} /* End of 'BZ6_RndPrimCreate' function */

/* Rendering free primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndPrimFree( bz6PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(bz6PRIM));
} /* End of 'BZ6_RndPrimFree' function */

/* Rendering draw primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       bz6PRIM *Pr;
 *   - matrix of transformation primitive:
 *       MATR World;
 * RETURNS:
 *   NONE.
 */
VOID BZ6_RndPrimDraw( bz6PRIM *Pr, MATR World )
{
  INT i;
  MATR wvp = MatrMulMatr3(Pr->Trans, World, BZ6_RndMatrVP);
  POINT *pnts;

  if ((pnts = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
    return;

  /* Build projection */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);

    pnts[i].x = (INT)((p.X + 1) * BZ6_RndFrameW / 2);
    pnts[i].y = (INT)((-p.Y + 1) * BZ6_RndFrameH / 2);
  }

  /* Draw triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(BZ6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    LineTo(BZ6_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(BZ6_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(BZ6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
  }
  free(pnts);
} /* End of 'BZ6_RndPrimDraw' function */

/* Rendering draw primitive function.
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
VOID BZ6_RndPrimCreateSphere( bz6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  INT i, j, k; 
  DBL tetha, phi;

  BZ6_RndPrimCreate(Pr, SplitW * SplitH, SplitW * SplitH * 6);

  for (i = 0, tetha = 0; i < SplitH; i++, tetha += PI / (SplitH - 1))
    for (j = 0, phi = 0; j < SplitW; j++, phi += 2 * PI / (SplitW - 1))
      Pr->V->P = VecSet(R * sin(tetha) * sin(phi), R * cos(tetha), R * sin(tetha) * cos(phi));

  for (i = 0, k = 0; i < SplitH; i++)
    for (j = 0; j < SplitW; j++, k += 6) 
    {
      Pr->I[0] = j + SplitW * j;
      Pr->I[1 + k] = j + SplitW * i + 1;
      Pr->I[2 + k] = j + (SplitW + 1) * i;
      Pr->I[3 + k] = j + SplitW * i + 1;
      Pr->I[4 + k] = j + (SplitW + 1) * i + 1;
      Pr->I[5 + k] = j + (SplitW + 1) * i;
    }
} /* End of 'BZ6_RndPrimCreateSphere' function */

/* END OF 'rndprim.c' FILE */