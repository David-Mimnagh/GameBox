#pragma once
#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GameBox.h"
class FlappyBurd : public AbstractState
{
	struct Burd {
		sf::Vector2f position;
		sf::Texture tex;
		sf::Sprite spr;
		int score;
		bool dead;
	};
	Burd fpBurd;
	float gravity;
	float jump;
	sf::View view_main;

	sf::Mouse mouse;
	sf::Vector2f mouse_pos;

	sf::Texture FBbackground[2], pipeTex[4];
	sf::Sprite FBbg_sprite[2], pipeSpr[4];

	sf::Font MainFont;
	sf::Text messageText, gameText;

	sf::Texture logoTex, backButton[2], resetButton[2];
	sf::Sprite logoSpr, backButtonSpr[2], resetButtonSpr[2];
	bool back, quit;
	bool backHighlight, resetHighlight, drawReset;
public:
	FlappyBurd(StateManager& state_manager); // constructor
	~FlappyBurd(); // destructor
	void pause() override final; // Pause function
	void resume() override final; // Resume Function
	void update(const sf::Time& delta) override final; //Update function logic updates like score
	void render() override final; // Render function - drawing everything
	void handle_input(const sf::Time& delta) override final; // function to handle user input	
	void handle_state_changes(); // handles changing in states ie from main menu to playing different game
	void initGame(); // initialise the game
	void Reset(); // Reset the game
};