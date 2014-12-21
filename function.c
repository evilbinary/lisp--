//
//  function.c
//  lisp--
//
//  Created by evil on 11/23/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#include "function.h"
#include "parser.h"



void register_functions(){
    add_procedure("display", display);
    add_procedure("newline", newline);
    
    add_procedure("print-dot", print_dot_obj_proc);
    
    //    add_procedure("trace", trace);
    add_procedure("not", notf);
    add_procedure("pair?", is_pair);
    
    add_procedure("sys:top-env", sys_get_top_env);
    add_procedure("sys:lookup", sys_lookup);
    add_procedure("sys:lookups", sys_lookups);
    add_procedure("sys:lookup-var", sys_lookup_var);

    
    add_procedure("sys:find", sys_lookup);
    add_procedure("sys:update", sys_update);
    add_procedure("sys:print-dot", print_dot_obj);
    add_procedure("sys:set-log-level", sys_set_log_level);

    
    add_procedure("load", sys_load);
    add_procedure("symbol?", is_symbol);
    add_procedure("procedure?", is_procedure);
    add_procedure("null?", is_null);
    add_procedure("integer?", is_interger);
    add_procedure("boolean?", is_boolean);
    add_procedure("real?", is_real);
    add_procedure("eq?", is_eq);
    add_procedure("atom?", is_atom);
    add_procedure("number?", is_number);
    add_procedure("string?", is_string);
    add_procedure("zero?", is_zero);
    add_procedure("char?", is_char);
    
    add_procedure("set-car!", prim_setcar);
    add_procedure("set-cdr!", prim_setcdr);
    
    add_procedure("read", sys_read);
    add_procedure("error", sys_error);
    add_procedure("apply", apply_proc);
    

}

//funs
object *display(object *args){
    object *o=cdr(args);
//    
//    printf("dot obj:===");
//    write_dot_obj(stdout, args);
//    println();
    
//    write_obj(stdout,o);
//    printf("o==nil %p %p %p\n",o,nil,tee);
    
//    if(car(args)->type==PROC){
//        write_obj(stdout,car(args)->obj[1] );
//        println();
//        return sym_status;
//    }
    
    if(o==nil){
//        printf("aa");
        write_obj(stdout, car(args));
    }else{
        
    }
    return sym_status;
}
object *newline(object *args){
    if(cdr(args)==nil){
        fprintf(stdout, "\n");
    }
    return sym_status;
}

object *print_dot_obj_proc(object *args){
    object *o=cdr(args);
    if(o==nil){
        //        printf("aa");
        write_dot_obj(stdout, car(args));
    }else{
        
    }
    return sym_status;
}



object *notf(object *args){
    if(car(args)==fee){
        return tee;
    }
    return fee;
}

object *is_pair(object *args){
    if(gettype(car(args))==CONS&&caar(args)!=nil){
        //        error("is_pair tee");
        return tee;
    }
    return fee;
}
object *is_number(object *args){
    if(gettype(car(args))==FLOAT||gettype(car(args))==INT){
        return tee;
    }
    return fee;
}


object *is_interger(object *args){
    if(gettype(car(args))==INT){
        return tee;
    }
    return fee;
}
object *is_boolean(object *args){
    if(gettype(car(args))==BOOL){
        return tee;
    }
    return fee;
}
object *is_real(object *args){
    if(gettype(car(args))==FLOAT||gettype(car(args))==INT){
        return tee;
    }
    return fee;
}
object *is_eq(object *args){
    object *obj1=car(args);
    object *obj2=cadr(args);
    
//    printf("@args::");
//    print_obj(args);
//    printf(" ");
//    printf("obj1:");
//    print_obj(obj1);
//    printf(" obj2:");
//    print_obj(obj2);
//    println();
    
    if(obj1->type!=obj2->type){
        return fee;
    }
    switch (obj1->type) {
        case STRING:
            return (strcmp(symname(obj1), symname(obj2))==0)? tee:fee;
        case INT:
            
            return intval(obj1)==intval(obj2)? tee:fee;
        case FLOAT:
            
            return floatval(obj1)==floatval(obj2)? tee:fee;
        default:
            return obj1==obj2? tee:fee;
    }

