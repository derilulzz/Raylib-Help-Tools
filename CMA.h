#ifndef COOL_MEMORY_ALLOCATOR
#define COOL_MEMORY_ALLOCATOR


#include "raylib.h"
#include "stdio.h"


#define MAX_ALLOCS 1000
void* Alocs[MAX_ALLOCS] = {NULL};
int AlocsSizes[MAX_ALLOCS] = {-1};
int AllocatedMem = 0;


const char * GetMemoryAmntTxt() {
	const char * MemType = "Bytes";
	int RemoveAmnt = 0;


	if (AllocatedMem < 1000000) {
		MemType = "Bytes";
	}else if (AllocatedMem < 1000000 * 1000) {
		MemType = "Megabytes";
		RemoveAmnt += 1000000;
	}else{
		MemType = "Gigabytes";
	}


	const char * MemBff = TextFormat("%i %s", AllocatedMem - RemoveAmnt, MemType);
	return MemBff;
}


int GetMemorySize(void* Ptr) {
	for (int i = 0; i < MAX_ALLOCS; i++) {
		if (Alocs[i] == Ptr) {
			return AlocsSizes[i];
		}
	}


	return 0;
}
void AddPtr(void* What, int Size) {
	for (int i = 0; i < MAX_ALLOCS; i++) {
		if (Alocs[i] == NULL) {
			Alocs[i] = What;
			AlocsSizes[i] = Size;
			return;
		}
	}
}
void RemovePtr(void* What) {
	for (int i = 0; i < MAX_ALLOCS; i++) {
		if (Alocs[i] == What) {
			Alocs[i] = NULL;
			AlocsSizes[i] = -1;
			return;
		}
	}
}
bool HasPtr(void* What) {
    for (int i = 0; i < MAX_ALLOCS; i++) {
        if (Alocs[i] == What) {
            return true;
        }
    }


    return false;
}


void* AllocateMem(size_t Size) {
	void* Ptr = MemAlloc(Size);
	AddPtr(Ptr, Size);
	AllocatedMem += Size;
	return Ptr;
}


void FreeMem(void* What) {
	int Size = GetMemorySize(What);
	AllocatedMem -= Size;
	RemovePtr(What);
	MemFree(What);
}


void FreeAllMem() {
	for (int i = 0; i < MAX_ALLOCS; i++) {
		if (Alocs[i] != NULL) {
			FreeMem(Alocs[i]);
		}
	}
}


#endif
