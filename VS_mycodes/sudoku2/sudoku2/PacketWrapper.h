#include <vector>
#include <string>
using namespace std;
class PacketWrapper
{
	public:
		PacketWrapper();
		static void send_packet(string packet, int client_fd);
};