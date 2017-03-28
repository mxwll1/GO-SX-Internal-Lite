#include "main.h"

int __attribute__((constructor)) Init() {

    HookManager::Initialize();
    
    return 0;
}

void __attribute__((constructor)) DeInit() {
}
