#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GameBox.h"
class Hangman : public AbstractState
{

	struct Title
	{
		string title;
	};
	struct Catagory
	{
		string catName; /*Available Catagories*/
		vector<Title> titleName;/*Available titles*/
	};
	struct Player
	{
		int tryCount;
		int lives;
		string guess;
	};
	string catagoryChoice;
	int CatagoryID;
	int vectorCounter;
	vector<Catagory> CatObject;
	Player player;
	string correctMessage, wrongMessage;
	vector<char> currentProgressChar;
	string word, wordToGuess, wordToGuessCryptic, currentProgressWord;
	int randomWordID;

	sf::View view_main;
	sf::Vector2f mouse_pos;

	sf::Texture HMbackground;
	sf::Sprite HMbg_sprite;
	sf::Font MainFont;
	string newWord;
	sf::Text messageText, gameText, livesText, pointsText, wordToGuesssCrypticText, progressText;
	sf::Texture logoTex, backButton[2], resetButton[2],catagoryChoiceTex[3], catagoryChoiceTexH[3], guessLetter[26], guessHLetter[26], gameTex[6],confirmButton[3];
	sf::Sprite  logoSpr, backButtonSpr[2], resetButtonSpr[2], catagoryChoiceSpr[3], catagoryChoiceSprH[3], guessLetterSpr[26], guessHLetterSpr[26], gameSpr[6], confirmButtonSpr[3];
	bool backHighlight, resetHighlight, confirmHighlight, guessLetterHighlight[26], catHighlight[3];
	bool init, reset, choosing, fullGuess, playing, win, quit, back, drawReset, waitForGuess, confirmSelect;

public:
	Hangman(StateManager& state_manager);
	~Hangman();
	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes();

	void imageDraw(sf::Sprite thissprite, sf::Texture thistexture);
	void setPlayingState(int p) { playing = p; }
	int getPlayingState() { return playing; }
	void setWinState(int w) { win = w; }
	int getWinState() { return win; }
	void setChoosingState(int c) { choosing = c; }
	int getChoosingState() { return choosing; }
	void initGame();
	void RandomWord();
	void ConvertWord();
	void PlayerGuess();
	void PlayerTurn();
	void Playing();
	void Reset();
};
