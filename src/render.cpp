/*===========================================================================
	Title: Render.cpp
	Author: Michael Menne
	Version: 1.2
	Description: Init SDL OpenGL, loads & draws graphics and text
				 Seit 1.2 wird die SDL_image library zum laden der Bilder verwendet
===========================================================================*/

#include "render.h"
#include <iostream>
#include <stdarg.h>
#include <SDL/SDL_image.h>

/*------------------------------------------------------------------------
	Init / State / Drawing code:
------------------------------------------------------------------------*/

int Render::m_nTextWidths[128] =
{
//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 1
    4, 2, 5, 6, 7, 8, 7, 2, 3, 3, 4, 5, 4, 3, 2, 7, // 2
    6, 4, 6, 6, 6, 6, 6, 6, 6, 6, 4, 0, 5, 0, 5, 7, // 3
    6, 7, 6, 6, 6, 5, 5, 6, 7, 2, 5, 7, 5, 7, 6, 7, // 4
    5, 7, 6, 6, 6, 6, 7, 7, 6, 7, 6, 3, 7, 3, 4, 7, // 5
    4, 5, 5, 5, 5, 5, 4, 5, 5, 2, 3, 5, 3, 7, 5, 6, // 6
    5, 5, 3, 5, 4, 5, 5, 7, 5, 5, 5, 4, 2, 4, 0, 0  // 7
};

Render::Render()
{
}

Render::~Render()
{
	for(TexVector::iterator i = m_vTexRefs.begin(); i != m_vTexRefs.end(); ++i)
    {
        if((*i)->info->num != (~0))
            glDeleteTextures(1, &((*i)->info->num));

        delete (*i)->info; (*i)->info = NULL;
        delete *i;
    }
}

bool Render::Init(int nWidth, int nHeight, bool bFullscreen)
{
	int flags = SDL_OPENGL;
	if(bFullscreen)
		flags |= SDL_FULLSCREEN;

	// Init OpenGL
	if (SDL_SetVideoMode(nWidth, nHeight, 0, flags) == NULL)
        return false;
	
	// Set OpenGL preferences
    glViewport(0, 0, nWidth, nHeight);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	glOrtho(0, nWidth, nHeight, 0, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		// black Background
	glEnable(GL_TEXTURE_2D);					// Enable Texture Mapping

	// Alpha testing
	glDisable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0f);

	// Alpha blending
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_uiCurTexture = 0;
	m_bAlphaBlend  = false;
	m_bAlphaTest   = false;

	// Load Font Texture:
	m_tFont = LoadTexture("data/images/font.bmp", TF_FILTER_NEAREST);
	m_nTextWidth  = 16;
	m_nTextHeight = 32;

	return true;
}

void Render::Shut()
{
	// Unload front
	DeleteTexture(m_tFont); m_tFont = NULL;
}

void Render::SetState(TexInfo *tInfo)
{
	if(tInfo)
	{
		// Texture binding
		if(m_uiCurTexture != tInfo->num)
		{
			glBindTexture(GL_TEXTURE_2D, tInfo->num);
			m_uiCurTexture = tInfo->num;
		}

		// Alpha Testing
		if(m_bAlphaTest != ((tInfo->flags & TF_ALPHATEST)!=0))
		{
			if(tInfo->flags & TF_ALPHATEST)
			{
				glEnable(GL_ALPHA_TEST);
				m_bAlphaTest = true;
			}
			else
			{
				glDisable(GL_ALPHA_TEST);
				m_bAlphaTest = false;
			}
		}

		// Alpha Blending
		if(m_bAlphaBlend != ((tInfo->flags & TF_ALPHABLEND)!=0))
		{
			if(tInfo->flags & TF_ALPHABLEND)
			{
				glEnable(GL_BLEND);
				m_bAlphaBlend = true;
			}
			else
			{
				glDisable(GL_BLEND);
				m_bAlphaBlend = false;
			}
		}
	}
	else
	{
		// Unbind texture, diable AlphaBlend and AlphaTest
		glBindTexture(GL_TEXTURE_2D, 0);
		m_uiCurTexture = 0;
		glDisable(GL_ALPHA_TEST);
		m_bAlphaTest = false;
		glDisable(GL_BLEND);
		m_bAlphaBlend = false;
	}
}

void Render::SetOffset(int xOff, int yOff)
{
	glLoadIdentity();
	glTranslatef((float)xOff, (float)yOff, 0.0f);
}

void Render::BeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::DrawTile(int x, int y, int w, int h, TexInfo *tInfo)
{
	SetState(tInfo);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(x,   y);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(x,   y+h);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(x+w, y+h);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(x+w, y);
	glEnd();
}

