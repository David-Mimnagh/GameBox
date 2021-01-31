#include "Hangman.h"



Hangman::Hangman(StateManager& state_manager) : AbstractState(state_manager)
{
	init = true;
	win = false;
	choosing = true;
	fullGuess = false;
	playing = true;
	win = false;
	drawReset = false;
	CatagoryID = 0;
	player.lives = 5;
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
	messageText.setString("Welcome to GameBox - Hangman.");
	messageText.setCharacterSize(24);
	messageText.setPosition(WINDOW_WIDTH / 2 - 250, 200);
	messageText.setFillColor(sf::Color::Blue);

	wordToGuesssCrypticText.setFont(MainFont);
	wordToGuesssCrypticText.setString("");
	wordToGuesssCrypticText.setCharacterSize(24);
	wordToGuesssCrypticText.setPosition(WINDOW_WIDTH / 2 - 205, 750);
	wordToGuesssCrypticText.setFillColor(sf::Color::Blue);

	gameText.setFont(MainFont);
	gameText.setCharacterSize(32);
	gameText.setPosition(WINDOW_WIDTH / 2 - 50, 350);
	gameText.setString("Playing this game is quite simple.\nYou start by selecting a catagory on the left,\na word will then be randomly generated\nfrom that catagory.\nYou then take guesses, one letter at a time\nto complete the word.\nAre you ready? Select a catagory to begin.");
	gameText.setFillColor(sf::Color::Blue);

	livesText.setFont(MainFont);
	
	livesText.setCharacterSize(24);
	livesText.setPosition(WINDOW_WIDTH / 2 - 205, 715);
	livesText.setFillColor(sf::Color::Blue);
	
	if (!HMbackground.loadFromFile("HM/HMbackground.png"))
	{
		std::cout << "Could not load image\n";
	}
	HMbg_sprite.setTexture(HMbackground);
	if (!logoTex.loadFromFile("Logo.png"))
	{
		std::cout << "Could not load image\n";
	}
	logoSpr.setTexture(logoTex);
	logoSpr.setOrigin(logoSpr.getGlobalBounds().width / 2, logoSpr.getGlobalBounds().height / 2);
	logoSpr.setPosition(WINDOW_WIDTH / 2, 100);


	if (!gameTex[0].loadFromFile("HM/Stand-noose.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!gameTex[1].loadFromFile("HM/Stand-HB.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!gameTex[2].loadFromFile("HM/Stand-HBA1.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!gameTex[3].loadFromFile("HM/Stand-HBA2.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!gameTex[4].loadFromFile("HM/Stand-HBAL1.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!gameTex[5].loadFromFile("HM/Stand-HBAL2.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 6; i++)
	{
		gameSpr[i].setTexture(gameTex[i]);
		gameSpr[i].setPosition(WINDOW_WIDTH / 2 - 465, 250);
		gameSpr[i].setScale(2, 2);
	}
	if (!catagoryChoiceTex[0].loadFromFile("HM/TVCat.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!catagoryChoiceTexH[0].loadFromFile("HM/TVCatH.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!catagoryChoiceTex[1].loadFromFile("HM/FilmCat.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!catagoryChoiceTexH[1].loadFromFile("HM/FilmCatH.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!catagoryChoiceTex[2].loadFromFile("HM/CelebCat.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!catagoryChoiceTexH[2].loadFromFile("HM/CelebCatH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			catagoryChoiceSpr[0].setPosition(WINDOW_WIDTH / 2 - 300, 390);
			catagoryChoiceSprH[0].setPosition(WINDOW_WIDTH / 2 - 300, 390);
		}
		else if (i == 1)
		{
			catagoryChoiceSpr[1].setPosition(WINDOW_WIDTH / 2 - 300, 460);
			catagoryChoiceSprH[1].setPosition(WINDOW_WIDTH / 2 - 300, 460);
		}
		else if (i == 2)
		{
			catagoryChoiceSpr[2].setPosition(WINDOW_WIDTH / 2 - 300, 530);
			catagoryChoiceSprH[2].setPosition(WINDOW_WIDTH / 2 - 300, 530);
		}
		catagoryChoiceSpr[i].setTexture(catagoryChoiceTex[i]);
		catagoryChoiceSprH[i].setTexture(catagoryChoiceTexH[i]);
	}
	for (int i = 0; i < 26; i++)
	{
		if (!guessLetter[i].loadFromFile("HM/"+ to_string(i) + ".png"))
		{
			std::cout << "Could not load image\n";
		}
		if (!guessHLetter[i].loadFromFile("HM/" + to_string(i) + "H.png"))
		{
			std::cout << "Could not load image\n";
		}
		guessLetterSpr[i].setTexture(guessLetter[i]);
		guessHLetterSpr[i].setTexture(guessHLetter[i]);
		if (i < 5) 
		{
			guessLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + (i * 65) - 3, 250);
			guessHLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + (i * 65)-3, 250);
		}
		else if (i>4 && i < 10) 
		{
			guessLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i - 5) * 65), 320);
			guessHLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i - 5) * 65), 320);
		}
		else if (i>9 && i < 15)
		{
			guessLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i - 10) * 65), 390);
			guessHLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i - 10)* 65), 390);
		}
		else if (i>14 && i < 20)
		{
			guessLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i -15)* 65), 460);
			guessHLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i - 15)* 65), 460);
		}
		else if (i>19&& i < 25)
		{
			guessLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i-20) * 65), 530);
			guessHLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i-20) * 65), 530);
		}
		else if (i>24)
		{
			guessLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i-25) * 65), 600);
			guessHLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + ((i-25) * 65), 600);
		}
		guessLetterHighlight[i] = false;
	}

	if (!backButton[0].loadFromFile("HM/Back.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!backButton[1].loadFromFile("HM/BackH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 2; i++)
	{
		backButtonSpr[i].setTexture(backButton[i]);
		backButtonSpr[i].setPosition(10, WINDOW_HEIGHT - 80);
	}

	if (!resetButton[0].loadFromFile("HM/reset.png"))
	{
		std::cout << "Could not load image\n";
	}
	if (!resetButton[1].loadFromFile("HM/ResetH.png"))
	{
		std::cout << "Could not load image\n";
	}
	for (int i = 0; i < 2; i++)
	{
		resetButtonSpr[i].setTexture(resetButton[i]);
		resetButtonSpr[i].setPosition(WINDOW_WIDTH - 105, WINDOW_HEIGHT - 80);
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

	CatObject.resize(3);
	CatObject[0].titleName.resize(7);
	CatObject[0].catName = "TV";
	CatObject[0].titleName[0].title = "breaking bad";
	CatObject[0].titleName[1].title = "stranger things";
	CatObject[0].titleName[2].title = "scream";
	CatObject[0].titleName[3].title = "power";
	CatObject[0].titleName[4].title = "family guy";
	CatObject[0].titleName[5].title = "american dad";
	CatObject[0].titleName[6].title = "storage hunters";


	CatObject[1].titleName.resize(7);
	CatObject[1].catName = "Film";
	CatObject[1].titleName[0].title = "catch me if you can";
	CatObject[1].titleName[1].title = "saving private ryan";
	CatObject[1].titleName[2].title = "aladdin";
	CatObject[1].titleName[3].title = "butterfly effect";
	CatObject[1].titleName[4].title = "big daddy";
	CatObject[1].titleName[5].title = "honey i shrunk the kids";
	CatObject[1].titleName[6].title = "wizard of Oz";


	CatObject[2].titleName.resize(7);
	CatObject[2].catName = "Celebrity";
	CatObject[2].titleName[0].title = "howard stern";
	CatObject[2].titleName[1].title = "tom hanks";
	CatObject[2].titleName[2].title = "megan fox";
	CatObject[2].titleName[3].title = "scarlett johanson";
	CatObject[2].titleName[4].title = "kit harrington";
	CatObject[2].titleName[5].title = "peter dinklage";
	CatObject[2].titleName[6].title = "brad pitt";
}


Hangman::~Hangman()
{
}
void Hangman::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (back == true)
		state_current.change_state(state_manager_.state_ptr<GameBox>());
	if (quit == true)
		state_manager_.quit();

	if (getWinState() == true)
		drawReset = true;
}
void Hangman::update(const sf::Time& delta)
{
	if (getPlayingState())
		PlayerTurn();
}

