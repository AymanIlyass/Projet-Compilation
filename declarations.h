#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define SIZE 10007
// typedef enum
// {
//     ARRAY,
//     STRING,
//     RECORD
// } np_type;
typedef enum
{
    ERROR,
    NUM,
    ID,
    ID_FUNCTION,
    SPECIAL,
    STRING,
    CHAR

} enus;
typedef enum
{
    // SPECIAL
    CRO_TOKEN,   // [
    CRF_TOKEN,   // ]
    ACO_TOKEN,   // {
    ACF_TOKEN,   // }
    COLON_TOKEN, // :
    NOT_TOKEN,   // !
    AFF_TOKEN,   // =
    MOD_TOKEN,   // %
    PV_TOKEN,    // ;
    PLUS_TOKEN,  // +
    MOINS_TOKEN, // -
    MULT_TOKEN,  // *
    DIV_TOKEN,   // /
    VIR_TOKEN,   // ,
    EG_TOKEN,    // ==
    INF_TOKEN,   // <
    INFEG_TOKEN, // <=
    SUP_TOKEN,   // >
    SUPEG_TOKEN, // >=
    DIFF_TOKEN,  // !=
    PO_TOKEN,    // (
    PF_TOKEN,    // )
    // KEYWORD
    NUMCONST_TOKEN,    // numconst
    CHARCONST_TOKEN,   // charconstant
    STRINGCONST_TOKEN, // stringconstant
    TRUE_TOKEN,        // true
    FALSE_TOKEN,       // false
    IDFCT_TOKEN,       // idfunc
    INT_TOKEN,         // int
    BOOL_TOKEN,        // bool
    CHAR_TOKEN,        // char
    LET_TOKEN,         // let
    ELSE_TOKEN,        // else
    FOR_TOKEN,         // for
    TO_TOKEN,          // to
    BY_TOKEN,          // by
    RETURN_TOKEN,      // return
    BREAK_TOKEN,       // break
    CIN_TOKEN,         // cin
    COUT_TOKEN,        // cout
    OR_TOKEN,          // or
    AND_TOKEN,         // and
    IF_TOKEN,          // if
    THEN_TOKEN,        // then
    WHILE_TOKEN,       // while
    DO_TOKEN,          // do
    ID_TOKEN,          // id
    FIN_TOKEN,
    ERREUR_TOKEN,
    NULL_TOKEN
} Codes_LEX;
typedef enum
{
    // SPECIAL
    CRO_TOKEN_ERREUR,   // [
    CRF_TOKEN_ERREUR,   // ]
    ACO_TOKEN_ERREUR,   // {
    ACF_TOKEN_ERREUR,   // }
    COLON_TOKEN_ERREUR, // :
    NOT_TOKEN_ERREUR,   // !
    AFF_TOKEN_ERREUR,   // =
    MOD_TOKEN_ERREUR,   // %
    PV_TOKEN_ERREUR,    // ;
    PLUS_TOKEN_ERREUR,  // +
    MOINS_TOKEN_ERREUR, // -
    MULT_TOKEN_ERREUR,  // *
    DIV_TOKEN_ERREUR,   // /
    VIR_TOKEN_ERREUR,   // ,
    EG_TOKEN_ERREUR,    // ==
    INF_TOKEN_ERREUR,   // <
    INFEG_TOKEN_ERREUR, // <=
    SUP_TOKEN_ERREUR,   // >
    SUPEG_TOKEN_ERREUR, // >=
    DIFF_TOKEN_ERREUR,  // !=
    PO_TOKEN_ERREUR,    // (
    PF_TOKEN_ERREUR,    // )
    // KEYWORD
    NUMCONST_TOKEN_ERREUR,    // numconst
    CHARCONST_TOKEN_ERREUR,   // charconstant
    STRINGCONST_TOKEN_ERREUR, // stringconstant
    TRUE_TOKEN_ERREUR,        // true
    FALSE_TOKEN_ERREUR,       // false
    IDFCT_TOKEN_ERREUR,       // idfunc
    INT_TOKEN_ERREUR,         // int
    BOOL_TOKEN_ERREUR,        // bool
    CHAR_TOKEN_ERREUR,        // char
    LET_TOKEN_ERREUR,         // let
    ELSE_TOKEN_ERREUR,        // else
    FOR_TOKEN_ERREUR,         // for
    TO_TOKEN_ERREUR,          // to
    BY_TOKEN_ERREUR,          // by
    RETURN_TOKEN_ERREUR,      // return
    BREAK_TOKEN_ERREUR,       // break
    CIN_TOKEN_ERREUR,         // cin (read)
    COUT_TOKEN_ERREUR,        // cout (write)
    OR_TOKEN_ERREUR,          // or
    AND_TOKEN_ERREUR,         // and
    IF_TOKEN_ERREUR,          // if
    THEN_TOKEN_ERREUR,        // then
    WHILE_TOKEN_ERREUR,       // while
    DO_TOKEN_ERREUR,          // do
    ID_TOKEN_ERREUR,          // id
    VIR_PV_ERREUR,
    AFF_VIR_PV_ERREUR,
    AFF_VIR_PV_CRO_ERREUR,
    INT_PF_ERREUR,
    VIR_PF_ERREUR,
    CRO_VIR_PF_ERREUR,
    STMT_ERREUR,
    EXPSTMT_ERREUR,
    LOCALDECLS1_ERREUR,
    STMTLIST1_ERREUR,
    ITERSTMT_ERREUR,
    FSIMPLEEXP1_ERREUR,
    EXP_ERREUR,
    SIMPLEEXP1_ERREUR,
    ANDEXP1_ERREUR,
    NOTEXP_ERREUR,
    COMPAREXTRA_ERREUR,
    SUMEXP1_ERREUR,
    MULEXP1_ERREUR,
    FACTOR_ERREUR,
    MUTABLEEXTRA_ERREUR,
    IMMUTABLE_ERREUR,
    ARGS_ERREUR,
    CONSTANT_ERREUR,
    FIN_TOKEN_ERREUR,
} Codes_LEX_Erreurs;
typedef struct
{
    Codes_LEX token;
    char identif[31];
    char value[31];
    int ligne;
    int colonne;
} Maptoken;

