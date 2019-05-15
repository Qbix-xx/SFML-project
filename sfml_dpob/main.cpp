#include "GameClasses.h"
#include <iostream>
#include <string>
#include <vector>

#define SCR_WIDTH 1366
#define SCR_HEIGHT 768
enum GameStates { MENU, CHAR_SELECT, PLAYING, PAUSE };

using namespace std;

void refresh_stats_display(sf::Text *stat_array, PlayerClass *character)
{
	for (int i = 0; i < 7; i++) //iterating over "stats" enum. (sort of.)
	{
		string temp = to_string(character->getStats(i));
		stat_array[i].setString(sf::String(temp));
	}
}
void refresh_enemy_count(sf::Text *counters)
{
	counters[0].setString(std::to_string(Orc::getCount()));
	counters[1].setString(std::to_string(Goblin::getCount()));
	counters[2].setString(std::to_string(Lizard::getCount()));
}

int main()
{
	/*----------declarations----------*/
	sf::RenderWindow window({ SCR_WIDTH, SCR_HEIGHT }, "DPOB project");
	sf::Vector2f mousePos;
	GameStates game_state = MENU;

	sf::Font	font; //arial bold italic
	sf::Text	text_stats[7];
	sf::Text	text_stats_values[7];
	sf::Text	text_enemy_count[3];
	sf::Vertex	outline[] = //white outline around character stat display
	{
		//each pair of vertices make a line
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 350, SCR_HEIGHT / 2 + 50)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 350, SCR_HEIGHT / 2 + 320)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 350, SCR_HEIGHT / 2 + 50)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 600, SCR_HEIGHT / 2 + 50)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 350, SCR_HEIGHT / 2 + 320)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 600, SCR_HEIGHT / 2 + 320)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 600, SCR_HEIGHT / 2 + 50)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 600, SCR_HEIGHT / 2 + 320)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 400, SCR_HEIGHT / 2 + 50)),
		sf::Vertex(sf::Vector2f(SCR_WIDTH / 2 - 400, SCR_HEIGHT / 2 + 320))
	};

	//menu elements
	sf::Texture	tex_menu_rune;
	sf::Sprite	spr_menu_rune;
	sf::Texture tex_menu_play;
	sf::Sprite	spr_menu_play;
	sf::Texture tex_menu_exit;
	sf::Sprite	spr_menu_exit;
	//character select elements
	sf::Texture tex_cselect_choose;
	sf::Sprite	spr_cselect_choose;
	sf::Texture tex_cselect_apprentice;
	sf::Sprite	spr_cselect_apprentice;
	sf::Texture tex_cselect_fighter;
	sf::Sprite	spr_cselect_fighter;
	sf::Texture tex_cselect_rogue;
	sf::Sprite	spr_cselect_rogue;
	//gameplay state UI elements
	sf::Texture	tex_play_heal;
	sf::Sprite	spr_play_heal;
	sf::Texture	tex_play_kill;
	sf::Sprite	spr_play_kill;
	sf::Texture	tex_play_hurt;
	sf::Sprite	spr_play_hurt;
	sf::Texture	tex_play_attack;
	sf::Sprite	spr_play_attack_orc;
	sf::Sprite	spr_play_attack_goblin;
	sf::Sprite	spr_play_attack_lizard;
	sf::Texture	tex_play_lvlup;
	sf::Sprite	spr_play_lvlup;
	sf::Texture	tex_play_spawn;
	sf::Sprite	spr_play_spawn_orc;
	sf::Sprite	spr_play_spawn_goblin;
	sf::Sprite	spr_play_spawn_lizard;
	sf::Texture	tex_enemy_orc;
	sf::Sprite	spr_enemy_orc;
	sf::Texture	tex_enemy_goblin;
	sf::Sprite	spr_enemy_goblin;
	sf::Texture	tex_enemy_lizard;
	sf::Sprite	spr_enemy_lizard;


	PlayerClass *player = NULL;
	vector<EnemyClass*> enemies_orcs;
	vector<EnemyClass*> enemies_goblins;
	vector<EnemyClass*> enemies_lizards;
	/*--------------------------------*/

	/*-----------setting up-----------*/
	window.setFramerateLimit(30);
	//loading font (Arial bold italic)
	if (!font.loadFromFile("Assets/arialbi.ttf"))
		cout << "error loading font :(";
	//setting up text for displaying stats:
	text_stats[0].setString("STR");
	text_stats[1].setString("INT");
	text_stats[2].setString("DEX");
	text_stats[3].setString("MAX HP");
	text_stats[4].setString("CUR HP");
	text_stats[5].setString("MAX MP");
	text_stats[6].setString("CUR MP");

	for (int i = 0; i < 7; ++i)
	{
		text_stats[i].setFont(font);
		text_stats[i].setCharacterSize(24);
		text_stats[i].setFillColor(sf::Color(50, 75, 200, 255));
		text_stats[i].setPosition(SCR_WIDTH / 2 - 600, SCR_HEIGHT / 2 + 50 + i*40);
	}
	for (int i = 0; i < 7; ++i)
	{
		text_stats_values[i].setFont(font);
		text_stats_values[i].setCharacterSize(24);
		text_stats_values[i].setFillColor(sf::Color(50, 75, 200, 255));
		text_stats_values[i].setPosition(SCR_WIDTH / 2 - 400, SCR_HEIGHT / 2 + 50 + i * 40);
	}
	//setting up enemy counters
	for (int i = 0; i < 3; ++i)
	{
		text_enemy_count[i].setFont(font);
		text_enemy_count[i].setCharacterSize(24);
		text_enemy_count[i].setFillColor(sf::Color(50, 75, 200, 255));
		text_enemy_count[i].setPosition(SCR_WIDTH / 2 + 400, SCR_HEIGHT / 2 - 160 + i * 200);
	}
	//loading PLAY button texture
	if (tex_menu_play.loadFromFile("Assets/UI/play.png"))
	{
		spr_menu_play.setTexture(tex_menu_play);
		spr_menu_play.setOrigin(190, 50);
		spr_menu_play.setPosition(SCR_WIDTH / 2, SCR_HEIGHT / 2 - 100);
	}
	//loading EXIT button texture
	if (tex_menu_exit.loadFromFile("Assets/UI/exit.png"))
	{
		spr_menu_exit.setTexture(tex_menu_exit);
		spr_menu_exit.setOrigin(190,50);
		spr_menu_exit.setPosition(SCR_WIDTH / 2, SCR_HEIGHT / 2 + 100);
	}
	//loading rune circle texture
	if (tex_menu_rune.loadFromFile("Assets/UI/rune_circle.jpg"))
	{
		spr_menu_rune.setTexture(tex_menu_rune);
		spr_menu_rune.setOrigin(450, 450);
		spr_menu_rune.setScale(sf::Vector2f(0.5, 0.5));
		spr_menu_rune.setColor(sf::Color(0, 150, 255, 150));
		spr_menu_rune.setPosition(SCR_WIDTH / 2, SCR_HEIGHT / 2);
	}
	//loading "Choose your class:" text texture
	if (tex_cselect_choose.loadFromFile("Assets/UI/choose.png"))
	{
		spr_cselect_choose.setTexture(tex_cselect_choose);
		spr_cselect_choose.setOrigin(350, 50);
		spr_cselect_choose.setPosition(SCR_WIDTH / 2, SCR_HEIGHT / 2-300);
	}
	//loading HEAL button texture
	if (tex_play_heal.loadFromFile("Assets/UI/heal.png"))
	{
		spr_play_heal.setTexture(tex_play_heal);
		spr_play_heal.setOrigin(150, 50);
		spr_play_heal.setPosition(SCR_WIDTH / 2 - 200, SCR_HEIGHT / 2 - 300);
	}
	//loading STAT+ button texture
	if (tex_play_kill.loadFromFile("Assets/UI/stat.png"))
	{
		spr_play_kill.setTexture(tex_play_kill);
		spr_play_kill.setOrigin(150, 50);
		spr_play_kill.setPosition(SCR_WIDTH / 2 - 200, SCR_HEIGHT / 2 - 200);
	}
	//loading HURT button texture
	if (tex_play_hurt.loadFromFile("Assets/UI/hurt.png"))
	{
		spr_play_hurt.setTexture(tex_play_hurt);
		spr_play_hurt.setOrigin(150, 50);
		spr_play_hurt.setPosition(SCR_WIDTH / 2 - 200, SCR_HEIGHT / 2 - 100);
	}
	//loading LVL UP button texture
	if (tex_play_lvlup.loadFromFile("Assets/UI/lvlup.png"))
	{
		spr_play_lvlup.setTexture(tex_play_lvlup);
		spr_play_lvlup.setOrigin(150, 50);
		spr_play_lvlup.setPosition(SCR_WIDTH / 2 - 200, SCR_HEIGHT / 2);
	}
	//loading ATTACK button textures ( all 3 )
	if (tex_play_attack.loadFromFile("Assets/UI/attack.png"))
	{
		spr_play_attack_orc.setTexture(tex_play_attack);
		spr_play_attack_goblin.setTexture(tex_play_attack);
		spr_play_attack_lizard.setTexture(tex_play_attack);
		spr_play_attack_orc.setOrigin(150, 50);
		spr_play_attack_orc.setScale(0.5f, 0.5f);
		spr_play_attack_orc.setPosition(SCR_WIDTH / 2 + 350, SCR_HEIGHT / 2 - 200);
		spr_play_attack_goblin.setOrigin(150, 50);
		spr_play_attack_goblin.setScale(0.5f, 0.5f);
		spr_play_attack_goblin.setPosition(SCR_WIDTH / 2 + 350, SCR_HEIGHT / 2);
		spr_play_attack_lizard.setOrigin(150, 50);
		spr_play_attack_lizard.setScale(0.5f, 0.5f);
		spr_play_attack_lizard.setPosition(SCR_WIDTH / 2 + 350, SCR_HEIGHT / 2 + 200);
	}
	//loading SPAWN button texture ( all 3 )
	if (tex_play_spawn.loadFromFile("Assets/UI/spawn.png"))
	{
		spr_play_spawn_orc.setTexture(tex_play_spawn);
		spr_play_spawn_orc.setOrigin(25, 25);
		spr_play_spawn_orc.setPosition(SCR_WIDTH / 2 + 350, SCR_HEIGHT / 2 - 150);
		spr_play_spawn_goblin.setTexture(tex_play_spawn);
		spr_play_spawn_goblin.setOrigin(25, 25);
		spr_play_spawn_goblin.setPosition(SCR_WIDTH / 2 + 350, SCR_HEIGHT / 2 + 50);
		spr_play_spawn_lizard.setTexture(tex_play_spawn);
		spr_play_spawn_lizard.setOrigin(25, 25);
		spr_play_spawn_lizard.setPosition(SCR_WIDTH / 2 + 350, SCR_HEIGHT / 2 + 250);
	}
	//loading character sprites for CHAR_SELECT state
	if (tex_cselect_apprentice.loadFromFile("Assets/magic/Apprentice/idle_1.png"))
	{
		spr_cselect_apprentice.setTexture(tex_cselect_apprentice);
		spr_cselect_apprentice.setOrigin(204, 212);
		spr_cselect_apprentice.setScale(0.5f, 0.5f);
		spr_cselect_apprentice.setPosition(SCR_WIDTH / 2 - 300, SCR_HEIGHT / 2);
	}
	if (tex_cselect_fighter.loadFromFile("Assets/melee/Fighter/1_IDLE_000.png"))
	{
		spr_cselect_fighter.setTexture(tex_cselect_fighter);
		spr_cselect_fighter.setOrigin(204, 212);
		spr_cselect_fighter.setScale(0.25f, 0.25f);
		spr_cselect_fighter.setPosition(SCR_WIDTH / 2, SCR_HEIGHT / 2 - 30);
	}
	if (tex_cselect_rogue.loadFromFile("Assets/ranged/Rogue/1_IDLE_000.png"))
	{
		spr_cselect_rogue.setTexture(tex_cselect_rogue);
		spr_cselect_rogue.setOrigin(204, 212);
		spr_cselect_rogue.setScale(0.25f, 0.25f);
		spr_cselect_rogue.setPosition(SCR_WIDTH / 2 + 300, SCR_HEIGHT / 2 - 30);
	}
	//loading enemy sprites for PLAYING state
	if (tex_enemy_orc.loadFromFile("Assets/enemy/Orc/orc_idle.png"))
	{
		spr_enemy_orc.setTexture(tex_enemy_orc);
		spr_enemy_orc.setOrigin(700, 575);
		spr_enemy_orc.setScale(0.1f, 0.1f);
		spr_enemy_orc.setPosition(SCR_WIDTH / 2 + 550, SCR_HEIGHT / 2 - 165);
	}
	if (tex_enemy_goblin.loadFromFile("Assets/enemy/Goblin/goblin_idle.png"))
	{
		spr_enemy_goblin.setTexture(tex_enemy_goblin);
		spr_enemy_goblin.setOrigin(10, 25);
		spr_enemy_goblin.setScale(3.0f, 3.0f);
		spr_enemy_goblin.setPosition(SCR_WIDTH / 2 + 550, SCR_HEIGHT / 2);
	}
	if (tex_enemy_lizard.loadFromFile("Assets/enemy/Lizard/lizard_idle.png"))
	{
		spr_enemy_lizard.setTexture(tex_enemy_lizard);
		spr_enemy_lizard.setOrigin(10, 20);
		spr_enemy_lizard.setScale(3.0f, 3.0f);
		spr_enemy_lizard.setPosition(SCR_WIDTH / 2 + 550, SCR_HEIGHT / 2 + 200);
	}
	/*--------------------------------*/
	
	/*------------main loop-----------*/
	while (window.isOpen())
	{
		//handling events (key pressed etc)
		sf::Event event;
		while (window.pollEvent(event))
		{
			//LMB (all the UI buttons being clicked on)
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				switch (game_state)
				{
				case MENU:
				{
					//PLAY button clicked
					if (spr_menu_play.getGlobalBounds().contains(mousePos))
						game_state = CHAR_SELECT;
					//EXIT button clicked
					else if (spr_menu_exit.getGlobalBounds().contains(mousePos))
						window.close();
				} break;
				case CHAR_SELECT:
				{
					//Apprentice class selected
					if (spr_cselect_apprentice.getGlobalBounds().contains(mousePos))
					{
						player = new Apprentice;
						game_state = PLAYING;
					}
					//Fighter class selected
					if (spr_cselect_fighter.getGlobalBounds().contains(mousePos))
					{
						player = new Fighter;
						text_stats[5].setString("RAGE MAX");
						text_stats[6].setString("RAGE CUR");
						game_state = PLAYING;
					}
					//Rogue class selected
					if (spr_cselect_rogue.getGlobalBounds().contains(mousePos))
					{
						player = new Rogue;
						text_stats[5].setString("ENERGY MAX");
						text_stats[6].setString("ENERGY CUR");
						game_state = PLAYING;
					}
				} break;
				case PLAYING:
				{
					//HEAL button clicked
					if (spr_play_heal.getGlobalBounds().contains(mousePos))
						player->HealUp(25);
					//KILL button clicked
					if (spr_play_kill.getGlobalBounds().contains(mousePos))
						++(*player);
					//HURT button clicked
					if (spr_play_hurt.getGlobalBounds().contains(mousePos))
						player->TakeDamage(10);
					//LVL UP button clicked
					if (spr_play_lvlup.getGlobalBounds().contains(mousePos))
						player->level_up(&player);
					//ATTACK button clicked (orc)
					if (spr_play_attack_orc.getGlobalBounds().contains(mousePos))
					{
						if (enemies_orcs.size() > 0)
						{
							if (player->Attack(*enemies_orcs[0]))
								enemies_orcs.erase(enemies_orcs.begin());
						}
						else
							std::cout << "There is no orc alive\n";
					}
					//ATTACK button clicked (goblin)
					if (spr_play_attack_goblin.getGlobalBounds().contains(mousePos))
					{
						if (enemies_goblins.size() > 0)
						{
							if (player->Attack(*enemies_goblins[0]))
								enemies_goblins.erase(enemies_goblins.begin());
						}
						else
							std::cout << "There is no goblin alive\n";
					}
					//ATTACK button clicked (lizard)
					if (spr_play_attack_lizard.getGlobalBounds().contains(mousePos))
					{
						if (enemies_lizards.size() > 0)
						{
							if (player->Attack(*enemies_lizards[0]))
								enemies_lizards.erase(enemies_lizards.begin());
						}
						else
							std::cout << "There is no lizard alive\n";
					}
					//SPAWN button clicked (orc)
					if (spr_play_spawn_orc.getGlobalBounds().contains(mousePos))
						enemies_orcs.push_back(new Orc);
					//SPAWN button clicked (goblin)
					if (spr_play_spawn_goblin.getGlobalBounds().contains(mousePos))
						enemies_goblins.push_back(new Goblin);
					//SPAWN button clicked (lizard)
					if (spr_play_spawn_lizard.getGlobalBounds().contains(mousePos))
						enemies_lizards.push_back(new Lizard);
				} break;
				case PAUSE:
				{

				} break;
				default:
					break;
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		//start drawing
		switch (game_state)
		{
		case MENU:
			spr_menu_rune.setRotation(spr_menu_rune.getRotation() - 0.5);
			window.draw(spr_menu_rune);
			window.draw(spr_menu_exit);
			window.draw(spr_menu_play);
			break;
		case CHAR_SELECT:
			window.draw(spr_cselect_choose);
			window.draw(spr_cselect_apprentice);
			window.draw(spr_cselect_fighter);
			window.draw(spr_cselect_rogue);
			break;
		case PLAYING:
			refresh_stats_display(text_stats_values, player);
			for (int i = 0; i < 7; ++i)
			{
				window.draw(text_stats[i]);
				window.draw(text_stats_values[i]);
			}
			refresh_enemy_count(text_enemy_count);
			for (int i = 0; i < 3; ++i)
			{
				window.draw(text_enemy_count[i]);
			}
			window.draw(outline, 10, sf::Lines);
			window.draw(spr_play_heal);
			window.draw(spr_play_kill);
			window.draw(spr_play_hurt);
			window.draw(spr_play_lvlup);
			window.draw(spr_play_attack_orc);
			window.draw(spr_play_attack_goblin);
			window.draw(spr_play_attack_lizard);
			window.draw(spr_play_spawn_orc);
			window.draw(spr_play_spawn_goblin);
			window.draw(spr_play_spawn_lizard);
			window.draw(spr_enemy_orc);
			window.draw(spr_enemy_goblin);
			window.draw(spr_enemy_lizard);
			window.draw(player->getSprite());
			break;
		case PAUSE:
			break;
		default:
			cout << "Game state error\n";
		}
		//stop drawing
		window.display();
	}
	/*--------------------------------*/
	delete player;
	return 0;
}