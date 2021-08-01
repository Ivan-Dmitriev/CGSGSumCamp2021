/* FILE NAME  : t03mandl.cpp
 * PROGRAMMER : ID3
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Mandelbrot & Julia set drawing program.
 */

#include <glut.h>

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <thread>

#include <commondf.h>

#define FRAME_W 300
#define FRAME_H 300

static INT Zoom = 1;
static BYTE Frame[FRAME_H][FRAME_W][4];
DOUBLE SyncTime, FPS;
std::thread Th[6];

struct frame {
  INT W = 500, H = 500;
  //BYTE Frame[FRAME_H][FRAME_W][4];

  VOID DrawFrame( VOID );
};

struct timer {
  INT64 Freq;

  timer( VOID )
  {
    LARGE_INTEGER t;
    QueryPerformanceFrequency(&t);
    Freq = t.QuadPart;
  } 
  DOUBLE Get( VOID )
  {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return (DOUBLE)t.QuadPart / Freq;
  }
};

struct cmpl {
  DOUBLE Real, Imag;
  
  cmpl( DOUBLE R = 0, DOUBLE I = 0 ) : Real(R), Imag(I) 
  {
  }

  cmpl & operator+=( const cmpl &val ) 
  {
    Real += val.Real;
    Imag += val.Imag;
    return *this;
  }
  cmpl & operator*=( const cmpl &val ) 
  {
    Real = Real * val.Real - Imag * val.Imag;
    Imag = Real * val.Imag + Imag * val.Real;
    return *this;
  }

  DOUBLE Normalize( cmpl val ) 
  {
    return sqrt(val.Real * val.Real + val.Imag * val.Imag);
  }
  DOUBLE operator~( void )
  {
    return Real * Real + Imag * Imag;
  }
  INT MandelBrot( cmpl Z );
  INT Julia( cmpl Z, cmpl C );
};

cmpl operator+( const cmpl &C1, const cmpl &C2 )
{
  return cmpl(C1.Real + C2.Real, C1.Imag + C2.Imag);
}

cmpl operator*( const cmpl &C1, const cmpl &C2 )
{
  return cmpl(C1.Real * C2.Real - C1.Imag * C2.Imag, C1.Real * C2.Imag + C1.Imag * C2.Real);
}

VOID PutPixel( INT x, INT y, INT r, INT g, INT b )
{
  //assert(x < 0 || x >= FRAME_W);
  //assert(y < 0 || y >= FRAME_H);
  if (x < 0 || y < 0 || x >= FRAME_W || y >= FRAME_H)
    return;

  Frame[y][x][0] = b;
  Frame[y][x][1] = g;
  Frame[y][x][2] = r;
}

INT cmpl::MandelBrot( cmpl Z )
{
  INT n = 0;
  cmpl Z0 = Z;

  while ((n < 255) && (~Z < 4))
  {
    Z = Z * Z;
    Z += Z0;
    n++;
  }
  return n;
}

INT cmpl::Julia( cmpl Z, cmpl C )
{
  INT n = 0;

  while ((n < 255) && (~Z < 4))
  {
    Z = Z * Z * Z;
    Z += C;
    n++;
  }
  return n;
}

VOID DrawMandelbrot0( VOID )
{
  DOUBLE X0 = -2, X1 = 2, Y0 = -2, Y1 = 2, kt = 300;
  INT n;
  cmpl Z, C;

  for (INT ys = 0; ys < FRAME_H / 2; ys++)
    for (INT xs = 0; xs < FRAME_W / 4; xs++)
    {
       C = cmpl(0.47 + 0.1 * sin(SyncTime * 3), 0.1 * sin(0.5 * SyncTime));
       Z = cmpl(xs * (X1 - X0) / FRAME_W + X0, ys * (Y1 - Y0) / FRAME_H + Y0);
       n = Z.Julia(Z, C);

       if (n < 16)
         PutPixel(xs, ys, n * 8, n * 8, n * 4 + 128);
       else if (n >= 16 && n < 64)
         PutPixel(xs, ys, 128 + n - 16 * sin(SyncTime), (128 + n - 16), 192 + n - 16);
       else 
         PutPixel(xs, ys, kt - n * sin(SyncTime), (128 + (kt - n) / 2), kt - n);
    }
}

