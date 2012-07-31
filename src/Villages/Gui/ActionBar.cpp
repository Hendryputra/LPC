/**************************************************************************************************
* Copyright 2012 Ryan Holzum                                                                      *
*                                                                                                 *
* This file is part of Villages.                                                                  *
*                                                                                                 *
* Villages is free software: you can redistribute it and/or modify it under the terms of the      *
* GNU General Public License as published by the Free Software Foundation, either version 3 of    *
* the License, or (at your option) any later version.                                             *
*                                                                                                 *
* Vilages is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without    *
* even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
* GNU General Public License for more details.                                                    *
*                                                                                                 *
* You should have received a copy of the GNU General Public License along with Vilages.           *
* If not, see http://www.gnu.org/licenses/.                                                       *
**************************************************************************************************/

#include "ActionBar.h"

#include <string>

#include "SDL.h"

#include "Engine/Gui/ClickableButton.h"
#include "Engine/Gui/UI.h"
#include "Engine/Util/Logger.h"
#include "Engine/Util/VillageException.h"
#include "Villages/Gui/HoverImage.h"
#include "Villages/States/SimState.h"

using namespace std;

ActionBar::ActionBar(SimState* state, int x, int y, int width, int height, string backgroundSrc) : UI(x, y, width, height, backgroundSrc)
{
	Logger::debug("ActionBar Constructor");

	ActionBar::state = state;

	Image* temp = NULL;

	buildHouse = new ClickableButton<ActionBar>(x + 10, y + 10, 64, 64, "house-button-normal.png", "house-button-hover.png", "house-button-pressed.png", this, &ActionBar::placeHouse); 
	addComponent("buildHouse", buildHouse);
	hoverHouse = new HoverImage(state, x + 10, y - 65, 180, 75, x + 10, y + 10, 64, 64);
	hoverHouse->addLine("Houses Hold 10 People");
	hoverHouse->addLine("200");
	hoverHouse->addLine("150");
	temp = new Image("icon-gold.png", (Uint8)255, 0, 255, .5);
	hoverHouse->addImage(40, 25, temp);
	temp = new Image("icon-wood.png", (Uint8)255, 0, 255, .5);
	hoverHouse->addImage(40, 45, temp);

	buildFarm = new ClickableButton<ActionBar>(x + 74, y + 10, 64, 64, "farm-button-normal.png", "farm-button-hover.png", "farm-button-pressed.png", this, &ActionBar::placeFarm);
	addComponent("buildFarm", buildFarm);
	hoverFarm = new HoverImage(state, x + 74, y - 85, 240, 95, x + 74, y + 10, 64, 64);
	hoverFarm->addLine("Farms Generate Food Each Turn");
	hoverFarm->addLine("Max Workers = 10");
	hoverFarm->addLine("Output = Workers * 5");
	hoverFarm->addLine("100");
	temp = new Image("icon-gold.png", (Uint8)255, 0, 255, .5);
	hoverFarm->addImage(40, 65, temp);

	buildMiningCamp = new ClickableButton<ActionBar>(x + 138, y + 10, 64, 64, "miningcamp-button-normal.png", "miningcamp-button-hover.png", "miningcamp-button-pressed.png", this, &ActionBar::placeMiningCamp);
	addComponent("buildMiningCamp", buildMiningCamp);
	hoverMine = new HoverImage(state, x + 138, y - 125, 240, 135, x + 138, y + 10, 64, 64);
	hoverMine->addLine("Mines Generate Ore Each Turn");
	hoverMine->addLine("Must be placed next to caves");
	hoverMine->addLine("Max Workers = 5");
	hoverMine->addLine("Output = Workers * 2");
	hoverMine->addLine("500");
	hoverMine->addLine("100");
	temp = new Image("icon-gold.png", (Uint8)255, 0, 255, .5);
	hoverMine->addImage(40, 85, temp);
	temp = new Image("icon-wood.png", (Uint8)255, 0, 255, .5);
	hoverMine->addImage(40, 105, temp);

	buildMill = new ClickableButton<ActionBar>(x + 202, y + 10, 64, 64, "mill-button-normal.png", "mill-button-hover.png", "mill-button-pressed.png", this, &ActionBar::placeMill);
	addComponent("buildMill", buildMill);
	hoverMill = new HoverImage(state, x + 202, y - 125, 240, 135, x + 202, y + 10, 64, 64);
	hoverMill->addLine("Mills Generate Wood Each Turn");
	hoverMill->addLine("Must be placed next to trees");
	hoverMill->addLine("Max Workers = 10");
	hoverMill->addLine("Output = 4");
	hoverMill->addLine("150");
	hoverMill->addLine("25");
	temp = new Image("icon-gold.png", (Uint8)255, 0, 255, .5);
	hoverMill->addImage(40, 85, temp);
	temp = new Image("icon-wood.png", (Uint8)255, 0, 255, .5);
	hoverMill->addImage(40, 105, temp);

	buildWell = new ClickableButton<ActionBar>(x + 266, y + 10, 64, 64, "well-button-normal.png", "well-button-hover.png", "well-button-pressed.png", this, &ActionBar::placeWell);
	addComponent("buildWell", buildWell);
	hoverWell = new HoverImage(state, x + 266, y - 105, 295, 115, x + 266, y + 10, 64, 64);
	hoverWell->addLine("Wells Generate Water");
	hoverWell->addLine("Lack of water causes people to leave");
	hoverWell->addLine("Each well provides 15 water");
	hoverWell->addLine("Each villager consumes 1 water");
	hoverWell->addLine("100");
	temp = new Image("icon-gold.png", (Uint8)255, 0, 255, .5);
	hoverWell->addImage(40, 85, temp);

	/*buildTavern = new ClickableButton<ActionBar>(x + 330, y + 10, 64, 64, "tavern-button-normal.png", "tavern-button-hover.png", "tavern-button-pressed.png", this, &ActionBar::placeTavern);

	addComponent("buildTavern", buildTavern);

	buildTheatre = new ClickableButton<ActionBar>(x + 394, y + 10, 64, 64, "theatre-button-normal.png", "theatre-button-hover.png", "theatre-button-pressed.png", this, &ActionBar::placeTheatre);

	addComponent("buildTheatre", buildTheatre);

	buildWeaver = new ClickableButton<ActionBar>(x + 458, y + 10, 64, 64, "weaver-button-normal.png", "weaver-button-hover.png", "weaver-button-pressed.png", this, &ActionBar::placeWeaver);

	addComponent("buildWeaver", buildWeaver);

	buildJeweler = new ClickableButton<ActionBar>(x + 522, y + 10, 64, 64, "jeweler-button-normal.png", "jeweler-button-hover.png", "jeweler-button-pressed.png", this, &ActionBar::placeJeweler);

	addComponent("buildJeweler", buildJeweler);*/

	buildBlacksmith = new ClickableButton<ActionBar>(x + 330, y + 10, 64, 64, "blacksmith-button-normal.png", "blacksmith-button-hover.png", "blacksmith-button-pressed.png", this, &ActionBar::placeBlacksmith);

	addComponent("buildBlacksmith", buildBlacksmith);

	/*buildBakery = new ClickableButton<ActionBar>(x + 650, y + 10, 64, 64, "bakery-button-normal.png", "bakery-button-hover.png", "bakery-button-pressed.png", this, &ActionBar::placeBakery);

	addComponent("buildBakery", buildBakery);*/

	buildGuardStation = new ClickableButton<ActionBar>(x + 394, y + 10, 64, 64, "guardstation-button-normal.png", "guardstation-button-hover.png", "guardstation-button-pressed.png", this, &ActionBar::placeGuardStation);

	addComponent("buildGuardStation", buildGuardStation);

	/*buildMarket = new ClickableButton<ActionBar>(x + 778, y + 10, 64, 64, "market-button-normal.png", "market-button-hover.png", "market-button-pressed.png", this, &ActionBar::placeMarket);

	addComponent("buildMarket", buildMarket);*/

	buildRoad = new ClickableButton<ActionBar>(x + 458, y + 10, 64, 64, "road-button-normal.png", "road-button-hover.png", "road-button-pressed.png", this, &ActionBar::placeRoad);

	addComponent("buildRoad", buildRoad);

	buildWonder = new ClickableButton<ActionBar>(x + 522, y + 10, 64, 64, "wonder-button-normal.png", "wonder-button-hover.png", "wonder-button-pressed.png", this, &ActionBar::placeWonder);

	addComponent("buildWonder", buildWonder);

	in = new ClickableButton<ActionBar>(x + 586, y + 10, 32, 32, "zoomin-button-normal.png", "zoomin-button-hover.png", "zoomin-button-pressed.png", this, &ActionBar::zoomIn);

	addComponent("zoomIn", in);

	out = new ClickableButton<ActionBar>(x + 586, y + 42, 32, 32, "zoomout-button-normal.png", "zoomout-button-hover.png", "zoomout-button-pressed.png", this, &ActionBar::zoomOut);

	addComponent("zoomOut", out);

	del = new ClickableButton<ActionBar>(x + 618, y + 10, 64, 64, "delete-button-normal.png", "delete-button-hover.png", "delete-button-pressed.png", this, &ActionBar::deleteStuff);

	addComponent("delete", del);
}

