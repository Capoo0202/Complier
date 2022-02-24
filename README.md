Final_Project for Mini Lisp
========

開發環境:

DevC++

token:

separator ::= ‘\t’(tab) | ‘\n’ | ‘\r’ | ‘ ’(space) | '(' | ')'
letter ::= [a-z]
digit ::= [0-9]
number ::= 0 | [1-9]digit* | -[1-9]digit*
ID ::= letter (letter | digit | ‘-’)*
bool-val ::= #t | #f

文法:

PROGRAM ::= STMT+

STMT ::= EXP | DEF-STMT | PRINT-STMT

PRINT-STMT ::= (print-num EXP) | (print-bool EXP)

EXP ::= bool-val | number | VARIABLE | NUM-OP | LOGICAL-OP
| FUN-EXP | FUN-CALL | IF-EXP

NUM-OP ::= PLUS | MINUS | MULTIPLY | DIVIDE | MODULUS | GREATER
| SMALLER | EQUAL

PLUS ::= (+ EXP EXP+)
MINUS ::= (- EXP EXP)
MULTIPLY ::= (* EXP EXP+)
DIVIDE ::= (/ EXP EXP)
MODULUS ::= (mod EXP EXP)
GREATER ::= (> EXP EXP)
SMALLER ::= (< EXP EXP)
EQUAL ::= (= EXP EXP+)

LOGICAL-OP ::= AND-OP | OR-OP | NOT-OP

AND-OP ::= (and EXP EXP+)
OR-OP ::= (or EXP EXP+)
NOT-OP ::= (not EXP)

DEF-STMT ::= (define VARIABLE EXP)

VARIABLE ::= id

FUN-EXP ::= (fun FUN_IDs FUN-BODY)

FUN-IDs ::= (id*)
FUN-BODY ::= EXP

FUN-CALL ::= (FUN-EXP PARAM*) | (FUN-NAME PARAM*)

PARAM ::= EXP
LAST-EXP ::= EXP
FUN-NAME ::= id

IF-EXP ::= (if TEST-EXP THAN-EXP ELSE-EXP)

TEST-EXP ::= EXP
THEN-EXP ::= EXP
ELSE-EXP ::= EXP

輸出範例:

syntax error:

(+) => syntax error

PLUS:

(+ 1 2) => 3

Minus:

(- 12 3) => 9

MUL:

(* 2 5 3) => 30

DIV:

(/ 6 2) => 3

MOD:

(mod 5 2) => 1

Greater:

(> 3 5) => #f

Smaller:

(< 2 6) => #t

Equal:

(= 5 5) => #t

And:

(and #t #f) => #f

Or:

(or #f #t) => #t

Not:

(not #f) => #t

Print-Num:

(print-num (+ 1 2)) => 3

Print-Bool:

(print-bool #t) => #t

If:

(if #t 1 2) => 1

Define:

(define x 1) => x = 1