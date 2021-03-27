#include "Functions.h"
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

bool c = 0;
struct node *ptr = NULL;

void Symbole_Suiv()
{
  if (ptr == NULL)
    printf("A");
  else
    // printf("%s ", Cour_Token.value);
    ptr = ptr->next;
  prev_token = Cour_Token;
  Cour_Token = ptr->info;
}

void Test_Symbole(Codes_LEX token)
{

  if (Cour_Token.token == token)
  {

    Symbole_Suiv();
  }
  else if (c == 0)
  {

    // printf("%s\n dans la ligne : %d colonne :%d \n", maperror[token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
  }
}

void PROGRAM()
{
  DECLLIST();
}

void DECLLIST()
{
  DECL();
  DECLLIST1();
}

void DECLLIST1()
{
  switch (Cour_Token.token)
  {
  case INT_TOKEN:
    DECL();
    Symbole_Suiv();
    while (Cour_Token.token == INT_TOKEN || Cour_Token.token == BOOL_TOKEN || Cour_Token.token == CHAR_TOKEN)
    {
      DECLLIST1();
    }
    break;
  case BOOL_TOKEN:
    DECL();
    Symbole_Suiv();
    while (Cour_Token.token == INT_TOKEN || Cour_Token.token == BOOL_TOKEN || Cour_Token.token == CHAR_TOKEN)
    {
      DECLLIST1();
    }
    break;
  case CHAR_TOKEN:
    DECL();
    Symbole_Suiv();
    while (Cour_Token.token == INT_TOKEN || Cour_Token.token == BOOL_TOKEN || Cour_Token.token == CHAR_TOKEN)
    {
      DECLLIST1();
    }
    break;
  case NULL_TOKEN:
    break;
  }
}

void DECL()
{
  TYPE();
  FTYPE();
}

void FTYPE()
{
  switch (Cour_Token.token)
  {
  case ID_TOKEN:
    VARDECLLIST();
    Symbole_Suiv();
    Test_Symbole(PV_TOKEN);
    break;
  case IDFUNC_TOKEN:
    Symbole_Suiv();
    Test_Symbole(PO_TOKEN);
    PARAMS();
    Test_Symbole(PF_TOKEN);
    STMT();
    break;
  }
}

void VARDECLLIST()
{
  VARID();
  VARVALLIST1();
}

void VARDECLLIST1()
{
  switch (Cour_Token.token)
  {
  case VIR_TOKEN:
    VARVAL();
    Symbole_Suiv();
    while (Cour_Token.token == VIR_TOKEN)
    {
      VARVALLIST1();
    }
    break;
  case NULL_TOKEN:
    break;
  }
}

void VARVAL()
{
  VARID();
  VARVALLIST();
}

void VARVALLIST()
{
  switch (Cour_Token.token)
  {
  case AFF_TOKEN:
    SIMPLEEXP();
    break;
  case NULL_TOKEN:
    break;
  }
}

void VARID()
{
  Test_Symbole(ID_TOKEN);
  VARIDEXTRA();
}

void VARIDEXTRA()
{
  switch (Cour_Token.token)
  {
  case CRO_TOKEN: //[
    //Symbole_Suiv();
    Test_Symbole(NUMCONST_TOKEN);
    //Symbole_Suiv();
    Test_Symbole(CRF_TOKEN); //]
    break;
  }
case NULL_TOKEN:
  break;
}

void TYPE()
{
  switch (Cour_Token.token)
  {
  case INT_TOKEN:
    break;
  case BOOL_TOKEN:
    break;
  case CHAR_TOKEN:
    break;
  }
}

/*void FUNDECL()
{
    TYPE();
    Test_Symbole(IDFUNC_TOKEN);
    Test_Symbole(PO_TOKEN); //(
    PARAMS();  
    Test_Symbole(PF_TOKEN); //)
    STMT();                          
}*/

void PARAMS()
{
  switch (Cour_Token.token)
  {
  case (INT_TOKEN):
    PARAMSLIST();
    break;
  case (BOOL_TOKEN):
    PARAMSLIST();
    break;
  case (CHAR_TOKEN):
    PARAMSLIST();
    break;
  case (NULL_TOKEN):
    break;
  }
}

