#pragma once
#include <Windows.h>
#include <iostream>
#include <chrono>
#include "Rendering/Renderer.h"
#include "Input/InputManager.h"

namespace hyunwoo {
	class GameEngine;
}

/************************************************************
 *    게임 엔진이 구현된 클래스입니다.....
 *********/
class hyunwoo::GameEngine
{
public:

	/**GameEngine의 속성을 담는 구조체입니다....*/
	struct Attribute {
		int64_t bEngine_initialized   : 1 = 0;
		int64_t bRenderer_initialized : 1 = 0;
	};

private:
	using Time_point      = std::chrono::high_resolution_clock::time_point;
	using High_clock      = std::chrono::high_resolution_clock;
	using Float_duration  = std::chrono::duration<float>;
	

	//=====================================================
	//////////			    Fields..				///////
	//=====================================================
	static GameEngine*  _active_enginePtr;

	/**델타타임과 프레임 관련 필드....*/
	UINT       _cur_fps      = 0;
	UINT       _targetFps    = 60;
	float      _timerElapse  = (1.f/60.f);

	/**엔진에서 사용되는 정보 및 객체들의 참조...*/
	HWND         _mainHwnd   = NULL;
	Attribute    _attribute;
	Renderer     _renderer; 
	InputManager _input;




	//===================================================
	/////////			   Property..			/////////
	//===================================================
public:
	UINT      GetTargetFrame() const { return _targetFps; }
	UINT      GetFrameRate()   const { return _cur_fps; };
	void      SetTargetFrameRate(UINT newTargetFrame);

	HWND				GetMainHWnd()    const  { return _mainHwnd; }
	Attribute			GetAttribute()   const  { return _attribute; }
	Renderer&			GetRenderer()           { return _renderer; }
	const InputManager& GetInputManager() const { return _input; }



	//=====================================================
	////////			Public methods				///////
	//=====================================================
	GameEngine()				  = default;
	GameEngine(const GameEngine&) = delete;
	virtual ~GameEngine()         = default;

	const bool Start( const std::wstring& appName, HINSTANCE hInstance, LPWSTR commandLine, const int bShowCmd );



	//============================================================
	//////////			  Override methods..			 /////////
	//============================================================
protected:
	virtual void OnEngine_Started() {}
	virtual void OnEngine_EnterFrame(float deltaTime) {}
	virtual void OnEngine_Ended() {}



private:
	//========================================================
	////////			Private methods..			 /////////
	//========================================================
	static LRESULT CALLBACK WndProc_internal(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};