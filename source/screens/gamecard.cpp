#include "gameManagement.hpp"
#include "titleManagement.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "gamecard.hpp"
#include "mainMenu.hpp"
#include "msg.hpp"

#include <unistd.h>
#include <iostream>

extern bool touching(touchPosition touch, Structs::ButtonPos button);
extern bool exiting;


gamecard::gamecard() {
	Msg::DisplayMsg("Scan Gamecard...");
	GameManagement::scanGamecard();
	maxTitles = (int)GameManagement::gamecardtitle.size();
}

void gamecard::Draw(void) const {
	
	GFX::DrawTop();
	GFX::DrawBetteryTop();
	Gui::DrawString(0, 2 , 0.8f, WHITE, timeStr());
	
	Gui::DrawStringCentered(0, 2, 0.8f, WHITE, "D7-Menu", 400);
	Gui::DrawString(397-Gui::GetStringWidth(0.8f, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles)), 237-Gui::GetStringHeight(0.8f, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles)), 0.8f, WHITE, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles));
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect

	Gui::Draw_Rect(10, 50, 380, 100, C2D_Color32(130, 130, 130, 255));
	Gui::DrawStringCentered(0, 105, 0.7f, BLACK, GameManagement::gamecardtitle[selectedTitle]->Author());
	Gui::DrawStringCentered(0, 75, 0.7f, BLACK, GameManagement::gamecardtitle[selectedTitle]->name());
	
	
	GFX::DrawBottom();
	


	

	

	for(int i=0;i<ENTRIES_PER_SCREENG && i<maxTitles;i++) {
		if(screenPos + i == selection) {
			Gui::Draw_Rect(135 +(i*60)-1, 160-1, 50, 50, C2D_Color32(0, 200, 0, 255));
		}
		
		
		C2D_DrawImageAt(GameManagement::gamecardtitle[screenPos+i]->icon(), 135 +(i*60), 160, 0.5f); // Installed Title Icon.
	}

	

	Gui::DrawString(37, 214, 0.8f, WHITE, "Hold \uE046 to show controols!");
	// Draw Buttons. ;P

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect

}




void gamecard::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	// Press Start to exit the app.
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
		Gui::DrawString(1, 150, 0.8f, WHITE, "Hold \uE053 to go to Mainmenu");

		Gui::DrawString(1, 180, 0.8f, WHITE, "Press \uE045 to exit!");
	}
	if (hHeld & KEY_L){
		
		Msg::DisplayMsg("Scan Gamecard...");
		GameManagement::scanGamecard();
	}
	if (hDown & KEY_R){
		Gui::setScreen(std::make_unique<MainMenu>(), true, false);
	}
	

	// Scroll with D-Pad Left to the last available Title.
		
		// Launch the Title with <A>.
		if (hDown & KEY_A) {
			if (!GameManagement::gamecardtitle.empty()) {
				u8 param[0x300];
				u8 hmac[0x20];
				memset(param, 0, sizeof(param));
				memset(hmac, 0, sizeof(hmac));
				APT_PrepareToDoApplicationJump(0, GameManagement::gamecardtitle[0]->ID(), MEDIATYPE_GAME_CARD);
				APT_DoApplicationJump(param, sizeof(param), hmac);
			}

		}
	
	
	

	

	// Press Down to go one entry down. - 1 -> Because we don't want to go one Entry after the actual Buttons.
	
}
