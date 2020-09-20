#include "common.hpp"
#include "structs.hpp"

#include "gameManagement.hpp"

#include <vector>

class SDMenu : public Screen {
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	int Selection = 0;
	std::vector<Structs::ButtonPos> mainButtons = {
		{10, 40, 50, 50}, // Button 1.
		{10, 100, 50, 50}, // Button 2.
		{10, 160, 50, 50}, // Button 3.
       
	};
    std::shared_ptr<TitleManagement> titleFromIndex(int i) const
	{
		if (i == -2)
		{
			return nullptr;
		}
		else if ((size_t)i < GameManagement::installedTitles.size())
		{
			return GameManagement::installedTitles[i];
		}
		return nullptr;
	}
};