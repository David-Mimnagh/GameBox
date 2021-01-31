#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GameBox.h"
class ConnectFour : public AbstractState
{
	struct Player {
		sf::Texture tex;
		sf::Sprite spr;
		bool win;
	};
	Player player1;
	Player player2;
	sf::Texture highlight_tex;
	sf::Sprite highlight_spr;
	sf::View view_main;

	sf::Mouse mouse;
	sf::Vector2f mouse_pos;

	sf::Texture C4background;
	sf::Sprite C4bg_sprite;

	sf::Font MainFont;
	sf::Text messageText, gameText;

	sf::Texture logoTex, backButton[2], resetButton[2], blankTex, player1HTex, player2HTex, dropTex;
	sf::Sprite logoSpr, backButtonSpr[2], resetButtonSpr[2], dropSpr;
	sf::CircleShape circle[6][7];
	int board[6][7];
	bool boardHighlight[6][7];
	bool player1_turn, win;
	bool back, quit;
	bool backHighlight, resetHighlight, drawReset;
public:
	ConnectFour(StateManager& state_manager); // constructor
	~ConnectFour(); // destructor
	void pause() override final; // Pause function
	void resume() override final; // Resume Function
	void update(const sf::Time& delta) override final; //Update function logic updates like score
	void render() override final; // Render function - drawing everything
	void handle_input(const sf::Time& delta) override final; // function to handle user input	
	void handle_state_changes(); // handles changing in states ie from main menu to playing different game
	void placeChip(int i, int j);
	void CheckVertical(int rowNum, int colNum);
	void CheckHorizontal(int rowNum, int colNum);
	void CheckDiag(int rowNum, int colNum);
	void initGame(); // initialise the game
	void Reset(); // Reset the game
};