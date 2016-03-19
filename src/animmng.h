/*===========================================================================
	Title: AnimMng.h
	Author: Michael Menne
	Description: Loads ANI files and builds linked lists from them

    Modified by Gregor Mitsch (see below)
===========================================================================*/

#ifndef _ANIMMNG_H_
#define _ANIMMNG_H_

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

/*---------------------------------------------------------------------------
	Headers:
---------------------------------------------------------------------------*/

#include "parser.h"
#include "render.h"
#include <vector>
#include <map>
using namespace std;

/*---------------------------------------------------------------------------
	Structs:
---------------------------------------------------------------------------*/

struct anim_frame
{
	TexInfo *tInfo;
	int   xOrigin, yOrigin;
	int   xOffset, yOffset;
	int   nWidth, nHeight;
	float fFrameTime;
	anim_frame *pNext;
};

enum EnumAnims
{
	ANI_STAND = 0,
	ANI_WALK,
	ANI_DYING,
	ANI_CORNER,
	ANI_TILE_SOLID,
	ANI_TILE_NONSOLID,
	ANI_BOMB,
	ANI_TRIGGER,
	ANI_FLAME,
	ANI_NUMBER_OF
};

enum EnumDir
{
	DIR_NORTH=0,
	DIR_WEST,
	DIR_SOUTH,
	DIR_EAST
};


/*---------------------------------------------------------------------------
	Class AnimMng:
---------------------------------------------------------------------------*/

class Animation
{
public:
	Animation();
	~Animation();

	/*
	 *	Start und Stop
	 *	Wenn die Animation nicht gestartet ist, wird sie nicht abgespielt (Update macht nix)
	 */
	void Start() {m_bActive = true;};
	void Stop()  {m_bActive = false;};
	
	/*
	 *	Advances the animation
	 *	Sollte vor jedem Aufruf von Draw() aufgerufen werden.
	 */
	void Update();

	/*
	 *	Zeichnet die Animation an der x/y position, optional kann man noch die Zeichengröße angeben
	 */
	void Draw(int x, int y, int width = -1, int height = -1);

	/*
	 *	Setzt die animation des Objektes
	 *	Die ID zeigt welche Art der Animation gebraucht wird, z.b. ANI_WALK_NORTH für die Lauf-Animation
	 *	Wenn mehrere Animationen der gleichen Art (z.b. Todesanimationen) zur verfügung stehen wird eine 
	 *	zufällig gewählte Animation der Art ausgewählt, ausser man gibt mit nWhich die exakte Animation an
	 *	z.b.: SetAnimation(ANI_DEATH, 4) wählt die todesanimation Nr. 5 (zero based)aus
     *                                                            fSpeed added by gm
	 */
	void SetAnimation(EnumAnims nAnimType, int nWhich = -1, float fSpeed = 1.0f);

	/*
	 *	Gibt true zurück wenn die Animation fertig ist (es kein nächstes Frame mehr gibt)
	 */
	bool IsFinished();

	/*
	 *	Gibt den Typ der aktuallen Animation zurück
	 */
	EnumAnims GetCurAnimType() {return m_nCurAnim;};

	/*
	 *	Setzt die Geschwindigkeit mit der die Animation abgespielt wird
	 *	1.0 ist dabei der default wert
     *
     * removed by gm
	 */
//	void SetSpeed(float fSpeed = 1.0f) {m_fSpeed = fSpeed;};

//    Animation& operator = (const Animation & rhs);
//    Animation (const Animation & rhs);

protected:
//    void copy (const Animation & rhs);

private:
	bool        m_bActive;
	float		m_fTimeElapsed;
	float		m_fSpeed;
	anim_frame *m_pFrame;

	EnumAnims  m_nCurAnim;

};

/*---------------------------------------------------------------------------
	Class AnimMng:
---------------------------------------------------------------------------*/

typedef vector <anim_frame*> AnimFrameVector;
typedef vector <AnimFrameVector> AnimVector;

class AnimMng  
{
public:
	AnimMng();
	virtual ~AnimMng();

	/*
	 *	Initialized the Anim Manager (should only be called once)
	 *	-> Loads all animation listed in the animlist.res
	 */
	void Init();

	/*
	 *	Shuts the Anim Manager (Don't forget to call this)
	 *	-> Deletes all loded animations (+frees memory)
	 */
	void Shut();

	AnimVector m_aAnimations;
	static string m_strAnims[ANI_NUMBER_OF];

protected:
	anim_frame* LoadAnimation(string strAnim);
	bool ParserFrame(CParser *pParser, const char *dir, anim_frame *pFrame);

	bool m_bInitialized;
	
};

#endif // _ANIMMNG_H_
