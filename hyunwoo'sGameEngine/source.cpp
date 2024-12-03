#include <windows.h>
#include "GameEngine/GameEngine.h"
#include "GameEngine/Utility/String_lamda.h"
#include "GameEngine/Math/Vector.h"
#include "GameEngine/Math/Color.h"
#include "GameEngine/Math/Math.h"
using namespace hyunwoo;

/*******************************************************
 *    ���ӿ������� ���� �������α׷��� ������ Ŭ�����Դϴ�..
 ********/
class TestApp : public GameEngine
{
	Vector2 _fpsPos = Vector2::Zero;
	Vector2 _txtPos = Vector2::Zero;
	Vector2 _pos    = {50.f, 50.f};

	float time = 0.f;

	/**������ �������� ���....**/
	virtual void OnEngine_Started() override {
		Renderer& renderer = GetRenderer();
		renderer.BackgroundColor = LinearColor::White;
		renderer.bUsedAutoClear  = true;

		_fpsPos = {renderer.GetWidth()*-.5f, renderer.GetHeight()*.5f};
		_txtPos = _fpsPos + (Vector2::Down * 100.f);

		SetTargetFrameRate(60);
	}

	/**������ ���� �̺�Ʈ.......**/
	virtual void OnEngine_EnterFrame(float deltaTime) override 
	{
		Renderer&           renderer = GetRenderer();
		const InputManager& input    = GetInputManager();

		Vector2 dir = {
			input.GetAxisValue(KeyCode::LEFT, KeyCode::RIGHT),
			input.GetAxisValue(KeyCode::DOWN, KeyCode::UP)
		};

		Vector2Int size = {
			renderer.GetWidth(),
			renderer.GetHeight()
		};

		_pos += (dir * 300.f * deltaTime);
		renderer.DrawLine(Vector2::Zero, _pos, LinearColor::Blue);
		renderer.DrawTextField(w$(L"fps :", GetFrameRate(), L"/ time: ", time+=deltaTime, L"/ deltaTime: ", deltaTime), _fpsPos);
		renderer.DrawTextField(w$(L"pos: ", Vector2Int(_pos), L", size: ", size), _txtPos, LinearColor::Purple);
		renderer.DrawLine(Vector2::Zero, _pos, LinearColor::Blue);


		Vector2 v = { -30.f, 40.f };
		Vector2 n = { -30.f, -15.f };

		renderer.DrawLine(Vector2::Zero, v, LinearColor::Green);
		renderer.DrawLine(Vector2::Zero, n, LinearColor::Red);
		renderer.DrawTextField(w$(L"v dot n: ", Vector2::Dot(v.GetNormalized(), n.GetNormalized())));
	}
};


/************************************************************
 *    ���α׷��� ������....
 *********/
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPWSTR commandLine, _In_ int bShowCmd)
{
	TestApp engine;
	engine.Start(L"�׽�Ʈ��", hInstance, commandLine, bShowCmd);

	return 0;
}