    return fee;
}
object *is_zero(object *args){
    object *obj=car(args);
    int type=obj->type;
    if(type==INT ){
        return intval(obj)==0? tee :fee ;
    }else if(type==FLOAT){
        return floatval(obj)==0.0? tee :fee ;
    }else{
        error("type not support.\n");
    }
    return fee;
}

object *is_symbol(object *args){
    //    error(__FUNCTION__<<"  args:";args->dprint();
    
    if(gettype(car(args))==SYM){
        return tee;
    }
    return fee;
}object *is_string(object *args){
    if(gettype(car(args))==STRING){
        return tee;
    }
    return fee;
}object *is_char(object *args){
    if(gettype(car(args))==CHAR){
        return tee;
    }
    return fee;
}
object *is_atom(object *args){
    if(gettype(car(args))!=CONS){
        return tee;
    }
    return fee;
}
object *is_procedure(object *args){
    if(gettype(car(args))==PROC||gettype(car(args))==PRIMOP){
        return tee;
    }
    return fee;
}
object *is_null(object *args){
    //    error(__FUNCTION__<<"  args:";args->dprint();
    if(car(args)==nil){
        return tee;
    }
    return fee;
}


object *sys_get_top_env(object*args){
    return top_env;
}
object *sys_lookup(object *args){
    object *id=car(args);
    object *env=cadr(args);
    return lookup(id, env);
}
object *sys_lookups(object *args){
    object *var=car(args);
    object *env=cadr(args);
    return lookups(var, env);
}
object *sys_lookup_var(object *args){
    object *val=car(args);
    object *env=cadr(args);
    return lookup_var(val, env);
}
object *sys_update(object *args){
    object *id=car(args);
    object *val=cadr(args);
    object *env=caddr(args);
     update(id, val, env );
    return none;
}

object *load_file(char *name){
    object *env=nil;
    init();
    object *ret;
    io* in=fopen(name,"r");
    if(in==NULL){
        error("file %s not exit.\n",name);
        return none;
    }
    //init();
    
    while(true){
        object* o;
        o=parse(in);
        //        printf("aaa===========");
        if(o==NULL)
            break;
        //        write_obj(stderr, o);
        ret=eval(o,env);
        //        write_obj(stderr, ret);
        print_obj(ret);
        if(ret!=none||ret!=sym_status)
            printf("\n");
        //delete ret;
    }
    fclose(in);
    return none;
}

object *sys_load(object *args){
    object *file=car(args);
    char *name=symname(file);
   return load_file(name);
}

object *sys_read(object *args){
    io* in=NULL;
    if(args==nil){
        in=stdin;
    }else{
        
    }
    return parse(in);
}
object *sys_error(object *args){
    while(args!=nil){
        write_obj(stderr, car(args));
        fprintf(stderr, " ");
        args=cdr(args);
    }
    printf("\n");
    return sym_status;
}

object *sys_set_log_level(object *args){
    object *level=car(args);
    log_level=level;
    return sym_status;
}




//build in function
//数学运算、字符串运算(todo)
object *prim_sum(object *args){
    double fsum=0.0;
    int isum=0;
    bool isfloat=false;
    
    for(;car(args)!=nil;args=cdr(args)){
        //        error("    car(args):";car(args)->dprint();
        object *num=car(args);
        if(num->type==INT){
            isum+=intval(num);
        }else if(num->type==FLOAT){
            isfloat=true;
            fsum+=floatval(num);
        }else{
            error("unkown type to sum.\n");
//                print_obj(car(args));
//                printf("\n");
        }        
    }
    //    error("       "<<fsum+isum);
    if(isfloat){
        return mkfloat(fsum+isum);
    }
    
    
    return mkint(isum);
}
object *prim_sub(object *args){
    int isub=0;
    double fsub=0.0;
    bool isfloat=false;
    
