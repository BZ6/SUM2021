#include <windows.h>

#define GRID_H 30
#define GRID_W 30

typedef DOUBLE DBL;

typedef struct tagVEC
{
  DBL x, y, z;
} VEC;

/* Forward declaration */
VOID GlobeSet( INT w, INT h );
VOID GlobeDraw( HDC hDC, DBL Size );
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);