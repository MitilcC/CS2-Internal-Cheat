#pragma once

#define _USE_MATH_DEFINES

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "Address.h"
#include "LocalPlayer.h"
#include "Entity.h"
#include "menu.h"
#include "Ults.h"
#include <vector>
#include <bitset>
#include "Console.h"
#include "Bone.h"
#include "math.h"
#include <tuple>
namespace Misc
{
	bool GetRadarTarget();
	bool Start();
};

class Base_Radar
{
public:
	// 设置雷达数据
	void SetSize(const float& Size);
	void SetPos(const Vector2& Pos);
	void SetRange(const float& Range);
	void SetCrossColor(const ImColor& Color);
	void SetProportion(const float& Proportion);
	void SetDrawList(ImDrawList* DrawList);
	void AddPoint(const Vector3& LocalPos, const float& LocalYaw, const Vector3& Pos, ImColor Color, float Yaw);
	// 获取雷达数据
	float GetSize();
	Vector2 GetPos();
	// 渲染
	void Render();
public:
	ImDrawList* DrawList = nullptr;
	// 十字显示
	bool ShowCrossLine = true;
	// 十字颜色
	ImColor CrossColor = ImColor(255, 255, 255, 255);
	// 比例
	float Proportion = 2680;
	// 圆点半径
	float CircleSize = 4;
	// 箭头尺寸
	float ArrowSize = 11;
	// 圆弧箭头尺寸
	float ArcArrowSize = 7;
	// 雷达范围
	float RenderRange = 250;
	// 本地Yaw数据
	float LocalYaw = 0.0f;
	// 状态
	bool Opened = true;
	// 雷达绘制类型 0:圆形 1:箭头 2:圆弧箭头
	int  PointType = 0;
private:
	Vector2  Pos{ 0,0 };
	float Width = 200;
	std::vector<std::tuple<Vector2, ImColor, int, float>> Points;
};