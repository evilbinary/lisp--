//
//  main.c
//  lisp--
//
//  Created by evil on 11/22/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#include <stdio.h>
#include "parser.h"
#include "object.h"
#include "define.h"
#include <unistd.h>

typedef int (*FUN)();


int lisp_test0(){
    init();
    object *p=mkobj("hello");
    object o=*p;
    /*cout<<nil;
    cout<<o<<endl;
    object* t=o.car(&o);
    cout<<*t<<endl;
    cout<<"=====find if symbol."<<endl;
    object * tmp=t->findsym("if");
    cout<<"=====find if symbol end."<<endl;
    cout<<(*tmp)<<endl;
    cout<<*(tmp->car())<<endl;
    cout<<*(tmp->cdr())<<endl;
    cout<<*(tmp->car(tmp))<<endl;
    tmp->print();
    
    cout<<"======find labmda."<<endl;
    object * lambda=t->findsym("lambda");
    cout<<"======find labmda end."<<endl;
    lambda->tprint();
    
    lambda->print();
    
    {
        object& a=o;
    }
    cout<<*o.car()<<endl;;
    o.dprint();
    cout<<endl;
    symbols->dprint();
    cout<<endl;
    //o.eval(&o,&o);*/
    
    return 0;
}

int test_parse(int number,char *test,char *result){
    /*Parser p;
    object *obj=p.parse(test);
    stringstream os;
    obj->dstream(os);
    if(os.str()!=result){
        cout<<"[FAILED] test"<<number<<" input:"<<test<<" result:"<<result<<" ret:"<<os.str()<<endl;
        return 0;
    }else{
        cout<<"[PASS] test"<<number<<" input:"<<test<<" result:"<<result<<" ret:"<<os.str()<<endl;;
        return 1;
    }*/
    return 0;
}
int test_eval(int number,char *test,char *result,int type){
    object *env=NULL;
    object *obj=parse(stdin);
    object *ret;
    init();
    ret=eval(obj,env);
    char * r=symname(ret);
    if(strcmp(r,result)==0 ){
        error("[FAILED] test input:%s result:%s ret:",r,result);
        return 0;
    }else{
        error("[PASS] test input:%s result:%s ret:",r,result);
        return 1;
    }
    
    return 0;
}



int lisp_test1(){
    char *test_string[]={"(A B C)",
        "((A) B C)",
        "((A B) C D)",
        "(A (B) C)",
        "(A B (C))",
        "((A) (B) (C))",
        "(((A B)))",
        "(abc efg)",
        "(a . b)"
    };
    char *test_result[]={"(A . (B . (C . nil)))",
        "((A . nil) . (B . (C . nil)))",
        "((A . (B . nil)) . (C . (D . nil)))",
        "(A . ((B . nil) . (C . nil)))",
        "(A . (B . ((C . nil) . nil)))",
        "((A . nil) . ((B . nil) . ((C . nil) . nil)))",
        "(((A . (B . nil)) . nil) . nil)",
        "(abc . (efg . nil))",
        "(a . b)"
    };
    int count=0;
    int i;
    for(i=0;i<sizeof(test_string)/sizeof(char*);i++){
        count=test_parse(i,test_string[i],test_result[i]);
    }
    
    return 0;
}
int lisp_test2(){
    /*init();
    Parser p;
    object *env=NULL;
    object *o[5]={NULL};
    char *test[]={
        "(define count 0)",
        "(define jj (lambda () (if (< count 10000) (begin (set! count (+ count 1)) (jj)) count)))",
        "(jj)",
        "(define count 0)",
        "(jj)",
    };
    for(int i=0;i<5;i++){
        o[i]=p.parse(test[i]);
        
        cout<<"["<<i<<"]"<<"<<<<<<===============#################################  "<<test[i]<<endl;
        object *ret=o[i]->eval(o[i],env);
        
        cout<<">>>>>>>===============################################# result="<<ret;
        cout<<endl;
    }*/
    return 0;
}
int test_eval2(int type){
    //test1();
    //    object *o=p.parse("((A) B C)");
    //    o->dprint();
    //    o->car()->dprint();
    //    o->cdr()->car()->dprint();
    //    o->cdr()->cdr()->dprint();
    init();
    object *env;
    char *test_primop="(/ (+ (+ 1 2) (+ 3)  (+ 4 (+ 1 2)) (+ 1 2) (- 5 3) (* 19 2 (+ 1 3))) 3)";
    char *test_lambda="((lambda (a b c) (+ 1 a b c)) 2 3 4)";
    char *test_lambda2="(+ ((lambda (a b c) (+ 1 a b c)) 2 3 4) ((lambda (a b c) (+ 1 a b c)) 2 1 1114))";
    char *test_define="(define x 100)";
    char *test_define2="(define f (lambda (x) (+ 1 x)))";
    char *test_define3="(define (f x y) (+ 1 x y))";
    char *test_if="(if (= 12 13) 1 2)";
    char *test_car="(car '(a b c d))";
    char *test_cdr="(cdr '(a b c d))";
    char *test_cons="(cons '(a)  'c))";
    char *test_cons2="(car (cdr (car (cons (cons '(a b c d e f g) '(c d e f g)) '(aaaa bbbbb cccc)))))";
    char *test_define_set="(define x nil)";
    char *test_setb="(set! x '(a b c d e f))";
    char *test_setcar="(cdr x)";
    char *test_begin="(begin (+ 1 2) (+ 3 4) (+ 9 8))";
    
    char *test_mix="(define add3 (lambda (x) (+ x 3)))";
    char *test_mix1=" (define f1 (+ 1))";
    char *test_mix2="(begin  f1 add3 (add3 10) )";
    char *test_gt="(> 10 2)";
    char *test_lt="(< 10 2 )";
    
    //    char test_define_add[]="(define (add exp) (+ exp))";
    //    char test_call_define[]="(add 2)";
    //
    char *test_string[]={
        test_primop,
        test_lambda,
        test_lambda2,
        test_define,
        test_define2,
        test_define3,
        test_if,
        test_car,
        test_cdr,
        test_cons,
        test_cons2,
        test_define_set,
        test_setb,
        test_setcar,
        test_begin,
        test_mix,
        test_mix1,
        test_mix2,
        test_gt,
        test_lt
    };
    char *test_result[]={
        "56.66666667",//test_primop
        "10",//test_lambda
        "1128",//test_lambda2
        "",//test_define
        "", //test_define2
        "",//test_define3
        "2",//(if (= 12 13) 1 2)
        "a",//(car '(a b c d))
        "(b . (c . (d . nil)))",//test_cdr
        "((a . nil) . c)",//test_cons
        "c",//test_cons2
        "",//test_define_set
        "",//test_setb
        "(b . (c . (d . (e . (f . nil)))))",//test_setcar
        "17",//test_begin
        "",//test_mix
        "",//test_mix1
        "13",//test_mix2
        "#t",//test_gt
        "#f",//test_lt
    };
    int i;
    for(i=0;i<sizeof(test_string)/sizeof(char*);i++){
        test_eval(i,test_string[i],test_result[i],type);
    }
    return 0;
}


