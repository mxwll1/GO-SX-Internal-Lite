//
//  EconomyItem.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 23.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef EconomyItem_h
#define EconomyItem_h

struct EconomyItem_t {
    void Reset() {
        this->entity_quality = -1;
        this->fallback_seed = -1;
        this->fallback_paint_kit = -1;
        this->fallback_stattrak = -1;
        this->fallback_wear = -1;
        this->item_definition_index = -1;
    }

    bool is_valid = false;
    int entity_quality = -1;
    int fallback_seed = -1;
    int fallback_paint_kit = -1;
    int fallback_stattrak = -1;
    float fallback_wear = -1;
    int item_definition_index = -1;
    char custom_name[32];
};

#endif /* EconomyItem_h */
