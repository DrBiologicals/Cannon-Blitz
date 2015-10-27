#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include <windows.h>

class CBackBuffer
{
public:
	CBackBuffer();
	virtual ~CBackBuffer();

	virtual bool Initialise(HWND _hWnd, int _iWidth, int _iHeight);

	HDC GetBackDC() const;

	int GetHeight() const;
	int GetWidth() const;

	void Clear();
	void Present();

private:
	CBackBuffer(const CBackBuffer& _kr);
	CBackBuffer& operator= (const CBackBuffer& _kr);

protected:
	HWND m_hWnd;
	HDC m_hDC;
	HBITMAP m_hSurface;
	HBITMAP m_hOldObject;
	int m_iWidth;
	int m_iHeight;
};
#endif //__BACKBUFFER_H__
