/* FILE NAME: u_ball.c
 * PROGRAMMER: BZ6
 * DATE: 19.06.2021
 * PURPOSE: 3D animation ball function module.
 */

#include <time.h>
#include "units.h"

typedef struct
{
  BZ6_UNIT_BASE_FIELDS;
  VEC Pos;
  bz6PRIM Pr;
  DBL t;
} bz6UNIT_BALL;

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_BALL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitInit( bz6UNIT_BALL *Uni, bz6ANIM *Ani )
{
  Uni->Pos = VecSet(0, 0, 0);
  Uni->t = 0;
  BZ6_RndPrimCreateSphere(&Uni->Pr, Uni->Pos, 2, 30, 20);
} /* End of 'BZ6_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_BALL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitResponse( bz6UNIT_BALL *Uni, bz6ANIM *Ani )
{
  Uni->t = clock() / 20.0;
} /* End of 'BZ6_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_BALL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitRender( bz6UNIT_BALL *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimDraw(&Uni->Pr, MatrRotate(Uni->t, VecSet1(1)));
} /* End of 'BZ6_UnitRender' function */

/* Unit ball unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_BALL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitClose( bz6UNIT_BALL *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimFree(&Uni->Pr);
} /* End of 'BZ6_UnitClose' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (bz6UNIT *) pointer to created unit.
 */
bz6UNIT * BZ6_UnitCreateBall( VOID )
{
  bz6UNIT *Uni;

  if ((Uni = (bz6UNIT *)BZ6_AnimUnitCreate(sizeof(bz6UNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)BZ6_UnitInit;
  Uni->Response = (VOID *)BZ6_UnitResponse;
  Uni->Render = (VOID *)BZ6_UnitRender;
  Uni->Close = (VOID *)BZ6_UnitClose;

  return Uni;
} /* End of 'BZ6_UnitCreateBall' function */

/* END OF 'u_ball.c' FILE */