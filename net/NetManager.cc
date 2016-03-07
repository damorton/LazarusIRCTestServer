#include "net/NetManager.h"

#include <cstring> // strlen()
#include <iostream>
#include <time.h>

namespace net{

	NetManager::NetManager()
	{
		
	}

	NetManager::~NetManager()
	{
		Close(m_iSocketFileDescriptor);
	}

	void NetManager::Init(int fileDescriptor)
	{
		m_iSocketFileDescriptor = fileDescriptor;		
	}

	int NetManager::SendData(char* buffer)
	{
		size_t size = strlen(buffer) + 1;
		int flags = 0;
		int bytesSents = 0;

		bytesSents = Send(m_iSocketFileDescriptor, buffer, size, flags);
		ClearBuffer(buffer);
		return bytesSents;
	}

	int NetManager::ReadData(char* buffer, int size)
	{
		int flags = 0;
		int bytesRecv = 0;
	
		ClearBuffer(buffer);

		bytesRecv = Recv(m_iSocketFileDescriptor, buffer, size, flags);
		if (strcmp(buffer, "0") != 0)
		{
			std::cout << "Server buffer: " << buffer << std::endl;
		}		

		// Client shutdown connection
		if (bytesRecv == 0 && m_eState == CONNECTED)
		{			
			std::cout << "client disconnected: " << buffer << std::endl;
			m_eState = CONNECTION_FAILED;
			Close(m_iSocketFileDescriptor);
		}

		return bytesRecv;
	}

	void NetManager::ClearBuffer(char *buffer)
	{
		sprintf(buffer, "%s", "0");
	}

	char *NetManager::TimeNow()
	{
		time_t rawtime;
		struct tm * timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		return asctime(timeinfo);
	}

} // namespace net