//--------
typedef struct
{
    Codes_LEX token;
    char message_erreur[100];

} Maptoken_erreur;

//-----
typedef enum
{
    CAR_INC,
    FICH_VID,
    ID_LONG,
    NUM_LONG,
    MORE_THEN_CHAR
} Erreurlyx;
//------
typedef struct
{
    Erreurlyx code_err;
    char message_erreur[50];
    int ligneErreur;
    int colonneErreur;
} Erreurs;
//-------------------------------------
Erreurs mes_err[5] = {{CAR_INC, "caractère inconnu"},
                      {FICH_VID, "fichier vide"},
                      {ID_LONG, "l'identifiant est long"},
                      {NUM_LONG, "le nombre est grand"},
                      {MORE_THEN_CHAR, "le type char ne peut avoir plus d'un caractère"}};
//--------
Erreurs Error_table[SIZE];
int curseur = 0;
//------
Maptoken specials[23] = {
    {CRO_TOKEN, "CRO_TOKEN"},
    {CRF_TOKEN, "CRF_TOKEN"},
    {ACO_TOKEN, "ACO_TOKEN"},
    {ACF_TOKEN, "ACF_TOKEN"},
    {COLON_TOKEN, "COLON_TOKEN"},
    {NOT_TOKEN, "NOT_TOKEN"},
    {AFF_TOKEN, "AFF_TOKEN"},
    {MOD_TOKEN, "MOD_TOKEN"},
    {PV_TOKEN, "PV_TOKEN"},
    {PLUS_TOKEN, "PLUS_TOKEN"},
    {MOINS_TOKEN, "MOINS_TOKEN"},
    {MULT_TOKEN, "MULT_TOKEN"},
    {DIV_TOKEN, "DIV_TOKEN"},
    {VIR_TOKEN, "VIR_TOKEN"},
    {EG_TOKEN, "EG_TOKEN"},
    {INF_TOKEN, "INF_TOKEN"},
    {INFEG_TOKEN, "INFEG_TOKEN"},
    {SUP_TOKEN, "SUP_TOKEN"},
    {SUPEG_TOKEN, "SUPEG_TOKEN"},
    {DIFF_TOKEN, "DIFF_TOKEN"},
    {PO_TOKEN, "PO_TOKEN"},
    {PF_TOKEN, "PF_TOKEN"},
    {FIN_TOKEN, "FIN_TOKEN"},
};

Maptoken key_words[24] = {
    {NUMCONST_TOKEN, "NUMCONST", ""},
    {CHARCONST_TOKEN, "CHARCONST", ""},
    {STRINGCONST_TOKEN, "STRINGCONST", ""},
    {TRUE_TOKEN, "TRUE", ""},
    {FALSE_TOKEN, "FALSE", ""},
    {IDFCT_TOKEN, "IDFCT", ""},
    {INT_TOKEN, "INT", ""},
    {BOOL_TOKEN, "BOOL", ""},
    {CHAR_TOKEN, "CHAR", ""},
    {LET_TOKEN, "LET", ""},
    {ELSE_TOKEN, "ELSE", ""},
    {FOR_TOKEN, "FOR", ""},
    {TO_TOKEN, "TO", ""},
    {BY_TOKEN, "BY", ""},
    {RETURN_TOKEN, "RETURN", ""},
    {BREAK_TOKEN, "BREAK", ""},
    {CIN_TOKEN, "CIN", ""},
    {COUT_TOKEN, "COUT", ""},
    {OR_TOKEN, "OR", ""},
    {AND_TOKEN, "AND", ""},
    {IF_TOKEN, "IF", ""},
    {THEN_TOKEN, "THEN", ""},
    {WHILE_TOKEN, "WHILE", ""},
    {DO_TOKEN, "DO", ""},
};

