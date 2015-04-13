//
//  v_reverse_iterator.h
//  VSTL
//
//  Created by lms on 4/13/15.
//  Copyright (c) 2015 lms. All rights reserved.
//

#ifndef _V_REVERSE_ITERATOR_H
#define _V_REVERSE_ITERATOR_H

#include "v_iterator.h"
namespace VSTL {
    template <class Iterator>
    class reverse_iterator{
    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef const pointer const_pointer;
        typedef typename iterator_traits<Iterator>::reference reference;
        typedef const reference const_reference;
        
    private:
        Iterator    base_;
        Iterator    cur_;   //表示iterator所指的
    
    public:
        reverse_iterator() : base_(0), cur_(0) {};
        explicit reverse_iterator(const iterator_type &it) :base_(it){
            auto temp = it;
            cur_ = --temp;
        }
        
        //还没弄懂为何需要这个= =。
        template <class Iter>
        reverse_iterator_t(const reverse_iterator_t<Iter>& rev_it){
            base_ = (iterator_type)rev_it.base();
            auto temp = base_;
            cur_ = --temp;
        };
        
        iterator_type base() const{
            return base_;
        }
        
        reference operator*() const{
            return (*cur_);
        }
        
        const_reference operator*() const{
            return (*cur_);
        }
        
        
        //没懂
        pointer operator->() const{
            return &(operator*());
        }
        
        const pointer operator-> const{
            return &(operator*());
        }
        
        reverse_iterator& operator++(){
            --base;
            --cur_;
            return *this;
        }
        
        //bug?
        reverse_iterator& operator++(int i){
            
        }
    };
}


#endif
