#include "FlappyBurd.h"

FlappyBurd::FlappyBurd(StateManager & state_manager) : AbstractState(state_manager)
{
	fpBurd.dead = false;
	fpBurd.position = sf::Vector2f(150, WINDOW_HEIGHT / 2);
	fpBurd.score = 0;
	fpBurd.tex.loadFromFile("FB/Burd.png");
	fpBurd.spr.setTexture(fpBurd.tex);
	gravity = 2.0f;
	jump = 63.5f;
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
	for (int i = 1; i < 5; i++)
	{
		pipeTex[i - 1].loadFromFile("FB/pipe" +std::to_string(i) + ".png");
		pipeSpr[i - 1].setTexture(pipeTex[i - 1]);
		int newPos = i * 280;
		pipeSpr[i - 1].setPosition(100 + newPos, WINDOW_HEIGHT - pipeSpr[i - 1].getGlobalBounds().height);
	}
	messageText.setFont(MainFont);
	//messageText.setString("Welcome to GameBox - Flappy Burd.");
	messageText.setCharacterSize(18);
	messageText.setOrigin(messageText.getGlobalBounds().width / 2, messageText.getGlobalBounds().height / 2);
	messageText.setPosition(WINDOW_WIDTH / 2, 572);
	messageText.setFillColor(sf::Color::Red);

	gameText.setFont(MainFont);
	//gameText.setString("Player 1- It's your turn");
	gameText.setOrigin(gameText.getGlobalBounds().width / 2, gameText.getGlobalBounds().height / 2 - 50);
	gameText.setCharacterSize(28);
	gameText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
	gameText.setFillColor(sf::Color::Red);

		if (!FBbackground[0].loadFromFile("FB/FBBackground0.png"))
		{
			std::cout << "Could not load image\n";
		}
		FBbg_sprite[0].setTexture(FBbackground[0]);

		if (!FBbackground[1].loadFromFile("FB/FBBackground1.png"))
		{
			std::cout << "Could not load image\n";
		}
		FBbg_sprite[1].setTexture(FBbackground[1]);
		FBbg_sprite[1].setPosition(FBbg_sprite[0].getPosition().x + FBbg_sprite[0].getGlobalBounds().width, FBbg_sprite[0].getPosition().y);
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

FlappyBurd::~FlappyBurd()
{
}

void FlappyBurd::pause()
{
	set_paused(true);
}

void FlappyBurd::resume()
{
	set_paused(false);
}

void FlappyBurd::update(const sf::Time & delta)
{
	fpBurd.position.y += gravity;
	fpBurd.spr.setPosition(fpBurd.position);
	


	for (int i = 0; i < 4; i++)
	{
		if (pipeSpr[i].getPosition().x < 80)
		{
			srand(time(NULL));
			int randomPipeSpr = rand() % 4;
			pipeSpr[i].setTexture(pipeTex[randomPipeSpr]);
			int newPos = 0;
			if( i==0 )
			newPos = pipeSpr[3].getPosition().x + 280;
			else
				newPos = pipeSpr[i-1].getPosition().x + 280;

			pipeSpr[i].setPosition(newPos, pipeSpr[i].getPosition().y);
		}
	}


	if (FBbg_sprite[0].getPosition().x + FBbg_sprite[0].getGlobalBounds().width <= 0)
		FBbg_sprite[0].setPosition(FBbg_sprite[1].getPosition().x + FBbg_sprite[1].getGlobalBounds().width, FBbg_sprite[1].getPosition().y);
	if (FBbg_sprite[1].getPosition().x + FBbg_sprite[1].getGlobalBounds().width <= 0)
		FBbg_sprite[1].setPosition(FBbg_sprite[0].getPosition().x + FBbg_sprite[0].getGlobalBounds().width, FBbg_sprite[0].getPosition().y);
}

void FlappyBurd::render()
{
	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view

	
	for (int i = 0; i < 2; i++) 
	{
		//float newPos = FBbg_sprite[i].getPosition().x - 0.06f;
		//FBbg_sprite[i].setPosition(newPos, FBbg_sprite[i].getPosition().y);
		window.draw(FBbg_sprite[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		float newPos = pipeSpr[i].getPosition().x - 0.06f;
		pipeSpr[i].setPosition(newPos, pipeSpr[i].getPosition().y);
		window.draw(pipeSpr[i]);
	}
		
	window.draw(logoSpr);
	window.draw(messageText);
	window.draw(fpBurd.spr);
	if (fpBurd.dead)
		gameText.setString("YOU DIED!");


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

void FlappyBurd::handle_input(const sf::Time & delta)
{

	auto inputManager = state_manager_.get_input_manager();
	sf::RenderWindow& window = state_manager_.get_render_window();
	inputManager.giveStateManager(&state_manager_);
	inputManager.setRegionSize();
	inputManager.setwindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	sf::Vector2i windowO(view_main.getCenter().x - view_main.getSize().x / 2, view_main.getCenter().y - view_main.getSize().y / 2);

	mouse_pos.x = windowO.x + inputManager.get_mouse_x();
	mouse_pos.y = windowO.y + inputManager.get_mouse_y();

	//cout << "X. " << mouse_pos.x << "Y. " << mouse_pos.y << endl;
	if (inputManager.is_key_released(InputKey::space))
	{
		fpBurd.position.y -= jump;
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

void FlappyBurd::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (back == true)
		state_current.change_state(state_manager_.state_ptr<GameBox>());
	if (quit == true)
		state_manager_.quit();
}

void FlappyBurd::initGame()
{
}

void FlappyBurd::Reset()
{
}
