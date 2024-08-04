#include "mem_pool.h"
struct MyStruct {
	int d_[3];
};

int main(int, char**) {
	using namespace Common;
	MemPool<double> prim_pool(50);
	MemPool<MyStruct> struct_pool(50);
		for(auto i = 0; 

