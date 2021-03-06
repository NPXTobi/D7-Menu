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

#ifndef GFX_HPP
#define GFX_HPP

#include "gui.hpp"
#include "sprites.h"
#include "colors.hpp"

#include <citro2d.h>



#include <3ds.h>
#include <string>

enum class ProgressBar {
	Downloading,
	Titleloader,
	Installing
};

namespace UI {
	// Progressbar.
	void DrawProgressBar(u64 currentProgress, u64 totalProgress);
	// Draw Button.
}
#define WHITE C2D_Color32(255, 255, 255, 255)

namespace GFX {
	// Draw Basic GUI.
	void DrawTop(void);
	void DrawBottom(void);
	void DrawFileBrowseBG(bool isTop = true);
	void DrawBetteryTop(void);
	
	// Draw Sprites.
	void DrawSprite(int img, int x, int y, float ScaleX = 1, float ScaleY = 1);
}

 class progressBar
    {
        public:
            progressBar(const uint32_t& _max);
            void update(const uint32_t& _prog);
            void draw();

        private:
            float max, prog, width;
    };

#endif