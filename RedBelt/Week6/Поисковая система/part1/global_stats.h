#pragma once
#include "total_duration.h"

struct SStats{
    TotalDuration split;
    TotalDuration lookup;
    TotalDuration sort;
    TotalDuration format;
}; 