//
//  IVModelInfoClient.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 23.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef IVModelInfoClient_h
#define IVModelInfoClient_h

struct model_t;

class IVModelInfoClient {
public:
    virtual ~IVModelInfoClient (void) {};
    virtual const model_t* GetModel(int modelindex) const = 0;
    virtual int GetModelIndex(const char* name) const = 0;
    virtual const char* GetModelName(const model_t* model) const = 0;
};

#endif /* IVModelInfoClient_h */
