#include "RPS.h"

RPS::RPS(StateManager& state_manager) : AbstractState(state_manager)
{
	init = true;
	win = false;
	choosing = true;
	playing = true;
	totalTime = 6000;
	drawReset = false;
	confirmHighlight = false; confirmSelect = false;
	
	choiceNumber = 0;
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
	messageText.setString("Welcome to GameBox - Rock Paper Scissors.");
	messageText.setCharacterSize(24);
	messageText.setPosition(WINDOW_WIDTH / 2 - 250, 200);
	messageText.setFillColor(sf::Color::White);

	gameText.setFont(MainFont);
	gameText.setCharacterSize(40);
	gameText.setPosition(WINDOW_WIDTH / 2 - 575, 250);
	gameText.setFillColor(sf::Color::White);

	livesText.setFont(MainFont);
	livesText.setString("\t\t\tClick your selection.\nClick confirm to confirm your selection");
	livesText.setCharacterSize(24);
	livesText.setPosition(WINDOW_WIDTH / 2 - 205, 715);
	livesText.setFillColor(sf::Color::White);

	if (!GGbackground.loadFromFile("RPS/RPSbackground.png"))
	{
		std::cout << "Could not load image\n";
	}
	GGbg_sprite.setTexture(GGbackground);
	if (!logoTex.loadFromFile("Logo.png"))
	{
		std::cout << "Could not load image\n";
	}
	logoSpr.setTexture(logoTex);
	logoSpr.setOrigin(logoSpr.getGlobalBounds().width / 2, logoSpr.getGlobalBounds().height / 2);
	logoSpr.setPosition(WINDOW_WIDTH / 2, 100);
	if (!backButton[0].loadFromFile("RPS/Back.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!backButton[1].loadFromFile("RPS/BackH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 2; i++)
	{
		backButtonSpr[i].setTexture(backButton[i]);
		backButtonSpr[i].setPosition(10, WINDOW_HEIGHT - 80);
	}

	if (!resetButton[0].loadFromFile("RPS/reset.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!resetButton[1].loadFromFile("RPS/ResetH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 2; i++)
	{
		resetButtonSpr[i].setTexture(resetButton[i]);
		resetButtonSpr[i].setPosition(WINDOW_WIDTH - 105, WINDOW_HEIGHT - 80);
	}

	if (!pButton[0].loadFromFile("RPS/P_Rock.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!pButton[1].loadFromFile("RPS/P_Paper.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!pButton[2].loadFromFile("RPS/P_Scissors.png"))
	{
		std::cout << "Could not load image\n";
	}

	if (!pButtonS[0].loadFromFile("RPS/PS_Rock.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!pButtonS[1].loadFromFile("RPS/PS_Paper.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!pButtonS[2].loadFromFile("RPS/PS_Scissors.png"))
	{
		std::cout << "Could not load image\n";
	}

	if (!pButtonH[0].loadFromFile("RPS/PH_Rock.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!pButtonH[1].loadFromFile("RPS/PH_Paper.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!pButtonH[2].loadFromFile("RPS/PH_Scissors.png"))
	{
		std::cout << "Could not load image\n";
	}

	if (!cButton[0].loadFromFile("RPS/C_Rock.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!cButton[1].loadFromFile("RPS/C_Paper.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!cButton[2].loadFromFile("RPS/C_Scissors.png"))
	{
		std::cout << "Could not load image\n";
	}

	for (int i = 0; i < 3; i++)
		if (!countDownText[i].loadFromFile("RPS/" + to_string(i + 1) + ".png"))
		{
			std::cout << "Could not load image\n";
		}

	if (!confirmButton[0].loadFromFile("RPS/confirm.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!confirmButton[1].loadFromFile("RPS/confirmH.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!confirmButton[2].loadFromFile("RPS/confirmS.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 3; i++)
	{
		confirmButtonSpr[i].setTexture(confirmButton[i]);
		confirmButtonSpr[i].setPosition(WINDOW_WIDTH / 2 - 60, 780);
	}

	for (int i = 0; i < 3; i++)
	{
		countDownTextSpr[i].setTexture(countDownText[i]);
		countDownTextSpr[i].setPosition(WINDOW_WIDTH / 2 - 40, 520);
	}

	for (int i = 0; i < 3; i++)
	{
		pButtonSpr[i].setTexture(pButton[i]);
		pButtonSpr[i].setPosition(WINDOW_WIDTH /2 - 250, 400 + i * 110);
	}
	for (int i = 0; i < 3; i++)
	{
		pButtonSSpr[i].setTexture(pButtonS[i]);
		pButtonSSpr[i].setPosition(WINDOW_WIDTH /2- 250, 400 + i * 110);
	}
	for (int i = 0; i < 3; i++)
	{
		pButtonHSpr[i].setTexture(pButtonH[i]);
		pButtonHSpr[i].setPosition(WINDOW_WIDTH /2 - 250, 400 + i * 110);
	}
	for (int i = 0; i < 3; i++)
	{
		cButtonSpr[i].setTexture(cButton[i]);
		cButtonSpr[i].setPosition(WINDOW_WIDTH /2 + 140, 400 + i * 110);
	}
	for (int i = 0; i < 3; i++)
	{
		pButtonHighlight[i] = false;
		pButtonSelect[i] = false;
	}
	initGame();

}


RPS::~RPS()
{
}

void RPS::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (back == true)
		state_current.change_state(state_manager_.state_ptr<GameBox>());
	if (quit == true)
		state_manager_.quit();

	if (getWinState())
		drawReset = true;
}
void RPS::update(const sf::Time& delta)
{
}

void RPS::pause()
{
	set_paused(true);
}

void RPS::resume()
{
	set_paused(false);
}

void RPS::handle_input(const sf::Time& delta)
{

	auto inputManager = state_manager_.get_input_manager();
	sf::RenderWindow& window = state_manager_.get_render_window();
	inputManager.giveStateManager(&state_manager_);
	inputManager.setRegionSize();
	inputManager.setwindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);  //should be lwvel not window will change it later ;-)
	sf::Vector2i windowO(view_main.getCenter().x - view_main.getSize().x / 2, view_main.getCenter().y - view_main.getSize().y / 2);

	mouse_pos.x = windowO.x + inputManager.get_mouse_x();
	mouse_pos.y = windowO.y + inputManager.get_mouse_y();
	//cout << "X. " << mouse_pos.x << "Y. " << mouse_pos.y << endl;
	if (inputManager.is_key_released(InputKey::escape))
	{
		state_manager_.quit();
	}

	// check the type of the event...
	for (int i = 0; i < 3; i++)
	{
		if (pButtonHighlight[i] == true)
		{
			if (!getWinState())
			{
				if (inputManager.left_clicked())
				{
					for (int j = 0; j < 3; j++)
					pButtonSelect[j] = false;
					pButtonSelect[i] = true;
					if (i == 0)
					{
						player.Playerchoice.choice = "Rock";
						setChoosingState(false);
					}
					if (i == 1)
					{
						player.Playerchoice.choice = "Paper";
						setChoosingState(false);
					}
					if (i == 2)
					{
						player.Playerchoice.choice = "Scissors";
						setChoosingState(false);
					}
					inputManager.setReleased_left(false);
					break;

				}
			}
		}
	}

	if (backHighlight == true)
		if (inputManager.left_clicked())
			back = true;

	if (confirmHighlight == true)
		if (inputManager.left_clicked())
		{
			if (getChoosingState())
			{
				gameText.setString("\t\t\tYou need to make a selection first.");
			}
			else
			{
				gameText.setString(" ");
				confirmSelect = true;
			}
		}
			

	if (resetHighlight == true)
		if (inputManager.left_clicked())
		{
			Reset();
			initGame();
			Sleep(600);
		}
	if (confirmButtonSpr[0].getGlobalBounds().contains(mouse_pos))
		confirmHighlight = true;
	else
		confirmHighlight = false;

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


	for (int i = 0; i < 3; i++)
	{
		if (pButtonSpr[i].getGlobalBounds().contains(mouse_pos))
		{
			pButtonHighlight[i] = true;
			break;
		}
		else pButtonHighlight[i] = false;
	}
}
void RPS::render()
{

	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view
	window.draw(GGbg_sprite);
	window.draw(logoSpr);
	window.draw(messageText);
	window.draw(livesText);
	window.draw(gameText);
	window.draw(pointsText);

	if (confirmSelect)
	{
		
		totalTime -= 1.0 / 60.0; //increase time
		if (totalTime > 4000)  // 3.
			window.draw(countDownTextSpr[2]);
		else if (totalTime > 2000)  // 2.
			window.draw(countDownTextSpr[1]);
		else if (totalTime > 0)
			window.draw(countDownTextSpr[0]);
		else
			Playing();
	}
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

	if (!confirmHighlight && !confirmSelect)
	{
		window.draw(confirmButtonSpr[0]);
	}
	if(confirmSelect)
		window.draw(confirmButtonSpr[2]);
	else if(confirmHighlight)
		window.draw(confirmButtonSpr[1]);

	for (int i = 0; i < 3; i++)
	{
		if (pButtonHighlight[i])
		{
			window.draw(pButtonHSpr[i]);
		}
		else if (pButtonSelect[i])
		{
			window.draw(pButtonSSpr[i]);
		}
		else
			window.draw(pButtonSpr[i]);
	}

	for (int i = 0; i < 3; i++)
		window.draw(cButtonSpr[i]);
}
void RPS::initGame()
{
		cout << "Initialising Rock, Paper, Scissors..." << endl;
		srand(time(NULL));
		choiceNumber = rand() % 3 + 1;

		if (choiceNumber == 1)
			ai.AIchoice.choice = "Rock";
		else if (choiceNumber == 2)
			ai.AIchoice.choice = "Paper";
		else if (choiceNumber == 3)
			ai.AIchoice.choice = "Scissors";
		gameText.setString("The AI has made up its mind...");
		gameText.setPosition(WINDOW_WIDTH / 2 - 290, 250);
		init = false;
		setChoosingState(true);
		setWinState(false);
}
void RPS::Playing()
{
	/*ROCK > SCISSORS. PAPER > ROCK. SCISSORS > PAPER*/
	if (!getWinState())
	{
		if (player.Playerchoice.choice == "Rock")
		{
			if (ai.AIchoice.choice == "Rock")
			{
				gameText.setString("Ouch! That's a draw");
				gameText.setPosition(WINDOW_WIDTH / 2 - 200, 250);
				drawReset = true;
				setPlayingState(false);
				setWinState(false);
			}
			if (ai.AIchoice.choice == "Paper")
			{
				gameText.setString("\t\t  Well that's unfortunate.\n\tIt looks like the AI won this one.");
				gameText.setPosition(WINDOW_WIDTH / 2 - 355, 250);
				drawReset = true;
				setPlayingState(false);
				setWinState(false);

			}
			if (ai.AIchoice.choice == "Scissors")
			{
				gameText.setString("Woohoo! Good choice, you won!");
				gameText.setPosition(WINDOW_WIDTH / 2 - 305, 250);
				state_manager_.setPoints(state_manager_.getPoints() + 1);
				setWinState(true);
				drawReset = true;
				setPlayingState(false);
			}
		}
		else if (player.Playerchoice.choice == "Paper")
		{
			if (ai.AIchoice.choice == "Rock")
			{
				gameText.setString("Woohoo! Good choice, you won!");
				gameText.setPosition(WINDOW_WIDTH / 2 - 305, 250);
				state_manager_.setPoints(state_manager_.getPoints() + 1);
				setWinState(true);
				drawReset = true;
				setPlayingState(false);
			}
			if (ai.AIchoice.choice == "Paper")
			{
				gameText.setString("\t\t\tOuch! That's a draw");
				gameText.setPosition(WINDOW_WIDTH / 2 - 200, 250);
				drawReset = true;
				setPlayingState(false);
				setWinState(false);
			}

			if (ai.AIchoice.choice == "Scissors")
			{
				gameText.setString("\t\t  Well that's unfortunate.\n\tIt looks like the AI won this one.");
				gameText.setPosition(WINDOW_WIDTH / 2 - 355, 250);
				drawReset = true;
				setPlayingState(false);
				setWinState(false);

			}
		}
		else if (player.Playerchoice.choice == "Scissors")
		{
			if (ai.AIchoice.choice == "Rock")
			{
				gameText.setString("\t\t  Well that's unfortunate.\n\tIt looks like the AI won this one.");
				gameText.setPosition(WINDOW_WIDTH / 2 - 355, 250);
				drawReset = true;
				setPlayingState(false);
				setWinState(false);
			}
			if (ai.AIchoice.choice == "Paper")
			{
				gameText.setString("Woohoo! Good choice, you won!");
				gameText.setPosition(WINDOW_WIDTH / 2 - 305, 250);
				state_manager_.setPoints(state_manager_.getPoints() + 1);
				setWinState(true);
				drawReset = true;
				setPlayingState(false);
			}

			if (ai.AIchoice.choice == "Scissors")
			{
				gameText.setString("Clink Clink! That's a draw");
				gameText.setPosition(WINDOW_WIDTH / 2 - 250, 250);
				drawReset = true;
				setPlayingState(false);
				setWinState(false);
			}
		}
	}
}
void RPS::Reset()
{
	init = true;
	win = false;
	choosing = true;
	playing = true;
	totalTime = 6000;
	drawReset = false;
	confirmHighlight = false; confirmSelect = false;
	for (int i = 0; i < 3; i++)
	{
		pButtonHighlight[i] = false;
		pButtonSelect[i] = false;
	}
	drawReset = false;
	choiceNumber = 0;
}