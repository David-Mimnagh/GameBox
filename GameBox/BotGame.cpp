#include "BotGame.h"
const int boardXLength = 25;
const int boardYLength = 25;
sf::Texture boardTex[boardYLength][boardXLength];
sf::Sprite boardSpr[boardYLength][boardXLength];
char board[boardYLength][boardXLength];
std::vector<int> pos; std::vector<int> botPos;
int botPosX = 0;
int botPosY = 0;
int bombCount = 0;
string lastDir;
int playerLives = 3;
std::vector<Key> BotInvent;
Level currLevel;
int currentLevelNumber = 1;
const char* node_types[] =
{
	"null", "document", "element", "pcdata", "cdata", "comment", "pi", "declaration"
};
BotGame::BotGame(StateManager & state_manager)  : AbstractState(state_manager)
{
	

	backHighlight = false;
	drawReset = false;
	view_main.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	view_main.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

	int currentX =  (WINDOW_WIDTH / 4) - 25; 
	int currentY = 225;
	
	for (size_t i = 0; i < boardYLength; i++)
	{
		currentY += 25;
		currentX = (WINDOW_WIDTH / 4) - 25;
		for (size_t j = 0; j < boardXLength; j++)
		{
			currentX += 25;
			if (i == 0 || i == boardYLength - 1)
			{
				board[i][j] = '#';
			}
			else if (j == 0 ||j == boardXLength - 1)
			{
				board[i][j] = '#';
			}
			else if (i == 1&& j == 1)
			{
				board[i][j] = 'B';
				
			}
			else if (i == 3 && j == 23)
			{
				board[i][j] = 'E';
				Exit e;
				e.XPos = j; e.YPos = i;
				currLevel.Exit = e;
			}
			else if (i <= 15 && j == 10)
			{
				board[i][j] = 'W';
				Wall W;
				W.Breakable = false;
				W.Horizontal = false;
				W.YPos = i; W.XPos = j;
				currLevel.Walls.push_back(W);
			}
			else if (i >= 16 && j == 10)
			{
				board[i][j] = 'w';
				Wall w;
				w.Breakable = false;
				w.Horizontal = false;
				w.YPos = i; w.XPos = j;
				currLevel.Walls.push_back(w);
			}
			else if (i == 15 && j >= 10)
			{
				if (j == 20)
				{
					board[i][j] = 'G';
					Gate g;
					g.GateID = 1;
					g.XPos = j; g.YPos = i;
					currLevel.Gates.push_back(g);
				}
				else
				{
					board[i][j] = 'W';
					Wall W;
					W.Breakable = false;
					W.Horizontal = false;
					W.YPos = i; W.XPos = j;
					currLevel.Walls.push_back(W);
				}
				
			}
			else if (i == 16 && j == 16)
			{
				board[i][j] = 'K';
				Key k;
				k.GateID = 1;
				k.XPos = j; k.Ypos = j;
				BotInvent.push_back(k);
				currLevel.Keys.push_back(k);
			}
			else 
			{
				board[i][j] = '-';
			}

			boardSpr[i][j].setPosition(currentX, currentY);
		}
	}

	/*guessLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + (i * 65) - 3, 250);
	guessHLetterSpr[i].setPosition(WINDOW_WIDTH / 2 + (i * 65) - 3, 250);*/


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

	if (!BGbackground.loadFromFile("BG/BGBackground.png"))
	{
		std::cout << "Could not load image\n";
	}
	BGbg_sprite.setTexture(BGbackground);

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
	bombCount = 3;
	Level l = LoadLevelFromFile(currentLevelNumber);
	initGame();
}

