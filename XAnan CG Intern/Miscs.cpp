#include "Miscs.h"

Vector2 RevolveCoordinatesSystem(float RevolveAngle, Vector2 OriginPos, Vector2 DestPos)
{
	Vector2 ResultPos;
	if (RevolveAngle == 0)
		return DestPos;
	ResultPos.x = OriginPos.x + (DestPos.x - OriginPos.x) * cos(RevolveAngle * M_PI / 180) + (DestPos.y - OriginPos.y) * sin(RevolveAngle * M_PI / 180);
	ResultPos.y = OriginPos.y - (DestPos.x - OriginPos.x) * sin(RevolveAngle * M_PI / 180) + (DestPos.y - OriginPos.y) * cos(RevolveAngle * M_PI / 180);
	return ResultPos;
}


void Base_Radar::SetRange(const float& Range)
{
	this->RenderRange = Range;
}

void Base_Radar::SetCrossColor(const ImColor& Color)
{
	this->CrossColor = Color;
}

void Base_Radar::SetPos(const Vector2& Pos)
{
	this->Pos = Pos;
}

void Base_Radar::SetSize(const float& Size)
{
	this->Width = Size;
}

float Base_Radar::GetSize()
{
	return this->Width;
}

Vector2 Base_Radar::GetPos()
{
	return this->Pos;
}

void Base_Radar::SetProportion(const float& Proportion)
{
	this->Proportion = Proportion;
}

void Base_Radar::SetDrawList(ImDrawList* DrawList)
{
	this->DrawList = DrawList;
}

void Base_Radar::AddPoint(const Vector3& LocalPos, const float& LocalYaw, const Vector3& Pos, ImColor Color, float Yaw)
{
	Vector2 PointPos;
	float Distance;
	float Angle;

	this->LocalYaw = LocalYaw;

	Distance = sqrt(pow(LocalPos.x - Pos.x, 2) + pow(LocalPos.y - Pos.y, 2));

	Angle = atan2(Pos.y - LocalPos.y, Pos.x - LocalPos.x) * 180 / M_PI;
	Angle = (this->LocalYaw - Angle) * M_PI / 180;

	Distance = Distance / this->Proportion * this->RenderRange * 2;

	PointPos.x = this->Pos.x + Distance * sin(Angle);
	PointPos.y = this->Pos.y - Distance * cos(Angle);

	// Circle range
	//Distance = sqrt(pow(this->Pos.x - PointPos.x, 2) + pow(this->Pos.y - PointPos.y, 2));
	//if (Distance > this->RenderRange)
	//	return;

	// Rectangle range
	if (PointPos.x < this->Pos.x - RenderRange || PointPos.x > this->Pos.x + RenderRange
		|| PointPos.y > this->Pos.y + RenderRange || PointPos.y < this->Pos.y - RenderRange)
		return;

	std::tuple<Vector2, ImColor, int, float> Data(PointPos, Color, 2, Yaw);
	this->Points.push_back(Data);
}

void DrawTriangle(Vector2 Center, ImColor Color, float Width, float Height, float Yaw)
{
	Vector2 a, b, c;
	Vector2 Re_a, Re_b, Re_c;
	a = Vector2{ Center.x - Width / 2,Center.y };
	b = Vector2{ Center.x + Width / 2,Center.y };
	c = Vector2{ Center.x,Center.y - Height };
	a = RevolveCoordinatesSystem(-Yaw, Center, a);
	b = RevolveCoordinatesSystem(-Yaw, Center, b);
	c = RevolveCoordinatesSystem(-Yaw, Center, c);
	ImGui::GetForegroundDrawList()->AddTriangleFilled(
		ImVec2(a.x, a.y),
		ImVec2(b.x, b.y),
		ImVec2(c.x, c.y),
		Color);
}
Base_Radar Radar;

