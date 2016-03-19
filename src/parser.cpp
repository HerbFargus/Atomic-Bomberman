/*===========================================================================
  Title: Parser.cpp
  Author: Michael Menne
  Description: class to parse strings, buffers and files
  ===========================================================================*/

#include "parser.h"

/*---------------------------------------------------------------------------
  Constructor / Destructor:
  ---------------------------------------------------------------------------*/

CParser::CParser()
{
    buffer     = NULL;
    buf_pos    = NULL;
    buf_end    = NULL;
    token[0]   = NULL;
    scriptline = 0;
}

CParser::~CParser()
{
    if(buffer)
    {
        delete [] buffer;
        buffer = NULL;
    }
}

/*---------------------------------------------------------------------------
  Methods:
  ---------------------------------------------------------------------------*/

bool CParser::StartParseFile(const char *szFile)
{
    FILE *pFile = NULL;
    pFile = fopen(szFile, "r");
    if(!pFile)
        return false;

    if(buffer)
    {
        delete [] buffer;
        buffer = NULL;
    }

    fseek(pFile, 0L, SEEK_END);
    int len = ftell(pFile);
    rewind(pFile);

    buffer = new BYTE[len];
    fread(buffer, len, 1, pFile);
    fclose(pFile);

    StartParseBuffer(buffer, len);
    return true;
}

void CParser::StartParseBuffer(const BYTE *buff, const int size)
{
    buf_pos  = buff;
    buf_end  = buff + size;
    scriptline=0;
}

/*
 *  Parses a null terminated string
 */
void CParser::StartParseString(const char *string)
{
    buf_pos  = (BYTE *)string;
    buf_end  = (BYTE *)string + strlen(string);
    scriptline = 0;
}

/*
 * If crossline is false, GetToken returns false when a line break is found
 * GetToken(true) returns 0 only if end of file
 * GetToken(false) returns 0 if line break or end of file
 */
bool CParser::NextToken(bool crossline)
{
    char    *token_p;

    if(!buf_pos) return 0;
    if(buf_pos == buf_end) return 0;

    *token = 0; // init to zero


// skip space
 skipspace:
    while (*buf_pos <= 32 || *buf_pos == '\n' || *buf_pos == ';')
    {
        if(*buf_pos == '\n')
            scriptline++;
        if (buf_pos >= buf_end)
        {
            if (!crossline)
            {
                //console.insert("Line %i is incomplete",scriptline);
            }
            return 0;
        }

        if (!crossline)
        {
            if(*buf_pos=='\n' || *buf_pos==';')
            {
                return 0;
            }
        }
        buf_pos++;
    }

    if (buf_pos >= buf_end)
        return 0;

    // # // comments
    if (*buf_pos == '#' || ( buf_pos[0] == '/' && buf_pos[1] == '/') )
    {
        while (*buf_pos++ != '\n')
        {
            if (buf_pos >= buf_end) return 0;
        }
        scriptline++;
        if(!crossline) return 0;
        goto skipspace;
    }

    // /* */ comments
    if (buf_pos[0] == '/' && buf_pos[1] == '*')
    {
        buf_pos+=2;
        while (!(buf_pos[0] == '*' && buf_pos[1] == '/'))
        {
            buf_pos++;
            if (buf_pos >= buf_end)
            {
                //console->Print("*** Error: Premature end of file, '/*' without '*/'\n");
                return 0;
            }
            if(*buf_pos == '\n') scriptline++;
        }
        buf_pos += 2;
        goto skipspace;
    }


    /*
     * copy token
     */
    token_p = token;

    if (*buf_pos == '"')
    {       // quoted token
        buf_pos++;
        while (*buf_pos != '"')
        {
            *token_p++ = *buf_pos++;
            if (buf_pos == buf_end) break;
            if (token_p == &token[MAXTOKEN])
            {
                //console.insert("*** Error, Token too large on line %i\n",scriptline);
            }
        }
        buf_pos++;
    }
    else
    {   // regular token
        if(*buf_pos == '{' || *buf_pos == '}')
        {
            *token_p++=*buf_pos++;
            *token_p = 0;
            return 1;
        }
        while ( *buf_pos > 32 && *buf_pos != '\n' && *buf_pos != ';' && *buf_pos !='{' && *buf_pos !='}')
        {
            *token_p++ = *buf_pos++;
            if (buf_pos == buf_end) break;
            if (token_p == &token[MAXTOKEN])
            {
                //console.insert("*** Error, Token too large on line %i\n",scriptline);
            }
        }
    }

    *token_p = 0;

    return 1;
}
