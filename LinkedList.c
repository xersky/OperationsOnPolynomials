#include <stdio.h>
#include <stdlib.h>

typedef struct monome{
    int Expos;
    int Coeff;
}monome;


typedef struct poly{
    monome val;
    struct poly *suivant;
}poly;

monome Saisir(){
    monome nm;
    printf("Entrer le coefficient :");
    scanf("%d",&nm.Coeff);
    printf("Entrer l'exposant :");
    scanf("%d",&nm.Expos);
    while(nm.Expos<0){
        printf("L'Exposant ne doit pas être négatif\n Veuillez saisir un autre Exposant supérieur ou égal à 0 :");
        scanf("%d",&nm.Expos);
    } 
    return nm;
}

poly *Derive(poly *debut){
poly *Derive=debut;
    while(Derive!= NULL){
        Derive->val.Coeff *= Derive->val.Expos;
        Derive->val.Expos--;
        if(Derive->val.Expos == 0) Derive->suivant = NULL; 
        Derive=Derive->suivant;
    }
    return debut;
}

poly *AjouterMonome(poly *debut, monome valeur){
    poly *nv = (poly *)malloc(sizeof(poly));
    nv->val=valeur;
    if (debut == NULL){
        nv->suivant=NULL;
        return nv;
    }else if (debut->val.Expos < nv->val.Expos){
       nv->suivant=debut;
       debut=nv;
       return debut; 
    }else {
        poly *tmp=debut;
        while (tmp->suivant!=NULL && tmp->val.Expos > nv->val.Expos){
            tmp=tmp->suivant;
        }
        if(tmp->val.Expos == nv->val.Expos) tmp->val.Coeff+=nv->val.Coeff;
        else {
        nv->suivant=tmp->suivant;
        tmp->suivant=nv; 
        } 
        return debut; 
    }
}  

poly *TriPolynome(poly *debut){
    int perm=0;
    poly *temp, *ptemp;
    monome valeur;

    while (!perm){
        temp = debut;
        perm=1;
        while (temp->suivant != NULL){
            ptemp = temp->suivant;
            if (temp->val.Expos < ptemp->val.Expos){
                valeur = temp->val;
                temp->val = ptemp->val;
                ptemp->val = valeur;
                perm=0;
            }
            temp = ptemp;
        }
    }
    return debut;
}


/*void AfficherPolynome(poly *debut){
    poly *temp = debut;
    while(temp!=NULL){
        if(temp->val.Expos > 1){
            if(temp->val.Coeff==1) printf("x%d", temp->val.Expos);
            else printf("%dx%d", temp->val.Coeff, temp->val.Expos);
        }
        else{ 
            if(temp->val.Expos == 1) printf("%dx", temp->val.Coeff);
            else printf("%d", temp->val.Coeff);
        }
        temp = temp->suivant;
        if (temp != NULL) printf("+");
    }
    printf("\n");
}*/

void AfficherPolynome(poly *debut){
    poly *temp = debut;
    while(temp!=NULL){
        if(temp->val.Expos > 1){
            if(temp->val.Coeff==1) printf("x%d", temp->val.Expos);
            else if(temp->val.Coeff!=0) printf("%dx%d", temp->val.Coeff, temp->val.Expos);
        }
        else{ 
            if(temp->val.Expos == 1) printf("%dx", temp->val.Coeff);
            else if (temp->val.Coeff != 0) printf("%d", temp->val.Coeff);
        }
        if (temp->suivant != NULL && temp->val.Coeff!=0 && temp->suivant->val.Coeff!=0) printf("+");
        temp = temp->suivant;

    }
    printf("\n");
}

poly *SommePolynomes(poly *poly1, poly *poly2 ){
    poly *somme = poly1;
    while ( poly2 != NULL ){
        somme = AjouterMonome(somme, poly2->val);
        poly2 = poly2->suivant;
    }
    return somme;
}
void StockerPolynomes(poly *debut, char *NomFichier){   

    FILE *f=NULL;
    f = fopen(NomFichier, "w+");
    poly *temp=debut;
    while (temp != NULL){
        if(temp->val.Expos > 1){
            if(temp->val.Coeff==1) fprintf(f,"x%d", temp->val.Expos);
            else if(temp->val.Coeff!=0) fprintf(f,"%dx%d", temp->val.Coeff, temp->val.Expos);
        }
        else if(temp->val.Expos == 1) fprintf(f,"%dx", temp->val.Coeff);
        else if(temp->val.Coeff != 0) fprintf(f,"%d", temp->val.Coeff);
        if (temp->suivant != NULL && temp->val.Coeff!=0 && temp->suivant->val.Coeff!=0) fprintf(f,"+");
        temp = temp->suivant;
    }

    fclose(f);
}


int Menu(){

    int choix;
    printf("\n\t*********************************************************\n");
    printf("\t\t\t 1-Ajouter un monome au polynome\n");
    printf("\t\t\t 2-Afficher le polynome\n");
    printf("\t\t\t 3-Derivation du polyome\n");
    printf("\t\t\t 4-Somme de deux polynomes\n");
    printf("\t\t\t 5-Stocker le polynome dans un fichier\n");
    printf("\t\t\t 0-Quitter \n");
    printf("\n\t*********************************************************\n");
    printf("\tEntrer votre choix: ");
    scanf("%d",&choix);
    return choix;
}



int main(){
    int choix, C;
    poly *debut=NULL, *poly1 = NULL, *poly2 = NULL, *SOMME=NULL;
    char NomFichier[15];
	do {
        choix=Menu();
        switch(choix){
            case 1: 
                debut=AjouterMonome(debut, Saisir());
            break;
            case 2:
                if(debut != NULL){
                debut=TriPolynome(debut);
                printf("\nVotre polynome est : \n");
                AfficherPolynome(debut);
                }else printf("\nAucun polynome a afficher");
            break;
            case 3: 
                if(debut != NULL){
                debut=Derive(debut);
                printf("\nLe derive de votre polynome est : \n");
                AfficherPolynome(debut);
                }else printf("\nAucun polynome a afficher");
            break;
            case 4 :    
                printf("Poly1: Entrer le nombre de monome a ajouter :");
                scanf("%d", &C);
                for (int i = 0; i < C; i++){
                    poly1 = AjouterMonome(poly1,Saisir());
                    poly1=TriPolynome(poly1);
                }
                printf("\nLe premier polynome que vous avez entre est : \n");
                AfficherPolynome(poly1);
                printf("\n-----------------------------------\n");
                printf("Poly2: Entrer le nombre de monome a ajouter :");
                scanf("%d", &C);
                for (int i = 0; i < C; i++){
                    poly2 = AjouterMonome(poly2,Saisir());
                    poly2=TriPolynome(poly2);
                }
                printf("\nLe deuxieme polynome que vous avez entre est : \n");
                AfficherPolynome(poly2);
                printf("\n-----------------------------------\n");
                printf("\nLa somme des deux polynomes est : \n");
                SOMME=SommePolynomes(poly1,poly2);
                SOMME=TriPolynome(SOMME);
                AfficherPolynome(SOMME);
            break;

            case 5:
                if(debut != NULL){
                printf("Entrer un nom a votre fichier : ");
                scanf("%s", NomFichier);
                StockerPolynomes(debut,NomFichier);
                }else printf("\nAucun polynome a stocker");
            break;

            case 0: 
            break;

            default: 
                printf("Veuillez entrer un choix valable (entre 0 et 5)");
        }
    }while(choix !=0);

    return 0;
}