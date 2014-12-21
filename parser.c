//
//  parser.c
//  lisp--
//
//  Created by evil on 11/22/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#include "parser.h"


void eatws(io* in){
    int c;
    while ((c = getc(in))!=EOF) {
        if (isspace(c)) {
            //cout<<"isspace"<<endl;
            continue;
        }else if (c == ';') {//;注释忽略
            //            cout<<"conmmon:"<<(char)c<<endl;
            while (((c = getc(in))) != EOF &&(c !='\n')){
                //                cout<<(char)c<<endl;
            }
            continue;
        }
        ungetc(c,in);
        //in.putback(c);
        break;;
    }

}



//if((ch1>=0x81)&&(ch1<=0xfe))    //GB码
//if((ch1>=0xa1)&&(ch1<=0xfe))    //BIG5码
int is_gbk(int ch){
    if(ch<0) return 0;
    unsigned char *c;
    c=(unsigned char*)&ch;
    if(c[0]>=0x81&&c[0]<=0xef){
        return 1;
    }
    return 0;
    //    if (c[0]>=0xa1){
    //        if (c[0]==0xa3)
    //            return 1;//全角字符
    //        else
    //            return 2;//汉字
    //    }else{
    //        return 0;//英文、数字、英文标点
    //    }
}

bool is_delimiter(int c){
    return isspace(c) || c == EOF ||
    c == '('   || c == ')' ||
    c == '"'   || c == ';';
}

bool is_initial(int c){
    return isalpha(c) || c == '*' || c == '/' || c == '>' ||
    c == '<' || c == '=' || c == '?' || c == '!'||is_gbk(c)||c=='.'||c==':';
}
int peek(io *in) {
    int c;
    c = getc(in);
    ungetc(c, in);
    return c;
}

object* parse_char(io* in){
    char c=getc(in);
    return mkchar(c);
}

object* parse(io* in){
    object *o=NULL;
    int c;
    short sign = 1;
    int num = 0;
    //    cout<<"#=====eof:"<<in.eof()<<" bad:"<<in.bad()<<" failbit:"<<in.fail()<<" good:"<<in.good()<<endl;
    
    eatws(in);
    c=getc(in);
    //    cout<<(char)c<<endl;
    
