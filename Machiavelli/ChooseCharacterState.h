#pragma once
#include "State.h"

class ChooseCharacterState : public State
{
public:
	ChooseCharacterState(Game& game);
	void onEnter() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;
	void onLeave() override {};
	~ChooseCharacterState();
};

