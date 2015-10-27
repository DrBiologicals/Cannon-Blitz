#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <windows.h>

class CSprite
{
public:
	CSprite();
	virtual ~CSprite();

	virtual bool Initialise(int _iResourceID, int _iMaskResourceID);

	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	int GetWidth() const;
	int GetHeight() const;

	int GetX() const;
	int GetY() const;
	void SetX(int _i);
	void SetY(int _i);

	void TranslateRelative(int _iX, int _iY);
	void TranslateAbsolute(int _iX, int _iY);

private:
	CSprite(const CSprite& _kr);
	CSprite& operator= (const CSprite& _kr);

protected:
	static int s_iRefCount;
	static HDC s_hSharedSpriteDC;

	int m_iX;
	int m_iY;
	int m_iFrameWidth;

	HBITMAP m_hSprite;
	HBITMAP m_hMask;

	BITMAP m_bitmapSprite;
	BITMAP m_bitmapMask;
};
#endif // __SPRITE_H__
