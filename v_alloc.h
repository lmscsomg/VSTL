//
//  v_alloc.h
//  VSTL
//
//  Created by lms on 4/5/15.
//  Copyright (c) 2015 lms. All rights reserved.
//

#ifndef _V_ALLOC_H
#define _V_ALLOC_H

namespace VSTL
{
    class alloc{
    private:
        enum VAlign{ ALIGN = 8};
        enum VMax_bytes{ MAX_BYTES = 128};
        enum VNfreelists{ NFREELISTS = VMax_bytes::MAX_BYTES/VAlign::ALIGN }
    
    private:
        union obj{
            union obj *free_list_link;
            char client_data[1];
        };
    };
    
}

#endif
