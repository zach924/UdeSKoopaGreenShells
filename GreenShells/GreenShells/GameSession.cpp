#include "GameSession.h"
#include "WorldState.h"
#include "Player.h"


GameSession::GameSession()
	:m_worldState()
{
	Player* player = new Player();
}


GameSession::~GameSession()
{
	
}

void GameSession::PrepareGameSession()
{
	//GenerateTiles();
	AddPlayer();
}

void GameSession::Run()
{

}


void GameSession::AddPlayer(Player * player)
{

}
//void GameSession::AddPlayer(Player * player)
//{
//	if (!player)
//	{
//		player = new Player();
//	}
//	m_players.push_back(player);
//
//	// TODO: Notify all clients that a new player has arrived
//}

//void GameSession::AddPlayer(Player * player)
//{
//	if (!player)
//	{
//		player = new Player();
//	}
//	m_players.push_back(player);
//
//	// TODO: Notify all clients that a new player has arrived
//}
//
//void GameSession::GenerateTiles()
//{
//	std::ifstream ifs{ "Ressources\\maps\\FirstMap.txt" };
//	
//	std::string map((std::istreambuf_iterator<char>(ifs)),
//		             std::istreambuf_iterator<char>());
//
//	map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());
//	for (int i = 0; i < ROWS; ++i)
//	{
//		for (int j = 0; j < ROWS; ++j)
//		{
//			char tileType = map.at((i * ROWS) + j);
//			switch (tileType)
//			{
//			case '0':
//				m_tiles[i][j] = new TileGround();
//				break;
//
//			case '1':
//				m_tiles[i][j] = new TileMountain();
//				break;
//
//			case '2':
//			default:
//				m_tiles[i][j] = new TileWater();
//				break;
//			}
//		}
//	}
//}
