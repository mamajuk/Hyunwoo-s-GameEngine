#include "GameEngine.h"
#include "Utility/String_lamda.h"
using namespace hyunwoo;

GameEngine* GameEngine::_active_enginePtr = nullptr;

void hyunwoo::GameEngine::SetTargetFrameRate(UINT newTargetFrame)
{
	if (_active_enginePtr != this) return;
	_targetFps   = newTargetFrame;
	_timerElapse = (1.f/ float(newTargetFrame));
}

const bool hyunwoo::GameEngine::Start(const std::wstring& appName, HINSTANCE hInstance, LPWSTR commandLine, const int bShowCmd )
{
	RECT     rect;
	WNDCLASS wc = { 0, };

	/**이미 활성화되어있는 게임엔진 객체가 존재하는가?*/
	if (_active_enginePtr != nullptr) return false;

	/*******************************************
	 *   윈도우 클래스를 초기화한다...
	 *******/
	wc.lpfnWndProc   = WndProc_internal;
	wc.lpszClassName = appName.c_str();
	wc.lpszMenuName  = NULL;
	wc.style		 = (CS_HREDRAW | CS_VREDRAW);
	wc.hInstance     = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);


	/**윈도우 클래스 등록을 실패했는가?*/
	if (RegisterClassW(&wc)==NULL) {
		return false;
	}

	_active_enginePtr = this;

	/**윈도우 창을 생성하고, 생성한 창에 대한 핸들을 얻는다...*/
	if ((_mainHwnd = CreateWindowW(
		appName.c_str(),
		appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL ))==NULL)
	{
		_active_enginePtr = nullptr;
		return false;
	}

	/**생성한 윈도우를 표시한다...*/
	ShowWindow(_mainHwnd, bShowCmd);


	/**랜더러를 초기화하지 못했는가?*/
	GetClientRect(_mainHwnd, &rect);
	if (_renderer.Init(_mainHwnd, rect.right, rect.bottom) == false) {
		_active_enginePtr         = nullptr;
		return false;
	}

	_attribute.bEngine_initialized   = true;
	_attribute.bRenderer_initialized = true;
	OnEngine_Started();


	/*****************************************************************
	 *    정상적으로 엔진 시작 성공. 메인 루프를 진행한다....
	 **********/
	MSG         msg         = { 0, };
	Time_point  prevTime    = High_clock::now();

	int         fpsCounts   = 0;
	float       totalTime   = 0.f;
	float       updateTime  = 0.f;

	while (msg.message!=WM_QUIT) 
	{
		/******************************************************
		*   윈도우 큐에 있는 메세지들을 모두 처리한다....
		*********/
		if (PeekMessage(&msg, 0,0,0,PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		/*****************************************************
		 *   프레임 진입 이벤트를 적용한다....
		 ********/
		float deltaTime = std::chrono::duration_cast<Float_duration>(High_clock::now()-prevTime).count();

		/**현재 fps값을 갱신한다...**/
		if ((totalTime += deltaTime) >= 1.f) {
			_cur_fps  = (fpsCounts+1);
			fpsCounts = 0;
			totalTime = 0.f;
		}

		/**프레임 업데이트가 필요한가?*/
		if ((updateTime+=deltaTime)>=_timerElapse) 
		{
			/**화면을 초기화하는가?*/
			if (_renderer.bUsedAutoClear) {
				_renderer.ClearScreen(_renderer.BackgroundColor);
			}

			/**프레임 업데이트 후, 화면을 갱신한다...*/
			OnEngine_EnterFrame(updateTime);
			InvalidateRect(_mainHwnd, NULL, false);

			_input.UpdateBuffer();
			fpsCounts++;
			updateTime = 0.f;
		}

		prevTime = High_clock::now();
	}

	OnEngine_Ended();

	/**활성화된 엔진의 참조를 끊는다...*/
	if (_active_enginePtr == this) {
		_active_enginePtr = nullptr;
	}

	return true;
}

LRESULT hyunwoo::GameEngine::WndProc_internal(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	GameEngine&   engine    = *_active_enginePtr;
	Attribute&    attribute = engine._attribute;
	Renderer&     renderer  = engine.GetRenderer();
	InputManager& input     = engine._input;

	/****************************************************
	 *    메세지 종류에 따른 처리를 진행한다....
	 ********/
	switch (msg) {

		/**윈도우가 생성되었을 경우...*****************************/
		case(WM_CREATE): {
			break;
		}


		/**화면 갱신 이벤트*******************************************/
		case(WM_PAINT): {
			renderer.UpdateScreen();
			break;
		}


		/**키누름 이벤트....********************************************/
		case(WM_KEYDOWN): {
			input.SetKeyState(wparam, KeyState::DOWN);
			break;
		}


		/**키뗌 이벤트***************************************************/
		case(WM_KEYUP): {
			input.SetKeyState(wparam, KeyState::UP);
			break;
		}


		/**윈도우가 파괴되었을경우....**********************************/
		case(WM_DESTROY): {
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}