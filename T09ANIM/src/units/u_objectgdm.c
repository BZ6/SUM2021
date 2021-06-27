/* FILE NAME: u_ball.c
 * PROGRAMMER: BZ6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation ball unit module.
 */

#include "units.h"

typedef struct
{
  BZ6_UNIT_BASE_FIELDS;
  VEC Pos;
  bz6PRIMS Prs;
} bz6UNIT_G3DM;

/* Unit ball initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_G3DM *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitInit( bz6UNIT_G3DM *Uni, bz6ANIM *Ani )
{
  bz6MATERIAL mtl = MtlGetDef();

  BZ6_RndPrimsLoad(&Uni->Prs, "BIN/MODELS/uh60.g3dm");
  mtl.ShdNo = BZ6_RndShaderAdd("DEFAULT");
  Uni->Prs.Prims->MtlNo = BZ6_RndMaterialAdd(&mtl);
  Uni->Pos = VecSet1(0);
} /* End of 'BZ6_UnitInit' function */

/* Unit ball inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_G3DM *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitResponse( bz6UNIT_G3DM *Uni, bz6ANIM *Ani )
{
} /* End of 'BZ6_UnitResponse' function */

/* Unit ball render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_G3DM *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitRender( bz6UNIT_G3DM *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimsDraw(&Uni->Prs, MatrRotateX(-90));
} /* End of 'BZ6_UnitRender' function */

/* Unit ball deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_G3DM *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitClose( bz6UNIT_G3DM *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimsFree(&Uni->Prs);
} /* End of 'BZ6_UnitClose' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (bz6UNIT *) pointer to created unit.
 */
bz6UNIT * BZ6_UnitCreateObject( VOID )
{
  bz6UNIT *Uni;

  if ((Uni = (bz6UNIT *)BZ6_AnimUnitCreate(sizeof(bz6UNIT_G3DM))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)BZ6_UnitInit;
  Uni->Response = (VOID *)BZ6_UnitResponse;
  Uni->Render = (VOID *)BZ6_UnitRender;
  Uni->Close = (VOID *)BZ6_UnitClose;

  return Uni;
} /* End of 'BZ6_UnitCreateBall' function */

/* END OF 'u_ball.c' FILE */