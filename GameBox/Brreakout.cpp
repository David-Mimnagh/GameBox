#include "Brreakout.h"



Breakout::Breakout(StateManager& state_manager) : AbstractState(state_manager)
{
	player.lives = 5;
	player.pos.x = WINDOW_WIDTH /2; player.pos.y = 930 - (player.spr.getGlobalBounds().height);
	player.score = 0;
	player.tex.loadFromFile("Br/PlayerPaddle.png");
	player.spr.setTexture(player.tex);
	player.spr.setOrigin(player.spr.getGlobalBounds().width / 2, player.spr.getGlobalBounds().height / 2);
	player.spr.setPosition(player.pos);

	ball.pos.x = player.pos.x + ball.direction.x; 
	ball.pos.y = (player.pos.y - 30) + ball.direction.y;
	ball.currentSpeed = 3.0f;
	ball.speedModifier = 0.2f;
	ball.direction.x = 3.0f; ball.direction.y = 3.0f;
	ball.tex.loadFromFile("Br/Ball.png");
	ball.spr.setTexture(ball.tex);
	ball.spr.setOrigin(ball.spr.getGlobalBounds().width / 2, ball.spr.getGlobalBounds().height / 2);
	ball.spr.setPosition(ball.pos);
	
	for (int i = 0; i < 48; i++)
	{
		gameWon[i] = false;
		blockList.resize(48);
		blockList[i].draw = true;
		if (i < 12) {
			blockList[i].tex.loadFromFile("Br/Brick1.png");
			blockList[i].spr.setTexture(blockList[i].tex);
			blockList[i].scoreToGive = 1;
			blockList[i].typeId = 1;
			blockList[i].pos = sf::Vector2f(90 + (i * 100), 400);
			blockList[i].spr.setOrigin(blockList[i].spr.getGlobalBounds().width / 2, blockList[i].spr.getGlobalBounds().height / 2);
			blockList[i].spr.setPosition(blockList[i].pos);
		}
		else if (i > 11 && i < 24 ) {
			blockList[i].tex.loadFromFile("Br/Brick2.png");
			blockList[i].spr.setTexture(blockList[i].tex);
			blockList[i].scoreToGive = 2;
			blockList[i].typeId = 2;
			blockList[i].pos = sf::Vector2f(90 + ((i-12) * 100), 350);
			blockList[i].spr.setOrigin(blockList[i].spr.getGlobalBounds().width / 2, blockList[i].spr.getGlobalBounds().height / 2);
			blockList[i].spr.setPosition(blockList[i].pos);
		}
		else if (i > 23 && i < 36) {
			blockList[i].tex.loadFromFile("Br/Brick3.png");
			blockList[i].spr.setTexture(blockList[i].tex);
			blockList[i].scoreToGive = 3;
			blockList[i].typeId = 3;
			blockList[i].pos = sf::Vector2f(90 + ((i-24) * 100),300);
			blockList[i].spr.setOrigin(blockList[i].spr.getGlobalBounds().width / 2, blockList[i].spr.getGlobalBounds().height / 2);
			blockList[i].spr.setPosition(blockList[i].pos);
		}
		else if (i > 35 && i < 48) {
			blockList[i].tex.loadFromFile("Br/Brick4.png");
			blockList[i].spr.setTexture(blockList[i].tex);
			blockList[i].scoreToGive = 4;
			blockList[i].typeId = 4;
			blockList[i].pos = sf::Vector2f(90 + ((i-36) * 100), 250);
			blockList[i].spr.setOrigin(blockList[i].spr.getGlobalBounds().width / 2, blockList[i].spr.getGlobalBounds().height / 2);
			blockList[i].spr.setPosition(blockList[i].pos);
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
	messageText.setString("Welcome to GameBox - Breakout.");
	messageText.setCharacterSize(18);
	messageText.setOrigin(messageText.getGlobalBounds().width / 2, messageText.getGlobalBounds().height / 2);
	messageText.setPosition(WINDOW_WIDTH / 2, 182);
	messageText.setFillColor(sf::Color::Red);

	pointsText.setFont(MainFont);
	pointsText.setString("Points: [" + to_string(player.score) +"]");
	pointsText.setOrigin(pointsText.getGlobalBounds().width / 2, pointsText.getGlobalBounds().height / 2);
	pointsText.setCharacterSize(18);
	pointsText.setPosition(0 + (pointsText.getGlobalBounds().width * 2), 187);
	pointsText.setFillColor(sf::Color::Red);

	livesText.setFont(MainFont);
	livesText.setString("Lives: [" + to_string(player.lives) + "]");
	livesText.setOrigin(livesText.getGlobalBounds().width / 2, livesText.getGlobalBounds().height / 2);
	livesText.setCharacterSize(18);
	livesText.setPosition(WINDOW_WIDTH - (livesText.getGlobalBounds().width * 2), 187);
	livesText.setFillColor(sf::Color::Red);

	gameText.setFont(MainFont);
	gameText.setString("Press 'Space' to start playing");
	gameText.setOrigin(gameText.getGlobalBounds().width / 2, gameText.getGlobalBounds().height / 2 - 50);
	gameText.setCharacterSize(28);
	gameText.setPosition(WINDOW_WIDTH /2, WINDOW_HEIGHT/ 2);
	gameText.setFillColor(sf::Color::Red);

	if (!Brbackground.loadFromFile("Br/BrBackground.png"))
	{
		std::cout << "Could not load image\n";
	}
	Brbg_sprite.setTexture(Brbackground);
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
		backButtonSpr[i].setPosition(10, 0 + 60);
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
		resetButtonSpr[i].setPosition(WINDOW_WIDTH - 160, 0 + 60);
	}
	initGame();
}

void Breakout::initGame()
{
	playing = false;
}

Breakout::~Breakout()
{
}

void Breakout::pause()
{
	set_paused(true);
}

void Breakout::resume()
{
	set_paused(false);
}

void Breakout::setVel(sf::Vector2f vel)
{
	ball.direction = vel;
}
void Breakout::update(const sf::Time & delta)
{
	for (int i = 0; i < blockList.size(); i++)
	{
		if (blockList[i].draw == false)
			gameWon[i] = true;
	
	if (std::all_of(std::begin(gameWon),
		std::end(gameWon),[](bool i)
	{
		return i; // or return !i ;
	})) {
		win = true;
		playing = false;
		break;
	}
	}
		player.spr.setPosition(player.pos);
		if (player.spr.getPosition().x <= 0 + player.spr.getGlobalBounds().width / 2) 
		{
			player.pos.x = 0 + player.spr.getGlobalBounds().width / 2;
			player.spr.setPosition(player.spr.getGlobalBounds().width / 2, player.spr.getPosition().y);
		}
		else if (player.spr.getPosition().x >= WINDOW_WIDTH - player.spr.getGlobalBounds().width /2)
		{
			player.pos.x = WINDOW_WIDTH - player.spr.getGlobalBounds().width / 2;
			player.spr.setPosition(WINDOW_WIDTH - player.spr.getGlobalBounds().width / 2, player.spr.getPosition().y);
		}
		if (!playing) 
		{
			ball.pos.x = player.pos.x + ball.direction.x;
			ball.pos.y = (player.pos.y - 30) + ball.direction.y;
			ball.spr.setPosition(ball.pos);
		}
	if (playing)
	{
		
		ball.spr.move(ball.direction);
		// LEFT WALL
		if (ball.spr.getPosition().x + ball.spr.getGlobalBounds().width /2 <= 0) {
			setVel(sf::Vector2f((ball.direction.x * -1), ball.direction.y));
			ball.pos.x = 0;
			ball.spr.setPosition(0, ball.spr.getPosition().y);
		} //RIGHT WALL
		else if (ball.spr.getPosition().x + ball.spr.getGlobalBounds().width /2 >= WINDOW_WIDTH)
		{
			setVel(sf::Vector2f((ball.direction.x * - 1),ball.direction.y ));
			ball.pos.x = WINDOW_WIDTH - ball.spr.getGlobalBounds().width;
			ball.spr.setPosition(WINDOW_WIDTH - ball.spr.getGlobalBounds().width, ball.spr.getPosition().y);
		}//TOP
		else if (ball.spr.getPosition().y <= 205) {
			//ball.direction.y = ball.currentSpeed * -mi(ball.direction.y);
			ball.direction.y *= -1;
		}//BOTTOM
		else if (ball.spr.getPosition().y >= WINDOW_HEIGHT - ball.spr.getGlobalBounds().height)
		{
			ball.direction.y *= -1;
			player.lives--;
			ball.pos = sf::Vector2f(WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2 - 15);
			playing = false;
			ball.spr.setPosition(ball.pos);
		}
		//PLAYER
		 if (ball.spr.getGlobalBounds().intersects(player.spr.getGlobalBounds()))
		{
			setVel(sf::Vector2f(ball.direction.x, (ball.direction.y * -1)));
		}
		 //BLOCKS
		 for (auto& block : blockList)
		 {
			 if (ball.spr.getGlobalBounds().intersects(block.spr.getGlobalBounds()) && block.draw == true)
			 {
				 //RIGHT HAND SIDE
				 if ( ball.pos.x + ball.spr.getGlobalBounds().width >= block.pos.x + block.spr.getGlobalBounds().width)
				 {
					 setVel(sf::Vector2f((ball.direction.x * -1), ball.direction.y));
					 //ball.pos.x += ball.direction.x;
				 }
				 // next, check if it has hit the left hand side of the box
				 else if (ball.pos.x + ball.spr.getGlobalBounds().width <= block.pos.x)
				 {
					 setVel(sf::Vector2f((ball.direction.x * -1), ball.direction.y));
					// ball.pos.x += ball.direction.x;
				 }
				 // next, check if it has hit the bottom of the box
				 else if (ball.pos.y + ball.spr.getGlobalBounds().height <= block.pos.y)
				 {
					 setVel(sf::Vector2f(ball.direction.x, (ball.direction.y * -1)));
					 //ball.pos.y += ball.direction.y;
				 }
				 // next, check if it has hit the top of the box
				 else if (ball.pos.y + ball.spr.getGlobalBounds().height >= block.pos.y + block.spr.getGlobalBounds().height)
				 {
					 setVel(sf::Vector2f(ball.direction.x, (ball.direction.y * -1)));
					 //ball.pos.y += ball.direction.y;
				 }
				 player.score += block.scoreToGive;
				 block.draw = false;
				 
				 break;
			 }
		 }
	
		ball.pos += ball.direction;
		//ball.pos = sf::Vector2f(ball.direction);
		ball.spr.setPosition(ball.pos);
	}
}

void Breakout::render()
{
	sf::RenderWindow& window = state_manager_.get_render_window();
	pointsText.setString("Points: [" + to_string(player.score) + "]");
	livesText.setString("Lives: [" + to_string(player.lives) + "]");
	window.setView(view_main); // applying the view
	window.draw(Brbg_sprite);
	window.draw(player.spr);
	window.draw(ball.spr);
	window.draw(logoSpr);
	window.draw(messageText);
	window.draw(livesText);
	window.draw(pointsText);
	if (win)
		gameText.setString("YOU WIN!");

	if (!playing)
		window.draw(gameText);

	for (int i = 0; i < 48; i++) {
		if(blockList[i].draw)
		window.draw(blockList[i].spr);

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

}

void Breakout::handle_input(const sf::Time & delta)
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
	if (inputManager.is_key_released(InputKey::space))
	{
		if (!playing) {
			playing = true;
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

	if (inputManager.is_key_pressed(InputKey::left))
			player.pos.x -= 8;
		else
			if (inputManager.is_key_pressed(InputKey::right))
				player.pos.x += 8;
			else
				player.pos.x = player.pos.x;

}

void Breakout::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (back == true)
		state_current.change_state(state_manager_.state_ptr<GameBox>());
	if (quit == true)
		state_manager_.quit();
}

void Breakout::Reset()
{
}
