#pragma once
#include "State.h"

class RemoveCharacterState : public State
{
public:
	RemoveCharacterState(Game& game);
	void onEnter() override {};
	bool act(ClientInfo& clientInfo, std::string cmd) override;
	void onLeave() override {};
	~RemoveCharacterState();
};

