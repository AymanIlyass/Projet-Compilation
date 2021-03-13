#include "declarations.h"

void read_char()
{
    cour_char = fgetc(file);
    if (cour_char == '\n')
        colonne = 1, ligne++;
    else
        colonne++;
}
//------------
void read_string()
{
    memset(Cour_Token.value, '\0', 31);

    int nbchar = 0;
    bool isStringConst = false;
    bool isCharConst = false;
    if (cour_char != '"' && cour_char != '\'')
        Cour_Token.value[nbchar] = cour_char, nbchar++;
    else if (cour_char == '"')
        isStringConst = true;
    else
        isCharConst = true;
    // printf("%c ", cour_char);

    read_char();
    while (((cour_char >= 'a' && cour_char <= 'z') || (cour_char >= '0' && cour_char <= '9')) || ((cour_char >= 'A' && cour_char <= 'Z')) && nbchar <= 30)
    {

        Cour_Token.value[nbchar] = cour_char;
        nbchar++;
        read_char();
    }
    if (nbchar <= 30)
    {
        if (cour_char == '(')
            tokenmap(ID_FUNCTION);
        else if (isCharConst)
            tokenmap(CHAR), read_char();
        else if (isStringConst)
            tokenmap(STRING), read_char();
        else
            tokenmap(ID);
    }
    else
    {
        Error_table[curseur].code_err = ID_LONG;
        Error_table[curseur].ligneErreur = ligne;
        Error_table[curseur].colonneErreur = colonne;
        curseur++;
        tokenmap(ERROR);
    }
}
//-----------------------
void read_number()
{

    int taille = 0;

    Cour_Token.value[taille] = cour_char;
    taille++;
    read_char();
    while (cour_char >= '0' && cour_char <= '9' && taille <= 11)
    {

        Cour_Token.value[taille] = cour_char;
        taille++;
        read_char();
    }
    if (taille <= 11)
    {

        tokenmap(NUM);
    }
    else
    {
        Error_table[curseur].code_err = NUM_LONG;
        Error_table[curseur].ligneErreur = ligne;
        Error_table[curseur].colonneErreur = colonne;
        curseur++;
        tokenmap(ERROR);
    }
}
//-----------------------
void read_symbole()
{

    // memset(cour_noeud.token_str,'', sizeof(cour_noeud.token_str));
    memset(Cour_Token.identif, '\0', 31);
    memset(Cour_Token.value, '\0', 31);
    Cour_Token.token = NULL_TOKEN;
    int check = 0;
    while (cour_char == '\n' || cour_char == '\t' || cour_char == ' ')
    {
        read_char();
    }
    if ((cour_char >= 'a' && cour_char <= 'z') || (cour_char >= 'A' && cour_char <= 'Z'))
    {
        read_string();
        check = 1;
    }
    else if (cour_char >= '0' && cour_char <= '9')
    {
        read_number();
        check = 1;
    }
    else if (cour_char == '"')
    {
        read_string();
        check = 1;
    }
    else if (cour_char == '\'')
    {
        read_string();
        check = 1;
    }
    else if (cour_char == ';')
    {
        Cour_Token.token = PV_TOKEN;
        Cour_Token.value[0] = ';';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '+')
    {
        Cour_Token.token = PLUS_TOKEN;
        Cour_Token.value[0] = '+';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '-')
    {
        Cour_Token.token = MOINS_TOKEN;
        Cour_Token.value[0] = '-';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '*')
    {
        Cour_Token.token = MULT_TOKEN;
        Cour_Token.value[0] = '*';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '%')
    {
        Cour_Token.token = MOD_TOKEN;
        Cour_Token.value[0] = '%';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '/')
    {
        read_char();
        if (cour_char == '/')
        {
            while (cour_char != '\n')
                read_char();
        }
        else if (cour_char == '*')
        {
            commentignore();
        }
        else
        {
            Cour_Token.token = DIV_TOKEN;
            Cour_Token.value[0] = '/';
            tokenmap(SPECIAL);
        }
    }
    else if (cour_char == ',')
    {
        Cour_Token.token = VIR_TOKEN;
        Cour_Token.value[0] = ',';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '(')
    {
        Cour_Token.token = PO_TOKEN;
        Cour_Token.value[0] = '(';
        tokenmap(SPECIAL);
    }
    else if (cour_char == ')')
    {
        Cour_Token.token = PF_TOKEN;
        Cour_Token.value[0] = ')';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '=')
    {
        read_char();
        if (cour_char == '=')
        {
            Cour_Token.token = EG_TOKEN;
            strcpy(Cour_Token.value, "==");
            tokenmap(SPECIAL);
        }
        else
        {
            Cour_Token.token = AFF_TOKEN;
            Cour_Token.value[0] = '=';
            tokenmap(SPECIAL);
            check = 1;
        }
    }
    else if (cour_char == '!')
    {
        read_char();
        if (cour_char == '=')
        {
            Cour_Token.token = DIFF_TOKEN;
            strcpy(Cour_Token.value, "!=");
            tokenmap(SPECIAL);
        }
        else
        {
            Cour_Token.token = NOT_TOKEN;
            Cour_Token.value[0] = '!';
            tokenmap(SPECIAL);
            check = 1;
        }
    }
    else if (cour_char == ':')
    {
        Cour_Token.token = COLON_TOKEN;
        Cour_Token.value[0] = ':';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '<')
    {
        read_char();
        if (cour_char == '=')
        {
            Cour_Token.token = INFEG_TOKEN;
            strcpy(Cour_Token.value, "<=");
            tokenmap(SPECIAL);
        }
        else
        {
            Cour_Token.token = INF_TOKEN;
            Cour_Token.value[0] = '<';
            tokenmap(SPECIAL);
            check = 1;
        }
    }
    else if (cour_char == '>')
    {
        read_char();
        if (cour_char == '=')
        {
            Cour_Token.token = SUPEG_TOKEN;
            strcpy(Cour_Token.value, ">=");
            tokenmap(SPECIAL);
        }
        else
        {
            Cour_Token.token = SUP_TOKEN;
            Cour_Token.value[0] = '>';
            tokenmap(SPECIAL);
            check = 1;
        }
    }
    else if (cour_char == '{')
    {
        Cour_Token.token = ACO_TOKEN;
        Cour_Token.value[0] = '{';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '}')
    {
        Cour_Token.token = ACF_TOKEN;
        Cour_Token.value[0] = '}';
        tokenmap(SPECIAL);
    }
    else if (cour_char == '[')
    {
        Cour_Token.token = CRO_TOKEN;
        Cour_Token.value[0] = '[';
        tokenmap(SPECIAL);
    }
    else if (cour_char == ']')
    {
        Cour_Token.token = CRF_TOKEN;
        Cour_Token.value[0] = ']';
        tokenmap(SPECIAL);
    }
    else
    {
        if (cour_char != EOF)
        {
            Error_table[curseur].code_err = CAR_INC;
            Error_table[curseur].ligneErreur = ligne;
            Error_table[curseur].colonneErreur = colonne;
            curseur++;
            tokenmap(ERROR);
        }
        else
        {
            Cour_Token.token = FIN_TOKEN;
            strcpy(Cour_Token.identif, "FIN_TOKEN");
        }
    }
    if (Cour_Token.token != NULL_TOKEN)
        push(Cour_Token);
    if (!check)
        read_char();
}

