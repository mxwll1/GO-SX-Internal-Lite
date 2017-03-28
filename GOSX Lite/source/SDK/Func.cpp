#include "Func.h"

namespace Func {

    std::string GetWorkingPath()
    {
        char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
        proc_pidpath(getpid(), pathbuf, sizeof(pathbuf));
        auto dirname = DirName(pathbuf);
        return dirname;
    }
    
    std::string DirName(std::string source)
    {
        source.erase(find(source.rbegin(), source.rend(), '/').base(), source.end());
        return source;
    }

    bool IsFileExists(const std::string& name)
    {
        int res = access(name.c_str(), R_OK);
        if (res < 0) {
            if (errno == ENOENT) {
                return false;
            } else if (errno == EACCES) {
                return true;
            } else {
                return true;
            }
        }
        return true;
    }

    IMaterial* CreateMaterial(bool bShouldIgnoreZ, bool bShouldFlat)
    {
        IMaterial* createdMaterial;

        if (bShouldIgnoreZ)
        {
            if (bShouldFlat)
                createdMaterial = Interfaces::MaterialSystem()->FindMaterial("chamsmat_flat_ignorez");
            else
                createdMaterial = Interfaces::MaterialSystem()->FindMaterial("chamsmat_ignorez");
        }
        else
        {
            if (bShouldFlat)
                createdMaterial = Interfaces::MaterialSystem()->FindMaterial("chamsmat_flat");
            else
                createdMaterial = Interfaces::MaterialSystem()->FindMaterial("chamsmat");
        }

        createdMaterial->IncrementReferenceCount();

        return createdMaterial;
    }

    float RandomFloat(float minVal, float maxVal)
    {
        return minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    }
}
