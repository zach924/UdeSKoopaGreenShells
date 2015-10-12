#include <iostream>

#include "GameSession.h"
#include "GameWindow.h"
#include "RPCBase.h"
#include "SynchronizedQueue.h"
#include "TCPConnection.h"
#include "MapRemote.h"
#include "ServerSession.h"


#include "Player.h"
#include "UnitMelee.h"
#include "unitRange.h"
#include "DistrictDefensive.h"

// These needs to be before main
bool SetUpServer(int port)
{
	if (port != 0)
	{
		ServerSession::GetInstance().StartServer(port);


		GameSession::GetInstance().SetPort(port);
		GameSession::GetInstance().SetServerIP("127.0.0.1");
		if (GameSession::GetInstance().ConnectToServer())
		{
			std::cout << "Connected to server." << std::endl;
			return true;
		}
		else
		{
			std::cout << "Could not connect to server." << std::endl;
		}
	}

	return false;
}

bool SetUpClient(char* ip,int port)
{
	GameSession::GetInstance().SetServerIP(ip);
	if (port != 0)
	{
		GameSession::GetInstance().SetPort(port);
		if (GameSession::GetInstance().ConnectToServer())
		{
			GameSession::GetInstance().GetWorldState()->SetMap(new MapRemote());
			GameSession::GetInstance().GetWorldState()->GetMap()->MoveUnit(1, Position(2, 3), Position(3, 3));
			return true;
		}
		else
		{
			std::cout << "Could not connect to server." << std::endl;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	const int CLIENT_SERVER_ARG = 1;
	const int PORT_ARG = 2;
	const int SERVER_IP_ARG = 3;

	if (argc == 1)
	{
		// We need to ask user to enter manually the data
	}
	else
	{
		// User is supposed to have written the values in the command line
		std::cout << "Starting game with arguments : " << std::endl;
		for (int i = 1; i < argc; ++i)
		{
			std::cout << argv[i] << std::endl;
		}

		//------- Client or Server -------  
		char* gameType = argv[CLIENT_SERVER_ARG];

		if (strcmp(gameType, "server") == 0)
		{
			if (argc == 3)
			{
				if (SetUpServer(atoi(argv[PORT_ARG])))
				{

				}
				else
				{
					std::cout << "Could not set up a server." << std::endl;
					system("PAUSE");
					return 0;
				}
			}
			else
			{
				std::cout << "Server usage : GreenShells.exe server port" << std::endl;
				system("PAUSE");
				return 0;
			}
		}
		else if (strcmp(gameType, "client") == 0)
		{
			if (argc == 4)
			{
				if (SetUpClient(argv[SERVER_IP_ARG], atoi(argv[PORT_ARG])))
				{

				}
				else
				{
					std::cout << "Could not set up a client" << std::endl;
					system("PAUSE");
					return 0;
				}

			}
			else
			{
				std::cout << "Client usage : GreenShells.exe client port ip" << std::endl;
				system("PAUSE");
				return 0;
			}
		}


		// ===================================================
		// TEST DELETE BEFORE PUSH IN MASTER
		// ===================================================
		GameSession::GetInstance().GetWorldState()->PrepareGame();
		Player p2 = {};
		GameSession::GetInstance().GetWorldState()->AddPlayer(p2);

		auto p1 = GameSession::GetInstance().GetWorldState()->GetPlayer(0);

		auto map = GameSession::GetInstance().GetWorldState()->GetMap();
		auto p1Tile53 = map->GetTile(Position{ 5,3 });
		auto p1Tile54 = map->GetTile(Position{ 5,4 });
		auto p1Tile55 = map->GetTile(Position{ 5,5 });
		auto p2Tile63 = map->GetTile(Position{ 6,3 });
		auto p2Tile64 = map->GetTile(Position{ 6,4 });
		auto p2Tile65 = map->GetTile(Position{ 6,5 });

		UnitMelee* p1Melee = new UnitMelee(p1.GetPlayerID());
		UnitRange* p1Range = new UnitRange(p1.GetPlayerID(), 3);
		District* p1District = new District(p1.GetPlayerID());
		DistrictDefensive* p1DistrictDefensive = new DistrictDefensive(p1.GetPlayerID(), 20);

		UnitMelee* p2Melee = new UnitMelee(p2.GetPlayerID());
		UnitRange* p2Range = new UnitRange(p2.GetPlayerID(), 3);
		District* p2District = new District(p2.GetPlayerID());
		DistrictDefensive* p2DistrictDefensive = new DistrictDefensive(p2.GetPlayerID(), 20);

		p1Tile53->SetUnit(p1Range);
		p1Tile54->SetDistrict(p1District);
		p1Tile55->SetUnit(p1Melee);
		p1Tile55->SetDistrict(p1DistrictDefensive);

		p2Tile63->SetUnit(p2Range);
		p2Tile64->SetUnit(p2Melee);
		p2Tile64->SetDistrict(p2District);
		p2Tile65->SetDistrict(p2DistrictDefensive);

		map->Attack(p1.GetPlayerID(), Position(5, 5), Position(6, 4));

		// ===================================================

		GameWindow::GetInstance().ShowWindow();
		GameWindow::GetInstance().Close();
		

		system("PAUSE");
		return 0;
	}
	return 0;
}
