#include "GuessingGame.h"



GuessingGame::GuessingGame(StateManager& state_manager) : AbstractState(state_manager)
{
	numberToGuess, GuessedNumber, numberOfGuesses = 0;
	guessing = true;
	win = false;
	guessesLeft = 5;
	subtractGuess = true;
	backHighlight = false;
	guessed = false;
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
	messageText.setString("Welcome to GameBox - Guessing Game.");
	messageText.setCharacterSize(24);
	messageText.setPosition(WINDOW_WIDTH / 2 - 190, 200);
	messageText.setFillColor(sf::Color::Red);

	gameText.setFont(MainFont);
	gameText.setCharacterSize(40);
	gameText.setPosition(WINDOW_WIDTH / 2 - 575, 250);
	gameText.setFillColor(sf::Color::Red);

	livesText.setFont(MainFont);
	livesText.setString("You have: [" + to_string(guessesLeft) + "] guesses left.");
	livesText.setCharacterSize(24);
	livesText.setPosition(WINDOW_WIDTH / 2 - 125, 705);
	livesText.setFillColor(sf::Color::Red);

	if (!GGbackground.loadFromFile("GG/GGbackground.png"))
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
		backButtonSpr[i].setPosition(10, WINDOW_HEIGHT - 100);
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
		resetButtonSpr[i].setPosition(WINDOW_WIDTH - 160, WINDOW_HEIGHT - 100);
	}

	for (int i = 0; i < 10; i++)
	{
		button[i].loadFromFile("GG/Guess_" + to_string(i + 1) + ".png");
		buttonH[i].loadFromFile("GG/Guess_" + to_string(i + 1) + "H.png");
	}
	
	for (int i = 0; i < 10; i++)
	{
		buttonHSpr[i].setTexture(buttonH[i]);
	}
	for (int i = 0; i < 11; i++)
	{
		buttonSpr[i].setTexture(button[i]);
		if (i < 3)
		{
			buttonSpr[i].setPosition(550 + (i * 80), 400);
			buttonHSpr[i].setPosition(550 + (i * 80), 400);
		}
		else if (i > 2 && i < 6)
		{
			for (int j = 0; j < 3; j++)
			{
				buttonSpr[i].setPosition(550 + ((i - 3) * 80), 480);
				buttonHSpr[i].setPosition(550 + ((i - 3) * 80), 480);
				break;
			}
		}
		else if (i > 5 && i < 9)
		{
			for (int j = 0; j < 3; j++)
			{
				buttonSpr[i].setPosition(550 + ((i - 6) * 80), 560);
				buttonHSpr[i].setPosition(550 + ((i - 6) * 80), 560);
				break;
			}
		}
		else
		{
			buttonSpr[i].setPosition(625, 640);
			buttonHSpr[i].setPosition(625, 640);
		}
	}
	back, quit = false;
	for (int i = 0; i < 11; i++)
		highlight[i] = false;
	initGame();
}


GuessingGame::~GuessingGame()
{
}
void GuessingGame::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (back == true)
		state_current.change_state(state_manager_.state_ptr<GameBox>());
	if (quit == true)
		state_manager_.quit();

}
void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}
void GuessingGame::update(const sf::Time& delta)
{
	if (guessed)
	{

		guessesLeft -= 1;
		Guess();
		if (!getWinState())
			Sleep(600);
		else
		{
			Sleep(600);
			drawReset = true;
		}
	}

	if (guessing == false)
	{
		CorrectGuess();
	}
}

void GuessingGame::pause()
{
	set_paused(true);
}

void GuessingGame::resume()
{
	set_paused(false);
}
void GuessingGame::handle_input(const sf::Time& delta)
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
	for (int i = 0; i < 10; i++)
	{
		if (highlight[i] == true)
		{
			if (!getWinState())
			{
				if (inputManager.left_clicked())
				{
					GuessedNumber = i + 1;
					guessed = true;
					inputManager.setReleased_left(false);
					break;

				}
			}
		}
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


	for (int i = 0; i < 10; i++)
	{
		if (buttonSpr[i].getGlobalBounds().contains(mouse_pos))
		{
			highlight[i] = true;
			break;
		}
		else highlight[i] = false;
	}
}
void GuessingGame::render()
{

	sf::RenderWindow& window = state_manager_.get_render_window();

	if (getWinState())
	{
		gameText.setPosition(WINDOW_WIDTH / 2 - 425, 235);
		gameText.setCharacterSize(32);
		gameText.setString("\t\t\t\tGood Job! you correctly guessed: [" + to_string (GuessedNumber) + "].\n\t\t\t\tYou got: [" + to_string(guessesLeft) + "] bonus points this round.\n\t\t\tPress [Back] to go back to the main menu...\nAlternatively, press [Reset] to replay the game for more points.");
	}

	window.setView(view_main); // applying the view
	window.draw(GGbg_sprite);
	window.draw(logoSpr);
	window.draw(messageText);
	window.draw(livesText);
	window.draw(gameText);
	window.draw(pointsText);
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
	for (int i = 0; i < 10; i++)
	{
		if (!highlight[i])
		{
			window.draw(buttonSpr[i]);
		}
		else
			window.draw(buttonHSpr[i]);
	}
}

void GuessingGame::initGame()
{
	srand(time(NULL));
	numberToGuess = rand() % 10 + 1;
	cout << "Random number between 1 - 10 generated!" << endl;

}
void GuessingGame::Guess()
{
	livesText.setString("You have: [" + to_string(guessesLeft) + "] guesses left.");

	if (guessesLeft <= 0)
	{
		cout << "Sorry, you have ran out of possible guesses..." << endl;
		cout << "You lost!" << endl;
		guessing = false;
	}

	cout << "\nYou have guessed: " << GuessedNumber << endl;
	numberOfGuesses++;
	cout << "You have [" << guessesLeft << "] guesses left." << endl;
	if (GuessedNumber > 0 && GuessedNumber < 11)
	{
		if (GuessedNumber == numberToGuess)
		{
			if (numberOfGuesses == 1)
				cout << "\nNo Way! You got it in " << numberOfGuesses << " try." << endl;
			else
				cout << "\nNo Way! You got it in " << numberOfGuesses << " tries." << endl;
			guessing = false;
			setWinState(true);
			state_manager_.setPoints(state_manager_.getPoints() + 1 + guessesLeft);
			drawReset = true;
		}
		else
		{
			if (GuessedNumber < numberToGuess) 
			{
				gameText.setPosition(WINDOW_WIDTH / 2 - 210, 265);
				gameText.setCharacterSize(40);
				gameText.setString("Maybe try a higher guess!");
			}
			else if (GuessedNumber > numberToGuess)
			{
				gameText.setPosition(WINDOW_WIDTH / 2 - 165, 265);
				gameText.setCharacterSize(40);
				gameText.setString("Try guessing lower!");
			}
		}

	}
	guessed = false;
}
void GuessingGame::CorrectGuess()
{
	setWinState(true);
}
void GuessingGame::Reset()
{
	numberToGuess, GuessedNumber, numberOfGuesses = 0;
	guessing = true;
	win = false;
	guessesLeft = 5;
	subtractGuess = true;
	backHighlight = false;
	guessed = false;
	livesText.setString("You have: [" + to_string(guessesLeft) + "] guesses left.");
	gameText.setString("");
}