    if(c=='('){
        // cout<<"(:"<<endl;
        return pair(in);
    }else if(c==EOF){
        return NULL;
    }if (c == '#') {
        c = getc(in);
        switch (c) {
            case 't':
                //                cout<<"#t---"<<Object::tee<<endl;
                return tee;;
            case 'f':
                //                cout<<"#f---"<<Object::fee<<endl;
                
                return fee;
            case '\\':{
                //                cout<<"===================="<<endl;
                return parse_char(in);
            }default:
                error("unknown boolean or character literal\n");
                break;
                
        }
    }else if (isdigit(c) || ((c=='.'||c == '-') && (isdigit(peek(in))))) {
        //        cout<<"c:"<<(char)c<<endl;
        if (c == '-') {
            sign = -1;
        }else {
            ungetc(c,in);
        }
        while (isdigit(c = getc(in))) {
            num = (num * 10) + (c - '0');
        }
        num *= sign;
        if (is_delimiter(c)) {
            ungetc(c,in);
            //cout<<"mkint:"<<num<<endl;
            return mkint(num);
        }else if(c=='.'){
            double fnum=num*1.0;
            double fdp=0.0;
            double dp=0.1;
            while (isdigit(c = getc(in))) {
                fdp = fdp  + (c - '0')*dp;
                //                cout<<"##:"<<(c - '0')*dp<<endl;
                dp=dp*0.1;
            }
            fdp*=sign;
            if(is_delimiter(c)){
                ungetc(c,in);
                //                cout<<"fnum="<<fnum<<" fdp="<<fdp<<" ret:"<<(fnum+fdp)<<endl;
                return mkfloat(fdp+fnum);
            }else{
                error("float number not followed by delimiter\n");
            }
        }else {
            error("number not followed by delimiter\n");
        }
    }
    else if(c=='\''){
        //cout<<"':"<<endl;
        object *str=parse(in);
        //        cout<<"str:"<<str<<endl;
        return cons(sym_quote, cons(str, nil));
        return cons(sym_quote,str);
    }
    //   else if (c == '\'') { /* read quoted expression */
    //        Object *ret= Object::cons(Object::symQuote, Object::cons(parse(in),Object::el));
    ////        cout<<"ret:"<<ret<<endl;
    //        return ret;
    //    }
    else if (c == '"') { /* read a string */
        int i = 0;
        char buf[BUFFER_SIZE]={0};
        while ((c = getc(in)) != '"') {
            if (c == '\\') {
                c = getc(in);
                if (c == 'n') {
                    c = '\n';
                }
            }
            if (c == EOF) {
                fprintf(stderr, "non-terminated string literal\n");
                exit(1);
            }
            /* subtract 1 to save space for '\0' terminator */
            if (i < BUFFER_SIZE - 1) {
                buf[i++] = c;
            }
            else {
                fprintf(stderr,
                        "string too long. Maximum length is %d\n",
                        BUFFER_SIZE);
                exit(1);
            }
        }
        object *obj;
        buf[i] = '\0';
        //        cout<<"buf:"<<buf<<endl;
//        printf("buf:%s\n",buf);
        obj=mkstring(buf);
//        write_obj(stdout, obj);
//        printf("\n");
        //        cout<<"obj:"<<obj<<endl;
        return obj;
    }
    else if(is_initial(c) ||((c=='+'||c=='-')&&is_delimiter(peek(in)) ) ){
        object *obj;
        int i=0;
        char buf[BUFFER_SIZE]={0};
        while(is_initial(c)||isdigit(c)||c=='+'||c=='-'){
            if(i<BUFFER_SIZE-1){
                buf[i++]=c;
            }else{
                error("maximum length of buff %d length.\n",BUFFER_SIZE);
            }
            c=getc(in);
            //            cout<<"ccc:"<<(char)c<<endl;
            //            cout<<buf<<endl;
        }
        if(is_delimiter(c)){
            buf[i]='\0';
            ungetc(c,in);
            obj=inter(buf);
            //            cout<<"obj:"<<obj<<endl;
            //obj->dprint();
            return obj;
        }else{
            //            cout<<c<<" buf:"<<buf<<endl;
            error("symbol '%c'  not followed by delimiter.\n",(char)c);
        }
        //cout<<len<<endl;
        //        cout<<"=======:"<<buf[0]<<buf[len]<<endl;
        
    }else{
        error("syntax error on '%c'.\n",(char)c);
    }
    //cout<<"ret1"<<endl;
    return o;
    
}
object *pair(io* in){
    object *car=NULL;
    object *cdr=NULL;
    int c;
    //    cout<<"#eof:"<<in.eof()<<" bad:"<<in.bad()<<" failbit:"<<in.fail()<<" good:"<<in.good()<<endl;
    
    eatws(in);
    
   
    
    c=getc(in);
    if(c==EOF){
        return NULL;
    }else if(c==')'){
        return nil;
    }
    ungetc(c,in);
    //cout<<"car===begin"<<endl;;
    car=parse(in);
    //    cout<<"car===";
    //    car->dprint();
    eatws(in);
    c=getc(in);
    if (c == '.'&&!isdigit(peek(in))) {
        c = peek(in);
        //        cout<<"pair c===:"<<(char)c<<endl;
        if (!is_delimiter(c)) {
            error("dot not followed by delimiter\n");
        }
        cdr = parse(in);
        eatws(in);
        c = getc(in);
        //        cout<<"cc:"<<(char)c<<endl;
        //        cout<<"cdr:"<<cdr<<endl;
        if (c != ')') {
            //            error("where was the trailing right paren?\n");
            
        }
        return cons(car,cdr);
    }else {
        //        cout<<"pair else "<<endl;
        
        //        if(in.eof())
        //            return Object::nil;
        
        ungetc(c,in);
        
        cdr = pair(in);
        //        cout<<" =car:"<<car<<endl;;
        //        car->dprint();
        
        //        cout<<" =cdr:"<<cdr<<endl;
        //        cdr->dprint();
        object *obj=cons(car, cdr);
        //        cout<<"     =cons:"<<obj<<endl;
        //obj->dprint();
        //cout<<endl;
        return obj;
    }

}



