/***************************************************************
 * readlineistream.h Christopher W. Brown (Feb. 2007)
 * 
 * This file defines the class readlineIstream, which is a
 * a C++ istream object that reads from standard input (cin),
 * but uses the readline library, so the user sees emacs-style
 * editing, history and, eventually, tab-completion.
 ***************************************************************/
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
using namespace std;

class readlineInBuff : public streambuf
{
protected:
  char *buff;
  int buffSize;  
  int fileDes;
public:
  inline readlineInBuff();
  inline readlineInBuff(int fd);
  inline virtual int_type underflow();
};

class readlineIstream : public istream
{
protected:
  readlineInBuff buff;
public:
  inline readlineIstream() : buff(), istream(&buff) { }
  inline readlineIstream(int fd) : buff(fd), istream(&buff) { }
};

/***************************************************************
 * Implementation of realineInBuff member functions
 ***************************************************************/
const int extra = 4;
readlineInBuff::readlineInBuff()
{
  buff = (char*)malloc(extra);
  buffSize = extra;
  setg(buff+extra,buff+extra,buff+extra);
}
readlineInBuff::readlineInBuff(int fd)
{
  buff = (char*)malloc(extra);
  buffSize = extra;
  setg(buff+extra,buff+extra,buff+extra);
  fileDes = fd;
  FILE* fp = fdopen(fileDes,"r");
  rl_instream = fp;
}
readlineInBuff::int_type readlineInBuff::underflow()
{
  if (gptr() >= egptr())
  {
    char *s = readline("");    //would like some way to check if \n was read in or not!
    if (s == NULL) return EOF;
    add_history(s);
    int ls = strlen(s);
    
    int leftover =  min((long int)extra,(long int)(gptr()-eback()));
    char *newbuff = (char*)malloc(extra + ls + 1);
    memcpy(newbuff+(extra-leftover),gptr() - leftover, leftover);
    memcpy(newbuff+extra,s,ls);
    newbuff[extra + ls] = '\n';
    free(s);
    free(buff);
    buffSize = extra + ls + 1;
    buff = newbuff;
    setg(buff + (extra - leftover), buff + extra, buff + (extra + ls) + 1);
  }
  return *gptr();
}
