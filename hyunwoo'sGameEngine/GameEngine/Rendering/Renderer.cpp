#include "Renderer.h"

hyunwoo::Renderer::~Renderer()
{
    if (_isInit) {
        SelectObject(_memDC, _old_bitmap);
        DeleteObject(_backBuffer_bitmap);
        DeleteDC(_memDC);
    }
}

bool hyunwoo::Renderer::Init(HWND targetHwnd, UINT width, UINT height)
{
    /**이미 초기화가 되어있는가?*/
    if (_isInit) {
        SelectObject(_memDC, _old_bitmap);
        DeleteObject(_backBuffer_bitmap);
        DeleteDC(_memDC);
    }

    /****************************************************************************
     *    화면 DC와 대응되는 메모리 DC를 만들고, 메모리 DC에 대응되는 비트맵을 만든다..
     *********/
    BITMAPINFO info              = { 0, };
    info.bmiHeader.biWidth       = width;
    info.bmiHeader.biHeight      = height;
    info.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biBitCount    = 32;
    info.bmiHeader.biPlanes      = 1;
    info.bmiHeader.biCompression = BI_RGB;

    HDC hdc = GetDC(targetHwnd);
    _memDC  = CreateCompatibleDC(hdc);

    /**비트맵 생성에 실패했는가?*/
    if ((_backBuffer_bitmap = CreateDIBSection(hdc, &info, DIB_RGB_COLORS, (void**)&_backBuffer_ptr, NULL, 0))==NULL) {
        return false;
    }

    /**변수 초기화...*/
    _width      = width;
    _height     = height;
    _mainHwnd   = targetHwnd;
    _isInit     = true;

    /**메모리DC는 항상 해당 비트맵을 GDI 도구로서 사용함을 선언...*/
    _old_bitmap = (HBITMAP)SelectObject(_memDC, _backBuffer_bitmap);
    ReleaseDC(targetHwnd, hdc);

    ClearScreen();
    return true;
}

void hyunwoo::Renderer::UpdateScreen()
{
    if (_isInit == false) return;

    /*******************************************
     *   화면을 갱신한다....
     *******/
    HDC         hdc;
    RECT        rect;
    PAINTSTRUCT ps;
    GetClientRect(_mainHwnd, &rect);

    hdc = BeginPaint(_mainHwnd, &ps);
    StretchBlt(hdc, 0, 0, rect.right, rect.bottom, _memDC, 0, 0, _width, _height, SRCCOPY);
    EndPaint(_mainHwnd, &ps);
}

void hyunwoo::Renderer::ClearScreen(const LinearColor& color)
{
    if (_isInit == false) return;

    memset(_backBuffer_ptr, color.ToDWORD_rgba(2, 1, 0, 3), (_width*_height) * sizeof(DWORD));
}

void hyunwoo::Renderer::SetPixel_internal(int index, const LinearColor& color)
{
    if (_isInit == false || index < 0 || index >= (_width * _height)) {
        return;
    }

    _backBuffer_ptr[index] = color.ToDWORD_rgba(2,1,0,3);
}

void hyunwoo::Renderer::SetPixel_internal(int x, int y, const LinearColor& color)
{
    const int idx = (y * _width) + x;
    if (_isInit == false || idx < 0 || idx >= (_width * _height)) {
        return;
    }

    _backBuffer_ptr[idx] = color.ToDWORD_rgba(2,1,0,3);
}

Vector2 hyunwoo::Renderer::GetClipPoint_internal(const Vector2& p0, const Vector2& p1) const
{
    /************************************************************
    *   카타시안 좌표계에서, 비트맵 크기만큼 클립핑을 진행한다....
    ********/
    const float width1_2  = _width * 0.5f;
    const float height1_2 = _height * 0.5f;

    Vector2 ret = p0;

    // Top or Bottom
    if (p0.y > height1_2) {
        const float s = (height1_2 - p1.y) / (ret.y - p1.y);
        ret = (ret * s) + p1 * (1.f - s);
    }
    else if (p0.y < -height1_2) {
        const float s = -(height1_2 + p1.y) / (ret.y - p1.y);
        ret = (ret * s) + p1 * (1.f - s);
    }

    // Left or Right
    if (p0.x > width1_2) {
        const float s = (width1_2 - p1.x) / (ret.x - p1.x);
        ret = (ret * s) + p1 * (1.f - s);
    }
    else if (p0.x < -width1_2) {
        const float s = -(width1_2 + p1.x) / (ret.x - p1.x);
        ret = (ret * s) + p1 * (1.f - s);
    }

    return ret;
}

void hyunwoo::Renderer::SetPixel(const Vector2& pos, const LinearColor& color)
{
    const Vector2Int screenPos = CartesianToScreen(pos);
    SetPixel_internal(screenPos.x, screenPos.y, color);
}

void hyunwoo::Renderer::DrawTextField(const std::wstring& text, const Vector2& pos, const LinearColor& color)
{
    if (_isInit == false) return;

    /**스크린 좌표계로 변환한다....*/
    const float w = (_width * .5f);
    const float h = (_height * .5f);
    const Vector2Int screenPos = Vector2((w + pos.x), (h - pos.y));

    SetTextColor(_memDC, color.ToDWORD_rgb(0,1,2));
    TextOut(_memDC, screenPos.x, screenPos.y, text.c_str(), text.size());
}

void hyunwoo::Renderer::DrawLine(const Vector2& start, const Vector2& end, const LinearColor& color)
{
    const Vector2Int startPos = CartesianToScreen(GetClipPoint_internal(start, end));
    const Vector2Int endPos   = CartesianToScreen(GetClipPoint_internal(end, start));
    const Vector2Int dst      = (endPos-startPos);

    const int w    = Math::Abs(dst.x);
    const int h    = Math::Abs(dst.y);
    const int wDir = (dst.x>=0 ? 1:-1);
    const int hDir = (dst.y>=0 ? 1:-1);

    /****************************************************
     *    w가 더 클경우....
     *******/
    Vector2Int cur = startPos;

    if (w>=h) {
        int       d      = (2*h - w);
        const int dTrue  = (2*h);
        const int dFalse = (2 * (h-w));

        /**선을 찍는다....*/
        for(int i=0; i<w; i++)
        {
            SetPixel_internal(cur.x, cur.y, color);

            if (d < 0) d += dTrue;
            else
            {
                d += dFalse;
                cur.y += hDir;
            }

            cur.x += wDir;
        }

        return;
    }

    /************************************************
     *   h가 더 클경우....
     *******/
    int       d      = (2 * w - h);
    const int dTrue  = (2 * w);
    const int dFalse = (2 * (w - h));

    /**선을 찍는다....*/
    for (int i = 0; i < h; i++)
    {
        SetPixel_internal(cur.x, cur.y, color);

        if (d < 0) d += dTrue;
        else
        {
            d += dFalse;
            cur.x += wDir;
        }

        cur.y += hDir;
    }
}

const Vector2Int hyunwoo::Renderer::CartesianToScreen(const Vector2& cartesianPos) const
{
    if (_isInit == false) return Vector2Int::Zero;

    const float w = (_width*.5f);
    const float h = (_height*.5f);
    return Vector2((w+cartesianPos.x), (h+cartesianPos.y));
}

const Vector2 hyunwoo::Renderer::ScreenToCartesian(const Vector2Int& screenPos) const
{
    if (_isInit == false) return Vector2::Zero;

    const float w = (_width * .5f);
    const float h = (_height * .5f);
    return Vector2((w - screenPos.x), (h - screenPos.y));
}
