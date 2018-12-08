#define MAX_PACKET_LEN (1232)

static const uint16_t PORT = 31313;
static constexpr const char* MULTICAST_ADDR = "ff03::1:1001";

UDP udpThread;

int fetchMulticastAddress(IPAddress& mcastAddr) {
    HAL_IPAddress addr = {};
    addr.v = 6;
    inet_inet_pton(AF_INET6, MULTICAST_ADDR, addr.ipv6);
    mcastAddr = addr;
    return 0;
}

void setup()
{
    Serial.begin();

    uint8_t idx = 0;
    if_name_to_index("th1", &idx);
    udpThread.setBuffer(MAX_PACKET_LEN);
    udpThread.begin(PORT, idx);

    IPAddress mcastAddr;
    fetchMulticastAddress(mcastAddr);
    udpThread.joinMulticast(mcastAddr);
}

void loop() {
    if (udpThread.parsePacket()) {
        Serial.print("Got packet: ");
        Serial.write(udpThread.buffer(), udpThread.available());
        Serial.println("");
    }
}