VOID DrawMandelbrot1( VOID )
{
  DOUBLE X0 = -2, X1 = 2, Y0 = -2, Y1 = 2, kt = 300;
  INT n;
  cmpl Z, C;

  for (INT ys = 0; ys < FRAME_H / 2; ys++)
    for (INT xs = FRAME_W / 4; xs < FRAME_W / 2; xs++)
    {
       C = cmpl(0.47 + 0.1 * sin(SyncTime * 3), 0.1 * sin(0.5 * SyncTime));
       Z = cmpl(xs * (X1 - X0) / FRAME_W + X0, ys * (Y1 - Y0) / FRAME_H + Y0);
       n = Z.Julia(Z, C);

       if (n < 16)
         PutPixel(xs, ys, n * 8, n * 8, n * 4 + 128);
       else if (n >= 16 && n < 64)
         PutPixel(xs, ys, 128 + n - 16 * sin(SyncTime), (128 + n - 16), 192 + n - 16);
       else 
         PutPixel(xs, ys, kt - n * sin(SyncTime), (128 + (kt - n) / 2), kt - n);
    }
}


VOID DrawMandelbrot2( VOID )
{
  DOUBLE X0 = -2, X1 = 2, Y0 = -2, Y1 = 2, kt = 300;
  INT n;
  cmpl Z, C;

  for (INT ys = FRAME_H / 2; ys < FRAME_H; ys++)
    for (INT xs = FRAME_W / 2; xs < FRAME_W; xs++)
    {
       C = cmpl(0.47 + 0.1 * sin(SyncTime * 3), 0.1 * sin(0.5 * SyncTime));
       Z = cmpl(xs * (X1 - X0) / FRAME_W + X0, ys * (Y1 - Y0) / FRAME_H + Y0);
       n = Z.Julia(Z, C);

       if (n < 16)
         PutPixel(xs, ys, n * 8, n * 8, n * 4 + 128);
       else if (n >= 16 && n < 64)
         PutPixel(xs, ys, 128 + n - 16 * sin(SyncTime), (128 + n - 16), 192 + n - 16);
       else 
         PutPixel(xs, ys, kt - n * sin(SyncTime), (128 + (kt - n) / 2), kt - n);
    }
}

VOID DrawMandelbrot3( VOID )
{
  DOUBLE X0 = -2, X1 = 2, Y0 = -2, Y1 = 2, kt = 300;
  INT n;
  cmpl Z, C;

  for (INT ys = 0; ys < FRAME_H / 2; ys++)
    for (INT xs = FRAME_W / 2; xs < FRAME_W; xs++)
    {
      C = cmpl(0.47 + 0.1 * sin(SyncTime * 3), 0.1 * sin(0.5 * SyncTime));
      Z = cmpl(xs * (X1 - X0) / FRAME_W + X0, ys * (Y1 - Y0) / FRAME_H + Y0);
      n = Z.Julia(Z, C);

      if (n < 16)
        PutPixel(xs, ys, n * 8, n * 8, n * 4 + 128);
      else if (n >= 16 && n < 64)
        PutPixel(xs, ys, 128 + n - 16 * sin(SyncTime), (128 + n - 16), 192 + n - 16);
      else 
        PutPixel(xs, ys, kt - n * sin(SyncTime), (128 + (kt - n) / 2), kt - n);
    }
}

