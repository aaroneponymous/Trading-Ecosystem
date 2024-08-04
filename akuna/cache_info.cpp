#include <iostream>
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <cpuid.h>
#endif

void get_cache_info() {
    unsigned int eax, ebx, ecx, edx;
    
    // Get the number of basic CPUID functions
#ifdef _MSC_VER
    int cpuInfo[4];
    __cpuid(cpuInfo, 0);
    int max_basic_cpuid = cpuInfo[0];
#else
    __cpuid(0, eax, ebx, ecx, edx);
    int max_basic_cpuid = eax;
#endif

    // Check if the CPU supports cache information
    if (max_basic_cpuid >= 4) {
        for (int i = 0; ; i++) {
#ifdef _MSC_VER
            __cpuidex(cpuInfo, 4, i);
            eax = cpuInfo[0];
            ebx = cpuInfo[1];
            ecx = cpuInfo[2];
            edx = cpuInfo[3];
#else
            __cpuid_count(4, i, eax, ebx, ecx, edx);
#endif

            int type = eax & 0x1F;
            if (type == 0) break; // No more caches

            int level = (eax >> 5) & 0x7;
            int cache_type = (eax >> 14) & 0x3;

            int cache_sets = ecx + 1;
            int cache_coherency_line_size = (ebx & 0xFFF) + 1;
            int cache_partitions = ((ebx >> 12) & 0x3FF) + 1;
            int cache_ways_of_associativity = ((ebx >> 22) & 0x3FF) + 1;

            int cache_size = cache_sets * cache_coherency_line_size * cache_partitions * cache_ways_of_associativity;

            std::string cache_type_str;
            switch (cache_type) {
                case 1:
                    cache_type_str = "Data Cache";
                    break;
                case 2:
                    cache_type_str = "Instruction Cache";
                    break;
                case 3:
                    cache_type_str = "Unified Cache";
                    break;
                default:
                    cache_type_str = "Unknown Cache";
            }

            std::cout << "L" << level << " " << cache_type_str << ": " << cache_size / 1024 << " KB" << std::endl;
        }
    } else {
        std::cout << "Cache information not available on this CPU." << std::endl;
    }
}

int main() {
    get_cache_info();
    return 0;
}