void PARAMSLIST1()
{
  switch (Cour_Token.token)
  {
  case VIR_TOKEN:
    PARAMTYPE();
    while (Cour_Token.token == VIR_TOKEN)
    {
      PARAMSLIST1();
    }
    break;
  case NULL_TOKEN:
    break;
  }
}

void PARAMTYPE()
{
  TYPE();
  PARAMID();
}

void PARAMID()
{
  Test_Symbole(ID_TOKEN);
  EXTRA();
}

void EXTRA()
{
  switch (Cour_Token.token)
  {
  case CRO_TOKEN:
    //Symbole_Suiv();
    Test_Symbole(CRF_TOKEN);
    break;
  case NULL_TOKEN:
    break;
  }
}

void STMT()
{
  switch (Cour_Token.token)
  {
  case COLON_TOKEN:
    EXPSMT();
    break;
  case ACO_TOKEN:
    SCOPESTMT();
    break;
  case IF_TOKEN:
    CONDSTMT();
    break;
  case WHILE_TOKEN:
    ITERSTMT();
    break;
  case RETURN_TOKEN:
    RETURNSTMT();
    break;
  case BREAK_TOKEN:
    BREAKSTMT();
    break;
  case CIN_TOKEN:
    READSTMT();
    break;
  case COUT_TOKEN:
    READSTMT();
    break;
  }
}

void EXPSTMT()
{
  switch (Cour__Token.token)
  {
  case COL_TOKEN:
    EXP();
    Test_Symbole(PV_TOKEN);
    break;
  case NOT_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case PO_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case ID_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case IDFCT_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case NUMCONST_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case CHARCONST_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case STRINGCONST_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case TRUE_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case FALSE_TOKEN:
    ANDEXP();
    SIMPLEEXP1();
    break;
  case PV_TOKEN:
    break;
  }
}

void SCOPESTMT()
{
  Test_Symbole(ACO_TOKEN);
  LOCALDECLS();
  STMTLIST();
  Test_Symbole(ACF_TOKEN);
}

void SCOPEDVARDECL()
{
  Type();
  VARDECLLIST();
  Test_Symbole(PV_TOKEN);
}

void LOCALDECLS()
{
  LOCALDECLS1();
}

void LOCALDECLS1()
{
  switch (Cour_Token.token)
  {
  case INT_TOKEN:
    SCOPEDVARDECL();
    Symbole_Suiv();
    while (Cour_Token.token == INT_TOKEN || Cour_Token.token == BOOL_TOKEN || Cour_Token.token == CHAR_TOKEN)
    {
      LOCALDECLS1();
    }
    break;
  case BOOL_TOKEN:
    SCOPEDVARDECL();
    Symbole_Suiv();
    while (Cour_Token.token == INT_TOKEN || Cour_Token.token == BOOL_TOKEN || Cour_Token.token == CHAR_TOKEN)
    {
      LOCALDECLS1();
    }
    break;
  case CHAR_TOKEN:
    SCOPEDVARDECL();
    Symbole_Suiv();
    while (Cour_Token.token == INT_TOKEN || Cour_Token.token == BOOL_TOKEN || Cour_Token.token == CHAR_TOKEN)
    {
      LOCALDECLS1();
    }
    break;
  case NULL_TOKEN:
    break;
  }
}

void STMTLIST()
{
  STMTLIST1();
}

void STMTLIST1()
{
  switch (Cour_Token.token)
  {
  case PV_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case NOT_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case IF_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case WHILE_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case FOR_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case RETURN_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case BREAK_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case CIN_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case COUT_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case COL_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case ACO_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case PO_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case IDFUNC_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case NUMCONST_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case CHARCONST_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case STRINGCONST_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case TRUE_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case FALSE_TOKEN:
    STMT();
    Symbole_Suiv();
    while (Cour_Token.token == PV_TOKEN || Cour_Token.token == NOT_TOKEN || Cour_Token.token == IF_TOKEN || Cour_Token.token == WHILE_TOKEN || Cour_Token.token == FOR_TOKEN || Cour_Token.token == RETURN_TOKEN || Cour_Token.token == BREAK_TOKEN || Cour_Token.token == CIN_TOKEN || Cour_Token.token == COUT_TOKEN || Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      STMTLIST1();
    }
    break;
  case NULL_TOKEN:
    break;
  }
}

