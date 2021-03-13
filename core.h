#include "Functions.h"

struct node *ptr = NULL;

void printErreur(Codes_LEX token)
{
    if (Cour_Token.ligne != prev_Erreur.ligne || Cour_Token.colonne != prev_Erreur.colonne)
    {
        printf("\nErreur :%d :%d :  %s \n", Cour_Token.ligne, Cour_Token.colonne, maperror[token].message_erreur);
        prev_Erreur.colonne = Cour_Token.colonne;
        prev_Erreur.ligne = Cour_Token.ligne;
        // exit(-1);
    }
}

void Symbole_Suiv()
{
    if (ptr == NULL)
        printf("Fichier VIDE ");
    printf("%s ", Cour_Token.value);
    ptr = ptr->next;
    prev_token = Cour_Token;
    Cour_Token = ptr->info;
}

void Test_Symbole(Codes_LEX token)
{
    if (Cour_Token.token == token)
    {
        Symbole_Suiv();
        return;
    }
    printErreur(token);
}

void PROGRAM()
{
    prev_Erreur.colonne = 0;
    prev_token.ligne = 0;
    ptr = head;
    Cour_Token = ptr->info;
    DECLLIST();
}

void DECLLIST()
{
    DECL();
    DECLLIST1();
}
void DECLLIST1()
{
    if (Cour_Token.token == FIN_TOKEN)
        return;
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
        SCOPESTMT();
        break;
    default:
        printErreur(ID_TOKEN);
        switch (Cour_Token.token)
        {
        case VIR_TOKEN:
        case AFF_TOKEN:
        case PV_TOKEN:
            VARDECLLIST();
            Test_Symbole(PV_TOKEN);
        case PO_TOKEN:
            Test_Symbole(PO_TOKEN);
            PARAMS();
            Test_Symbole(PF_TOKEN);
            SCOPESTMT();
            break;
        }

        break;
    }
}
void VARDECLLIST()
{
    // printf("VARDECLLIST ");
    VARVAL();
    VARDECLLIST1();
}

void VARDECLLIST1()
{
    // printf("VARDECLLIST1 ");
    switch (Cour_Token.token)
    {
    case VIR_TOKEN:
        while (Cour_Token.token == VIR_TOKEN)
        {
            Symbole_Suiv();
            VARVAL();
        }
        VARDECLLIST1();
        break;
    case PV_TOKEN:
        break;
    default:
        printErreur(VIR_PV_ERREUR);
        break;
    }
}

void VARVAL()
{
    // printf("VARVAL ");
    VARID();
    VARVALLIST();
}

void VARVALLIST()
{
    // printf("VARVALLIST ");
    switch (Cour_Token.token)
    {
    case AFF_TOKEN:
        Symbole_Suiv();
        SIMPLEEXP();
        break;
    case VIR_TOKEN:
        // VARVAL();
        // VARDECLLIST1();
        break;
    case PV_TOKEN:
        break;
    default:
        printErreur(AFF_VIR_PV_ERREUR);
        break;
        //     //erreur
    }
}
void VARID()
{
    // printf("VARID ");
    Test_Symbole(ID_TOKEN);
    VARIDEXTRA();
}

void VARIDEXTRA()
{
    // printf("VARIDEXTRA ");
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
        printErreur(AFF_VIR_PV_CRO_ERREUR);
        while (Cour_Token.token != PV_TOKEN && Cour_Token.token != AFF_TOKEN && Cour_Token.token != VIR_TOKEN)
            Symbole_Suiv();
        break;
    }
}

void TYPE()
{
    // printf("TYPE %s ", Cour_Token.value);
    switch (Cour_Token.token)
    {
    case INT_TOKEN:
    case BOOL_TOKEN:
    case CHAR_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printErreur(INT_TOKEN);
        //     //erreur
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
        break;
    default:
        printErreur(INT_PF_ERREUR);
        break;
        //     //erreur
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
        while (Cour_Token.token == VIR_TOKEN)
        {
            Symbole_Suiv();
            PARAMTYPE();
        }
        PARAMSLIST1();
        break;
    case (PF_TOKEN):
        break;
    default:
        printErreur(VIR_PF_ERREUR);
        //     //erreur
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
    case PF_TOKEN:
        // PARAMTYPE();
        // PARAMSLIST1();
        break;
    default:
        printErreur(CRO_VIR_PF_ERREUR);
        break;
        // erreur
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
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        CONSTANT();
        break;
    case PV_TOKEN:
        EXPSTMT();
        break;
    case NOT_TOKEN:
        NOTEXP();
        break;
    case ID_TOKEN:
        MUTABLE();
        break;
    case IDFCT_TOKEN:
        CALL();
        break;

    default:
        printErreur(STMT_ERREUR);
        //     //erreur
    }
}

