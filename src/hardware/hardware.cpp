#include <windows.h>
#include <Registry.hpp>

#include <hardware.h>

// 全局硬件信息缓存，一次性初始化避免重复查询
static HardwareInfo g_cached_hardware_info;
static bool g_hardware_cache_initialized = false;

// 一次性获取所有硬件信息，避免多次系统调用
HardwareInfo getHardwareInfo() {
    if (g_hardware_cache_initialized) {
        return g_cached_hardware_info;
    }
    
    HardwareInfo info{};
    
    // 查询显示分辨率
    DISPLAY_DEVICE dd{};
    dd.cb = sizeof(dd);
    EnumDisplayDevices(NULL, 0, &dd, 0);
    
    DEVMODE dm{};
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm);
    
    info.horizontal = dm.dmPelsWidth;
    info.vertical = dm.dmPelsHeight;
    info.hz = dm.dmDisplayFrequency;
    
    // 查询CPU信息
    using namespace m4x1m1l14n;
    try {
        auto key = Registry::LocalMachine->Open(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
        info.cpu = key->GetString(L"ProcessorNameString");
    }
    catch (const std::exception&) {
        info.cpu = L"Unknown processor";
    }
    
    // 查询GPU信息
    try {
        auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinSAT");
        info.gpu = key->GetString(L"PrimaryAdapterString");
    }
    catch (const std::exception&) {
        info.gpu = L"Unknown (try running WinSAT to fix this)";
    }
    
    // 查询内存信息
    MEMORYSTATUSEX mem{};
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);
    
    info.mem_percent = mem.dwMemoryLoad;
    info.mem_total = mem.ullTotalPhys / 1048576;
    info.mem_used = info.mem_total - (mem.ullAvailPhys / 1048576);
    
    // 查询磁盘信息
    ULARGE_INTEGER TotalNumberOfBytes;
    ULARGE_INTEGER TotalNumberOfFreeBytes;
    
    BOOL check = GetDiskFreeSpaceExA("C:\\", nullptr, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
    
    if (check) {
        ULONGLONG totalspace = TotalNumberOfBytes.QuadPart / 1024 / 1024;
        ULONGLONG freespace = TotalNumberOfFreeBytes.QuadPart / 1024 / 1024;
        
        info.disk_total_gb = totalspace / 1000.0;
        info.disk_free_gb = freespace / 1000.0;
    } else {
        info.disk_total_gb = 0.0;
        info.disk_free_gb = 0.0;
    }
    
    g_cached_hardware_info = info;
    g_hardware_cache_initialized = true;
    
    return info;
}

void getresolution(int& horizontal, int& vertical, int& hz) {
    DISPLAY_DEVICE dd{};
    dd.cb = sizeof(dd);

    EnumDisplayDevices(NULL, 0, &dd, 0);
    DEVMODE dm{};
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;

    EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm);

    horizontal = dm.dmPelsWidth;
    vertical = dm.dmPelsHeight;
    hz = dm.dmDisplayFrequency;
}

std::wstring getcpu() {
    using namespace m4x1m1l14n;

    try {
        auto key = Registry::LocalMachine->Open(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
        auto cpuname = key->GetString(L"ProcessorNameString");
        return cpuname;
    }
    catch (const std::exception&) {
        return L"Unknown processor";
    }
}

std::wstring getgpu() {
    using namespace m4x1m1l14n;

    try {
        auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinSAT");
        auto gpuname = key->GetString(L"PrimaryAdapterString");
        return gpuname;
    }
    catch (const std::exception&) {
        return L"Unknown (try running WinSAT to fix this)";
    }
}

int getmem(int typesel) {
    MEMORYSTATUSEX mem{};
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);

    int percent = mem.dwMemoryLoad;
    int total = mem.ullTotalPhys / 1048576;
    int used = total - mem.ullAvailPhys / 1048576;

    if (typesel == 0) {
        return percent;
    }
    else if (typesel == 1) {
        return total;
    }
    else {
        return used;
    }
}

void getdisk() {
    ULARGE_INTEGER FreeBytesAvailableToCaller;
    ULARGE_INTEGER TotalNumberOfBytes;
    ULARGE_INTEGER TotalNumberOfFreeBytes;

    double total{};
    double free{};

    BOOL check = GetDiskFreeSpaceExA("C:\\", &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);

    if (check) {
        ULONGLONG totalspace = TotalNumberOfBytes.QuadPart / 1024 / 1024;
        if (totalspace <= INT_MAX) total = static_cast<double>(totalspace);

        ULONGLONG freespace = TotalNumberOfFreeBytes.QuadPart / 1024 / 1024;
        if (freespace <= INT_MAX) free = static_cast<double>(freespace);

        double totalgb = total / 1000;
        double freegb = free / 1000;

        printf("C:\\ %.2f GB (%.2f GB free)", totalgb, freegb);
    }
    else {
        printf("Disk info unknown");
    }
}