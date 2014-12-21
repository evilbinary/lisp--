//
//  object.c
//  lisp--
//
//  Created by evil on 11/22/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#include "object.h"
#include "function.h"
#include "memory.h"

extern object *top_env=NULL;


void write_dot_obj(io* out,object *obj){
    if(obj==nil){
         fprintf(out,"()");
        return ;

    }
    switch (obj->type) {
        case EOB:{
            fprintf(out, "%s",(const char*)obj->data);
            break;
        }
//        case nil:
//            fprintf(out,"()");
//            break;
        case CHAR:
                fprintf(out,"%c",*(char*)obj->data);
            break;
        case INT:
            fprintf(out,"%d",*(int*)obj->data);
             break;
        case FLOAT:
            fprintf(out,"%.10f",*(double*)obj->data);
            break;
        case STRING:{
            fprintf(out, "%s",(const char*)obj->data);
             break;
        }
        case SYM:{
            //            if((obj->isnil())){
            //                os<<"nil";
            //            }else{
            if(obj->data!=NULL)
                fprintf(out, "%s",symname(obj));
            //            }
            break;
        }
        case BOOL:{
            fprintf(out, "%s",(const char*)obj->data);
            break;}
        case CONS:
            fprintf(out,"(");
            write_dot_pair(out,obj);
            fprintf(out,")");
            break;
        case PRIMOP:
            fprintf(out,"#<primop %p>",obj->data);
            break;
        case PROC:{
            fprintf(out,"#<procedure %s>",(char*)obj->data);
            break;
        }
        default:
            fprintf(out,"undefine ");
            break;
    }
 }
void write_dot_pair(io* out,object *obj){
    object *first= car(obj);
    object *rest=cdr(obj);
    write_dot_obj(out,first);
    if(first->type==CONS){
        fprintf(out," ");
        write_dot_obj(out,rest);
    }else if(rest->type==nil){
        
    }else{
        fprintf(out," . ");
        write_dot_obj(out,rest);
    }

}

void write_obj(io* out,object *obj){
//    printf("%s\n",__FUNCTION__);
    
    if(obj==NULL){
//        fprintf(out,"NULL");
        return ;
    }else if(obj==none){
        return ;
    }else if(obj->type==EOB){
        if(symname(obj)!=NULL){
        }
        return ;
    }else if(obj==nil){
        fprintf(out,"()");
    }else if(obj->type==SYM||obj->type==BOOL){
        if(obj->data!=NULL)
            fprintf(out,"%s",symname(obj));
    } else if(obj->type==INT){
        fprintf(out,"%d",*(int*)obj->data);
    } else if(obj->type==CHAR){
        fprintf(out,"%c",*(char*)obj->data);
    }else if(obj->type==FLOAT){
        fprintf(out,"%.10f",*(double*)obj->data);
    }else if(obj->type==STRING){
        fprintf(out, "%s",(const char*)obj->data);
    }else if(obj->type==CONS){
        fprintf(out,"(");
        while(true) {
            write_obj(out,car(obj));
            if(cdr(obj)==nil){
                fprintf(out,")");
                break;
            }else if(cdr(obj)==nil){
                
            }else{
                fprintf(out," ");
            }
            obj=cdr(obj);
            if(obj==NULL){
                break;
            }else if(obj->type==nil){
            }else if(obj==nil){
                fprintf(out,")");
                break;
            }else if(obj->type!=CONS){
                fprintf(out,". ");
                write_obj(out,obj);
                fprintf(out,")");
                break;
            }
                
        }
        
    }else if(obj->type==PROC){
        fprintf(out,"#<procedure %s>",(char*)obj->data);
        
        
    }else if(obj->type==PRIMOP){
        fprintf(out,"#<primop %p>",obj->data);
    }
    else {
        fprintf(out,"undefine type:%d.",obj->type);

    }
    
}

void print_obj(object* obj){
    write_obj(stdout, obj);
}
void print_dot_obj(object* obj){
    write_dot_obj(stdout, obj);
}
void println(){
    printf("\n");
}

