/*
 * main.c
 */

#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"
#include "temp.h" /* needed by translate.h */
#include "tree.h" /* needed by frame.h */
#include "assem.h"
#include "frame.h" /* needed by translate.h and printfrags prototype */
#include "semant.h" /* function prototype for transProg */
#include "canon.h"
#include "prabsyn.h"
#include "printtree.h"
#include "escape.h"
#include "parse.h"
#include "codegen.h"

extern bool anyErrors;

/* print the assembly language instructions to filename.s */
static void doProc(FILE *out, F_frame frame, T_stm body)
{
 AS_proc proc;
 struct RA_result allocation;
 T_stmList stmList;
 AS_instrList iList;

 stmList = C_linearize(body);
 stmList = C_traceSchedule(C_basicBlocks(stmList));
 /* printStmList(stdout, stmList);*/
 iList  = F_codegen(frame, stmList); /* 9 */

 fprintf(out, "BEGIN %s\n", Temp_labelstring(F_name(frame)));
 AS_printInstrList (out, iList,
                       Temp_layerMap(F_tempMap,Temp_name()));
 fprintf(out, "END %s\n\n", Temp_labelstring(F_name(frame)));
}

int main(int argc, string *argv)
{
 A_exp absyn_root;
 S_table base_env, base_tenv;
 F_fragList frags;
 char outfile[100];
 FILE *out = stdout;

 if (argc==2) {
   absyn_root = parse(argv[1]);
   if (!absyn_root)
     return 1;
     
#if 0
   pr_exp(out, absyn_root, 0); /* print absyn data structure */
   fprintf(out, "\n");
#endif

   Esc_findEscape(absyn_root); /* set varDec's escape field */

   frags = SEM_transProg(absyn_root);
   if (anyErrors) return 1; /* don't continue */

   /* convert the filename */
   sprintf(outfile, "%s.s", argv[1]);
   out = fopen(outfile, "w");
   /* Chapter 8, 9, 10, 11 & 12 */
   for (;frags;frags=frags->tail)
     if (frags->head->kind == F_procFrag) 
       doProc(out, frags->head->u.proc.frame, frags->head->u.proc.body);
     else if (frags->head->kind == F_stringFrag) 
       fprintf(out, "%s\n", frags->head->u.stringg.str);

   fclose(out);
   return 0;
 }
 EM_error(0,"usage: tiger file.tig");
 return 1;
}
