#include <iostream>

#include "GameSession.h"
#include "GameWindow.h"
#include "RPCBase.h"
#include "SynchronizedQueue.h"
#include "TCPConnection.h"

// These needs to be before main
bool SetUpServer(int port)
{
	GameSession::GetGameSession().SetIsServer(true);
	if (port != 0)
	{
		GameSession::GetGameSession().SetPort(port);
		GameSession::GetGameSession().PrepareGame();
		return true;
	}

	return false;
}

bool SetUpClient(char* ip,int port)
{
	GameSession::GetGameSession().SetIsServer(false);
	GameSession::GetGameSession().SetServerIP(ip);
	if (port != 0)
	{
		GameSession::GetGameSession().SetPort(port);
		if (GameSession::GetGameSession().ConnectToServer())
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
		else
		{
			std::cout << "Could not determine if user wanted a client or server" << std::endl;
			system("PAUSE");
			return 0;
		}

		GameWindow::GetInstance().Init();
		GameWindow::GetInstance().Show(800, 600);
		GameWindow::GetInstance().Close();

		system("PAUSE");
		return 0;
	}

	std::cout << "Usages : " << std::endl;
	std::cout << "Greenshells.exe client port ip" << std::endl;
	std::cout << "Greenshells.exe server port" << std::endl;
	system("PAUSE");
	return 0;
}