void init(){
    if(top_env==NULL){
        nil=mksym("nil");
        nil=cons(nil,nil);
        eob=mkobj2(EOB,(void*)NULL);
        
        symbols=cons(nil,nil);
        
        tee=inter("#t");
        tee->type=BOOL;
        fee=inter("#f");
        fee->type=BOOL;
        none=inter("");
        top_env=cons(top_env,nil);
        top_env=cons(tee,fee);
        
        
        object *add=mkpriop(prim_sum);
        object *sub=mkpriop(prim_sub);
        object *mul=mkpriop(prim_mul);
        object *div=mkpriop(prim_div);
        
        extend_top(inter("+"),add);
        extend_top(inter("-"),sub);
        extend_top(inter("*"),mul);
        extend_top(inter("/"),div);
//        top_env=extend(inter("+"),add,top_env);
//        top_env=extend(inter("-"),sub,top_env);
//        top_env=extend(inter("*"),mul,top_env);
//        top_env=extend(inter("/"),div,top_env);
        
        object *mnumeq=mkpriop(prim_numeq);
        object *cons=mkpriop(prim_cons);
        object *car=mkpriop(prim_car);
        object *cdr=mkpriop(prim_cdr);
        object *mnumgt=mkpriop(prim_numgt);
        object *mnumlt=mkpriop(prim_numlt);
        object *primor=mkpriop(prim_or);
        object *primand=mkpriop(prim_and);
        
        
        extend_top(inter("="),mnumeq);
        extend_top(inter("cons"),cons);
        extend_top(inter("car"),car);
        extend_top(inter("cdr"),cdr);
        
        extend_top(inter(">"),mnumgt);
        extend_top(inter("<"),mnumlt);
        extend_top(inter("or"),primor);
        extend_top(inter("and"),primand);

        
//        top_env=extend(inter("="),mnumeq,top_env);
//        top_env=extend(inter("cons"),cons,top_env);
//        top_env=extend(inter("car"),car,top_env);
//        top_env=extend(inter("cdr"),cdr,top_env);
//        
//        top_env=extend(inter(">"),mnumgt,top_env);
//        top_env=extend(inter("<"),mnumlt,top_env);
//        top_env=extend(inter("or"),primor,top_env);
//        top_env=extend(inter("and"),primand,top_env);
        
        
        sym_cond=inter("cond");
        sym_if=inter("if");
        sym_quote=inter("quote");
        sym_define=inter("define");
        sym_setb=inter("set!");
        sym_lambda=inter("lambda");
        sym_begin=inter("begin");
        sym_else=inter("else");
        sym_atom=inter("atom");
        sym_eq=inter("eq");
        sym_car=inter("car");
        sym_cdr=inter("cdr");
        sym_label=inter("sym_label");
        sym_status=inter("");
        sym_and=inter("and");
        sym_or=inter("or");
        sym_let=inter("let");
        
        
        log_level=mkint(LOG_NONE);
        
        //function.c
        register_functions();
    }

}

bool isnil(object *obj){
    if(obj==nil)
        return true;
    return false;
}
object *car(object *obj){
    if(obj!=NULL&&(obj->obj!=NULL)&&!isnil(obj)){
        if( obj->obj[0]==NULL)
            return nil;
        return obj->obj[0];
        
    }
//    printf("car===================\n");
    //return obj;
    return nil;
}
object *cdr(object *obj){
    if(obj!=NULL&&obj->obj!=NULL&&!isnil(obj))
        return obj->obj[1];
    return nil;
}
object *setcdr(object *obj1,object *obj2){
    if(obj1!=NULL&&obj1->obj!=NULL){
        obj1->obj[1]=obj2;
        return obj2;
    }
    return nil;
}
object *setcar(object *obj1,object *obj2){
    if(obj1!=NULL&&obj1->obj!=NULL&&!isnil(obj1)){
        obj1->obj[0]=obj2;
        
        return obj2;
    }
    return nil;
}
object *atom(object *obj){
    if(obj->type==INT||obj->type==SYM||obj->type==STRING||obj->type==FLOAT){
        return tee;
    }
    return fee;
}


object *cons(object* obj1,object *obj2){
    object *o;
    o=mknobj(CONS,2,obj1,obj2);
    setcar(o,obj1);
    setcdr(o,obj2);
    
    
//    vm_push_obj(obj1);
//    vm_push_obj(obj2);
////    vm_push_pair_obj(o);
//    vm_pop();
//    vm_pop();

    
    return  o;
}
object *mksym(char *name){
    return mkobj(name);
}
char*  symname(object *obj){
    char* ret=NULL;
    if(obj==NULL||obj->data==NULL){
        return ret;
    }else if(obj->type==SYM||obj->type==STRING){
        ret=(char *)(obj->data);
    }else if(obj->type==BOOL||obj->type==INT){
        ret=(char *)(obj->data);
    }else if(obj->type==PROC||obj->type==PRIMOP){
        if(obj->data!=NULL)
            ret=(char*)obj->data;
    }else{
         error("%s type %d erro.\n", __FUNCTION__,obj->type);
    }
    
    return ret;
}

