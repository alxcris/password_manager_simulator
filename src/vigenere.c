#include <stdio.h>
#include <string.h>
#include <stdio.h>

/* Daca cheia e valid,caz in care functia returneaza
valoarea 1,iar in caz contrar,cand cheia e invalid,
functia returneaza 0.*/

int verificare_cheie(char *s)
{
    int i;
    for(i = 0; i < strlen(s); i++)
    {
        if(strchr
            ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
                 s[i]) == 0)
            return 0;
    }
    return 1;
}
/* Daca textul e valid,caz in care functia returneaza
valoarea 1,iar in caz contrar,cand textul e invalid,
functia returneaza 0.*/

int verificare_text(char *s)
{
    int i;
    for(i = 0; i < strlen(s); i++)
    {
        if(strchr
            ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
                 s[i]) == 0)
            return 0;
    }
    return 1;
}

/*Functia transformare_criptare are rolul de a tranforma codul corespunzator
literei din alfabet in litera respectiva.*/

char transformare_criptare(int n)
{
    if(n >= 0 && n <= 25)
    {
        return(97 + n); /*Transformam codul ascii in litera sa mica*/
    }
    
    if(n >= 26 && n <= 51)
    {
        return(65 + n - 26); /*Transformam codul ascii in litera sa mare*/
    }
    return 0; /*Nu se va ajunge niciodata la 0 deoarece avem '% 52' in main*/
}




int main()
{
    char cheie[14000] = "";
    char text[14000] = "";
    char rezultat[14000] = "";
    char cheie_noua[14000] = "";
   
    int i = 0;
   
    scanf("%s%s", cheie, text);
    
    if(verificare_text(text) == 0)
    {
        printf("INVALID\n");
        return 0;
    }
    
    if(verificare_cheie(cheie) == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    /*Verificam daca lungimea cheii este mai mica ca lungimea textului,
    iar daca cheia este mai mica*/
    if(strlen(cheie) < strlen(text))
    {
        strcpy(cheie_noua, cheie);
        int i_cheie = 0;
        
        for(i = strlen(cheie); i < strlen(text); i++)
        {
            cheie_noua[i] = cheie_noua[i_cheie];
            i_cheie = (i_cheie + 1) % strlen(cheie); /*Se mareste contorul
            cand ajunge la lungimea lui cheie,apoi o ia de la inceput*/
        }

        cheie_noua[strlen(text)] = 0;
        strcpy(cheie, cheie_noua);
    }

    int transformare_text;
    int transformare_cheie;
    int valoare_criptata;

    /*Valoarea transformare_text/cheie are rolul de a 
    tranforma valoare a literei din text de pe pozitia
    i in codul respectiv celor 52 de litere din cifru*/
    for(i = 0; i < strlen(text); i++)
    {
        if(text[i] >= 'a' && text[i] <= 'z')
            transformare_text = text[i] - 97; /*Litera ia valoare intre 0-25*/
        
        if(text[i] >= 'A' && text[i] <= 'Z')
            transformare_text = text[i] - 65 + 26; /*Ia valoarea intre 26-52*/

        if(cheie[i] >= 'a' && cheie[i] <= 'z')
            transformare_cheie = cheie[i] - 97;/*Litera ia valoare intre 0-25*/
        
        if(cheie[i] >= 'A' && cheie[i] <= 'Z')
            transformare_cheie = cheie[i] - 65 + 26;/*Ia valoarea intre 26-52*/

        /*Tranformam codul literei din alfabet in litera respectiva
        si o adaugam in rezultat*/
        valoare_criptata = (transformare_text + transformare_cheie) % 52;
        rezultat[i] = transformare_criptare(valoare_criptata);
    }
    rezultat[strlen(text)] = 0;
    printf("%s\n", rezultat);
    
    return 0;
}
