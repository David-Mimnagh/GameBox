#include "GameBox.h"



GameBox::GameBox(StateManager& state_manager) : AbstractState(state_manager)
{
	choice, points = 0;
	playAgain = "";

	view_main.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	view_main.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	
	// zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
	view_main.zoom(1.0f);

	// define a centered viewport, with half the size of the window
	view_main.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
	if (!Menu_background.loadFromFile("sfml-icon-big.png"))
	{
		std::cout << "Could not load image\n";
	}
	Menu_bg_sprite.setTexture(Menu_background);
	// Load from a font file on disk
	if (!MainFont.loadFromFile("../../GameBox/MavenPro-Regular.ttf"))
	{
		cout << "NO font found.";
	}

	welcomeText.setFont(MainFont); 
	welcomeText.setString("Welcome to GameBox.");
	welcomeText.setCharacterSize(24);
	welcomeText.setPosition(WINDOW_WIDTH / 2 - 120, 200);
	welcomeText.setFillColor(sf::Color::Cyan);

	intro1.setFont(MainFont);
	intro1.setString("Within Gamebox there are a number of different games...");
	intro1.setCharacterSize(18);
	intro1.setPosition(WINDOW_WIDTH / 2 - 235, 300);
	intro1.setFillColor(sf::Color::Cyan);
	
	intro2.setFont(MainFont);
	intro2.setString("For each win within a game a point will be gained.");
	intro2.setCharacterSize(18);
	intro2.setPosition(WINDOW_WIDTH / 2 - 200, 325);
	intro2.setFillColor(sf::Color::Cyan);

	gameText.setFont(MainFont);
	gameText.setString("Click an option below to launch the game.");
	gameText.setCharacterSize(18);
	gameText.setPosition(WINDOW_WIDTH / 2 - 175, 450);
	gameText.setFillColor(sf::Color::Cyan);

	DescriptionText.setFont(MainFont);
	DescriptionText.setCharacterSize(24);
	DescriptionText.setPosition(270, 600);
	DescriptionText.setFillColor(sf::Color::Cyan);

	pointsText.setFont(MainFont);
	string points = to_string(state_manager.getPoints());
	pointsText.setString("Your Points: " + points);
	pointsText.setCharacterSize(32);
	pointsText.setPosition(530, 380);
	pointsText.setFillColor(sf::Color::Cyan);

	if (!Menu_background.loadFromFile("background.png"))
	{
		std::cout << "Could not load image\n";
	}
	Menu_bg_sprite.setTexture(Menu_background);
	if (!logoTex.loadFromFile("Logo.png"))
	{
		std::cout << "Could not load image\n";
	}
	logoSpr.setTexture(logoTex);
	logoSpr.setOrigin(logoSpr.getGlobalBounds().width / 2, logoSpr.getGlobalBounds().height / 2);
	logoSpr.setPosition(WINDOW_WIDTH / 2, 100);

	GGButton.loadFromFile("GG/GuessingGameB1.png");
	GGButton2.loadFromFile("GG/GuessingGameB2.png");

	HMButton.loadFromFile("HangmanB1.png");
	HMButton2.loadFromFile("HangmanB2.png");

	RPSButton.loadFromFile("RPSB1.png");
	RPSButton2.loadFromFile("RPSB2.png");

	TTTButton.loadFromFile("TTTB1.png");
	TTTButton2.loadFromFile("TTTB2.png");

	BrButton1.loadFromFile("HangmanB1.png");
	BrButton2.loadFromFile("HangmanB2.png");

	C4Button1.loadFromFile("HangmanB1.png");
	C4Button2.loadFromFile("HangmanB2.png");

	FBButton1.loadFromFile("HangmanB1.png");
	FBButton2.loadFromFile("HangmanB2.png");

	BGButton1.loadFromFile("HangmanB1.png");
	BGButton2.loadFromFile("HangmanB2.png");

	GGSprite1.setTexture(GGButton);
	GGSprite1.setPosition(100, 500);
	GGSprite2.setTexture(GGButton2);
	GGSprite2.setPosition(100, 500);

	HMSprite1.setTexture(HMButton);
	HMSprite1.setPosition(400, 500);
	HMSprite2.setTexture(HMButton2);
	HMSprite2.setPosition(400, 500);

	RPSSprite1.setTexture(RPSButton);
	RPSSprite1.setPosition(665, 500);
	RPSSprite2.setTexture(RPSButton2);
	RPSSprite2.setPosition(665, 500);

	TTTSprite1.setTexture(TTTButton);
	TTTSprite1.setPosition(WINDOW_WIDTH - 270, 500);
	TTTSprite2.setTexture(TTTButton2);
	TTTSprite2.setPosition(WINDOW_WIDTH - 270, 500);

	BrSprite1.setTexture(BrButton1);
	BrSprite1.setPosition(100, 700);
	BrSprite2.setTexture(BrButton2);
	BrSprite2.setPosition(100, 700);

	C4Sprite1.setTexture(C4Button1);
	C4Sprite1.setPosition(400, 700);
	C4Sprite2.setTexture(C4Button2);
	C4Sprite2.setPosition(400, 700);

	C4Sprite1.setTexture(C4Button1);
	C4Sprite1.setPosition(400, 700);
	C4Sprite2.setTexture(C4Button2);
	C4Sprite2.setPosition(400, 700);

	FBSprite1.setTexture(FBButton1);
	FBSprite1.setPosition(665, 700);
	FBSprite2.setTexture(FBButton2);
	FBSprite2.setPosition(665, 700);

	BGSprite1.setTexture(BGButton1);
	BGSprite1.setPosition(WINDOW_WIDTH - 270, 700);
	BGSprite2.setTexture(BGButton2);
	BGSprite2.setPosition(WINDOW_WIDTH - 270, 700);

	change_GG, change_RPS, change_HM, change_TTT, change_Br, change_C4, change_FB, change_BG, quit = false;
	for (int i = 0; i < 8;i++)
	highlight[i] = false;
}


