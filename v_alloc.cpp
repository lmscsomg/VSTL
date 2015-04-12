//
//  v_alloc.cpp
//  VSTL
//
//  Created by lms on 4/12/15.
//  Copyright (c) 2015 lms. All rights reserved.
//

#include "v_alloc.h"

namespace VSTL {
    char *alloc::start_free = 0;
    char *alloc::end_free = 0;
    size_t alloc::heap_size = 0;
    
    alloc::obj *alloc::free_list[alloc::VNfreelists::NFREELISTS] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    
    // 空间配置
    void *alloc::allocate(size_t bytes){
        if (bytes > alloc::VMax_bytes::MAX_BYTES) {
            return malloc(bytes);
        }
        
        size_t index = FREELIST_INDEX(bytes);
        obj *list = free_list[index];
        
        if(list){
            // 拨出一块
            free_list[index] = list->next;
            return list;
        }
        else{
            return refill(ROUND_UP(bytes));
        }
    }
    
    // 空间回收
    void alloc::deallocate(void *p, size_t bytes){
        // 直接回收
        if (bytes > alloc::VMax_bytes::MAX_BYTES) {
            free(p);
        }
        //放入free list中
        else{
            size_t index = FREELIST_INDEX(bytes);
            obj *node = static_cast<obj *>(p);
            node->next = free_list[index];
            free_list[index] = node;
        }
    }
    
    void *alloc::reallocate(void *p, size_t old_sz, size_t new_sz){
        deallocate(p, old_sz);
        p = allocate(new_sz);
        
        return p;
    }
    
    
    // free list中没可用块时，调用refill重新填充空间
    // 新空间取自内存池，由chunk_alloc完成，默认取得20个新节点
    // 返回拍一个大小为bytes的对象，并且有时候会适当为free list增加节点
    void *alloc::refill(size_t bytes){
        size_t nobjs = alloc::VNOBJS::NOBJS;
        
        char *chunk = chunk_alloc(bytes, nobjs);
        
        obj **my_free_list;
        obj *result;
        obj *current_obj, *next_obj;
        
        if (1 == nobjs) {
            return chunk;
        }
        else{
            my_free_list = free_list + FREELIST_INDEX(bytes);
            //在chunk空间内建立free list
            
            result = (obj *)chunk; //这一块分配给客户端
            
            *my_free_list = next_obj = (obj *)(chunk + bytes);
            //将真个free list串起来
            for (int i = 1; ; i++) {
                current_obj = next_obj;
                next_obj = (obj *)((char*)next_obj + bytes);
                
                if (i == nobjs - 1) {
                    current_obj->next = 0;
                    break;
                }
                else{
                    current_obj->next = next_obj;
                }
            }
            
        }
        
        return result;
    }
    
    
    //从内存池中取空间给free list使用
    char *alloc::chunk_alloc(size_t size, size_t &nobjs){
        char *result;
        size_t  total_bytes = size * nobjs;
        size_t  bytes_left = end_free - start_free;
        
        if (bytes_left >= total_bytes) {
            // 满足需求
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else if (bytes_left >= size){
            //至少能供应一个块
            nobjs = bytes_left/size;
            total_bytes = size * nobjs;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else{
            //内存池连一个区块的大小都不能供应
            size_t bytes_to_get = 2*total_bytes + ROUND_UP(heap_size >> 4);
            if (bytes_left > 0) {
                //残余的不到一整块的先分配给适当的free list
                obj **my_free_list = free_list + FREELIST_INDEX(bytes_left);
                
                //将原来的start_free部分当做节点的新头部
                ((obj *)start_free)->next = *my_free_list;
                *my_free_list = (obj *)start_free;
            }
            
            //配置heap空间，补充内存池
            start_free = (char *)malloc(bytes_to_get);
            if (start_free == 0) {
                //heap空间不足,从free list中找可用块
                obj **my_free_list = 0, *p = 0;
                for (size_t i= size; i<=VMax_bytes::MAX_BYTES; i+=VAlign::ALIGN) {
                    my_free_list = free_list + FREELIST_INDEX(i);
                    p = *my_free_list;
                    
                    if (0 != p) {
                        *my_free_list = p->next;
                        start_free = (char *)p;
                        end_free = start_free + i;
                        
                        return  chunk_alloc(size, nobjs);
                    }
                }
                end_free = 0;
            }
            heap_size +=bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunk_alloc(size, nobjs);
        }
    }
}
