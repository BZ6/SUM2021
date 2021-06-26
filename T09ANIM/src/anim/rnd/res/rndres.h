/* FILE NAME: rndres.h
 * PROGRAMMER: BZ6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation rendering resourse declaration module.
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "../rnd.h"

/* Maximum elements in string */
#define BZ6_STR_MAX 100

/***
 * Shaders stock functions
 ***/

/* Shaders stock */
#define BZ6_MAX_SHADERS 30

/* Shader representation type */
typedef struct tagbz6SHADER
{
  CHAR Name[BZ6_STR_MAX];
  INT ProgId;
} bz6SHADER;

/* Shader stock array and it size */
extern bz6SHADER BZ6_RndShaders[BZ6_MAX_SHADERS];
extern INT BZ6_RndShadersSize;

/* Shader stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID BZ6_RndShadersInit( VOID );

/* Shader stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID BZ6_RndShadersClose( VOID );

/* Shader add to stock function.
 * ARGUMENTS:
 *   - shader folder prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader number in stock.
 */
INT BZ6_RndShaderAdd( CHAR *FileNamePrefix );

/* Shader stock update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID BZ6_RndShadersUpdate( VOID );

/* Shader stock delete function.
 * ARGUMENTS: 
 *   - program Id:
 *       INT ProgId.
 * RETURNS: None.
 */
VOID BZ6_RndShdDelete( INT ProgId );

/***
 * Textures stock functions
 ***/

/* Texture representation type */
typedef struct tagbz6TEXTURE
{
  CHAR Name[BZ6_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} bz6TEXTURE;

/* Textures stock */
#define BZ6_MAX_TEXTURES 300
extern bz6TEXTURE BZ6_RndTextures[BZ6_MAX_TEXTURES]; /* Array of textures */
extern INT BZ6_RndTexturesSize;                      /* Textures array store size */

/* Texture stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
BZ6_RndTexInit( VOID );

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
INT BZ6_RndTextureAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );

/* Texture image add from file function.
 * ARGUMENTS:
 *   - name of image:
 *       CHAR *FileName; 
 * RETURNS:
 *   (INT) texture number.
 */
INT BZ6_RndTextureAddFromFile( CHAR *FileName );

/* Texture delete in stock function.
 * ARGUMENTS:
 *   - texture number:
 *       INT TexNo; 
 * RETURNS: NONE.
 */
VOID BZ6_RndTextureDelete( INT TexNo );

/* Texture close function.
 * ARGUMENTS: NONE; 
 * RETURNS: NONE.
 */
VOID BZ6_RndTexClose( VOID );

/***
 * Materials stock functions
 ***/

/* Material store type */
typedef struct tagbz6MATERIAL
{
  CHAR Name[BZ6_STR_MAX]; /* Material name */


  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */

  FLT Trans;                /* Transparency factor */
  INT Tex[8];               /* Texture references from texture table (or -1) */

  INT ShdNo;                /* Shader number in shader table */
} bz6MATERIAL;

/* Material stock */
#define BZ6_MAX_MATERIALS 300
bz6MATERIAL BZ6_RndMaterials[BZ6_MAX_MATERIALS]; /* Array of materials */
INT BZ6_RndMaterialsSize;                        /* Materials array store size */

INT BZ6_RndMtlApply( INT MtlNo );
INT BZ6_RndMaterialAdd( bz6MATERIAL *Mtl );
VOID BZ6_RndMtlInit( VOID );
VOID BZ6_RndMtlClose( VOID );

/***
 * Resourses functions
 ***/

VOID BZ6_RndResInit( VOID );
VOID BZ6_RndResClose( VOID );

#endif /* __rndres_h_ */

/* END OF 'rndres.h' FILE */