#pragma once
#include "State.h"

class PlayingState : public State
{
public:
	PlayingState(Game& game);
	void onEnter() override;
	void act(ClientInfo& clientInfo,std::string cmd) override;
	void onLeave() override;
	~PlayingState();
};