void Render::FillRect(SDL_Rect rcDest, float red, float green, float blue, float alpha /*= 1.0f*/)
{
	SetState(NULL);
	glEnable(GL_BLEND);	 // HACK HACK!
	glColor4f(red, green, blue, alpha);
	glRectf((float)rcDest.x, (float)rcDest.y, (float)rcDest.x + rcDest.w, (float)rcDest.y + rcDest.h);

	glDisable(GL_BLEND); // HACK HACK!
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Render::DrawText(int x, int y, float red, float green, float blue, string strText)
{
	char		text[1024];									// Holds Our String
	va_list		ap;											// Pointer To List Of Arguments

	if (strText.empty())									// If There's No Text
		return;												// Do Nothing

// FIXME:
//	va_start(ap, strText);									// Parses The String For Variables
	    sprintf(text, strText.c_str(), ap);				// And Converts Symbols To Actual Numbers
//	va_end(ap);												// Results Are Stored In Text
// END: FIXME

	// Choose new color
	glColor3f(red, green, blue);

	for(int i=0; text[i]; i++)
	{
		DrawChar(x, y, text[i]);
		x += m_nTextWidths[text[i]] * (m_nTextWidth / 8);
	}

	glColor3f(1.0f, 1.0f, 1.0f);
}

void Render::DrawChar(int x, int y, char c)
{
	//c &= 255;
	if ( (c&127) == 32 )
		return;		// space

	if (y <= -8)
		return;			// totally off screen

	int row = c>>4;		// Calculate charter position on sheet
	int col = c&15;
	float frow  = row * 0.125;
	float fcol  = col * 0.0625;

	SetState(m_tFont);
	glBegin(GL_QUADS);
		glTexCoord2f(fcol,          frow);			glVertex2i(x,				 y);
		glTexCoord2f(fcol,          frow + 0.125);	glVertex2i(x,				 y + m_nTextHeight);
		glTexCoord2f(fcol + 0.0625, frow + 0.125);	glVertex2i(x + m_nTextWidth, y + m_nTextHeight);
		glTexCoord2f(fcol + 0.0625, frow);			glVertex2i(x + m_nTextWidth, y);
	glEnd();
}

void Render::EndFrame()
{
	SDL_GL_SwapBuffers();
}

/*------------------------------------------------------------------------
	Texture Loading / Deleting Code:
------------------------------------------------------------------------*/

TexInfo* Render::LoadTexture(string szTexture, int nFlags /*TF_FILTER_LINEAR*/)
{
	// Check if this texture is already loaded
	for (TexVector::iterator i = m_vTexRefs.begin(); i != m_vTexRefs.end(); i++)
	{
		if((*i)->name == szTexture)
		{
			(*i)->iCount++;
			return (*i)->info;
		}
	}

	// If it isen't loaded yet, create a TexRef and load the texture
	TexRef *pTex = new TexRef;
	
	pTex->name   = szTexture;
	pTex->iCount = 1;

	pTex->info = new TexInfo;
	pTex->info->num	= (~0);
	pTex->info->flags = nFlags;

	LoadGLTexture(pTex);

	m_vTexRefs.push_back(pTex);
	return pTex->info;
}

void Render::DeleteTexture(TexInfo *pInfo)
{
	if(pInfo == NULL)
		return;

	for(TexVector::iterator i = m_vTexRefs.begin(); i != m_vTexRefs.end(); i++)
	{
		if((*i)->info == pInfo)
		{
			if((*i)->iCount > 0)
				(*i)->iCount--;
			
			if((*i)->iCount == 0)
			{
				if((*i)->info->num != (~0))
					glDeleteTextures(1, &((*i)->info->num));

				delete    (*i)->info; (*i)->info = NULL;
				delete    *i;
				m_vTexRefs.erase(i);
			}
			return;
		}
	}
}

/*------------------------------------------------------------------------
	Protected Members:
------------------------------------------------------------------------*/

/*
 *	Lädt ein Bild und erstellt damit eineOpenGL texture
 *	Die ID der OpenGL Texture wird in pRef->info->num hinterlegt
 */
void Render::LoadGLTexture(TexRef *pRef)
{
    SDL_Surface *image;
	
	image = IMG_Load(pRef->name.c_str());
	if ( image == NULL ) 
	{
	    cerr << "Unable to load " << pRef->name << " " << SDL_GetError() << endl;
		LoadDefaultTex(pRef);
	}	
	else
	{
		IMAGE_TYPE type = GetFileType(pRef->name);
		switch(type)
		{
		case IT_JPG:
		case IT_PNG:
		case IT_PCX:
			RGB_Decode(image, pRef);
			break;

		default:
			BGR_Decode(image, pRef);
			break;
		}	
	}

	RegisterTexture(pRef);
	delete [] pRef->mem;
    SDL_FreeSurface(image); // gibt den Speicher des temporären Surfaces wieder frei...    // by gm
	return;
}

/*
 *	Kopiert das Bild so wie es ist von der Surface in die pRef Strucktur
 */
void Render::RGB_Decode(SDL_Surface *image, TexRef *pRef)
{
	BYTE *dest, *src;
	int x, y;

	int w   = pRef->info->width  = image->w;
	int h   = pRef->info->height = image->h;
	pRef->bpp = image->format->BytesPerPixel;

	// Copy from surface to pRef
	pRef->mem = new BYTE[w * h * pRef->bpp];
	dest = pRef->mem;
	for(y=0; y<h; y++)
	{
		src = (BYTE*)image->pixels + y*image->pitch;
		for(x=0; x<w; x++)
		{
			*dest++ = *src; src++;
			*dest++ = *src; src++;
			*dest++ = *src; src++;
		}
	}
}

/*
 *	Konvertiert von BGR zu RGB
 *  Magenta Pixel werden als transparent angesehen!
 */
void Render::BGR_Decode(SDL_Surface *image, TexRef *pRef)
{
	BYTE red, green, blue;
	BYTE *dest, *src;
	int x, y;

	int w   = pRef->info->width  = image->w;
	int h   = pRef->info->height = image->h;
	pRef->bpp = image->format->BytesPerPixel;

	// Check if the image has transparency
	if(pRef->bpp == 3)
	{
		for(y=0; y<h; y++)
		{
			src = (BYTE*)image->pixels + y*image->pitch;
			for(x=0; x<w; x++)
			{
				if(*src == 255 && *(src+1) == 0 && *(src+2) == 255)
				{
					pRef->bpp = 4;
					pRef->info->flags |= TF_ALPHATEST;
					break;
				}
				src += 3;
			}
			if(pRef->bpp == 4)
				break;
		}
	}
	else //if(pRef->bpp == 4) // bpp kann nur 3 oder 4 sein!
	{
		pRef->info->flags |= TF_ALPHABLEND;
	}

	// Convert the bicture from BGR to RGB(A)
	pRef->mem = new BYTE[w * h * pRef->bpp];
	dest = pRef->mem;
	for(y=0; y<h; y++)
	{
		src = (BYTE*)image->pixels + y*image->pitch;
		for(x=0; x<w; x++)
		{
			blue  = *src; src++;
			green = *src; src++;
			red   = *src; src++;
			*dest++ = red;
			*dest++ = green;
			*dest++ = blue;

			if(pRef->bpp == 4)
			{
				if(pRef->info->flags & TF_ALPHATEST)
				{
					if(red == 255 && green == 0 && blue == 255)
						*dest++ = 0;
					else
						*dest++ = 255;
				}
				else
				{
					*dest++ = *src; src++;
				}
			}
		}
	}
}

/*
 *  Loads a default texture
 */
void Render::LoadDefaultTex(Render::TexRef *pRef)
{
	cerr << "Loading default texture instead of " << pRef->mem << endl;

	pRef->mem = new BYTE[3];
	pRef->mem[0] = ~0;	// Just red
	pRef->mem[1] =  0;
	pRef->mem[2] =  0;
	pRef->info->width  = 1;
	pRef->info->height = 1;
	pRef->bpp = 3;
}

bool Render::RegisterTexture(Render::TexRef *pRef)
{
	BYTE *mem;
	int format;
	int newWidth  = NextPowerOfTwo(pRef->info->width);
	int newHeight = NextPowerOfTwo(pRef->info->height);

	switch(pRef->bpp)
	{
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		format = GL_RGB;
	}

	// Get the maximal texture size supported, and change the size of the texture if it is to big
	int iMaxTextureSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &iMaxTextureSize);
	if(newWidth  > iMaxTextureSize) newWidth  = iMaxTextureSize;
	if(newHeight > iMaxTextureSize) newHeight = iMaxTextureSize;

	// Scale the texture if it's actuall size differs from the new size
	if(pRef->info->width != newWidth || pRef->info->height != newHeight)
	{
		mem = new BYTE[newHeight * newWidth * pRef->bpp];
		ScaleImage(format, pRef->info->width, pRef->info->height, pRef->mem, newWidth, newHeight, mem);
	}
	else
		mem = pRef->mem;

	glGenTextures(1, &pRef->info->num);		// Create The Texture

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, pRef->info->num);
	if(glGetError() != GL_NO_ERROR)
		return false;

	glTexImage2D(GL_TEXTURE_2D, 0, pRef->bpp, newWidth, newHeight, 0, format, GL_UNSIGNED_BYTE, mem);
	if(glGetError() != GL_NO_ERROR)
		return false;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Disable Antialiazing for magnification/minification
	GLint nFilter = GL_NEAREST;
	if(pRef->info->flags & TF_FILTER_LINEAR)
		nFilter = GL_LINEAR;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, nFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, nFilter);

	if(mem != pRef->mem)
		delete [] mem;	
	return true;
}

