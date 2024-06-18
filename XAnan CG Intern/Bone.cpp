#include "Bone.h"

void Bone::HeadCricle(intptr_t pawn, ImColor Color) 
{
	Vector3 drawhead;
	Vector3 drawneck;

	if (!Utils::WorldToScreen(Get::BonePos(pawn, BoneIndex::head), drawhead, Address::GetViewMatrixPtr(), Get::WindowSize().x, Get::WindowSize().y))
		return;

	if (!Utils::WorldToScreen(Get::BonePos(pawn, BoneIndex::neck_0), drawneck, Address::GetViewMatrixPtr(), Get::WindowSize().x, Get::WindowSize().y))
		return;

	float radius = Math::distance(drawhead.x-drawneck.x,drawhead.y-drawneck.y);

	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(drawhead.x, drawhead.y), radius, Color);

}

void Bone::DrawLine(std::vector<Vector3> list , ImColor Color) 
{
	Vector3 drawpos;
	std::vector<Vector3>Drawlist{};
	for (int i = 0 ; i < list.size(); ++i)
	{
		
		if (!Utils::WorldToScreen(list[i], drawpos, Address::GetViewMatrixPtr(), Get::WindowSize().x, Get::WindowSize().y))
			continue;

		Drawlist.push_back(drawpos);

	}

	for (int i = 0; i < Drawlist.size() - 1; ++i)
	{
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Drawlist[i].x, Drawlist[i].y), ImVec2(Drawlist[i + 1].x, Drawlist[i + 1].y), Color);
	}
}

void Bone::Start(intptr_t pawn, ImColor BoneColor)
{

	Bone::BoneDrawList.clear();
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::neck_0));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::spine_2));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::pelvis));
    DrawLine(Bone::BoneDrawList, BoneColor);

	Bone::BoneDrawList.clear();
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::neck_0));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::arm_upper_L));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::arm_lower_L));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::hand_L));
	DrawLine(Bone::BoneDrawList, BoneColor);

	Bone::BoneDrawList.clear();
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::neck_0));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::arm_upper_R));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::arm_lower_R));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::hand_R));
	DrawLine(Bone::BoneDrawList, BoneColor);

	Bone::BoneDrawList.clear();
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::pelvis));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::leg_upper_L));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::leg_lower_L));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::ankle_L));
	DrawLine(Bone::BoneDrawList, BoneColor);

	Bone::BoneDrawList.clear();
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::pelvis));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::leg_upper_R));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::leg_lower_R));
	Bone::BoneDrawList.push_back(Get::BonePos(pawn, BoneIndex::ankle_R));
	DrawLine(Bone::BoneDrawList, BoneColor);
}