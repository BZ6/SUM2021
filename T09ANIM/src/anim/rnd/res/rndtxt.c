/* FILE NAME: rndtxt.crndtxt.c
 * PROGRAMMER: BZ6
 * DATE: 23.06.2021
 * PURPOSE: 3D animation rendering texture handle functions module.
 */

#include <stdio.h>
#include <string.h>

#include "../../anim.h"

/* Texture stock array and it size */
bz6TEXTURE BZ6_RndTextures[BZ6_MAX_TEXTURES]; /* Array of textures */
INT BZ6_RndTexturesSize;                      /* Textures array store size */

/* Texture stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
BZ6_RndTexInit( VOID )
{
  BZ6_RndTexturesSize = 0;
} /* End of 'BZ6_RndTexInit' function */

/* Texture image add in stock function.
 * ARGUMENTS:
 *   - name of image:
 *       CHAR *Name; 
 *   - size of image:
 *       INT W, H;
 *   - texture data:
 *       VOID *Bits.
 * RETURNS:
 *   (INT) texture number.
 */
INT BZ6_RndTextureAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  INT n;

  if (BZ6_RndTexturesSize >= BZ6_MAX_TEXTURES)
    return -1;

  /* Allocate texture space */
  glGenTextures(1, &BZ6_RndTextures[BZ6_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, BZ6_RndTextures[BZ6_RndTexturesSize].TexId);

  n = log(W > H ? W : H) / log(2);
  n = n < 1 ? 1 : n;

  glTexStorage2D(GL_TEXTURE_2D, n, C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H,
                      C == 4 ? GL_RGBA : C == 3 ? GL_RGB : GL_LUMINANCE, GL_UNSIGNED_BYTE, Bits);

  /* Upload texture */
  glGenerateMipmap(GL_TEXTURE_2D);             
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strncpy(BZ6_RndTextures[BZ6_RndTexturesSize].Name, Name, BZ6_STR_MAX - 1);
  BZ6_RndTextures[BZ6_RndTexturesSize].W = W;
  BZ6_RndTextures[BZ6_RndTexturesSize].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);

  return BZ6_RndTexturesSize++;
} /* End of 'BZ6_RndTextureAddImg' function */

/* Texture image add from file function.
 * ARGUMENTS:
 *   - name of image:
 *       CHAR *FileName; 
 * RETURNS:
 *   (INT) texture number.
 */
INT BZ6_RndTextureAddFromFile( CHAR *FileName )
{
   return -1;
} /* End of 'BZ6_RndTextureAddFromFile' function */

/* Texture delete in stock function.
 * ARGUMENTS:
 *   - texture number:
 *       INT TexNo; 
 * RETURNS: NONE.
 */
VOID BZ6_RndTextureDelete( INT TexNo )
{
  if (TexNo < 0 || TexNo >= BZ6_RndTexturesSize)
    return;
  glDeleteTextures(1, &BZ6_RndTextures[TexNo].TexId);

  BZ6_RndTexturesSize--;
} /* End of 'BZ6_RndTextureDelete' function */

/* Texture close function.
 * ARGUMENTS: NONE; 
 * RETURNS: NONE.
 */
VOID BZ6_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < BZ6_RndTexturesSize; i++)
    glDeleteTextures(1, &BZ6_RndTextures[i].TexId);
} /* End of 'BZ6_RndTexClose' function */

/* END OF 'rndtxt.c' FILE */