#include "TicTacToe.h"



TicTacToe::TicTacToe(StateManager& state_manager) : AbstractState(state_manager)
{
	firstMove = true;
	computer.placed = false;
	computer.checked = false;
	drawReset = false;
	resetH = false;
	computer.moveCount = 0;
	spacesLeft = 9;
	for (int i = 0; i < 9; i++)
	{
		stillGo[i] = true;
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = 0;
	whoGO = 0;
	if (!TTTbackground.loadFromFile("TTT/TTTbackground.png"))
	{
		std::cout << "Could not load image\n";
	}
	TTTbg_sprite.setTexture(TTTbackground);

	if (!logoTex.loadFromFile("Logo.png"))
	{
		std::cout << "Could not load image\n";
	}
	logoSpr.setTexture(logoTex);
	logoSpr.setOrigin(logoSpr.getGlobalBounds().width / 2, logoSpr.getGlobalBounds().height / 2);
	logoSpr.setPosition(WINDOW_WIDTH / 2, 100);

	if (!MainFont.loadFromFile("MavenPro-Regular.ttf"))
	{
		cout << "NO font found.";
	}

	messageText.setFont(MainFont);
	messageText.setString("Welcome to GameBox - TicTacToe.");
	messageText.setCharacterSize(24);
	messageText.setOrigin(messageText.getGlobalBounds().width / 2, messageText.getGlobalBounds().height / 2);
	messageText.setPosition(WINDOW_WIDTH / 2, 200);
	messageText.setFillColor(sf::Color::Red);

	gameText.setFont(MainFont);
	gameText.setString("");
	gameText.setCharacterSize(24);
	gameText.setOrigin(gameText.getGlobalBounds().width / 2, gameText.getGlobalBounds().height / 2);
	gameText.setPosition(WINDOW_WIDTH /2 - gameText.getGlobalBounds().width, 250);
	gameText.setFillColor(sf::Color::Red);

	winText.setFont(MainFont);
	winText.setString("");
	winText.setCharacterSize(24);
	winText.setOrigin(winText.getGlobalBounds().width / 2, winText.getGlobalBounds().height / 2);
	winText.setPosition(WINDOW_WIDTH / 2, 650);
	winText.setFillColor(sf::Color::Red);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!playerMarkerTex[i][j].loadFromFile("TTT/pChip.png"))
			{
				std::cout << "Could not load image\n";
			}
			playerMarkerSpr[i][j].setTexture(playerMarkerTex[i][j]);
			playerMarkerSpr[i][j].scale(1, 1);
			playerMarkerSpr[i][j].setOrigin(playerMarkerSpr[i][j].getGlobalBounds().width / 2, playerMarkerSpr[i][j].getGlobalBounds().height / 2);

			if (!computerMarkerTex[i][j].loadFromFile("TTT/cChip.png"))
			{
				std::cout << "Could not load image\n";
			}
			computerMarkerSpr[i][j].setTexture(computerMarkerTex[i][j]);
			computerMarkerSpr[i][j].scale(1, 1);
			computerMarkerSpr[i][j].setOrigin(computerMarkerSpr[i][j].getGlobalBounds().width / 2, computerMarkerSpr[i][j].getGlobalBounds().height / 2);

		}
	}
	if (!boardTex.loadFromFile("TTT/board.png"))
	{
		std::cout << "Could not load image\n";
	}
	boardSpr.setTexture(boardTex);
	boardSpr.setOrigin(boardSpr.getGlobalBounds().width / 2, boardSpr.getGlobalBounds().height / 2);
	boardSpr.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!boardMarkerTex[i][j].loadFromFile("TTT/box.png"))
			{
				std::cout << "Could not load image\n";
			}
			boardMarkerSpr[i][j].setTexture(boardMarkerTex[i][j]);
			boardMarkerSpr[i][j].scale(1, 1);
			boardMarkerSpr[i][j].setOrigin(boardSpr.getGlobalBounds().width / 2, boardSpr.getGlobalBounds().height / 2);
		}
	}
	boardMarkerSpr[0][0].setPosition(657, 488);
	boardMarkerSpr[0][1].setPosition(770, 488);
	boardMarkerSpr[0][2].setPosition(887, 488);

	boardMarkerSpr[1][0].setPosition(657, 611);
	boardMarkerSpr[1][1].setPosition(770, 611);
	boardMarkerSpr[1][2].setPosition(887, 611);

	boardMarkerSpr[2][0].setPosition(657, 726);
	boardMarkerSpr[2][1].setPosition(770, 726);
	boardMarkerSpr[2][2].setPosition(887, 726);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			boardHighlight[i][j] = false;
			freeSpace[i][j] = true;
			if (!boardMarkerHTex[i][j].loadFromFile("TTT/boxH.png"))
			{
				std::cout << "Could not load image\n";
			}
			boardMarkerHSpr[i][j].setTexture(boardMarkerHTex[i][j]);
			boardMarkerHSpr[i][j].scale(1, 1);
			boardMarkerHSpr[i][j].setOrigin(boardSpr.getGlobalBounds().width / 2, boardSpr.getGlobalBounds().height / 2);
		}
	}
	boardMarkerHSpr[0][0].setPosition(657, 488);
	boardMarkerHSpr[0][1].setPosition(770, 488);
	boardMarkerHSpr[0][2].setPosition(887, 488);

	boardMarkerHSpr[1][0].setPosition(657, 611);
	boardMarkerHSpr[1][1].setPosition(770, 611);
	boardMarkerHSpr[1][2].setPosition(887, 611);

	boardMarkerHSpr[2][0].setPosition(657, 726);
	boardMarkerHSpr[2][1].setPosition(770, 726);
	boardMarkerHSpr[2][2].setPosition(887, 726);

	setPlayingState(true);
	// output each array element's value


	srand(time(NULL));
	whoGO = rand() % 2 + 1;
	if (whoGO == 1)
	{
		playerTurn = true;
		computerTurn = false;
	}
	else
	{
		computerTurn = true;
		playerTurn = false;
	}
	if (!backButton[0].loadFromFile("TTT/Back.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!backButton[1].loadFromFile("TTT/BackH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 2; i++)
	{
		backButtonSpr[i].setTexture(backButton[i]);
		backButtonSpr[i].setPosition(10, WINDOW_HEIGHT - 80);
	}
	if (!resetButton[0].loadFromFile("TTT/Reset.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!resetButton[1].loadFromFile("TTT/ResetH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 2; i++)
	{
		resetButtonSpr[i].setTexture(resetButton[i]);
		resetButtonSpr[i].setPosition(WINDOW_WIDTH - 105, WINDOW_HEIGHT - 80);
	}
}


TicTacToe::~TicTacToe()
{
}
void TicTacToe::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (back == true)
		state_current.change_state(state_manager_.state_ptr<GameBox>());
	
	

}

