#include "Functions.h"

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

        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
    DECL();
    DECLLIST1();
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
        Test_Symbole(PV_TOKEN);
        break;
    case IDFCT_TOKEN:
        Symbole_Suiv();
        Test_Symbole(PO_TOKEN);
        PARAMS();
        Test_Symbole(PF_TOKEN);
        STMT();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[ID_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;    
    }
}
void VARDECLLIST()
{
    VARVAL();
    VARDECLLIST1();
}

void VARDECLLIST1()
{
    switch (Cour_Token.token)
    {
    case VIR_TOKEN:
        VARVAL();
        Symbole_Suiv();
        VARDECLLIST1();
        break;
    case PV_TOKEN:
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[VIR_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case VIR_TOKEN:
        // VARVAL();
        // Symbole_Suiv();
        // VARDECLLIST1();
        break;
    case PV_TOKEN:
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[AFF_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
        Symbole_Suiv();
        Test_Symbole(NUMCONST_TOKEN);
        //Symbole_Suiv();
        Test_Symbole(CRF_TOKEN); //]
        break;
    case PV_TOKEN: //1
    case AFF_TOKEN:
    case VIR_TOKEN:
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[CRO_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}

void TYPE()
{
    switch (Cour_Token.token)
    {
    case INT_TOKEN:
        Symbole_Suiv();
        break;
    case BOOL_TOKEN:
        Symbole_Suiv();
        break;
    case CHAR_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[INT_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}

void PARAMS()
{
    switch (Cour_Token.token)
    {
    case (INT_TOKEN):
    case (BOOL_TOKEN):
    case (CHAR_TOKEN):
        PARAMSLIST();
        break;
    case (PF_TOKEN):
        Symbole_Suiv();
        STMT();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[INT_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}

void PARAMSLIST()
{
    PARAMTYPE();
    PARAMSLIST1();
}

void PARAMSLIST1()
{
    switch (Cour_Token.token)
    {
    case (VIR_TOKEN):
        Symbole_Suiv();
        PARAMTYPE();
        PARAMSLIST1();
        break;
    case (PO_TOKEN):
        Symbole_Suiv();
        STMT();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[VIR_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
        Symbole_Suiv();
        Test_Symbole(CRF_TOKEN);
        break;
    case VIR_TOKEN:
        Symbole_Suiv();
        PARAMTYPE();
        PARAMSLIST1();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[CRO_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}

void STMT()
{
    switch (Cour_Token.token)
    {
    case COLON_TOKEN:
        EXPSTMT();
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
    case FOR_TOKEN:
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
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}

void EXPSTMT()
{
    switch (Cour_Token.token)
    {
    case COLON_TOKEN:
        EXP();
        Test_Symbole(PV_TOKEN);
        break;
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[COLON_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
        LOCALDECLS1();
        break;
    case BOOL_TOKEN:
        SCOPEDVARDECL();
        LOCALDECLS1();
        break;
    case CHAR_TOKEN:
        SCOPEDVARDECL();
        LOCALDECLS1();
        break;
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    case IF_TOKEN:
        CONDSTMT();
        break;
    case WHILE_TOKEN:
        ITERSTMT();
        break;
    case FOR_TOKEN:
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
        WRITESTMT();
        break;
    case COLON_TOKEN:
        EXP();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case PO_TOKEN:
        EXPSTMT();
        break;
    case ACO_TOKEN:
        SCOPESTMT();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //
        break;
    case ID_TOKEN:
        EXPSTMT();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}

void SCOPEDVARDECL()
{
    TYPE();
    VARDECLLIST();
    Test_Symbole(PV_TOKEN);
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
    case IF_TOKEN:
    case WHILE_TOKEN:
    case FOR_TOKEN:
    case RETURN_TOKEN:
    case BREAK_TOKEN:
    case CIN_TOKEN:
    case COUT_TOKEN:
    case COLON_TOKEN:
    case NOT_TOKEN:
    case PO_TOKEN:
    case ACO_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        STMT();
        STMTLIST1();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //}
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
void ITERSTMT()
{
    switch (Cour_Token.token)
    {
    case WHILE_TOKEN:
        Symbole_Suiv();
        SIMPLEEXP();
        Test_Symbole(DO_TOKEN);
        STMT();
        break;
    case FOR_TOKEN:
        Symbole_Suiv();
        Test_Symbole(ID_TOKEN);
        Test_Symbole(AFF_TOKEN);
        ITERRANGE();
        Test_Symbole(DO_TOKEN);
        STMT();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[WHILE_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case LET_TOKEN:
        Symbole_Suiv();
        STMT();
        break;
    case THEN_TOKEN:
        Symbole_Suiv();
        STMT();
        Test_Symbole(ELSE_TOKEN);
        STMT();
        break;
    case DO_TOKEN:
        Symbole_Suiv();
        STMT();
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    case IF_TOKEN:
        CONDSTMT();
        break;
    case WHILE_TOKEN:
        ITERSTMT();
        break;
    case FOR_TOKEN:
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
        WRITESTMT();
        break;
    case COLON_TOKEN:
        EXP();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case PO_TOKEN:
        EXPSTMT();
        break;
    case ACO_TOKEN:
        SCOPESTMT();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //
        break;
    case ID_TOKEN:
        EXPSTMT();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case NULL_TOKEN:
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);


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
    Test_Symbole(PV_TOKEN);
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
    Test_Symbole(PV_TOKEN);
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
        LISTID1();
    case PF_TOKEN:
        Symbole_Suiv();
        Test_Symbole(PV_TOKEN);
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[VIR_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void EXP()
{
    switch (Cour_Token.token)
    {
    case COLON_TOKEN:
        MUTABLE();
        Test_Symbole(AFF_TOKEN);
        Symbole_Suiv();
        EXP();
        break;
    case NOT_TOKEN:
    case PO_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        SIMPLEEXP();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[COLON_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
        SIMPLEEXP1();
    case BY_TOKEN:
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case LET_TOKEN:
        Symbole_Suiv();
        STMT();
        break;
    case THEN_TOKEN:
        Symbole_Suiv();
        STMT();
        Test_Symbole(ELSE_TOKEN);
        STMT();
        break;
    case DO_TOKEN:
        Symbole_Suiv();
        STMT();
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    case IF_TOKEN:
        CONDSTMT();
        break;
    case WHILE_TOKEN:
        ITERSTMT();
        break;
    case FOR_TOKEN:
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
        WRITESTMT();
        break;
    case COLON_TOKEN:
        EXP();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case PO_TOKEN:
        EXPSTMT();
        break;
    case ACO_TOKEN:
        SCOPESTMT();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //
        break;
    case ID_TOKEN:
        EXPSTMT();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case TO_TOKEN:
        Symbole_Suiv();
        FTO();
        break;
    case PF_TOKEN:
        Symbole_Suiv();
        break;
    case CRF_TOKEN:
        Symbole_Suiv();
        break;
    case VIR_TOKEN:
        Symbole_Suiv();
        EXP();
        ARGLIST1();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
    case AND_TOKEN:
        Symbole_Suiv();
        NOTEXP();
        ANDEXP1();
        break;
    case OR_TOKEN:
        Symbole_Suiv();
        ANDEXP();
        Symbole_Suiv();
        SIMPLEEXP1();
    case BY_TOKEN:
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case LET_TOKEN:
        Symbole_Suiv();
        STMT();
        break;
    case THEN_TOKEN:
        Symbole_Suiv();
        STMT();
        Test_Symbole(ELSE_TOKEN);
        STMT();
        break;
    case DO_TOKEN:
        Symbole_Suiv();
        STMT();
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    case IF_TOKEN:
        CONDSTMT();
        break;
    case WHILE_TOKEN:
        ITERSTMT();
        break;
    case FOR_TOKEN:
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
        WRITESTMT();
        break;
    case COLON_TOKEN:
        EXP();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case PO_TOKEN:
        EXPSTMT();
        break;
    case ACO_TOKEN:
        SCOPESTMT();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //
        break;
    case ID_TOKEN:
        EXPSTMT();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case TO_TOKEN:
        Symbole_Suiv();
        FTO();
        break;
    case PF_TOKEN:
        Symbole_Suiv();
        break;
    case CRF_TOKEN:
        Symbole_Suiv();
        break;
    case VIR_TOKEN:
        Symbole_Suiv();
        EXP();
        ARGLIST1();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void NOTEXP()
{
    switch (Cour_Token.token)
    {
    case NOT_TOKEN:
        Symbole_Suiv();
        NOTEXP();
        break;
    case PO_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
    case ID_TOKEN:
        COMPAREXP();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);        
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
    case DIFF_TOKEN:
    case EG_TOKEN:
    case SUP_TOKEN:
    case SUPEG_TOKEN:
    case INF_TOKEN:
    case INFEG_TOKEN:
        COMPAROP();
        SUMEXP();
        break;
    case AND_TOKEN:
        Symbole_Suiv();
        NOTEXP();
        ANDEXP1();
        break;
    case OR_TOKEN:
        Symbole_Suiv();
        ANDEXP();
        Symbole_Suiv();
        SIMPLEEXP1();
    case BY_TOKEN:
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case LET_TOKEN:
        Symbole_Suiv();
        STMT();
        break;
    case THEN_TOKEN:
        Symbole_Suiv();
        STMT();
        Test_Symbole(ELSE_TOKEN);
        STMT();
        break;
    case DO_TOKEN:
        Symbole_Suiv();
        STMT();
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    case IF_TOKEN:
        CONDSTMT();
        break;
    case WHILE_TOKEN:
        ITERSTMT();
        break;
    case FOR_TOKEN:
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
        WRITESTMT();
        break;
    case COLON_TOKEN:
        EXP();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case PO_TOKEN:
        EXPSTMT();
        break;
    case ACO_TOKEN:
        SCOPESTMT();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //
        break;
    case ID_TOKEN:
        EXPSTMT();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case TO_TOKEN:
        Symbole_Suiv();
        FTO();
        break;
    case PF_TOKEN:
        Symbole_Suiv();
        break;
    case CRF_TOKEN:
        Symbole_Suiv();
        break;
    case VIR_TOKEN:
        Symbole_Suiv();
        EXP();
        ARGLIST1();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void COMPAROP()
{
    switch (Cour_Token.token)
    {
    case DIFF_TOKEN:
    case EG_TOKEN:
    case SUP_TOKEN:
    case SUPEG_TOKEN:
    case INF_TOKEN:
    case INFEG_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
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
    case MOINS_TOKEN:
        SUMOP();
        MULEXP();
        SUMEXP1();
        break;
    case DIFF_TOKEN:
    case EG_TOKEN:
    case SUP_TOKEN:
    case SUPEG_TOKEN:
    case INF_TOKEN:
    case INFEG_TOKEN:
        COMPAROP();
        SUMEXP();
        break;
    case AND_TOKEN:
        Symbole_Suiv();
        NOTEXP();
        ANDEXP1();
        break;
    case OR_TOKEN:
        Symbole_Suiv();
        ANDEXP();
        Symbole_Suiv();
        SIMPLEEXP1();
    case BY_TOKEN:
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case LET_TOKEN:
        Symbole_Suiv();
        STMT();
        break;
    case THEN_TOKEN:
        Symbole_Suiv();
        STMT();
        Test_Symbole(ELSE_TOKEN);
        STMT();
        break;
    case DO_TOKEN:
        Symbole_Suiv();
        STMT();
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    case IF_TOKEN:
        CONDSTMT();
        break;
    case WHILE_TOKEN:
        ITERSTMT();
        break;
    case FOR_TOKEN:
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
        WRITESTMT();
        break;
    case COLON_TOKEN:
        EXP();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case PO_TOKEN:
        EXPSTMT();
        break;
    case ACO_TOKEN:
        SCOPESTMT();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //
        break;
    case ID_TOKEN:
        EXPSTMT();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case TO_TOKEN:
        Symbole_Suiv();
        FTO();
        break;
    case PF_TOKEN:
        Symbole_Suiv();
        break;
    case CRF_TOKEN:
        Symbole_Suiv();
        break;
    case VIR_TOKEN:
        Symbole_Suiv();
        EXP();
        ARGLIST1();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void SUMOP()
{
    switch (Cour_Token.token)
    {
    case PLUS_TOKEN:
    case MOINS_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
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
    case DIV_TOKEN:
    case MOD_TOKEN:
        MULOP();
        FACTOR();
        MULEXP1();
        break;
    case PLUS_TOKEN:
    case MOINS_TOKEN:
        Symbole_Suiv();
        SUMOP();
        break;
    case DIFF_TOKEN:
    case EG_TOKEN:
    case SUP_TOKEN:
    case SUPEG_TOKEN:
    case INF_TOKEN:
    case INFEG_TOKEN:
        Symbole_Suiv();
        COMPAROP();
        SUMEXP();
        break;
    case AND_TOKEN:
        Symbole_Suiv();
        NOTEXP();
        ANDEXP1();
        break;
    case OR_TOKEN:
        Symbole_Suiv();
        ANDEXP();
        Symbole_Suiv();
        SIMPLEEXP1();
    case BY_TOKEN:
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case LET_TOKEN:
        Symbole_Suiv();
        STMT();
        break;
    case THEN_TOKEN:
        Symbole_Suiv();
        STMT();
        Test_Symbole(ELSE_TOKEN);
        STMT();
        break;
    case DO_TOKEN:
        Symbole_Suiv();
        STMT();
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    case IF_TOKEN:
        CONDSTMT();
        break;
    case WHILE_TOKEN:
        ITERSTMT();
        break;
    case FOR_TOKEN:
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
        WRITESTMT();
        break;
    case COLON_TOKEN:
        EXP();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case PO_TOKEN:
        EXPSTMT();
        break;
    case ACO_TOKEN:
        SCOPESTMT();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //
        break;
    case ID_TOKEN:
        EXPSTMT();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case TO_TOKEN:
        Symbole_Suiv();
        FTO();
        break;
    case PF_TOKEN:
        Symbole_Suiv();
        break;
    case CRF_TOKEN:
        Symbole_Suiv();
        break;
    case VIR_TOKEN:
        Symbole_Suiv();
        EXP();
        ARGLIST1();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void MULOP()
{
    switch (Cour_Token.token)
    {
    case MULT_TOKEN:
    case DIV_TOKEN:
    case MOD_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void FACTOR()
{
    switch (Cour_Token.token)
    {
    case PO_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        IMMUTABLE();
        break;
    case ID_TOKEN:
        MUTABLE();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void MUTABLE()
{
    Test_Symbole(ID_TOKEN);
    MUTABLEEXTRA();
}

void MUTABLEEXTRA()
{
    switch (Cour_Token.token)
    {
    case CRO_TOKEN:
        Symbole_Suiv();
        EXP();
        Test_Symbole(CRF_TOKEN);
        break;
    case MULT_TOKEN:
    case DIV_TOKEN:
    case MOD_TOKEN:
        MULOP();
        FACTOR();
        MULEXP1();
        break;
    case PLUS_TOKEN:
    case MOINS_TOKEN:
        Symbole_Suiv();
        SUMOP();
        break;
    case DIFF_TOKEN:
    case EG_TOKEN:
    case SUP_TOKEN:
    case SUPEG_TOKEN:
    case INF_TOKEN:
    case INFEG_TOKEN:
        Symbole_Suiv();
        COMPAROP();
        SUMEXP();
        break;
    case AND_TOKEN:
        Symbole_Suiv();
        NOTEXP();
        ANDEXP1();
        break;
    case OR_TOKEN:
        Symbole_Suiv();
        ANDEXP();
        Symbole_Suiv();
        SIMPLEEXP1();
    case BY_TOKEN:
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case LET_TOKEN:
        Symbole_Suiv();
        STMT();
        break;
    case THEN_TOKEN:
        Symbole_Suiv();
        STMT();
        Test_Symbole(ELSE_TOKEN);
        STMT();
        break;
    case DO_TOKEN:
        Symbole_Suiv();
        STMT();
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    case IF_TOKEN:
        CONDSTMT();
        break;
    case WHILE_TOKEN:
        ITERSTMT();
        break;
    case FOR_TOKEN:
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
        WRITESTMT();
        break;
    case COLON_TOKEN:
        EXP();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case PO_TOKEN:
        EXPSTMT();
        break;
    case ACO_TOKEN:
        SCOPESTMT();
        break;
    case ACF_TOKEN:
        Symbole_Suiv(); //
        break;
    case ID_TOKEN:
        EXPSTMT();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case TO_TOKEN:
        Symbole_Suiv();
        FTO();
        break;
    case PF_TOKEN:
        Symbole_Suiv();
        break;
    case CRF_TOKEN:
        Symbole_Suiv();
        break;
    case VIR_TOKEN:
        Symbole_Suiv();
        EXP();
        ARGLIST1();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[CRO_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void IMMUTABLE()
{
    switch (Cour_Token.token)
    {
    case PO_TOKEN:
        EXP();
        Test_Symbole(PF_TOKEN);
        break;
    case IDFCT_TOKEN:
        CALL();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[PO_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void CALL()
{
    Test_Symbole(IDFCT_TOKEN);
    Test_Symbole(PO_TOKEN);
    ARGS();
    Test_Symbole(PF_TOKEN);
}

void ARGS()
{
    switch (Cour_Token.token)
    {
    case COLON_TOKEN:
    case NOT_TOKEN:
    case PO_TOKEN:
    case IDFCT_TOKEN:
    case ID_TOKEN:
        ARGLIST();
        break;
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case PF_TOKEN:
        Symbole_Suiv();
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
        ARGLIST1();
        break;
    case PF_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[VIR_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}

void CONSTANT()
{
    switch (Cour_Token.token)
    {
    case NUMCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case CHARCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
    }
}
