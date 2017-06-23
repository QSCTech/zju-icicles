/*
 * types.c - 
 *
 * All types and functions declared in this header file begin with "Ty_"
 * Linked list types end with "..list"
 */

#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "types.h"

static struct Ty_ty_ tynil = {Ty_nil};
Ty_ty Ty_Nil(void) {return &tynil;}

static struct Ty_ty_ tyint = {Ty_int};
Ty_ty Ty_Int(void) {return &tyint;}

static struct Ty_ty_ tystring = {Ty_string};
Ty_ty Ty_String(void) {return &tystring;}

static struct Ty_ty_ tyvoid = {Ty_void};
Ty_ty Ty_Void(void) {return &tyvoid;}

Ty_ty Ty_Record(Ty_fieldList fields)
{Ty_ty p = checked_malloc(sizeof(*p));
 p->kind=Ty_record;
 p->u.record=fields;
 return p;
}

Ty_ty Ty_Array(Ty_ty ty)
{Ty_ty p = checked_malloc(sizeof(*p));
 p->kind=Ty_array;
 p->u.array=ty;
 return p;
}

Ty_ty Ty_Name(S_symbol sym, Ty_ty ty)
{Ty_ty p = checked_malloc(sizeof(*p));
 p->kind=Ty_name;
 p->u.name.sym=sym;
 p->u.name.ty=ty;
 return p;
}


Ty_tyList Ty_TyList(Ty_ty head, Ty_tyList tail)
{Ty_tyList p = checked_malloc(sizeof(*p));
 p->head=head;
 p->tail=tail;
 return p;
}

Ty_field Ty_Field(S_symbol name, Ty_ty ty)
{Ty_field p = checked_malloc(sizeof(*p));
 p->name=name;
 p->ty=ty;
 return p;
}

Ty_fieldList Ty_FieldList(Ty_field head, Ty_fieldList tail)
{Ty_fieldList p = checked_malloc(sizeof(*p));
 p->head=head;
 p->tail=tail;
 return p;
}

/* printing functions - used for debugging */
static char str_ty[][12] = {
   "ty_record", "ty_nil", "ty_int", "ty_string", 
   "ty_array", "ty_name", "ty_void"};

/* This will infinite loop on mutually recursive types */
void Ty_print(Ty_ty t)
{
  if (t == NULL) printf("null");
  else { printf("%s", str_ty[t->kind]);
         if (t->kind == Ty_name) {
	   printf(", %s", S_name(t->u.name.sym)); }
       }
}

void TyList_print(Ty_tyList list)
{
  if (list == NULL) printf("null");
  else {
    printf("TyList( ");
    Ty_print(list->head);
    printf(", ");
    TyList_print(list->tail);
    printf(")");
  }
}

