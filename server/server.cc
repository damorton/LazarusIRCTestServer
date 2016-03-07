#include "server/server.h"

#include <iostream>

namespace server{

	Server::Server()
	{
		std::unique_ptr<net::NetManager> netManager(new net::NetManager());
		m_NetManager = std::move(netManager);
		Init();
	}

	void Server::Init()
	{
		m_iListenSocketFileDescriptor = Connection(NULL, (char*)"27000", TYPE_SERVER, SOCK_STREAM);

		Listen(m_iListenSocketFileDescriptor, MAX_LISTEN_QUEUE_SIZE);
						
		m_iConnfd = accept(m_iListenSocketFileDescriptor, NULL, NULL);
		if (m_iConnfd == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(m_iListenSocketFileDescriptor);
			WSACleanup();			
		}

		SetNonBlocking(m_iConnfd);
		m_NetManager->Init(m_iConnfd);

		Start();
	}

	void Server::Start()
	{
		std::cout << "Lazaraus Server Started" << std::endl;
				
		char buffer[100];
		while (1)
		{		
			m_NetManager->ReadData(m_cRecvBuffer, MAX_BUFFER_SIZE); // pass
			std::cout << "Buffer: " << m_cRecvBuffer << std::endl;
			// Process buffer after read from network
			ProcessMsg();

			// Get user input
			std::cout << "Enter a game command" << std::endl;
			fgets(buffer, 100, stdin);
			sprintf(m_cSendBuffer, "%s", buffer);
			m_NetManager->SendData(m_cSendBuffer);
		}
	}

	void Server::ProcessMsg()
	{
		/*
		// Server commands commands
		if (strstr(m_cRecvBuffer, "!chant"))
		{
			// Create event
		}
		*/
	}
}