void CONDSTMT()
{
  Test_Symbole(IF_TOKEN);
  FIF();
}

void FIF()
{
  SIMPLEEXP();
  FSIMPLEEXP1();
}

void FSIMPLEEXP1()
{
  switch (Cour_Token.token)
  {
  case LET_TOKEN:
    STMT();
    break;
  case THEN_TOKEN:
    STMT();
    Test_Symbole(ELSE_TOKEN);
    STMT();
    break;
  }
}

void ITERSTMT()
{
  switch (Cour_Token.token)
  {
  case WHILE_TOKEN:
    SIMPLEEXP();
    Test_Symbole(DO_TOKEN);
    STMT();
    break;
  case FOR_TOKEN:
    Test_Symbole(ID_TOKEN);
    Test_Symbole(AFF_TOKEN);
    ITERRANGE();
    Test_Symbole(DO_TOKEN);
    STMT();
    break;
  }
}

void ITERRANGE()
{
  SIMPLEEXP();
  FSIMPLEEXP();
}

void FSIMPLEEXP()
{
  Test_Symbole(TO_TOKEN);
  FTO();
}

void FTO()
{
  SIMPLEEXP();
  FSIMPLEEXP1();
}

void FSIMPLEEXP1()
{
  switch (Cour_Token.token)
  {
  case BY_TOKEN:
    SIMPLEEXP();
    break;
  case NULL_TOKEN:
    break;
  }
}

void RETURNSTMT()
{
  Test_Symbole(RETURN_TOKEN);
  EXPSTMT();
}

void BREAKSTMT()
{
  Test_Symbole(BREAK_TOKEN);
}

void READSTMT()
{
  Test_Symbole(CIN_TOKEN);
  Test_Symbole(PO_TOKEN);
  LISTID();
  Test_Symbole(PF_TOKEN);
  Test_Symbole(PV_TOKEN);
}

void WRITESTMT()
{
  Test_Symbole(COUT_TOKEN);
  Test_Symbole(PO_TOKEN);
  EXP();
  Test_Symbole(PF_TOKEN);
}

void LISTID()
{
  Test_Symbole(ID_TOKEN);
  LISTID1();
}

void LISTID1()
{
  switch (Cour_Token.token)
  {
  case VIR_TOKEN:
    Symbole_Suiv();
    Test_Symbole(ID_TOKEN);
    Symbole_Suiv();
    while (Cour_Token.token == VIR_TOKEN)
    {
      LISTID1();
    }
  case NULL_TOKEN:
    break;
  }
}

void EXP()
{
  switch (Cour_Token.token)
  {
  case COL_TOKEN:
    MUTABLE();
    Test_Symbole(AFF_TOKEN);
    Symbole_Suiv();
    while (Cour_Token.token == COL_TOKEN || Cour_Token.token == ACO_TOKEN || Cour_Token.token == PO_TOKEN || Cour_Token.token == IDFUNC_TOKEN || Cour_Token.token == NUMCONST_TOKEN || Cour_Token.token == CHARCONST_TOKEN || Cour_Token.token == STRINGCONST_TOKEN || Cour_Token.token == TRUE_TOKEN || Cour_Token.token == FALSE_TOKEN)
    {
      EXP();
    }
    break;
  case NOT_TOKEN:
    SIMPLEEXP();
    break;
  case PO_TOKEN:
    SIMPLEEXP();
    break;
  case ID_TOKEN:
    SIMPLEEXP();
    break;
  case IDFUNC_TOKEN:
    SIMPLEEXP();
    break;
  case NUMCONST_TOKEN:
    SIMPLEEXP();
    break;
  case CHARCONST_TOKEN:
    SIMPLEEXP();
    break;
  case STRINGCONST_TOKEN:
    SIMPLEEXP();
    break;
  case TRUE_TOKEN:
    SIMPLEEXP();
    break;
  case FALSE_TOKEN:
    SIMPLEEXP();
    break;
  }
}

