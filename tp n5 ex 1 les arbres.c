#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct data
{
   char clepere[5];
   char cle[5];
   char description [31];
};
typedef struct data DATA;

struct arbre
{
    DATA d;
    struct arbre* fils;
    struct arbre *frere;

};
typedef struct arbre ARBRE;


void coderdata(char * s,DATA *d,char *clepere)
{
   strncpy(clepere,s,4);clepere[4]='\0';
   strncpy(d->cle,s+4,4);d->cle[4]='\0';
   strncpy(d->description,s+8,30);



}



ARBRE *trouvernoeud(char *cle, ARBRE *a)
{
    if (a == NULL) return NULL;

    if (strcmp(cle, a->d.cle) == 0)
    {
        return a;
    }
    ARBRE *trouvefils = trouvernoeud(cle, a->fils);
    if (trouvefils != NULL) return trouvefils;

    ARBRE *trouvefrere = trouvernoeud(cle, a->frere);
    if (trouvefrere != NULL) return trouvefrere;

    return NULL;
}


void inserenoeud(ARBRE **a,DATA d,char clepere[])
{
    if (*a==NULL )
    {
        printf("creation d'un nouvel arbre\n");
        *a=(ARBRE *)malloc(sizeof(ARBRE));
        if (*a==NULL)
        {
            printf("erreur d'allocation\n");
            exit(-3);
        }
        (*a)->d=d;
        (*a)->fils=NULL;
        (*a)->frere=NULL;
        printf("adresse de l'arbre :%p\n",*a);
        return ;
    }
    ARBRE *p=trouvernoeud(clepere,*a);

    if(p==NULL )
    {
        printf("noeud introuvable\n");
        return;
    }
     printf("adresse du noeud pere: %p\n",p);


    ARBRE *nouveau = (ARBRE *)malloc(sizeof(ARBRE));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(-3);
    }

    nouveau->d = d;
    nouveau->fils = NULL;
    nouveau->frere = NULL;
    strcpy(nouveau->d.clepere, clepere);

    if (p->fils == NULL) {
        p->fils = nouveau;

        printf("adresse du noeud ajoute: %p\n",nouveau);

    }
    else {
        ARBRE *temp = p->fils;
        while (temp->frere != NULL) {
            temp = temp->frere;
        }
        temp->frere = nouveau;

        printf("adresse du noeud ajoute: %p\n",nouveau);
        printf("c est un frere\n");

    }
    printf("Noeud ajoute sous %s\n", p->d.cle);

}


ARBRE *creerarbre(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(-1);
    }

    ARBRE *a = NULL;
    char s[40];
     int caractere;
     int i=0;
     fseek(f, 0, SEEK_END);
     long taille = ftell(f);
     fseek(f, 0, SEEK_SET);

    while(ftell(f)<taille)
  {

    while(i<40)
     {
        caractere=fgetc(f);
        if(caractere==EOF || caractere=='\n' )
        {
            i=0;
            break;
        }
        s[i]=(char)caractere;
        i=i+1;
        s[i]='\0';
     }

     printf("la ligne recuperee du fichier : %s\n\n",s);


         DATA dd;
         coderdata(s,&dd,&dd.clepere);
         inserenoeud(&a,dd,dd.clepere);


     printf("\nla cle du noeud pere :%s\n",dd.clepere);
     printf("\nla cle du noeud:%s\n",dd.cle);
     printf("\nla description du noeud :%s\n",dd.description);



  }
    fclose(f);
    return a;
}




void stat_arbre(ARBRE *a,int *nb_total,int *nb_feuille,int *nb_pere,int n)
{

    if (a == NULL) return;
    (*nb_total)++;


    stat_arbre(a->fils,nb_total,nb_feuille,nb_pere,n);
    stat_arbre(a->frere,nb_total,nb_feuille,nb_pere,n);

    if (a->fils == NULL)
        (*nb_feuille)++;

    else
    {
        int nb=0;
        a=a->fils;
    while(a!=NULL)
    {
           nb++;
           a=a->frere;
    }
     if (nb>=n)(*nb_pere)++;
    }


}



void main ()
{


   ARBRE * a = creerarbre("C:\\Users\\ACER-PC\\Desktop\\arbre.txt");

   int nb_total=0;
   int nb_feuille=0;
   int nb_fils=0;
   int nb_pere=0;
   int n;

   printf("\ndonner le nombre n de fils\n");
   scanf("%d",&n);

   stat_arbre(a,&nb_total,&nb_feuille,&nb_pere,n);

   printf("le nombre total des noeuds :%d\nle nombre des feuilles : %d\nle nombre des peres ayanyt au moins %d fils :%d\n",nb_total,nb_feuille,n,nb_pere);

   char critere[5];

   printf("\ndonner le critere de suppresiion\n");
   scanf("%4s",critere);
   puts(critere);






}
