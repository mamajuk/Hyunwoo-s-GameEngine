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

	/**�̹� Ȱ��ȭ�Ǿ��ִ� ���ӿ��� ��ü�� �����ϴ°�?*/
	if (_active_enginePtr != nullptr) return false;

	/*******************************************
	 *   ������ Ŭ������ �ʱ�ȭ�Ѵ�...
	 *******/
	wc.lpfnWndProc   = WndProc_internal;
	wc.lpszClassName = appName.c_str();
	wc.lpszMenuName  = NULL;
	wc.style		 = (CS_HREDRAW | CS_VREDRAW);
	wc.hInstance     = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);


	/**������ Ŭ���� ����� �����ߴ°�?*/
	if (RegisterClassW(&wc)==NULL) {
		return false;
	}

	_active_enginePtr = this;

	/**������ â�� �����ϰ�, ������ â�� ���� �ڵ��� ��´�...*/
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

	/**������ �����츦 ǥ���Ѵ�...*/
	ShowWindow(_mainHwnd, bShowCmd);


	/**�������� �ʱ�ȭ���� ���ߴ°�?*/
	GetClientRect(_mainHwnd, &rect);
	if (_renderer.Init(_mainHwnd, rect.right, rect.bottom) == false) {
		_active_enginePtr         = nullptr;
		return false;
	}

	_attribute.bEngine_initialized   = true;
	_attribute.bRenderer_initialized = true;
	OnEngine_Started();


	/*****************************************************************
	 *    ���������� ���� ���� ����. ���� ������ �����Ѵ�....
	 **********/
	MSG         msg         = { 0, };
	Time_point  prevTime    = High_clock::now();

	int         fpsCounts   = 0;
	float       totalTime   = 0.f;
	float       updateTime  = 0.f;

	while (msg.message!=WM_QUIT) 
	{
		/******************************************************
		*   ������ ť�� �ִ� �޼������� ��� ó���Ѵ�....
		*********/
		if (PeekMessage(&msg, 0,0,0,PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		/*****************************************************
		 *   ������ ���� �̺�Ʈ�� �����Ѵ�....
		 ********/
		float deltaTime = std::chrono::duration_cast<Float_duration>(High_clock::now()-prevTime).count();

		/**���� fps���� �����Ѵ�...**/
		if ((totalTime += deltaTime) >= 1.f) {
			_cur_fps  = (fpsCounts+1);
			fpsCounts = 0;
			totalTime = 0.f;
		}

		/**������ ������Ʈ�� �ʿ��Ѱ�?*/
		if ((updateTime+=deltaTime)>=_timerElapse) 
		{
			/**ȭ���� �ʱ�ȭ�ϴ°�?*/
			if (_renderer.bUsedAutoClear) {
				_renderer.ClearScreen(_renderer.BackgroundColor);
			}

			/**������ ������Ʈ ��, ȭ���� �����Ѵ�...*/
			OnEngine_EnterFrame(updateTime);
			InvalidateRect(_mainHwnd, NULL, false);

			_input.UpdateBuffer();
			fpsCounts++;
			updateTime = 0.f;
		}

		prevTime = High_clock::now();
	}

	OnEngine_Ended();

	/**Ȱ��ȭ�� ������ ������ ���´�...*/
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
	 *    �޼��� ������ ���� ó���� �����Ѵ�....
	 ********/
	switch (msg) {

		/**�����찡 �����Ǿ��� ���...*****************************/
		case(WM_CREATE): {
			break;
		}


		/**ȭ�� ���� �̺�Ʈ*******************************************/
		case(WM_PAINT): {
			renderer.UpdateScreen();
			break;
		}


		/**Ű���� �̺�Ʈ....********************************************/
		case(WM_KEYDOWN): {
			input.SetKeyState(wparam, KeyState::DOWN);
			break;
		}


		/**Ű�� �̺�Ʈ***************************************************/
		case(WM_KEYUP): {
			input.SetKeyState(wparam, KeyState::UP);
			break;
		}


		/**�����찡 �ı��Ǿ������....**********************************/
		case(WM_DESTROY): {
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}