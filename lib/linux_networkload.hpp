#pragma once


#include <map>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <chrono>


class networkLoad {

public:
    static std::list<std::string> scanNetworkDevices(std::string ethernetDataFile);
    static std::vector<std::shared_ptr<networkLoad>> createLinuxEthernetScanList() {
        std::vector<std::shared_ptr<networkLoad>> v;
        for (auto elem: networkLoad::scanNetworkDevices("/proc/net/dev")) {
            v.push_back(std::make_shared<networkLoad>("/proc/net/dev",elem));
        }
        return v;
    }

    explicit networkLoad(std::string ethernetDataFileName = "/proc/net/dev", std::string ethName = "eth0");
    uint64_t getBytesPerSecond();
    uint64_t getBytesSinceStartup();
    uint64_t getRXBytesPerSecond();
    uint64_t getRXBytesSinceStartup();
    uint64_t getTXBytesPerSecond();
    uint64_t getTXBytesSinceStartup();
    std::string getBytesPerSeceondString(uint64_t bytesPerSecond);
    std::string getBitsPerSeceondString(uint64_t bytesPerSecond);
    bool isDeviceUp();
    std::string getDeviceName();

private:
    void initNetworkMonitor();
    uint64_t parseEthernetDevice();
    std::string ethernetDataFile;
    std::string ethDev;
    uint64_t m_totalTransceivedBytes = 0;
    uint64_t m_totalReceivedBytes = 0;
    uint64_t m_totalTransmittedBytes = 0;
    std::map<std::string, std::string> networkstatMap;
    bool isDeviceAvailable = false;
    std::chrono::time_point<std::chrono::steady_clock> timeBefore;
    std::chrono::time_point<std::chrono::steady_clock> timeBefore_rx;
    std::chrono::time_point<std::chrono::steady_clock> timeBefore_tx;
    uint64_t BytesPerSecond = 0;
    uint64_t BytesSinceStartup = 0;
    std::chrono::time_point<std::chrono::steady_clock> timeStamp;

};
