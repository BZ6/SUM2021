/* FILE NAME: u_plane.c
 * PROGRAMMER: BZ6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation plane unit module.
 */

#include "units.h"

typedef struct
{
  BZ6_UNIT_BASE_FIELDS;
  VEC Pos;
  bz6PRIM Pr, Tx;
  INT TexId;
} bz6UNIT_PLANE;

/* Unit plane initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_BALL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitInit( bz6UNIT_PLANE *Uni, bz6ANIM *Ani )
{
  bz6VERTEX V[] =
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 0, 0}},
    {{1, 0, 0}, {1, 0}, {0, 0, 1}, {1, 0, 0, 0}},
    {{0, 1, 0}, {0, 1}, {0, 0, 1}, {1, 1, 0, 0}},
    {{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 0, 0, 0}},
  };
  FLT t[2][2] =
  {
    {0.8, 1},
    {1, 0.3}
  };
  
  Uni->Pos = VecSet1(0);
  glGenTextures(1, &Uni->TexId);

  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  glTexImage2D(GL_TEXTURE_2D, 0, 1, 2, 2, 0, GL_LUMINANCE, GL_FLOAT, t);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  BZ6_RndPrimCreateGrid(&Uni->Tx, 2, 2, V);
  BZ6_RndPrimCreateBase(&Uni->Pr, Uni->Pos, VecSet(1, 0, 0), VecSet(0, 0, 1), 1, 1, 100, 100);
} /* End of 'BZ6_UnitInit' function */

/* Unit plane render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_BALL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitRender( bz6UNIT_PLANE *Uni, bz6ANIM *Ani )
{
  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  BZ6_RndPrimDraw(&Uni->Pr, MatrTranslate(VecSet(0, 0, 0)));
} /* End of 'BZ6_UnitRender' function */

/* Unit plane deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_BALL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitClose( bz6UNIT_PLANE *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimFree(&Uni->Pr);
} /* End of 'BZ6_UnitClose' function */

/* Unit plane creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (bz6UNIT *) pointer to created unit.
 */
bz6UNIT * BZ6_UnitCreatePlane( VOID )
{
  bz6UNIT *Uni;

  if ((Uni = (bz6UNIT *)BZ6_AnimUnitCreate(sizeof(bz6UNIT_PLANE))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)BZ6_UnitInit;
  Uni->Render = (VOID *)BZ6_UnitRender;
  Uni->Close = (VOID *)BZ6_UnitClose;

  return Uni;
} /* End of 'BZ6_UnitCreatePlane' function */

/* END OF 'u_plane.c' FILE */