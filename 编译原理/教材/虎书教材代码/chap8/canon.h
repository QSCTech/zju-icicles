/*
 * canon.h - Definitions for canon.c which converts the IR trees into
 *           basic blocks and traces.
 *
 */
typedef struct C_stmListList_ *C_stmListList;
struct C_block { C_stmListList stmLists; Temp_label label;};
struct C_stmListList_ { T_stmList head; C_stmListList tail;};

T_stmList C_linearize(T_stm stm);
        /* From an arbitrary Tree statement, produce a list of cleaned trees
	   satisfying the following properties:
	      1.  No SEQ's or ESEQ's
	      2.  The parent of every CALL is an EXP(..) or a MOVE(TEMP t,..)
        */

struct C_block C_basicBlocks(T_stmList stmList);
        /* basicBlocks : Tree.stm list -> (Tree.stm list list * Tree.label)
	       From a list of cleaned trees, produce a list of
	 basic blocks satisfying the following properties:
	      1. and 2. as above;
	      3.  Every block begins with a LABEL;
              4.  A LABEL appears only at the beginning of a block;
              5.  Any JUMP or CJUMP is the last stm in a block;
              6.  Every block ends with a JUMP or CJUMP;
           Also produce the "label" to which control will be passed
           upon exit.
        */

T_stmList C_traceSchedule(struct C_block b);
         /* traceSchedule : Tree.stm list list * Tree.label -> Tree.stm list
            From a list of basic blocks satisfying properties 1-6,
            along with an "exit" label,
	    produce a list of stms such that:
	      1. and 2. as above;
              7. Every CJUMP(_,t,f) is immediately followed by LABEL f.
            The blocks are reordered to satisfy property 7; also
	    in this reordering as many JUMP(T.NAME(lab)) statements
            as possible are eliminated by falling through into T.LABEL(lab).
         */

