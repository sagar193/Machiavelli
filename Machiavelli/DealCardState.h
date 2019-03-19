#pragma once
#include "State.h"
#include <algorithm>

class DealCardState : public State
{
public:
	DealCardState(Game& game);
	void onEnter() override;
	void act(ClientInfo& clientInfo,std::string cmd) override;
	void onLeave() override;

	void printCharacterCards(ClientInfo& clientInfo);

	~DealCardState();
};

