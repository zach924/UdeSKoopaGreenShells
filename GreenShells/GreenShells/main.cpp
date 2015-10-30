#include <iostream>

#include "GameSession.h"
#include "GameWindow.h"
#include "RPCBase.h"
#include "SynchronizedQueue.h"
#include "TCPConnection.h"
#include "MapRemote.h"
#include "ServerSession.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

// These needs to be before main
bool SetUpServer(char* playerName, int port)
{
	if (port != 0)
	{
		ServerSession::GetInstance().StartServer(port);

		GameSession::GetInstance().SetPort(port);
		GameSession::GetInstance().SetServerIP("127.0.0.1");
		if (GameSession::GetInstance().ConnectToServer(playerName))
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

bool SetUpClient(char* playerName, char* ip, int port)
{
	GameSession::GetInstance().SetServerIP(ip);
	if (port != 0)
	{
		GameSession::GetInstance().SetPort(port);
		if (GameSession::GetInstance().ConnectToServer(playerName))
		{
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
	const int PLAYER_NAME_ARG = 1;
	const int CLIENT_SERVER_ARG = 2;
	const int PORT_ARG = 3;
	const int SERVER_IP_ARG = 4;

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

		//------- Player name -------  
		char* playerName = argv[PLAYER_NAME_ARG];

		//------- Client or Server -------  
		char* gameType = argv[CLIENT_SERVER_ARG];

		if (strcmp(gameType, "server") == 0)
		{
			if (argc == 4)
			{
				if (SetUpServer(playerName, atoi(argv[PORT_ARG])))
				{
					GameWindow::GetInstance().ShowWindow();
					GameWindow::GetInstance().Close();
					ServerSession::GetInstance().StopServer();
				}
				else
				{
					std::cout << "Could not set up a server." << std::endl;

					return 0;
				}
			}
			else
			{
				std::cout << "Server usage : GreenShells.exe playerName server port" << std::endl;

				return 0;
			}
		}
		else if (strcmp(gameType, "client") == 0)
		{
			if (argc == 5)
			{
				if (SetUpClient(playerName, argv[SERVER_IP_ARG], atoi(argv[PORT_ARG])))
				{
					GameWindow::GetInstance().ShowWindow();
					GameWindow::GetInstance().Close();
				}
				else
				{
					std::cout << "Could not set up a client" << std::endl;

					return 0;
				}

			}
			else
			{
				std::cout << "Client usage : GreenShells.exe playerName client port ip" << std::endl;

				return 0;
			}
		}
		_CrtDumpMemoryLeaks();

		return 0;
	}

	system("PAUSE");
	return 0;
}
