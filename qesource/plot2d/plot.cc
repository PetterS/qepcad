/*****************************************************************
 * ADJ2D_plot - the renderer for QEPCADB's facilities for plotting
 * CADs of R^2.  The "rend" extension of QEPCADB has it's own
 * format for sending out data describing a CAD of R^2.  This
 * program reads that data and renders it in a window.
 *****************************************************************/
extern "C" {
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
};
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Point.h"
inline void glVertex2(const Point &p) { glVertex2d(p.x,p.y); }

/*****************************************************************
 ******  CLASS DEFINITIONS
 ******************************************************************/
class CADColors
{
public:
  void glSetColor(char c, char w) const; // w is 'L' or 'D'
};

class CADELT
{
public:
  virtual bool read(istream &in) = 0;
  virtual void glRend(const CADColors &C) = 0;
};

class SNoverSR : public CADELT
{
  char colorType;
  vector<Point> V;
public:
  bool read(istream &in);
  void glRend(const CADColors &C);
};

class SRoverSR : public CADELT
{
  char colorType;
  vector<Point> V;
public:
  bool read(istream &in);
  void glRend(const CADColors &C);
};

class SRoverSN : public CADELT
{
  char colorType;
  Point a, b;
public:
  bool read(istream &in);
  void glRend(const CADColors &C);
};

class SNoverSN : public CADELT
{
  char colorType;
  Point a;
public:
  bool read(istream &in);
  void glRend(const CADColors &C);
};

class SN : public CADELT
{
  char colorType;
  double x;
public:
  bool read(istream &in);
  void glRend(const CADColors &C);
};

class SR : public CADELT
{
  char colorType;
  double x1, x2;
public:
  bool read(istream &in);
  void glRend(const CADColors &C);
};

/*****************************************************************
 ******  GLOBALS
 ******************************************************************/
pthread_mutex_t M,F;
vector<CADELT*> CE;
bool newdata = true;
CADColors Colors;
string name;
istream *inp;
int d1,d2;

/*****************************************************************
 ******  Function for the data-reading thread
 ******************************************************************/
void* readdata(void *x)
{
  vector<CADELT*> E;
  istream &in = *inp;
  int flag;
  char c;
  do {
    while( in >> c )
    {
      if (c == 'L' || c == 'P' || c == 'R' || c == 'V' || c == 'C' || c == 'S') {
	CADELT *p = 0;
	if      (c == 'L') p = new SNoverSR;
	else if (c == 'P') p = new SRoverSR;
	else if (c == 'R') p = new SRoverSN;
	else if (c == 'V') p = new SN;
	else if (c == 'C') p = new SR;
	else if (c == 'S') p = new SNoverSN;
	p->read(in);
	E.push_back(p); }
      else if (c == 'F') { /******* Refresh it! **************/
	pthread_mutex_lock(&F);
	newdata = true;
	pthread_mutex_unlock(&F);
	pthread_mutex_lock(&M);
	swap(CE,E);
	pthread_mutex_unlock(&M);
	for(int i = 0; i < E.size(); i++) delete E[i];
	E.clear(); }
      else if (c == 'E') { /******* Exit! *******************/
	return 0;
      }
      else { cerr << "Unknown graphics command!" << endl; exit(1); }
    }

    return 0;
   
  }while(1);
  return 0;
}

/*****************************************************************
 ******  CALL-BACK FUNCTIONS
 ******************************************************************/
void display()
{
  pthread_mutex_lock(&M);
  glClear(GL_COLOR_BUFFER_BIT);
  for(int i = 0; i < CE.size(); i++)
    CE[i]->glRend(Colors);
  pthread_mutex_unlock(&M);  
  glutSwapBuffers();
}
void  idle(void)
{
  static int i = 0;
  ++i;
  if(i % 100000 == 0) cerr << "10K...";
  pthread_mutex_lock(&F);
  if (newdata) {
      glutPostRedisplay();
      newdata = false; }
  pthread_mutex_unlock(&F);  
}

// I'm using this instead of and "idle" function
void  checkForChanges(int t) 
{
  pthread_mutex_lock(&F);
  if (newdata) {
      glutPostRedisplay();
      newdata = false; }
  pthread_mutex_unlock(&F);  
  glutTimerFunc(30,checkForChanges,0);              	
}
void reshape(GLsizei w, GLsizei h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, d1, 0, d2, -10, 10);
   glMatrixMode(GL_MODELVIEW);
   glutPostRedisplay();
}

/*****************************************************************
 ******  main function for plotting program.
 ******************************************************************/
int main(int argc, char* argv[])
{
  //char B[11] = {'\0'};
  //cin.rdbuf()->pubsetbuf(B,1);
  inp = &cin;
  istream &in = cin;

  /***************************************
  ** read in window size.  Window is not allowed to be larger than
  ** 1000x1000, and the arrays winX and winY are defined to contain
  ** the coordinates of the window corners.
  ****************************************/
  in >> d1 >> d2;
  if (!in) { cerr << "Couldn't read window dimensions!" << endl; exit(1); }
  d1 = d1 > 1000 ? 1000 : d1;
  d2 = d2 > 1000 ? 1000 : d2;


  /***************************************
  ** GL and GLUT initialization.  
  ****************************************/
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(d1,d2);
  glutInit(&argc, argv);
  glutCreateWindow("CADPlotter");

  glViewport(0, 0, d1, d2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,d1,0,d2,-10,10);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(1.0, 1.0, 1.0, 0.0);

  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  // glDepthFunc(GL_LEQUAL);
  //  glEnable(GL_DEPTH_TEST);

  glPointSize(2);
  glLineWidth(2);
  glutDisplayFunc(display);
  //  glutIdleFunc(idle); <-- I removed this because it's simply called too often
  glutReshapeFunc(reshape);

  // CREATE MUTEX
  int ecmM = pthread_mutex_init(&M,NULL);
  int ecmF = pthread_mutex_init(&F,NULL);
  if (ecmM || ecmF) { cerr << "Mutex could not be created!" << endl; exit(1); }
  
  // CREATE THREAD
  pthread_t t;
  int ect = pthread_create(&t,0,readdata,0);
  if (ect) { cerr << "Thread could not be created!" << endl; exit(1); }

  glutTimerFunc(30,checkForChanges,0);  
  glutMainLoop();
  return 0;
}

