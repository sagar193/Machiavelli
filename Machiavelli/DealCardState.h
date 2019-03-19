#pragma once
#include "State.h"
#include <algorithm>
#include "ChooseCharacterState.h"
#include "RemoveCharacterState.h"

class DealCardState : public State
{
private:
	State* currentState;
	ChooseCharacterState chooseCharacterState;
	RemoveCharacterState removeCharacterState;
	bool firstTurn;
public:
	DealCardState(Game& game);
	void onEnter() override;
	bool act(ClientInfo& clientInfo,std::string cmd) override;
	void onLeave() override;

	void printCharacterCards(ClientInfo& clientInfo);

	~DealCardState();
};

