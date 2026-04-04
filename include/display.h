#pragma once

#include <hardware.h>

// 显示和视觉函数
void drawbar(double input);
void membar();
void diskbar();
void color1();
void color2();

// 使用缓存硬件信息的优化版本（推荐使用，避免重复查询）
void membar(const HardwareInfo& hw_info);
void diskbar(const HardwareInfo& hw_info);