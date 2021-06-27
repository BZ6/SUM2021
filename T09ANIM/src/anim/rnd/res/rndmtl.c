/* FILE NAME : rndmtl.c
 * PROGRAMMER: BZ6
 * DATE      : 21.06.2021 
 * PURPOSE   : WinAPI Animation startup module
 */

#include "../../anim.h"

static struct
{
  CHAR *Name;
  VEC Ka, Kd, Ks;
  FLT Ph;
} MatLib[] =
{
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32},
  {"Brass",         {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974},
  {"Bronze",        {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
  {"Chrome",        {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
  {"Copper",        {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
  {"Gold",          {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
  {"Peweter",       {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
  {"Silver",        {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
  {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
  {"Turquoise",     {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
  {"Ruby",          {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
  {"Polished Gold", {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
  {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
  {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
  {"Jade",          {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
  {"Obsidian",      {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
  {"Pearl",         {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
  {"Emerald",       {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
  {"Black Rubber",  {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
};
#define MAT_N (sizeof(MatLib) / sizeof(MatLib[0]))


bz6MATERIAL BZ6_RndMaterials[BZ6_MAX_MATERIALS];
INT BZ6_RndMaterialsSize;

bz6MATERIAL * BZ6_RndMtlGet( INT MtlNo )
{
  if (MtlNo < 0 || MtlNo >= BZ6_RndMaterialsSize)
    MtlNo = 0;
  return &BZ6_RndMaterials[MtlNo];
}

INT BZ6_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  bz6MATERIAL *mtl;
  
  mtl = BZ6_RndMtlGet(MtlNo);

  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= BZ6_RndShadersSize)
    prg = 0;
  prg = BZ6_RndShaders[prg].ProgId;

  glUseProgram(prg);
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";

    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, BZ6_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  return prg;
} /* End of 'BZ6_RndMtlApply' function */



INT BZ6_RndMaterialAdd( bz6MATERIAL *Mtl )
{
  if (BZ6_RndMaterialsSize >= BZ6_STR_MAX)
    return -1;

  BZ6_RndMaterials[BZ6_RndMaterialsSize] = *Mtl;
  return BZ6_RndMaterialsSize++;
}

bz6MATERIAL MtlGetDef( VOID )
{
  return BZ6_RndMaterials[0];
}

VOID BZ6_RndMtlInit( VOID )
{
  INT i;
  bz6MATERIAL mtl;

  strcpy(mtl.Name, "DEFAULT");

  mtl.Ka = VecSet1(0.1);
  mtl.Kd = VecSet1(1);
  mtl.Ks = VecSet1(0);

  mtl.Ph = 30;

  mtl.Trans = 1;
  mtl.ShdNo = 0;

  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;

  BZ6_RndMaterialsSize = 0;
  BZ6_RndMaterialAdd(&mtl);
}

/*bz6MATERIAL * MaterialGet( INT MtlNo )
{
  if (MtlNo < 0 || MtlNo > ND4_RndMaterialsSize)
    return &BZ6_RndMaterials[0];
} */

VOID BZ6_RndMtlClose( VOID )
{
  BZ6_RndMaterialsSize = 0;
}


/* END OF 'rndmtl.c' FILE */