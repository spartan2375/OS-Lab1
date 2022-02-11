#include <iostream>
#include <sys/utsname.h>
#include <fstream>
#include <ctime>

void PartA();
void PartB();

int main()
{
    PartA();
    PartB();
    return 0;
}

void PartA()
{
    struct utsname sysInfo;
    int returnValue = uname(&sysInfo);
    std::cout << "System name: " << sysInfo.sysname << std::endl;
    std::cout << "Node name: " << sysInfo.nodename << std::endl;
    std::cout << "Release level of OS: " << sysInfo.release << std::endl;
    std::cout << "Version level of OS: " << sysInfo.version << std::endl;
    std::cout << "Machine name: " << sysInfo.machine << std::endl;
}

void GetBootTime()
{
    double upTime
}

void GetProcTime()
{
    std::string epochTime;
    std::ifstream file;
    file.open("/proc/stat");
    std::string line = "";

    while (1)
    {
        std::getline(file, line);
        if (file.eof())
            break;
        if (line.find("btime") != std::string::npos)
        {
            size_t spacePos = 0;
            spacePos = line.find(" ");
            epochTime = line.substr(spacePos, line.length());
            std::cout << "EPOCH TIME " << epochTime << std::endl;
            break;
        }
    }

    file.close();

    long time = std::stol(epochTime);
    time_t unixTime = time; // ctime(&unixTime)
    char timeThing[60];
    strftime(timeThing, 60, "%Y-%m-%d %H:%M:%S", localtime(&unixTime));
    std::cout << "Normal time: " << timeThing << std::endl;
}