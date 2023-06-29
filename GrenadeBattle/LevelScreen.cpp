// Local includes
#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"
#include "Platform.h"


// Library includes
#include <iostream>
#include <fstream>

LevelScreen::LevelScreen(Game* newGamePointer)
	:Screen(newGamePointer)
	,camera()
	,player()
	,player2()
	,platforms()
	,currentLevel(0)
	
{
	switchScreen = false;

	tag = "Level";

	

	player.SetController(0);
	player2.SetController(1);

	LoadLevel("Assets/Level1.txt");
	player.SetTag("Player");
	player2.SetTag("Player2");

	player.SetEnemy(&player2);
	player2.SetEnemy(&player);


	player.SetStartingPos(sf::Vector2f(242, 1089));
	player2.SetStartingPos(sf::Vector2f(1210, 1089));
 

	

	font = AssetManager::RequestFont("Assets/dogica.ttf");

	player1Lives.setFont(font);
	player2Lives.setFont(font);

	
	player1Lives.setFillColor(sf::Color::White); 
	player1Lives.setPosition(10, 10); 

	
	player2Lives.setCharacterSize(24);
	player2Lives.setFillColor(sf::Color::White);
	player2Lives.setPosition(1500, 10); 
	
}

void LevelScreen::Update(sf::Time frameTime)
{
	
	if (player.GetLives() <= 0 || player2.GetLives() <= 0)
	{
		switchScreen = true;
	}

	
	
	player1Lives.setString( "Player 1 Lives: " + std::to_string(player.GetLives()));
	player2Lives.setString("Player 2 Lives: " + std::to_string(player2.GetLives()));

	player.Update(frameTime);
	player2.Update(frameTime);
	
	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Update(frameTime);
	}

	for (int i = 0; i < player.GetGrenadeVector().size(); i++)
	{		
		player.GetGrenadeVector()[i]->Update(frameTime);
	}

	for (int i = 0; i < player2.GetGrenadeVector().size(); i++)
	{
		player2.GetGrenadeVector()[i]->Update(frameTime);
	}

	// Check collision between player and objects

	for (int i = 0; i < platforms.size(); ++i)
	{
		if (player.CheckCollision(*platforms[i]))
		{
			player.HandleCollision(*platforms[i]);
			platforms[i]->HandleCollision(player);
		}

		if (player2.CheckCollision(*platforms[i]))
		{
			player2.HandleCollision(*platforms[i]);
			platforms[i]->HandleCollision(player2);
		}

		for (int c = 0; c < player.GetGrenadeVector().size(); c++)
		{
			if (player.GetGrenadeVector()[c]->CheckCollision(*platforms[i]))
			{
				//std::cout << "Collision Detected" << std::endl;
				player.GetGrenadeVector()[c]->HandleCollision(*platforms[i]);
				//platforms[i]->HandleCollision(player.GetGrenadeVector()[c]);
			}
		}



		for (int c = 0; c < player.GetGrenadeVector().size(); c++)
		{
			if (player2.CheckCollision(*player.GetGrenadeVector()[c]))
			{
				player2.HandleCollision(*player.GetGrenadeVector()[c]);
			}
		}


		for (int c = 0; c < player2.GetGrenadeVector().size(); c++)
		{
			if (player.CheckCollision(*player2.GetGrenadeVector()[c]))
			{
				player.HandleCollision(*player2.GetGrenadeVector()[c]);
			}
		}


		for (int c = 0; c < player2.GetGrenadeVector().size(); c++)
		{
			if (player2.GetGrenadeVector()[c]->CheckCollision(*platforms[i]))
			{
				//std::cout << "Collision Detected" << std::endl;
				player2.GetGrenadeVector()[c]->HandleCollision(*platforms[i]);
				//platforms[i]->HandleCollision(player.GetGrenadeVector()[c]);
			}
		}

	}

}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	// Update camera based on render target and player position
	// Update the camera based on render target size and player position
	camera = target.getDefaultView();
	camera.setCenter(sf::Vector2f(752, 1028));

	// Update the render target to use the camera
	target.setView(camera);

	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}
	
	for (int i = 0; i < 5; i++)
	{
		player.GetPipVector()[i].Draw(target);
	}

	for (int i = 0; i < 5; i++)
	{
		player2.GetPipVector()[i].Draw(target);
	}

	for (int i = 0; i < player.GetGrenadeVector().size(); i++)
	{
		player.GetGrenadeVector()[i]->Draw(target);
	}

	for (int i = 0; i < player2.GetGrenadeVector().size(); i++)
	{
		player2.GetGrenadeVector()[i]->Draw(target);
	}

	player.Draw(target);
	player2.Draw(target);
	
	

	// For any UI, reset the camera before drawing!
	target.setView(target.getDefaultView());


	target.draw(player1Lives);
	target.draw(player2Lives);
}

void LevelScreen::LoadNextLevel()
{
}

void LevelScreen::LoadLevel()
{
	platforms.push_back(new Platform(sf::Vector2f(0,100)));
	platforms.push_back(new Platform(sf::Vector2f(100, 100)));
	platforms.push_back(new Platform(sf::Vector2f(0, 100)));
	platforms.push_back(new Platform(sf::Vector2f(-100,100)));
	platforms.push_back(new Platform(sf::Vector2f(200, 100)));
	platforms.push_back(new Platform(sf::Vector2f(-200, 100)));
	platforms.push_back(new Platform(sf::Vector2f(300, 100)));
	platforms.push_back(new Platform(sf::Vector2f(-300, 100)));
	platforms.push_back(new Platform(sf::Vector2f(200, -200)));
	platforms.push_back(new Platform(sf::Vector2f(200, -300)));

	
}

bool LevelScreen::LoadLevel(std::string fileName)
{
	// Open the level file
	std::ifstream inFile;
	inFile.open(fileName);


	// Make sure the file was opened
	if (!inFile)
	{
		return false;
		// Assume we finished all levels, we'll win now!
	}

	// Remove any existing platforms
	for (int i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}
	platforms.clear();

	// Set the starting x and y coordinates used to position level objects
	float x = 0.0f;
	float y = 0.0f;

	// Define the spacing we will use for our grid
	const float X_SPACE = 121.0f;
	const float Y_SPACE = 121.0f;

	// Read each character one by one from the file...
	char ch;
	// Each time, try to read the next character
	// If successful, execute body of loop
	// the "noskipws" means our input from the file will include 
	// the white space (spaces and new lines)
	while (inFile >> std::noskipws >> ch)
	{
		// Perform actions based on what character was read in

		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
		else if (ch == 'P')
		{
			player.SetPosition(x, y);
		}	
		else if (ch == 'K')
		{
			player2.SetPosition(x, y);
		}
		else if (ch == 'N') // Normal platform
		{
			platforms.push_back(new Platform(sf::Vector2f(x, y)));
		}
		else if (ch == '-')
		{
			// Do nothing - empty space
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}
	}

	// Close the file now that we are done with it
	inFile.close();

	return true;
}

