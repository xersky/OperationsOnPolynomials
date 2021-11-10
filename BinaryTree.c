#include <stdio.h>
#include <stdlib.h>

typedef struct monome{
    int Expos;
    int Coeff;
}monome;

typedef struct ABR{
    monome val;
    struct ABR *fg;
    struct ABR *fd;
}ABR;


ABR* Saisir(){
    ABR *nm = (ABR *)malloc(sizeof(ABR));
    printf("Entrer le coefficient :");
    scanf("%d",&nm->val.Coeff);
    printf("Entrer l'exposant :");
    scanf("%d",&nm->val.Expos);
    while(nm->val.Expos<0){
    printf("L'Exposant ne doit pas être négatif\n Veuillez saisir un autre Exposant supérieur ou égal à 0 :");
    scanf("%d",&nm->val.Expos);
    } 
    nm->fg = NULL;
    nm->fd = NULL;
    return nm;
}


ABR* INSERER(ABR* Arbre, ABR* New){
    if(Arbre==NULL) return New;
    if(New->val.Expos==Arbre->val.Expos){
        printf("L'exposant de ce monome existe deja !");
        return Arbre;
    }else{
        if(New->val.Expos < Arbre->val.Expos){
            if(Arbre->fg==NULL) Arbre->fg = New;
            else INSERER(Arbre->fg, New);
        }else{
            if(Arbre->fd==NULL) Arbre->fd = New;
            else INSERER(Arbre->fd, New);
        }
    }
    return Arbre;
}


void AFFICHER(ABR* Arbre){
    if(Arbre!=NULL){
        if(Arbre->val.Expos > 1){
            if (Arbre->val.Coeff==1) printf("x%d", Arbre->val.Expos);
            else printf("%dx%d",Arbre->val.Coeff, Arbre->val.Expos);
        }else{
            if(Arbre->val.Expos==1) printf("%dx", Arbre->val.Coeff);
            else printf("%d", Arbre->val.Coeff);
        }
        if(Arbre->fg!=NULL) printf("+");
        AFFICHER(Arbre->fg);
        if(Arbre->fd!=NULL) printf("+");
        AFFICHER(Arbre->fd);
    }
}


int DELETE(ABR **Arbre){
    int Exposant;
    if((*Arbre)->fg==NULL){
        Exposant=(*Arbre)->val.Expos;
        (*Arbre)=(*Arbre)->fd;
    }else Exposant=DELETE((&(*Arbre)->fg));
 return(Exposant);
 }


void SUPPRIMER(ABR** Arbre, int Exposant) {

    if((*Arbre)==NULL) printf("Monome inexistant !\n");
    else{
        if(Exposant > ((*Arbre)->val.Expos )) SUPPRIMER((&(*Arbre)->fd),Exposant);
        else{
            if(Exposant < ((*Arbre)->val.Expos )) SUPPRIMER((&(*Arbre)->fg),Exposant);
            else{ // expo==val.expo
                if(((*Arbre)->fd==NULL) && ((*Arbre)->fg==NULL)) *Arbre=NULL; 
                else if((*Arbre)->fd==NULL) (*Arbre)=(*Arbre)->fg; // continue la procedure
                else if((*Arbre)->fg==NULL) (*Arbre)=(*Arbre)->fd; // continue la procedure
                else ((*Arbre)->val.Expos)=DELETE((&(*Arbre)->fd)); // (fg && fd != NULL)
            }
        }
    }
}


int CALCULER(ABR* Arbre){

    if(Arbre==NULL) return 0;
    else{
        if(Arbre->fd==NULL) return Arbre->val.Expos;
        else CALCULER(Arbre->fd);
    }
}


int COMPARER(ABR* poly1, ABR* poly2){
    if(poly1==NULL){
        if(poly2==NULL) return 1;
        else return 0;
    } 
    else{   
        if(poly2==NULL) return 0;
        else{ 
            if((poly1->val.Coeff == poly2->val.Coeff) && (poly1->val.Expos == poly2->val.Expos)){
                COMPARER(poly1->fg,poly2->fg);
                COMPARER(poly1->fd,poly2->fd);
            }else return 0; 
        }
    }
}

int Menu(){

    int choix;
    printf("\n\t*********************************************************\n");
    printf("\t\t\t 1-Inserer un monome\n");
    printf("\t\t\t 2-Afficher le polynome\n");
    printf("\t\t\t 3-Supprimer un monome\n");
    printf("\t\t\t 4-Calculer le degre du polynome\n");
    printf("\t\t\t 5-Comparer deux polynomes\n");
    printf("\t\t\t 0-Quitter \n");
    printf("\n\t*********************************************************\n");
    printf("\tEntrer votre choix: ");
    scanf("%d",&choix);
    return choix;
}


int main(){
    ABR* Arbre=NULL, *poly1=NULL, *poly2=NULL;
    int choix, Exposant, Degre, C, COM;
	do {
        choix=Menu();
        switch(choix){
            case 1: 
                Arbre=INSERER(Arbre, Saisir());
            break;
            case 2:
                if(Arbre != NULL){
                printf("\nVotre polynome est : \n");
                AFFICHER(Arbre);
                }else printf("\nAucun polynome a afficher !");
            break;
            case 3: 
                if(Arbre != NULL){
                    printf("Entrer l'exposant que vous voulez supprimer: ");
                    scanf("%d",&Exposant);
                    SUPPRIMER((&Arbre),Exposant);
                    if(Arbre != NULL){
                        printf("\nLe nouveau polynome apres la suppression est : \n");
                        AFFICHER(Arbre);
                    }else printf("\nLe polynome est devenu vide apres la suppression !");
                }else printf("\nAucun polynome a afficher !");
            break;

            case 4:    
                Degre=CALCULER(Arbre);
                printf("\nDegre du polynome est : %d", Degre);

            break;

            case 5:
                Arbre=NULL;
                printf("Poly1: Entrer le nombre de monome a ajouter :");
                scanf("%d", &C);
                for (int i = 0; i < C; i++){
                    poly1 = INSERER(poly1,Saisir());
                }
                printf("\nLe premier polynome que vous avez entre est : \n");
                AFFICHER(poly1);
                printf("\n-----------------------------------\n");
                printf("Poly2: Entrer le nombre de monome a ajouter :");
                scanf("%d", &C);
                for (int i = 0; i < C; i++){
                    poly2 = INSERER(poly2,Saisir());
                }
                printf("\nLe deuxieme polynome que vous avez entre est : \n");
                AFFICHER(poly2);
                printf("\n-----------------------------------\n");
                COM = COMPARER(poly1,poly2);
                if(COM) printf("Ces deux polynomes sont egaux !");
                else printf("Ces deux polynomes sont differents !");
            break;

            case 0: 
            break;

            default: 
                printf("Veuillez entrer un choix valable (entre 0 et 5)");
        }
    }while(choix !=0);

    return 0;
}