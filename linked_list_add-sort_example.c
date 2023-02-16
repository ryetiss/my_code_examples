#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct ogrno {
	int numara;
	struct ogrno * next;
};

struct liste {
	int erisim;
	int yil;
	int sirali;
	struct ogrno * front;
	struct liste * next;
};

void ogr_numara(struct ogrno * head, int numara) {
	struct ogrno * current = head;
	int i, bolen = 10000000;
	current->numara = (numara / 100000000);
	current->next = (struct ogrno *)malloc(sizeof(struct ogrno));
	for (i = 0; i < 7; i++) {
		current = current->next;
		current->numara = (numara / bolen) % 10;
		current->next = (struct ogrno *)malloc(sizeof(struct ogrno));
		bolen = bolen / 10;
	}
	current = current->next;
	current->numara = numara % 10;
	current->next = NULL;
}

void numara_kaydet(struct liste * head, int numara) {
	struct liste * current = head;

	if (current->erisim == 0) {
		current->erisim = numara % 10000;
		current->yil = (numara / 10000) % 100;
		current->sirali = 0;
		current->front = (struct ogrno *)malloc(sizeof(struct ogrno));
		ogr_numara(current->front, numara);
		current->next = NULL;
	}
	else {
		while (current->next != NULL){
			current = current->next;
		}
		current->next = (struct liste *)malloc(sizeof(struct liste));
		current = current->next;
		current->erisim = numara % 10000;
		current->yil = (numara / 10000) % 100;
		current->sirali = 0;
		current->front = (struct ogrno *)malloc(sizeof(struct ogrno));
		ogr_numara(current->front, numara);
		current->next = NULL;
	}

}

void artan_liste_yazdir(struct liste * head) {
	struct liste * current = head;
	struct liste * temp = head;
	struct ogrno * ogrcurrent;
	int i, sayi = 0;
	printf("\n");

	while (current != NULL) {
		current = current->next;
		sayi++;
	}
	current = head;
	current = current->next;

	for (i = 0; i < sayi; i++) {
		while (current != NULL) {
			if ((current->erisim < temp->erisim) && (current->sirali == 0)) {
				temp = current;
			}
			current = current->next;
		}
		temp->sirali = 1;
		ogrcurrent = temp->front;
		while (ogrcurrent != NULL) {
			printf("%d ", ogrcurrent->numara);
			ogrcurrent = ogrcurrent->next;
		}
		current = head;
		while (current != NULL) {
			if (current->sirali == 0) {
				temp = current;
			}
			current = current->next;
		}
		printf("\n");
		current = head;
	}

	current = head;
	while (current != NULL) {
		current->sirali = 0;
		current = current->next;
	}
}

void yila_gore_yazdir(struct liste * head) {
	struct liste * current = head;
	struct liste * temp = head;
	struct ogrno * ogrcurrent;
	int i, sayi = 0;
	printf("\n");

	while (current != NULL) {
		current = current->next;
		sayi++;
	}
	current = head;
	current = current->next;

	for (i = 0; i < sayi; i++) {
		while (current != NULL) {
			if ((current->erisim < temp->erisim) && (current->yil <= temp->yil) && (current->sirali == 0)) {
				temp = current;
			}
			current = current->next;
		}
		temp->sirali = 1;
		ogrcurrent = temp->front;
		while (ogrcurrent != NULL) {
			printf("%d ", ogrcurrent->numara);
			ogrcurrent = ogrcurrent->next;
		}
		current = head;
		while (current != NULL) {
			if (current->sirali == 0) {
				temp = current;
			}
			current = current->next;
		}
		printf("\n");
		current = head;
	}

	current = head;
	while (current != NULL) {
		current->sirali = 0;
		current = current->next;
	}
}

int main(void) {
	struct liste * ogrListesi = (struct liste *)malloc(sizeof(struct liste));
	ogrListesi->erisim = 0;
	int secim = 0;
	int okulNo;

	printf(" 1 - Okul numarasi gir\n");
	printf(" 2 - Numaralari artan sirada goster\n");
	printf(" 3 - Numaralari yillara gore goster\n");
	printf(" 4 - Kapat\n");

	while (secim != 4) {
		printf("\n Seciminizi Giriniz : ");
		scanf("%d", &secim);
		if (secim == 1) {
			printf("Okul Numarasini girin : ");
			scanf("%d", &okulNo);
			if ((okulNo < 999999999) && (okulNo > 100000000)){
				numara_kaydet(ogrListesi, okulNo);
			}
			else {
				printf("Hatali Numara!\n");
			}
		}
		else if(secim == 2){
			if (ogrListesi->erisim == 0) {
				printf("Liste Bos!\n");
			}
			else {
				artan_liste_yazdir(ogrListesi);
			}
		}
		else if(secim == 3){
			if (ogrListesi->erisim == 0) {
				printf("Liste Bos!\n");
			}
			else {
				yila_gore_yazdir(ogrListesi);
			}
		}
		else{
			printf("Yanlis Secim!\n");
		}
	}
	
}
