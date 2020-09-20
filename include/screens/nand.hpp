#ifndef NAND_HPP
#define NAND_HPP


#include "common.hpp"
#include "structs.hpp"
#include "gameManagement.hpp"


#include <vector>

#define ENTRIES_PER_SCREENG 1

class nand : public Screen {
    public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	nand();
	
private:

	
	int selectedTitle = 0;
	bool GameSelected   = false;
	int maxTitles;

	 int screenPos = 0;
	int screenPosList = 0;
	int selection = 0;

	std::shared_ptr<TitleManagement> titleFromIndex(int i) const
	{
		if (i == -2)
		{
			return nullptr;
		}
		else if ((size_t)i < GameManagement::nandtitle.size())
		{
			return GameManagement::nandtitle[i];
		}
		return nullptr;
	}
};


#endif

