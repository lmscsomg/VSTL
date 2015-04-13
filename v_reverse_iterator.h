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
        Iterator    cur_;
    
    public:
        reverse_iterator() : base_(0), cur_(0) {};
        explicit reverse_iterator(const 
    };
}


#endif
