#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GameBox.h"

class GuessingGame : public AbstractState
{
	int numberToGuess, GuessedNumber, numberOfGuesses, guessesLeft;
	bool guessing, win;
	sf::Mouse mouse;
	sf::View view_main;
	sf::Vector2f mouse_pos;
	sf::Texture GGbackground;
	sf::Sprite GGbg_sprite;
	sf::Font MainFont;
	sf::Text messageText, gameText, livesText, pointsText;
	sf::Texture button[11], buttonH[11], logoTex, backButton[2], resetButton[2];
	sf::Sprite  buttonSpr[11], buttonHSpr[11], logoSpr, backButtonSpr[2], resetButtonSpr[2];
	bool back, quit, guessed, subtractGuess;
	bool highlight[11], backHighlight, resetHighlight, drawReset;
	
public:
	GuessingGame(StateManager& state_manager);
	~GuessingGame();
	void pause() override final;
	void resume() override final;
	void update(const sf::Time& delta) override final;
	void render() override final;
	void handle_input(const sf::Time& delta) override final;
	void handle_state_changes();

	void imageDraw(sf::Sprite thissprite, sf::Texture thistexture);
	
	void setWinState(int w) { win = w; }
	int getWinState() { return win; }

	void initGame();
	void Guess();
	void CorrectGuess();
	void Reset();
};

