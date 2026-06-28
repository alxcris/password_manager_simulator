#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pair
{
    char *field;
    char *value;
};




int main()
{
    int N;
    int i;


    scanf("%d", &N);
    getchar(); /*pentru a trece peste  linia formata de scanf*/

    /*Alocam dinamic vectorul care retine cate perechi citite avem*/
    struct pair *vector = (struct pair *)malloc(N * sizeof(struct pair));
    if(vector == 0)
    {
        printf("eroare de alocare");
        return 0;
    }
    
    /*Acest for are rolul de a  citi cuvintele care reprezinta atat field,cat
    si value din structura,si le aloca dinamic memoria necesara 
    pentru a avea fix lungimea cuvintelor puse*/
    for(i = 0; i < N; i++)
    {
        char citire[256];
        fgets(citire, 256, stdin);

        char *copie_field = strtok(citire, " \n");
        char *copie_value = strtok(NULL, " \n");

        vector[i].field = (char *)malloc(strlen(copie_field) + 1);
        vector[i].value = (char *)malloc(strlen(copie_value) + 1);

        strcpy(vector[i].field, copie_field);
        strcpy(vector[i].value, copie_value);
    }

    /*Citim textul din formular*/
    char text_formular[11000];
    char cuvant_text[11000];
    char *formular_final = (char *)malloc(100000 * sizeof(char));

    formular_final[0] = 0; /*Pentru a lucra pe sir ii dam terminatorul de sir*/
    fgets(text_formular, 11000, stdin);   
     
    int caractere = 0;/*Numarul de caractere din cuvant*/
    int gasit;
    int j;
    int lungime_formular = strlen(text_formular);
    int lungime;
    
    /*Forul are rolul de a trece prin fiecare litera a formularului*/
    for(i = 0; i < lungime_formular; i++)
    {
        /*Daca gasim delimitator de  sir,facem prelucrarile necesare*/
        if(text_formular[i] == ' ' || text_formular[i] == '.' ||
                text_formular[i] == ',' || text_formular[i] == '!' ||
                text_formular[i] == '?' || text_formular[i] == ':' ||
                text_formular[i] == ';' || text_formular[i] == '\n' ||
                text_formular[i] == ')' || text_formular[i] == '(')
        {
            if(caractere > 0)
            {
                cuvant_text[caractere] = 0;
                gasit = -1; /*Daca luam 0,era egal cu fieldul de pe pozitia 0*/

                /*For are rolul de a compara fiecare 
                cuvant cu un field pana gaseste unul*/
                for(j = 0; j < N; j++)
                {
                    if(strcmp(cuvant_text, vector[j].field) == 0)
                    {
                        gasit = j;
                        j = N;/*Pentru a opri forul in caz de gasim un field*/
                    }
                }

                /*Daca am gasit un cuvant in formular care e un 
                field,atunci ii copiem valoarea din field
                (exemplu ion pt campul PRENUME) in formularul final.
                Daca cuvantul nu e field,atunci il lipim in formular.*/
                if(gasit != -1)
                {
                    strcat(formular_final, vector[gasit].value);
                }

                else
                {
                    strcat(formular_final, cuvant_text);
                }

                caractere = 0;
            }
            /*Daca nu e '\0',adaugam delimitatorul in formularul final*/
            if(text_formular[i] != 0)
            {
                lungime = strlen(formular_final);
                formular_final[lungime] = text_formular[i];
                formular_final[lungime + 1] = 0;
            }
        }
        /*Daca nu este un delimitator,salvam litera din text in cuvant*/
        else
        {
            cuvant_text[caractere++] = text_formular[i];
        }
    }

    /*Realocam  formularul final pentru a avea marimea necesara lungimii*/
    formular_final = (char *)realloc(formular_final, (strlen(formular_final) + 1) * sizeof(char));
    
    if(formular_final == 0)
    {
        printf("eroare de alocare");
        return 0;
    }
    
    printf("%s", formular_final);

    /*Dupa afisare eliberam memoria alocata din toate locurile folosite*/
    for(i = 0; i < N; i++)
    {
        free(vector[i].field);
        free(vector[i].value);
    }
    
    free(vector);
    free(formular_final);

    return 0;
}
