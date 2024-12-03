#pragma once
#include <cmath>
#include "Vector.h"

namespace hyunwoo {
	class Math;
	class Vector2;
}


/*******************************************************
 *   ���� ���� ��ɵ��� ������ Ŭ�����Դϴ�....
 ********/
class hyunwoo::Math final
{
	//========================================================
	////////				Property..				//////////
	//========================================================
	static constexpr float PI        = 3.14159265359f;
	static constexpr float Rad2Angle = (180.f / PI);
	static constexpr float Angle2Rad = (PI / 180.f);



private:
	//=================================================================
	/////////			Constructor	and Destructor			 //////////
	//=================================================================
	Math()			  = delete;
	Math(const Math&) = delete;
	~Math()			  = delete;



	//=========================================================
	///////////			 Public methods..			///////////
	//=========================================================
public:
	static const float Cos(const float radian) {
		return cosf(radian);
	}

	static const float Sin(const float radian) {
		return sinf(radian);
	}

	static const float Tan(const float radian) {
		return tanf(radian);
	}

	static const float Acos(const float cos_value) {
		return acosf(cos_value);
	}

	static const float ASin(const float sin_value) {
		return asinf(sin_value);
	}

	static const float Atan(const float tan_value) {
		return atanf(tan_value);
	}

	static const float Atan2(const float y, const float x) {
		return atan2f(y, x);
	}

	static const float Atan2(const hyunwoo::Vector2& rhs);

	static const float Sqrt(const float rhs) {
		return sqrtf(rhs);
	}

	static const int Sqrt(const int rhs) {
		return sqrtl(rhs);
	}

	static const float Abs(const float rhs) {
		return fabsf(rhs);
	}

	static const int Abs(const int rhs) {
		return labs(rhs);
	}

	static const float Range(const float value, const float min, const float max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	static const float Range01(const float value) {
		if (value < 0.f) return 0.f;
		if (value > 1.f) return 0.f;
		return value;
	}

	template<typename T, typename...Tn>
	static const float Max(const T lhs, Tn... args) {
		float max = lhs;
		(((args>max) && (max=args)),...);
		return max;
	}

	template<typename T, typename...Tn>
	static const float Min(const T lhs, Tn... args) {
		float min = lhs;
		(((args < min) && (min = args)), ...);
		return min;
	}
};