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
        enum VAlign{ ALIGN = 8};    //上边界调整，同时也是block size的gap
        enum VMax_bytes{ MAX_BYTES = 128};  //free list中块大小上限
        //free list个数
        enum VNfreelists{ NFREELISTS = VMax_bytes::MAX_BYTES/VAlign::ALIGN}
    
    private:
        // free list节点
        union obj{
            union obj *free_list_link;
            char client_data[1];
        };
        
        //16个free list
        static obj* volatile free_list[VNfreelists::NFREELISTS];
        
    private:
        static char *start_free;    //内存池起始位置
        static char *end_free;      //内存池结束位置
        static size_t heap_size;
        
    private:
        //调整bytes至8的倍数
        static size_t ROUND_UP(size_t bytes){
            return (bytes + VALIGN::ALIGN) & ~(VALIGN::ALIGN-1);
        }
        
        static size_t FREELIST_INDEX(size_t bytes){
            return (bytes + VALIGN::ALIGN-1)/(VALIGN::ALIGN)-1；
        }
        
        //返回一个大小为n的对象，并可能加入大小为n的其他区块到free list
        static void *refill(size_t n);
        
        //配置一大块空间，可荣男nobjs个大小为size的区块
        //若配置nobjs个区块有所不便，nobj可能会降低
        static void *chunk_alloc(size_t size, int &nobjs);
        
    public:
        static void *allocate(size_t n);
        static void deallocate(void *p, size_t n);
        static void *reallocate(void *p, size_t old_sz, size_t new_sz);
    };
}

#endif
