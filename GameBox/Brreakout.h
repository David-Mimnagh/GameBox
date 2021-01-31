#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GameBox.h"


class Breakout : public AbstractState
{
	 struct Player {
		int lives;
		int score;
		sf::Vector2f pos;
		sf::Texture tex;
		sf::Sprite spr;
	};
	struct Block {
		int typeId;
		int scoreToGive;
		bool draw;
		sf::Vector2f pos;
		sf::Texture tex;
		sf::Sprite spr;
	};
	struct Ball{
		float speedModifier;
		float currentSpeed;
		sf::Vector2f direction;
		sf::Vector2f pos;
		sf::Texture tex;
		sf::Sprite spr;
		
	};
	Player player;
	Ball ball;
	std::vector<Block> blockList;

	sf::View view_main;

	sf::Mouse mouse;
	sf::Vector2f mouse_pos;

	sf::Texture Brbackground;
	sf::Sprite Brbg_sprite;

	sf::Font MainFont;
	sf::Text messageText, gameText, livesText, pointsText;

	sf::Texture logoTex, backButton[2], resetButton[2];
	sf::Sprite logoSpr, backButtonSpr[2], resetButtonSpr[2];
	bool gameWon[48];
	bool playing, win;
	bool back, quit;
	bool backHighlight, resetHighlight, drawReset;
public:
	Breakout(StateManager& state_manager); // constructor
	~Breakout(); // destructor
	void pause() override final; // Pause function
	void resume() override final; // Resume Function
	void update(const sf::Time& delta) override final; //Update function logic updates like score
	void render() override final; // Render function - drawing everything
	void handle_input(const sf::Time& delta) override final; // function to handle user input	
	void handle_state_changes(); // handles changing in states ie from main menu to playing different game

	void setVel(sf::Vector2f vel);
	void initGame(); // initialise the game
	void Reset(); // Reset the game
};

