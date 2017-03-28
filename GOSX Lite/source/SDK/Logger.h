//
//  Logger.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 21.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Logger_hpp
#define Logger_hpp

#include "Engine/common.h"

class FileLogger {
public:
    FileLogger();
    static FileLogger* Instance() {
        if(!instance) {
            instance = new FileLogger();
        }

        return instance;
    }

    template <typename type>
    void Log(const char* file, const char* mask, type content) {
        std::ofstream logFile;

        logFile.open(file, std::ios::out | std::ios::app);

        if(!logFile.good()) {
            logFile.close();
            return;
        }

        char fileContent[1024] = "";
        sprintf(fileContent, mask, content);

        logFile << fileContent << std::endl;
        
        logFile.close();
    }
private:
    static FileLogger* instance;
};

#endif /* Logger_hpp */
