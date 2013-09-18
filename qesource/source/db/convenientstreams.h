/***************************************************************
 * This file defines two very convenient stream classes:
 *
 * cacIstream  - Comments and continuations istream,
 *               i.e. # & \\n mean what you think
 *
 * slwcistream - Single-line buffered, respecting #'s for 
 *               comments and \\n for continuations
 * Chris Brown, 11 April, 2007
 ***************************************************************/
#ifndef _CONVENIENT_STREAMS_
#define _CONVENIENT_STREAMS_
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
using namespace std;


/***************************************************************
 * slwcistream - Single-line buffered, respecting #'s for 
 * comments and \\n for continuations
 ***************************************************************/
class slwcistream : public istringstream
{
public:
  enum option {none = 0, skipleadingws = 1};
  slwcistream(istream& in, option opt = none)
  {
    string s = "";
    char c = in.get(); 
    if (opt == skipleadingws) 
      while(c != EOF && (isspace(c) || c == '\\' && isspace(in.peek()))) c = in.get();
    // States  : 0 = normal, 1 = in comment, 2 = just read a backslash
    int state = 0;
    do {
      if (c == EOF) break;
      if (state == 2 && c == '\n') { state = 0; continue; }
      if (c == '\n') break;
      if (state == 1 && c == '\\' && in.peek() == '\n') { in.get(); state = 0; continue; }
      if (state == 1) continue;
      if (state == 0 && c == '#') { state = 1; continue; }
      if (state == 0 && c == '\\') { state = 2; continue; }
      s += c;
      state = 0;
    }while(c = in.get());
    str(s);
  }
};


/***************************************************************
 * cacIstream - Comments and continuations istream, 
 * i.e. # and \\n mean what you think
 ***************************************************************/


class cacInBuff : public streambuf
{  
protected:
  static const int buffSize = 10;
  static const int extra = 4;
  char buff[buffSize];
  istream *trueIn;
public:
  cacInBuff(istream &_in) { trueIn = &_in; char *tmp = buff+extra; setg(tmp,tmp,tmp); }
  inline virtual int_type underflow();
};

class cacIstream : public istream
{
protected:
  cacInBuff buff;
public:
  cacIstream(istream &_in) : buff(_in), istream(&buff) { }
};

/***************************************************************
 * Implementation of realineInBuff member functions
 ***************************************************************/
cacInBuff::int_type cacInBuff::underflow()
{
  if (gptr() >= egptr())
  {
    int leftover = min((long int)extra, (long int)(gptr() - eback()));
    memmove(buff + (extra-leftover), gptr() - leftover, leftover);

    char *s = buff + extra;     // the string I'm reading in
    int ls = 0;                 // the actual size of s

    // States  : 0 = normal, 1 = in comment, 2 = just read a backslash
    istream & in = *trueIn;
    int state = 0;
    char c;
    while(ls < buffSize - extra && (c = in.get()))
    {
      if (c == EOF) break;
      else if (state == 2 && c == '\n') { state = 0; continue; }
      else if (c == '\n') ;
      else if (state == 1 && c == '\\' && in.peek() == '\n') { in.get(); state = 0; continue; }
      else if (state == 1) continue;
      else if (state == 0 && c == '#') { state = 1; continue; }
      else if (state == 0 && c == '\\') { state = 2; continue; }
      s[ls++] = c;
      state = 0;
    }
    if (ls == 0) return EOF;
    setg(buff + (extra-leftover), buff + extra, buff + extra + ls);
  }
  return *gptr();
}
#endif
