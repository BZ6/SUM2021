/* FILE NAME: u_cow.c
 * PROGRAMMER: BZ6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation cow unit module.
 */

#include "units.h"

typedef struct
{
  BZ6_UNIT_BASE_FIELDS;
  VEC Pos;
  bz6PRIM Pr;
  VEC Dir;
  MATR Cow;
} bz6UNIT_COW;

/* Unit cow initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitInit( bz6UNIT_COW *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimLoad(&Uni->Pr, "BIN/MODELS/cow.obj");
  Uni->Pos = VecSet1(0);
  Uni->Dir = VecSet(1, 0 ,0);
  Uni->Cow = MatrMulMatr(MatrScale(VecSet1(0.1)), MatrTranslate(VecSet(-0.6, -0.5, 0)));
  BZ6_RndShadersClose();
  BZ6_RndShaderAdd("COW");
} /* End of 'BZ6_UnitInit' function */

/* Unit cow inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitResponse( bz6UNIT_COW *Uni, bz6ANIM *Ani )
{
  Uni->Cow = MatrMulMatr(Uni->Cow, MatrRotate(Ani->DeltaTime * 400 * (Ani->Keys['A']- Ani->Keys['D']), VecSet(0, 1, 0)));
  Uni->Dir = VectorTransform(Uni->Dir, MatrRotate(Ani->DeltaTime * 400 * (Ani->Keys['A']- Ani->Keys['D']), VecSet(0, 1, 0)));
  Uni->Pos = VecAddVec(Uni->Pos, VecMulNum(Uni->Dir, Ani->DeltaTime * 50 * (Ani->Keys['W']- Ani->Keys['S'])));
} /* End of 'BZ6_UnitResponse' function */

/* Unit cow render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitRender( bz6UNIT_COW *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimDraw(&Uni->Pr, MatrMulMatr(Uni->Cow, MatrTranslate(Uni->Pos)));
} /* End of 'BZ6_UnitRender' function */

/* Unit cow deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitClose( bz6UNIT_COW *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimFree(&Uni->Pr);
} /* End of 'BZ6_UnitClose' function */

/* Unit cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (bz6UNIT *) pointer to created unit.
 */
bz6UNIT * BZ6_UnitCreateCow( VOID )
{
  bz6UNIT *Uni;

  if ((Uni = (bz6UNIT *)BZ6_AnimUnitCreate(sizeof(bz6UNIT_COW))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)BZ6_UnitInit;
  Uni->Response = (VOID *)BZ6_UnitResponse;
  Uni->Render = (VOID *)BZ6_UnitRender;
  Uni->Close = (VOID *)BZ6_UnitClose;

  return Uni;
} /* End of 'BZ6_UnitCreateCow' function */

/* END OF 'u_cow.c' FILE */