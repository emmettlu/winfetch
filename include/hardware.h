#pragma once

#include <string>

// 硬件信息缓存结构体
struct HardwareInfo {
    // 显示信息
    int horizontal;
    int vertical;
    int hz;
    
    // CPU/GPU信息
    std::wstring cpu;
    std::wstring gpu;
    
    // 内存信息
    int mem_percent;
    int mem_total;
    int mem_used;
    
    // 磁盘信息
    double disk_total_gb;
    double disk_free_gb;
};

// 获取硬件信息缓存（一次性查询所有信息，避免重复查询）
HardwareInfo getHardwareInfo();

// 单独的查询函数（向后兼容）
void getresolution(int& horizontal, int& vertical, int& hz);
std::wstring getcpu();
std::wstring getgpu();
int getmem(int typesel);
void getdisk();