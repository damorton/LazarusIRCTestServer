cmake_minimum_required(VERSION 2.8)
project(lazarusServer)

set(SOURCES 
	net/NetManager.cc
	socket/socket.c
	server/server.cc
	main.cc
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(lazarusServer ${SOURCES})

if(WIN32)
  target_link_libraries(lazarusServer wsock32 ws2_32)
endif()

set_target_properties(lazarusServer
    PROPERTIES    
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)