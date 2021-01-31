#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GameBox.h"
class RPS : public AbstractState
{
	struct Choice
	{
		string choice;
	};

	struct AI
	{
		int lives;
		Choice AIchoice; /* 1- Rock, 2 - Paper, 3 - Scissors*/

	};
	struct Player
	{
		int lives;
		Choice Playerchoice; /* 1- Rock, 2 - Paper, 3 - Scissors*/
	};
	AI ai;
	Player player;
	int choiceNumber;
	string correctMessage, wrongMessage;
	sf::Texture GGbackground;
	sf::Sprite GGbg_sprite;
	sf::Font MainFont;
	sf::Text messageText, gameText, livesText, pointsText;
	sf::Texture logoTex, backButton[2], resetButton[2], pButton[3], pButtonS[3], pButtonH[3],countDownText[3], cButton[3], confirmButton[3];
	sf::Sprite  logoSpr, backButtonSpr[2], resetButtonSpr[2], pButtonSpr[3], pButtonSSpr[3], pButtonHSpr[3], countDownTextSpr[3], cButtonSpr[3], confirmButtonSpr[3];
	bool backHighlight, resetHighlight, pButtonHighlight[3], pButtonSelect[3], confirmHighlight;
	bool init, reset, choosing, playing, win, quit, back, drawReset, confirmSelect;
	int totalTime;

	sf::View view_main;
	sf::Vector2f mouse_pos;
public:
	RPS(StateManager& state_manager);
	~RPS();
	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes();
	void imageDraw(sf::Sprite thissprite, sf::Texture thistexture);
	void setPlayingState(int p) { playing = p; }
	int getPlayingState() { return playing; }

	void setResetState(int r) { reset = r; }
	int getResetState() { return reset; }

	void setWinState(int w) { win = w; }
	int getWinState() { return win; }

	void setChoosingState(int c) { choosing = c; }
	int getChoosingState() { return choosing; }

	void initGame();
	void PlayerTurn();
	void Playing();
	void Reset();
};