object * mknobj(object_type type,int count,...){
    object *thiz=new_obj();
    va_list ap;
    int i;
    va_start(ap,count);
    //    this->obj = (object**) new object[count]();
    thiz->obj=new_objs(count);
    thiz->type = type;
    thiz->isalive=true;
    thiz->data=NULL;
    for(i = 0; i < count; i++){
        object *o=(object *) va_arg(ap,object*);
        thiz->obj[i]=o ;
        
    }
    va_end(ap);
    
//    thiz->flag=INIT;
    return thiz;
}
object * mkobj(char*name){
    object *thiz=new_obj();
    size_t len=strlen(name);
    len++;
    thiz->type=SYM;
    thiz->data=malloc(len);
    memset(thiz->data,0,len);
    strcpy((char*)thiz->data,(const char*)name);
    thiz->obj=NULL;
    thiz->isalive=true;

    return thiz;
}
object * mkobj2(object_type type,void* data){
    object* thiz=new_obj();
    thiz->type=type;
    thiz->data=data;
    thiz->obj=NULL;
    thiz->isalive=true;

    return thiz;
}

object * mkpriop(FUNCTION fun){
    object *o=mkobj2(PRIMOP,(void*)fun);
    return o;
}

object * mkproc(object *args,object *body,object* env){
    object *o=  mknobj(PROC,3,args,body,env);
    return o;
}
object * mkproc2(char* name,object *args,object *body,object* env){
    object *o=mknobj(PROC,3,args,body,env);
    size_t len=strlen(name);
    len++;
    o->data=malloc(len);
    memset(o->data,0,len);
    strcpy((char*)o->data,(const char*)name);
    return o;

}

object *inter(char *name){
    object *op=findsym(name);
    if(!isnil(op)){
        //printf("%p\n",op);
        return car(op);
    }
    
    //DEBUG_INFO;
    op=mksym(name);
    symbols=cons(op,symbols);
    //printf("%p\n",op);
    return op;
}
object *findsym(char* name){
    object *symlist;
    //DEBUG_INFO;
    for(symlist=symbols;symlist!=NULL&&!isnil(symlist);symlist=cdr(symlist)){
        char *name2=symname(car(symlist));
        //DEBUG_INFO;
        if(name2!=NULL&&0==strcmp(name,name2)){
            return symlist;
        }
    }
    return nil;
}

int intval(object *obj){
    if(obj->type==INT){
        return *(int*)obj->data;
    }else if(obj->type==FLOAT){
        int d;
        d=(int)*(double*)obj->data;
        return d;
    }else{
        error("erro obj type %d intval.\n",obj->type);
        return -1;
    }
}
double floatval(object *obj){
    if(obj->type==FLOAT){
        return *(double*)obj->data;
    }else if(obj->type==INT){
        double d;
        d=(double)*(int*)obj->data;
        return d;
    }else{
         error("erro obj type %d floatval.\n",obj->type);

        return -1.0;
    }
}

object *mkchar(char ch){
    char *p=(char*) malloc(sizeof(char));
    *p=ch;
    object *o=mkobj2(CHAR,p);
    return o;
}

object *mkint(int val){
    int *p=(int*) malloc(sizeof(int));
    *p=val;
    object *o=mkobj2(INT,p);
    return o;
}
object *mkfloat(double val){
    double *p=(double*) malloc(sizeof(double));
    *p=val;
    object *o=mkobj2(FLOAT,p);
    return o;
}

object *mkstring(char* name){
    object *o=mkobj(name);
    o->type=STRING;
    return o;
}

object *add_procedure(char *name,FUNCTION function){
    object* funob=mkpriop(function);
    top_env=extend(inter(name),funob,top_env);
    return funob;
}
object_type gettype(object *o){
    if(o==NULL){
        return -1;
    }else{
        return o->type;
    }
}





