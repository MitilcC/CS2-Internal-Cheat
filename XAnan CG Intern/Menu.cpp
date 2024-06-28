#include "menu.h"
#include <string>


void Menu::start() 
{

	ImGui::SetNextWindowSize(ImVec2(855 * dpi_scale, 790 * dpi_scale));
	ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
	{
		ImGuiStyle& s = ImGui::GetStyle();

		s.Colors[ImGuiCol_WindowBg] = ImColor(60, 65, 80, 60);
		s.Colors[ImGuiCol_ChildBg] = ImColor(20, 20, 20, 255);
		s.Colors[ImGuiCol_PopupBg] = ImColor(26, 26, 26, 255);
		s.Colors[ImGuiCol_Text] = ImColor(120, 120, 120, 255);
		s.Colors[ImGuiCol_TextDisabled] = ImColor(100, 100, 100, 255);
		s.Colors[ImGuiCol_Border] = ImColor(28, 28, 28, 255);
		s.Colors[ImGuiCol_TextSelectedBg] = ImColor(25, 22, 33, 100);

		s.Colors[ImGuiCol_ScrollbarGrab] = ImColor(24, 24, 24, 255);
		s.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(24, 24, 24, 255);
		s.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);

		s.WindowBorderSize = 0;
		s.WindowPadding = ImVec2(0, 0);
		s.WindowRounding = 5.f;
		s.PopupBorderSize = 0.f;
		s.PopupRounding = 5.f;
		s.ChildRounding = 7;
		s.ChildBorderSize = 1.f;
		s.FrameBorderSize = 1.0f;
		s.ScrollbarSize = 3.0f;
		s.FrameRounding = 5.f;
		s.ItemSpacing = ImVec2(0, 20);
		s.ItemInnerSpacing = ImVec2(10, 0);

		const auto& p = ImGui::GetWindowPos();


		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
		ImGui::BeginChild("G-Tab", ImVec2(173 * dpi_scale, 790 * dpi_scale), false);
		{
			ImGui::GetForegroundDrawList()->AddText(tab_text3, 35 * dpi_scale, ImVec2(16 * dpi_scale + p.x, 12 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "XAnanCG2");
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(273 * dpi_scale + p.x, 790 * dpi_scale + p.y), ImGui::GetColorU32(colors::Tab_Child), s.WindowRounding);

			ImGui::SetCursorPosY(60);

			ImGui::SetWindowFontScale(dpi_scale);
			if (ImGui::Tab("H", "Aimbot", "Auto Aim Function", 0 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 0;
			if (ImGui::Tab("G", "Changer", "Inventory & Profile", 1 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale)))Gui::tabs = 1;
			if (ImGui::Tab("F", "Visuals", "Show Player Esp", 2 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 2;
			if (ImGui::Tab("E", "Misc", "Other settings", 3 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 3;
			if (ImGui::Tab("B", "Config", "Manage your configs", 6 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 4;

		}ImGui::EndChild();


		ImGui::PopStyleColor();

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(855 * dpi_scale + p.x, 790 * dpi_scale + p.y), ImGui::GetColorU32(colors::main_color), s.WindowRounding);

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 755 * dpi_scale + p.y), ImVec2(855 * dpi_scale + p.x, 755 * dpi_scale + p.y), ImGui::GetColorU32(colors::lite_color), s.WindowRounding);

		//   ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(705 + p.x, 60 + p.y), ImGui::GetColorU32(colors::lite_color), s.WindowRounding);


		ImGui::GetForegroundDrawList()->AddText(tab_text3, 16 * dpi_scale, ImVec2(10 * dpi_scale + p.x, 765 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Uid:0001");
		ImGui::GetForegroundDrawList()->AddText(tab_text3, 16 * dpi_scale, ImVec2(790 * dpi_scale + p.x, 765 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Release");
		Gui::tab_alpha = ImClamp(Gui::tab_alpha + (7.f * ImGui::GetIO().DeltaTime * (Gui::tabs == Gui::active_tab ? 1.f : -1.f)), 0.f, 1.f);
		Gui::tab_add = ImClamp(Gui::tab_add + (std::round(50.f) * ImGui::GetIO().DeltaTime * (Gui::tabs == Gui::active_tab ? 1.f : -1.f)), 0.f, 1.f);

		if (Gui::tab_alpha == 0.f && Gui::tab_add == 0.f) Gui::active_tab = Gui::tabs;


		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Gui::tab_alpha * s.Alpha);

		ImGui::SetCursorPos(ImVec2(203 * dpi_scale, 30 * dpi_scale));

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
		ImGui::BeginChild("General", ImVec2(717 * dpi_scale, 720 * dpi_scale), false);
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetColorU32(colors::lite_color));
			switch (Gui::active_tab) 
			{
            //Aimbot
			case 0:
			{

				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(tab_text3, 26 * dpi_scale, ImVec2(475 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Aimbot");
					ImGui::GetForegroundDrawList()->AddText(tab_text3, 16 * dpi_scale, ImVec2(405 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Help you to kill emery more easy");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				ImGui::BeginChildPos("AimBot", ImVec2(300 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::SetWindowFontScale(dpi_scale);
					ImGui::Checkbox("AimBot", &Menu::bAimBot);

					ImGui::Keybind("Aim Bind", &Menu::Aimbot::AimKey, true);

					float FovMin = 0.1f, FovMax = 89.f;
					float SmoothMin = 0.f, SmoothMax = 0.9f;
					//ImGui::SliderFloat("Aim Fov", &AimControl::AimFov, FovMin, FovMax, "%.1f", ImGuiSliderFlags_None);



					//ImGui::SliderFloat("Smooth", &AimControl::Smooth, SmoothMin, SmoothMax, "%.1f", ImGuiSliderFlags_None);

					//int BulletMin = 0, BulletMax = 6;
					//float RecoilMin = 0.f, RecoilMax = 2.f;
					//ImGui::SliderInt("Start Bullet", &AimControl::RCSBullet, BulletMin, BulletMax, "%d", ImGuiSliderFlags_None);
					//ImGui::SliderFloat("RCS Yaw", &AimControl::RCSScale.x, RecoilMin, RecoilMax, "%.1f", ImGuiSliderFlags_None);
					//ImGui::SliderFloat("RCS Pitch", &AimControl::RCSScale.y, RecoilMin, RecoilMax, "%.1f", ImGuiSliderFlags_None);




				}
				ImGui::EndChild();
				ImGui::SetCursorPos(ImVec2(320 * dpi_scale, 120 * dpi_scale));
				ImGui::BeginChildPos("Misc", ImVec2(300 * dpi_scale, 580 * dpi_scale));
				{

					ImGui::SetWindowFontScale(dpi_scale);
					//ImGui::Checkbox("TriggerBot", &MenuConfig::TriggerBot);
					//ImGui::Keybind("Trigger Key", &MenuConfig::TriggerHotKey, true);
					//if (ImGui::Combo("TriggerMode", &MenuConfig::TriggerMode, "Hold\0Toggle"))
					//{
					//}
					//ImGui::Keybind("Trigger Mode", &MenuConfig::TriggerMode, true);


					//ImGui::Checkbox("Visible Check", &MenuConfig::VisibleCheck);
					//ImGui::Checkbox("FovCircle", &MenuConfig::ShowAimFovRange);


					//DWORD TriggerDelayMin = 15, TriggerDelayMax = 170;
					//ImGui::SliderInt("Delay", &TriggerBot::TriggerDelay, TriggerDelayMin, TriggerDelayMax, "%d", ImGuiSliderFlags_None);

					/*
					if (ImGui::Combo("Hitbox", &MenuConfig::AimPosition, "Head\0Neck\0Spine"))
					{
						switch (MenuConfig::AimPosition)
						{
						case 0:
							MenuConfig::AimPositionIndex = BONEINDEX::head;
							break;
						case 1:
							MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
							break;
						case 2:
							MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
							break;
						default:
							break;
						}
					}
					*/

					//ImGui::ColorEdit4("Fov Circle##FovCircleColor", reinterpret_cast<float*>(&MenuConfig::AimFovRangeColor), ImGuiColorEditFlags_NoInputs);
				}
				ImGui::EndChild();

			}
			      break;
			//SkinChanger
			case 1: 
			{
			
			}
			      break;
			//Visual
			case 2: {
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(tab_text3, 26 * dpi_scale, ImVec2(475 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Visuals");
					ImGui::GetForegroundDrawList()->AddText(tab_text3, 16 * dpi_scale, ImVec2(425 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Painting on Object Overlay");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				ImGui::BeginChildPos("Esp", ImVec2(300 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::SetWindowFontScale(dpi_scale);

					ImGui::Checkbox("BoxESP", &Menu::ESP::Box);

					ImGui::Combo("BoxType", &Menu::ESP::BoxType, "Rect\0Filled");

					ImGui::Checkbox("HealthBar", &Menu::ESP::Health);

					ImGui::Checkbox("BoneESP", &Menu::ESP::Bone);

					ImGui::Checkbox("Glow", &Menu::ESP::Glow);

					ImGui::Checkbox("HeadCricle", &Menu::ESP::HeadCricle);

					ImGui::Checkbox("PlayerName", &Menu::ESP::Name);

					ImGui::Checkbox("LineToEnemy", &Menu::ESP::Line);

					ImGui::Combo("LineType", &Menu::ESP::LineType, "Button\0Top");

					ImGui::Checkbox("AimCricle", &Menu::ESP::AimCricle);

					ImGui::Combo("CricleType", &Menu::ESP::CricleType, "Emerey\0Screen");



				}
				ImGui::EndChild();
				ImGui::SetCursorPos(ImVec2(320 * dpi_scale, 120 * dpi_scale));
				ImGui::BeginChildPos("Color", ImVec2(300 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::SetWindowFontScale(dpi_scale);

					if(Menu::ESP::BoxType == 0)
						ImGui::ColorEdit4("Box Color##BoxColor", reinterpret_cast<float*>(&Menu::Color::BoxColor), ImGuiColorEditFlags_NoInputs);
					else
						ImGui::ColorEdit4("Filled Color##FilledColor", reinterpret_cast<float*>(&Menu::Color::FilledColor), ImGuiColorEditFlags_NoInputs);

					ImGui::ColorEdit4("Bone Color##BoneColor", reinterpret_cast<float*>(&Menu::Color::BoneColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("HeadCricle Color##HeadCricleColor", reinterpret_cast<float*>(&Menu::Color::HeadCricleColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Eye Ray Color##EyeRay", reinterpret_cast<float*>(&Menu::Color::EyeRayColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Name Color Color##Name", reinterpret_cast<float*>(&Menu::Color::NameColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Line to enemy Color##LineToEnemyColor", reinterpret_cast<float*>(&Menu::Color::LineColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("AimCricle Color##AimCricle", reinterpret_cast<float*>(&Menu::Color::AimCricleColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Health Color##Health", reinterpret_cast<float*>(&Menu::Color::HealthColor), ImGuiColorEditFlags_NoInputs);

				}
				ImGui::EndChild();
			}
				  break;
			//Misc
			case 3: {
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(tab_text3, 26 * dpi_scale, ImVec2(450 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Miscellaneous");
					ImGui::GetForegroundDrawList()->AddText(tab_text3, 16 * dpi_scale, ImVec2(390 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Modify menu games and other functions");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				ImGui::BeginChildPos("Misc", ImVec2(620 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::SetWindowFontScale(dpi_scale);

					//ImGui::Checkbox("RadarHack", &Menu::Misc::Radar);
					//if (Menu::Misc::Radar)
					//{to be finish
						ImGui::Checkbox("Ingame Radar", &Menu::Misc::IngameRadar);
					//}

				}
				ImGui::EndChild();
			}
			      break;
			//Comfig
			case 4:
			{
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 400 * dpi_scale));
				{
					ImGui::SetWindowFontScale(dpi_scale);

				}
				ImGui::EndChild();
			}
			      break;
			}
			ImGui::PopStyleColor(1);

			ImGui::Spacing();

			ImGui::EndChild();

			ImGui::PopStyleColor(1);
		}
		//if (animated_background)
			//Particles();
		ImGui::PopStyleVar(1);

	}
	ImGui::End();
}