void TicTacToe::update(const sf::Time& delta)
{
	if (std::count(stillGo, std::end(stillGo), false) < 9)
	{
		setPlayingState(true);
		CheckBoardWin();
		CheckWinPlayer();
		CheckWinComputer();
	}
	else
		setPlayingState(false);

	if (!getPlayingState())
	{
		playerTurn = false;
		computerTurn = false;
		gameText.setString("Dang! Game is a bogey!");
		drawReset = true;
	}
	else
		drawReset = false;

	
}

void TicTacToe::pause()
{
	set_paused(true);
}

void TicTacToe::resume()
{
	set_paused(false);
}

void TicTacToe::handle_input(const sf::Time& delta)
{

	auto inputManager = state_manager_.get_input_manager();

	inputManager.giveStateManager(&state_manager_);
	inputManager.setRegionSize();
	inputManager.setwindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	sf::Vector2i windowO(view_main.getCenter().x - view_main.getSize().x / 2, view_main.getCenter().y - view_main.getSize().y / 2);

	mouse_pos.x = windowO.x + inputManager.get_mouse_x();
	mouse_pos.y = windowO.y + inputManager.get_mouse_y();

	if (inputManager.is_key_released(InputKey::escape))
	{
		state_manager_.quit();
	}
	if (getPlayingState())
	{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (boardMarkerSpr[i][j].getGlobalBounds().contains(mouse_pos))
					{
						boardHighlight[i][j] = true;
					}
					else
						boardHighlight[i][j] = false;
				}
			}
			if (getPlayingState() == true) {
				if (playerTurn == true)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (boardHighlight[i][j] == true)
							{
								if (inputManager.left_clicked())
								{
									if (whoGO == 1)
									{
										firstMove = false;
										playerMarkerSpr[i][j].setPosition(boardMarkerSpr[i][j].getPosition().x - playerMarkerSpr[i][j].getTextureRect().width * 1.7, boardMarkerSpr[i][j].getPosition().y - playerMarkerSpr[i][j].getTextureRect().height * 1.6);
										boardMarkerSpr[i][j].setTexture(playerMarkerTex[i][j]);
										board[i][j] = 1;
										CheckBoardWin();
										PlayerTurn();
										computer.placed = false;
										Sleep(600);
									}
								}
							}
						}
					}
				}
				else if (computerTurn == true)
				{
					if (whoGO == 2)
					{
						if (drawReset == false) {
							if (!computer.placed)
								AIMove();

						}
						Sleep(600);

					}
				}
			}
	}

	if (backButtonSpr[0].getGlobalBounds().contains(mouse_pos))
	{
		backH = true;
	}
	else
		backH = false;
	if (backH == true)
		if (inputManager.left_clicked())
			back = true;
	if (drawReset)
	{
		if (resetButtonSpr[0].getGlobalBounds().contains(mouse_pos))
			resetH = true;
		else
			resetH = false;
	}
	if (resetH)
	{
		if (inputManager.left_clicked())
		{
			Reset();
			Sleep(600);
		}
	}
}
void TicTacToe::render()
{

	sf::RenderWindow& window = state_manager_.get_render_window();
	window.draw(TTTbg_sprite);
	window.draw(logoSpr);
	window.draw(boardSpr);
	window.draw(messageText);
	if (drawReset == true)
	{
		gameText.setString("Dang! Game is a bogey!");
		gameText.setOrigin(gameText.getGlobalBounds().width / 2, gameText.getGlobalBounds().height / 2);
		gameText.setPosition(WINDOW_WIDTH / 2, 250);
	}
	else if (playerTurn == true)
	{
		gameText.setString("Hey... It's your turn!");
		gameText.setOrigin(gameText.getGlobalBounds().width / 2, gameText.getGlobalBounds().height / 2);
		gameText.setPosition(WINDOW_WIDTH / 2, 250);
	}
	else if (computerTurn == true)
	{
		gameText.setString("Let's wait for the computer to go..");
		gameText.setOrigin(gameText.getGlobalBounds().width / 2, gameText.getGlobalBounds().height / 2);
		gameText.setPosition(WINDOW_WIDTH / 2, 250);
	}

	window.draw(gameText);
	window.draw(winText);
	if (backH)
	{
		window.draw(backButtonSpr[1]);
	}
	else
		window.draw(backButtonSpr[0]);

	if (drawReset)
	{
		if (resetH)
			window.draw(resetButtonSpr[1]);
		else
			window.draw(resetButtonSpr[0]);
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
			{
				if (boardHighlight[i][j] != true)
				{
					if (freeSpace[i][j] == true)
						window.draw(boardMarkerSpr[i][j]);
				}
				else
				{
					if (freeSpace[i][j] == true)
						window.draw(boardMarkerHSpr[i][j]);
				}
			}
			else if (board[i][j] == 1)
				window.draw(playerMarkerSpr[i][j]);
			else if (board[i][j] == 2)
				window.draw(computerMarkerSpr[i][j]);
		}
	}
}
void TicTacToe::initGame()
{

}

void TicTacToe::randomPos()
{
	srand(time(NULL));
	Row = rand() % 3 + 1;
	Col = rand() % 3 + 1;
}

void TicTacToe::CheckBoard()
{
	if (!computer.placed)
		CRowOne();/*ROW 1 LOGIC*/
	if (!computer.placed)
		CRowTwo();/*ROW 2 LOGIC*/
	if (!computer.placed)
		CRowThree();/*ROW 3 LOGIC*/
	if (!computer.placed)
		CColOne();/*COL 1 LOGIC*/
	if (!computer.placed)
		CColTwo();/*COL 2 LOGIC*/
	if (!computer.placed)
		CColThree();/*COL 3 LOGIC*/
	if (!computer.placed)
		CDiagRight();/*DIAG RIGHT LOGIC*/
	if (!computer.placed)
		CDiagLeft();/*DIAG LEFT LOGIC*/
	computer.checked = true;

}