BotGame::~BotGame()
{
}
Level BotGame::LoadLevelFromFile(int currentLevel) 
{
	string fileName = "level_" + to_string(currentLevel)+".xml";
	doc.load_file(fileName.c_str());
	Level newLevel = currLevel;
	Exit e;
	pugi::xml_node root = doc.document_element();
	struct simple_walker : pugi::xml_tree_walker
	{
		virtual bool for_each(pugi::xml_node& node)
		{
			for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation

			std::cout << node_types[node.type()] << ": name='" << node.name() << "', value='" << node.value() << "'\n";
			string lastNode = "";
			switch (node.type())
			{
				//Element
				case 'e':
					
					lastNode = node.name();
					break;
				case pugi::node_pcdata:
					if (lastNode == "BoardWidth") {
						currLevel.BoardWidth = (int)node.value();
					}
					else if (lastNode == "BoardHeight") {
						currLevel.BoardHeight = (int)node.value();

					}
					else if (lastNode == "Walls") {

					}
					else if (lastNode == "Wall") {

					}
					else if (lastNode == "XPos") {

					}
					else if (lastNode == "XLength") {

					}
					else if (lastNode == "YPos") {

					}
					else if (lastNode == "YLength") {

					}
					else if (lastNode == "Horizontal") {

					}
					else if (lastNode == "Breakable") {

					}
					else if (lastNode == "Exit") {
						if (lastNode == "XPos") {

						}
						else if (lastNode == "XPos") {

						}
					}
					else if (lastNode == "Gates") {

					}
					else if (lastNode == "Gate") {

					}
					else if (lastNode == "GateID") {

					}
					else if (lastNode == "Keys") {

					}
					else if (lastNode == "Key") {

					}
					break;
				default:
					break;
			}
			return true; // continue traversal
		}
	};
	simple_walker walker;
	doc.traverse(walker);
	int x = 2;
	
	return currLevel;
}
void BotGame::load_level(Level l)
{
	char boardNew[boardYLength][boardXLength];
	
	//ADD IN THE OUTER AREA
	for (int i = 0; i < boardYLength; i++)
	{
		for (int j = 0; j < boardXLength; j++)
		{

			if (i == 0 || j == 0 || i == boardYLength - 1 || j == boardXLength - 1)
			{
				boardNew[i][ j] = '#';
			}
			else
			{
				boardNew[i][ j] = '-';
			}
		}

	}
	for (int i = 0; i < boardYLength; i++)
	{
		for (int j = 0; j < boardXLength; j++)
		{
			if (i == l.Exit.YPos)
			{
				if (j == l.Exit.XPos)
				{
					boardNew[i][ j] = 'E'; // add in the exit
				}
			}
		}
	}
	//ADD IN THE WALLS
	for (size_t i = 0; i < l.Walls.size(); i++)
	{
		Wall W = l.Walls[i];
		for (int i = 0; i < boardYLength; i++)
		{
			for (int j = 0; j < boardXLength; j++)
			{
				if (W.Horizontal)
				{
					if (i == W.YPos)
					{
						int length = 0;
						if (W.XLength == 0)
							length = boardXLength - 2;
						else
							length = W.XPos + W.XLength;

						if (j >= W.XPos && j <= length)
						{
							if (W.Breakable == true)
								boardNew[i][ j] = 'w';
							else
								boardNew[i][ j] = 'W';
						}
					}
				}
				else
				{
					if (i >= 1)
					{
						int length = 0;
						if (W.YLength == 0)
							length = boardYLength - 2;
						else
							length = W.YPos + W.YLength;

						if (i >= W.YPos && i <= length)
						{
							if (i <= boardYLength - 2)
							{
								if (j == W.XPos)
								{
									if (W.Breakable == true)
										boardNew[i][ j] = 'w';
									else
										boardNew[i][ j] = 'W';
								}
							}
						}
					}
				}
			}
		}
	}


	//ADD IN THE KEYS
	for (size_t i = 0; i < l.Keys.size(); i++)
	{
		Key k = l.Keys[i];
		for (int i = 0; i < boardYLength; i++)
		{
			for (int j = 0; j < boardXLength; j++)
			{
				if (i == k.Ypos)
				{
					if (j == k.XPos)
					{
						boardNew[i][ j] = 'K';
					}
				}
			}
		}
	}

	//ADD IN THE GATES
	for (size_t i = 0; i < l.Gates.size(); i++)
	{
		Gate g = l.Gates[i];
		for (int i = 0; i < boardYLength; i++)
		{
			for (int j = 0; j < boardXLength; j++)
			{
				if (i == g.YPos)
				{
					if (j == g.XPos)
					{
						boardNew[i][ j] = 'G';
					}
				}
			}
		}
	}
	for (size_t i = 0; i < boardYLength; i++)
	{
		for (size_t j = 0; j < boardXLength; j++)
		{
			board[i][j] = boardNew[i][j];
		}

	}
}
void BotGame::pause()
{
	set_paused(true);
}