Maptoken_erreur maperror[100] = {
    {CRO_TOKEN_ERREUR, " un '['est  manquant"},   // [
    {CRF_TOKEN_ERREUR, " un ']'est  manquant"},   // ]
    {ACO_TOKEN_ERREUR, " un '{'est  manquant"},   // {
    {ACF_TOKEN_ERREUR, " un '}'est  manquant"},   // },
    {COLON_TOKEN_ERREUR, " un ':'est  manquant"}, // :
    {NOT_TOKEN_ERREUR, " un '!'est  manquant"},   // !
    {AFF_TOKEN_ERREUR, " un '='est  manquant"},   // =
    {MOD_TOKEN_ERREUR, " un '%'est  manquant"},   // %
    {PV_TOKEN_ERREUR, " un ';'est  manquant"},
    {PLUS_TOKEN_ERREUR, "une operation mathematique ne peut etre effectuer sans operateur"},
    {MOINS_TOKEN_ERREUR, "une operation mathematique ne peut etre effectuer sans operateur"},
    {MULT_TOKEN_ERREUR, "une operation mathematique ne peut etre effectuer sans operateur"},
    {DIV_TOKEN_ERREUR, "une operation mathematique ne peut etre effectuer sans operateur"},
    {VIR_TOKEN_ERREUR, " un ','est  manquant"}, // ,""},
    {EG_TOKEN_ERREUR, " un '='est  manquant"},
    {INF_TOKEN_ERREUR, "une operation  booleenne ne peut etre effectuer sans operateur"},
    {INFEG_TOKEN_ERREUR, "une operation  booleenne ne peut etre effectuer sans operateur"},
    {SUP_TOKEN_ERREUR, "une operation  booleenne ne peut etre effectuer sans operateur"},
    {SUPEG_TOKEN_ERREUR, "une operation  booleenne ne peut etre effectuer sans operateur"},
    {DIFF_TOKEN_ERREUR, "une operation  booleenne ne peut etre effectuer sans operateur"},
    {PO_TOKEN_ERREUR, " un '('est  manquant"},
    {PF_TOKEN_ERREUR, " un ')'est  manquant"},
    {NUMCONST_TOKEN_ERREUR, " un entier est manquant"},                      // numconst
    {CHARCONST_TOKEN_ERREUR, "un caractere est manquant"},                   // charconstant
    {STRINGCONST_TOKEN_ERREUR, "une chaine de caractere est manquante"},     // stringconstant
    {TRUE_TOKEN_ERREUR, "un true or false est manquant"},                    // true
    {FALSE_TOKEN_ERREUR, "un true or false est manquant"},                   // false
    {IDFCT_TOKEN_ERREUR, " un identifiant est manquant"},                    // idfunc
    {INT_TOKEN_ERREUR, "le type (int |bool | char ...) n'est pas precise"},  // int
    {BOOL_TOKEN_ERREUR, "le type (int |bool | char ...) n'est pas precise"}, // bool
    {CHAR_TOKEN_ERREUR, "le type (int |bool | char ...) n'est pas precise"}, // char
    {LET_TOKEN_ERREUR, "un 'let ' est manquant "},                           // let
    {ELSE_TOKEN_ERREUR, " un 'else ' est manquant"},                         // else
    {FOR_TOKEN_ERREUR, " un 'for' est manquant"},                            // for
    {TO_TOKEN_ERREUR, "un 'to' est manquant "},                              // to
    {BY_TOKEN_ERREUR, "un 'by' est manquant"},                               // by
    {RETURN_TOKEN_ERREUR, " un return est manquant"},                        // return
    {BREAK_TOKEN_ERREUR, "un break est manquant"},                           // break
    {CIN_TOKEN_ERREUR, " erreur de lecture "},
    {COUT_TOKEN_ERREUR, " erreur d'ecreture"},                                             // cout (write)
    {OR_TOKEN_ERREUR, "une operation  booleenne ne peut etre effectuer sans operateur  "}, // or
    {AND_TOKEN_ERREUR, "une operation  booleenne ne peut etre effectuer sans operateur"},  // and
    {IF_TOKEN_ERREUR, " un 'IF'est  manquant"},                                            // if
    {THEN_TOKEN_ERREUR, " un 'THEN'est  manquant"},                                        // then
    {WHILE_TOKEN_ERREUR, " un 'WHILE'est  manquant"},                                      // while
    {DO_TOKEN_ERREUR, " un 'DO'est  manquant"},
    {ID_TOKEN_ERREUR, " un identifiant est manquant"}, // do
    {VIR_PV_ERREUR, " ',' or ';' expected"},
    {AFF_VIR_PV_ERREUR, " '=' or ',' or ';' expected "},
    {AFF_VIR_PV_CRO_ERREUR, " '=' or ',' or ';' or '[' expected "},
    {INT_PF_ERREUR, " prototype or ')' expected "},
    {VIR_PF_ERREUR, " ',' or ')' expected"},
    {CRO_VIR_PF_ERREUR, " '[' or ',' or ')' expected"},
    {STMT_ERREUR, " the beging of the the statement is invalid "},
    {EXPSTMT_ERREUR, " Expr or ';' expected "},
    {LOCALDECLS1_ERREUR, " prototype or Statement expected "},
    {STMTLIST1_ERREUR, " '}' or statement expected"},
    {ITERSTMT_ERREUR, " Iteration Statement expected"},
    {FSIMPLEEXP1_ERREUR, " then or let or by or Expr expected"},
    {EXP_ERREUR, " ':' or Expr expected "},
    {SIMPLEEXP1_ERREUR, " ' or ' or Statement expected"},
    {ANDEXP1_ERREUR, " ' AND ' or Statement expected"},
    {NOTEXP_ERREUR, " '!' or ComparaisonExpr expected "},
    {COMPAREXTRA_ERREUR, " ComparOperator or Statement expected "},
    {SUMEXP1_ERREUR, " SumOperator or Statement expected "},
    {MULEXP1_ERREUR, "MulOperator or Statement expected "},
    {FACTOR_ERREUR, "Factor expected"},
    {MUTABLEEXTRA_ERREUR, " '[' or Expr expected"},
    {IMMUTABLE_ERREUR, " '(' or Function call or Value expected  "},
    {ARGS_ERREUR, "Arguments or ')'  expected"},
    {CONSTANT_ERREUR, " Value expected "},
};

