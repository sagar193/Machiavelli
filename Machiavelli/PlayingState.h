#pragma once
#include "State.h"

class PlayingState : public State
{
public:
	enum States {
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
	void chooseState(ClientInfo& clientInfo, std::string cmd);
	void placeBuidlingCard(ClientInfo& clientInfo, std::string cmd);
	void useCharacterCard(ClientInfo& clientInfo, std::string cmd);

};