object * eval(object *exp,object *env){
    object *procedure;
    object *arguments;
    object *result;
calltail:
    if(exp==nil||exp==NULL){
        return exp;
    
    }else if(exp->type==INT||exp->type==STRING||exp->type==FLOAT||exp->type==BOOL||exp->type==CHAR||exp->type==EOB){//to do string boolean and more data type
        return exp;
    }
    else if(exp->type==SYM){
        if(exp==tee||exp==fee||exp==sym_status)
            return exp;
        object* symbol=lookup(exp, env);
//        printf("eeee-==");
//        print_obj(env);
//        println();
        if(symbol==NULL){
            
//            if(strcmp(symname(exp),"product")==0){
//                printf("    id: ");
//                print_obj(exp);
//                printf("   env: ");
//                print_obj(env);
//                println();
//            }
            
            symbol=lookup(exp,top_env);
            if(symbol==NULL){
                error("can't find symbol %s.\n",symname(exp));
//                print_dot_obj(exp);
//                printf("    env:=====: ");
//                print_obj(env);
//                println();
                symbol=NULL;
            }
        }
        return symbol;
    }
    else{
        object *sym=car(exp);
        
//        printf("    exp:");
//        print_obj(exp);
//        println();
        
        if(sym==sym_quote){
            return cadr(exp);
        }else if(sym==sym_setb){
            object *set_var=cadr(exp);
            object *set_val=caddr(exp);
            object *ret=NULL;
            
//            printf("    set_var:");
//            print_obj(set_var);
//            printf(" =");
//            print_obj(eval(set_var,env));
            //println();
            
//            printf("    set_val:");
//            print_obj(set_val);
//            println();
//            print_obj(top_env);
//            println();
            
            
            if(lookup(set_var, top_env)!=NULL){
                set_val=eval(set_val,top_env);
                ret=update(set_var, set_val, top_env);
            }else{
                set_val=eval(set_val,env);
                ret=update(set_var, set_val, env);
            }
        
            
//            printf("    ret=");
//            print_obj(set_val);
//            println();
            
//            set_val=eval(set_val,env);
//            object *ret=update(set_var, set_val, env);
////            print_obj(ret);
////            println();
//            
//            if(ret==NULL){
//                printf("==========================\n");
////                set_val=eval(set_val,top_env);
//                ret=update(set_var, set_val, top_env);
//            }
            return sym_status;
        }else if(sym==sym_define){
            object *def_var;
            object *def_val;
        
            if(cadr(exp)->type==SYM){
                def_var=cadr(exp);
                def_val=caddr(exp);
                def_val=eval(def_val,env);

            }else{
                object *params=cdadr(exp);
                object *body=cddr(exp);
                def_var=caadr(exp);
//                def_val=cons(sym_lambda,cons(params,body));
//                def_val=eval(def_val,env);
                def_val=mkproc2(symname(def_var), params, body, env);
                setcdr(env, cons(cons(def_var,def_val),cdr(env)));
            }
            extend_top(def_var,def_val);

            return sym_status;
        }else if(sym==sym_if){
            object* if_test=cadr(exp);
            object* if_consequent=caddr(exp);
            object * if_alternate=cadddr(exp);
            object *test=eval(if_test,env);
            
//            printf("    if_test:");
//            print_obj(if_test);
//            println();
//            printf("    test:");
//            print_obj(test);
//            println();
            
            if(test==tee||(test!=nil&&test!=fee)){
                exp=if_consequent;//first exp
//                print_obj(if_consequent);
//                println();
            }else{//else exp
                if(cdddr(exp)==nil){
//                    exp=cadddr(exp);
                    return none;
                }else{
//                    printf("    #alternate:");
//                    print_obj(if_alternate);
//                    println();
                    exp=if_alternate;
                }
            }
            goto calltail;
        }else if(sym==sym_lambda){
            object *lambda_parms=cadr(exp);
            object *lambda_body=cddr(exp);
            return mkproc(lambda_parms, lambda_body, env);
        }else if(sym==sym_begin){
            //exp=cdr(exp);
            
            exp=cdr(exp);
            while(cadr(exp)!=nil){//is the last
//                print_obj(car(exp) );
//                println();
                
                eval(car(exp),env);
                exp= cdr(exp);
            }
             exp=car(exp);
            goto calltail;
        }else if(sym==sym_cond){
            object *the_clauses=cdr(exp);
//            printf("    ##the_clauses= ");
//            print_obj(the_clauses);
//            println();
            
//            printf("    ##cdr(the_clauses)=  ");
//            print_obj(cdr(the_clauses));
//            println();
            
            if(cdr(the_clauses)==nil){
                return fee;
            }else{
//                printf("    ##expand_clauses=  ");
//                print_obj(the_clauses);
//                println();
                
                exp=expand_clauses(the_clauses);
//                printf("        ###expand_clauses=  ");
//                print_obj(exp);
//                println();
            }
            goto calltail;
        }else if(sym==sym_atom){
            exp=cadr(exp);
            exp=eval(exp,env);
            return atom(exp);
        }else if(sym==sym_let){
            
            object *let_parms=nil;
            object *let_body=cddr(exp);
            object *let_args=nil;
            
            
            object* let_parms_t=cons(nil,nil);
            object* let_args_t=cons(nil,nil);
            object *e;
            let_parms=let_parms_t;
            let_args=let_args_t;
            
            for(e=cadr(exp);e!=nil;e=cdr(e)){
                object* tmp=car(e);
                
                setcar(let_parms_t,car(tmp));
                setcdr(let_parms_t,cons(nil,nil));
                let_parms_t=cdr(let_parms_t);
                
                setcar(let_args_t,cadr(tmp));
                setcdr(let_args_t,cons(nil,nil));
                let_args_t=cdr(let_args_t);
                
//                env=extend(car(tmp),cadr(tmp),env);
                
            }
//                        env=extend(let_parms,let_args,env);
            
            object *lambda=mkproc(let_parms, let_body, env);
            
//            printf("let_body:");
//            print_obj(let_body);
//            println();
            exp=cons(lambda,let_args);
            //            exp=lambda;
            //            exp=cons(symBegin,lambda);
            //            exp=cons(lambda,nil);
            //            exp->dprint();
            
            goto calltail;
        }else if(exp->type==CONS){//proc to execute
            object *op=car(exp);
            object *ol=cdr(exp);
            
//            printf("    op=");
//            print_obj(op);
//            printf(" ol:");
//            print_obj(ol);
//            printf("\n");
            
//            printf("    procedure=");
//            print_obj(procedure);
//            printf(" op:");
//            print_obj(op);
//            printf(" ol:");
//            print_obj(ol);
//            printf("\n");
            

            procedure=eval(op,env);
            arguments=evlis(ol, env);
            if (intval(log_level)==LOG_DEBUG){
                printf("    #op:");
                print_obj(op);
                printf(" ol:");
                print_obj(ol);
                printf(" env:");
                print_obj(env);
                printf("\n");
                
                printf("        procedure:");
                print_obj(procedure);
                printf(" arguments:");
                print_obj(arguments);
                printf("\n");
                
                object *t=arguments;
                object *f;
                printf("        args:");
                for(;t!=nil;t=cdr(t)){
                    f=car(t);
                    if(f->type==PROC){
                        print_obj(f->obj[1]);
                        printf(",");
                    }
                    else
                        print_obj(f);
                    printf("   ");
                }
                println();
                
            }
            if(procedure==NULL){
                 return exp;
            }
            else if(procedure->type==PRIMOP){
                object *ret= ((FUNCTION)(procedure->data))(arguments);
                if (intval(log_level)==LOG_DEBUG){
                    printf("       ret:");
                    print_obj(ret);
                    printf("\n");
                }
//                printf("arguments:");
//                print_obj(arguments);
//                println();
//                del_all_objs(arguments);
                
                return ret;
            }else if(procedure->type==PROC){
                object *proc_params=car(procedure);//params
                object *proc_body=cdr(procedure);//body
                object *proc_env=procedure->obj[2];

//                printf("====");
//                print_obj(proc_env);
//                printf(" ====end");
//                println();
                env=extend(proc_params,arguments,proc_env);
                exp=cons(sym_begin,proc_body);//make begin this should avoid tail call stack overflow.
                goto calltail;
            }else{
//                goto calltail;
                return procedure;
            }
        }
        else{
//            error("eval erro on exp ");
//            print_obj(exp);
//            printf(" .");
//            printf("type:%d\n",exp->type);
//            println();
            
         }
    }
//    error("eval unknow state.");
    return exp;

}
object * evlis(object *exps,object *env){