void BotGame::resume()
{
	set_paused(false);
}
void BotGame::get_bot_pos(char board[25][25])
{
	bool found = false;
	for (int i = 0; i < boardYLength; i++)
	{
		for (int j = 0; j < boardXLength; j++)
		{
			if (board[i][j] == 'B')
			{
				botPosY = i;
				botPosX = j;
				found = true;
				break;
			}
		}
		if (found)break;
	}
}
void BotGame::placeBomb(char board[25][25])
{
	get_bot_pos(board);
	int oldX = botPosX; int oldY = botPosY;
	if (bombCount >= 1)
	{
		
		bombCount--;
		if (lastDir == "left")
		{
			move_player("right", board);
		}
		else if (lastDir == "right")
		{
			move_player("left", board);
		}
		else if (lastDir == "up")
		{
			move_player("down", board);
		}
		else if (lastDir == "down")
		{
			move_player("up", board);
		}
		board[oldY][oldX] = 'X';
	}
}
void BotGame::detonateBomb(char board[25][25])
{
	get_bot_pos(board);
	int oldX = botPosX; int oldY = botPosY;
	for (int i = 0; i < boardYLength; i++)
	{
		for (int j = 0; j < boardXLength; j++)
		{
			if (board[i][ j] == 'X')
			{
				//top left
				if (board[i - 1][ j - 1] == 'w')
					board[i - 1][ j - 1] = '-';
				else if (board[i - 1][ j - 1] == 'B')
				{
					board[i - 1][ j - 1] = '-';
					board[1][ 1] = 'B';
					playerLives -= 1;
				}
				//top 
				if (board[i - 1][ j] == 'w')
					board[i - 1][ j] = '-';
				else if (board[i - 1][ j] == 'B')
				{
					board[i - 1][ j] = '-';
					board[1][ 1] = 'B';
					playerLives -= 1;
				}
				//top right
				if (board[i - 1][ j + 1] == 'w')
					board[i - 1][ j + 1] = '-';
				else if (board[i - 1][ j + 1] == 'B')
				{
					board[i - 1][ j + 1] = '-';
					board[1][ 1] = 'B';
					playerLives -= 1;
				}
				// left
				if (board[i][ j - 1] == 'w')
					board[i][ j - 1] = '-';
				else if (board[i][ j - 1] == 'B')
				{
					board[i][ j - 1] = '-';
					board[1][ 1] = 'B';
					playerLives -= 1;
				}
				//center
				board[i][ j] = '-';
				bombCount += 1;
				//right
				if (board[i][ j + 1] == 'w')
					board[i][ j + 1] = '-';
				else if (board[i][ j + 1] == 'B')
				{
					board[i][ j + 1] = '-';
					board[1][ 1] = 'B';
					playerLives -= 1;
				}
				//bottom left
				if (board[i + 1][ j - 1] == 'w')
					board[i + 1][ j - 1] = '-';
				else if (board[i + 1][ j - 1] == 'B')
				{
					board[i + 1][ j - 1] = '-';
					board[1][ 1] = 'B';
					playerLives -= 1;
				}
				//bottom 
				if (board[i + 1][ j] == 'w')
					board[i + 1][ j] = '-';
				else if (board[i + 1][ j] == 'B')
				{
					board[i + 1][ j] = '-';
					board[1][ 1] = 'B';
					playerLives -= 1;
				}
				//bottom right
				if (board[i + 1][ j + 1] == 'w')
					board[i + 1][ j + 1] = '-';
				else if (board[i + 1][ j] == 'B')
				{
					board[i + 1][ j + 1] = '-';
					board[1][ 1] = 'B';
					playerLives -= 1;
				}
			}
		}
	}
}
void BotGame::add_key_to_invent(int posY, int posX)
{
	size_t size = currLevel.Keys.size();
	for (size_t i = 0; i < size; i++)
	{
		Key k = currLevel.Keys[i];
		if (posX == k.XPos)
		{
			if (posY == k.Ypos)
			{
				BotInvent.push_back(k);
			}
		}
	}
	/*foreach(var k in curreLevel.Keys)
	{
		if (posX == k.XPos)
		{
			if (posY == k.Ypos)
			{
				BotInvent.Add(k);
			}
		}
	}*/
}
bool BotGame::check_player_invent(int posY, int posX )
{
	int gId = 0;
	bool hasKey = false;
	Gate g;
	for (size_t i = 0; i < currLevel.Gates.size(); i++)
	{
		g = currLevel.Gates[i];
		if (posX == g.XPos)
		{
			if (posY == g.YPos)
			{
				gId = g.GateID;
			}
		}
	}
	for (size_t i = 0; i <  BotInvent.size(); i++)
	{
		Key k = BotInvent[i];
		if (k.GateID == gId)
		{
			hasKey = true;
			break;
		}
	}
	/*foreach(var g in curreLevel.Gates)
	{
		if (posX == g.XPos)
		{
			if (posY == g.YPos)
			{
				gId = g.GateID;
			}
		}
	}
	foreach(var k in BotInvent)
	{
		if (k.GateID == gId)
		{
			hasKey = true;
			break;
		}
	}*/
	return hasKey;
}
void BotGame::move_player(std::string dir, char board[25][25])
{
	get_bot_pos(board);

	if (dir == "up")
	{
	 	if (board[botPosY  - 1][botPosX] == '#' || board[botPosY  - 1][botPosX] == 'W')
		{
			board[botPosY ][botPosX] = 'B';
			
		}
		else if (board[botPosY  - 1][botPosX] == 'w')
		{
			board[botPosY ][botPosX] = 'B';
			
		}
		else if (board[botPosY  - 1][botPosX] == 'G')
		{
			if (check_player_invent(botPosY - 1, botPosX))
			{
				board[botPosY][botPosX] = '-';
				board[botPosY  - 1][botPosX] = 'B';
			}
			else
			{
			board[botPosY ][botPosX] = 'B';
				
			}
		}
		else if (board[botPosY  - 1][botPosX] == 'K')
		{
			add_key_to_invent(botPosY - 1, botPosX);
			board[botPosY ][botPosX] = '-';
			board[botPosY  - 1][botPosX] = 'B';
		}
		else if (board[botPosY  - 1][botPosX] == 'E')
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY  - 1][botPosX] = 'B';
		}
		else if (board[botPosY  - 1][botPosX] == 'X')
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY  - 1][botPosX] = 'B';
			bombCount += 1;
		}
		else
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY  - 1][botPosX] = 'B';
		}
	}
	if (dir == "down")
	{
		if (board[botPosY  + 1][botPosX] == '#' || board[botPosY  + 1][botPosX]== 'W')
		{
			board[botPosY ][botPosX] = 'B';
		}
		else if (board[botPosY  + 1][botPosX]== 'w')
		{
			board[botPosY ][botPosX] = 'B';
		}
		else if (board[botPosY  + 1][botPosX]== 'G')
		{
			if (check_player_invent(botPosY + 1, botPosX))
			{
				board[botPosY][botPosX] = '-';
				board[botPosY  + 1][botPosX]= 'B';
			}
			else
			{
				board[botPosY ][botPosX] = 'B';
			}
		}
		else if (board[botPosY  + 1][botPosX]== 'K')
		{
			add_key_to_invent(botPosY + 1, botPosX);
			board[botPosY ][botPosX] = '-';
			board[botPosY  + 1][botPosX]= 'B';
		}
		else if (board[botPosY  + 1][botPosX]== 'E')
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY  + 1][botPosX]= 'B';
		}
		else if (board[botPosY  + 1][botPosX]== 'X')
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY  + 1][botPosX]= 'B';
			bombCount += 1;
		}
		else
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY  + 1][botPosX]= 'B';
		}
	}
	if (dir == "left")
	{
		if (board[botPosY ][botPosX-1]  == '#' || board[botPosY ][botPosX-1]  == 'W')
		{
			board[botPosY ][botPosX] = 'B';
			
		}
		else if (board[botPosY ][botPosX-1]  == 'w')
		{
			board[botPosY ][botPosX] = 'B';
			
		}
		else if (board[botPosY ][botPosX-1]  == 'G')
		{
			if (check_player_invent(botPosY, botPosX - 1))
			{
				board[botPosY ][botPosX] = '-';
				board[botPosY ][botPosX-1]  = 'B';
			}
			else
			{
				board[botPosY ][botPosX] = 'B';
				
			}
		}
		else if (board[botPosY ][botPosX-1]  == 'K')
		{
			add_key_to_invent(botPosY, botPosX - 1);
			board[botPosY ][botPosX] = '-';
			board[botPosY ][botPosX-1]  = 'B';
		}
		else if (board[botPosY ][botPosX-1]  == 'E')
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY ][botPosX-1]  = 'B';
		}
		else if (board[botPosY ][botPosX-1]  == 'X')
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY ][botPosX-1]  = 'B';
			bombCount += 1;
		}
		else
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY ][botPosX-1]  = 'B';
		}
	}
	if (dir == "right")
	{
		if (board[botPosY ][botPosX+1] == '#' || board[botPosY ][botPosX+1] == 'W')
		{
			board[botPosY ][botPosX] = 'B';
		}
		else if (board[botPosY ][botPosX+1] == 'w')
		{
			board[botPosY ][botPosX] = 'B';
		}
		else if (board[botPosY ][botPosX+1] == 'G')
		{
			if (check_player_invent(botPosY, botPosX + 1))
			{
				board[botPosY ][botPosX] = '-';
				board[botPosY ][botPosX+1] = 'B';
			}
			else
			{
				board[botPosY ][botPosX] = 'B';
			}
		}
		else if (board[botPosY ][botPosX+1] == 'K')
		{
			add_key_to_invent(botPosY, botPosX + 1);
			board[botPosY ][botPosX] = '-';
			board[botPosY ][botPosX+1] = 'B';
		}
		else if (board[botPosY ][botPosX+1] == 'E')
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY ][botPosX+1] = 'B';
		}
		else if (board[botPosY ][botPosX+1] == 'X')
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY ][botPosX+1] = 'B';
			bombCount += 1;
		}
		else
		{
			board[botPosY ][botPosX] = '-';
			board[botPosY ][botPosX+1] = 'B';
		}
	}
}
void BotGame::update(const sf::Time & delta)
{	
	auto inputManager = state_manager_.get_input_manager();
	get_bot_pos(board);
	if (botPosY == currLevel.Exit.YPos)
	{
		if (botPosX == currLevel.Exit.XPos)
		{
			std::cout << "\n\n\n\t GOOD JOB YOU REACHED THE END";
		//	waiting = false;
		//	playing = false;
			currentLevelNumber += 1;
			BotInvent.clear();
		}
	}
}
void BotGame::draw_board(char board[boardYLength][boardXLength], sf::RenderWindow& window)
{
	for (size_t i = 0; i < boardYLength; i++)
	{
		for (size_t j = 0; j < boardXLength; j++)
		{
			switch (board[i][j])
			{
			case '#':
				if (!boardTex[i][j].loadFromFile("BG/wall.png"))
				{
					std::cout << "Could not load image\n";
				}
				break;
			case 'W':
				if (!boardTex[i][j].loadFromFile("BG/wall.png"))
				{
					std::cout << "Could not load image\n";
				}
				break;
			case 'w':
				if (!boardTex[i][j].loadFromFile("BG/wallCracked.png"))
				{
					std::cout << "Could not load image\n";
				}
				break;
			case 'B':
				if (!boardTex[i][j].loadFromFile("BG/bot.png"))
				{
					std::cout << "Could not load image\n";
				}
				break;
			case 'K':
				if (!boardTex[i][j].loadFromFile("BG/key.png"))
				{
					std::cout << "Could not load image\n";
				}
				break;
			case 'G':
				if (!boardTex[i][j].loadFromFile("BG/Gate.png"))
				{
					std::cout << "Could not load image\n";
				}
				break;
			case 'E':
				if (!boardTex[i][j].loadFromFile("BG/Exit.png"))
				{
					std::cout << "Could not load image\n";
				}
				break;
			case '-':
				if (!boardTex[i][j].loadFromFile("BG/tile.png"))
				{
					std::cout << "Could not load image\n";
				}
				break;	
			case 'X':
					if (!boardTex[i][j].loadFromFile("BG/bomb.png"))
					{
						std::cout << "Could not load image\n";
					}
					break;
			}
			boardSpr[i][j].setTexture(boardTex[i][j]);
			boardSpr[i][j].setOrigin(boardSpr[i][j].getGlobalBounds().width / 2, boardSpr[i][j].getGlobalBounds().height / 2);
			window.draw(boardSpr[i][j]);

		}
	}
}
void BotGame::render()
{
	sf::RenderWindow& window = state_manager_.get_render_window();
	window.setView(view_main); // applying the view


	window.draw(logoSpr);
	window.draw(messageText);
	window.draw(BGbg_sprite);

	window.draw(gameText);
	
	draw_board(board, window);
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


void BotGame::handle_input(const sf::Time & delta)
{

	auto inputManager = state_manager_.get_input_manager();
	sf::RenderWindow& window = state_manager_.get_render_window();
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
	if (inputManager.is_key_released(InputKey::left))
	{
		move_player("left", board);
		lastDir = "left";
	}
	if (inputManager.is_key_released(InputKey::right))
	{
		move_player("right", board);
		lastDir = "right";
	}
	if (inputManager.is_key_released(InputKey::up))
	{
		move_player("up", board);
		lastDir = "up";
	}
	if (inputManager.is_key_released(InputKey::down))
	{
		move_player("down", board);
		lastDir = "down";
	}
	if (inputManager.is_key_released(InputKey::b))
	{
		placeBomb(board);
	}
	if (inputManager.is_key_released(InputKey::d))
	{
		detonateBomb(board);
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

void BotGame::handle_state_changes()
{
	auto& state_current = state_manager_;
	if (back == true)
		state_current.change_state(state_manager_.state_ptr<GameBox>());
	if (quit == true)
		state_manager_.quit();
}



void BotGame::initGame()
{
}

void BotGame::Reset()
{
}
