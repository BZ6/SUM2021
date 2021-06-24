/* FILE NAME: u_cowsecond.c
 * PROGRAMMER: BZ6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation second cow unit module.
 */

#include "units.h"

typedef struct
{
  BZ6_UNIT_BASE_FIELDS;
  VEC Pos;
  bz6PRIM Pr;
  VEC Dir;
  MATR Cow;
} bz6UNIT_COW_SECOND;

/* Unit cow initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW_SECOND *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitInit( bz6UNIT_COW_SECOND *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimLoad(&Uni->Pr, "BIN/MODELS/cow.obj");
  Uni->Pos = VecSet1(0);
  Uni->Dir = VecSet(1, 0 ,0);
  Uni->Cow = MatrMulMatr(MatrScale(VecSet1(0.1)), MatrTranslate(VecSet(0, 0, 0)));
} /* End of 'BZ6_UnitInit' function */

/* Unit cow inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW_SECOND *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitResponse( bz6UNIT_COW_SECOND *Uni, bz6ANIM *Ani )
{
  VEC ve;

  Uni->Cow = MatrMulMatr(Uni->Cow, MatrRotate(Ani->DeltaTime * 400 * (Ani->Keys[VK_LEFT]- Ani->Keys[VK_RIGHT]), VecSet(0, 1, 0)));
  Uni->Dir = VectorTransform(Uni->Dir, MatrRotate(Ani->DeltaTime * 400 * (Ani->Keys[VK_LEFT]- Ani->Keys[VK_RIGHT]), VecSet(0, 1, 0)));
  ve = VecAddVec(Uni->Pos, VecMulNum(Uni->Dir, Ani->DeltaTime * 50 * (Ani->Keys[VK_UP]- Ani->Keys[VK_DOWN])));
  if (ve.X < 47.5 && ve.X > -48.5 && ve.Z < 47.5 && ve.Z > -48.5)
    Uni->Pos = ve;
} /* End of 'BZ6_UnitResponse' function */

/* Unit cow render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW_SECOND *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitRender( bz6UNIT_COW_SECOND *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimDraw(&Uni->Pr, MatrMulMatr(Uni->Cow, MatrTranslate(Uni->Pos)));
} /* End of 'BZ6_UnitRender' function */

/* Unit cow deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW_SECOND *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitClose( bz6UNIT_COW_SECOND *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimFree(&Uni->Pr);
} /* End of 'BZ6_UnitClose' function */

/* Unit second cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (bz6UNIT *) pointer to created unit.
 */
bz6UNIT * BZ6_UnitCreateCowSecond( VOID )
{
  bz6UNIT *Uni;

  if ((Uni = (bz6UNIT *)BZ6_AnimUnitCreate(sizeof(bz6UNIT_COW_SECOND))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)BZ6_UnitInit;
  Uni->Response = (VOID *)BZ6_UnitResponse;
  Uni->Render = (VOID *)BZ6_UnitRender;
  Uni->Close = (VOID *)BZ6_UnitClose;

  return Uni;
} /* End of 'BZ6_UnitCreateCowSecond' function */

/* END OF 'u_cowsecond.c' FILE */