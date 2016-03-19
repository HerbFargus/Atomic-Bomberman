// v0.5  by gm (created)
// v0.51 by gm (cosmetic changes)

#ifndef TEXTMESSAGES_H
#define TEXTMESSAGES_H

#include "nameddatafile.h"

class TextMessages
{
public:
    /**
     * loads the key config from file
     */
    TextMessages ();

    virtual ~TextMessages ();

    /**
     * returns the message with the ID which
     */
    const string get(string which) const;

private:
    NamedDataFile m_ndf;
};

#endif // TEXTMESSAGES_H
