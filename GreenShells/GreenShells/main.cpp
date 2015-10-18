//#include <iostream>
//
//#include "GameSession.h"
//#include "GameWindow.h"
//#include "RPCBase.h"
//#include "SynchronizedQueue.h"
//#include "TCPConnection.h"
//#include "MapRemote.h"
//#include "ServerSession.h"
//
//// These needs to be before main
//bool SetUpServer(int port)
//{
//	if (port != 0)
//	{
//		ServerSession::GetInstance().StartServer(port);
//
//
//		GameSession::GetInstance().SetPort(port);
//		GameSession::GetInstance().SetServerIP("127.0.0.1");
//		if (GameSession::GetInstance().ConnectToServer())
//		{
//			std::cout << "Connected to server." << std::endl;
//			return true;
//		}
//		else
//		{
//			std::cout << "Could not connect to server." << std::endl;
//		}
//	}
//
//	return false;
//}
//
//bool SetUpClient(char* ip,int port)
//{
//	GameSession::GetInstance().SetServerIP(ip);
//	if (port != 0)
//	{
//		GameSession::GetInstance().SetPort(port);
//		if (GameSession::GetInstance().ConnectToServer())
//		{
//			GameSession::GetInstance().GetWorldState()->PrepareRemoteGame();
//			//GameSession::GetInstance().GetWorldState()->GetMap()->MoveUnit(1, Position(2, 3), Position(3, 3));
//			return true;
//		}
//		else
//		{
//			std::cout << "Could not connect to server." << std::endl;
//		}
//	}
//
//	return false;
//}
//
//int main(int argc, char* argv[])
//{
//	const int CLIENT_SERVER_ARG = 1;
//	const int PORT_ARG = 2;
//	const int SERVER_IP_ARG = 3;
//
//	if (argc == 1)
//	{
//		// We need to ask user to enter manually the data
//	}
//	else
//	{
//		// User is supposed to have written the values in the command line
//		std::cout << "Starting game with arguments : " << std::endl;
//		for (int i = 1; i < argc; ++i)
//		{
//			std::cout << argv[i] << std::endl;
//		}
//
//		//------- Client or Server -------  
//		char* gameType = argv[CLIENT_SERVER_ARG];
//
//		if (strcmp(gameType, "server") == 0)
//		{
//			if (argc == 3)
//			{
//				if (SetUpServer(atoi(argv[PORT_ARG])))
//				{
//
//				}
//				else
//				{
//					std::cout << "Could not set up a server." << std::endl;
//					return 0;
//				}
//			}
//			else
//			{
//				std::cout << "Server usage : GreenShells.exe server port" << std::endl;
//				return 0;
//			}
//		}
//		else if (strcmp(gameType, "client") == 0)
//		{
//			if (argc == 4)
//			{
//				if (SetUpClient(argv[SERVER_IP_ARG], atoi(argv[PORT_ARG])))
//				{
//
//				}
//				else
//				{
//					std::cout << "Could not set up a client" << std::endl;
//					return 0;
//				}
//
//			}
//			else
//			{
//				std::cout << "Client usage : GreenShells.exe client port ip" << std::endl;
//				return 0;
//			}
//		}
//
//		GameWindow::GetInstance().ShowWindow();
//		GameWindow::GetInstance().Close();
//		return 0;
//	}
//	return 0;
//}



#include <fstream>

// include headers that implement a archive in simple text format
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "WorldState.h"

int main() {
	// create and open a character archive for output

	// create class instance
	WorldState worldState;
	worldState.PrepareLocalGame();

	// save data to archive
	{
		std::ofstream ofs("serializationData");
		boost::archive::binary_oarchive oa(ofs);
		// write class instance to archive
		oa << worldState;
		// archive and stream closed when destructors are called
	}

	// ... some time later restore the class instance to its orginal state
	WorldState newWorldState;
	{
		// create and open an archive for input
		std::ifstream ifs("serializationData");
		boost::archive::binary_iarchive ia(ifs);
		// read class state from archive
		ia >> newWorldState;
		// archive and stream closed when destructors are called
	}
	return 0;
}