#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#define MAX_BUFFER_SIZE 255

#include <memory>

#include "net/NetManager.h"

namespace server{

	class Server{
	public:
		Server();		

	private:

		void Init();
		
		void Start();
		
		void ProcessMsg();

		std::unique_ptr<net::NetManager> m_NetManager;
		
		// Server listen file descriptor
		int m_iListenSocketFileDescriptor;

		// New connection file descriptor
		int m_iConnfd;

		// Client address structure
		struct Address m_sAddress;

		std::string m_strChat;
		
		char m_cSendBuffer[MAX_BUFFER_SIZE];
		char m_cRecvBuffer[MAX_BUFFER_SIZE];
	};

}

#endif