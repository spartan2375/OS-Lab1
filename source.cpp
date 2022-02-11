#include <iostream>
#include <sys/utsname.h>
#include <fstream>
#include <ctime>

void PartA();
void PartB();
void GetBootTime();
void GetModeTime();
void GetMemory();
void GetProcTime();

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

void PartB()
{
    GetProcTime();
    GetBootTime();
    GetModeTime();
    GetMemory();
}

void GetMemory()
{
    std::string g, a, r, b, e;
    long memTotal, memFree, memAvail;
    std::ifstream file;
    file.open("/proc/meminfo");

    file >> g >> memTotal >> a >> r >> memFree >> b >> e >> memAvail;

    if (g != "MemTotal:" || e != "MemAvailable:") // switch this back to the right var
    {
        std::cout << g << "[ERROR]: Could not parse memory info!\n";
        return;
    }

    std::cout << g << " " << memTotal << std::endl
              << e << " " << memAvail << std::endl;

    file.close();
}

void GetModeTime()
{
    std::string asdf;
    int userModeTime, garbage, systemModeTime;
    std::ifstream file;
    file.open("/proc/stat");
    file >> asdf >> userModeTime >> garbage >> systemModeTime;
    if (asdf != "cpu")
    {
        std::cout << "[ERROR]: Could not parse user and system mode times!\n";
        return;
    }
    std::cout << "Time spent in user mode: " << userModeTime
              << "\nTime spent in system mode: " << systemModeTime << std::endl;

    file.close();
}

void GetBootTime()
{
    double upTime, garbage;
    std::ifstream file;
    file.open("/proc/uptime");
    file >> upTime >> garbage;
    int days = int(upTime) / 86400;
    int hours = int(upTime) / 3600 % 24;
    int minutes = int(upTime) / 60 % 60;
    int seconds = int(upTime) % 60;

    std::cout << "Time since last reboot: " << days << ":"
              << hours << ":" << minutes << ":" << seconds << std::endl;

    file.close();
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