#include "mem_pool.h"

struct MyStruct
{
    int d_[3];
};

int main(int, char **)
{
    using namespace Common;

    MemPool<double> prim_pool(50);
    MemPool<MyStruct> struct_pool(50);

    for (auto i = 0; i < 50; ++i)
    {
        auto p_ret = prim_pool.allocate(i);
        auto s_ret = struct_pool.allocate(MyStruct{i, i + 1, i + 2});

        std::cout << "prim elem: " << *p_ret << " allocated at: " << p_ret << std::endl;
        std::cout << "struct elem: " << s_ret->d_[0] << ", " << s_ret->d_[1] << ", " << s_ret->d_[2] << " allocated at: " << s_ret << std::endl;

        if (i % 5 == 0)
        {

            std::cout << std::endl;
            std::cout << "deallocating prim elem: " << *p_ret << " from: " << p_ret << std::endl;
            std::cout << "deallocating struct elem: " << s_ret->d_[0] << ", " << s_ret->d_[1] << ", " << s_ret->d_[2] << " from: " << s_ret << std::endl;

            prim_pool.deallocate(p_ret);
            struct_pool.deallocate(s_ret);
        }
    }

    return 0;
}


// Output:

/* 
aaroneponymous@Blade-14:~/Aaron's Folder/Projects/hft_book/Building-Low-Latency-Applications-with-CPP/Chapter4$ ./mem_pool_example 
prim elem: 0 allocated at: 0x63bf359d0eb0
struct elem: 0, 1, 2 allocated at: 0x63bf359d1220

deallocating prim elem: 0 from: 0x63bf359d0eb0
deallocating struct elem: 0, 1, 2 from: 0x63bf359d1220
prim elem: 1 allocated at: 0x63bf359d0ec0
struct elem: 1, 2, 3 allocated at: 0x63bf359d1230
prim elem: 2 allocated at: 0x63bf359d0ed0
struct elem: 2, 3, 4 allocated at: 0x63bf359d1240
prim elem: 3 allocated at: 0x63bf359d0ee0
struct elem: 3, 4, 5 allocated at: 0x63bf359d1250
prim elem: 4 allocated at: 0x63bf359d0ef0
struct elem: 4, 5, 6 allocated at: 0x63bf359d1260
prim elem: 5 allocated at: 0x63bf359d0f00
struct elem: 5, 6, 7 allocated at: 0x63bf359d1270

deallocating prim elem: 5 from: 0x63bf359d0f00
deallocating struct elem: 5, 6, 7 from: 0x63bf359d1270
prim elem: 6 allocated at: 0x63bf359d0f10
struct elem: 6, 7, 8 allocated at: 0x63bf359d1280
prim elem: 7 allocated at: 0x63bf359d0f20
struct elem: 7, 8, 9 allocated at: 0x63bf359d1290
prim elem: 8 allocated at: 0x63bf359d0f30
struct elem: 8, 9, 10 allocated at: 0x63bf359d12a0
prim elem: 9 allocated at: 0x63bf359d0f40
struct elem: 9, 10, 11 allocated at: 0x63bf359d12b0
prim elem: 10 allocated at: 0x63bf359d0f50
struct elem: 10, 11, 12 allocated at: 0x63bf359d12c0

deallocating prim elem: 10 from: 0x63bf359d0f50
deallocating struct elem: 10, 11, 12 from: 0x63bf359d12c0
prim elem: 11 allocated at: 0x63bf359d0f60
struct elem: 11, 12, 13 allocated at: 0x63bf359d12d0
prim elem: 12 allocated at: 0x63bf359d0f70
struct elem: 12, 13, 14 allocated at: 0x63bf359d12e0
prim elem: 13 allocated at: 0x63bf359d0f80
struct elem: 13, 14, 15 allocated at: 0x63bf359d12f0
prim elem: 14 allocated at: 0x63bf359d0f90
struct elem: 14, 15, 16 allocated at: 0x63bf359d1300
prim elem: 15 allocated at: 0x63bf359d0fa0
struct elem: 15, 16, 17 allocated at: 0x63bf359d1310

deallocating prim elem: 15 from: 0x63bf359d0fa0
deallocating struct elem: 15, 16, 17 from: 0x63bf359d1310
prim elem: 16 allocated at: 0x63bf359d0fb0
struct elem: 16, 17, 18 allocated at: 0x63bf359d1320
prim elem: 17 allocated at: 0x63bf359d0fc0
struct elem: 17, 18, 19 allocated at: 0x63bf359d1330
prim elem: 18 allocated at: 0x63bf359d0fd0
struct elem: 18, 19, 20 allocated at: 0x63bf359d1340
prim elem: 19 allocated at: 0x63bf359d0fe0
struct elem: 19, 20, 21 allocated at: 0x63bf359d1350
prim elem: 20 allocated at: 0x63bf359d0ff0
struct elem: 20, 21, 22 allocated at: 0x63bf359d1360

deallocating prim elem: 20 from: 0x63bf359d0ff0
deallocating struct elem: 20, 21, 22 from: 0x63bf359d1360
prim elem: 21 allocated at: 0x63bf359d1000
struct elem: 21, 22, 23 allocated at: 0x63bf359d1370
prim elem: 22 allocated at: 0x63bf359d1010
struct elem: 22, 23, 24 allocated at: 0x63bf359d1380
prim elem: 23 allocated at: 0x63bf359d1020
struct elem: 23, 24, 25 allocated at: 0x63bf359d1390
prim elem: 24 allocated at: 0x63bf359d1030
struct elem: 24, 25, 26 allocated at: 0x63bf359d13a0
prim elem: 25 allocated at: 0x63bf359d1040
struct elem: 25, 26, 27 allocated at: 0x63bf359d13b0

deallocating prim elem: 25 from: 0x63bf359d1040
deallocating struct elem: 25, 26, 27 from: 0x63bf359d13b0
prim elem: 26 allocated at: 0x63bf359d1050
struct elem: 26, 27, 28 allocated at: 0x63bf359d13c0
prim elem: 27 allocated at: 0x63bf359d1060
struct elem: 27, 28, 29 allocated at: 0x63bf359d13d0
prim elem: 28 allocated at: 0x63bf359d1070
struct elem: 28, 29, 30 allocated at: 0x63bf359d13e0
prim elem: 29 allocated at: 0x63bf359d1080
struct elem: 29, 30, 31 allocated at: 0x63bf359d13f0
prim elem: 30 allocated at: 0x63bf359d1090
struct elem: 30, 31, 32 allocated at: 0x63bf359d1400

deallocating prim elem: 30 from: 0x63bf359d1090
deallocating struct elem: 30, 31, 32 from: 0x63bf359d1400
prim elem: 31 allocated at: 0x63bf359d10a0
struct elem: 31, 32, 33 allocated at: 0x63bf359d1410
prim elem: 32 allocated at: 0x63bf359d10b0
struct elem: 32, 33, 34 allocated at: 0x63bf359d1420
prim elem: 33 allocated at: 0x63bf359d10c0
struct elem: 33, 34, 35 allocated at: 0x63bf359d1430
prim elem: 34 allocated at: 0x63bf359d10d0
struct elem: 34, 35, 36 allocated at: 0x63bf359d1440
prim elem: 35 allocated at: 0x63bf359d10e0
struct elem: 35, 36, 37 allocated at: 0x63bf359d1450

deallocating prim elem: 35 from: 0x63bf359d10e0
deallocating struct elem: 35, 36, 37 from: 0x63bf359d1450
prim elem: 36 allocated at: 0x63bf359d10f0
struct elem: 36, 37, 38 allocated at: 0x63bf359d1460
prim elem: 37 allocated at: 0x63bf359d1100
struct elem: 37, 38, 39 allocated at: 0x63bf359d1470
prim elem: 38 allocated at: 0x63bf359d1110
struct elem: 38, 39, 40 allocated at: 0x63bf359d1480
prim elem: 39 allocated at: 0x63bf359d1120
struct elem: 39, 40, 41 allocated at: 0x63bf359d1490
prim elem: 40 allocated at: 0x63bf359d1130
struct elem: 40, 41, 42 allocated at: 0x63bf359d14a0

deallocating prim elem: 40 from: 0x63bf359d1130
deallocating struct elem: 40, 41, 42 from: 0x63bf359d14a0
prim elem: 41 allocated at: 0x63bf359d1140
struct elem: 41, 42, 43 allocated at: 0x63bf359d14b0
prim elem: 42 allocated at: 0x63bf359d1150
struct elem: 42, 43, 44 allocated at: 0x63bf359d14c0
prim elem: 43 allocated at: 0x63bf359d1160
struct elem: 43, 44, 45 allocated at: 0x63bf359d14d0
prim elem: 44 allocated at: 0x63bf359d1170
struct elem: 44, 45, 46 allocated at: 0x63bf359d14e0
prim elem: 45 allocated at: 0x63bf359d1180
struct elem: 45, 46, 47 allocated at: 0x63bf359d14f0

deallocating prim elem: 45 from: 0x63bf359d1180
deallocating struct elem: 45, 46, 47 from: 0x63bf359d14f0
prim elem: 46 allocated at: 0x63bf359d1190
struct elem: 46, 47, 48 allocated at: 0x63bf359d1500
prim elem: 47 allocated at: 0x63bf359d11a0
struct elem: 47, 48, 49 allocated at: 0x63bf359d1510
prim elem: 48 allocated at: 0x63bf359d11b0
struct elem: 48, 49, 50 allocated at: 0x63bf359d1520
prim elem: 49 allocated at: 0x63bf359d11c0
struct elem: 49, 50, 51 allocated at: 0x63bf359d1530 */