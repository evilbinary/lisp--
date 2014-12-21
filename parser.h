//
//  parser.h
//  lisp--
//
//  Created by evil on 11/22/14.
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//

#ifndef lisp___parser_h
#define lisp___parser_h


#include "object.h"
#include "define.h"


void eatws(io* in);
bool is_delimiter(int c);
bool is_initial(int c);
int peek(io *in);

object* parse(io* in);
object *pair(io* in);


#endif