void TicTacToe::CRowOne()
{
	/*COMPUTER */
	if (board[0][0] == 2)
	{
		if (board[0][1] == 2)
		{
			if (board[0][2] == 0)
			{
				computerMarkerSpr[0][2].setPosition(boardMarkerSpr[0][2].getPosition().x - computerMarkerSpr[0][2].getTextureRect().width * 1.7, boardMarkerSpr[0][2].getPosition().y - computerMarkerSpr[0][2].getTextureRect().height * 1.6);
				boardMarkerSpr[0][2].setTexture(computerMarkerTex[0][2]);
				board[0][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][0] == 2)
	{
		if (board[0][2] == 2)
		{
			if (board[0][1] == 0)
			{
				computerMarkerSpr[0][1].setPosition(boardMarkerSpr[0][1].getPosition().x - computerMarkerSpr[0][1].getTextureRect().width * 1.7, boardMarkerSpr[0][1].getPosition().y - computerMarkerSpr[0][1].getTextureRect().height * 1.6);
				boardMarkerSpr[0][1].setTexture(computerMarkerTex[0][1]);
				board[0][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][1] == 2)
	{
		if (board[0][2] == 2)
		{
			if (board[0][0] == 0)
			{
				computerMarkerSpr[0][0].setPosition(boardMarkerSpr[0][0].getPosition().x - computerMarkerSpr[0][0].getTextureRect().width * 1.7, boardMarkerSpr[0][0].getPosition().y - computerMarkerSpr[0][0].getTextureRect().height * 1.6);
				boardMarkerSpr[0][0].setTexture(computerMarkerTex[0][0]);
				board[0][0] = 2;
				computer.placed = true;
			}
		}
	}

	if (board[0][0] == 1)
	{
		if (board[0][1] == 1)
		{
			if (board[0][2] == 0)
			{
				computerMarkerSpr[0][2].setPosition(boardMarkerSpr[0][2].getPosition().x - computerMarkerSpr[0][2].getTextureRect().width * 1.7, boardMarkerSpr[0][2].getPosition().y - computerMarkerSpr[0][2].getTextureRect().height * 1.6);
				boardMarkerSpr[0][2].setTexture(computerMarkerTex[0][2]);
				board[0][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][0] == 1)
	{
		if (board[0][2] == 1)
		{
			if (board[0][1] == 0)
			{
				computerMarkerSpr[0][1].setPosition(boardMarkerSpr[0][1].getPosition().x - computerMarkerSpr[0][1].getTextureRect().width * 1.7, boardMarkerSpr[0][1].getPosition().y - computerMarkerSpr[0][1].getTextureRect().height * 1.6);
				boardMarkerSpr[0][1].setTexture(computerMarkerTex[0][1]);
				board[0][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][1] == 1)
	{
		if (board[0][2] == 1)
		{
			if (board[0][0] == 0)
			{
				computerMarkerSpr[0][0].setPosition(boardMarkerSpr[0][0].getPosition().x - computerMarkerSpr[0][0].getTextureRect().width * 1.7, boardMarkerSpr[0][0].getPosition().y - computerMarkerSpr[0][0].getTextureRect().height * 1.6);
				boardMarkerSpr[0][0].setTexture(computerMarkerTex[0][0]);
				board[0][0] = 2;
				computer.placed = true;
			}
		}
	}
}

void TicTacToe::CRowTwo()
{
	/*Computer*/
	if (board[1][0] == 2)
	{
		if (board[1][1] == 2)
		{
			if (board[1][2] == 0)
			{
				computerMarkerSpr[1][2].setPosition(boardMarkerSpr[1][2].getPosition().x - computerMarkerSpr[1][2].getTextureRect().width * 1.7, boardMarkerSpr[1][2].getPosition().y - computerMarkerSpr[1][2].getTextureRect().height * 1.6);
				boardMarkerSpr[1][2].setTexture(computerMarkerTex[1][2]);
				board[1][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][0] == 2)
	{
		if (board[1][2] == 2)
		{
			if (board[1][1] == 0)
			{
				computerMarkerSpr[1][1].setPosition(boardMarkerSpr[1][1].getPosition().x - computerMarkerSpr[1][1].getTextureRect().width * 1.7, boardMarkerSpr[1][1].getPosition().y - computerMarkerSpr[1][1].getTextureRect().height * 1.6);
				boardMarkerSpr[1][1].setTexture(computerMarkerTex[1][1]);
				board[1][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][1] == 2)
	{
		if (board[1][2] == 2)
		{
			if (board[1][0] == 0)
			{
				computerMarkerSpr[1][0].setPosition(boardMarkerSpr[1][0].getPosition().x - computerMarkerSpr[1][0].getTextureRect().width * 1.7, boardMarkerSpr[1][0].getPosition().y - computerMarkerSpr[1][0].getTextureRect().height * 1.6);
				boardMarkerSpr[1][0].setTexture(computerMarkerTex[1][0]);
				board[1][0] = 2;
				computer.placed = true;
			}
		}
	}
	/*-------------------------------------------*/
	if (board[1][0] == 1)
	{
		if (board[1][1] == 1)
		{
			if (board[1][2] == 0)
			{
				computerMarkerSpr[1][2].setPosition(boardMarkerSpr[1][2].getPosition().x - computerMarkerSpr[1][2].getTextureRect().width * 1.7, boardMarkerSpr[1][2].getPosition().y - computerMarkerSpr[1][2].getTextureRect().height * 1.6);
				boardMarkerSpr[1][2].setTexture(computerMarkerTex[1][2]);
				board[1][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][0] == 1)
	{
		if (board[1][2] == 1)
		{
			if (board[1][1] == 0)
			{
				computerMarkerSpr[1][1].setPosition(boardMarkerSpr[1][1].getPosition().x - computerMarkerSpr[1][1].getTextureRect().width * 1.7, boardMarkerSpr[1][1].getPosition().y - computerMarkerSpr[1][1].getTextureRect().height * 1.6);
				boardMarkerSpr[1][1].setTexture(computerMarkerTex[1][1]);
				board[1][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][1] == 1)
	{
		if (board[1][2] == 1)
		{
			if (board[1][0] == 0)
			{
				computerMarkerSpr[1][0].setPosition(boardMarkerSpr[1][0].getPosition().x - computerMarkerSpr[1][0].getTextureRect().width * 1.7, boardMarkerSpr[1][0].getPosition().y - computerMarkerSpr[1][0].getTextureRect().height * 1.6);
				boardMarkerSpr[1][0].setTexture(computerMarkerTex[1][0]);
				board[1][0] = 2;
				computer.placed = true;
			}
		}
	}
}

void TicTacToe::CRowThree()
{
	/*Computer*/
	if (board[2][0] == 2)
	{
		if (board[2][1] == 2)
		{
			if (board[2][2] == 0)
			{
				computerMarkerSpr[2][2].setPosition(boardMarkerSpr[2][2].getPosition().x - computerMarkerSpr[2][2].getTextureRect().width * 1.7, boardMarkerSpr[2][2].getPosition().y - computerMarkerSpr[2][2].getTextureRect().height * 1.6);
				boardMarkerSpr[2][2].setTexture(computerMarkerTex[2][2]);
				board[2][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[2][0] == 2)
	{
		if (board[2][2] == 2)
		{
			if (board[2][1] == 0)
			{
				computerMarkerSpr[2][1].setPosition(boardMarkerSpr[2][1].getPosition().x - computerMarkerSpr[2][1].getTextureRect().width * 1.7, boardMarkerSpr[2][1].getPosition().y - computerMarkerSpr[2][1].getTextureRect().height * 1.6);
				boardMarkerSpr[2][1].setTexture(computerMarkerTex[2][1]);
				board[2][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[2][1] == 2)
	{
		if (board[2][2] == 2)
		{
			if (board[2][0] == 0)
			{
				computerMarkerSpr[2][0].setPosition(boardMarkerSpr[2][0].getPosition().x - computerMarkerSpr[2][0].getTextureRect().width * 1.7, boardMarkerSpr[2][0].getPosition().y - computerMarkerSpr[2][0].getTextureRect().height * 1.6);
				boardMarkerSpr[2][0].setTexture(computerMarkerTex[2][0]);
				board[2][0] = 2;
				computer.placed = true;
			}
		}
	}
	/*-----------------------*/
	if (board[2][0] == 1)
	{
		if (board[2][1] == 1)
		{
			if (board[2][2] == 0)
			{
				computerMarkerSpr[2][2].setPosition(boardMarkerSpr[2][2].getPosition().x - computerMarkerSpr[2][2].getTextureRect().width * 1.7, boardMarkerSpr[2][2].getPosition().y - computerMarkerSpr[2][2].getTextureRect().height * 1.6);
				boardMarkerSpr[2][2].setTexture(computerMarkerTex[2][2]);
				board[2][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[2][0] == 1)
	{
		if (board[2][2] == 1)
		{
			if (board[2][1] == 0)
			{
				computerMarkerSpr[2][1].setPosition(boardMarkerSpr[2][1].getPosition().x - computerMarkerSpr[2][1].getTextureRect().width * 1.7, boardMarkerSpr[2][1].getPosition().y - computerMarkerSpr[2][1].getTextureRect().height * 1.6);
				boardMarkerSpr[2][1].setTexture(computerMarkerTex[2][1]);
				board[2][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[2][1] == 1)
	{
		if (board[2][2] == 1)
		{
			if (board[2][0] == 0)
			{
				computerMarkerSpr[2][0].setPosition(boardMarkerSpr[2][0].getPosition().x - computerMarkerSpr[2][0].getTextureRect().width * 1.7, boardMarkerSpr[2][0].getPosition().y - computerMarkerSpr[2][0].getTextureRect().height * 1.6);
				boardMarkerSpr[2][0].setTexture(computerMarkerTex[2][0]);
				board[2][0] = 2;
				computer.placed = true;
			}
		}
	}
}

void TicTacToe::CColOne()
{
	/*Computer*/
	if (board[0][0] == 2)
	{
		if (board[1][0] == 2)
		{
			if (board[2][0] == 0)
			{
				computerMarkerSpr[2][0].setPosition(boardMarkerSpr[2][0].getPosition().x - computerMarkerSpr[2][0].getTextureRect().width * 1.7, boardMarkerSpr[2][0].getPosition().y - computerMarkerSpr[2][0].getTextureRect().height * 1.6);
				boardMarkerSpr[2][0].setTexture(computerMarkerTex[2][0]);
				board[2][0] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][0] == 2)
	{
		if (board[2][0] == 2)
		{
			if (board[1][0] == 0)
			{
				computerMarkerSpr[1][0].setPosition(boardMarkerSpr[1][0].getPosition().x - computerMarkerSpr[1][0].getTextureRect().width * 1.7, boardMarkerSpr[1][0].getPosition().y - computerMarkerSpr[1][0].getTextureRect().height * 1.6);
				boardMarkerSpr[1][0].setTexture(computerMarkerTex[1][0]);
				board[1][0] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][0] == 2)
	{
		if (board[2][0] == 2)
		{
			if (board[0][0] == 0)
			{
				computerMarkerSpr[0][0].setPosition(boardMarkerSpr[0][0].getPosition().x - computerMarkerSpr[0][0].getTextureRect().width * 1.7, boardMarkerSpr[0][0].getPosition().y - computerMarkerSpr[0][0].getTextureRect().height * 1.6);
				boardMarkerSpr[0][0].setTexture(computerMarkerTex[0][0]);
				board[0][0] = 2;
				computer.placed = true;
			}
		}
	}
	/*------------------------------*/
	if (board[0][0] == 1)
	{
		if (board[1][0] == 1)
		{
			if (board[2][0] == 0)
			{
				computerMarkerSpr[2][0].setPosition(boardMarkerSpr[2][0].getPosition().x - computerMarkerSpr[2][0].getTextureRect().width * 1.7, boardMarkerSpr[2][0].getPosition().y - computerMarkerSpr[2][0].getTextureRect().height * 1.6);
				boardMarkerSpr[2][0].setTexture(computerMarkerTex[2][0]);
				board[2][0] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][0] == 1)
	{
		if (board[2][0] == 1)
		{
			if (board[1][0] == 0)
			{
				computerMarkerSpr[1][0].setPosition(boardMarkerSpr[1][0].getPosition().x - computerMarkerSpr[1][0].getTextureRect().width * 1.7, boardMarkerSpr[1][0].getPosition().y - computerMarkerSpr[1][0].getTextureRect().height * 1.6);
				boardMarkerSpr[1][0].setTexture(computerMarkerTex[1][0]);
				board[1][0] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][0] == 1)
	{
		if (board[2][0] == 1)
		{
			if (board[0][0] == 0)
			{
				computerMarkerSpr[0][0].setPosition(boardMarkerSpr[0][0].getPosition().x - computerMarkerSpr[0][0].getTextureRect().width * 1.7, boardMarkerSpr[0][0].getPosition().y - computerMarkerSpr[0][0].getTextureRect().height * 1.6);
				boardMarkerSpr[0][0].setTexture(computerMarkerTex[0][0]);
				board[0][0] = 2;
				computer.placed = true;
			}
		}
	}
}

void TicTacToe::CColTwo()
{
	/*COMPUTER*/
	if (board[0][1] == 2)
	{
		if (board[1][1] == 2)
		{
			if (board[2][1] == 0)
			{
				computerMarkerSpr[2][1].setPosition(boardMarkerSpr[2][1].getPosition().x - computerMarkerSpr[2][1].getTextureRect().width * 1.7, boardMarkerSpr[2][1].getPosition().y - computerMarkerSpr[2][1].getTextureRect().height * 1.6);
				boardMarkerSpr[2][1].setTexture(computerMarkerTex[2][1]);
				board[2][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][1] == 2)
	{
		if (board[2][1] == 2)
		{
			if (board[1][1] == 0)
			{
				computerMarkerSpr[1][1].setPosition(boardMarkerSpr[1][1].getPosition().x - computerMarkerSpr[1][1].getTextureRect().width * 1.7, boardMarkerSpr[1][1].getPosition().y - computerMarkerSpr[1][1].getTextureRect().height * 1.6);
				boardMarkerSpr[1][1].setTexture(computerMarkerTex[1][1]);
				board[1][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][1] == 2)
	{
		if (board[2][1] == 2)
		{
			if (board[0][1] == 0)
			{
				computerMarkerSpr[0][1].setPosition(boardMarkerSpr[0][1].getPosition().x - computerMarkerSpr[0][1].getTextureRect().width * 1.7, boardMarkerSpr[0][1].getPosition().y - computerMarkerSpr[0][1].getTextureRect().height * 1.6);
				boardMarkerSpr[0][1].setTexture(computerMarkerTex[0][1]);
				board[0][1] = 2;
				computer.placed = true;
			}
		}
	}
	/*-----------------------*/
	if (board[0][1] == 1)
	{
		if (board[1][1] == 1)
		{
			if (board[2][1] == 0)
			{
				computerMarkerSpr[2][1].setPosition(boardMarkerSpr[2][1].getPosition().x - computerMarkerSpr[2][1].getTextureRect().width * 1.7, boardMarkerSpr[2][1].getPosition().y - computerMarkerSpr[2][1].getTextureRect().height * 1.6);
				boardMarkerSpr[2][1].setTexture(computerMarkerTex[2][1]);
				board[2][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][1] == 1)
	{
		if (board[2][1] == 1)
		{
			if (board[1][1] == 0)
			{
				computerMarkerSpr[1][1].setPosition(boardMarkerSpr[1][1].getPosition().x - computerMarkerSpr[1][1].getTextureRect().width * 1.7, boardMarkerSpr[1][1].getPosition().y - computerMarkerSpr[1][1].getTextureRect().height * 1.6);
				boardMarkerSpr[1][1].setTexture(computerMarkerTex[1][1]);
				board[1][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][1] == 1)
	{
		if (board[2][1] == 1)
		{
			if (board[0][1] == 0)
			{
				computerMarkerSpr[0][1].setPosition(boardMarkerSpr[0][1].getPosition().x - computerMarkerSpr[0][1].getTextureRect().width * 1.7, boardMarkerSpr[0][1].getPosition().y - computerMarkerSpr[0][1].getTextureRect().height * 1.6);
				boardMarkerSpr[0][1].setTexture(computerMarkerTex[0][1]);
				board[0][1] = 2;
				computer.placed = true;
			}
		}
	}
}

void TicTacToe::CColThree()
{
	/*COMPUTER*/
	if (board[0][2] == 2)
	{
		if (board[1][2] == 2)
		{
			if (board[2][2] == 0)
			{
				computerMarkerSpr[2][2].setPosition(boardMarkerSpr[2][2].getPosition().x - computerMarkerSpr[2][2].getTextureRect().width * 1.7, boardMarkerSpr[2][2].getPosition().y - computerMarkerSpr[2][2].getTextureRect().height * 1.6);
				boardMarkerSpr[2][2].setTexture(computerMarkerTex[2][2]);
				board[2][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][2] == 2)
	{
		if (board[2][2] == 2)
		{
			if (board[1][2] == 0)
			{
				computerMarkerSpr[1][2].setPosition(boardMarkerSpr[1][2].getPosition().x - computerMarkerSpr[1][2].getTextureRect().width * 1.7, boardMarkerSpr[1][2].getPosition().y - computerMarkerSpr[1][2].getTextureRect().height * 1.6);
				boardMarkerSpr[1][2].setTexture(computerMarkerTex[1][2]);
				board[1][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][2] == 2)
	{
		if (board[2][2] == 2)
		{
			if (board[0][2] == 0)
			{
				computerMarkerSpr[0][2].setPosition(boardMarkerSpr[0][2].getPosition().x - computerMarkerSpr[0][2].getTextureRect().width * 1.7, boardMarkerSpr[0][2].getPosition().y - computerMarkerSpr[0][2].getTextureRect().height * 1.6);
				boardMarkerSpr[0][2].setTexture(computerMarkerTex[0][2]);
				board[0][2] = 2;
				computer.placed = true;
			}
		}
	}
	/*------------------------------*/
	if (board[0][2] == 1)
	{
		if (board[1][2] == 1)
		{
			if (board[2][2] == 0)
			{
				computerMarkerSpr[2][2].setPosition(boardMarkerSpr[2][2].getPosition().x - computerMarkerSpr[2][2].getTextureRect().width * 1.7, boardMarkerSpr[2][2].getPosition().y - computerMarkerSpr[2][2].getTextureRect().height * 1.6);
				boardMarkerSpr[2][2].setTexture(computerMarkerTex[2][2]);
				board[2][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][2] == 1)
	{
		if (board[2][2] == 1)
		{
			if (board[1][2] == 0)
			{
				computerMarkerSpr[1][2].setPosition(boardMarkerSpr[1][2].getPosition().x - computerMarkerSpr[1][2].getTextureRect().width * 1.7, boardMarkerSpr[1][2].getPosition().y - computerMarkerSpr[1][2].getTextureRect().height * 1.6);
				boardMarkerSpr[1][2].setTexture(computerMarkerTex[1][2]);
				board[1][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][2] == 1)
	{
		if (board[2][2] == 1)
		{
			if (board[0][2] == 0)
			{
				computerMarkerSpr[0][2].setPosition(boardMarkerSpr[0][2].getPosition().x - computerMarkerSpr[0][2].getTextureRect().width * 1.7, boardMarkerSpr[0][2].getPosition().y - computerMarkerSpr[0][2].getTextureRect().height * 1.6);
				boardMarkerSpr[0][2].setTexture(computerMarkerTex[0][2]);
				board[0][2] = 2;
				computer.placed = true;
			}
		}
	}
}

void TicTacToe::CDiagRight()
{
	/*COMPUTER*/
	if (board[0][0] == 2)
	{
		if (board[1][1] == 2)
		{
			if (board[2][2] == 0)
			{
				computerMarkerSpr[2][2].setPosition(boardMarkerSpr[2][2].getPosition().x - computerMarkerSpr[2][2].getTextureRect().width * 1.7, boardMarkerSpr[2][2].getPosition().y - computerMarkerSpr[2][2].getTextureRect().height * 1.6);
				boardMarkerSpr[2][2].setTexture(computerMarkerTex[2][2]);
				board[2][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][0] == 2)
	{
		if (board[2][2] == 2)
		{
			if (board[1][1] == 0)
			{
				computerMarkerSpr[1][1].setPosition(boardMarkerSpr[1][1].getPosition().x - computerMarkerSpr[1][1].getTextureRect().width * 1.7, boardMarkerSpr[1][1].getPosition().y - computerMarkerSpr[1][1].getTextureRect().height * 1.6);
				boardMarkerSpr[1][1].setTexture(computerMarkerTex[1][1]);
				board[1][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][1] == 2)
	{
		if (board[2][2] == 2)
		{
			if (board[0][0] == 0)
			{
				computerMarkerSpr[0][0].setPosition(boardMarkerSpr[0][0].getPosition().x - computerMarkerSpr[0][0].getTextureRect().width * 1.7, boardMarkerSpr[0][0].getPosition().y - computerMarkerSpr[0][0].getTextureRect().height * 1.6);
				boardMarkerSpr[0][0].setTexture(computerMarkerTex[0][0]);
				board[0][0] = 2;
				computer.placed = true;
			}
		}
	}
	/*-------------------------------------------*/
	if (board[0][0] == 1)
	{
		if (board[1][1] == 1)
		{
			if (board[2][2] == 0)
			{
				computerMarkerSpr[2][2].setPosition(boardMarkerSpr[2][2].getPosition().x - computerMarkerSpr[2][2].getTextureRect().width * 1.7, boardMarkerSpr[2][2].getPosition().y - computerMarkerSpr[2][2].getTextureRect().height * 1.6);
				boardMarkerSpr[2][2].setTexture(computerMarkerTex[2][2]);
				board[2][2] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][0] == 1)
	{
		if (board[2][2] == 1)
		{
			if (board[1][1] == 0)
			{
				computerMarkerSpr[1][1].setPosition(boardMarkerSpr[1][1].getPosition().x - computerMarkerSpr[1][1].getTextureRect().width * 1.7, boardMarkerSpr[1][1].getPosition().y - computerMarkerSpr[1][1].getTextureRect().height * 1.6);
				boardMarkerSpr[1][1].setTexture(computerMarkerTex[1][1]);
				board[1][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][1] == 1)
	{
		if (board[2][2] == 1)
		{
			if (board[0][0] == 0)
			{
				computerMarkerSpr[0][0].setPosition(boardMarkerSpr[0][0].getPosition().x - computerMarkerSpr[0][0].getTextureRect().width * 1.7, boardMarkerSpr[0][0].getPosition().y - computerMarkerSpr[0][0].getTextureRect().height * 1.6);
				boardMarkerSpr[0][0].setTexture(computerMarkerTex[0][0]);
				board[0][0] = 2;
				computer.placed = true;
			}
		}
	}
}

void TicTacToe::CDiagLeft()
{
	/*COMPUTER*/
	if (board[0][2] == 2)
	{
		if (board[1][1] == 2)
		{
			if (board[2][0] == 0)
			{
				computerMarkerSpr[2][0].setPosition(boardMarkerSpr[2][0].getPosition().x - computerMarkerSpr[2][0].getTextureRect().width * 1.7, boardMarkerSpr[2][0].getPosition().y - computerMarkerSpr[2][0].getTextureRect().height * 1.6);
				boardMarkerSpr[2][0].setTexture(computerMarkerTex[2][0]);
				board[2][0] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][2] == 2)
	{
		if (board[2][0] == 2)
		{
			if (board[1][1] == 0)
			{
				computerMarkerSpr[1][1].setPosition(boardMarkerSpr[1][1].getPosition().x - computerMarkerSpr[1][1].getTextureRect().width * 1.7, boardMarkerSpr[1][1].getPosition().y - computerMarkerSpr[1][1].getTextureRect().height * 1.6);
				boardMarkerSpr[1][1].setTexture(computerMarkerTex[1][1]);
				board[1][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][1] == 2)
	{
		if (board[2][0] == 2)
		{
			if (board[0][2] == 0)
			{
				computerMarkerSpr[0][2].setPosition(boardMarkerSpr[0][2].getPosition().x - computerMarkerSpr[0][2].getTextureRect().width * 1.7, boardMarkerSpr[0][2].getPosition().y - computerMarkerSpr[0][2].getTextureRect().height * 1.6);
				boardMarkerSpr[0][2].setTexture(computerMarkerTex[0][2]);
				board[0][2] = 2;
				computer.placed = true;
			}
		}
	}
	/*------------------------*/
	if (board[0][2] == 1)
	{
		if (board[1][1] == 1)
		{
			if (board[2][0] == 0)
			{
				computerMarkerSpr[2][0].setPosition(boardMarkerSpr[2][0].getPosition().x - computerMarkerSpr[2][0].getTextureRect().width * 1.7, boardMarkerSpr[2][0].getPosition().y - computerMarkerSpr[2][0].getTextureRect().height * 1.6);
				boardMarkerSpr[2][0].setTexture(computerMarkerTex[2][0]);
				board[2][0] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[0][2] == 1)
	{
		if (board[2][0] == 1)
		{
			if (board[1][1] == 0)
			{
				computerMarkerSpr[1][1].setPosition(boardMarkerSpr[1][1].getPosition().x - computerMarkerSpr[1][1].getTextureRect().width * 1.7, boardMarkerSpr[1][1].getPosition().y - computerMarkerSpr[1][1].getTextureRect().height * 1.6);
				boardMarkerSpr[1][1].setTexture(computerMarkerTex[1][1]);
				board[1][1] = 2;
				computer.placed = true;
			}
		}
	}
	if (board[1][1] == 1)
	{
		if (board[2][0] == 1)
		{
			if (board[0][2] == 0)
			{
				computerMarkerSpr[0][2].setPosition(boardMarkerSpr[0][2].getPosition().x - computerMarkerSpr[0][2].getTextureRect().width * 1.7, boardMarkerSpr[0][2].getPosition().y - computerMarkerSpr[0][2].getTextureRect().height * 1.6);
				boardMarkerSpr[0][2].setTexture(computerMarkerTex[0][2]);
				board[0][2] = 2;
				computer.placed = true;
			}
		}
	}
}

void TicTacToe::CheckBoardWin()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
			{
				if (i == 0)
				{
					if (j == 0)
						stillGo[0] = true;
					if (j == 1)
						stillGo[1] = true;
					if (j == 2)
						stillGo[2] = true;
				}
				if (i == 1)
				{
					if (j == 0)
						stillGo[3] = true;
					if (j == 1)
						stillGo[4] = true;
					if (j == 2)
						stillGo[5] = true;
				}
				if (i == 2)
				{
					if (j == 0)
						stillGo[6] = true;
					if (j == 1)
						stillGo[7] = true;
					if (j == 2)
						stillGo[8] = true;
				}
			}
			else
			{
				if (i == 0)
				{
					if (j == 0)
						stillGo[0] = false;
					if (j == 1)
						stillGo[1] = false;
					if (j == 2)
						stillGo[2] = false;
				}
				if (i == 1)
				{
					if (j == 0)
						stillGo[3] = false;
					if (j == 1)
						stillGo[4] = false;
					if (j == 2)
						stillGo[5] = false;
				}
				if (i == 2)
				{
					if (j == 0)
						stillGo[6] = false;
					if (j == 1)
						stillGo[7] = false;
					if (j == 2)
						stillGo[8] = false;
				}
			}
		}
	}

}

void TicTacToe::CheckWinPlayer()
{
	if (board[0][0] == 1)
	{
		if (board[0][1] == 1)
		{
			if (board[0][2] == 1)
			{
				winText.setString("Player WINS!   - ROW 1");
				setWinState(true);
				setPlayingState(false);
			}
		}
	}
	if (board[1][0] == 1)
	{
		if (board[1][1] == 1)
		{
			if (board[1][2] == 1)
			{
				winText.setString("Player WINS!   - ROW 2");
				setWinState(true);
				setPlayingState(false);
			}
		}
	}
	if (board[2][0] == 1)
	{
		if (board[2][1] == 1)
		{
			if (board[2][2] == 1)
			{
				winText.setString("Player WINS!   - ROW 3");
				setWinState(true);
				setPlayingState(false);
			}
		}
	}
	if (board[0][0] == 1)
	{
		if (board[1][0] == 1)
		{
			if (board[2][0] == 1)
			{
				winText.setString("Player WINS!   - COLUMN 1");
				setWinState(true);
				setPlayingState(false);
			}
		}
	}
	if (board[0][1] == 1)
	{
		if (board[1][1] == 1)
		{
			if (board[2][1] == 1)
			{
				winText.setString("Player WINS!   - COLUMN 2");
				setWinState(true);
				setPlayingState(false);
			}
		}
	}
	if (board[0][2] == 1)
	{
		if (board[1][2] == 1)
		{
			if (board[2][2] == 1)
			{
				winText.setString("Player WINS!   - COLUMN 3");
				setWinState(true);
				setPlayingState(false);
			}
		}
	}
	if (board[0][0] == 1)
	{
		if (board[1][1] == 1)
		{
			if (board[2][2] == 1)
			{
				winText.setString("Player WINS!   - Diag, Down right");
				setWinState(true);
				setPlayingState(false);
			}
		}
	}
	if (board[2][0] == 1)
	{
		if (board[1][1] == 1)
		{

			if (board[0][2] == 1)
			{
				cout << "\nPlayer WINS!  - Diag, Down left";
				winText.setString("Player WINS!   - Diag, Down left");
				setWinState(true);
				setPlayingState(false);
			}
		}
	}
	if (getPlayingState() == false)
	{
		drawReset = true;
	}
}

void TicTacToe::CheckWinComputer()
{
	/*COMPUTER LOGIC*/
	if (board[0][0] == 2)
	{
		if (board[0][1] == 2)
		{
			if (board[0][2] == 2)
			{
				winText.setString("Computer WINS!   - ROW 1");
				setWinState(false);
				setPlayingState(false);
			}
		}
	}
	if (board[1][0] == 2)
	{
		if (board[1][1] == 2)
		{
			if (board[1][2] == 2)
			{
				winText.setString("Computer WINS!   - ROW 2");
				setWinState(false);
				setPlayingState(false);
			}
		}
	}
	if (board[2][0] == 2)
	{
		if (board[2][1] == 2)
		{
			if (board[2][2] == 2)
			{
				winText.setString("Computer WINS!   - ROW 3");
				setWinState(false);
				setPlayingState(false);
			}
		}
	}
	if (board[0][0] == 2)
	{
		if (board[1][0] == 2)
		{
			if (board[2][0] == 2)
			{
				winText.setString("Computer WINS!   - COLUMN 1");
				setWinState(false);
				setPlayingState(false);
			}
		}
	}
	if (board[0][1] == 2)
	{
		if (board[1][1] == 2)
		{
			if (board[2][1] == 2)
			{
				winText.setString("Computer WINS!   - COLUMN 2");
				setWinState(false);
				setPlayingState(false);
			}
		}
	}
	if (board[0][2] == 2)
	{
		if (board[1][2] == 2)
		{
			if (board[2][2] == 2)
			{
				winText.setString("Computer WINS!   - COLUMN 3");
				setWinState(false);
				setPlayingState(false);
			}
		}
	}
	if (board[0][0] == 2)
	{
		if (board[1][1] == 2)
		{
			if (board[2][2] == 2)
			{
				winText.setString("Computer WINS!   - Diag, Down right");
				setWinState(false);
				setPlayingState(false);
			}
		}
	}
	if (board[0][2] == 2)
	{
		if (board[1][1] == 2)
		{

			if (board[2][0] == 2)
			{
				winText.setString("Computer WINS!   - Diag, Down left");
				setWinState(false);
				setPlayingState(false);
			}
		}
	}
	if (getPlayingState() == false)
	{
		drawReset = true;
	}
}

void TicTacToe::AIMove()
{

	computer.placed = false;
	if (firstMove)
	{
		randomPos();
		board[Row - 1][Col - 1] = 2;
		computerMarkerSpr[Row - 1][Col - 1].setPosition(boardMarkerSpr[Row - 1][Col - 1].getPosition().x - computerMarkerSpr[Row - 1][Col - 1].getTextureRect().width * 1.7, boardMarkerSpr[Row - 1][Col - 1].getPosition().y - computerMarkerSpr[Row - 1][Col - 1].getTextureRect().height * 1.6);
		boardMarkerSpr[Row - 1][Col - 1].setTexture(computerMarkerTex[Row - 1][Col - 1]);
		firstMove = false;
		computer.placed = true;
	}
	else if (spacesLeft == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == 0)
				{
					computerMarkerSpr[i][j].setPosition(boardMarkerSpr[i][j].getPosition().x - computerMarkerSpr[i][j].getTextureRect().width * 1.7, boardMarkerSpr[i][j].getPosition().y - computerMarkerSpr[i][j].getTextureRect().height * 1.6);
					boardMarkerSpr[i][j].setTexture(computerMarkerTex[i][j]);
					board[i][j] = 2;
					computer.placed = true;
				}

			}
		}
	}
	else
	{
		CheckBoard();
		if (!computer.placed)
		{
			randomPos();
			do
			{
				randomPos();
			} while (board[Row - 1][Col - 1] == 1 || board[Row - 1][Col - 1] == 2);

			if (board[Row - 1][Col - 1] != 1)
			{
				if (board[Row - 1][Col - 1] != 2)
				{
					computerMarkerSpr[Row - 1][Col - 1].setPosition(boardMarkerSpr[Row - 1][Col - 1].getPosition().x - computerMarkerSpr[Row - 1][Col - 1].getTextureRect().width * 1.7, boardMarkerSpr[Row - 1][Col - 1].getPosition().y - computerMarkerSpr[Row - 1][Col - 1].getTextureRect().height * 1.6);
					boardMarkerSpr[Row - 1][Col - 1].setTexture(computerMarkerTex[Row - 1][Col - 1]);
					board[Row - 1][Col - 1] = 2;
					computer.checked = false;
				}
			}
			computer.placed = true;
		}
	}
	spacesLeft--;
	playerTurn = true;
	computerTurn = false;
	whoGO = 1;
}

void TicTacToe::PlayerTurn()
{
	spacesLeft--;
	computerTurn = true;
	playerTurn = false;
	whoGO = 2;
}

void TicTacToe::Playing()
{

	if (getPlayingState())
	{
		if (std::count(stillGo, std::end(stillGo), false) < 9)
		{
			if (whoGO == 1)
			{
				cout << "\nPlayer Turn... \n" << endl;
				whoGO = 2;
				PlayerTurn();

			}
			else if (whoGO == 2)
			{
				cout << "\nComputer Turn... \n" << endl;
				whoGO = 1;
				AIMove();
				cout << "\Okay, it's your go. \n" << endl;
			}
		}
		else
		{
			cout << "\nGame is a bogey!\n";
			system("pause");
		}
	}
	else
	{
		system("pause");
	}

}

void TicTacToe::Reset()
{

	firstMove = true;
	computer.placed = false;
	computer.checked = false;
	drawReset = false;
	resetH = false;
	computer.moveCount = 0;
	spacesLeft = 9;
	for (int i = 0; i < 9; i++)
	{
		stillGo[i] = true;
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = 0;
	whoGO = 0;
	srand(time(NULL));
	whoGO = rand() % 2 + 1;
	winText.setString("");
	if (whoGO == 1)
	{
		playerTurn = true;
		computerTurn = false;
	}
	else
	{
		computerTurn = true;
		playerTurn = false;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			boardMarkerSpr[i][j].setTexture(boardMarkerTex[i][j]);
			boardMarkerSpr[i][j].scale(1, 1);
			boardMarkerSpr[i][j].setOrigin(boardSpr.getGlobalBounds().width / 2, boardSpr.getGlobalBounds().height / 2);
		}
	}
	boardMarkerSpr[0][0].setPosition(657, 488);
	boardMarkerSpr[0][1].setPosition(770, 488);
	boardMarkerSpr[0][2].setPosition(887, 488);

	boardMarkerSpr[1][0].setPosition(657, 611);
	boardMarkerSpr[1][1].setPosition(770, 611);
	boardMarkerSpr[1][2].setPosition(887, 611);

	boardMarkerSpr[2][0].setPosition(657, 726);
	boardMarkerSpr[2][1].setPosition(770, 726);
	boardMarkerSpr[2][2].setPosition(887, 726);

	
}
