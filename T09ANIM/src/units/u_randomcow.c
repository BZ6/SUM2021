/* FILE NAME: u_randomcow.c
 * PROGRAMMER: BZ6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation second cow unit module.
 */

#include <stdlib.h>

#include "units.h"

VEC PosCowSecond;
VEC veSecond;
INT CountSecond;

typedef struct
{
  BZ6_UNIT_BASE_FIELDS;
  bz6PRIM Pr;
  VEC Dir;
  MATR Cow;
  BOOL IsDvig;
} bz6UNIT_COW_RANDOM;

static FLT Distance( VEC PositionCircle, VEC PositionObject )
{
  return VecLen(VecSubVec(PositionCircle, PositionObject));
}

/* Unit cow initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW_RANDOM *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitInit( bz6UNIT_COW_RANDOM *Uni, bz6ANIM *Ani )
{
  veSecond = VecSet1(0);
  Uni->IsDvig = FALSE;
  BZ6_RndPrimLoad(&Uni->Pr, "BIN/MODELS/cow.obj");
  PosCowSecond = VecSet(-3, 0, 5);
  Uni->Dir = VecSet(0, 0, -1);
  Uni->Cow = MatrMulMatr(MatrScale(VecSet1(0.1)), MatrRotateY(90));
} /* End of 'BZ6_UnitInit' function */

/* Unit cow inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW_RANDOM *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitResponse( bz6UNIT_COW_RANDOM *Uni, bz6ANIM *Ani )
{
  VEC ve;

  Uni->IsDvig = FALSE;
  Uni->Cow = MatrMulMatr(Uni->Cow, MatrRotate(Ani->DeltaTime * 400 * (Ani->Keys[VK_LEFT]- Ani->Keys[VK_RIGHT]), VecSet(0, 1, 0)));
  Uni->Dir = VectorTransform(Uni->Dir, MatrRotate(Ani->DeltaTime * 400 * (Ani->Keys[VK_LEFT]- Ani->Keys[VK_RIGHT]), VecSet(0, 1, 0)));
  veSecond = VecMulNum(Uni->Dir, Ani->DeltaTime * 50 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));
  ve = VecAddVec(PosCowSecond, veSecond);

  if (ve.X < 47.5 && ve.X > -48.5 && ve.Z < 47.5 && ve.Z > -48.5)
    if (Distance(VecSet(3.5 + RandomNumberX, 0, RandomNumberZ), ve) > 2.6 && Distance(VecSet(-3.5 + RandomNumberX, 0, RandomNumberZ), ve) > 2.6)
      Uni->IsDvig = TRUE;

  if (ve.X < 1.5 + RandomNumberX && ve.Z > -2 + RandomNumberZ && ve.Z < 2 + RandomNumberZ && ve.X > -1.5 + RandomNumberX && Uni->IsDvig)
      RandomNumberX = rand() % 80 - 40, RandomNumberZ = rand() % 80 - 40, CountSecond++;

  if (Uni->IsDvig)
    PosCowSecond = ve;
  else
    PosCowSecond = PosCowSecond;

} /* End of 'BZ6_UnitResponse' function */

/* Unit cow render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW_RANDOM *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitRender( bz6UNIT_COW_RANDOM *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimDraw(&Uni->Pr, MatrMulMatr(Uni->Cow, MatrTranslate(PosCowSecond)));
} /* End of 'BZ6_UnitRender' function */

/* Unit cow deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_COW_RANDOM *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitClose( bz6UNIT_COW_RANDOM *Uni, bz6ANIM *Ani )
{
  BZ6_RndPrimFree(&Uni->Pr);
} /* End of 'BZ6_UnitClose' function */

/* Unit second cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (bz6UNIT *) pointer to created unit.
 */
bz6UNIT * BZ6_UnitCreateCowRandom( VOID )
{
  bz6UNIT *Uni;

  if ((Uni = (bz6UNIT *)BZ6_AnimUnitCreate(sizeof(bz6UNIT_COW_RANDOM))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)BZ6_UnitInit;
  Uni->Response = (VOID *)BZ6_UnitResponse;
  Uni->Render = (VOID *)BZ6_UnitRender;
  Uni->Close = (VOID *)BZ6_UnitClose;

  return Uni;
} /* End of 'BZ6_UnitCreateCowSecond' function */

/* END OF 'u_randomcow.c' FILE */