    //    error("   sub args:";args->dprint();
    object *first=(car(args));
//    printf("first:%d\n",intval(first));
//    printf("#####################");
//    print_obj(args);
//    printf("===\n");
//    print_obj(    cdr(args));
//    printf("#=\n");
//
    if(cdr(args)==nil){
        if(first->type==INT){
            return mkint(0-intval(first));
        }else if(first->type==FLOAT){
            return mkfloat(0-floatval(first));
        }
    }else{
        
        if(first->type==INT){
            isub=intval(first);
        }else if(first->type==FLOAT){
            fsub=floatval(first);
            isfloat=true;
        }
        
        for(args=cdr(args);car(args)!=nil;args=cdr(args)){
            //        error("    car(args):";car(args)->dprint();
            object *num=car(args);
            //            error(endl;
            if(num->type==INT){
                isub-=intval(num);
            }else if(num->type==FLOAT){
                isfloat=true;
                fsub-=floatval(num);
            }else{
                error("unkown type %d to sub.\n",num->type);
            }
        }
    }
    //    error("       "<<fsub+isub);
    
    if(isfloat){
        return mkfloat(fsub+isub);
    }
    return mkint(isub);
}
object *prim_mul(object *args){
    int imul=1;
    double fmul=1.0;
    bool isfloat=false;
    
    //error("   sub args:";args->dprint();
    object *first=(car(args));
    if(cdr(args)==nil){
        if(first->type==INT){
            return mkint(intval(first));
        }else if(first->type==FLOAT){
            return mkfloat(floatval(first));
        }
    }else{
        for(;car(args)!=nil;args=cdr(args)){
            //        error("    car(args):";car(args)->dprint();
            object *num=car(args);
            //                        error(endl;
            if(num->type==INT){
                imul*=intval(num);
            }else if(num->type==FLOAT){
                isfloat=true;
                fmul*=floatval(num);
            }else{
                error(" unkown type to mul.\n");
            }
        }
    }
    //    error("       "<<fmul*imul);
    
    if(isfloat){
        return mkfloat(fmul*imul);
    }
    return mkint(imul);
    
}
object *prim_div(object *args){
    int idiv=1;
    double fdiv=1.0;
    bool isfloat=false;
    
    //    error("   div args:";args->dprint();
    object *first=(car(args));
    if(cdr(args)==nil){
        if(first->type==INT){
            return mkint(intval(first));
        }else if(first->type==FLOAT){
            return mkfloat(floatval(first));
        }
    }else{
        //        if(first->type==INT){
        //            idiv=intval(first);
        //        }else if(first->type==FLOAT){
        fdiv=floatval(first);
        //            isfloat=true;
        //        }
        //        if(first->type==FLOAT){
        //            isfloat=true;
        //        }
        for(args=cdr(args);car(args)!=nil;args=cdr(args)){
            //            error("    car(args):";car(args)->dprint();
            object *num=car(args);
            //            error(endl;
            if(num->type==INT){
                //                idiv/=intval(num);
                //                error("idiv:"<<idiv);
            }else if(num->type==FLOAT){
                isfloat=true;
                
            }else{
                //                error("unkown type to div.");
            }
            fdiv/=floatval(num);
        }
    }
    //    error("       "<<fdiv);
    
    //    if(isfloat){
    return mkfloat(fdiv);
    //    }
    //    return mkint(fdiv);

}

