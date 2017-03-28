#pragma once

#include "Definitions.h"

typedef struct player_info_s {
private:
    int64_t unknown;
public:
    union {
        int64_t xuid;
        struct {
            int xuid_low;
            int xuid_high;
        };
    };
    char name[MAX_PLAYER_NAME_LENGTH + 96];
    int userid;
    int m_nUserID;
    char guid[SIGNED_GUID_LEN + 1];
    unsigned int friendsid;
    char friendsname[MAX_PLAYER_NAME_LENGTH + 96];
    bool fakeplayer;
    bool ishltv;
    unsigned int customfiles[4];
    unsigned char filesdownloaded;
} player_info_t;
