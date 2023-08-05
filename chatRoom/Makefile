all: server client

server: chatServer/chatServer.cpp chatServer/serverDemo.cpp netUnity/netUnity.cpp tool/tool.cpp
	g++ -o server chatServer/chatServer.cpp chatServer/serverDemo.cpp netUnity/netUnity.cpp tool/tool.cpp -lpthread

client: chatClint/chatClint.cpp chatClint/clintDemo.cpp netUnity/netUnity.cpp tool/tool.cpp
	g++ -o client chatClint/chatClint.cpp chatClint/clintDemo.cpp netUnity/netUnity.cpp tool/tool.cpp -lpthread