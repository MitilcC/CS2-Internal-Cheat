#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"
// vector lib port from liv's OS-ImGui
class Vector2
{
public:
	float x, y;
public:
	Vector2() :x(0.f), y(0.f) {}
	Vector2(float x_, float y_) :x(x_), y(y_) {}
	Vector2(ImVec2 ImVec2_) :x(ImVec2_.x), y(ImVec2_.y) {}
	Vector2 operator+(Vector2 d);
	Vector2 operator-(Vector2 d);
	Vector2 operator*(Vector2 d);
	Vector2 operator*(float d);
	Vector2 operator/(float d);
	bool operator==(Vector2 Vector2_)
	{
		return x == Vector2_.x && y == Vector2_.y;
	}
	bool operator!=(Vector2 Vector2_)
	{
		return x != Vector2_.x || y != Vector2_.y;
	}
	ImVec2 ToImVec2()
	{
		return ImVec2(x, y);
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}
	float DistanceTo(const Vector2& Pos)
	{
		return sqrtf(powf(Pos.x - x, 2) + powf(Pos.y - y, 2));
	}
};

class Vector3
{
public:
	float x, y, z;
public:
	Vector3() :x(0.f), y(0.f), z(0.f) {}
	Vector3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
	Vector3 operator+(Vector3 d);
	Vector3 operator-(Vector3 d);
	Vector3 operator*(Vector3 d);
	Vector3 operator*(float d);
	Vector3 operator/(float d);

	bool operator==(Vector3 Vector3_)
	{
		return x == Vector3_.x && y == Vector3_.y && z == Vector3_.z;
	}
	bool operator!=(Vector3 Vector3_)
	{
		return x != Vector3_.x || y != Vector3_.y || z != Vector3_.z;
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}
	float DistanceTo(const Vector3& Pos)
	{
		return sqrtf(powf(Pos.x - x, 2) + powf(Pos.y - y, 2) + powf(Pos.z - z, 2));
	}
};

class Vector4
{
public:
	float x, y, w ,h;
public:
	Vector4() :x(0.f), y(0.f), w(0.f), h(0.f) {}
	Vector4(float x_, float y_, float w_, float h_) :x(x_), y(y_), w(w_) ,h(h_) {}
	Vector4 operator+(Vector4 d);
	Vector4 operator-(Vector4 d);
	Vector4 operator*(Vector4 d);
	Vector4 operator*(float d);
	Vector4 operator/(float d);
	
	bool operator==(Vector4 Vector4_)
	{
		return x == Vector4_.x && y == Vector4_.y && w == Vector4_.w && h == Vector4_.h;
	}
	bool operator!=(Vector4 Vector4_)
	{
		return x != Vector4_.x || y != Vector4_.y || w != Vector4_.w || h != Vector4_.h;
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(w, 2) + powf(h, 2));
	}
	float DistanceTo(const Vector4& Pos)
	{
		return sqrtf(powf(Pos.x - x, 2) + powf(Pos.y - y, 2) + powf(Pos.w - w, 2) + powf(Pos.h - h, 2));
	}
};