ActionBar::~ActionBar()
{
	Logger::debug("ActionBar Destructor");

	delete hoverHouse;
	delete hoverFarm;
	delete hoverMine;
	delete hoverMill;
	delete hoverWell;

	//delete buildHouse;
	//delete buildFarm;
	//delete buildMiningCamp;
	//delete buildMill;
	//delete buildWell;
	//delete buildTavern;
	//delete buildTheatre;
	//delete buildWeaver;
	//delete buildJeweler;
	//delete buildBlacksmith;
	//delete buildBakery;
	//delete buildGuardStation;
	//delete buildMarket;
	//delete buildRoad;
	//delete in;
	//delete out;
}

ActionBar::ActionBar(const ActionBar& data) : UI(0, 0, 0, 0, "")
{
	throw VillageException("ActionBar Copy Constructor");
}

ActionBar& ActionBar::operator=(const ActionBar* rhs)
{
	throw VillageException("ActionBar Assignment Operator");
}

void ActionBar::raiseEvent(SDL_Event* event)
{
	UI::raiseEvent(event);

	hoverHouse->raiseEvent(event);
	hoverFarm->raiseEvent(event);
	hoverMine->raiseEvent(event);
	hoverMill->raiseEvent(event);
	hoverWell->raiseEvent(event);
}

