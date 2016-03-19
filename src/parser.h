/*===========================================================================
  Title: Parser.h
  Author: Michael Menne
  Description: class to parse strings and buffers
  ===========================================================================*/

#ifndef PARSER_H
#define PARSER_H

#define MAXTOKEN            1024

#include <stdio.h>
#include <string.h>

typedef unsigned char  BYTE;
// #define NULL 0

/*---------------------------------------------------------------------------
  Class CParser:
  ---------------------------------------------------------------------------*/

class CParser
{
public:
    CParser();
    virtual ~CParser();
    bool StartParseFile(const char *szFile);
    void StartParseBuffer(const BYTE *buffer, const int size);
    void StartParseString(const char *string);

    bool  NextToken(bool crossline);
    /*char* Token() {return token;};
      int   GetScriptLine() {return scriptline;};*/

    char token[MAXTOKEN];               // buffer for tokens
    int scriptline;

protected:
    BYTE  *buffer;
    const BYTE *buf_pos;
    const BYTE *buf_end;


};

#endif
