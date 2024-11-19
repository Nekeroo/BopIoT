#include <cstddef>
class NetworkManager {
    public :
        void initialize();
        void setup_wifi();
        void callback(char* topic, byte* payload, unsigned int length);
        void reconnect();
        void sendMessage();
}