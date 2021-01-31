#include "Common.h"
#include "GameBox.h"
#include "StateManager.hpp"

string AIchoice; string Playerchoice;
int choice, points;

int main(int argc, char *argv[])
{
	try
	{
		StateManager state_manager("Game Box", 1280, 960);

		state_manager.change_state(state_manager.state_ptr<GameBox>());

		return state_manager.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	return 0;
	
}