void SIMPLEEXP()
{
  ANDEXP();
  SIMPLEEXP1();
}

void SIMPLEEXP1()
{
  switch (Cour_Token.token)
  {
  case OR_TOKEN:
    Symbole_Suiv();
    ANDEXP();
    Symbole_Suiv();
    while (Cour_Token.token == OR_TOKEN)
    {
      SIMPLEEXP1();
    }
  case NULL_TOKEN:
    break;
  }
}

void ANDEXP()
{
  NOTEXP();
  ANDEXP1();
}

void ANDEXP1()
{
  switch (Cour_Token.token)
  {
  case OR_TOKEN:
    Symbole_Suiv();
    NOTEEXP();
    Symbole_Suiv();
    while (Cour_Token.token == AND_TOKEN)
    {
      ANDEXP1();
    }
  case NULL_TOKEN:
    break;
  }
}

void NOTEXP()
{
  switch (Cour_Token.token)
  {
  case NOT_TOKEN:
    Symbole_Suiv();
    while (Cour_Token.token == NOT_TOKEN)
    {
      NOTEXP();
    }
  case PO_TOKEN:
    COMPAREEXP();
    break;

  case IDFUNC_TOKEN:
    COMPAREEXP();
    break;
  case NUMCONST_TOKEN:
    COMPAREEXP();
    break;
  case CHARCONST_TOKEN:
    COMPAREEXP();
    break;
  case STRINGCONST_TOKEN:
    COMPAREEXP();
    break;
  case TRUE_TOKEN:
    COMPAREEXP();
    break;
  case FALSE_TOKEN:
    COMPAREEXP();
    break;
  case ID_TOKEN:
    COMPAREEXP();
    break;
  }
}

void COMPAREXP()
{
  SUMEXP();
  COMPAREXTRA();
}

void COMPAREXTRA()
{
  switch (Cour_Token.token)
  {
  case EG_TOKEN:
    COMPAROP();
    SUMEXP();
    break;
  case INF_TOKEN:
    COMPAROP();
    SUMEXP();
    break;
  case SUP_TOKEN:
    COMPAROP();
    SUMEXP();
    break;
  case INFEG_TOKEN:
    COMPAROP();
    SUMEXP();
    break;
  case SUPEG_TOKEN:
    COMPAROP();
    SUMEXP();
    break;
  case DIFF_TOKEN:
    COMPAROP();
    SUMEXP();
    break;
  case NULL_TOKEN:
    break;
  }
  COMPAROP();
  SUM
}

void COMPAROP()
{
  Test_Symbole(EG_TOKEN);
  Test_Symbole(INF_TOKEN);
  Test_Symbole(SUP_TOKEN);
  Test_Symbole(INFEG_TOKEN);
  Test_Symbole(SUPEG_TOKEN);
  Test_Symbole(DIFF_TOKEN);
}

void SUMEXP()
{
  MULEXP();
  SUMEXP1();
}

void SUMEXP1()
{
  switch (Cour_Token.token)
  {
  case PLUS_TOKEN:
    SUMOP();
    MULEXP();
    Symbole_Suiv();
    while (Cour_Token.token == PLUS_TOKEN || Cour_Token.token == MOINS_TOKEN)
    {
      SUMEXP1();
    }
    break;
  case MOINS_TOKEN:
    SUMOP();
    MULEXP();
    Symbole_Suiv();
    while (Cour_Token.token == PLUS_TOKEN || Cour_Token.token == MOINS_TOKEN)
    {
      SUMEXP1();
    }
    break;
  case NULL_TOKEN:
    break;
  }
}

void SUMOP()
{
  Test_Symbole(PLUS_TOKEN);
  Test_Symbole(MOINS_TOKEN);
}

void MULEXP()
{
  FACTOR();
  MULEXP1();
}

