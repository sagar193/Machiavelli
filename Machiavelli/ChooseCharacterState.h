#pragma once
#include "State.h"

class Game;
class ClientInfo;
class ChooseCharacterState : public State
{
public:
	ChooseCharacterState(Game& game);
	void onEnter() override;
	bool act(ClientInfo& clientInfo, std::string cmd) override;
	void onLeave() override {};
	~ChooseCharacterState();
};