object *prim_numeq(object *args){
    object *first=(car(args));
    if(cdr(args)==nil){
        error("error = require two argument at least.\n");
        return nil;
    }else{
        int icur=intval(first);
        double fcur=floatval(first);
        
        for(args=cdr(args);car(args)!=nil;args=cdr(args)){
            object *num=car(args);
            if(num->type==INT){
                if(icur!=intval(num)){
                    return fee;
                }else{
                    icur=intval(num);
                    fcur=floatval(num);
                }
            }else if(num->type==FLOAT){
                if(fcur!=floatval(num)){
                    return fee;
                }else{
                    fcur=floatval(num);
                    icur=fcur;
                }
            }else{
                error(" other type not support");
                return nil;
            }
        }
        return tee;
    }

}
object * prim_numgt(object *args){
    object *first=(car(args));
    if(cdr(args)==nil){
        error("error > require two argument at least.\n");
        return nil;
    }else{
        int icur=intval(first);
        double fcur=floatval(first);
        
        for(args=cdr(args);car(args)!=nil;args=cdr(args)){
            object *num=car(args);
            if(num->type==INT){
                if(icur<=intval(num)){
                    return fee;
                }else{
                    icur=intval(num);
                    fcur=floatval(num);
                }
            }else if(num->type==FLOAT){
                if(fcur<=floatval(num)){
                    //                    error("     "<<fee);
                    return fee;
                }else{
                    fcur=floatval(num);
                    icur=fcur;
                }
            }else{
                error(" other type not support\n");
                return nil;
            }
        }
        //        error("     "<<tee);
        return tee;
    }

}
object * prim_numlt(object *args){
    object *first=(car(args));
    if(cdr(args)==nil){
        error("error < require two argument at least.\n");
        return nil;
    }else{
        int icur=intval(first);
        double fcur=floatval(first);
        
        for(args=cdr(args);car(args)!=nil;args=cdr(args)){
            object *num=car(args);
            //            error("         num:"<<num);
            if(num->type==INT){
                if(icur>=intval(num)){
                    //                    error("     3:"<<fee);
                    
                    return fee;
                }else{
                    icur=intval(num);
                    fcur=floatval(num);
                }
            }else if(num->type==FLOAT){
                if(fcur>=floatval(num)){
                    //                    error("     "<<fee);
                    
                    return fee;
                }else{
                    fcur=floatval(num);
                    icur=intval(num);
                }
            }else{
                error(" other type not support\n");
                return nil;
            }
        }
        //        error("     ee:"<<tee);
        
        return tee;
    }
}
//end of数学运算

object *prim_cons(object *args){
     return cons(car(args), car(cdr(args)));
}
object *prim_car(object *args){
//    printf("args=");
//    print_obj(args);
//    printf("\n");
//    printf("    prim car ,args=");
//    printf("    ");
//    print_obj(car(args));
//    printf("\n");
    
    if(gettype(car(args))==CONS ){
        return car(car(args));
    }else{
       
        error("car args must be pair.\n");
        printf("    type:%d ",gettype(car(args)));
        print_obj(car(args));
        printf("\n");
        return (car(args));
    }
}
object *prim_cdr(object *args){
    if(gettype(car(args))==CONS ){
        return cdr(car(args));
    }else{
        error("cdr args must be pair.\n");
        return nil;
    }
//    object *ret=(cdr(car(args)));
//    if(ret==nil){
//        ret=cons(ret,el);
//        ret=el;
//    }
//    return ret;
}
object *prim_or(object *args){
//    error(args);
    object *ret=fee;
    for(;car(args)!=nil;args=cdr(args)){
        if(car(args)==tee){
            //            error("     ="<<car(args));
            return car(args);
        }
    }
    //    error("     ="<<ret);
    
    return ret;
}
object *prim_and(object *args){
    //    error("   primand:";args->dprint();
    //    error(args);
    object *ret=fee;
    for(;car(args)!=nil;args=cdr(args)){
        if(car(args)!=tee){
            //            error("     ="<<car(args));
            return car(args);
        }
    }
    //    error("     ="<<ret);
    
    return ret;
}


//(set-cdr! x x) to fix
object *prim_setcar(object *args){
    object *obj1=car(args);
    object *obj2=cadr(args);
    setcar(obj1, obj2);
    return sym_status;
}
object *prim_setcdr(object *args){
    object *obj1=car(args);
    object *obj2=cadr(args);
    setcdr(obj1, obj2);
    return sym_status;

}



//========end of prim===========

object *apply_proc(object *args){
    object *ret=nil;
    object *proc=car(args);
    object *arguments=cadr(args);
    if(gettype(proc)==PROC){
//        proc->obj[2]=arg;
//        ret=eval(proc, proc->obj[2]);
//        
        object *env;
        object *exp;
        object *proc_params=car(proc);//params
        object *proc_body=cdr(proc);//body
        object *proc_env=proc->obj[2];
        env=extend(proc_params,arguments,proc_env);
        proc->obj[2]=env;
        exp=cons(sym_begin,proc_body);
        return eval(exp, env);
    }else if(gettype(proc)==PRIMOP){
          ret=((FUNCTION)(proc->data))(arguments);
    }else{
        error("apply erro proc type %d.\n",gettype(proc));
    }
    return ret;
}




