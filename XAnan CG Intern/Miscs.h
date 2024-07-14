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
class Base_Radar
{
public:
	// �����״�����
	void SetSize(const float& Size);
	void SetPos(const Vector2& Pos);
	void SetRange(const float& Range);
	void SetCrossColor(const ImColor& Color);
	void SetProportion(const float& Proportion);
	void SetDrawList(ImDrawList* DrawList);
	void AddPoint(const Vector3& LocalPos, const float& LocalYaw, const Vector3& Pos, ImColor Color, float Yaw);
	// ��ȡ�״�����
	float GetSize();
	Vector2 GetPos();
	// ��Ⱦ
	void Render();
public:
	ImDrawList* DrawList = nullptr;
	// ʮ����ʾ
	bool ShowCrossLine = true;
	// ʮ����ɫ
	ImColor CrossColor = ImColor(255, 255, 255, 255);
	// ����
	float Proportion = 2680;
	// Բ��뾶
	float CircleSize = 4;
	// ��ͷ�ߴ�
	float ArrowSize = 11;
	// Բ����ͷ�ߴ�
	float ArcArrowSize = 7;
	// �״ﷶΧ
	float RenderRange = 250;
	// ����Yaw����
	float LocalYaw = 0.0f;
	// ״̬
	bool Opened = true;
	// �״�������� 0:Բ�� 1:��ͷ 2:Բ����ͷ
	int  PointType = 0;
private:
	Vector2  Pos{ 0,0 };
	float Width = 200;
	std::vector<std::tuple<Vector2, ImColor, int, float>> Points;
};

namespace Misc
{
	void RadarSetting(Base_Radar& Radar);
	bool Start();
};

