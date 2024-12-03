#include "String_lamda.h"

std::string hyunwoo::$::str;
std::wstring hyunwoo::w$::str;

void hyunwoo::WString_lamda::add_wstring(const wchar_t* string)
{
	str += string;
}

void hyunwoo::WString_lamda::add_wstring(const Vector2& vec)
{
	str += L"(";
	str += std::to_wstring(vec.x);
	str += L", ";
	str += std::to_wstring(vec.y);
	str += L")";
}

void hyunwoo::WString_lamda::add_wstring(const Vector3& vec)
{
	str += L"(";
	str += std::to_wstring(vec.x);
	str += L", ";
	str += std::to_wstring(vec.y);
	str += L", ";
	str += std::to_wstring(vec.z);
	str += L")";
}

void hyunwoo::WString_lamda::add_wstirng(const Vector4& vec)
{
	str += L"(";
	str += std::to_wstring(vec.x);
	str += L", ";
	str += std::to_wstring(vec.y);
	str += L", ";
	str += std::to_wstring(vec.z);
	str += L", ";
	str += std::to_wstring(vec.w);
	str += L")";
}

void hyunwoo::WString_lamda::add_wstring(const Vector2Int& vec)
{
	str += L"(";
	str += std::to_wstring(vec.x);
	str += L", ";
	str += std::to_wstring(vec.y);
	str += L")";
}

void hyunwoo::WString_lamda::add_wstring(const Vector3Int& vec)
{
	str += L"(";
	str += std::to_wstring(vec.x);
	str += L", ";
	str += std::to_wstring(vec.y);
	str += L", ";
	str += std::to_wstring(vec.z);
	str += L")";
}

void hyunwoo::WString_lamda::add_wstirng(const Vector4Int& vec)
{
	str += L"(";
	str += std::to_wstring(vec.x);
	str += L", ";
	str += std::to_wstring(vec.y);
	str += L", ";
	str += std::to_wstring(vec.z);
	str += L", ";
	str += std::to_wstring(vec.w);
	str += L")";
}

void hyunwoo::WString_lamda::add_wstring(const LinearColor& color)
{
	str += L"(";
	str += std::to_wstring(color.r);
	str += L", ";
	str += std::to_wstring(color.g);
	str += L", ";
	str += std::to_wstring(color.b);
	str += L")";
}

void hyunwoo::String_lamda::add_string(const char* string)
{
	str += string;
}

void hyunwoo::String_lamda::add_string(const Vector2& vec)
{
	str += "(";
	str += std::to_string(vec.x);
	str += ", ";
	str += std::to_string(vec.y);
	str += ")";
}

void hyunwoo::String_lamda::add_string(const Vector3& vec)
{
	str += "(";
	str += std::to_string(vec.x);
	str += ", ";
	str += std::to_string(vec.y);
	str += ", ";
	str += std::to_string(vec.z);
	str += ")";
}

void hyunwoo::String_lamda::add_stirng(const Vector4& vec)
{
	str += "(";
	str += std::to_string(vec.x);
	str += ", ";
	str += std::to_string(vec.y);
	str += ", ";
	str += std::to_string(vec.z);
	str += ", ";
	str += std::to_string(vec.w);
	str += ")";
}

void hyunwoo::String_lamda::add_string(const Vector2Int& vec)
{
	str += "(";
	str += std::to_string(vec.x);
	str += ", ";
	str += std::to_string(vec.y);
	str += ")";
}

void hyunwoo::String_lamda::add_string(const Vector3Int& vec)
{
	str += "(";
	str += std::to_string(vec.x);
	str += ", ";
	str += std::to_string(vec.y);
	str += ", ";
	str += std::to_string(vec.z);
	str += ")";
}

void hyunwoo::String_lamda::add_stirng(const Vector4Int& vec)
{
	str += "(";
	str += std::to_string(vec.x);
	str += ", ";
	str += std::to_string(vec.y);
	str += ", ";
	str += std::to_string(vec.z);
	str += ", ";
	str += std::to_string(vec.w);
	str += ")";
}

void hyunwoo::String_lamda::add_string(const LinearColor& color)
{
	str += "(";
	str += std::to_string(color.r);
	str += ", ";
	str += std::to_string(color.g);
	str += ", ";
	str += std::to_string(color.b);
	str += ")";
}