//-----------------------

void tokenmap(int type)
{
    if (type == SPECIAL)
    {
        for (int i = 0; i < 23; i++)
        {
            if (Cour_Token.token == specials[i].token)
            {
                strcpy(Cour_Token.identif, specials[i].identif);
                break;
            }
        }
    }
    else if (type == NUM)
    {
        strcpy(Cour_Token.identif, "NUMCONST_TOKEN");
        Cour_Token.token = NUMCONST_TOKEN;
    }
    else if (type == ERROR)
    {
        strcpy(Cour_Token.identif, "ERREUR_TOKEN");
        Cour_Token.token = ERREUR_TOKEN;
    }
    else if (type == ID)
    {
        int check = 0;
        for (int i = 0; i < strlen(Cour_Token.value); i++)
        {
            if (islower(Cour_Token.value[i]))
                Cour_Token.value[i] = Cour_Token.value[i] - 'a' + 'A';
        }
        // printf("%s ", Cour_Token.value);
        for (int i = 0; i < 24; i++)
        {
            // printf("%s ", key_words[i].identif);
            if (strcmp(Cour_Token.value, key_words[i].identif) == 0)
            {
                strcpy(Cour_Token.identif, key_words[i].identif);
                strcat(Cour_Token.identif, "_TOKEN");
                Cour_Token.token = key_words[i].token;
                check = 1;
                // printf("%s ", Cour_Token.identif);
                break;
            }
        }
        if (check == 0)
        {
            strcpy(Cour_Token.identif, "ID_TOKEN");
            Cour_Token.token = ID_TOKEN;
        }
    }
    else if (type == ID_FUNCTION)
    {
        strcpy(Cour_Token.identif, "IDFCT_TOKEN");
        Cour_Token.token = IDFCT_TOKEN;
    }
    else if (type == CHAR)
    {
        if (strlen(Cour_Token.value) == 1)
        {
            strcpy(Cour_Token.identif, "CHARCONST_TOKEN");
            Cour_Token.token = CHARCONST_TOKEN;
        }
        else
        {
            strcpy(Cour_Token.identif, "ERREUR_TOKEN");
            Cour_Token.token = ERREUR_TOKEN;
            //error more then 1 caractere
            Error_table[curseur].code_err = MORE_THEN_CHAR;
            Error_table[curseur].ligneErreur = ligne;
            Error_table[curseur].colonneErreur = colonne;
            curseur++;
        }
    }
    else if (type == STRING)
    {
        strcpy(Cour_Token.identif, "STRINGCONST_TOKEN");
        Cour_Token.token = STRINGCONST_TOKEN;
    }
    Cour_Token.ligne = ligne;
    Cour_Token.colonne = colonne;
}
//-------------------------
//----------------------------
void Analex(const char *filename)
{
    file = fopen(filename, "r+");
    read_char();

    while (cour_char != EOF)
    {
        read_symbole();
    }
    if (head == NULL)
    {
        Error_table[curseur].code_err = FICH_VID;
        Error_table[curseur].ligneErreur = ligne;
        Error_table[curseur].colonneErreur = colonne;
        curseur++;
        printf("Erreur :%s", mes_err[1].message_erreur);
        return;
    }
    Cour_Token.token = FIN_TOKEN;
    strcpy(Cour_Token.identif, "FIN_TOKEN");
    push(Cour_Token);
    display();

    fclose(file);
}
//-------------
void push(Maptoken Cour_Token)
{
    struct node *temp, *ptr;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->info = Cour_Token;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        ptr = head;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}
//------------------------
void display()
{
    struct node *ptr;
    if (head == NULL)
    {
        printf("nList is empty:n");
        return;
    }
    else
    {
        ptr = head;
        while (ptr != NULL)
        {
            if (ptr->info.identif[0] != '\n')
                printf("%s %d %d ", ptr->info.identif, ptr->info.ligne, ptr->info.colonne);
            ptr = ptr->next;
        }
    }
}

//--------------
void commentignore()
{

    while (cour_char != EOF)
    {
        read_char();
        if (cour_char == '*')
        {
            read_char();
            if (cour_char == '/')
            {
                break;
            }
        }
    }
}
