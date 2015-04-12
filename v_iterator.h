//
//  v_iterator.h
//  VSTL
//
//  Created by lms on 4/12/15.
//  Copyright (c) 2015 lms. All rights reserved.
//

#ifndef _V_ITERATOR_H
#define _V_ITERATOR_H

namespace VSTL{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_acess_iterator_tag : public bidirectional_iterator_tag {};
    
    template <class Category, class
    
}

#endif