/*****************************************************************
 ******  MEMBER FUNCTION DEFINITIONS
 ******************************************************************/
void CADColors::glSetColor(char c, char w) const
{
  if (c == 'T' && w == 'D') { glColor3f(1,0,0); }
  if (c == 'T' && w == 'L') { glColor3f(153.0/255.0,1,1); }
  if (c == 'F' && w == 'D') { glColor3f(153/255.0,102.0/255.0,0); }
  if (c == 'F' && w == 'L') { glColor3f(1,1,204.0/255.0); }
  if (c == 'U' && w == 'D') { glColor3f(102.0/255.0,102.0/255.0,102.0/255.0); }
  if (c == 'U' && w == 'L') { glColor3f(204.0/255.0,204.0/255.0,204.0/255.0); }
}

bool SNoverSR::read(istream &in)
{
  in >> colorType;
  int N;
  in >> N;
  V.resize(N);
  for(int i = 0; i < N; i++)
    in >> V[i];
  return in;
}
  
void SNoverSR::glRend(const CADColors &C)
{  
  // Note: it appears tht GL_LINE_STRIP has a limit of
  // 128 or so points that can appear.
  C.glSetColor(colorType,'D');
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < V.size(); i++)
    glVertex2(V[i]);
  glEnd();
}

bool SRoverSR::read(istream &in)
{
  in >> colorType;
  int N;
  in >> N;
  V.resize(N);
  for(int i = 0; i < N; i++)
    in >> V[i];

  // Check that the x coordinates are a palindrome! & correct if needed
  bool pal = true;
  for(int i = 0, j = N-1; i < j; ++i,--j)
    pal = pal && (V[i].x == V[j].x);
  if (!pal) {
    if (V[0].x == V[N-1].x && V[1].x == V[2].x)
    {
      vector<Point> W(2*(N-2));
      double Y = V[0].y;
      for(int i = 2, j = W.size()-1; i < N; ++i, --j) {
	W[i-2] = V[i];
	W[j].x = V[i].x;
	W[j].y = Y; }
      swap(W,V);
    }
    else if (V[0].x == V[N-1].x && V[N-2].x == V[N-3].x)
    {
      vector<Point> W(2*(N-2));
      double Y = V[N-1].y;
      for(int i = 0, j = W.size()-1; i < N-2; ++i, --j) {
	W[i] = V[i];
	W[j].x = V[i].x;
	W[j].y = Y; }
      swap(W,V);
    }
    else 
    {
      cerr << "Sector over sector in unknown format!" << endl;
      for(int i = 0; i < V.size(); i++)
	cerr << V[i] << endl;
      exit(1);
    }
  }

  return in;
}
  
void SRoverSR::glRend(const CADColors &C)
{  
  glBegin(GL_QUAD_STRIP);
  C.glSetColor(colorType,'L');
  for(int i = 0, j = V.size() - 1; i < j; i++, j--) {
    glVertex2(V[i]);
    glVertex2(V[j]); }
  if (V.size() % 2) { int i = V.size()/2; glVertex2(V[i]); glVertex2(V[i]); }
  glEnd();
}

bool SRoverSN::read(istream &in)
{
  in >> colorType >> a >> b.y;
  b.x = a.x;
  return in;
}

void SRoverSN::glRend(const CADColors &C)
{  
  glBegin(GL_LINE_STRIP);
  C.glSetColor(colorType,'D');
  glVertex2(a);
  glVertex2(b);
  glEnd();
}

bool SNoverSN::read(istream &in)
{
  return in >> colorType >> a;
}
  
void SNoverSN::glRend(const CADColors &C)
{  
  GLUquadricObj* p = gluNewQuadric();
  C.glSetColor(colorType,'D');
  glPushMatrix();
  glTranslated(a.x,a.y,0);
  gluDisk(p,4,5,20,1);
  glPopMatrix();
}

bool SN::read(istream &in)
{
  return in >> colorType >> x;
}
  
void SN::glRend(const CADColors &C)
{  
  glBegin(GL_LINE_STRIP);
  C.glSetColor(colorType,'D');
  glVertex2d(x,0);
  glVertex2d(x,d2);
  glEnd();
}

bool SR::read(istream &in)
{
  return in >> colorType >> x1 >> x2;
}
  
void SR::glRend(const CADColors &C)
{  
  glBegin(GL_QUAD_STRIP);
  C.glSetColor(colorType,'L');
  glVertex2d(x1,0);
  glVertex2d(x1,d2);
  glVertex2d(x2,0);
  glVertex2d(x2,d2);
  glEnd();
}
