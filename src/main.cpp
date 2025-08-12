#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;

std::vector<std::string> roasts = {
	"You're the reason the loading screen takes longer.",
	"Even the pause button needs a break from you.",
	"Your icon has seen better players.",
	"Geometry Dash called—it wants its dignity back.",
	"You jump like lag is a personality trait."};

class $modify(MyMenuLayer, MenuLayer)
{
	bool init()
	{
		if (!MenuLayer::init())
			return false;

		auto mySprite = CCSprite::createWithSpriteFrameName("geode.loader/baseCircle_BigAlt_Green.png");
		if (!mySprite)
			return true;

		auto iconSprite = CCSprite::createWithSpriteFrameName("shard_glow_001.png");
		if (!iconSprite)
			return true;

		auto iconSprite2 = CCSprite::createWithSpriteFrameName("shardShadow_001.png");
		if (!iconSprite2)
			return true;

		iconSprite->setScale(0.9f);
		iconSprite2->setScale(0.9f);

		CCPoint center = mySprite->getContentSize() / 2;
		CCPoint offset = CCPoint(-1, 1);

		iconSprite->setPosition(center + offset);
		iconSprite2->setPosition(center + offset);

		iconSprite->setRotation(345);
		iconSprite2->setRotation(345);

		mySprite->addChild(iconSprite);
		mySprite->addChild(iconSprite2);

		mySprite->setScale(0.95f);

		auto myButton = CCMenuItemSpriteExtra::create(
			mySprite,
			this,
			menu_selector(MyMenuLayer::onMyButton));
		myButton->setID("my-button"_spr);

		auto menu = this->getChildByID("bottom-menu");
		if (!menu)
			return true;

		menu->addChild(myButton);
		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject *)
	{
		if (roasts.empty())
			return;

		int index = rand() % roasts.size();
		std::string roast = roasts[index];

		FLAlertLayer::create("Icon Roaster", roast.c_str(), "Cry")->show();
	}
};