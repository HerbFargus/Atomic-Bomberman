/*===========================================================================
	Title: AnimMng.h
	Author: Michael Menne
	Version: 0.1
	Description: Loads ANI files and builds linked lists from them
===========================================================================*/

#include "animmng.h"
#include "globals.h"
#include "render.h"
#include "timer.h"
#include "listreader.h"
#include <time.h>
#include <iostream>
using std::iostream;

/*---------------------------------------------------------------------------
	Static:
---------------------------------------------------------------------------*/

string AnimMng::m_strAnims[ANI_NUMBER_OF] = 
{
	"ANI_STAND",
	"ANI_WALK", 
	"ANI_DYING",
	"ANI_CORNER",
	"ANI_TILE_SOLID",
	"ANI_TILE_NONSOLID",
	"ANI_BOMB",
	"ANI_TRIGGER",
	"ANI_FLAME"
};

/*---------------------------------------------------------------------------
	Construction/Destruction:
---------------------------------------------------------------------------*/

AnimMng::AnimMng()
{
    // first randomize
    srand(time(NULL));
	m_bInitialized = false;
}

AnimMng::~AnimMng()
{
	if(m_bInitialized)
	{
		cerr << "You forgot to call AnimMng::Shut(), I will do this for you now ;)" << endl;
		Shut();
	}
}

/*---------------------------------------------------------------------------
	Animation Loading / Deleting code:
---------------------------------------------------------------------------*/

void AnimMng::Init()
{
	if(m_bInitialized)
	{
		cerr << "AnimMng is already initialized, please remove your call to Init()! Thanks." << endl;
		return;
	}
	m_bInitialized = true;

	string sp = "";
    string sl = "data/config/animlist.res";
	ListReader lr;

	// Set the size of the AnimVector
	m_aAnimations.resize(ANI_NUMBER_OF);

	// Load all animations
	for(int i=0; i<ANI_NUMBER_OF; i++)
	{
//        cout << i << ": ";
		StringVector strVector = lr.get(sp, sl, m_strAnims[i]);
		for(StringVector::iterator str = strVector.begin(); str != strVector.end(); str++)
		{
			anim_frame *pFrame = LoadAnimation(*str);

    		if (pFrame)
            {
//                cout << m_aAnimations[i].size();
//                cout << " : " << pFrame;
				m_aAnimations[i].push_back(pFrame);
            }
            else
            {
                cout << "AnimMng::Init(): ERROR while loading " << *str << ". Following anims will not be set correct!." << endl;
            }
//            cout << endl;
		}
//        cout << endl;
	}
}

anim_frame* AnimMng::LoadAnimation(string strAnim)
{
	CParser parser;
	if(!parser.StartParseFile(strAnim.c_str()))
    {
        cout << "AnimMng::LoadAnimation(string): Error 1" << endl;
		return NULL;
    }

	string strDir = strAnim;
	string::size_type pos = strDir.find_last_of("/");
	if(pos != string::npos)
		strDir.erase(pos+1);
	else
		strDir.erase();

	anim_frame standard;
	memset(&standard, 0, sizeof(anim_frame));

	anim_frame *pAnimation = NULL;
	anim_frame **pFrame = &pAnimation;

	while(parser.NextToken(true))
	{
		if(!strcmp(parser.token, "standard"))
		{
			ParserFrame(&parser, "", &standard);
		}
		else if(!strcmp(parser.token, "frame"))
		{
			*pFrame = new anim_frame();
			memcpy(*pFrame, &standard, sizeof(anim_frame));
			if(!ParserFrame(&parser, strDir.c_str(), *pFrame))
            {
                cout << "AnimMng::LoadAnimation(string): Error 2" << endl;
				return NULL;	// FIXME: Do something here
            }

			// No more animation if the current one has a fFrameTime of 0
			if((*pFrame)->fFrameTime == 0.0f)
			{
				return pAnimation;
			}

			pFrame = &(*pFrame)->pNext;
		}
	}

	// Link the last frame to the first (so that it will loop)
	*pFrame = pAnimation;
	return pAnimation;
}

bool AnimMng::ParserFrame(CParser *pParser, const char *dir, anim_frame *pFrame)
{
	if(pParser->NextToken(true))
	{
		if(strcmp(pParser->token, "{")) 
		{
			// '{' expected;
			return false;
		}
	}

	while(pParser->NextToken(true))
	{
		if(!strcmp(pParser->token, "}"))			// "}" token
			return true;
		else if(!strcmp(pParser->token, "map"))	// "map" token
		{
			if(!pParser->NextToken(false))
				continue;	// Token expected after 'map'
			
			char szFile[1024];
			strcpy(szFile, dir); strcat(szFile, pParser->token);

            // DEBUG:
//            cout << szFile << endl;

			pFrame->tInfo = Globals::render().LoadTexture(szFile);
		}
		else if(!strcmp(pParser->token, "origin"))	// "origin" token
		{
			if(!pParser->NextToken(false))
				continue;	// Token expected after 'origin'

			pFrame->xOrigin = atoi(pParser->token);

			if(!pParser->NextToken(false))
				continue;	// Token expected after 'origin'

			pFrame->yOrigin = atoi(pParser->token);
		}
		else if(!strcmp(pParser->token, "offset"))	// "offset" token
		{
			if(!pParser->NextToken(false))
				continue;	// Token expected after 'offset'

			pFrame->xOffset = atoi(pParser->token);

			if(!pParser->NextToken(false))
				continue;	// Token expected after 'offset'

			pFrame->yOffset = atoi(pParser->token);
		}
		else if(!strcmp(pParser->token, "size"))	// size token
		{
			if(!pParser->NextToken(false))
				continue;	// Token expected after 'offset'

			pFrame->nWidth = atoi(pParser->token);

			if(!pParser->NextToken(false))
				continue;	// Token expected after 'offset'

			pFrame->nHeight = atoi(pParser->token);
		}
		else if(!strcmp(pParser->token, "time"))	// "time" token
		{
			if(!pParser->NextToken(false))
				continue;	// Token expected after 'time'

			pFrame->fFrameTime = atof(pParser->token);
		}
		// else //Unknown token
	}
	return false;
}