void MULEXP1()
{
  switch (Cour_Token.token)
  {
  case MULT_TOKEN:
    MULOP();
    FACTOR();
    Symbole_Suiv();
    while (Cour_Token.token == MULT_TOKEN || Cour_Token.token == DIV_TOKEN)
    {
      MULEXP1();
    }
    break;
  case DIV_TOKEN:
    MULOP();
    FACTOR();
    Symbole_Suiv();
    while (Cour_Token.token == MULT_TOKEN || Cour_Token.token == DIV_TOKEN)
    {
      MULEXP1();
    }
    break;
  case NULL_TOKEN:
    break;
  }
}

void MULOP()
{
  Test_Symbole(MULT_TOKEN);
  Test_Symbole(DIV_TOKEN);
  Test_Symbole(MOD_TOKEN);
}

void FACTOR()
{
  switch (Cour_Token.token)
  {
  case PO_TOKEN:
    IMMUTABLE();
    break;

  case IDFUNC_TOKEN:
    IMMUTABLE();
    break;
  case NUMCONST_TOKEN:
    IMMUTABLE();
    break;
  case CHARCONST_TOKEN:
    IMMUTABLE();
    break;
  case STRINGCONST_TOKEN:
    IMMUTABLE();
    break;
  case TRUE_TOKEN:
    IMMUTABLE();
    break;
  case FALSE_TOKEN:
    IMMUTABLE();
    break;
  case ID_TOKEN:
    MUTABLE();
    break;
  }
}

void MUTABLE()
{
  Test_Symbole(ID_TOKEN);
  MUTABLEEXTRA();
}

void MUTABLEEXTRA()
{
  Test_Symbole(CRO_TOKEN);
  EXP();
  Test_Symbole(CRF_TOKEN);
}

void IMMUTABLE()
{
  switch (Cour_Token.token)
  {
  case PO_TOKEN:
    EXP();
    Test_Symbole(PF_TOKEN);
    break;

  case IDFUNC_TOKEN:
    CALL();
    break;
  case NUMCONST_TOKEN:
    ARGLIST();
    break;
  case CHARCONST_TOKEN:
    ARGLIST();
    break;
  case STRINGCONST_TOKEN:
    ARGLIST();
    break;
  case TRUE_TOKEN:
    ARGLIST();
    break;
  case FALSE_TOKEN:
    ARGLIST();
    break;
  }
}

void CALL()
{
  Test_Symbole(IDFUNC_TOKEN);
  Test_Symbole(PO_TOKEN);
  ARGS();
  Test_Symbole(PF_TOKEN);
}

void ARGS()
{
  switch (Cour_Token.token)
  {
  case COLON_TOKEN:
    ARGLIST();
    break;
  case NOT_TOKEN:
    ARGLIST();
    break;
  case PO_TOKEN:
    ARGLIST();
    break;

  case IDFUNC_TOKEN:
    ARGLIST();
    break;
  case NUMCONST_TOKEN:
    ARGLIST();
    break;
  case CHARCONST_TOKEN:
    ARGLIST();
    break;
  case STRINGCONST_TOKEN:
    ARGLIST();
    break;
  case TRUE_TOKEN:
    ARGLIST();
    break;
  case FALSE_TOKEN:
    ARGLIST();
    break;
  case NULL_TOKEN:
    break;
  }
}

void ARGLIST()
{
  EXP();
  ARGLIST1();
}

void ARGLIST1()
{
  switch (Cour_Token.token)
  {
  case VIR_TOKEN:
    EXP();
    Symbole_Suiv();
    while (Cour_Token.token == VIR_TOKEN)
    {
      ARGLIST1();
    }
    break;
  case NULL_TOKEN:
    break;
  }
}

void CONSTANT()
{
  Test_Symbole(NUMCONST_TOKEN);
  Test_Symbole(CHARCONST_TOKEN);
  Test_Symbole(STRINGCONST_TOKEN);
  Test_Symbole(TRUE_TOKEN);
  Test_Symbole(FALSE_TOKEN);
}
