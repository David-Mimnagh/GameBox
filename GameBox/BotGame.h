#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GameBox.h"
#include "pugixml.hpp"

struct Key
{
	int GateID;
	int XPos;
	int Ypos;
};
struct Exit
{
	int XPos;
	int YPos;
};

struct Gate
{
	int GateID;
	int XPos;
	int YPos;

};
struct Wall
{
	int XPos;
	int XLength;
	int YPos;
	int YLength;
	bool Horizontal;
	bool Breakable;
};
struct Level
{
	int BoardWidth;
	int BoardHeight;
	std::vector<Wall> Walls;
	Exit Exit;
	std::vector<Gate> Gates;
	std::vector<Key> Keys;
};
class BotGame : public AbstractState
{
	sf::View view_main;

	sf::Mouse mouse;
	sf::Vector2f mouse_pos;

	sf::Font MainFont;
	sf::Text messageText, gameText, livesText, pointsText;

	sf::Texture BGbackground;
	sf::Sprite BGbg_sprite;

	
	sf::Texture logoTex, backButton[2], resetButton[2]; 
	sf::Sprite logoSpr, backButtonSpr[2], resetButtonSpr[2];
	pugi::xml_document doc;
	bool playing, win;
	bool back, quit;
	bool backHighlight, resetHighlight, drawReset;
	
	
	

	static int goalY;
	static int goalX;
	static string elapsedTime;
	static int wallPosY;
	static int wallGapPosX;
	static int currentLevel;

public:
	BotGame(StateManager& state_manager); // constructor
	~BotGame(); // destructor
	void pause() override final; // Pause function
	void resume() override final; // Resume Function
	void update(const sf::Time& delta) override final; //Update function logic updates like score
	void render() override final; // Render function - drawing everything
	void handle_input(const sf::Time& delta) override final; // function to handle user input	
	void handle_state_changes(); // handles changing in states ie from main menu to playing different game
	void draw_board(char board[25][25], sf::RenderWindow& window);
	void detonateBomb(char board[25][25]);
	void placeBomb(char board[25][25]);
	void add_key_to_invent(int x, int y);
	bool check_player_invent(int x, int y);
	void load_level(Level l);
	Level LoadLevelFromFile(int currentLevel);
	void move_player(string dir, char board[25][25]);
	void  get_bot_pos(char board[25][25]);
	void initGame(); // initialise the game
	void Reset(); // Reset the game
};