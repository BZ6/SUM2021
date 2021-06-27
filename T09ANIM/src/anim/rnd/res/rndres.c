/* FILE NAME : rndres.c
 * PROGRAMMER: BZ6
 * DATE      : 21.06.2021 
 * PURPOSE   : WinAPI Animation startup module
 */

#include "../../anim.h"

VOID BZ6_RndResInit( VOID )
{
  BZ6_RndShadersInit();
  BZ6_RndTexInit();
  BZ6_RndMtlInit();
}

VOID BZ6_RndResClose( VOID )
{ 
  BZ6_RndMtlClose();
  BZ6_RndTexClose();
  BZ6_RndShadersClose();
}


/* END OF 'rndres.c' FILE */