//
//  gc.h
//  lisp--
//
//  Created by evil on 12/6/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#ifndef lisp___gc_h
#define lisp___gc_h


#define STACK_MAX 2048

typedef enum {
    OBJ_INT,
    OBJ_POINTER,
    OBJ_PAIR
} ObjectType;

typedef void (*FUNC_FREE) (void *addr);

typedef struct sObject {
    ObjectType type;
    unsigned char marked;
    
    FUNC_FREE free;
    
    /* The next object in the linked list of heap allocated objects. */
    struct sObject* next;
    
    union {
        /* OBJ_INT */
        int value;
        /*OBJ_POINTER*/
        
        void *pvalue;
        
        /* OBJ_PAIR */
        struct {
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;

typedef struct {
    Object* stack[STACK_MAX];
    int stackSize;
    
    /* The first object in the linked list of all objects on the heap. */
    Object* firstObject;
    
    /* The total number of currently allocated objects. */
    int numObjects;
    
    /* The number of objects required to trigger a GC. */
    int maxObjects;
} VM;


VM* newVM();
void push(VM* vm,Object *object);
Object* pushPair(VM* vm);
void freeVM(VM *vm);
Object* newObject(VM* vm, ObjectType type);
void gc(VM *vm);
Object* pop(VM* vm);



#endif