GameBox::~GameBox()
{
}
void GameBox::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (change_GG == true)
		state_current.change_state(state_manager_.state_ptr<GuessingGame>());
	else
		if (change_RPS == true)
			state_current.change_state(state_manager_.state_ptr<RPS>());
		else
			if (change_HM == true)
				state_current.change_state(state_manager_.state_ptr<Hangman>());
			else
				if (change_TTT == true)
					state_current.change_state(state_manager_.state_ptr<TicTacToe>());
				else
					if (change_Br == true)
						state_current.change_state(state_manager_.state_ptr<Breakout>());
					else
						if (change_C4 == true)
							state_current.change_state(state_manager_.state_ptr<ConnectFour>());
						else
							if (change_FB == true)
								state_current.change_state(state_manager_.state_ptr<FlappyBurd>());
							else
								if (change_BG == true)
									state_current.change_state(state_manager_.state_ptr<BotGame>());
				else
					if (quit == true)
						state_manager_.quit();
}
void GameBox::update(const sf::Time& delta)
{

}

void GameBox::pause()
{
	set_paused(true);
}

void GameBox::resume()
{
	set_paused(false);
}

void GameBox::handle_input(const sf::Time& delta)
{
	auto inputManager = state_manager_.get_input_manager();
	pointsText.setString("Your Points: " + to_string(state_manager_.getPoints()));
	//cout << "X. " << mouse_pos.x << "Y. " << mouse_pos.y << endl;
	inputManager.giveStateManager(&state_manager_);
	inputManager.setRegionSize();
	inputManager.setwindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);  

	if (inputManager.is_key_released(InputKey::escape))
	{
		state_manager_.quit();
	}

	if (highlight[0] == true)
		if (inputManager.left_clicked())
			change_GG = true;
	if (highlight[1] == true)
		if (inputManager.left_clicked())
			change_HM = true;
	if (highlight[2] == true)
		if (inputManager.left_clicked())
			change_RPS = true;
	if (highlight[3] == true)
		if (inputManager.left_clicked())
			change_TTT = true;
	if (highlight[4] == true)
		if (inputManager.left_clicked())
			change_Br = true;
	if (highlight[5] == true)
		if (inputManager.left_clicked())
			change_C4 = true;
	if (highlight[6] == true)
		if (inputManager.left_clicked())
			change_FB = true;
	if (highlight[7] == true)
		if (inputManager.left_clicked())
			change_BG = true;

	sf::Vector2i windowO(view_main.getCenter().x - view_main.getSize().x / 2, view_main.getCenter().y - view_main.getSize().y / 2);

	mouse_pos.x = windowO.x + inputManager.get_mouse_x();
	mouse_pos.y = windowO.y + inputManager.get_mouse_y();

	if (GGSprite1.getGlobalBounds().contains(mouse_pos))
	{
		DescriptionText.setPosition(102, 570);
		DescriptionText.setString("Try to guess\nthe random number\nthat was selected\nby the computer.");
		highlight[0] = true;
	}
	else if (HMSprite1.getGlobalBounds().contains(mouse_pos))
	{
		DescriptionText.setPosition(402, 600);
		DescriptionText.setString("Try to beat the\ncomputer in a classic\ngame of Hangman.");
		highlight[1] = true;
	} 
	else if (RPSSprite1.getGlobalBounds().contains(mouse_pos))
	{
		DescriptionText.setPosition(670, 600);
		DescriptionText.setString("Try to beat the\ncomputer in a classic\ngame of\nRock-Paper-Scissors.");
		highlight[2] = true;
	}
	else if (TTTSprite1.getGlobalBounds().contains(mouse_pos))
	{
		DescriptionText.setPosition(1010, 600);
		DescriptionText.setString("Go head to head\nwith the computer\nin a classic game\nof Tic-Tac-Toe.");
		highlight[3] = true;
	}
	else if (BrSprite1.getGlobalBounds().contains(mouse_pos))
	{
		DescriptionText.setPosition(102, 770);
		DescriptionText.setString("Go head to head\nwith the computer\nin a classic game\nof Breakout.");
		highlight[4] = true;
	}
	else if (C4Sprite1.getGlobalBounds().contains(mouse_pos))
	{
		DescriptionText.setPosition(402, 770);
		DescriptionText.setString("Go head to head\nwith your friend\nin a classic game\nof Connect Four.");
		highlight[5] = true;
	}
	else if (FBSprite1.getGlobalBounds().contains(mouse_pos))
	{
		DescriptionText.setPosition(665, 770);
		DescriptionText.setString("Go against the pipes\ntrying to slip through\nin a classic game\nof Flappy Burd.");
		highlight[6] = true;
	}
	else if (BGSprite1.getGlobalBounds().contains(mouse_pos))
	{
		DescriptionText.setPosition(WINDOW_WIDTH - 270, 770);
		DescriptionText.setString("Control a bot and\ntry your hardest\nto make your way\nthrough the various\nlevels of Bot Game.");
		highlight[7] = true;
	}
	else
	{
		for (size_t i = 0; i < 8; i++)
		{
			highlight[i] = false;
		}
		DescriptionText.setString("");
	}
		

}
void GameBox::render()
{

	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view
	window.draw(Menu_bg_sprite);
	window.draw(logoSpr);
	window.draw(welcomeText);
	window.draw(intro1);
	window.draw(intro2);
	window.draw(gameText);
	window.draw(pointsText);
	if (!highlight[0])
	{
		window.draw(GGSprite1);
		window.draw(DescriptionText);
	}
	else
		window.draw(GGSprite2);

	if (!highlight[1])
	{
		window.draw(HMSprite1);
		window.draw(DescriptionText);
	}
	else 
		window.draw(HMSprite2);

	if (!highlight[2])
	{
		window.draw(RPSSprite1);
		window.draw(DescriptionText);
	}
	else
		window.draw(RPSSprite2);

	if (!highlight[3])
	{
		window.draw(TTTSprite1);
		window.draw(DescriptionText);
	}
	else
	window.draw(TTTSprite2);

	if (!highlight[4])
	{
		window.draw(BrSprite1);
		window.draw(DescriptionText);
	}
	else
		window.draw(BrSprite2);

	if (!highlight[5])
	{
		window.draw(C4Sprite1);
		window.draw(DescriptionText);
	}
	else
		window.draw(C4Sprite2);

	if (!highlight[6])
	{
		window.draw(FBSprite1);
		window.draw(DescriptionText);
	}
	else
		window.draw(FBSprite2);

	if (!highlight[7])
	{
		window.draw(BGSprite1);
		window.draw(DescriptionText);
	}
	else
		window.draw(BGSprite2);

}