/*****************************************************************
 *****************************************************************
 *****************************************************************
 ***
 *** class Point  --  This file contains a simple implementation
 *** of a class for points, along with arithmatic on points,
 *** a certain kind of i/o.
 ****************************************************************
 ****************************************************************
 ****************************************************************/
#ifndef _Point_
#define _Point_

#include <fstream>
using namespace std;

/**********************************************************
 ** prototypes: i.e. all functions and classes defined here
 **********************************************************/
class Point;
inline Point operator-(const Point&,const Point&);
inline Point operator+(const Point&,const Point&);
inline Point operator/(const Point&,double);
inline ostream& operator<<(ostream &,const Point &);
inline istream& operator>>(istream &,Point &);

/*******************************************
 ** class Point
 *******************************************/
class Point
{
public:
  double x,y;
  Point(double a = 0, double b = 0) { x = a; y = b; }
  Point(const Point &P) { x = P.x; y = P.y; }
};

/*******************************************
 ** function def's
 *******************************************/
inline Point operator-(const Point &p, const Point &q)
{
  return Point(p.x - q.x, p.y - q.y);
}

inline Point operator+(const Point &p, const Point &q)
{
  return Point(p.x + q.x, p.y + q.y);
}

inline Point operator/(const Point &p, double k)
{
  return Point(p.x / k, p.y / k);
}

inline Point operator*(double k,const Point &p)
{
  return Point(k*p.x, k*p.y);
}

inline ostream& operator<<(ostream &OUT, const Point &p)
{
  return OUT << p.x << ' ' << p.y;
}

inline istream& operator>>(istream &IN, Point &p)
{
  return IN >> p.x >> p.y;
}

#endif
