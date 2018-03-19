grammar PLDCOMP;

op : '+'    # add
          | '-'   # moins
          | '*'   # mult
          | '/'   # div
          | '%'   # mod
          | '^'   # pow
          | '&'   # and
          | '|'   # or
          | '='   # equal
          | '+='   # addeq
          | '-='   # moinseq
          | '*='   # multeq
          | '/='   # diveq
          | '%='   # modeq
          | '&='   # andeq
          | '|='   # oreq
          | '^='   # xoreq
          | '<'   # infs
          | '<='  # inf
          | '>'   # sups
          | '>='  # sup
          | '<<'  # decg
          | '>>'  # decd
          | '=='  # equalb
          | '!='  # diff
          | '&&'  # andb
          | '||'  # orb
          ;

exp : exp op exp  # operateurBinaire
            | '(' exp ')' # parenthese        
            | '!' exp  # non
            | '-' exp  # negation
            | '~' exp  # invert
            | lvalue '++' # exppp
            | lvalue '--' # expmm
            | '++' lvalue # ppexp
            | '--' lvalue # mmexp
            | lvalue '=' exp # affectation
            | NOMBRE # constanteNombre
            | CHAR # constanteCaractere
            | lvalue # expLvalue
            | NOMVAR '(' exp (',' exp )* ')' # appelDeFonction
            | 'putchar' '(' exp ')' # appelPutchar
            | 'getchar' '(' ')' # appelGetchar
            ;

lvalue : NOMVAR # variable
        | NOMVAR '[' exp ']' # tableau
        ;

structure : if_statement # ifStatement
            | while_statement # whileStatement
            ;

constante : NOMBRE # constanteNb
          | CHAR # constanteCar ;

type_variable : 'char' | 'int32_t' | 'int64_t' ;

type_function : 'char' | 'int32_t' | 'int64_t' | 'void' ; 

if_statement : 'if' '(' exp ')' instruction #if
              | 'if' '(' exp ')' instruction 'else' instruction #ifElse
              ;

while_statement : 'while' '(' exp ')' instruction # while ;

val : NOMBRE ( ',' NOMBRE)* # tableauNombre
    | CHAR ( ',' CHAR)* # tableauCaractere ;

declaration_type : type_variable NOMVAR '=' constante # declarationConstante
                  | type_variable NOMVAR # declaration
                  | type_variable NOMVAR '[' NOMBRE ']' # declarationTableau
                  | type_variable NOMVAR '[' NOMBRE ']' '=' '{' val '}' # declarationTableauConstante
                  ;

param : 'void' # void
        | type_variable NOMVAR (',' type_variable NOMVAR)* # parametres
        ;

fonction : type_function NOMVAR '(' param ')' '{'declaration_variables bloc '}' # declarationFonctionParams
           | type_function NOMVAR '(' ')' '{' declaration_variables bloc '}' # declarationFonction ;

declaration_variables : ( declaration_type ';' )* # declarationVariables ;

bloc : instruction* ;

instruction :  '{' bloc '}' # blocInstruction
               | 'break' ';' # breakInstruction
               | structure # structureInstruction
               | 'return' exp ';' # returnInstruction
               | exp ';' # expInstruction
               ;

programme : declaration_variables fonction* ;

NOMVAR : [a-zA-Z][a-zA-Z0-9]* ;
NOMBRE : [0-9]+ ;
CHAR : '\''.'\'' ;
COMMENT: '/*' . *? '*/'-> skip ;
WS : [ \t\r\n]+ -> skip ;
INCLUDE : '#' ~[\r\n]* -> skip;









