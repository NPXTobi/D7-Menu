#include "gameManagement.hpp"
#include "titleManagement.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "nand.hpp"
#include "mainMenu.hpp"
#include "msg.hpp"

#include <unistd.h>
#include <iostream>

extern bool touching(touchPosition touch, Structs::ButtonPos button);
extern bool exiting;


nand::nand() {
	Msg::DisplayMsg("Scan System titles...");
	GameManagement::scanNAND();
	maxTitles = (int)GameManagement::nandtitle.size();
}

void nand::Draw(void) const {
	
	GFX::DrawTop();
	GFX::DrawBetteryTop();
	Gui::DrawString(0, 2 , 0.8f, WHITE, timeStr());
	
	Gui::DrawStringCentered(0, 2, 0.8f, WHITE, "HomeMen3D", 400);
	Gui::DrawString(397-Gui::GetStringWidth(0.8f, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles)), 237-Gui::GetStringHeight(0.8f, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles)), 0.8f, WHITE, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles));
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	GFX::DrawBottom();
	Gui::Draw_Rect(50, 160, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(110, 160, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(170, 160, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(230, 160, 48, 48, C2D_Color32(160, 160, 160, 255));

	

	Gui::Draw_Rect(10, 50, 300, 100, C2D_Color32(130, 130, 130, 255));

	for(int i=0;i<ENTRIES_PER_SCREENG && i<maxTitles;i++) {
		if(screenPos + i == selection) {
			Gui::Draw_Rect(50 +(i*60)-1, 160-1, 50, 50, C2D_Color32(0, 200, 0, 255));
		}
		
		
		C2D_DrawImageAt(GameManagement::nandtitle[screenPos+i]->icon(), 50 +(i*60), 160, 0.5f); // Installed Title Icon.
	}

	Gui::DrawStringCentered(0, 75, 0.7f, BLACK, GameManagement::nandtitle[selectedTitle]->name());
	Gui::DrawStringCentered(0, 105, 0.7f, BLACK, GameManagement::nandtitle[selectedTitle]->Author());
	

	Gui::DrawString(37, 214, 0.8f, WHITE, "Hold \uE046 to show controols!");
	// Draw Buttons. ;P

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect

}




void nand::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
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
		
		Msg::DisplayMsg("Scan nand...");
		GameManagement::scanNAND();
	}
	if (hDown & KEY_R){
		Gui::setScreen(std::make_unique<MainMenu>(), true, false);
	}
	

	// Scroll with D-Pad Left to the last available Title.
		
		// Launch the Title with <A>.
		if (hDown & KEY_A) {
			if (!GameManagement::nandtitle.empty()) {
				u8 param[0x300];
				u8 hmac[0x20];
				memset(param, 0, sizeof(param));
				memset(hmac, 0, sizeof(hmac));
				APT_PrepareToDoApplicationJump(0, GameManagement::nandtitle[0]->ID(), MEDIATYPE_GAME_CARD);
				APT_DoApplicationJump(param, sizeof(param), hmac);
			}

		}
	
	
	

	

	// Press Down to go one entry down. - 1 -> Because we don't want to go one Entry after the actual Buttons.
	
}