void EXPSTMT()
{
    switch (Cour_Token.token)
    {
    case COLON_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NOT_TOKEN:
    case PO_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        EXP();
        // printf("im here ");
        Test_Symbole(PV_TOKEN);
        // printf("im here ");
        break;
    case PV_TOKEN:
        Symbole_Suiv();
        break;
    default:
        printErreur(EXPSTMT_ERREUR);
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
    case BOOL_TOKEN:
    case CHAR_TOKEN:
        while (Cour_Token.token == INT_TOKEN || Cour_Token.token == BOOL_TOKEN || Cour_Token.token == CHAR_TOKEN)
            SCOPEDVARDECL();
        LOCALDECLS1();
        break;
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
    case ACF_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        break;
    default:
        printErreur(LOCALDECLS1_ERREUR);
        //     //erreur
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
        while (Cour_Token.token == PV_TOKEN || IF_TOKEN == Cour_Token.token || WHILE_TOKEN == Cour_Token.token || FOR_TOKEN == Cour_Token.token || RETURN_TOKEN == Cour_Token.token || BREAK_TOKEN == Cour_Token.token || CIN_TOKEN == Cour_Token.token || COUT_TOKEN == Cour_Token.token || COLON_TOKEN == Cour_Token.token || NOT_TOKEN == Cour_Token.token || PO_TOKEN == Cour_Token.token || ACO_TOKEN == Cour_Token.token || ID_TOKEN == Cour_Token.token || IDFCT_TOKEN == Cour_Token.token || NUMCONST_TOKEN == Cour_Token.token || CHAR_TOKEN == Cour_Token.token || STRINGCONST_TOKEN == Cour_Token.token || TRUE_TOKEN == Cour_Token.token || FALSE_TOKEN == Cour_Token.token)
            STMT();
        STMTLIST1();
        break;
    case ACF_TOKEN:
        //}
        break;
    default:
        printErreur(STMTLIST1_ERREUR);
        //     //erreur
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
    // printf("fin");
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
        printErreur(ITERSTMT_ERREUR);
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
    case ACF_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
        break;
    default:
        printErreur(FSIMPLEEXP1_ERREUR);
        //     //erreur
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
        while (Cour_Token.token == VIR_TOKEN)
        {
            Symbole_Suiv();
            Test_Symbole(ID_TOKEN);
            Symbole_Suiv();
        }
        LISTID1();
    case PF_TOKEN:
        // Test_Symbole(PV_TOKEN);
        break;
    default:
        printErreur(VIR_PF_ERREUR);
        //     //erreur
    }
}

void EXP()
{
    switch (Cour_Token.token)
    {
    case COLON_TOKEN:
        Symbole_Suiv();
        MUTABLE();
        Test_Symbole(AFF_TOKEN);
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
        printErreur(EXP_ERREUR);
        // erreur
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
        while (Cour_Token.token == OR_TOKEN)
        {
            Symbole_Suiv();
            ANDEXP();
        }
        SIMPLEEXP1();
    case BY_TOKEN:
        // SIMPLEEXP();
        break;
    case LET_TOKEN:
        break;
    case THEN_TOKEN:
        break;
    case DO_TOKEN:
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
    case ACF_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
    case TO_TOKEN:
    case PF_TOKEN:
    case CRF_TOKEN:
    case VIR_TOKEN:
        break;
    default:
        printErreur(SIMPLEEXP1_ERREUR);

        //     //erreur
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
        while (Cour_Token.token == AND_TOKEN)
        {
            Symbole_Suiv();
            NOTEXP();
        }
        ANDEXP1();
        break;
    case OR_TOKEN:
    case BY_TOKEN:
    case LET_TOKEN:
    case THEN_TOKEN:
    case DO_TOKEN:
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
    case ACF_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
    case TO_TOKEN:
    case PF_TOKEN:
    case CRF_TOKEN:
    case VIR_TOKEN:
        break;
        // default:
        //     printErreur(ANDEXP1_ERREUR);
        //     //erreur
    }
}

