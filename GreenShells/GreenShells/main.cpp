#include <iostream>

#include "GameSession.h"
#include "GameWindow.h"



// These needs to be before main
bool SetUpServer(int port)
{
	GameSession::GetGameSession().SetIsServer(true);
	if (port != 0)
	{
		GameSession::GetGameSession().SetPort(port);
	}
	else
	{
		std::cout << "Server requires a port number" << std::endl;
		return false;
	}

	GameSession::GetGameSession().PrepareGame();
	return true;
}

bool SetUpClient(char* ip,int port)
{
	GameSession::GetGameSession().SetIsServer(false);
	GameSession::GetGameSession().SetServerIP(ip);
	if (port != 0)
	{
		GameSession::GetGameSession().SetPort(port);
	}
	else
	{
		std::cout << "Client requires a port number" << std::endl;
		return false;
	}
	return true;
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
				if (!SetUpServer(atoi(argv[PORT_ARG])))
				{
					return 0;
				}
			}
			else
			{
				std::cout << "server requires a port number" << std::endl;
				return 0;
			}
		}
		else if (strcmp(gameType, "client") == 0)
		{
			if (argc == 4)
			{
				if (!SetUpClient(argv[SERVER_IP_ARG], atoi(argv[PORT_ARG])))
				{
					return 0;
				}
				else
				{
					std::cout << "client requires a server ip AND port number" << std::endl;
					return 0;
				}

			}
			else
			{
				std::cout << "Need to know if we are a \"client\" or a \"server\" in command line" << std::endl;
				return 0;
			}
		}
		GameSession::GetGameSession().RunGame();

		GameWindow::GetInstance().Init();
		GameWindow::GetInstance().Show(800, 600);
		GameWindow::GetInstance().Close();

		GameSession::GetGameSession().QuitGame();
		return 0;
	}
}
