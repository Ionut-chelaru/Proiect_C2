#include <stdio.h>
#include <string.h>

//Functii decalrate
void afisareMeniu(int* op1);
void deschidereFisier(FILE** f, char fisiernume[14], const char* mod);
void afisareTelefone();
void afisareMeniu2(int* op2);
void optiuniMeniu2(int* op2);
void afisarePret();
void afisareSpec();
void selectareTel();
void recenzii();
void cuponReducere();

//Variabile globale
int op_m1,op_m2,op_m3,i,cod_validare;
char cod[10];
FILE *f;


int main(){

	afisareMeniu(&op_m1);
	if(op_m1 != 0){
		afisareTelefone();
		do{
			afisareMeniu2(&op_m2);
			optiuniMeniu2(&op_m2);
		}while(op_m2 != 0);
	}
	printf("Va multumim pentru atentie! ٩(^‿^)۶");

	return 0;
}

//functii initializate

void afisareMeniu(int* op1){
	printf("Bun venit la magazinul nostru!\nAvem in stoc o gama de telefoane, doriti sa continuati?\n");
	printf("Alegeti(1. DA 0. NU): ");
	fflush(stdout);
	scanf("%d",op1);
	printf("\n");
}

void deschidereFisier(FILE** f, char fisiernume[14], const char* mod) {
	*f = fopen(fisiernume, mod);
	if (*f == NULL) {
		printf("\nFisierul %s nu s-a deschis!", fisiernume);
	}
}

void afisareTelefone(){
	char linie[50];
	deschidereFisier(&f,"telefoane.txt","r");
	i=0;
	while (fgets(linie, sizeof(linie), f)) {
		printf("%d. %s",i+1, linie);
		fflush(stdout);
		i++;
	}
	fclose(f);
}

void afisareMeniu2(int* op2){
	printf("\n\n1. Afiseaza pretul telefonului\n2. Afiseaza specificatiile telefonului\n3. Afiseaza recenzia produsului\n4. Scaneaza cuponul de reducere.\n0. Iesire\n");
	printf("Alege: ");
	fflush(stdout);
	scanf("%d",op2);
	printf("\n");
}

void optiuniMeniu2(int* op2){
	switch(*op2){
	case 1:
		afisarePret();
		break;
	case 2:
		afisareSpec();
		break;
	case 3:
		recenzii();
		break;
	case 4:
		cuponReducere();
	}

}

void selectareTel(){
	printf("Selectati telefonul: ");
	fflush(stdout);
	scanf("%d",&op_m3);

}

void afisarePret(){
	int op_val;
	selectareTel();
	printf("1. Euro\n2. Ron\nAlege: ");
	fflush(stdout);
	scanf("%d",&op_val);
	deschidereFisier(&f,"telefonpr.txt","r");
	i=0;
	float pret;
	char ron[4];


	while(fscanf(f,"%f%s",&pret,ron) == 2){
		if(cod_validare == 1)
			pret = pret - pret * 0.10;
		if(op_m3-1 == i && op_val == 2){
			printf("\nTelefonul %d are valoarea de %.1f %s",i+1,pret,ron);
			fflush(stdout);
		}
		else if(op_m3-1 == i && op_val == 1){
			pret *= 0.2;
			printf("\nTelefonul %d are valoarea de %.1f %s",i+1,pret,"EURO");
			fflush(stdout);
		}
		i++;
	}
	fclose(f);

}

void afisareSpec(){
	selectareTel();
	char linie[200];
	deschidereFisier(&f,"specificatii.txt","r");
	i=0;
	while (fgets(linie, sizeof(linie), f)) {
		if(op_m3-1 == i){
			printf("\n%s", linie);
			fflush(stdout);
		}
		i++;
	}
	fclose(f);
}

void recenzii(){
	selectareTel();
	deschidereFisier(&f,"recenziii.txt","r");
	i=0;
	int recenzie;
	char reziduu[5];
	while (fscanf(f,"%d%[^\n]",&recenzie,reziduu) == 2) {
		if(op_m3-1 == i){
			printf("\nRecenzia medie dupa achizitionare: %d",recenzie);
			switch(recenzie){
			case 1 ... 3:
			printf("\nAceasta recenzie specifica ca produsul este de proasta\ncalitate si nu merita a fi achizitionat");
			break;
			case 4 ... 6:
			printf("\nAceasta recenzie specifica ca produsul este de indeajuns\nde bun dar nu este cea mai buna solutie");
			break;
			case 7 ... 9:
			printf("\nAceasta recenzie specifica ca produsul este de buna\ncalitate si este recomandat");
			break;
			case 10: printf("\nUn produs extrem de bun, durabil si accesibil");
			}
		}
		i++;
	}
	fclose(f);
}

void cuponReducere(){
	printf("cod ROXANA pentru reducere de 10%%\nValideaza: ");
	fflush(stdout);
	scanf("%s",cod);
	if(strcmp("ROXANA",cod) == 0){
		cod_validare=1;
		printf("\nCodul este validat!! \\( ﾟヮﾟ)/");
	}
	else if (strcmp("ROXANA",cod) != 0){
		cod_validare = 0;
		printf("\nCodul nu a fost validat! ( ✜︵✜ )");
	}

}