    if(exps == nil) return nil;
    return cons(eval(car(exps), env),
                evlis(cdr(exps), env));
    
    if(exps == nil){
        return nil;
    }else if(car(exps)==nil){
        return nil;
    }
    
    object* t=cons(car(exps),nil);
    object*r=t;
    object*l=nil;
    for(;exps!=nil&&exps->type==CONS;exps=cdr(exps)){
        object *te;
//        if(car(exps)->type==PROC){
////                        printf("   ==============\n");
////                    print_dot_obj(te);
////                    println();
//            te=eval(car(exps),car(exps)->obj[2]);
//        }else{
        
        
        te=eval(car(exps),env);
//        }
        printf("    obj-te:");
        print_obj(te);
        println();
       
        setcar(t,te);
        setcdr(t,cons(nil,nil));
        l=t;
        t=cdr(t);
        
    }
//     println();
    setcdr(l,nil);
//    print_dot_obj(r);
//    println();
    return r;

}
object * apply(object *proc,object *args,object *env){
    args=evlis(args,env);
    return ((FUNCTION)(proc->data))(args);
}

object * lookup_var (object *val,object* env){
    while (env!=nil) {
//        print_obj(val);
//        println();
//        printf("    ######");
//        print_obj(cdar(env));
//        println();

        if((val==cdar(env)) ||symname(val)==symname(cdar(env)) ){// ||strcmp(symname(var),symname(caar(env)))==0
//            printf(" =======");
//            print_obj(caar(env));
//            println();
            return caar(env);
        }
        env=cdr(env);
    }
    //    error("unbound variable %s.\n",symname(var));
    return NULL;
}
object * lookups(object *var,object* env){
    while (env!=nil) {
        if((var==caar(env)) ||symname(var)==symname(caar(env)) ){// ||strcmp(symname(var),symname(caar(env)))==0
            return car(env);
        }
        env=cdr(env);
    }
    //    error("unbound variable %s.\n",symname(var));
    return NULL;
}

