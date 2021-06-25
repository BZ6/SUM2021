/* FILE NAME: u_ctrl.c
 * PROGRAMMER: BZ6
 * DATE: 19.06.2021
 * PURPOSE: 3D animation control unit module.
 */

#include <stdio.h>
#include "units.h"

typedef struct
{
  BZ6_UNIT_BASE_FIELDS;
  VEC Pos;
  VEC CamDir;
  DBL Speed;
  DBL AngleSpeed;
  VEC CamRight;
} bz6UNIT_CTRL;

/* Unit control initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_CTRL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitInit( bz6UNIT_CTRL *Uni, bz6ANIM *Ani )
{
  Uni->Pos = VecSet(0, 0, 5);
  Uni->CamDir = VecSet(0, 0, -5);
  Uni->CamRight = VecSet(5, 0, 0);
  Uni->Speed = 2;
  Uni->AngleSpeed = 90;
} /* End of 'BZ6_UnitInit' function */

/* Unit control inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_CTRL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitResponse( bz6UNIT_CTRL *Uni, bz6ANIM *Ani )
{
  if (Ani->KeysClick['P'])
      BZ6_Anim.IsPause = !BZ6_Anim.IsPause;

  Uni->Pos =
    VecAddVec(Uni->Pos,
    VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed / 10 * Ani->Mdz));

  Uni->Pos =
    PointTransform(Uni->Pos,
      MatrRotateY(Ani->Keys[VK_LBUTTON] *
      Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx));
  
  Uni->CamRight = VecMulMatr(Uni->CamRight, MatrRotateY(Ani->Keys[VK_LBUTTON] *
      Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx));
  Uni->CamDir = VecMulMatr(Uni->CamDir, MatrRotateY(Ani->Keys[VK_LBUTTON] *
      Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx));

  /* Joystick */
  Uni->CamDir = VectorTransform(Uni->CamDir, MatrRotate(-Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->JY, Uni->CamRight));
  
  Uni->CamRight = VectorTransform(Uni->CamRight, MatrRotate(-Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->JX, VecSet(0, 1, 0)));
  
  Uni->CamDir = VectorTransform(Uni->CamDir, MatrRotate(-Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->JX, VecSet(0, 1, 0)));

  Uni->Pos =
    VecAddVec(Uni->Pos,
    VecMulNum(Uni->CamRight, Ani->GlobalDeltaTime * Uni->Speed * Ani->JR));

  Uni->Pos =
    VecAddVec(Uni->Pos,
    VecMulNum(Uni->CamDir, -Ani->GlobalDeltaTime * Uni->Speed * Ani->JZ)); 
} /* End of 'BZ6_UnitResponse' function */

/* Unit plane render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_CTRL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitRender( bz6UNIT_CTRL *Uni, bz6ANIM *Ani )
{ 
  BZ6_RndCamSet(Uni->Pos, VecAddVec(Uni->CamDir, Uni->Pos), VecSet(0, 1, 0));
} /* End of 'BZ6_UnitRender' function */

/* Unit plane deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       bz6UNIT_CTRL *Uni;
 *   - animation context:
 *       bz6ANIM *Ani;
 * RETURNS: None.
 */
static VOID BZ6_UnitClose( bz6UNIT_CTRL *Uni, bz6ANIM *Ani )
{
} /* End of 'BZ6_UnitClose' function */

/* Unit plane creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (bz6UNIT *) pointer to created unit.
 */
bz6UNIT * BZ6_UnitCreateCtrl( VOID )
{
  bz6UNIT *Uni;

  if ((Uni = (bz6UNIT *)BZ6_AnimUnitCreate(sizeof(bz6UNIT_CTRL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)BZ6_UnitInit;
  Uni->Render = (VOID *)BZ6_UnitRender;
  Uni->Response = (VOID *)BZ6_UnitResponse;

  return Uni;
} /* End of 'BZ6_UnitCreatePlane' function */

/* END OF 'u_ctrl.c' FILE */