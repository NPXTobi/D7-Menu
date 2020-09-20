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

#include "common.hpp"
#include "msg.hpp"
#include "ptmu_x.h"
#include <citro2d.h>
#include <3ds.h>



extern u32 progressBar, selected;
extern ProgressBar progressbarType;



// Draws a Rectangle as the progressbar.
void UI::DrawProgressBar(u64 currentProgress, u64 totalProgress) {
	GFX::DrawTop();
		// Outline of progressbar.
		Gui::Draw_Rect(30, 120, 340, 30, BLACK);
		Gui::Draw_Rect(31, 121, (int)(((float)currentProgress / (float)totalProgress) * 338.0f), 28, WHITE);
	
}


extern C2D_SpriteSheet sprites; // Include the spritesheet extern.

void GFX::DrawTop(void) {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 30, C2D_Color32(0, 160, 160, 255));
	Gui::Draw_Rect(0, 30, 400, 180, C2D_Color32(0, 120, 120, 255));
	Gui::Draw_Rect(0, 210, 400, 30, C2D_Color32(0, 160, 160, 255));
}

void GFX::DrawBottom(void) {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 30, C2D_Color32(0, 160, 160, 255));
	Gui::Draw_Rect(0, 30, 320, 180, C2D_Color32(0, 120, 120, 255));
	Gui::Draw_Rect(0, 210, 320, 30, C2D_Color32(0, 160, 160, 255));
}

void GFX::DrawFileBrowseBG(bool isTop) {
	if (isTop == true) {
		Gui::ScreenDraw(Top);
		Gui::Draw_Rect(0, 0, 400, 27, C2D_Color32(0, 160, 210, 255));
		Gui::Draw_Rect(0, 27, 400, 31, C2D_Color32(0, 160, 160, 255));
		Gui::Draw_Rect(0, 58, 400, 31, C2D_Color32(0, 120, 120, 255));
		Gui::Draw_Rect(0, 89, 400, 31, C2D_Color32(0, 160, 160, 255));
		Gui::Draw_Rect(0, 120, 400, 31, C2D_Color32(0, 120, 120, 255));
		Gui::Draw_Rect(0, 151, 400, 31, C2D_Color32(0, 160, 160, 255));
		Gui::Draw_Rect(0, 182, 400, 31, C2D_Color32(0, 120, 120, 255));
		Gui::Draw_Rect(0, 213, 400, 27, C2D_Color32(0, 160, 210, 255));
	} else {
		Gui::ScreenDraw(Bottom);
		Gui::Draw_Rect(0, 0, 320, 27, C2D_Color32(0, 160, 210, 255));
		Gui::Draw_Rect(0, 27, 320, 31, C2D_Color32(0, 160, 160, 255));
		Gui::Draw_Rect(0, 58, 320, 31, C2D_Color32(0, 120, 120, 255));
		Gui::Draw_Rect(0, 89, 320, 31, C2D_Color32(0, 160, 160, 255));
		Gui::Draw_Rect(0, 120, 320, 31, C2D_Color32(0, 120, 120, 255));
		Gui::Draw_Rect(0, 151, 320, 31, C2D_Color32(0, 160, 160, 255));
		Gui::Draw_Rect(0, 182, 320, 31, C2D_Color32(0, 120, 120, 255));
		Gui::Draw_Rect(0, 213, 320, 27, C2D_Color32(0, 160, 210, 255));
	}
}

void GFX::DrawBetteryTop(){
	u8 batteryChargeState = 0;
	u8 batteryPercent;
	mcuGetBatteryLevel(&batteryPercent);
	

	char buf[5];

	snprintf(buf, 5, "%d%%", batteryPercent);
		
		
		Gui::DrawString(300, 2, 0.8f, WHITE, buf);

	// For battery status
 

	if (batteryPercent >= 0 && batteryPercent <= 5) {
		Gui::DrawSprite(sprites, sprites_battery0_idx, 361, 1, 1, 1);
	} else if (batteryPercent >= 6 && batteryPercent <= 10) {
		Gui::DrawSprite(sprites, sprites_battery1_idx, 361, 1, 1, 1);
	} else if(batteryPercent >= 11 && batteryPercent <= 30) {
		Gui::DrawSprite(sprites, sprites_battery2_idx, 361, 1, 1, 1);
	} else if(batteryPercent >= 31 && batteryPercent <= 60) {
		Gui::DrawSprite(sprites, sprites_battery3_idx, 361, 1, 1, 1);
	} else if(batteryPercent >= 61 || batteryPercent == 100) {
		Gui::DrawSprite(sprites, sprites_battery4_idx, 361, 1, 1, 1);
	}

	if (R_SUCCEEDED(PTMU_GetBatteryChargeState(&batteryChargeState)) && batteryChargeState) {
		Gui::DrawSprite(sprites, sprites_batteryCharge_idx, 361, 1, 1, 1);
	}
	
	 
	
		
			
}


void GFX::DrawSprite(int img, int x, int y, float ScaleX, float ScaleY) {
	Gui::DrawSprite(sprites, img, x, y, ScaleX, ScaleY);
}



progressBar::progressBar(const uint32_t& _max)
    {
        max = (float)_max;
    }

    void progressBar::update(const uint32_t& _prog)
    {
        prog = (float)_prog;

        float percent = (float)(prog / max) * 100;
        width  = (float)(percent * 288) / 100;
    }

    void progressBar::draw()
    {
        C2D_DrawRectSolid(8, 8, 0.5f, 304, 224, 0xFFE7E7E7);
        C2D_DrawRectSolid(16, 200, 0.5f, 288, 16, 0xFF000000);
        C2D_DrawRectSolid(16, 200, 0.5f, width, 16, 0xFF00FF00);
       
    }