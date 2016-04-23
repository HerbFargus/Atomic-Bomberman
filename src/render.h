/*===========================================================================
  Title: Render.h
  Author: Michael Menne
  Version: 1.2
  Description: Init SDL OpenGL, loads & draws graphics and text
  Seit 1.2 wird die SDL_image library zum laden der Bilder verwendet
  ===========================================================================*/

#ifndef _TILEMNG_H_
#define _TILEMNG_H_

/*---------------------------------------------------------------------------
  Headers:
  ---------------------------------------------------------------------------*/

#ifdef WIN32
#include <windows.h>
#endif
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <string>
#include <vector>
using namespace std;

/*---------------------------------------------------------------------------
  Definitions
  ---------------------------------------------------------------------------*/

typedef unsigned int   UINT;
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;

enum IMAGE_TYPE 
{
    IT_BMP,
    IT_TGA,
    IT_JPG,
    IT_PNG,
    IT_PCX,
    IT_UNKNOWN
};

enum
{
    TF_NONE = 0,
    TF_FILTER_LINEAR  = (1<<0),
    TF_FILTER_NEAREST = (1<<1),
    TF_ALPHATEST      = (1<<2), 
    TF_ALPHABLEND     = (1<<3)
};

/*------------------------------------------------------------------------
  Public Types:
  ------------------------------------------------------------------------*/

struct TexInfo	// tex info
{
    UINT	 num;	// OpenGL number of this tile
    int		 width;
    int		 height;
    int      flags;
};

/*---------------------------------------------------------------------------
  Class TileMng:
  ---------------------------------------------------------------------------*/

class Render
{
public:
    Render();
    virtual ~Render();

    void SetOffset(int xOff, int yOff);
	
    void EndFrame();
    void BeginFrame();
	
    /**
     *	Initializes OpenGL
     */
    bool Init(int nWidth, int nHeight, bool bFullscreen);

    /**
     *	Shuts the renderer, freeing all unfreed textures
     */
    void Shut();

    /**
     *	Draws a tile within the given rectangle using the texture from the TexInfo
     */
    void DrawTile(int x, int y, int w, int h, TexInfo *tInfo);

    /**
     *	Fills a rectangle 'rcDest' witht he given color
     */
    void FillRect(SDL_Rect rcDest, float red, float green, float blue, float alpha = 1.0f);

    // gm: last parameter '...' removed
    /**
     *	Draws formartet Text at the x/y position using the passed color
     */
    void DrawText(int x, int y, float red, float green, float blue, string strText);
    
    /**
     *	Sets the size of the text
     *	Default: 16x16
     */
    void SetTextSizes(int nWidth, int nHeight)
	{
            m_nTextWidth  = nWidth; 
            m_nTextHeight = nHeight;
	}

    /**
     *	Loads a texture, registers it with OpenGL and returns a TexInfo
     *	Note: You must call DeleteTexture to free the memory used by the TexInfo
     */
    TexInfo* LoadTexture(string szTexture, int nFlags = TF_FILTER_LINEAR);

    /**
     *	Unregisters the Texture from OpenGL and frees all used memory used by the texture
     */
    void     DeleteTexture(TexInfo* pInfo);



/***** und hinzufügen in h: */

    // gm: last parameter '...' removed
    /**
     * (by dh) see DrawText above
     */
    void DrawText(SDL_Rect r, float red, float green, float blue, string 
                  strText);

    // gm: last parameter '...' removed
    /**
     * (by dh) returns the count of pixels the text uses in width
     */
    int  TextWidth(string strText);


protected:
	
    /**
     *	Structs (non public)
     */
    struct TexRef
    {
        string	 name;
        int		 iCount;		// TODO: count could be used to give priorities
        BYTE	 *mem;
        int		 bpp;
        TexInfo  *info;			// each TexRef has an unique TexInfo
    };

    typedef vector<TexRef*> TexVector;

    struct TgaHeader			// TGA file header (18 BYTE)
    {	
        BYTE id_length, colormap_type, image_type;
        BYTE colormap_index[2], colormap_length[2];
        BYTE colormap_size;
        BYTE x_origin[2], y_origin[2], width[2], height[2];
        BYTE pixel_size, attributes;
    };

    struct BmpHeader		// BMP file header (54 BYTE)
    {
        BYTE bfType[2];
        BYTE bfSize[4]; 
        BYTE bfReserved1[2]; 
        BYTE bfReserved2[2]; 
        BYTE bfOffBits[4]; 

        BYTE biSize[4]; 
        BYTE biWidth[4]; 
        BYTE biHeight[4]; 
        BYTE biPlanes[2]; 
        BYTE biBitCount[2]; 
        BYTE biCompression[4]; 
        BYTE biSizeImage[4]; 
        BYTE biXPelsPerMeter[4]; 
        BYTE biYPelsPerMeter[4]; 
        BYTE biClrUsed[4]; 
        BYTE biClrImportant[4];
    };

private:
    /**
     *	Functions
     */
    void SetState(TexInfo *tInfo);
    void LoadGLTexture(TexRef *pRef);
    void LoadDefaultTex(TexRef *pRef);
    bool RegisterTexture(TexRef *pRef);

    void RGB_Decode(SDL_Surface *image, TexRef *pRef);
    void BGR_Decode(SDL_Surface *image, TexRef *pRef);

    void DrawChar(int x, int y, char c);

    IMAGE_TYPE GetFileType(string name);
    int  NextPowerOfTwo(int n);
    void ScaleImage(GLenum format, int inwidth, int inheight, const BYTE *in,
                    int outwidth, int outheight, BYTE *out );

    /**
     *	Variables
     */
    TexVector m_vTexRefs;
    UINT      m_uiCurTexture;
    bool      m_bAlphaTest;
    bool      m_bAlphaBlend;

    static int m_nTextWidths[128];

    // Text stuff
    TexInfo*  m_tFont;
    int m_nTextWidth, m_nTextHeight;
};

#endif // _TILEMNG_H_
