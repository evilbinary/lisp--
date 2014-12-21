//
//  object.h
//  lisp--
//
//  Created by evil on 11/22/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#ifndef __lisp____object__
#define __lisp____object__

#include <stdio.h>
#include "define.h"



typedef enum object_type{
    EL,//empyt list
    INT,//1
    SYM,//2
    CONS,//PAIR 3
    PROC,//4
    PRIMOP,//
    STRING,//
    FLOAT,
    INPUT_PORT,
    OUTPUT_PORT,
    EOB,//empty obj
    BOOL,//11,
    CHAR
}object_type;

typedef struct object{
    void *data;
    int isalive;
    object_type type;
    struct object **obj;
    
}object;


typedef object* (*FUNCTION)(object *args) ;

 object *nil;
// object *el;
 object *eob;
 object *tee;
 object *fee;

object *log_level;

object *symbols;
object *top_env;
object *sym_lambda;
object *sym_define;
object *sym_if;
object *sym_quote;
object *sym_atom;
object *sym_setb;
object *sym_begin;
object *none;
object *sym_cond;
object *sym_else;
object *sym_eq;
object *sym_car;
object *sym_cdr;


object *sym_cons;
object *sym_label;
object *sym_and;
object *sym_or;
object *sym_let;
object *sym_status;

object *sym_ok;




object * eval(object *exp,object *env);
object * evlis(object *exps,object *env);
object * apply(object *proc,object *args,object *env);


object * lookup(object *var,object* env);
object * lookups(object *var,object* env);
object * lookup_var(object *val,object* env);

object * extend_top(object* var,object *val);
object * update(object *var,object *value,object* env);
object * extend(object *vars,object* vals,object* env);
object * extend2(object *kvpair,object* env);

object *expand_clauses(object *clauses);
object *sequence_to_exp(object *seq);
object * assoc(object *x,object *y);


void write_dot_obj(io* out,object *obj);
void write_dot_pair(io* out,object *obj);


void write_obj(io* out,object *obj);

void print_obj(object* obj);
void print_dot_obj(object* obj);
void println();

void init();
bool isnil(object *obj);

object *car(object *obj);
object *cdr(object *obj);
object *setcdr(object *obj1,object *obj2);
object *setcar(object *obj1,object *obj2);
object *atom(object *obj);

object *cons(object* obj1,object *obj2);
object *mksym(char *name);
char*  symname(object *obj);

object * mknobj(object_type type,int count,...);
object * mkobj(char*name);
object * mkobj2(object_type type,void* data);

object * mkpriop(FUNCTION fun);

object * mkproc(object *args,object *body,object* env);
object * mkproc2(char* name,object *args,object *body,object* env);

object *inter(char *name);
object *findsym(char* name);
int intval(object *obj);
double floatval(object *obj);

object *mkchar(char ch);
object *mkint(int val);
object *mkfloat(double val);

object *mkstring(char* name);

object *add_procedure(char *name,FUNCTION function);

object_type gettype(object *o);

#endif /* defined(__lisp____object__) */
