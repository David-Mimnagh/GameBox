
#include "ConnectFour.h"
ConnectFour::ConnectFour(StateManager& state_manager) : AbstractState(state_manager)
{
	player1.win = false;
	player1.tex.loadFromFile("C4/player1.png");
	player1.spr.setTexture(player1.tex);
	player1.spr.setOrigin(player1.spr.getGlobalBounds().width / 2, player1.spr.getGlobalBounds().height / 2);
	player1HTex.loadFromFile("C4/player1-H.png");

	player2.win = false;
	player2.tex.loadFromFile("C4/player2.png");
	player2.spr.setTexture(player2.tex);
	player2.spr.setOrigin(player2.spr.getGlobalBounds().width / 2, player2.spr.getGlobalBounds().height / 2);
	player2HTex.loadFromFile("C4/player2-H.png");

	for (int row = 0; row < 6; row++)
	{
		int additionBot = row * 80;
		for (int i = 0; i < 7; i++)
		{
			int additionRight = i * 90;
			circle[row][i].setPosition(348 + additionRight, 90 + additionBot);
			circle[row][i].setRadius(36.0);
			blankTex.loadFromFile("C4/blank.png");
			circle[row][i].setTexture(&blankTex);
			//circle[row][i].setFillColor(sf::Color(sf::Color::Transparent));
			/*circle[row][i].setFillColor(sf::Color(255, 0, 0, 255));*/
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			board[i][j] = 0;
			boardHighlight[i][j] = false;
		}
	}
	win = false;
	backHighlight = false;
	drawReset = false;
	view_main.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	view_main.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

	// zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
	view_main.zoom(1.0f);

	// define a centered viewport, with half the size of the window
	view_main.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
	// Load from a font file on disk
	if (!MainFont.loadFromFile("MavenPro-Regular.ttf"))
	{
		cout << "NO font found.";
	}

	messageText.setFont(MainFont);
	messageText.setString("Welcome to GameBox - Connect 4.");
	messageText.setCharacterSize(18);
	messageText.setOrigin(messageText.getGlobalBounds().width / 2, messageText.getGlobalBounds().height / 2);
	messageText.setPosition(WINDOW_WIDTH / 2, 572);
	messageText.setFillColor(sf::Color::Red);

	player1_turn = true;
	gameText.setFont(MainFont);
	gameText.setString("Player 1- It's your turn");
	gameText.setOrigin(gameText.getGlobalBounds().width / 2, gameText.getGlobalBounds().height / 2 - 50);
	gameText.setCharacterSize(28);
	gameText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
	gameText.setFillColor(sf::Color::Red);

	if (!C4background.loadFromFile("C4/board.png"))
	{
		std::cout << "Could not load image\n";
	}
	C4bg_sprite.setTexture(C4background);
	if (!logoTex.loadFromFile("Logo.png"))
	{
		std::cout << "Could not load image\n";
	}
	logoSpr.setTexture(logoTex);
	logoSpr.setOrigin(logoSpr.getGlobalBounds().width / 2, logoSpr.getGlobalBounds().height / 2);
	logoSpr.setPosition(WINDOW_WIDTH / 2, 50);
	if (!backButton[0].loadFromFile("GG/Back.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!backButton[1].loadFromFile("GG/BackH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 2; i++)
	{
		backButtonSpr[i].setTexture(backButton[i]);
		backButtonSpr[i].setPosition(10, WINDOW_HEIGHT - 90);
	}

	if (!resetButton[0].loadFromFile("GG/Reset.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!resetButton[1].loadFromFile("GG/ResetH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 2; i++)
	{
		resetButtonSpr[i].setTexture(resetButton[i]);
		resetButtonSpr[i].setPosition(WINDOW_WIDTH - 160, WINDOW_HEIGHT - 90);
	}
	initGame();
}

ConnectFour::~ConnectFour()
{
}

void ConnectFour::pause()
{
	set_paused(true);
}

void ConnectFour::resume()
{
	set_paused(false);
}

void ConnectFour::initGame()
{
}

void ConnectFour::Reset()
{
	player1.win = false;
	player2.win = false;
	gameText.setString("Player 1- It's your turn");
	player1_turn = true;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
				boardHighlight[i][j] = false;


				board[i][j] = 0;

		}
	}
}

void ConnectFour::update(const sf::Time & delta)
{
	if (player1.win || player2.win)
		drawReset = true;
}