void ActionBar::draw(SDL_Surface* screen)
{
	UI::draw(screen);

	hoverHouse->draw(0, 0, screen);
	hoverFarm->draw(0, 0, screen);
	hoverMine->draw(0, 0, screen);
	hoverMill->draw(0, 0, screen);
	hoverWell->draw(0, 0, screen);
}

void ActionBar::placeHouse()
{
	state->placeHouse();
}

void ActionBar::placeFarm()
{
	state->placeFarm();
}

void ActionBar::placeMiningCamp()
{
	state->placeMiningCamp();
}

void ActionBar::placeMill()
{
	state->placeMill();
}

void ActionBar::placeWell()
{
	state->placeWell();
}

void ActionBar::placeTavern()
{
	state->placeTavern();
}

void ActionBar::placeTheatre()
{
	state->placeTheatre();
}

void ActionBar::placeWeaver()
{
	state->placeWeaver();
}

void ActionBar::placeJeweler()
{
	state->placeJeweler();
}

void ActionBar::placeBlacksmith()
{
	state->placeBlacksmith();
}

void ActionBar::placeBakery()
{
	state->placeBakery();
}

void ActionBar::placeGuardStation()
{
	state->placeGuardStation();
}

void ActionBar::placeMarket()
{
	state->placeMarket();
}

void ActionBar::placeRoad()
{
	state->placeRoad();
}

void ActionBar::zoomIn()
{
	state->zoomIn();
}

void ActionBar::zoomOut()
{
	state->zoomOut();
}

void ActionBar::deleteStuff()
{
	state->deleteStuff();
}

void ActionBar::placeWonder()
{
	state->placeWonder();
}