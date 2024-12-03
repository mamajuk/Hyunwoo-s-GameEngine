#pragma once

namespace hyunwoo {

	enum class KeyCode
	{
		Left_Mouse = 0x01,
		Right_Mouse = 0x02,
		Crtl_Break = 0x03,
		Mid_Mouse = 0x04,
		X1_Mouse = 0x05,
		X2_Mouse = 0x06,
		BACK_SPACE = 0x08,
		TAB = 0x09,
		CLEAR = 0x0C,
		ENTURN = 0x0D,
		SHIFT = 0x10,
		CONTROL = 0x11,
		ALT = 0x12,
		PAUSE = 0x13,
		CAPS_LOCK = 0x14,
		IME_KANA = 0x14,
		IME_HANGUL = 0x15,
		IME_JUNJA = 0x17,
		IME_FINAL = 0x18,
		IME_HANJA = 0x19,
		IME_KANJI = 0x19,
		IME_OFF = 0x1A,
		ESC = 0x1B,
		IME_CONVERT = 0x1C,
		IME_ACCEPT = 0x1E,
		IME_MODECHANGE = 0x1F,
		SPACE = 0x20,
		PAGE_UP = 0x21,
		PAGE_DOWN = 0x22,
		END = 0x23,
		HOME = 0x24,
		LEFT = 0x25,
		UP = 0x26,
		RIGHT = 0x27,
		DOWN = 0x28,
		SELECT = 0x29,
		PRINT = 0x2A,
		EXECUTE = 0x2B,
		PRINT_SCREEN = 0x2C,
		INSERT = 0x2D,
		DEL = 0x2E,
		HELP = 0x2F,
		NUM_0 = 0x30,
		NUM_1 = 0x31,
		NUM_2 = 0x32,
		NUM_3 = 0x33,
		NUM_4 = 0x34,
		NUM_5 = 0x35,
		NUM_6 = 0x36,
		NUM_7 = 0x37,
		NUM_8 = 0x38,
		NUM_9 = 0x39,
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,
		LEFT_WINDOW = 0x5B,
		RIGHT_WINDOW = 0x5C,
		APPLICATION = 0x5D,
		SLEEP = 0x5F,
		NUMPAD_0 = 0x60,
		NUMPAD_1 = 0x61,
		NUMPAD_2 = 0x62,
		NUMPAD_3 = 0x63,
		NUMPAD_4 = 0x64,
		NUMPAD_5 = 0x65,
		NUMPAD_6 = 0x66,
		NUMPAD_7 = 0x67,
		NUMPAD_8 = 0x68,
		NUMPAD_9 = 0x69,
		MULTIPLY = 0x6A,
		ADD = 0x6B,
		SEPARATOR = 0x6C,
		SUBTRACT = 0x6C,
		DECIMAL = 0x6E,
		DIVIDE = 0x6F,
		F1 = 0x70,
		F2 = 0x71,
		F3 = 0x72,
		F4 = 0x73,
		F5 = 0x74,
		F6 = 0x75,
		F7 = 0x76,
		F8 = 0x77,
		F9 = 0x78,
		F10 = 0x79,
		F11 = 0x80,
		F12 = 0x81,
		LEFT_SHIFT = 0xA0,
		RIGHT_SHIFT = 0xA1,
		LEFT_CTRL = 0xA2,
		RIGHT_CTRL = 0xA3,
		LEFT_ALT = 0xA4,
		RIGHT_ALT = 0xA5
	};

	enum class KeyState : char
	{
		NONE = 0,
		DOWN = 1,
		UP = 2,
		Invalid = 4,
	};

	class InputManager;
}


/******************************************************************
 *   게임에 사용되는 입력값들을 얻을 수 있는 인터페이스입니다....
 *******/
class hyunwoo::InputManager final
{

	//===============================================
	///////			    Fields				 ////////
	//===============================================
private:
	char _keyStates[255];


	//========================================================
	///////			     Constructor				  ////////
	//========================================================
public:
	InputManager() : _keyStates{ 0, } {};


	//=======================================================
	////////			 Public methods				/////////
	//=======================================================
public:
	bool GetKey(KeyCode keycode)     const;
	bool GetKeyUp(KeyCode keycode)   const;
	bool GetKeyDown(KeyCode keycode) const;

	float GetAxisValue(KeyCode minusDirKey, KeyCode plusDirKey) const;

	void SetKeyState(int keyCode, KeyState state);
	void UpdateBuffer();
};