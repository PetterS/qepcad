/***************************************************************
 * This file defines a class UnnamedPipe whose sole purpose
 * in life is to create ... an unnamed pipe, of course.  It is
 * Unix specific, relying on the "pipe" system call.
 *
 * The key member functions are in() and out(), which are
 * somewhat confusingly named!  in() returns the istream
 * associated with the pipe and out() returns the ostream
 * associated with the pipe.  That means you use out() to write 
 * things to the pipe and in() to read things from the pipe.
 * 
 ***************************************************************/
#ifndef _UNNAMEDPIPE_
#define _UNNAMEDPIPE_
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <streambuf>
using namespace std;

/**************************************************
See "The C++ Standard Library", by Nicolai M. Josuttis
Chapter 13 for info on how fd(in|out)(buff|stream)
works.  This code is based on that stuff.
**************************************************/

class fdoutbuff : public streambuf
{
public:
  int fileDes;
  fdoutbuff(int fd) { fileDes = fd; }
  int_type overflow(int c) { 
    char cp = c;
    return (c == EOF || write(fileDes,&cp,1) != 1) ? EOF : c; 
  }
  streamsize xsputn (const char* s, streamsize n) { return write(fileDes,s,n); }
};

class fdostream : public ostream
{
public:
  fdoutbuff buff;
  fdostream(int fd) : buff(fd), ostream(&buff) { }
};

static const int unpbuffSize = 10;
static const int unpextra = 4;

class fdinbuff : public streambuf
{

public:
  char buff[unpbuffSize];
  int fileDes;
  fdinbuff(int fd) { fileDes = fd; char *tmp = buff+unpextra; setg(tmp,tmp,tmp); }
  int_type underflow()
  {
    if (gptr() >= egptr())
    {
      int leftover = min((long int)unpextra, (long int)(gptr() - eback())), readSize;
      memmove(buff + (unpextra-leftover), gptr() - leftover, leftover);
      if ((readSize=read(fileDes, buff + unpextra, unpbuffSize - unpextra)) <= 0) return EOF;
      setg(buff + (unpextra-leftover), buff + unpextra, buff + (4+readSize));
    }
    return *gptr();
  }
};

class fdistream : public istream
{
public:
  fdinbuff buff;
  fdistream(int fd) : buff(fd), istream(&buff) { }
};

/***************************************************************
 * UnnamedPipe
 ***************************************************************/
class UnnamedPipe 
{
public:
  fdostream *_out;
  fdistream *_in;
  int fd[2];
  bool openmask[2];
  UnnamedPipe()
  {    
    if (pipe(fd) == -1) { perror("Failed to create pipe!"); exit(1); }
    openmask[0] = openmask[1] = true;
    _in  = 0;
    _out = 0;
  }
  ~UnnamedPipe() { 
    if (_in) { 
      delete _in; 
    }
    if (openmask[0]) { 
      close(fd[0]); 
    } 
    if (_out) { 
      delete _out; 
    } 
    if (openmask[1]) { 
      close(fd[1]); 
    } 
  }

  fdistream& in()  { if (!_in) _in = new fdistream(fd[0]); return *_in; }
  fdostream& out() { if (!_out) _out = new fdostream(fd[1]); return *_out; }
  int fdin() { return fd[0]; }
  int fdout() { return fd[1]; }
  int setStdinToPipe() { return dup2(fdin(),fileno(stdin)); }
  int setStdoutToPipe() { return dup2(fdout(),fileno(stdout)); }
  void closeIn() { 
    if (_in) { delete _in; _in = 0; }
    if (openmask[0]) { close(fd[0]); openmask[0] = false; } 
  }
  void closeOut() { 
    const char ts[2] = {EOF,'\n'};
    if (_out) { delete _out; _out = 0; }
    if (openmask[1]) { 
      //      write(fd[1],ts,2); 
      close(fd[1]);  
      openmask[1] = false; }
  }
};

#endif
