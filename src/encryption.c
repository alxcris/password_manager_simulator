#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Codificarea pe aparitii*/
char *codificare_1(char c)
{
    /*Am declarat vectorul de frecventa cu static deoarece
    valoarea sa va ramane intre apelurile functiei,fiind nevoie de o singura
    alocare frecventa[126] = {0}*/
    static int frecventa[126] = {0};
    int valoare_c = c;

    /*Daca codul ascii al literei c nu se afla in acel interval returnam 0*/
    if(valoare_c < 32 || valoare_c > 125)
    {
        return 0;
    }

    /*Se salveaza nr de apartii al lui c in numarare iar frecventa sa creste*/
    int numarare = frecventa[valoare_c];
    frecventa[valoare_c]++;
    
    int copie_numarare = numarare;
    int nr_cifre = 0;
    
    /*Daca c apare pentru prima data,frecventa sa tot 0 este la inceput
    asa ca trebuie sa marim numarul de cifre chiar daca numarare este 0 */
    if(copie_numarare == 0)
    {
        nr_cifre = 1;
    }
    else 
    {
        /*While-ul numara de cate caractere avem nevoie
        pentru numarul din sirul final*/
        while(copie_numarare > 0)
        {
            nr_cifre++;
            copie_numarare = copie_numarare / 10;
        }
    }

    /*Alocam 2+nr_cifre la rezultat deoarece adaugam si caracterul si '\0'*/
    char *rezultat = (char *)malloc((2 + nr_cifre) * sizeof(char));
    
    if(rezultat == 0)
    {
        printf("eroare de alocare");
        return 0;
    }

    rezultat[0] = valoare_c; /*Primul caracter*/
    char cifre[100];
    int i = 0;
    copie_numarare = numarare;

    /*Daca frecventa este 0,se adauga caracterul 0 deoarece pana in momentul
    respectiv,c nu a mai aparut(exemplu c0c1c2c),while-ul nu ar adauga 0*/
    if(copie_numarare == 0)
    {
        cifre[i] = '0';
        i++;
    }
    else 
    {
        /*Transformam fiecare cifra in cod ascii si o salvam in cifre*/
        while(copie_numarare > 0)
        {
            cifre[i] = (copie_numarare % 10) + 48; /*Transformam ultima cifra*/
            copie_numarare = copie_numarare / 10;
            i++;
        }
    }

    int contor_afisare = 1;

    /*Punem cifrele,pe rand,in rezultat in ordinea inversa din cifre*/
    while(i > 0)
    {
        i--;
        rezultat[contor_afisare] = cifre[i];
        contor_afisare++;
    }

    rezultat[contor_afisare] = 0;

    return rezultat;
}

/*Codificarea pe biti*/
char *codificare_2(char c)
{
    char copie = c; 
    int nrbiti = 0;
    int i;

    /* Negam bitii de pe pozitia 3 si 6 */
    copie = copie ^ (1 << 3);
    copie = copie ^ (1 << 6);

    /* Numaram bitii de 1 din c */
    for(i = 0; i < 8; i++)
    {
        if(copie & (1 << i))
        {
            nrbiti++;
        }
    }
    /* Folosim sau pe copie cu masca respectiva */
    copie = copie | 32;

    /* Setam LSB la 0 */
    copie = copie & ~1;
    
    char *rezultat = (char *)malloc(3 * sizeof(char));
    if (rezultat == 0)
    {
        printf("eroare de alocare");
        return 0;
    }
    /*La rezultatul final ne trebuie doar caracterul format si nr biti 1*/
    rezultat[0] = copie;
    rezultat[1] = nrbiti + 48; /*+48 pentru a transforma numarul in caracter*/
    rezultat[2] = 0;

    return rezultat;
}

/*Conversia de litere*/
char *codificare_3(char c)
{
    char caracter_transformat = c;

    /*Transformam literele mici in litere mari*/
    if(c >= 'a' && c <= 'z')
    {
        caracter_transformat = c - 32;
    }
    
    /*Se aloca doar 2 octeti deoarece avem un caracter + terminatorul de sir*/
    char *rezultat = (char *)malloc(2 * sizeof(char));
    
    if(rezultat == 0)
    {
        printf("eroare de alocare");
        return 0;
    }
    rezultat[0] = caracter_transformat;
    rezultat[1] = 0; /*Punem terminatorul de sir*/

    return rezultat;
}

char *transformare(char* sir_initial, char* (*codificari[])(char))
{
    /*Deoarece sirul nostru rezultat nu are nici un caracter la inceput,
    il alocam cu un octet pentru terminatorul de sir*/
    char *sir_final = (char *)malloc(sizeof(char));
    
    if(sir_final == 0)
    {
        printf("eroare la alocarea parolei");
        return 0;
    }

    sir_final[0] = 0; /*Pentru a putea lucra pe sir*/
    int lungime = 0;
    int i;
    int functie;
    int n = strlen(sir_initial);

    for(i = 0; i < n; i++)
    {
        char c = sir_initial[i];

        /*Se alege random o codificare din cele 3*/
        functie = rand() % 3;

        /*Apelam una dintre functii iar daca  functia returneaza 0,
        atunci si if ul va incheie programul*/
        char* codificare_rezultata = codificari[functie](c);
        
        if(codificare_rezultata == 0)
        {
            free(sir_final);
            return 0;
        }

        /*Luam lungimea din sirul initial si cel codificat,si le adunam
        pentru a putea realoca memoria in functie de lungimea finala*/
        int lungime2 = strlen(codificare_rezultata);
        int lungime_finala = lungime + lungime2;
        sir_final = (char *)realloc(sir_final, (lungime_finala + 1) * sizeof(char));
        
        if(sir_final == 0)
        {
            printf("eroare de realocare");
            return 0;
        }
        /*Lungime ia valoarea lungime_finala pentru a 
        tine minte la urmatoarea iteratie did for lungimea sirului*/
        lungime = lungime_finala; 

        /*Lipim codificarea rezultata la parola*/
        strcat(sir_final, codificare_rezultata);
        free(codificare_rezultata);
    }
    
    return sir_final;
}




int main()
{
    int seed, L;
    scanf("%d%d", &seed, &L);

    /*Pentru a putea utiliza functia de randomizare rand()
    avem nevoie de srand care foloseste seedul nostru*/

    srand(seed);
    int i;
    char *sir = (char*)malloc((L + 1) * sizeof(char));


    if (sir == 0)
    {
        printf("eroare de alocare");
        return 0;
    }

    /*Acest for are rolul de a genera un sir aleatoriu prin
    ajutorul functiei rand pentru fiecare caracter in parte,
    formula (rand()%94)+32 avand rolul de transforma
    un cod ascii intre 32 si 125 in caracterul respectiv codului)*/

    for(i = 0; i < L; i++)
    {
        sir[i] = ((rand() % 94) + 32);
    }
    sir[L] = 0;

    char* (*codificari[3])(char) = {codificare_1, codificare_2, codificare_3};

    /*Generarea parolei*/
    char *parola_finala = transformare(sir, codificari);
    
    if(parola_finala != 0)
    {
        printf("%s\n", parola_finala);
        free(parola_finala);
    }
    
    free(sir);
    return 0;
}
