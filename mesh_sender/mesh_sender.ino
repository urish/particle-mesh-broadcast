#define MAX_PACKET_LEN (1232)

static const uint16_t wifiPort = 8888;
static const uint16_t PORT = 31313;
static constexpr const char* MULTICAST_ADDR = "ff03::1:1001";

UDP udpWifi;
UDP udpThread;

int fetchMulticastAddress(IPAddress& mcastAddr) {
    HAL_IPAddress addr = {};
    addr.v = 6;
    inet_inet_pton(AF_INET6, MULTICAST_ADDR, addr.ipv6);
    mcastAddr = addr;
    return 0;
}

void setup() {
    Serial.begin();

    udpWifi.begin(wifiPort);
    udpWifi.setBuffer(MAX_PACKET_LEN);
  
    uint8_t idx = 0;
    if_name_to_index("th1", &idx);
    udpThread.setBuffer(MAX_PACKET_LEN);
    udpThread.begin(PORT, idx);
    
    Serial.printlnf("Listening for UDP packets on port %d", wifiPort);
}

void loop() {
    if (udpWifi.parsePacket() > 0) {
        Serial.printlnf("Got UDP from %s:%d, sending to mesh...", udpWifi.remoteIP().toString().c_str(), udpWifi.remotePort());
        IPAddress mcastAddr;
        fetchMulticastAddress(mcastAddr);
	    udpThread.beginPacket(mcastAddr, PORT);
	    udpThread.write((const uint8_t*)udpWifi.buffer(), udpWifi.available());
	    udpThread.endPacket();
    }
}
