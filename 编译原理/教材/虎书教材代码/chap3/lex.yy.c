# include "stdio.h"
# define U(x) ((x)&0377)
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern unsigned char yytext[];
int yymorfg;
extern unsigned char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
/* Copyright (c) 1997 Andrew W. Appel.  Licensed software: see LICENSE file */
#include <string.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "y.tab.h"
#include "errormsg.h"

static int comLevel=0;

#define STRINGMAX 1024
char stringbuild[STRINGMAX+1];
int stringindex=0;

static void append(char c)
{ if (stringindex<STRINGMAX)
    stringbuild[stringindex++]= c;
  else {EM_error(EM_tokPos,"string too long.");
	stringindex=0;}
}

static string getstring(void)
{stringbuild[stringindex]=0;
 stringindex=0;
 return String(stringbuild);
}
 

int charPos=1;

int yywrap(void)
{
 if (comLevel) 
	EM_error(EM_tokPos,"unclosed comment");
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

# define A 2
# define S 4
# define F 6
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
 {adjust(); continue;}
break;
case 2:
 {adjust(); EM_newline(); continue;}
break;
case 3:
 {adjust(); return COMMA;}
break;
case 4:
 {adjust(); return LBRACE;}
break;
case 5:
 {adjust(); return RBRACE;}
break;
case 6:
 {adjust(); return LBRACK;}
break;
case 7:
 {adjust(); return RBRACK;}
break;
case 8:
 {adjust(); return COLON;}
break;
case 9:
 {adjust(); return SEMICOLON;}
break;
case 10:
 {adjust(); return LPAREN;}
break;
case 11:
 {adjust(); return RPAREN;}
break;
case 12:
 {adjust(); return DOT;}
break;
case 13:
 {adjust(); return PLUS;}
break;
case 14:
 {adjust(); return MINUS;}
break;
case 15:
 {adjust(); return TIMES;}
break;
case 16:
 {adjust(); return DIVIDE;}
break;
case 17:
 {adjust(); return AND;}
break;
case 18:
 {adjust(); return OR;}
break;
case 19:
 {adjust(); return ASSIGN;}
break;
case 20:
 {adjust(); return EQ;}
break;
case 21:
 {adjust(); return NEQ;}
break;
case 22:
 {adjust(); return GT;}
break;
case 23:
 {adjust(); return LT;}
break;
case 24:
 {adjust(); return GE;}
break;
case 25:
 {adjust(); return LE;}
break;
case 26:
 	 {adjust(); return FOR;}
break;
case 27:
 {adjust(); return WHILE;}
break;
case 28:
 {adjust(); return BREAK;}
break;
case 29:
	 {adjust(); return LET;}
break;
case 30:
 	 {adjust(); return IN;}
break;
case 31:
 	 {adjust(); return NIL;}
break;
case 32:
 	 {adjust(); return TO;}
break;
case 33:
 	 {adjust(); return END;}
break;
case 34:
{adjust(); return FUNCTION;}
break;
case 35:
 	 {adjust(); return VAR;}
break;
case 36:
 	 {adjust(); return TYPE;}
break;
case 37:
	 {adjust(); return ARRAY;}
break;
case 38:
	 {adjust(); return IF;}
break;
case 39:
 	 {adjust(); return THEN;}
break;
case 40:
 	 {adjust(); return ELSE;}
break;
case 41:
 	 {adjust(); return DO;}
break;
case 42:
 	 {adjust(); return OF;}
break;
case 43:
 {adjust(); yylval.sval = String((char*)yytext); return ID;}
break;
case 44:
 {adjust(); yylval.ival=atoi(yytext); return INT;}
break;
case 45:
 {adjust(); BEGIN S; continue;}
break;
case 46:
 {adjust(); BEGIN A; comLevel = 1; continue;}
break;
case 47:
 {adjust(); EM_error(EM_tokPos,"unmatched close comment");
		    continue;}
break;
case 48:
 {adjust(); EM_error(EM_tokPos,"non-Ascii character");
		    continue;}
break;
case 49:
 {adjust(); EM_error(EM_tokPos,"illegal token");
		    continue;}
break;
case 50:
	 {adjust(); comLevel++; continue;}
break;
case 51:
	 {adjust(); EM_newline(); continue;}
break;
case 52:
	 {adjust(); comLevel--; 
		    if (comLevel==0) {BEGIN INITIAL;}
	                continue;}
break;
case 53:
	{adjust(); continue;}
break;
case 54:
	{adjust(); BEGIN INITIAL; 
	            yylval.sval=getstring();
	            return STRING;}
break;
case 55:
	 {adjust(); EM_error (EM_tokPos,"unclosed string");
                  EM_newline();
		    BEGIN INITIAL; 
	            yylval.sval=getstring();
		    return STRING;}
break;
case 56:
       	 {adjust(); EM_newline(); BEGIN F; continue;}
break;
case 57:
  	 {adjust(); BEGIN F; continue;}
break;
case 58:
	 {adjust(); append(*yytext); continue;}
break;
case 59:
	 {adjust(); EM_newline(); continue;}
break;
case 60:
	 {adjust(); continue;}
break;
case 61:
	 {adjust(); BEGIN S; continue;}
break;
case 62:
	 {adjust(); EM_error(EM_tokPos, "unclosed string"); 
		    BEGIN INITIAL; 
	           yylval.sval=getstring();
	          return STRING;}
break;
case 63:
	 {adjust(); append('\t'); continue;}
break;
case 64:
	 {adjust(); append('\n'); continue;}
break;
case 65:
	 {adjust(); append('\\'); continue;}
break;
case 66:
 {adjust(); append(yytext[1]); continue;}
break;
case 67:
 {adjust(); append(yytext[2]-'@');
	            continue;}
break;
case 68:
 {int x = yytext[1]*100 + yytext[2]*10 + yytext[3] - 
	                     ('0' * 111);
	          adjust();
                    if (x>255)
                         EM_error(EM_tokPos, "illegal ascii escape");
	            else append(x);
	            continue;
	           }
break;
case 69:
	 {adjust(); EM_error(EM_tokPos, "illegal string escape"); 
		    continue;}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
int yyvstop[] = {
0,

1,
60,
0,

1,
60,
0,

1,
60,
0,

1,
60,
0,

1,
60,
0,

1,
60,
0,

1,
60,
0,

1,
60,
0,

49,
0,

1,
49,
0,

2,
0,

45,
49,
0,

17,
49,
0,

10,
49,
0,

11,
49,
0,

15,
49,
0,

13,
49,
0,

3,
49,
0,

14,
49,
0,

12,
49,
0,

16,
49,
0,

44,
49,
0,

8,
49,
0,

9,
49,
0,

23,
49,
0,

20,
49,
0,

22,
49,
0,

43,
49,
0,

6,
49,
0,

7,
49,
0,

43,
49,
0,

43,
49,
0,

43,
49,
0,

43,
49,
0,

43,
49,
0,

43,
48,
49,
0,

43,
49,
0,

43,
49,
0,

43,
49,
0,

43,
49,
0,

43,
49,
0,

43,
49,
0,

43,
49,
0,

4,
49,
0,

18,
49,
0,

5,
49,
0,

53,
0,

51,
0,

53,
0,

53,
0,

58,
0,

55,
0,

54,
58,
0,

58,
69,
0,

62,
0,

60,
62,
0,

59,
0,

61,
62,
0,

1,
0,

47,
0,

46,
0,

44,
0,

19,
0,

25,
0,

21,
0,

24,
0,

43,
0,

43,
0,

43,
0,

41,
43,
0,

43,
0,

43,
0,

43,
0,

43,
0,

38,
43,
0,

30,
43,
0,

43,
0,

43,
0,

42,
43,
0,

43,
0,

32,
43,
0,

43,
0,

43,
0,

43,
0,

52,
0,

50,
0,

57,
0,

56,
0,

66,
0,

65,
0,

64,
0,

63,
0,

60,
0,

43,
0,

43,
0,

43,
0,

33,
43,
0,

26,
43,
0,

43,
0,

29,
43,
0,

31,
43,
0,

43,
0,

43,
0,

35,
43,
0,

43,
0,

67,
0,

43,
0,

43,
0,

40,
43,
0,

43,
0,

39,
43,
0,

36,
43,
0,

43,
0,

37,
43,
0,

28,
43,
0,

43,
0,

27,
43,
0,

43,
0,

68,
0,

43,
0,

34,
43,
0,
0};
# define YYTYPE unsigned char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,9,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,10,	1,11,	
0,0,	10,59,	0,0,	56,95,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,12,	
10,59,	6,53,	56,95,	1,13,	
0,0,	1,14,	1,15,	1,16,	
1,17,	1,18,	1,19,	1,20,	
1,21,	1,22,	4,49,	16,60,	
21,61,	49,85,	50,86,	4,50,	
0,0,	0,0,	0,0,	1,23,	
1,24,	1,25,	1,26,	1,27,	
23,63,	1,9,	1,28,	22,62,	
22,62,	22,62,	22,62,	22,62,	
22,62,	22,62,	22,62,	22,62,	
22,62,	25,64,	25,65,	27,66,	
0,0,	7,55,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	7,56,	7,57,	0,0,	
1,29,	8,58,	1,30,	6,54,	
1,9,	90,108,	1,31,	1,32,	
1,28,	1,33,	1,34,	1,35,	
1,28,	1,36,	1,37,	1,28,	
1,28,	1,38,	1,28,	1,39,	
1,40,	1,28,	1,28,	1,28,	
1,28,	1,41,	1,28,	1,42,	
1,43,	1,28,	1,28,	1,28,	
1,44,	1,45,	1,46,	2,12,	
7,55,	31,68,	32,69,	2,13,	
33,70,	2,14,	2,15,	2,16,	
2,17,	2,18,	2,19,	2,20,	
2,21,	34,71,	35,73,	34,72,	
7,55,	7,55,	38,77,	39,78,	
35,74,	37,75,	40,79,	2,23,	
2,24,	2,25,	2,26,	2,27,	
41,80,	37,76,	42,83,	43,84,	
68,96,	69,97,	71,98,	41,81,	
72,99,	73,100,	74,101,	77,102,	
78,103,	80,104,	82,105,	83,106,	
7,58,	41,82,	84,107,	7,55,	
96,110,	7,55,	97,111,	3,47,	
98,112,	101,113,	104,114,	105,115,	
2,29,	107,116,	2,30,	3,47,	
3,48,	110,118,	111,119,	2,32,	
2,28,	2,33,	2,34,	2,35,	
2,28,	2,36,	2,37,	2,28,	
2,28,	2,38,	2,28,	2,39,	
2,40,	2,28,	2,28,	2,28,	
2,28,	2,41,	2,28,	2,42,	
2,43,	2,28,	2,28,	2,28,	
2,44,	2,45,	2,46,	5,51,	
3,49,	113,120,	116,121,	117,122,	
120,123,	3,50,	3,47,	5,51,	
5,52,	108,117,	108,117,	108,117,	
108,117,	108,117,	108,117,	108,117,	
108,117,	108,117,	108,117,	123,125,	
125,126,	0,0,	3,47,	3,47,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
5,53,	122,124,	122,124,	122,124,	
122,124,	122,124,	122,124,	122,124,	
122,124,	122,124,	122,124,	0,0,	
0,0,	0,0,	5,51,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	3,47,	0,0,	3,47,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	5,51,	5,51,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	0,0,	5,54,	0,0,	
0,0,	5,51,	0,0,	5,51,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	0,0,	0,0,	
0,0,	0,0,	28,67,	0,0,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	28,67,	28,67,	
28,67,	28,67,	54,87,	54,88,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	54,87,	0,0,	54,89,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	54,90,	54,90,	54,90,	
54,90,	54,90,	54,90,	54,90,	
54,90,	54,90,	54,90,	92,109,	
92,109,	92,109,	92,109,	92,109,	
92,109,	92,109,	92,109,	92,109,	
92,109,	92,109,	92,109,	92,109,	
92,109,	92,109,	92,109,	92,109,	
92,109,	92,109,	92,109,	92,109,	
92,109,	92,109,	92,109,	92,109,	
92,109,	92,109,	92,109,	92,109,	
92,109,	92,109,	92,109,	0,0,	
0,0,	54,91,	0,0,	54,92,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	54,93,	
0,0,	0,0,	0,0,	0,0,	
0,0,	54,94,	0,0,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		yyvstop+1,
yycrank+-93,	yysvec+1,	yyvstop+4,
yycrank+-178,	0,		yyvstop+7,
yycrank+-8,	yysvec+3,	yyvstop+10,
yycrank+-218,	0,		yyvstop+13,
yycrank+-3,	yysvec+5,	yyvstop+16,
yycrank+-80,	0,		yyvstop+19,
yycrank+-1,	yysvec+7,	yyvstop+22,
yycrank+0,	0,		yyvstop+25,
yycrank+4,	0,		yyvstop+27,
yycrank+0,	0,		yyvstop+30,
yycrank+0,	0,		yyvstop+32,
yycrank+0,	0,		yyvstop+35,
yycrank+0,	0,		yyvstop+38,
yycrank+0,	0,		yyvstop+41,
yycrank+4,	0,		yyvstop+44,
yycrank+0,	0,		yyvstop+47,
yycrank+0,	0,		yyvstop+50,
yycrank+0,	0,		yyvstop+53,
yycrank+0,	0,		yyvstop+56,
yycrank+10,	0,		yyvstop+59,
yycrank+19,	0,		yyvstop+62,
yycrank+3,	0,		yyvstop+65,
yycrank+0,	0,		yyvstop+68,
yycrank+16,	0,		yyvstop+71,
yycrank+0,	0,		yyvstop+74,
yycrank+18,	0,		yyvstop+77,
yycrank+251,	0,		yyvstop+80,
yycrank+0,	0,		yyvstop+83,
yycrank+0,	0,		yyvstop+86,
yycrank+15,	yysvec+28,	yyvstop+89,
yycrank+16,	yysvec+28,	yyvstop+92,
yycrank+21,	yysvec+28,	yyvstop+95,
yycrank+33,	yysvec+28,	yyvstop+98,
yycrank+31,	yysvec+28,	yyvstop+101,
yycrank+0,	yysvec+28,	yyvstop+104,
yycrank+47,	yysvec+28,	yyvstop+108,
yycrank+45,	yysvec+28,	yyvstop+111,
yycrank+42,	yysvec+28,	yyvstop+114,
yycrank+48,	yysvec+28,	yyvstop+117,
yycrank+52,	yysvec+28,	yyvstop+120,
yycrank+61,	yysvec+28,	yyvstop+123,
yycrank+55,	yysvec+28,	yyvstop+126,
yycrank+0,	0,		yyvstop+129,
yycrank+0,	0,		yyvstop+132,
yycrank+0,	0,		yyvstop+135,
yycrank+0,	0,		yyvstop+138,
yycrank+0,	0,		yyvstop+140,
yycrank+6,	0,		yyvstop+142,
yycrank+12,	0,		yyvstop+144,
yycrank+0,	0,		yyvstop+146,
yycrank+0,	0,		yyvstop+148,
yycrank+0,	0,		yyvstop+150,
yycrank+365,	0,		yyvstop+153,
yycrank+0,	0,		yyvstop+156,
yycrank+6,	0,		yyvstop+158,
yycrank+0,	0,		yyvstop+161,
yycrank+0,	0,		yyvstop+163,
yycrank+0,	yysvec+10,	yyvstop+166,
yycrank+0,	0,		yyvstop+168,
yycrank+0,	0,		yyvstop+170,
yycrank+0,	yysvec+22,	yyvstop+172,
yycrank+0,	0,		yyvstop+174,
yycrank+0,	0,		yyvstop+176,
yycrank+0,	0,		yyvstop+178,
yycrank+0,	0,		yyvstop+180,
yycrank+0,	yysvec+28,	yyvstop+182,
yycrank+46,	yysvec+28,	yyvstop+184,
yycrank+60,	yysvec+28,	yyvstop+186,
yycrank+0,	yysvec+28,	yyvstop+188,
yycrank+47,	yysvec+28,	yyvstop+191,
yycrank+64,	yysvec+28,	yyvstop+193,
yycrank+51,	yysvec+28,	yyvstop+195,
yycrank+56,	yysvec+28,	yyvstop+197,
yycrank+0,	yysvec+28,	yyvstop+199,
yycrank+0,	yysvec+28,	yyvstop+202,
yycrank+51,	yysvec+28,	yyvstop+205,
yycrank+60,	yysvec+28,	yyvstop+207,
yycrank+0,	yysvec+28,	yyvstop+209,
yycrank+68,	yysvec+28,	yyvstop+212,
yycrank+0,	yysvec+28,	yyvstop+214,
yycrank+58,	yysvec+28,	yyvstop+217,
yycrank+57,	yysvec+28,	yyvstop+219,
yycrank+69,	yysvec+28,	yyvstop+221,
yycrank+0,	0,		yyvstop+223,
yycrank+0,	0,		yyvstop+225,
yycrank+0,	0,		yyvstop+227,
yycrank+0,	0,		yyvstop+229,
yycrank+0,	0,		yyvstop+231,
yycrank+5,	0,		0,	
yycrank+0,	0,		yyvstop+233,
yycrank+359,	0,		0,	
yycrank+0,	0,		yyvstop+235,
yycrank+0,	0,		yyvstop+237,
yycrank+0,	yysvec+56,	yyvstop+239,
yycrank+79,	yysvec+28,	yyvstop+241,
yycrank+81,	yysvec+28,	yyvstop+243,
yycrank+79,	yysvec+28,	yyvstop+245,
yycrank+0,	yysvec+28,	yyvstop+247,
yycrank+0,	yysvec+28,	yyvstop+250,
yycrank+82,	yysvec+28,	yyvstop+253,
yycrank+0,	yysvec+28,	yyvstop+255,
yycrank+0,	yysvec+28,	yyvstop+258,
yycrank+72,	yysvec+28,	yyvstop+261,
yycrank+82,	yysvec+28,	yyvstop+263,
yycrank+0,	yysvec+28,	yyvstop+265,
yycrank+77,	yysvec+28,	yyvstop+268,
yycrank+181,	0,		0,	
yycrank+0,	0,		yyvstop+270,
yycrank+68,	yysvec+28,	yyvstop+272,
yycrank+83,	yysvec+28,	yyvstop+274,
yycrank+0,	yysvec+28,	yyvstop+276,
yycrank+105,	yysvec+28,	yyvstop+279,
yycrank+0,	yysvec+28,	yyvstop+281,
yycrank+0,	yysvec+28,	yyvstop+284,
yycrank+121,	yysvec+28,	yyvstop+287,
yycrank+131,	0,		0,	
yycrank+0,	yysvec+28,	yyvstop+289,
yycrank+0,	yysvec+28,	yyvstop+292,
yycrank+119,	yysvec+28,	yyvstop+295,
yycrank+0,	yysvec+28,	yyvstop+297,
yycrank+205,	0,		0,	
yycrank+128,	yysvec+28,	yyvstop+300,
yycrank+0,	0,		yyvstop+302,
yycrank+130,	yysvec+28,	yyvstop+304,
yycrank+0,	yysvec+28,	yyvstop+306,
0,	0,	0};
struct yywork *yytop = yycrank+481;
struct yysvf *yybgin = yysvec+1;
unsigned char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
'@' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'@' ,'@' ,'@' ,'@' ,'_' ,
01  ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,
'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,
'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,
'a' ,'a' ,'a' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
0};
unsigned char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
*/
/*
#
# IBM CONFIDENTIAL
# Copyright International Business Machines Corp. 1989
# Unpublished Work
# All Rights Reserved
# Licensed Material - Property of IBM
#
#
# US Government Users Restricted Rights - Use, duplication or
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
# 
*/
/* @(#)ncform	1.3  com/lib/l,3.1,8951 9/7/89 18:48:47 */
int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
unsigned char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
unsigned char yysbuf[YYLMAX];
unsigned char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	unsigned char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( yyt > yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if(yyt < yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
