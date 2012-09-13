#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <time.h>
#include <string.h>

#define MUL 2
#define Xmul 0.03
#define Ymul 0.03
#define INITXY 150
//int X = INITXY, Y=INITXY;
int X = INITXY, Y=INITXY;
double X1;
double Y1;
#define TIER 2

#define VER_LOOPING 1
#define VER_CO 2

const double T1 = 0.01;
const double X0 = 0.0;
const double Y0 = 0.0;
const double T0 = 0.0;

double DT, DX, DY, DTDXDX, DTDYDY;
int hx=0,hy=0; 
clock_t lasttime;
int reshape = 0, rx,ry;
int drawing = 0;


// totally N*N*2 element,   first dimension    x*N*2    second dimension  y*2     third dimension  t
//#define U(t,x,y)   u[ (x)*Y*2 + (y)*2 + ((t)&1)]
//double *u=0;


double u[INITXY][INITXY][2];
#define U(t, x, y) u[x][y][(t)&1]



int firsttime = 1;
int hist[INITXY][INITXY];
int curver = VER_CO;

static inline void kernel(int t, int x, int y)
{
    if (x == 0 || x == X-1 || y == 0 || y == Y-1)
    {
      U(t+1,x,y) = 0.0;
    }
    else/**/
    U(t+1,x,y) =   DTDXDX * (U(t,x+1,y) - 2.0 * U(t,x,y) + U(t,x-1,y))
                 + DTDYDY * (U(t,x,y+1) - 2.0 * U(t,x,y) + U(t,x,y-1))
                 + U(t,x,y);
}


//static inline void coarse_kernel (int t0, int t1, 

//static inline lifted

#define ltThresh 10
const int ds = 1;
void walk2(int t0, int t1, 
	   int x0, int dx0, int x1, int dx1,
	   int y0, int dy0, int y1, int dy1)
{
  /*  if (firsttime)
    {
      printf ("calling t0 = %d, t1 = %d, x0 = %d, y0 = %d, x1 = %d, y1 = %d \n", t0, t1, x0, y0, x1, y1);
      }/**/

  int lt = t1 - t0;
  //if (lt==0)  printf ("lt is zero\n");

  if (lt == 1) {
    int x, y;
    //hist[x1-x0][y1-y0]++;
    U(t1,hx,hy)=5;
    for (x = x0; x < x1; x++)
      for (y = y0; y < y1; y++)
	kernel(t0, x, y);
  } else if (lt > 1) {
    //parallelize it
    if (2 * (x1 - x0) + (dx1 - dx0) * lt >= 4 * ds * lt) {
      int xm = (2 * (x0 + x1) + (2 * ds + dx0 + dx1) * lt) / 4;
      walk2(t0, t1, x0, dx0, xm, -ds, y0, dy0, y1, dy1);
      walk2(t0, t1, xm, -ds, x1, dx1, y0, dy0, y1, dy1);
    } else if (2 * (y1 - y0) + (dy1 - dy0) * lt >= 4 * ds * lt) {
      int ym = (2 * (y0 + y1) + (2 * ds + dy0 + dy1) * lt) / 4;
      walk2(t0, t1, x0, dx0, x1, dx1, y0, dy0, ym, -ds);
      walk2(t0, t1, x0, dx0, x1, dx1, ym, -ds, y1, dy1);
    } else {
      //if lt > THRESH ... 
      if (lt > ltThresh) {
	int halflt = lt / 2;
	walk2(t0, t0 + halflt, x0, dx0, x1, dx1, y0, dy0, y1, dy1);
	walk2(t0 + halflt, t1, 
	      x0 + dx0 * halflt, dx0, x1 + dx1 * halflt, dx1,
	      y0 + dy0 * halflt, dy0, y1 + dy1 * halflt, dy1);
      }
      else
	{
	  int t,x,y;
	  for (t=0; t<lt; ++t)
	    {
	      /*
	      walk2(t+t0,t+t0+1, 
		    x0 + dx0 * t, dx0, x1 + dx1 * t, dx1,
		    y0 + dy0 * t, dy0, y1 + dy1 * t, dy1);		    
	      */
	      //hist[x1-x0][y1-y0]++;
	      U(t1,hx,hy)=5;
	      for (x = x0; x < x1; x++)
		for (y = y0; y < y1; y++)
		    kernel(t0+t, x, y);
	      x0 += dx0;   y0 += dy0;
	      x1 += dx1;   y1 += dy1;
	    }
	}
    }
  }
}

void rect(int t0, int t1, int x0, int x1, int y0, int y1)
{
  printf ("using cache oblivious version\n");
  walk2(t0, t1, x0, 0, x1, 0, y0, 0, y1, 0);
}


void rectiter(int t0, int t1, int x0, int x1, int y0, int y1)
{
  int t, x, y;
  printf ("using loop version\n");
  for (t=t0; t<t1; t++)
    {
      U(t,hx,hy)=5;
      for (x=x0; x<x1; x++)
	for (y=y0; y<y1; y++)
	  kernel(t, x, y); 
    }
}


