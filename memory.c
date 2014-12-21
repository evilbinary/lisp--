//
//  memory.c
//  lisp--
//
//  Created by evil on 11/23/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

VM* global_vm=NULL;


void test_vm_gc(){
//    VM* global_vm=newVM();
//    vm_push_obj(new_obj());
//    vm_push_obj(new_obj());
//    vm_push_pair_obj(new_obj());
    
//    freeVM(global_vm);
//    global_vm=NULL;
    
    
    
    
}

object * new_obj(){
    object *o=(object*)malloc(sizeof(object));
//    memset(o,0,sizeof(object));
//    printf("%p type:%d\n",o,o->type);
    
    if(global_vm==NULL){
        global_vm = newVM();
//        printf("%p type:%d\n",o,o->type);
//        test_vm_gc();
//        printf("===test gc ok.===\n",o,o->type);

    }
//    vm_push_obj(o);
    return o;
}




void delete_obj(void *obj){
    if(obj==NULL)
        return;
    object* o=(object*)obj;
    printf("delete obj=");
    print_obj(o);
    println();
    if(o->type==CONS){
        del_objs(o->obj,2);
    }else if(o->type==PROC){
        del_objs(o->obj,3);
    }else{
//        del_objs(o->obj,1);
    }
    del_obj(o);
}

void vm_push_obj(object *obj){
    Object* o = newObject(global_vm, OBJ_POINTER);
    o->pvalue = obj;
    o->free=delete_obj;
    push(global_vm, o);
}
Object* vm_push_pair_obj(object *obj){
    Object* o = newObject(global_vm, OBJ_PAIR);
    o->pvalue=obj;
    o->free=delete_obj;

    o->tail = vm_pop(global_vm);
    o->head = vm_pop(global_vm);

    push(global_vm, o);
    return o;
}
void vm_push(Object *object){
    push(global_vm,object);
}
Object *vm_pop(){
    return  pop(global_vm);
}

void vm_gc(){
    gc(global_vm);
}



object ** new_objs(int count){
    int i;
    object **oo=(object**)malloc(sizeof(object*)*count);
   
    return oo;
}

void del_obj(object *obj){
    if(obj->data!=NULL){
        free(obj->data);
        obj->data=NULL;
    }
    free(obj);
}
void del_objs(object **objs,int count){
    int i;
    for(i=0;i<count;i++){
        free(objs[i]);
    }
}
void del_all_objs(object *obj){
    for(;car(obj)!=nil;obj=cdr(obj)){
        object *o=car(obj);
//        delete_obj(o);
//        free(o);
        
    }
}

