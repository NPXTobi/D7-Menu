/*
*   This file is part of Universal-Core-Example
*   Copyright (C) 2020 SuperSaiyajinStackie
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

// Screens.
#include <m3dia.hpp>

#include "mainMenu.hpp"
#include "gameManagement.hpp"
#include "titleManagement.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "gamecard.hpp"
#include "nand.hpp"
#include "sdmenuv2.hpp"


#include "msg.hpp"


#include <unistd.h>
#include <iostream>

extern bool touching(touchPosition touch, Structs::ButtonPos button);
extern bool exiting;


MainMenu::MainMenu() {
	Msg::DisplayMsg("Scanning SD Card...");
	GameManagement::scanTitleID();
	maxTitles = (int)GameManagement::installedTitles.size();
}

void MainMenu::Draw(void) const {
	
	GFX::DrawTop();
	GFX::DrawBetteryTop();
	Gui::DrawString(0, 2 , 0.8f, WHITE, timeStr());
	Gui::Draw_Rect(10, 50, 380, 100, C2D_Color32(130, 130, 130, 255));
	Gui::DrawStringCentered(0, 75, 0.7f, BLACK, GameManagement::installedTitles[selectedTitle]->name());
	Gui::DrawStringCentered(0, 105, 0.7f, BLACK, GameManagement::installedTitles[selectedTitle]->Author());
	Gui::DrawStringCentered(0, 2, 0.8f, WHITE, "D7-Menu", 400);
	Gui::DrawString(397-Gui::GetStringWidth(0.8f, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles)), 237-Gui::GetStringHeight(0.8f, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles)), 0.8f, WHITE, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles));
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/
	
	
	


	GFX::DrawBottom();
	Gui::Draw_Rect(15, 40, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(75, 40, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(135, 40, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(195, 40, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(255, 40, 48, 48, C2D_Color32(160, 160, 160, 255));



	

	

	for(int i=0;i<ENTRIES_PER_SCREEN && i<maxTitles;i++) {
		if(screenPos + i == selection) {
			Gui::Draw_Rect(15 +(i*60)-1, 40-1, 50, 50, C2D_Color32(0, 200, 0, 255));
		}
	
		
		
		C2D_DrawImageAt(GameManagement::installedTitles[screenPos+i]->icon(), 15 +(i*60), 40, 0.5f); 
		// Installed Title Icon.
	}

	
	

	Gui::DrawString(37, 214, 0.8f, WHITE, "Hold \uE046 to show controols!");
	// Draw Buttons. ;P

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect

}


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	// Press Start to exit the app.
//	m3d::Music music("sdmc:/bgm.mp3");
//
//    // enable looping
//    music.loop(true);
//
//    // start the playback
//    music.play();


	if (hDown & KEY_START) {
		fadecolor = 0;
		fadeout = true;
		exiting = true;
	}
	if (hHeld & KEY_SELECT){
		GFX::DrawTop();
		Gui::DrawString(1, 30, 0.8f, WHITE, "\uE000: Start");
		Gui::DrawString(1, 60, 0.8f, WHITE, "\uE07B / \uE07C: Navigate");
		Gui::DrawString(1, 90, 0.8f, WHITE, "\uE07B / \uE07C(CirclePad): Navigate Fast!");
		Gui::DrawString(1, 120, 0.8f, WHITE, "Hold \uE052 to Show nand titles.");
		Gui::DrawString(1, 150, 0.8f, WHITE, "Press \uE053 to go to GameCardMenu");

		Gui::DrawString(1, 180, 0.8f, WHITE, "Press \uE045 to exit!");
	}
	if (hDown & KEY_L){

		Gui::setScreen(std::make_unique<SDMenu>(), true, false);
		
		
	}
	if (hDown & KEY_R){
			Gui::setScreen(std::make_unique<gamecard>(), true, false);
	}
	if (hHeld & KEY_CPAD_RIGHT)
		{
			if (selectedTitle == (int)GameManagement::installedTitles.size() - 1 || selectedTitle == maxTitles - 1)
			{
				if ((int)GameManagement::installedTitles.size() > maxTitles && selectedTitle > maxTitles - 1)
				{
					if (selectedTitle > maxTitles - 1)
					{
						selectedTitle = maxTitles;
						selection = maxTitles;
					}
					else if (selectedTitle == maxTitles - 1)
					{
						selectedTitle = 0;
						selection = 0;
					}
				}
				else
				{
					selectedTitle = 0;
					selection = 0;
				}
			}
			else
			{
				selectedTitle++;
				selection++;
			}
		}
		if (hDown & KEY_DRIGHT)
		{
			if (selectedTitle == (int)GameManagement::installedTitles.size() - 1 || selectedTitle == maxTitles - 1)
			{
				if ((int)GameManagement::installedTitles.size() > maxTitles && selectedTitle > maxTitles - 1)
				{
					if (selectedTitle > maxTitles - 1)
					{
						selectedTitle = maxTitles;
						selection = maxTitles;
					}
					else if (selectedTitle == maxTitles - 1)
					{
						selectedTitle = 0;
						selection = 0;
					}
				}
				else
				{
					selectedTitle = 0;
					selection = 0;
				}
			}
			else
			{
				selectedTitle++;
				selection++;
			}
		}

	// Scroll with D-Pad Left to the last available Title.
		if (hHeld & KEY_CPAD_LEFT)
		{
			if (selectedTitle == -1)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() < maxTitles ? GameManagement::installedTitles.size() - 1 : maxTitles - 1;
				selection = (int)GameManagement::installedTitles.size() < maxTitles ? GameManagement::installedTitles.size() - 1 : maxTitles - 1;
			}
			else if (selectedTitle == maxTitles)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() - 1;
				selection = (int)GameManagement::installedTitles.size() - 1;
			}
			else if (selectedTitle == 0)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() > maxTitles ? maxTitles - 1 : (int)GameManagement::installedTitles.size() - 1;
				selection = (int)GameManagement::installedTitles.size() > maxTitles ? maxTitles - 1 : (int)GameManagement::installedTitles.size() - 1;
			}
			else
			{
				selectedTitle--;
				selection--;
			}
		}
		if (hDown & KEY_DLEFT)
		{
			if (selectedTitle == -1)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() < maxTitles ? GameManagement::installedTitles.size() - 1 : maxTitles - 1;
				selection = (int)GameManagement::installedTitles.size() < maxTitles ? GameManagement::installedTitles.size() - 1 : maxTitles - 1;
			}
			else if (selectedTitle == maxTitles)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() - 1;
				selection = (int)GameManagement::installedTitles.size() - 1;
			}
			else if (selectedTitle == 0)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() > maxTitles ? maxTitles - 1 : (int)GameManagement::installedTitles.size() - 1;
				selection = (int)GameManagement::installedTitles.size() > maxTitles ? maxTitles - 1 : (int)GameManagement::installedTitles.size() - 1;
			}
			else
			{
				selectedTitle--;
				selection--;
			}
		}
		// Launch the Title with <A>.
		if (hDown & KEY_A) {
			if (!GameManagement::installedTitles.empty()) {
				u8 param[0x300];
				u8 hmac[0x20];
				memset(param, 0, sizeof(param));
				memset(hmac, 0, sizeof(hmac));
				APT_PrepareToDoApplicationJump(0, GameManagement::installedTitles[selectedTitle]->ID(), MEDIATYPE_SD);
				APT_DoApplicationJump(param, sizeof(param), hmac);
			}
		}
	
	if(selection < screenPos) {
		screenPos = selection;
	} 
	if (selection > screenPos + ENTRIES_PER_SCREEN - 1) {
		screenPos = selection - ENTRIES_PER_SCREEN + 1;
	}

	

	// Press Down to go one entry down. - 1 -> Because we don't want to go one Entry after the actual Buttons.
	
}