void Misc::RadarSetting(Base_Radar& Radar)
{
	ImGui::SetNextWindowBgAlpha(Menu::Misc::RadarBgAlpha);
	ImGui::Begin(("Radar"), 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({ Menu::Misc::RadarRange * 2,Menu::Misc::RadarRange * 2 });
	if (!Menu::Misc::customRadar)
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		Menu::Misc::ShowRadarCrossLine = false;
		Menu::Misc::Proportion = 3300.f;
		Menu::Misc::RadarPointSizeProportion = 1.f;
		Menu::Misc::RadarRange = 150.f;
		Menu::Misc::RadarBgAlpha = 0.1f;
		Menu::Misc::RadarCrossLineColor = ImColor(200, 200, 200, 255);
	}


	// Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetDrawList(ImGui::GetWindowDrawList());
	Radar.SetPos({ ImGui::GetWindowPos().x + Menu::Misc::RadarRange, ImGui::GetWindowPos().y + Menu::Misc::RadarRange });
	Radar.SetProportion(Menu::Misc::Proportion);
	Radar.SetRange(Menu::Misc::RadarRange);
	Radar.SetSize(Menu::Misc::RadarRange * 2);
	Radar.SetCrossColor(Menu::Misc::RadarCrossLineColor);

	Radar.ArcArrowSize *= Menu::Misc::RadarPointSizeProportion;
	Radar.ArrowSize *= Menu::Misc::RadarPointSizeProportion;
	Radar.CircleSize *= Menu::Misc::RadarPointSizeProportion;

	Radar.ShowCrossLine = Menu::Misc::ShowRadarCrossLine;
	Radar.Opened = true;
}
void Base_Radar::Render()
{


	if (Width <= 0)
		return;

	// Cross
	std::pair<Vector2, Vector2> Line1;
	std::pair<Vector2, Vector2> Line2;

	Line1.first = Vector2(this->Pos.x - this->Width / 2, this->Pos.y);
	Line1.second = Vector2(this->Pos.x + this->Width / 2, this->Pos.y);
	Line2.first = Vector2(this->Pos.x, this->Pos.y - this->Width / 2);
	Line2.second = Vector2(this->Pos.x, this->Pos.y + this->Width / 2);

	if (this->Opened)
	{
		if (this->ShowCrossLine)
		{
			this->DrawList->AddLine(Line1.first.ToImVec2(), Line1.second.ToImVec2(), this->CrossColor, 1);
			this->DrawList->AddLine(Line2.first.ToImVec2(), Line2.second.ToImVec2(), this->CrossColor, 1);
		}

		for (auto PointSingle : this->Points)
		{
			Vector2	PointPos = std::get<0>(PointSingle);
			ImColor PointColor = std::get<1>(PointSingle);
			int		PointType = std::get<2>(PointSingle);
			float	PointYaw = std::get<3>(PointSingle);
			if (PointType == 0)
			{
				// 埴倛欴宒
				this->DrawList->AddCircle(PointPos.ToImVec2(), this->CircleSize, PointColor);
				this->DrawList->AddCircleFilled(PointPos.ToImVec2(), this->CircleSize, ImColor(0, 0, 0));
			}
			else if (PointType == 1)
			{
				// 璋芛欴宒
				Vector2 a, b, c;
				Vector2 Re_a, Re_b, Re_c;
				Vector2 Re_Point;
				float Angle = (this->LocalYaw - PointYaw) + 180;
				Re_Point = RevolveCoordinatesSystem(Angle, this->Pos, PointPos);

				Re_a = Vector2(Re_Point.x, Re_Point.y + this->ArrowSize);
				Re_b = Vector2(Re_Point.x - this->ArrowSize / 1.5, Re_Point.y - this->ArrowSize / 2);
				Re_c = Vector2(Re_Point.x + this->ArrowSize / 1.5, Re_Point.y - this->ArrowSize / 2);

				a = RevolveCoordinatesSystem(-Angle, this->Pos, Re_a);
				b = RevolveCoordinatesSystem(-Angle, this->Pos, Re_b);
				c = RevolveCoordinatesSystem(-Angle, this->Pos, Re_c);

				this->DrawList->AddQuadFilled(
					ImVec2(a.x, a.y),
					ImVec2(b.x, b.y),
					ImVec2(PointPos.x, PointPos.y),
					ImVec2(c.x, c.y),
					PointColor
				);
				this->DrawList->AddQuad(
					ImVec2(a.x, a.y),
					ImVec2(b.x, b.y),
					ImVec2(PointPos.x, PointPos.y),
					ImVec2(c.x, c.y),
					ImColor(0, 0, 0, 150),
					0.1
				);
			}
			else
			{
				// 埴說璋芛
				ImVec2 TrianglePoint, TrianglePoint_1, TrianglePoint_2;
				float Angle = (this->LocalYaw - PointYaw) - 90;

				this->DrawList->AddCircleFilled(PointPos.ToImVec2(), 0.85 * this->ArcArrowSize, PointColor, 30);
				this->DrawList->AddCircle(PointPos.ToImVec2(), 0.95 * this->ArcArrowSize, ImColor(0, 0, 0, 150), 0, 0.1);

				TrianglePoint.x = PointPos.x + (this->ArcArrowSize + this->ArcArrowSize / 3) * cos(-Angle * M_PI / 180);
				TrianglePoint.y = PointPos.y - (this->ArcArrowSize + this->ArcArrowSize / 3) * sin(-Angle * M_PI / 180);

				TrianglePoint_1.x = PointPos.x + this->ArcArrowSize * cos(-(Angle - 30) * M_PI / 180);
				TrianglePoint_1.y = PointPos.y - this->ArcArrowSize * sin(-(Angle - 30) * M_PI / 180);

				TrianglePoint_2.x = PointPos.x + this->ArcArrowSize * cos(-(Angle + 30) * M_PI / 180);
				TrianglePoint_2.y = PointPos.y - this->ArcArrowSize * sin(-(Angle + 30) * M_PI / 180);

				this->DrawList->PathLineTo(TrianglePoint);
				this->DrawList->PathLineTo(TrianglePoint_1);
				this->DrawList->PathLineTo(TrianglePoint_2);
				this->DrawList->PathFillConvex(ImColor(220, 220, 220, 240));
			}
		}
	}

	if (this->Points.size() > 0)
		this->Points.clear();
	ImGui::End();
}

