#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct node{
	struct node *prev;//pointer menuju generasi sebelumnya
	char nama[50];
	bool namaifdead=false;
	char namapasangan[50];
	bool namapasanganifdead=false;
	struct node *pertama;//pointer menuju anak 1
	struct node *kedua;//pointer menuju anak 2
};
struct node *tree;//pohon utama
struct node *current;//lokasi sekarang
struct node *temp;//digunakan sebagai perantara traversi
void create_tree(struct node *);
struct node *insertElement(struct node *);
struct node *turungenerasi(struct node *);
struct node *naikgenerasi(struct node *);
//traversal
void keluargainti(struct node *);
void meninggal(struct node *);
void postorderTraversal(struct node *);
void preorderTraversal(struct node *);
void inorderTraversal(struct node *);
void Traversal(struct node *);

int main(){
	char val[50];
	int option;
	struct node *ptr;//pointer malloc baru node
	struct node *bfr;//pointer before untuk current
	create_tree(tree);
	
	do{
		system("cls");
		printf("\n *******MAIN MENU*******\n");
		printf("\n 1. Insert Element");
		printf("\n 2. Keluarga Inti");
		printf("\n 3. Meninggal");
		printf("\n 4. Traversal");
		printf("\n 5. Turun Generasi");
		printf("\n 6. Naik Generasi");
		printf("\n 7. Reset Tree");
		printf("\n 8. Exite");
		printf("\n\n Enter your option : ");
		scanf("%d",&option);
		switch(option){
			case 1:
				tree = insertElement(tree);
				printf("\n Press Any Key To Continue...");
				getch();
				break;
			case 2:
				if(current==NULL){
					printf("Tidak Memiliki Keluarga Inti!\n");
					getch();
				}
				else if(current!=NULL){
					printf("\n Keluarga Inti ialah : \n");
					keluargainti(current);
					printf("\n Press Any Key To Continue...");
					getch();
				}
				break;
			case 3:
				printf("\n Meninggal : \n");
				meninggal(current);
				printf("\n Press Any Key To Continue...");
				getch();
				break;
			case 4:
				printf("\n The elements of the tree are : \n");
				Traversal(tree);
				printf("\n Press Any Key To Continue...");
				getch();
				break;
			case 5:
				printf("\nTurun Generasi\n");
				if(current==NULL){
					printf("Data generasi sekarang kosong!\n");
					getch();
				}
				else if(current!=NULL){
					if((current->pertama==NULL)&&(current->kedua==NULL)){
						printf("Tidak memiliki keturunan!\n");
						getch();
					}
					else{
						current = turungenerasi(tree);
						printf("\nSekarang adalah %s",current->nama);
						printf("\n Press Any Key To Continue...");
						getch();
					}
				}
				break;
			case 6:
				printf("\nNaik Generasi\n");
				if(current==NULL){
					printf("Data generasi sekarang kosong!\n");
					getch();
				}
				else if(current!=NULL){
					if(current->prev==NULL){
						printf("Tidak memiliki generasi sebelum ini!\n");
						getch();
					}
					else{
						current = naikgenerasi(tree);
						printf("\nSekarang adalah %s",current->nama);
						printf("\n Press Any Key To Continue...");
						getch();
					}
				}
				break;
			case 7:
				printf("Me-Reset....\n");
				tree=NULL;
				current=NULL;
				temp=NULL;
				bfr=NULL;
				printf("Berhasil!");
				getch();
				break;
		}
	}while(option!=8);
	printf("\n Press Any Key To Continue...");
	
	return 0;
}


void create_tree(struct node *tree){
	tree = NULL;
}

struct node *insertElement(struct node *tree){
	int pilih;
	char val[50];
	printf("\n Enter name of the new node : ");
	scanf("%s",&val);
	printf("Apakah punya pasangan ?");
	printf("\n1. Ya");
	printf("\n2. Tidak");
	printf("\n Enter your option : ");
	scanf("%d",&pilih);
	struct node *ptr, *nodeptr;
	ptr = (struct node*)malloc(sizeof(struct node));
	strcpy(ptr->nama,val);
	if(pilih==1){
		printf("\n Enter partner name : ");
		scanf("%s",&val);
		strcpy(ptr->namapasangan,val);
		ptr->namapasanganifdead=false;
	}
	else if(pilih==2){
		*ptr->namapasangan='\0';
		ptr->namapasanganifdead=true;
	}
	ptr->namaifdead=false;
	ptr->prev = NULL;
	ptr->pertama=NULL;
	ptr->kedua=NULL;
	if (tree==NULL){
		tree = ptr;
		tree->prev=NULL;
		tree->pertama=NULL;
		tree->kedua=NULL;
		current = tree;
	}
	else
	{
		nodeptr=current;
		if (current->pertama==NULL && current->kedua==NULL){
			printf("Anak pertama dari %s adalah %s\n",nodeptr->nama,ptr->nama);
			nodeptr->pertama=ptr;
			nodeptr->pertama->prev=current;
		}
		else if(current->pertama!=NULL && current->kedua==NULL){
			printf("Anak kedua dari %s adalah %s\n",nodeptr->nama,ptr->nama);
			nodeptr->kedua=ptr;
			nodeptr->kedua->prev=current;
		}
		else if(current->pertama!=NULL && current->kedua !=NULL){
			system("cls");
			printf("\nTidak bisa menambah anak, anak sudah 2!\n");
		}
	}
	return tree;
}