object * lookup(object *var,object* env){
    while (env!=nil) {
        if((var==caar(env)) ||symname(var)==symname(caar(env)) ){// ||strcmp(symname(var),symname(caar(env)))==0
            return cdar(env);
        }
        env=cdr(env);
    }
//    error("unbound variable %s.\n",symname(var));
    return NULL;
}
//object * values(object *id,object *env);

object * update(object *id,object *value,object* env){
//    printf("id:");
//    print_obj(id);
//    printf(" value:");
//    print_obj(value);
//    printf(" env:");
//    print_obj(env);
//    printf("\n\n");
//    printf("====env->type:%d\n",env->type);
    if(env==NULL){
        return env;
    }else if(env==nil){
        return nil;
    }else if(env->type==CONS){
        
        if(id==caar(env)){

            setcdr(car(env),value);

            return cdar(env);
        }else{
            char* idname=symname(id);
            char *envname=symname(caar(env));
            if(envname==NULL||idname==NULL){
                return NULL;
            }
            else if(idname==envname||strcmp(idname, envname)==0 ){
                 setcdr(car(env),value);
                return cdar(env);

            }
            
            return update(id,value,cdr(env));
        }
    }else{
//        error("no such binding %s.\n",symname(id));
//        print_obj(env);
        
        return NULL;
    }

}


//input as (a b c) (1 2 3) ,then as env list ((a 1) (b 2) (c 3))
object * extend(object *vars,object* vals,object* env){
    if(vars==NULL||vars==nil){
        if(vals==nil){
            return env;
        }else{
            error("too much values.\n");
        }
    }else if(vars->type==CONS){
        if(vals->type==CONS){
            env=cons(cons(car(vars),car(vals)),extend(cdr(vars),cdr(vals),env));
        }else{
            error("too less values.\n");
        }
    }else if(vars->type==SYM){
        env=cons(cons(vars,vals),env);
    }
    return env;
}
object * extend_top(object* var,object *val){
    setcdr(top_env, cons(cons(var,val),cdr(top_env)));
    return val;
}


object * extend2(object *kvpair,object* env);

object *expand_clauses(object *clauses){
    object *first;
    object *rest;
    if (car(clauses)==nil||car(clauses)==nil) {
        return nil;
    }else {
        first = car(clauses);
        rest  = cdr(clauses);
        if (car(first)==sym_else) {
            if (cddr(rest)==nil) {
                return sequence_to_exp(cdr(first));
            }
            else {
                error("else clause isn't last cond->if\n");
                exit(1);
            }
        }
        //        else if(rest==nil){
        //            return first;
        //        }
        else {
            object* if_cond=car(first);
            object *if_seq=sequence_to_exp(cdr(first));
            object *if_else=expand_clauses(rest);
            return cons(sym_if,cons(  if_cond, cons(if_seq,cons(if_else,nil))  ));
        }
    }
}
object *sequence_to_exp(object *seq){
    if(cddr(seq)==nil){
        return seq;
    }else if(cdddr(seq)==nil){
        return cadr(seq);
    }else{
        return cons(sym_begin,seq);
    }
}
object * assoc(object *x,object *y);




