#pragma once
#include "Common.h"
#include "AbstractState.hpp"
#include "GameBox.h"
class TicTacToe : public AbstractState
{
	struct AI
	{
		int positionID; /*0 - blank, 1 - Player, 2 - AI*/
		int movePosition;
		bool placed; bool checked;
		int moveCount;
	};
	struct Player
	{
		int positionID; /*0 - blank, 1 - Player, 2 - AI*/
		int movePosition;
	};
	/*0 - blank, 1 - Player, 2 - AI*/int	board[3][3] =
	{ { 0,0,0 }, /* ROW 0*/
	{ 0,0,0 }, /* ROW 1*/
	{ 0,0,0 }  /* ROW 2*/
	};
	int whoGO;
	int Row, Col, spacesLeft;
	AI computer;
	Player player;
	bool init, firstMove, choosing, playing, win, stillGo[9], boardHighlight[3][3], freeSpace[3][3], playerTurn, computerTurn, drawReset, resetH, backH,back,quit;
	sf::View view_main;
	sf::Vector2f mouse_pos;
	sf::Font MainFont;
	sf::Text messageText, gameText, winText;
	sf::Texture TTTbackground;
	sf::Sprite TTTbg_sprite;
	sf::Texture logoTex, backButton[2], resetButton[2], boardTex, boardMarkerTex[3][3], playerMarkerTex[3][3], computerMarkerTex[3][3], boardMarkerHTex[3][3];
	sf::Sprite  logoSpr, backButtonSpr[2], resetButtonSpr[2], boardSpr, boardMarkerSpr[3][3], playerMarkerSpr[3][3], computerMarkerSpr[3][3], boardMarkerHSpr[3][3];
public:
	TicTacToe(StateManager& state_manager);
	~TicTacToe();
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
	void setWhoGoes(int w) { whoGO = w; }
	int getWhoGoes() { return whoGO; }
	void initGame();
	void randomPos();
	void CheckBoard();
	void CRowOne();
	void CRowTwo();
	void CRowThree();
	void CColOne();
	void CColTwo();
	void CColThree();
	void CDiagRight();
	void CDiagLeft();
	void CheckBoardWin();
	void CheckWinPlayer();
	void CheckWinComputer();
	void AIMove();
	void PlayerTurn();
	void Playing();
	void Reset();
};