void keluargainti(struct node *now){
	if(now!=NULL){
			if(*now->namapasangan=='\0'){
				printf("Sekarang : %s\n", now->nama);
			}
			else if(*now->namapasangan!='\0'){
				printf("Sekarang : %s dan %s\n", now->nama, now->namapasangan);
			}
			if(now->pertama!=NULL){
			if(*now->pertama->namapasangan=='\0'){
				printf("Pertama : %s (anak)\n", now->pertama->nama);
			}
			else if(*now->pertama->namapasangan!='\0'){
				printf("Pertama : %s (anak) dan %s\n", now->pertama->nama,now->pertama->namapasangan);
			}
		}
			if(now->kedua!=NULL){

			if(*now->kedua->namapasangan=='\0'){
				printf("Kedua : %s (anak)\n", now->kedua->nama);
			}
			else if(*now->kedua->namapasangan!='\0'){
				printf("Kedua : %s (anak) dan %s\n", now->kedua->nama,now->kedua->namapasangan);
	}
			}
	}
	}

void meninggal(struct node* current){
	if(current!=NULL){
		char alm[5];
		temp = current;
		int menu;
		int pilih;
		keluargainti(current);
		strcpy(alm,"Alm. ");
		if(current->pertama!=NULL && current->kedua!=NULL){
			printf("\nPilih siapa yang meninggal (1. Sekarang/2. Anak Pertama / 3. Anak Kedua) : ");
		}
		else if(current->pertama!=NULL && current->kedua==NULL){
			printf("\nPilih siapa yang meninggal (1. Sekarang/2. Anak Pertama) : ");
		}
		else if(current->pertama==NULL && current->kedua==NULL){
			printf("\nPilih siapa yang meninggal (1. Sekarang) : ");
		}
		scanf("%d",&menu);
		if(menu==1){
			if((current->namaifdead==true&&current->namapasanganifdead==true)){
				printf("Sudah dinyatakan Meninggal!\n");
			}
			else{
				if(current->namaifdead==false&&current->namapasanganifdead==false){
					printf("%s\n",temp->nama);
					printf("%s\n",temp->namapasangan);
					printf("Pilih siapa yang meninggal [1/2] : ");
					scanf("%d", &pilih);
				}
				else if((current->namaifdead==false&&current->namapasanganifdead==true)){
					pilih=1;
				}
				else if(current->namaifdead==true&&current->namapasanganifdead==false){
					pilih=2;
				}
			}
			if(pilih==1){
					strcat(alm, temp->nama);
					strcpy(current->nama,alm);
					printf("Berhasil Meninggal!, %s\n",current->nama);
					current->namaifdead=true;
				}
			else if(pilih==2){
					strcat(alm, temp->namapasangan);
					strcpy(current->namapasangan,alm);
					printf("Berhasil Meninggal!, %s\n",current->namapasangan);
					current->namapasanganifdead=true;
				}
		}

		else if(menu==2){
			if((current->pertama->namaifdead==true&&current->pertama->namapasanganifdead==true)){
				printf("Sudah dinyatakan Meninggal!\n");
			}
			else{
				if(current->pertama->namaifdead==false&&current->pertama->namapasanganifdead==false){
					printf("%s\n",temp->pertama->nama);
					printf("%s\n",temp->pertama->namapasangan);
					printf("Pilih siapa yang meninggal [1/2] : ");
					scanf("%d", &pilih);
				}
				else if((current->pertama->namaifdead==false&&current->pertama->namapasanganifdead==true)){
					pilih=1;
				}
				else if(current->pertama->namaifdead==true&&current->pertama->namapasanganifdead==false){
					pilih=2;
				}
			}
			if(pilih==1){
					strcat(alm, temp->pertama->nama);
					strcpy(current->pertama->nama,alm);
					printf("Berhasil Meninggal!, %s\n",current->pertama->nama);
					current->pertama->namaifdead=true;
				}
			else if(pilih==2){
					strcat(alm, temp->pertama->namapasangan);
					strcpy(current->pertama->namapasangan,alm);
					printf("Berhasil Meninggal!, %s\n",current->pertama->namapasangan);
					current->pertama->namapasanganifdead=true;
				}
		}
		else if(menu==3){
			if((current->kedua->namaifdead==true&&current->kedua->namapasanganifdead==true)){
				printf("Sudah dinyatakan Meninggal!\n");
			}
			else{
				if(current->kedua->namaifdead==false&&current->kedua->namapasanganifdead==false){
					printf("%s\n",temp->kedua->nama);
					printf("%s\n",temp->kedua->namapasangan);
					printf("Pilih siapa yang meninggal [1/2] : ");
					scanf("%d", &pilih);
				}
				else if((current->kedua->namaifdead==false&&current->kedua->namapasanganifdead==true)){
					pilih=1;
				}
				else if(current->kedua->namaifdead==true&&current->kedua->namapasanganifdead==false){
					pilih=2;
				}
			}
			if(pilih==1){
					strcat(alm, temp->kedua->nama);
					strcpy(current->kedua->nama,alm);
					printf("Berhasil Meninggal!, %s\n",current->kedua->nama);
					current->kedua->namaifdead=true;
				}
			else if(pilih==2){
					strcat(alm, temp->kedua->namapasangan);
					strcpy(current->kedua->namapasangan,alm);
					printf("Berhasil Meninggal!, %s\n",current->kedua->namapasangan);
					current->kedua->namapasanganifdead=true;
				}
	}
	else{
		printf(" Tidak ada Data!");
	}
}
}
void postorderTraversal(struct node* tree){
	if(tree!=NULL){
		postorderTraversal(tree->pertama);
		postorderTraversal(tree->kedua);
		printf("%s\n",tree->nama);
	}
}
void preorderTraversal(struct node* tree){
	if(tree!=NULL){
		printf("%s\n", tree->nama);
		preorderTraversal(tree->pertama);
		preorderTraversal(tree->kedua);
	}
}
void inorderTraversal(struct node* tree){
	if(tree!=NULL){
		inorderTraversal(tree->pertama);
		printf("%s\n", tree->nama);
		inorderTraversal(tree->kedua);
	}
}
struct node *turungenerasi(struct node* tree){
	struct node *bfr;
	bfr = (struct node*)malloc(sizeof(struct node));
	bfr = current->prev;
	if(current==NULL){
		printf("Generasi sekarang kosong!");
	}
	else{
		int pilih;
		if((current->pertama!=NULL)&&(current->kedua==NULL)){
			current->prev = bfr;
			current->pertama->prev = current;;
			current = current->pertama;
			printf("Berhasil");
		}
		else if((current->pertama!=NULL)&&(current->kedua!=NULL)){
			printf("Pilih turun generasi : ");
			printf("\n1.%s",current->pertama->nama);
			printf("\n2.%s",current->kedua->nama);
			printf("\n Enter your option : ");
			scanf("%d",&pilih);
			if(pilih==1){
				current->prev = bfr;
				current->pertama->prev = current;
				current = current->pertama;
				printf("Berhasil, sekarang Anda adalah %s\n", current->nama);
			}
			else if(pilih==2){
				current->prev = bfr;
				current->kedua->prev = current;
				current = current->kedua;
				printf("Berhasil, sekarang Anda adalah %s\n", current->nama);
			}
		}
		return current;
		}
}
struct node *naikgenerasi(struct node* tree){
	temp = current->prev;
	if(current==NULL){
		printf("Generasi sekarang kosong!\n");
	}
	else{
		if(current->prev==NULL){
			printf("Tidak ada generasi di atas ini!\n");
		}
		else{
			current = temp;
			printf("Berhasil\n");
		}
		return current;
		}
}
void Traversal(struct node* tree){
	int traverse;
	if(tree==NULL){
		printf("Tidak ada data!\n");
	}
	else{
		printf("\t\tTraversal\n");
		printf("1. PreOrder Traversal\n");
		printf("2. InOrder Traversal\n");
		printf("3. PostOrder Traversal\n");
		scanf("%d", &traverse);
		if(traverse==1){
			preorderTraversal(tree);
		}
		else if(traverse==2){
			inorderTraversal(tree);
		}
		else if(traverse==3){
			postorderTraversal(tree);
		}
	}
}
