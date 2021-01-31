#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GuessingGame.h"
#include "RPS.h"
#include "Hangman.h"
#include "TicTacToe.h"
#include "Brreakout.h"
#include "ConnectFour.h"
#include "FlappyBurd.h"
#include "BotGame.h"
class GameBox : public AbstractState
{
	int choice, points;
	//RPS RPSObject;
	//Hangman HMObject;
	//TicTacToe TTTObject;
	string playAgain;
	sf::View view_main;

	sf::Texture Menu_background;
	sf::Sprite Menu_bg_sprite;
	sf::Font MainFont;
	sf::Text welcomeText, intro1, intro2,gameText, DescriptionText,pointsText;
	sf::Texture logoTex, GGButton, GGButton2, HMButton,HMButton2, RPSButton, RPSButton2, TTTButton, TTTButton2, BrButton1, BrButton2, C4Button1, C4Button2, FBButton1, FBButton2, BGButton1, BGButton2;
	sf::Sprite logoSpr, GGSprite1, GGSprite2, HMSprite1, HMSprite2, RPSSprite1, RPSSprite2, TTTSprite1, TTTSprite2, BrSprite1, BrSprite2, C4Sprite1, C4Sprite2, FBSprite1, FBSprite2, BGSprite1, BGSprite2;// NEW GAME
	sf::Vector2f mouse_pos;
	bool change_GG, change_RPS, change_HM, change_TTT, change_Br, change_C4, change_FB, change_BG, quit;
	bool highlight[9];
public:
	GameBox(StateManager& state_manager);
	~GameBox();

	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes();

	void setChoice(int c) { choice = c; }
	int getChoice() { return choice; }

	void setPoints(int p) { points = p; }
	int getPoints() { return points; }
	void Startup();
	void Home();
	void LoadGame();
};

