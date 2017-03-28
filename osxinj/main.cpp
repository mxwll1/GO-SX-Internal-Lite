#include "injector.h"

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    std::system("clear");
    if (getuid() > 0) {
        fprintf(stderr, "please run me as root\n");
        return -1;
    }

    char path[4096];
    std::string dylibpath = "gosx.dylib";
    realpath(dylibpath.c_str(), path);

    Injector inj;
    std::string process = "csgo_osx64";
    pid_t pid = inj.getProcessByName(process.c_str());
    if (!pid)
    {
        fprintf(stderr, "process %s not found\n", argv[1]);
        return 0;
    }
    std::system("clear");
    inj.inject(pid, path);
    return 0;
}
