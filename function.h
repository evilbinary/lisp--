//
//  function.h
//  lisp--
//
//  Created by evil on 11/23/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#ifndef __lisp____function__
#define __lisp____function__

#include <stdio.h>
#include "object.h"


void register_functions();

//primop buildin function
object *prim_sum(object *args);
object *prim_sub(object *args);
object *prim_mul(object *args);
object *prim_div(object *args);

object *prim_numeq(object *args);
object * prim_numgt(object *args);
object * prim_numlt(object *args);
object *prim_cons(object *args);
object *prim_car(object *args) ;
object *prim_cdr(object *args);
object *prim_or(object *args);
object *prim_and(object *args);
object *prim_setcar(object *args);
object *prim_setcdr(object *args);

object *apply_proc(object *args);


//funs
object *display(object *args);
object *print_dot_obj_proc(object *args);


object *newline(object *args);
object *notf(object *args);



object *is_pair(object *args);
object *is_number(object *args);
object *is_interger(object *args);
object *is_boolean(object *args);
object *is_real(object *args);
object *is_eq(object *args);
object *is_zero(object *args);

object *is_symbol(object *args);
object *is_string(object *args);
object *is_char(object *args);
object *is_atom(object *args);
object *is_procedure(object *args);
object *is_null(object *args);


object *sys_get_top_env(object*args);
object *sys_lookup(object *args);
object *sys_lookup_var(object *args);
object *sys_lookups(object *args);


object *sys_update(object *args);
object *sys_load(object *args);
object *sys_read(object *args);
object *sys_error(object *args);
object *sys_set_log_level(object *args);

object *load_file(char *name);


#endif /* defined(__lisp____function__) */