void NOTEXP()
{
    switch (Cour_Token.token)
    {
    case NOT_TOKEN:
        while (Cour_Token.token == NOT_TOKEN)
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
        printErreur(NOTEXP_ERREUR);
        while (Cour_Token.token != PV_TOKEN && Cour_Token.token != VIR_TOKEN && Cour_Token.token != FIN_TOKEN && Cour_Token.token != ACF_TOKEN && Cour_Token.token != ACO_TOKEN)
            Symbole_Suiv();
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
    case OR_TOKEN:
    case BY_TOKEN:
    case LET_TOKEN:
    case THEN_TOKEN:
    case DO_TOKEN:
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
    case ACF_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
    case TO_TOKEN:
    case PF_TOKEN:
    case CRF_TOKEN:
    case VIR_TOKEN:
        break;
        // default:
        // printErreur(COMPAREXTRA_ERREUR);
        //     //erreur
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
        printErreur(EG_TOKEN);
        // erreur
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
        while (Cour_Token.token == PLUS_TOKEN || Cour_Token.token == MOINS_TOKEN)
        {
            SUMOP();
            MULEXP();
        }
        SUMEXP1();
        break;
    case DIFF_TOKEN:
    case EG_TOKEN:
    case SUP_TOKEN:
    case SUPEG_TOKEN:
    case INF_TOKEN:
    case INFEG_TOKEN:
    case AND_TOKEN:
    case OR_TOKEN:
    case BY_TOKEN:
    case LET_TOKEN:
    case THEN_TOKEN:
    case DO_TOKEN:
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
    case ACF_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
    case TO_TOKEN:
    case PF_TOKEN:
    case CRF_TOKEN:
    case VIR_TOKEN:
        break;
        // default:
        // printErreur(SUMEXP1_ERREUR);
        //     //erreur
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
        printErreur(PLUS_TOKEN);
        // erreur
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
        while (Cour_Token.token == MULT_TOKEN || Cour_Token.token == DIV_TOKEN || Cour_Token.token == MOD_TOKEN)
        {
            MULOP();
            FACTOR();
        }
        MULEXP1();
        break;
    case PLUS_TOKEN:
    case MOINS_TOKEN:
    case DIFF_TOKEN:
    case EG_TOKEN:
    case SUP_TOKEN:
    case SUPEG_TOKEN:
    case INF_TOKEN:
    case INFEG_TOKEN:
    case AND_TOKEN:
    case OR_TOKEN:
    case BY_TOKEN:
    case LET_TOKEN:
    case THEN_TOKEN:
    case DO_TOKEN:
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
    case ACF_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
    case TO_TOKEN:
    case PF_TOKEN:
    case CRF_TOKEN:
    case VIR_TOKEN:
        break;
        // default:
        // printErreur(MULT_TOKEN);
        //     //erreur
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
        printErreur(MULT_TOKEN);
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
        // default:
        // printErreur(FACTOR_ERREUR);
        // erreur
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
    case AFF_TOKEN:
    case PLUS_TOKEN:
    case MOINS_TOKEN:
    case DIFF_TOKEN:
    case EG_TOKEN:
    case SUP_TOKEN:
    case SUPEG_TOKEN:
    case INF_TOKEN:
    case INFEG_TOKEN:
    case AND_TOKEN:
    case OR_TOKEN:
    case BY_TOKEN:
    case LET_TOKEN:
    case THEN_TOKEN:
    case DO_TOKEN:
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
    case ACF_TOKEN:
    case ID_TOKEN:
    case IDFCT_TOKEN:
    case NUMCONST_TOKEN:
    case CHARCONST_TOKEN:
    case STRINGCONST_TOKEN:
    case TRUE_TOKEN:
    case FALSE_TOKEN:
    case TO_TOKEN:
    case PF_TOKEN:
    case CRF_TOKEN:
    case VIR_TOKEN:
        break;
    default:
        printErreur(MUTABLEEXTRA_ERREUR);
        //     //erreur
    }
}

void IMMUTABLE()
{
    switch (Cour_Token.token)
    {
    case PO_TOKEN:
        Symbole_Suiv();
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
        printErreur(IMMUTABLE_ERREUR);
        // erreur
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
        break;
    default:
        printErreur(ARGS_ERREUR);
        // erreur
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
        while (Cour_Token.token == VIR_TOKEN)
        {
            Symbole_Suiv();
            EXP();
        }
        ARGLIST1();
        break;
    case PF_TOKEN:
        break;
    default:
        printErreur(VIR_PF_ERREUR);
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
        printErreur(CONSTANT_ERREUR);
        // erreur
    }
}
