/* FILE NAME: rndtxt.crndtxt.c
 * PROGRAMMER: BZ6
 * DATE: 23.06.2021
 * PURPOSE: 3D animation rendering texture handle functions module.
 */

#include <stdio.h>
#include <string.h>

#include "rndres.h"

/* Texture stock array and it size */
bz6TEXTURE BZ6_RndTextures[BZ6_MAX_TEXTURES]; /* Array of textures */
INT BZ6_RndTexturesSize;                      /* Textures array store size */


/* Shader stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
BZ6_RndTexInit( VOID )
{
  BZ6_RndTexturesSize = 0;

} /* End of 'BZ6_RndTexInit' function */


/* END OF 'rndtxt.c' FILE */