/*
 *  Determines the type of the file (bmp, tga or unkown)
 */
IMAGE_TYPE Render::GetFileType(string name)
{
	if(name.find(".bmp") != string::npos)
		return IT_BMP;
	else if (name.find(".tga") != string::npos)
		return IT_TGA;
	else if (name.find(".jpg") != string::npos)
		return IT_JPG;
	else if (name.find(".png") != string::npos)
		return IT_PNG;
	else if (name.find(".pcx") != string::npos)
		return IT_PCX;
	else 
		return IT_UNKNOWN;
}

/*
 * Find the value nearest to n which is also a power of two.
 */
int Render::NextPowerOfTwo(int n)
{
	/*int m;
	for (m=1; m<n; m*=2);

	if (m-n <= n-m/2)
	{
		return m;
	}
	else 
	{
		return m/2;
	}*/

	// This code yield better results but uses more memory
	int m = n;
	int answer = 0;
	while(m>>=1)
		answer++;

	answer = (1<<answer);
	if(answer < n)
		answer <<= 1;

	return answer;
}

/*
 *  Scales / Resizes the image 
 */
void Render::ScaleImage(GLenum format, int inwidth, int inheight, const BYTE *in,
				 int outwidth, int outheight, BYTE *out )
{
	int			i, j;
	const BYTE	*inrow;
	DWORD		frac, fracstep;

	fracstep = inwidth * 0x10000 / outwidth;

	switch(format)
	{
		case GL_RGB:
			for(i=0; i<outheight; i++, out+=outwidth*3)
			{
				inrow = in + 3*inwidth*(i*inheight/outheight);
				frac = fracstep >> 1;
				for(j=0; j<outwidth*3; j+=3) 
				{
					out[j]   = inrow[(frac>>16)*3];
					out[j+1] = inrow[(frac>>16)*3+1];
					out[j+2] = inrow[(frac>>16)*3+2];
					frac += fracstep;
				}
			}
			break;
			
		case GL_RGBA:
			for(i=0; i<outheight; i++, out+=outwidth*4) 
			{
				inrow = in + 4*inwidth*(i*inheight/outheight);
				frac = fracstep >> 1;
				for (j=0 ; j<outwidth*4 ; j+=4) 
				{
					out[j]   = inrow[(frac>>16)*4  ];
					out[j+1] = inrow[(frac>>16)*4+1];
					out[j+2] = inrow[(frac>>16)*4+2];
					out[j+3] = inrow[(frac>>16)*4+3];
					frac += fracstep;
				}
			}
			break;
	}
}