void AnimMng::Shut()
{
	if(!m_bInitialized)
	{
		cerr << "If you want to shut down the AnimMng, you first have to call AnimMng::Init()" << endl;
		return;
	}
	m_bInitialized = false;

	anim_frame *pNext, *pFrame;
	
	// Alle Einträge in der Map durchgeben
	for(int i=0; i<ANI_NUMBER_OF; i++)
	{
		// Alle Einträge in dem Vector durchgeben
		AnimFrameVector vec = m_aAnimations[(EnumAnims)i];
		for(AnimFrameVector::iterator anim = vec.begin(); anim != vec.end(); anim++)
		{
			// Die ganze linked list abgehen
			for(pFrame = *anim; pFrame; pFrame = pNext)
			{
				pNext = pFrame->pNext;

				// Jedes frame löschen
				Globals::render().DeleteTexture(pFrame->tInfo);
				delete pFrame;
				pFrame = NULL;

				// Wenn wir wieder beim ersten angelangt sind, raus aus der Schleife
				if(pNext == *anim)
					break;
			}
			*anim = NULL;
		}		
	}
}

/*---------------------------------------------------------------------------
	Animation class code:	
---------------------------------------------------------------------------*/

Animation::Animation()
{
	m_bActive      = false;
	m_fTimeElapsed = 0.0f;
	m_fSpeed	   = 1.0f;
	m_pFrame	   = NULL;	
	m_nCurAnim	   = (EnumAnims)-1;	// Friss oder stirb
}

Animation::~Animation()
{
	// Nothing to do!
}

void Animation::SetAnimation(EnumAnims nAnimType, int nWhich /*= -1*/, float fSpeed /*= 1.0f*/)
{
	Globals g;
	int nCount = g.anim().m_aAnimations[nAnimType].size();
	if(nCount == 0)
	{
		cerr << "Animation type: '" << g.anim().m_strAnims[nAnimType] << "' is not available / was not loaded." << endl;
		return;
	}

	if(nWhich == -1)
		nWhich = rand() % nCount;
	else
	{
		if(nWhich > (nCount-1))
			nWhich = nCount-1;
	}

	m_pFrame   = g.anim().m_aAnimations[nAnimType][nWhich];
	m_nCurAnim = nAnimType;	// Remeber animation type

    m_fSpeed = fSpeed;
}

void Animation::Update()
{
	if(!m_pFrame || !m_bActive)
		return;
	
	m_fTimeElapsed += Globals::timer().frame_time() * m_fSpeed;
	while(m_pFrame->fFrameTime > 0 && m_fTimeElapsed > m_pFrame->fFrameTime)
	{
		m_fTimeElapsed -= m_pFrame->fFrameTime;
		m_pFrame = m_pFrame->pNext;
	}
};

void Animation::Draw(int x, int y, int width /*= -1*/, int height /*= -1*/)
{
	if(!m_pFrame)
		return;

//  commented out by gm:
// 	if(width == -1)
// 		width = m_pFrame->tInfo->width;
// 	if(height == -1)
// 		height = m_pFrame->tInfo->height;

// 	width  = m_pFrame->nWidth;
// 	height = m_pFrame->nHeight;


//  new code by gm:
	if(width == -1)
		width = m_pFrame->nWidth;

	if(height == -1)
		height = m_pFrame->nHeight;

	x = x - m_pFrame->xOrigin * width  / m_pFrame->tInfo->width  + m_pFrame->xOffset;
	y = y - m_pFrame->yOrigin * height / m_pFrame->tInfo->height + m_pFrame->yOffset;
	Globals::render().DrawTile(x, y, width, height, m_pFrame->tInfo);
};

bool Animation::IsFinished()
{
	return (m_pFrame && m_pFrame->fFrameTime <= 0);
}

//Animation& Animation::operator = (const Animation & rhs)
//{
//    copy(rhs);
//    return *this;
//}
//
//Animation::Animation (const Animation & rhs)
//{
//    copy(rhs);
//}
//
//void Animation::copy (const Animation & rhs)
//{
//	m_bActive = rhs.m_bActive;
//	m_fTimeElapsed = rhs.m_fTimeElapsed;
//	m_fSpeed = rhs.m_fSpeed;
//	m_pFrame = rhs.m_pFrame;
//	m_nCurAnim = rhs.m_nCurAnim;
//}