VOID DrawMandelbrot4( VOID )
{
  DOUBLE X0 = -2, X1 = 2, Y0 = -2, Y1 = 2, kt = 300;
  INT n;
  cmpl Z, C;

  for (INT ys = FRAME_H / 2; ys < FRAME_H; ys++)
    for (INT xs = 0; xs < FRAME_W / 4; xs++)
    {
       C = cmpl(0.47 + 0.1 * sin(SyncTime * 3), 0.1 * sin(0.5 * SyncTime));
       Z = cmpl(xs * (X1 - X0) / FRAME_W + X0, ys * (Y1 - Y0) / FRAME_H + Y0);
       n = Z.Julia(Z, C);

       if (n < 16)
         PutPixel(xs, ys, n * 8, n * 8, n * 4 + 128);
       else if (n >= 16 && n < 64)
         PutPixel(xs, ys, 128 + n - 16 * sin(SyncTime), (128 + n - 16), 192 + n - 16);
       else 
         PutPixel(xs, ys, kt - n * sin(SyncTime), (128 + (kt - n) / 2), kt - n);
    }
}

VOID DrawMandelbrot5( VOID )
{
  DOUBLE X0 = -2, X1 = 2, Y0 = -2, Y1 = 2, kt = 300;
  INT n;
  cmpl Z, C;

  for (INT ys = FRAME_H / 2; ys < FRAME_H; ys++)
    for (INT xs = FRAME_W / 4; xs < FRAME_W / 2; xs++)
    {
       C = cmpl(0.47 + 0.1 * sin(SyncTime * 3), 0.1 * sin(0.5 * SyncTime));
       Z = cmpl(xs * (X1 - X0) / FRAME_W + X0, ys * (Y1 - Y0) / FRAME_H + Y0);
       n = Z.Julia(Z, C);

       if (n < 16)
         PutPixel(xs, ys, n * 8, n * 8, n * 4 + 128);
       else if (n >= 16 && n < 64)
         PutPixel(xs, ys, 128 + n - 16 * sin(SyncTime), (128 + n - 16), 192 + n - 16);
       else 
         PutPixel(xs, ys, kt - n * sin(SyncTime), (128 + (kt - n) / 2), kt - n);
    }
}

VOID frame::DrawFrame( VOID )
{
  DrawMandelbrot1();
  DrawMandelbrot2();
  DrawMandelbrot3();
  DrawMandelbrot4();
}

VOID Timer( VOID )
{   
  LONG t;
  static LONG StartTime = -1, FPSTime, FrameCount;

  t = clock();
  if (StartTime == -1)
    StartTime = FPSTime = t;
  SyncTime = (t - StartTime) / (DOUBLE)CLOCKS_PER_SEC;
  FrameCount++;
  if (t - FPSTime > 1 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (DOUBLE)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
  }
}

/* Display GLUT callback function */
VOID Display( VOID )
{
  //CHAR Buf[100];
  //SetWindowText(FindWindow(NULL, "PETROVICH"), Buf);
  glClear(GL_COLOR_BUFFER_BIT);
  Timer();
  
  Th[0] = std::thread(DrawMandelbrot0);
  Th[1] = std::thread(DrawMandelbrot1);
  Th[2] = std::thread(DrawMandelbrot2);
  Th[3] = std::thread(DrawMandelbrot3);
  Th[4] = std::thread(DrawMandelbrot4);
  Th[5] = std::thread(DrawMandelbrot5);
  
  Th[0].join();
  Th[1].join();
  Th[2].join();
  Th[3].join();
  Th[4].join();
  Th[5].join();

  //DrawMandelbrot0();
  //DrawMandelbrot1();
  //DrawMandelbrot2();
  //DrawMandelbrot3();
  //DrawMandelbrot4();
  //DrawMandelbrot5();


  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);

  glDrawPixels(FRAME_W, FRAME_H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

VOID Keyboard( BYTE Key, INT x, INT y )
{  
  if (Key == 27)
    exit(30);
  else if (Key == 'f' || Key == 'F')
    glutFullScreen();
  else if (Key == '+' || Key == '=')
    Zoom++;
  else if (Key == '_' || Key == '-')
    Zoom--;
}

/* The proram entry point */
INT main( INT ArgC, CHAR *ArgV[])
{
  INT n = std::thread::hardware_concurrency();

  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 700);
  glutCreateWindow("T02MANDL");
  
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glClearColor(0.30, 0.47, 0.8, 1);
  glutMainLoop();

  return 0;
}  /* End of 'main' function */

/* END OF 't03mandl.cpp' FILE */