bool Misc::Start()
{
	// Radar Data
	Base_Radar Radar;
	Misc::RadarSetting(Radar);

	Player LocalPlayer{};

	LocalPlayer.control = Address::GetLocalPlayerControl();

	LocalPlayer.pawn = Get::PlayerPawnAddress(LocalPlayer.control);

	LocalPlayer.team = Get::PlayerTeam(LocalPlayer.pawn);

	//if (!Get::PlayerAlive(LocalPlayer.pawn))
	//{
		//return false;
	//}

	for (int i{ 0 }; i < 64; ++i)
	{

		Player Entity{};

		Entity.control = Address::GetEntityBase(i);

		if (!Get::PawnAlive(Entity.control))
		{
			continue;
		}

		Entity.pawn = Get::PlayerPawnAddress(Entity.control);

		Entity.team = Get::PlayerTeam(Entity.pawn);

		Entity.health = Get::PlayerHealth(Entity.pawn);

		if (Get::IsDormant(Entity.pawn))
		{
			continue;
		}

		if (Menu::TeamCheck && Entity.team == LocalPlayer.team)
		{
			continue;
		}

		if (Entity.team != 2 && Entity.team != 3)
		{
			continue;
		}

		if (!Get::PlayerAlive(Entity.pawn))
		{
			continue;
		}
		if (Menu::Misc::IngameRadar)
		{
			Set::RadarHack(Entity.pawn);
			continue;
		}

		if (Menu::Misc::Radar) {
			Vector3 LocalPos = Get::PlayerPos(LocalPlayer.pawn);
			Vector3 TargetPos = Get::PlayerPos(Entity.pawn);
			Radar.AddPoint(LocalPos, LocalPlayer::GetViewAngles().y, TargetPos, ImColor(237, 85, 106, 200), Get::ViewAngles(Entity.pawn).y);
		}
		Vector3 Window = Get::WindowSize();


	}
	Radar.Render();
	return true;
}
