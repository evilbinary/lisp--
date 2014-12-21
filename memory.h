//
//  memory.h
//  lisp--
//
//  Created by evil on 11/23/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#ifndef __lisp____memory__
#define __lisp____memory__

#include <stdio.h>
#include "object.h"

#include "gc.h"



object * new_obj();
object ** new_objs(int count);
void del_obj(object *obj);
void del_objs(object **objs,int count);
void del_all_objs(object *obj);

//Object* vm_push_pair();
void vm_push(Object *object);
void vm_push_obj(object *obj);
Object *vm_pop();
Object* vm_push_pair_obj(object *obj);
void vm_gc();

#endif /* defined(__lisp____memory__) */
