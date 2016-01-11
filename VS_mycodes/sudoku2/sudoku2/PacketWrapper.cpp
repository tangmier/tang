#include "PacketWrapper.h"
#include "Config.h"
#include <winsock2.h>
#include <iostream>
PacketWrapper::PacketWrapper()
{

}

void PacketWrapper::send_packet(string packet, int client_fd)
{
	std::cout << "now send packet: " << packet << endl;
	unsigned int packet_len = packet.size();
	char *buf = new char[packet_len];
	memcpy(buf, packet.c_str(), packet_len);
	send(client_fd, buf, packet_len+1, 0);
	delete buf;
}