void Hangman::pause()
{
	set_paused(true);
}

void Hangman::resume()
{
	set_paused(false);
}

void Hangman::handle_input(const sf::Time& delta)
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
	if (backHighlight == true)
		if (inputManager.left_clicked())
			back = true;
	if (drawReset == false)
	{
		for (int i = 0; i < 26; i++)
		{
			if (guessLetterSpr[i].getGlobalBounds().contains(mouse_pos))
			{
				guessLetterHighlight[i] = true;
			}
			else
				guessLetterHighlight[i] = false;
		}
	}


	for (int i = 0; i < 3; i++)
	{
		if (catagoryChoiceSpr[i].getGlobalBounds().contains(mouse_pos))
		{
			catHighlight[i] = true;
		}
		else
			catHighlight[i] = false;
	}

	if (resetHighlight == true)
		if (inputManager.left_clicked())
		{
			Reset();
			initGame();
			Sleep(600);
		}
	for (int i = 0; i < 3; i++)
	{
		if (catHighlight[i]) 
		{
			if (inputManager.left_clicked())
			{
				if (i == 0)
				{
					catagoryChoice = "TV";
					choosing = false;
				}
				else if (i == 1) 
				{
					catagoryChoice = "Film";
					choosing = false;
				}
				else if (i == 2) 
				{
					catagoryChoice = "Celebrity";
					choosing = false;
				}
				Sleep(600);
			}
		}
	}
	if (choosing == false)
	{
		if (init == true)
			RandomWord();

	}
	if (choosing == false)
	{
		if (win == false)
		{
			newWord.resize(wordToGuessCryptic.length() * 2);
			int j = 0;
			for (int i = 0; i < wordToGuessCryptic.length();i++)
			{
				if (wordToGuessCryptic[i] == '_')
				{
					newWord[j] = wordToGuessCryptic[i];
					newWord[j + 1] = ' ';
				}
				if (wordToGuessCryptic[i] == ' ')
				{
					newWord[j] = ' ';
					newWord[j + 1] = ' ';
				}
				if (wordToGuessCryptic[i] != '_' || wordToGuessCryptic[i] != ' ')
				{
					newWord[j] = wordToGuessCryptic[i];
					newWord[j + 1] = ' ';
				}
				j += 2;

			}
			wordToGuesssCrypticText.setString(newWord);
		}

		livesText.setString("Current Lives: [" + to_string(player.lives) + "].");

		if (waitForGuess == true)
		{
			if (getPlayingState())
			{
				for (int i = 0; i < 26; i++)
				{
					if (guessLetterHighlight[i])
					{
						if (inputManager.left_clicked())
						{
							if (i == 0)
								player.guess = "a";
							else if (i == 1)
								player.guess = "b";
							else if (i == 2)
								player.guess = "c";
							else if (i == 3)
								player.guess = "d";
							else if (i == 4)
								player.guess = "e";
							else if (i == 5)
								player.guess = "f";
							else if (i == 6)
								player.guess = "g";
							else if (i == 7)
								player.guess = "h";
							else if (i == 8)
								player.guess = "i";
							else if (i == 9)
								player.guess = "j";
							else if (i == 10)
								player.guess = "k";
							else if (i == 11)
								player.guess = "l";
							else if (i == 12)
								player.guess = "m";
							else if (i == 13)
								player.guess = "n";
							else if (i == 14)
								player.guess = "o";
							else if (i == 15)
								player.guess = "p";
							else if (i == 16)
								player.guess = "q";
							else if (i == 17)
								player.guess = "r";
							else if (i == 18)
								player.guess = "s";
							else if (i == 19)
								player.guess = "t";
							else if (i == 20)
								player.guess = "u";
							else if (i == 21)
								player.guess = "v";
							else if (i == 22)
								player.guess = "w";
							else if (i == 23)
								player.guess = "x";
							else if (i == 24)
								player.guess = "y";
							else if (i == 25)
								player.guess = "z";

							cout << "Guess: " << player.guess << endl;
							waitForGuess = false;
							PlayerTurn();
							Sleep(600);
						}
					}
				}
			}

		}
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
void Hangman::render()
{
	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view
	window.draw(HMbg_sprite);
	window.draw(logoSpr);
	window.draw(messageText);

	if (choosing == true)
	window.draw(gameText);

	window.draw(pointsText);
	if (choosing == false)
	{
		if (!drawReset)
		window.draw(livesText);

		window.draw(wordToGuesssCrypticText);
	}	
	if (choosing == true)
	{
		for (int i = 0; i < 3; i++)
		{
			if(catHighlight[i] == true)
				window.draw(catagoryChoiceSprH[i]);
			else
				window.draw(catagoryChoiceSpr[i]);
		}
	}
	if (drawReset == false)
	{
		if (choosing == false)
		{
			if (player.lives == 5)
				window.draw(gameSpr[0]);
			else if (player.lives == 4)
				window.draw(gameSpr[1]);
			else if (player.lives == 3)
				window.draw(gameSpr[2]);
			else if (player.lives == 2)
				window.draw(gameSpr[3]);
			else if (player.lives == 1)
				window.draw(gameSpr[4]);
			else if (player.lives == 0)
				window.draw(gameSpr[5]);
		}

		if (choosing == false)
		{
			for (int i = 0; i < 26; i++)
			{
				if (guessLetterHighlight[i])
					window.draw(guessHLetterSpr[i]);
				else
					window.draw(guessLetterSpr[i]);
			}
		}
	}
	if (drawReset == true)
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

	
	waitForGuess = true;
}
void Hangman::initGame()
{

}
void Hangman::RandomWord()
{
	vectorCounter = 0;
	for (int i = 0; i < CatObject.size(); i++)
	{
		cout << "\t\t-> " << CatObject[i].catName << endl;
	}
	for (auto &choice : CatObject)
	{
		vectorCounter++;
		if (catagoryChoice == choice.catName)
		{
			choosing = false;
			CatagoryID = vectorCounter - 1;
		}

	}
	srand(time(NULL));
	randomWordID = rand() % 7 + 0;
	wordToGuess = CatObject[CatagoryID].titleName[randomWordID].title;
	word = wordToGuess;
	wordToGuessCryptic = wordToGuess;
	ConvertWord();
	init = false;
	win = false;
	setPlayingState(true);
	waitForGuess = true;
}
void Hangman::ConvertWord()
{
	for (char&c : wordToGuessCryptic)
	{
		if (c != ' ') 
			c = '_';
		else
			c = ' ';
		
	}
}
void Hangman::PlayerGuess()
{
	sf::RenderWindow& window = state_manager_.get_render_window();

	auto inputManager = state_manager_.get_input_manager();
	
}
void Hangman::PlayerTurn()
{
		if (waitForGuess == false)
		{
			if (wordToGuessCryptic != word)
			{
				cout << "\nAlright, it's your go." << endl;
				cout << "Your word to guess: \n\t" << wordToGuessCryptic << endl;

				if (getPlayingState())
				{

					currentProgressWord = wordToGuessCryptic;
					wordToGuesssCrypticText.setString(currentProgressWord);
					player.tryCount++;

					if (wordToGuess.find(player.guess) != -1)
					{
						while (wordToGuess.find(player.guess) != -1)
						{
							wordToGuessCryptic.replace(wordToGuess.find(player.guess), 1, (player.guess));
							wordToGuess.replace(wordToGuess.find(player.guess), 1, "_");
						}
					}
					else
					{
						cout << "\nUnfortunately, that is not a letter in the word!\n\n";
						if (player.lives >= 1)
							player.lives -= 1;
						else
						{
							setPlayingState(false);
							cout << "\nOUCH, GAME OVER!\n\n";
							system("pause");
						}
					}
				}
			}


			if (player.tryCount >= 2)
			if (wordToGuessCryptic == word)
			{
				cout << "\nYour word that you guessed: " << word;
				if (!fullGuess)
				{
						cout << "Holy smokes! You got that in " << player.tryCount << " tries.\n\n" << endl;
				}
				cout << "\n\nYou win!" << endl;
				wordToGuesssCrypticText.setPosition(WINDOW_WIDTH / 2 - 275, 350);
				wordToGuesssCrypticText.setString("Hey! Good job you managed to guess: '" + word + "' in [" + to_string(player.tryCount) +"] tries!\n\t\t\tYou gained a total of [" + to_string(player.lives + 1)+"] points this game.");
				state_manager_.setPoints(state_manager_.getPoints() + player.lives + 1);
				setWinState(true);
				setPlayingState(false);
				drawReset = true;
				
			}
	}
		waitForGuess = true;
}



	

void Hangman::Playing()
{
}
void Hangman::Reset()
{
	init = true;
	win = false;
	choosing = true;
	fullGuess = false;
	playing = true;
	win = false;
	drawReset = false;
	wordToGuesssCrypticText.setString("");
	wordToGuesssCrypticText.setPosition(WINDOW_WIDTH / 2 - 205, 750);
	player.guess = "";
	CatagoryID = 0;
	vectorCounter = 0;
	catagoryChoice = "";
	player.lives = 5;
}