/*
void init(void)
{
  if (!u)
    {
      u = (double*)malloc(sizeof(double)*X*Y*2);
      memset(u,0,sizeof(double)*X*Y*2);
    } else free(u);
    }*/

static void key(unsigned char k, int x, int y)
{
  switch (k) {
  case 27:  /* Escape */
  case 'q': case 'Q': 
    exit(0);
  case 'c': curver = VER_CO; 
    printf ("using cache oblivious version\n");
    break;
  case 'l': curver = VER_LOOPING; 
    printf ("using looping version\n");
    break;

  }
  glutPostRedisplay();
}


#define min(x,y)  (x<y?x:y)
#define max(x,y)  (x>y?x:y)
void motionPassive(int x, int y)
{
  hx = (int)((float)x/MUL);
  hy = (int)((float)y/MUL);
  hx = min(max(hx,0),X-1);
  hy = min(max(hy,0),Y-1);
}


void RenderString(float x, float y, void *font, char* string, float r, float g, float b)
{  
  char *c;
  glColor3f(r,g,b);
  glRasterPos3f(x,y,0);
  for (c=string; *c != '\0'; c++) 
    {
      glutBitmapCharacter(font, *c);
    }
}


int t = 0;
void draw(void)
{
  int x,y;
  if (reshape) 
    {
      X=rx/MUL;
      Y=ry/MUL;
      glViewport (0,0,rx,ry);
      //u=(double*)realloc(u,sizeof(double)*X*Y*2);
      //memset(u,0,sizeof(double)*X*Y*2);
      reshape = 0;
      printf ("X=%d, Y=%d\n", X, Y);

      X1 = X*Xmul;
      Y1 = Y*Ymul;   //how do we enlongate that?
      DT = (T1 - T0) / max(X,Y);
      DX = (X1 - X0) / (X-1);
      DY = (Y1 - Y0) / (Y-1);
      DTDXDX = DT / (DX * DX);
      DTDYDY = DT / (DY * DY);
    }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glFrustum (-X/2, X/2, -Y/2, Y/2, 100, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0,0,-100,  0,0,0,  0,-1,0);
  glTranslatef (-X/2, -Y/2, 0);
  glDisable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  if (firsttime)
    {
      memset(hist,0,sizeof(int)*INITXY*INITXY);
    }
  
  if (curver == VER_LOOPING)
    {
      //printf ("using looping version\n");
      rectiter(t, t+max(X,Y)*TIER, 0, X, 0, Y);
    }
  else
    {
      //printf ("using cache oblivious version\n");
      rect(t, t+max(X,Y)*TIER, 0, X, 0, Y);
    }
  
  if (firsttime)
  {
    int i,j,tmp;
    for (i=0;i<INITXY;i++)
      for (j=i;j<INITXY;j++)
	{
	  tmp = (i==j) ? hist[i][j] : hist[i][j] + hist[j][i];
	  if (tmp)
	    printf ("leave of size (%d,%d) or (%d,%d) %d\n", i, j, j, i, tmp);
	}
    firsttime = 0;
  }


  t+=max(X,Y)*TIER;
  glClearColor(0.0, 0.0, 0.0, 0.0);
  for (x=0; x<X; x++) {
    for (y=0; y<Y; y++) {
      glColor3d(U(0,x,y), 0.5*U(0,x,y), 1.0-0.8*U(0,x,y));
      glBegin(GL_POLYGON); {
	glVertex3f(x, y, 0);
	glVertex3f(x, y+1, 0);
	glVertex3f(x+1, y+1, 0);
	glVertex3f(x+1, y, 0);
      } glEnd();
    }
  }

  {
    char s[20];
    sprintf (s, "frame rate: %f",   (1/((float)(clock()-lasttime)/(float)CLOCKS_PER_SEC)));
    lasttime = clock();

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    RenderString(-1, -1, GLUT_BITMAP_TIMES_ROMAN_24, s, 1,1,0);

    //sprintf (s, "current version : %s",  (curver == VER_CO) ? "cache oblivious" : "looping");
    //    RenderString(-1, -0.8, GLUT_BITMAP_TIMES_ROMAN_24, s, 1,1,0);
  }

  glFlush();
  glutSwapBuffers();
}

void timerCallback (int value)
{
  if (!drawing) 
    {
      drawing = 1;
      draw();
      drawing = 0;
    }
  glutTimerFunc (15, timerCallback, 0);
}


void reshapeFun(int width, int height)
{
  glViewport (0,0,width,height);
  reshape = 1;
  rx = width;
  ry = height;
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 0);
  glutInitWindowSize(X*MUL, Y*MUL);
  glutInitDisplayMode(GLUT_RGB);// | GLUT_DOUBLE);
  glutCreateWindow("Cache Oblivious Stencil Demo");


  //  init();
  glutDisplayFunc(draw);
  glutKeyboardFunc(key);
  glutPassiveMotionFunc(motionPassive);
  glutTimerFunc (15, timerCallback, 0);
  lasttime = clock();
  glutReshapeFunc(reshapeFun);

  reshape = 1;
  rx = X*MUL;  ry = Y*MUL;
  glutMainLoop();
  //  init();


  return 0;
}
