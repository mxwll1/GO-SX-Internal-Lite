//
//  CClientState.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 23.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef CClientState_h
#define CClientState_h

class CBaseClientState {
public:
    void ForceFullUpdate() {
        *(int*)((uintptr_t)this + 0x204) = -1;
    };
};

#endif /* CClientState_h */
