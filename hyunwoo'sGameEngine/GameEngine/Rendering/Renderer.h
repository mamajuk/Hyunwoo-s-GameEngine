#pragma once
#include <windows.h>
#include <string>
#include "../Math/Vector.h"
#include "../Math/Color.h"
using namespace hyunwoo;

namespace hyunwoo {
	class Renderer;
}


/****************************************************
 *   랜더링 로직을 책임지는 클래스입니다....
 ********/
class hyunwoo::Renderer final
{
private:
	//===================================================
	/////////			  Fields..				 ////////
	//===================================================
	bool    _isInit = false;
	UINT    _width = 0;
	UINT    _height = 0;
	HDC     _memDC = NULL;
	HWND    _mainHwnd = NULL;
	DWORD* _backBuffer_ptr = nullptr;
	HBITMAP _old_bitmap = NULL;
	HBITMAP _backBuffer_bitmap = NULL;



	//=========================================================
	//////////				Property				///////////
	//=========================================================
public:
	uint64_t    bUsedAutoClear : 1 = true;
	LinearColor BackgroundColor = LinearColor::White;

	const bool IsInit()        const { return _isInit; }
	const int  GetWidth()      const { return _width; }
	const int  GetHeight()     const { return _height; }
	const HDC  GetMemoryDC()   const { return _memDC; }
	const HWND GetTargetHwnd() const { return _mainHwnd; }



	//========================================================
	////////			 Public methods..		      ////////
	//========================================================
	Renderer() = default;
	Renderer(const Renderer&) = delete;
	~Renderer();

	bool Init(HWND targetHwnd, UINT width, UINT height);

	void UpdateScreen();
	void ClearScreen(const LinearColor& color = LinearColor::White);

	void SetPixel(const Vector2& pos, const LinearColor& color = LinearColor::Black);
	void DrawTextField(const std::wstring& text, const Vector2& pos = Vector2::Zero, const LinearColor& color = LinearColor::Black);
	void DrawLine(const Vector2& start, const Vector2& end, const LinearColor& color = LinearColor::Black);

	const Vector2Int CartesianToScreen(const Vector2& cartesianPos) const;
	const Vector2    ScreenToCartesian(const Vector2Int& screenPos) const;



	//==========================================================
	////////			Private methods..				////////
	//==========================================================
private:
	void SetPixel_internal(int index, const LinearColor& color = LinearColor::Black);
	void SetPixel_internal(int x, int y, const LinearColor& color = LinearColor::Black);

	Vector2 GetClipPoint_internal(const Vector2& p0, const Vector2& p1) const;
};