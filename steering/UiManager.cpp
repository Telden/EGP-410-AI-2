#include "UiManager.h"
#include <sstream>

UiManager::UiManager()
{
	mpFont = NULL;
}

UiManager::~UiManager()
{
	cleanup();
}

bool UiManager::init()
{
	// Initialize the allegro font system
	al_init_font_addon();
	if (!al_init_ttf_addon())
	{
		printf("ttf font addon not initted properly!\n");
		return false;
	}

	//actually load the font
	mpFont = al_load_ttf_font("cour.ttf", 20, 0);
	if (mpFont == NULL)
	{
		printf("ttf font file not loaded properly!\n");
		return false;
	}

	// If everything loaded correctly, return true
	return true;
}

void UiManager::cleanup()
{
	al_destroy_font(mpFont);
	mpFont = NULL;
}

void UiManager::update()
{
	drawPointerText();
	if (mShouldDraw)
		drawDebugInfo();
}

void UiManager::switchUI()
{
	if (mShouldDraw)
		mShouldDraw = false;
	else
		mShouldDraw = true;
}

//Updates the mouse information from the input manager
void UiManager::updateMouseUiInformation(float& mouseX, float& mouseY, std::string mousePos, std::string currentSelction)
{
	mMouseX = mouseX;
	mMouseY = mouseY;
	mMousePos = mousePos;
	mCurrentSelection = currentSelction;
}

void UiManager::updateUnitUiInformation(float& reactionRadius, float& angularVelocity, float& enemyVelocity)
{
	mReactionRadius = reactionRadius;
	mAngularVelocity = angularVelocity;
	mEnemyVelocity = enemyVelocity;
}
void UiManager::drawPointerText()
{
	al_draw_text(mpFont, al_map_rgb(mRed, mGreen, mBlue), mMouseX, mMouseY, ALLEGRO_ALIGN_CENTRE, mMousePos.c_str());
}

void UiManager::drawDebugInfo()
{
	std::stringstream tmpText;
	
	// Draw the current increase/decrease selection
	tmpText << "Current selection: " << mCurrentSelection;
	al_draw_text(mpFont, al_map_rgb(mRed, mGreen, mBlue), 50, 30, ALLEGRO_ALIGN_LEFT, tmpText.str().c_str());
	tmpText.str("");

	// Draw the reaction Radius
	tmpText << "Reaction radius: " << mReactionRadius;
	al_draw_text(mpFont, al_map_rgb(mRed, mGreen, mBlue), 50, 50, ALLEGRO_ALIGN_LEFT, tmpText.str().c_str());
	tmpText.str("");

	// Draw the angular velocity
	tmpText << "Angular velocity: " << mAngularVelocity;
	al_draw_text(mpFont, al_map_rgb(mRed, mGreen, mBlue), 50, 70, ALLEGRO_ALIGN_LEFT, tmpText.str().c_str());
	tmpText.str("");

	// Draw the enemy velocity
	tmpText << "Enemy velocity: " << mEnemyVelocity;
	al_draw_text(mpFont, al_map_rgb(mRed, mGreen, mBlue), 50, 90, ALLEGRO_ALIGN_LEFT, tmpText.str().c_str());
	tmpText.str("");
}