void ConnectFour::render()
{
	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view
	window.draw(C4bg_sprite);
	window.draw(logoSpr);
	window.draw(messageText);

	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (board[i][j] == 0)
			{
				if (boardHighlight[i][j]) {
					if (player1_turn)
						circle[i][j].setTexture(&player1HTex);
					else
						circle[i][j].setTexture(&player2HTex);
				}
				else
					circle[i][j].setTexture(&blankTex);
			}
			else if (board[i][j] == 1)
				circle[i][j].setTexture(&player1.tex);
			else if (board[i][j] == 2)
				circle[i][j].setTexture(&player2.tex);


			window.draw(circle[i][j]);
		}
	}
	if (win)
		gameText.setString("YOU WIN!");


	window.draw(gameText);


	if (drawReset)
	{
		if (resetHighlight)
		{
			window.draw(resetButtonSpr[1]);
		}
		else
			window.draw(resetButtonSpr[0]);
	}

	if (backHighlight)
	{
		window.draw(backButtonSpr[1]);
	}
	else
		window.draw(backButtonSpr[0]);
}
void ConnectFour::placeChip(int i, int j)
{
	int placeOn = -1;
	if (player1_turn)
	{

		
		if (i != 5)
		{
			if (board[0][j] == 0)
				placeOn = 0;
			if (board[1][j] == 0)
				placeOn = 1;
			if (board[2][j] == 0)
				placeOn = 2;
			if (board[3][j] == 0)
				placeOn = 3;
			if (board[4][j] == 0)
				placeOn = 4;
		}
		else
		{
			if (board[i][j] == 0)
			{
				placeOn = 5;
				board[i][j] = 1;
				CheckVertical(i,j);
				CheckHorizontal(i, j);
				CheckDiag(i, j);
				circle[i][j].setTexture(&player1.tex);
				boardHighlight[i][j] = false;
			}
		}

		if (placeOn > -1 )
		{
			if (placeOn == 4)
			{
				if (board[5][j] == 0)
				{
					board[5][j] = 1;
					CheckVertical(i,j);
					CheckHorizontal(i, j);
					CheckDiag(i, j);
					circle[5][j].setTexture(&player1.tex);
					boardHighlight[i][j] = false;
				}
				else
				{
					board[placeOn][j] = 1;
					CheckVertical(i,j);
					CheckHorizontal(i, j);
					CheckDiag(i, j);
					circle[placeOn][j].setTexture(&player1.tex);
					boardHighlight[i][j] = false;
				}
			}
			else
			{

				board[placeOn][j] = 1;
				CheckVertical(i,j);
				CheckHorizontal(i, j);
				CheckDiag(i, j);
				circle[placeOn][j].setTexture(&player1.tex);
				boardHighlight[i][j] = false;
			}

		}
		else
		{
			//CAN'T PLACE IN THIS ROW#
			gameText.setString("CAN'T PLACE ON THIS ROW!");
		}
	}
	else if (!player1_turn)
	{
		if (i != 5)
		{
			if (board[0][j] == 0)
				placeOn = 0;
			if (board[1][j] == 0)
				placeOn = 1;
			if (board[2][j] == 0)
				placeOn = 2;
			if (board[3][j] == 0)
				placeOn = 3;
			if (board[4][j] == 0)
				placeOn = 4;

		}
		else
		{
			if (board[i][j] == 0)
			{
				placeOn = 5;
				board[i][j] = 2;
				CheckVertical(i,j);
				CheckHorizontal(i, j);
				CheckDiag(i, j);
				circle[i][j].setTexture(&player2.tex);
				boardHighlight[i][j] = false;
			}
		}

		if (placeOn > -1)
		{
			if (placeOn == 4)
			{
				if (board[5][j] == 0)
				{
					board[5][j] = 2;
					CheckVertical(i,j);
					CheckHorizontal(i, j);
					CheckDiag(i, j);
					circle[5][j].setTexture(&player2.tex);
					boardHighlight[i][j] = false;
				}
				else
				{
					board[placeOn][j] = 2;
					CheckVertical(i,j);
					CheckHorizontal(i, j);
					CheckDiag(i, j);
					circle[placeOn][j].setTexture(&player2.tex);
					boardHighlight[i][j] = false;
				}
			}
			else
			{

				board[placeOn][j] = 2;
				CheckVertical(i,j);
				CheckHorizontal(i, j);
				CheckDiag(i, j);
				circle[placeOn][j].setTexture(&player2.tex);
				boardHighlight[i][j] = false;
			}

		}
		else
		{
			//CAN'T PLACE IN THIS ROW#
			gameText.setString("CAN'T PLACE ON THIS ROW!");
		}
	}

	player1_turn = !player1_turn;
}
void ConnectFour::CheckVertical(int rowNum, int colNum)
{
		if (player1_turn) 
		{
			if (rowNum <= 2)
			{
				if (board[rowNum + 1][colNum] == 1)
					if (board[rowNum + 2][colNum] == 1)
						if (board[rowNum + 3][colNum] == 1)
						{
							player1.win = true;
						}
			}
		}
		else
		{
			if (rowNum <= 2)
			{
				if (board[rowNum + 1][colNum] == 2)
					if (board[rowNum + 2][colNum] == 2)
						if (board[rowNum + 3][colNum] == 2)
						{
							player2.win = true;
						}
			}
		}
	
}
void ConnectFour::CheckHorizontal(int rowNum, int colNum)
{
	
	if (player1_turn)
	{
		if (colNum ==0) 
		{
			if (board[rowNum][colNum+1] == 1)
				if (board[rowNum][colNum + 2] == 1)
					if (board[rowNum][colNum + 3] == 1)
					{
						player1.win = true;
					}
		}
		else if (colNum == 1)
		{
			if (board[rowNum][colNum + 1] == 1)
				if (board[rowNum][colNum + 2] == 1)
					if (board[rowNum][colNum + 3] == 1)
					{
						player1.win = true;
					}

			if (board[rowNum][colNum - 1] == 1)
				if (board[rowNum][colNum + 1] == 1)
					if (board[rowNum][colNum + 2] == 1)
					{
						player1.win = true;
					}
		}
		else if (colNum == 2)
		{
			if (board[rowNum][colNum + 1] == 1)
				if (board[rowNum][colNum + 2] == 1)
					if (board[rowNum][colNum + 3] == 1)
					{
						player1.win = true;
					}

			if (board[rowNum][colNum - 1] == 1)
				if (board[rowNum][colNum + 1] == 1)
					if (board[rowNum][colNum + 2] == 1)
					{
						player1.win = true;
					}
			if (board[rowNum][colNum - 2] == 1)
				if (board[rowNum][colNum - 1] == 1)
					if (board[rowNum][colNum + 1] == 1)
					{
						player1.win = true;
					}
		}
		else if (colNum == 3)
		{
			if (board[rowNum][colNum + 1] == 1)
				if (board[rowNum][colNum + 2] == 1)
					if (board[rowNum][colNum + 3] == 1)
					{
						player1.win = true;
					}

			if (board[rowNum][colNum - 1] == 1)
				if (board[rowNum][colNum + 1] == 1)
					if (board[rowNum][colNum + 2] == 1)
					{
						player1.win = true;
					}
			if (board[rowNum][colNum - 2] == 1)
				if (board[rowNum][colNum - 1] == 1)
					if (board[rowNum][colNum + 1] == 1)
					{
						player1.win = true;
					}
			if (board[rowNum][colNum - 3] == 1)
				if (board[rowNum][colNum - 2] == 1)
					if (board[rowNum][colNum - 1] == 1)
					{
						player1.win = true;
					}
		}
		else if (colNum == 4)
		{
			if (board[rowNum][colNum - 1] == 1)
				if (board[rowNum][colNum + 1] == 1)
					if (board[rowNum][colNum + 2] == 1)
					{
						player1.win = true;
					}
			if (board[rowNum][colNum - 2] == 1)
				if (board[rowNum][colNum - 1] == 1)
					if (board[rowNum][colNum + 1] == 1)
					{
						player1.win = true;
					}
			if (board[rowNum][colNum - 3] == 1)
				if (board[rowNum][colNum - 2] == 1)
					if (board[rowNum][colNum - 1] == 1)
					{
						player1.win = true;
					}
		}
		else if (colNum == 5)
		{
			if (board[rowNum][colNum - 2] == 1)
				if (board[rowNum][colNum - 1] == 1)
					if (board[rowNum][colNum + 1] == 1)
					{
						player1.win = true;
					}
			if (board[rowNum][colNum - 3] == 1)
				if (board[rowNum][colNum - 2] == 1)
					if (board[rowNum][colNum - 1] == 1)
					{
						player1.win = true;
					}
		}
		else if (colNum == 6)
		{
			if (board[rowNum][colNum - 3] == 1)
				if (board[rowNum][colNum - 2] == 1)
					if (board[rowNum][colNum - 1] == 1)
					{
						player1.win = true;
					}
		}
	}
	else
	{
		if (colNum == 0)
		{
			if (board[rowNum][colNum + 1] == 2)
				if (board[rowNum][colNum + 2] == 2)
					if (board[rowNum][colNum + 3] == 2)
					{
						player2.win = true;
					}
		}
		else if (colNum == 2)
		{
			if (board[rowNum][colNum + 1] == 2)
				if (board[rowNum][colNum + 2] == 2)
					if (board[rowNum][colNum + 3] == 2)
					{
						player2.win = true;
					}

			if (board[rowNum][colNum - 1] == 2)
				if (board[rowNum][colNum + 1] == 2)
					if (board[rowNum][colNum + 2] == 2)
					{
						player2.win = true;
					}
		}
		else if (colNum == 2)
		{
			if (board[rowNum][colNum + 1] == 2)
				if (board[rowNum][colNum + 2] == 2)
					if (board[rowNum][colNum + 3] == 2)
					{
						player2.win = true;
					}

			if (board[rowNum][colNum - 1] == 2)
				if (board[rowNum][colNum + 1] == 2)
					if (board[rowNum][colNum + 2] == 2)
					{
						player2.win = true;
					}
			if (board[rowNum][colNum - 2] == 2)
				if (board[rowNum][colNum - 1] == 2)
					if (board[rowNum][colNum + 1] == 2)
					{
						player2.win = true;
					}
		}
		else if (colNum == 3)
		{
			if (board[rowNum][colNum + 1] == 2)
				if (board[rowNum][colNum + 2] == 2)
					if (board[rowNum][colNum + 3] == 2)
					{
						player2.win = true;
					}

			if (board[rowNum][colNum - 1] == 2)
				if (board[rowNum][colNum + 1] == 2)
					if (board[rowNum][colNum + 2] == 2)
					{
						player2.win = true;
					}
			if (board[rowNum][colNum - 2] == 2)
				if (board[rowNum][colNum - 1] == 2)
					if (board[rowNum][colNum + 1] == 2)
					{
						player2.win = true;
					}
			if (board[rowNum][colNum - 3] == 2)
				if (board[rowNum][colNum - 2] == 2)
					if (board[rowNum][colNum - 1] == 2)
					{
						player2.win = true;
					}
		}
		else if (colNum == 4)
		{
			if (board[rowNum][colNum - 1] == 2)
				if (board[rowNum][colNum + 1] == 2)
					if (board[rowNum][colNum + 2] == 2)
					{
						player2.win = true;
					}
			if (board[rowNum][colNum - 2] == 2)
				if (board[rowNum][colNum - 1] == 2)
					if (board[rowNum][colNum + 1] == 2)
					{
						player2.win = true;
					}
			if (board[rowNum][colNum - 3] == 2)
				if (board[rowNum][colNum - 2] == 2)
					if (board[rowNum][colNum - 1] == 2)
					{
						player2.win = true;
					}
		}
					else if (colNum == 5)
					{
						if (board[rowNum][colNum - 2] == 2)
							if (board[rowNum][colNum - 1] == 2)
								if (board[rowNum][colNum + 1] == 2)
								{
									player2.win = true;
								}
						if (board[rowNum][colNum - 3] == 2)
							if (board[rowNum][colNum - 2] == 2)
								if (board[rowNum][colNum - 1] == 2)
								{
									player2.win = true;
								}
					}
					else if (colNum == 6)
					{
						if (board[rowNum][colNum - 3] == 2)
							if (board[rowNum][colNum - 2] == 2)
								if (board[rowNum][colNum - 1] == 2)
								{
									player2.win = true;
								}
					}
		
	}
}
void ConnectFour::CheckDiag(int rowNum, int colNum)
{
	if (player1_turn)
	{
		if (colNum <= 3)
		{
			if (rowNum >= 3)
			{
				if (board[rowNum-1][colNum+1] == 1)
					if (board[rowNum - 2][colNum+2] == 1)
						if (board[rowNum - 3][colNum+3] == 1)
						{
							player1.win = true;
						}
			}
			else if (rowNum <= 2)
			{
				if (board[rowNum + 1][colNum + 1] == 1)
					if (board[rowNum + 2][colNum + 2] == 1)
						if (board[rowNum + 3][colNum + 3] == 1)
						{
							player1.win = true;
						}

				if (board[rowNum + 1][colNum - 1] == 1)
					if (board[rowNum + 2][colNum - 2] == 1)
						if (board[rowNum + 3][colNum - 3] == 1)
						{
							player1.win = true;
						}
			}
		}
		else if (colNum >= 4)					
		{
				if (rowNum >= 3)
				{
					if (board[rowNum - 1][colNum - 1] == 1)
						if (board[rowNum - 2][colNum - 2] == 1)
							if (board[rowNum - 3][colNum - 3] == 1)
							{
								player1.win = true;
							}
				}
				else if (rowNum <= 2)
				{
					if (board[rowNum + 1][colNum - 1] == 1)
						if (board[rowNum + 2][colNum - 2] == 1)
							if (board[rowNum + 3][colNum - 3] == 1)
							{
								player1.win = true;
							}
				}
		}
	}
	else
	{
		if (colNum <= 3)
		{
			if (rowNum >= 3)
			{
				if (board[rowNum - 1][colNum + 1] == 2)
					if (board[rowNum - 2][colNum + 2] == 2)
						if (board[rowNum - 3][colNum + 3] == 2)
						{
							player2.win = true;
						}
			}
			else if (rowNum <= 2)
			{
				if (board[rowNum + 1][colNum + 1] == 2)
					if (board[rowNum + 2][colNum + 2] == 2)
						if (board[rowNum + 3][colNum + 3] == 2)
						{
							player2.win = true;
						}
				if (board[rowNum + 1][colNum - 1] == 2)
					if (board[rowNum + 2][colNum - 2] == 2)
						if (board[rowNum + 3][colNum - 3] == 2)
						{
							player2.win = true;
						}
			}
		}
		else if (colNum >= 4)
		{
			if (rowNum >= 3)
			{
				if (board[rowNum - 1][colNum - 1] == 2)
					if (board[rowNum - 2][colNum - 2] == 2)
						if (board[rowNum - 3][colNum - 3] == 2)
						{
							player2.win = true;
						}
			}
			else if (rowNum <= 2)
			{
				if (board[rowNum + 1][colNum - 1] == 2)
					if (board[rowNum + 2][colNum - 2] == 2)
						if (board[rowNum + 3][colNum - 3] == 2)
						{
							player2.win = true;
						}
			}
		}
	}
}
void ConnectFour::handle_input(const sf::Time & delta)
{
	if(player1.win)
		gameText.setString("PLAYER 1 WINS");
	else if(player2.win)
		gameText.setString("PLAYER 2 WINS");

	auto inputManager = state_manager_.get_input_manager();
	sf::RenderWindow& window = state_manager_.get_render_window();
	inputManager.giveStateManager(&state_manager_);
	inputManager.setRegionSize();
	inputManager.setwindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	sf::Vector2i windowO(view_main.getCenter().x - view_main.getSize().x / 2, view_main.getCenter().y - view_main.getSize().y / 2);

	mouse_pos.x = windowO.x + inputManager.get_mouse_x();
	mouse_pos.y = windowO.y + inputManager.get_mouse_y();
	bool placed = false;
	if (!player1.win || !player2.win)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 7; j++)
			{

				if (circle[i][j].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
				{
					boardHighlight[i][j] = true;

					if (inputManager.left_clicked())
					{
						if (!placed) {

							placeChip(i, j);
							Sleep(150);
							placed = true;
						}
					}
				}
				else
					boardHighlight[i][j] = false;

			}
		}
	}
	//cout << "X. " << mouse_pos.x << "Y. " << mouse_pos.y << endl;
	if (inputManager.is_key_released(InputKey::space))
	{
		player1_turn = !player1_turn;
		if (player1_turn)
			gameText.setString("Player 1- It's your turn");
		else
			gameText.setString("Player 2- It's your turn");

	}
	if (inputManager.is_key_released(InputKey::escape))
	{
		state_manager_.quit();
	}

	if (backHighlight == true)
		if (inputManager.left_clicked())
			back = true;

	if (resetHighlight == true)
		if (inputManager.left_clicked())
		{
			Reset();
			initGame();
			Sleep(600);
		}

	if (backButtonSpr[0].getGlobalBounds().contains(mouse_pos))
	{
		backHighlight = true;
	}
	else
		backHighlight = false;

	if (resetButtonSpr[0].getGlobalBounds().contains(mouse_pos))
	{
		resetHighlight = true;
	}
	else
		resetHighlight = false;

}

void ConnectFour::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (back == true)
		state_current.change_state(state_manager_.state_ptr<GameBox>());
	if (quit == true)
		state_manager_.quit();
}
