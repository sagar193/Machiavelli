#pragma once
#include "State.h"

class PlayingState : public State
{
public:
	enum States {
		InitState,
		ChooseState,
		PlaceBuildingCard,
		UseCharacterCard
	};
	PlayingState(Game& game);
	void onEnter() override;
	bool act(ClientInfo& clientInfo,std::string cmd) override;
	void onLeave() override;
	~PlayingState();
private:
	States currentState_;
	bool initState(ClientInfo& clientInfo, std::string cmd);
	bool chooseState(ClientInfo& clientInfo, std::string cmd);
	bool placeBuildingCard(ClientInfo& clientInfo, std::string cmd);
	bool useCharacterCard(ClientInfo& clientInfo, std::string cmd);
	bool initState_;
	bool placedBuildingCard_;
	bool usedCharacterCard_;
	int currentCharacterIndex;
	void printChooseStateOptions();

};