int lisp_test();
int lisp_test_1();
int lisp_test_2();
int lisp_test_3(int a,int b);

int lisp_test4(){
    return test_eval2(1);
}

int lisp_test3(){
    return test_eval2(0);
}
int lisp_test5(){
    return test_eval2(3);
}
#define LISP_VERSION "0.2.2"


void print_help(const char *name){
         printf("Lisp++ v%s\n"\
         "    Created by evil on 9/7/14.\n"\
         "    Copyright (c) 2014 evilbinary.org. All rights reserved.\n"
         "    rootntsd@gmail.com\n"\
         "Help info:\n"\
         "%s (direct to run interactive mode.)\n"\
         "%s [file] (run lisp with file.)\n",
                LISP_VERSION ,name,name);
}

int main(int argc, const char * argv[]) {
    
    object *env=nil;
    init();
    object *ret;
    io* in;
    int mode=0;
    
    FUN tests[]={lisp_test0,lisp_test1,lisp_test2,lisp_test3,lisp_test4,lisp_test5};
    
    if(argc>=1){
        bool argh=false; //for help
        bool argt=false;//for test
        char* argf="";//for file
        bool arginfo=false;
        int i;
        for(i=1;i<argc;i++){
            char* arg=argv[i];
            if(arg[0]=='-'){
                //cout<<argv[i]<<endl;
                if(strcmp(arg,"-t")==0){
                    //                    argt=string(argv[i]);
                    argt=true;
                }else if(strcmp(arg,"--info") ==0){
                    arginfo=true;
                }else if(strcmp(arg,"--test")==0){
                    if((i+1)<argc){
                        int num=atoi(argv[++i]);
                        if(num>=0&&num<sizeof(tests)/sizeof(FUN)){
                            return tests[num]();
                        }
                    }
                    
                }else if(strcmp(arg,"-h")==0||strcmp(arg,"--h")==0||strcmp(arg,"--help")==0||strcmp(arg,"-help")==0){
                    print_help(argv[i]);
                    return 0;
                }else if(strcmp(arg,"--load")==0){
                    if((i+1)<argc){
                        load_file(argv[i+1]);
                        i++;
                    }
                }
            }else{
                
                argf=argv[i];
                //                cout<<"argf:"<<argf<<endl;
            }
        }
        
        if(strcmp(argf,"")!=0){
            in=fopen(argf,"r");
            if(in==NULL){
                printf("open file %s fail.\n",argf);
                return 0;
            }
            mode=1;
        }else{
            in=stdin;
            mode=0;
        }
        
        while(true){
            object *o;
            object *ret;
            //            printf("a=======:%c\n",peek(in));
            
            if(mode==0){
                printf(">");
            }
            o=parse(in);
            if(o==NULL){
                break;
            }
            //            if(istrm.peek()==EOF&&o==eob){
            //                break;
            //            }
            if(arginfo){
                printf("#input:");
                write_obj(stdout, o);
                printf("\n");
            }
            ret=eval(o,env);
            if(arginfo){
                //                    cout<<"#result:";
            }
            if(ret!=none){
                //                    cout<<ret<<endl;
            }
            if(arginfo){
                //                    cout<<endl;
            }
            //            if(ret!=nil){
            if(mode==0||mode==1){
                print_obj(ret);
                if(ret!=none&&ret!=sym_status&&ret!=NULL){
                    printf("\n");
                    
                    //            vm_push_obj(o);
                    //            vm_pop();
                }
            }else{
                
            }
            
            //            }
            
        }
        fclose(in);
        
        return 0;
    }
}