//nombre total des token
int nbTokens = 0, ligne = 1, colonne = 1, indx;
//caractere courant
char cour_char;
// notre fichier a complier
FILE *file;
//courant token
Maptoken Cour_Token, Cour_symbole, prev_token, prev_Erreur;
//linked list(tokens table)
typedef struct node
{
    Maptoken info;
    struct node *next;
} node;
//the head of the linked list
node *head = NULL;

//-----
struct DataItem
{
    Maptoken data;
    int key;
    bool isset;
};
struct DataItem *hashArray[SIZE];
struct DataItem *dummyItem;
struct DataItem *item;
//functions
void read_char();
void read_string();
void read_number();
void read_symbole();
void tokenmap(int a);
void push();
void Analex();
void commentignore();
void display();
//____________
//partie syntaxique
//---------------------

void PROGRAM();
void DECLLIST();
void DECLLIST1();
void DECL();
void FTYPE();
//void VARDECL();
void VARDECLLIST();
void VARDECLLIST1();
void VARVAL();
void VARVALLIST();
void VARID();
void VARIDEXTRA();
void TYPE();
//void FUNDECL();
void PARAMS();
void PARAMSLIST();
void PARAMSLIST1();
void PARAMTYPE();
void PARAMID();
void EXTRA();
void STMT();
void EXPSTMT();
void SCOPESTMT();
void SCOPEDVARDECL();
void LOCALDECLS();
void LOCALDECLS1();
void STMTLIST();
void STMTLIST1();
void CONDSTMT();
void FIF();
void FSIMPLEEXP1();
void ITERSTMT();
void ITERRANGE();
void FSIMPLEEXP();
void FTO();
void FSIMPLEEXP1();
void RETURNSTMT();
void BREAKSTMT();
void READSTMT();
void WRITESTMT();
void LISTID();
void LISTID1();
void EXP();
void SIMPLEEXP();
void SIMPLEEXP1();
void ANDEXP();
void ANDEXP1();
void NOTEXP();
void COMPAREXP();
void COMPAREXTRA();
void COMPAROP();
void SUMEXP();
void SUMEXP1();
void SUMOP();
void MULEXP();
void MULEXP1();
void MULOP();
void FACTOR();
void MUTABLE();
void MUTABLEEXTRA();
void IMMUTABLE();
void CALL();
void ARGS();
void ARGLIST();
void ARGLIST1();
void CONSTANT();