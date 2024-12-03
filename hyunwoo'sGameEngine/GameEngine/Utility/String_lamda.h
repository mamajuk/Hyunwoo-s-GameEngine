#pragma once
#include <string>
#include "../Math/Vector.h"
#include "../Math/Color.h"

namespace hyunwoo {
	class String_lamda;
	class WString_lamda;

	using $  = String_lamda;
	using w$ = WString_lamda;
}


/*******************************************************************************
 *    복잡한 멀티바이트 환경의 문자열을 손쉽게 구성하고 반환하는 유틸리티 클래스입니다...
 *******/
class hyunwoo::String_lamda
{
private:
	//========================================================
	/////////			Private fields...			 /////////
	//========================================================
	static std::string  str;



	//========================================================
	//////////			Private methods...			//////////
	//=======================================================
	template<typename T>
	void add_string(const T& value) {
		str += std::to_string(value);
	}

	void add_string(const char* string);
	void add_string(const Vector2& vec);
	void add_string(const Vector3& vec);
	void add_stirng(const Vector4& vec);

	void add_string(const Vector2Int& vec);
	void add_string(const Vector3Int& vec);
	void add_stirng(const Vector4Int& vec);

	void add_string(const LinearColor& color);



	//======================================================
	/////////			Public methods..			////////
	//======================================================
public:
	String_lamda()					  = delete;
	String_lamda(const String_lamda&) = delete;
	~String_lamda()					  = default;

	template<typename...Tn>
	explicit constexpr String_lamda(Tn&&... args)
	{
		str.clear();
		((add_string(args)),...);
	}

	constexpr operator const std::string& () {
		return str;
	}

	constexpr operator const char* () {
		return str.c_str();
	}
};


/*********************************************************************************
 *    복잡한 유니코드 환경의 문자열을 손쉽게 구성하고 반환하는 유틸리티 클래스입니다...
 *******/
class hyunwoo::WString_lamda
{
private:
	//========================================================
	/////////			Private fields...			 /////////
	//========================================================
	static std::wstring str;



	//========================================================
	//////////			Private methods...			//////////
	//=======================================================
	template<typename T>
	void add_wstring(const T& value) {
		str += std::to_wstring(value);
	}

	void add_wstring(const wchar_t* string);
	void add_wstring(const Vector2& vec);
	void add_wstring(const Vector3& vec);
	void add_wstirng(const Vector4& vec);

	void add_wstring(const Vector2Int& vec);
	void add_wstring(const Vector3Int& vec);
	void add_wstirng(const Vector4Int& vec);

	void add_wstring(const LinearColor& color);



	//======================================================
	/////////			Public methods..			////////
	//======================================================
public:
	WString_lamda()					    = delete;
	WString_lamda(const WString_lamda&) = delete;
	~WString_lamda()				    = default;

	template<typename...Tn>
	explicit constexpr WString_lamda(Tn&&... args)
	{
		str.clear();
		((add_wstring(args)), ...);
	}

	constexpr operator const std::wstring& () {
		return str;
	}

	constexpr operator const wchar_t* () {
		return str.c_str();
	}
};