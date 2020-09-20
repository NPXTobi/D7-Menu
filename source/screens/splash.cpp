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

#include "mainMenu.hpp"
#include "splash.hpp"
#include "sprites.h"
#include "ptmu_x.h"
#include "utils.hpp"

extern C2D_SpriteSheet sprites;

void Stack::Draw(void) const {
	GFX::DrawTop();
	GFX::DrawBetteryTop();
	Gui::DrawString(0, 2, 0.8f, WHITE, timeStr());
	Gui::DrawStringCentered(0, 2, 0.8f, WHITE, "D7-Menu", 400);
	Gui::DrawStringCentered(0, 40, 0.8f, WHITE, "DSGameCards ar not supported yet.\n\nBefore removing a gamecard\n\ngo back to the MainMenu.", 400);
	Gui::DrawStringCentered(0, 214, 0.8, WHITE, "Universal-Team, Tobi", 400);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	GFX::DrawBottom();
	Gui::DrawSprite(sprites, sprites_ulogo_idx, -10, 20, 0.65, 0.65);
	
	
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
}


void Stack::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	this->delay++;
	// If the delay is larger than 130 -> Switch screen.
	if (this->delay > 130) {
		Gui::setScreen(std::make_unique<MainMenu>(), true, false);
	}
}