/***** und hinzufügen in cpp: */
    void Render::DrawText(SDL_Rect r, float red, float green, float blue, 
string strText)
    {
   	char		text[1024]; // Holds Our String
	va_list		ap;         // Pointer To List Of Arguments

	if (strText.empty())        // If There's No Text
		return;             // Do Nothing

// FIXME
//        va_start(ap, strText);      // Parses The String For Variables
        sprintf(text, strText.c_str(), ap); // And Converts Symbols To Actual Numbers
//	va_end(ap);                 // Results Are Stored In Text
// END: FIXME

        int length = 0;

        for(int i=0; text[i]; ++i)
	{
            length += m_nTextWidths[text[i]] * (m_nTextWidth / 8);
	}

        DrawText(r.x + r.w/2 - length/2, r.y + r.h/2 - m_nTextHeight/2, red, 
green, blue, text);
    }

    int Render::TextWidth(string strText)
    {
   	char		text[1024]; // Holds Our String
	va_list		ap;         // Pointer To List Of Arguments

	if (strText.empty())        // If There's No Text
		return 0;           // Do Nothing

// FIXME
//	va_start(ap, strText);      // Parses The String For Variables
        sprintf(text, strText.c_str(), ap); // And Converts Symbols To Actual Numbers
//	va_end(ap);                 // Results Are Stored In text
// END: FIXME

        int length = 0;

        for(int i=0; text[i]; ++i)
	{
		length += m_nTextWidths[text[i]] * (m_nTextWidth / 8);
	}

        return length;
    }
