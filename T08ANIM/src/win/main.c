/* FILE NAME: main.c
 * PROGRAMMER: BZ6
 * DATE: 17.06.2021
 * PURPOSE: 3D main module.
 */

#include <time.h>
#include "../anim/rnd/rnd.h"

/* Window class name */
#define BZ6_WND_CLASS_NAME "My Window Class Name"

/* Forward declaration */
LRESULT CALLBACK BZ6_WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG Msg;
  WNDCLASS wc;

  SetDbgMemHooks();

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszClassName = BZ6_WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = BZ6_WinFunc;

  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error regoister window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  /* Window creation */
  hWnd =
    CreateWindow(BZ6_WND_CLASS_NAME,
      "Title",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL,
      NULL,
      hInstance,
      NULL);

  ShowWindow(hWnd, CmdShow);
  UpdateWindow(hWnd);

  /* Message loop */
  while (TRUE)
    if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
    {
      if (Msg.message == WM_QUIT)
        break;
      DispatchMessage(&Msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 30, 0);

  return 30;
} /* End of 'WinMain' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *      HWND hWnd;
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT CALLBACK BZ6_WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  DBL t = clock() / 1000.0;
  static bz6PRIM PrF, PrH, PrBase;

  switch (Msg)
  {
  case WM_CREATE:
    BZ6_RndInit(hWnd);
    BZ6_RndPrimLoad(&PrF, "girl.obj");
    BZ6_RndPrimLoad(&PrH, "Harley.obj");
    BZ6_RndPrimCreateBase(&PrBase, VecSet1(0), VecSet(1, 0, 0), VecSet(0, 0, 1), 5, 8, 10, 15);
    SetTimer(hWnd, 30, 1, NULL);
    return 0;

  case WM_SIZE:
    BZ6_RndResize(LOWORD(lParam), HIWORD(lParam));
    
    /* Redraw frame */
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_TIMER:
    BZ6_RndStart();
    BZ6_RndCamSet(VecSet(100 * sin(t), 120, 100 * cos(t)), VecSet(0, 55, 0), VecSet(0, 1, 0));
    BZ6_RndPrimDraw(&PrF, MatrMulMatr3(MatrTranslate(VecSet(0, 0, -60)), MatrRotateY(0), MatrScale(VecSet1(0.5))));
    BZ6_RndPrimDraw(&PrH, MatrMulMatr4(MatrRotateX(-90), MatrRotateY(180), MatrTranslate(VecSet(0, 0, 60)), MatrScale(VecSet1(0.5))));
    BZ6_RndPrimDraw(&PrBase, MatrIdentity());
    BZ6_RndEnd();
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BZ6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_DESTROY:
    BZ6_RndPrimFree(&PrF);
    BZ6_RndPrimFree(&PrH);
    BZ6_RndPrimFree(&PrBase);
    BZ6_RndClose();
    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;

  case WM_KEYDOWN:
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'BZ6_WinFunc' function */

 /* END OF 'main.c' FILE */