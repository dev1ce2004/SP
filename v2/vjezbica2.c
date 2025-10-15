#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba {
	char ime[50], prezime[50];
	int godina_rodjenja;
	struct osoba* next;
} Osoba;

Osoba* novaOsoba(char* ime, char* prezime, int godina) {
	Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
	if (!nova) {
		perror("Greska pri alokaciji memorije");
		exit(EXIT_FAILURE);
	}
	strcpy(nova->ime, ime);
	strcpy(nova->prezime, prezime);
	nova->godina_rodjenja = godina;
	nova->next = NULL;
	return nova;
}

void dodajNaPocetak(Osoba** head, char* ime, char* prezime, int godina) {
	Osoba* nova = novaOsoba(ime, prezime, godina);
	nova->next = *head;
	*head = nova;
}

void ispisiListu(Osoba* head) {
	for (Osoba* trenutna = head; trenutna; trenutna = trenutna->next) {
		printf("\n\n%s %s %d\n\n", trenutna->ime, trenutna->prezime, trenutna->godina_rodjenja);
	}
}

void dodajNaKraj(Osoba** head, char* ime, char* prezime, int godina) {
	Osoba* nova = novaOsoba(ime, prezime, godina);
	if (!*head) {
		*head = nova;
	}
	else {
		Osoba* trenutna = *head;
		while (trenutna->next) trenutna = trenutna->next;
		trenutna->next = nova;
	}
}

Osoba* pronadjiPoPrezimenu(Osoba* head, char* prezime) {
	for (Osoba* trenutna = head; trenutna; trenutna = trenutna->next) {
		if (strcmp(trenutna->prezime, prezime) == 0) return trenutna;
	}
	return NULL;
}

void brisiOsobu(Osoba** head, char* prezime) {
	Osoba* trenutna = *head, * prethodna = NULL;
	while (trenutna && strcmp(trenutna->prezime, prezime)) {
		prethodna = trenutna;
		trenutna = trenutna->next;
	}
	if (!trenutna) {
		printf("Osoba s prezimenom %s nije pronađena\n", prezime);
		return;
	}
	if (!prethodna) *head = trenutna->next;
	else prethodna->next = trenutna->next;
	free(trenutna);
	printf("Osoba s prezimenom %s je izbrisana\n", prezime);
}

int main() {
	Osoba* head = NULL;
	int izbor;
	char ime[50], prezime[50], buffer[100];
	int godina_rodjenja;

	do {
		printf("\n1. Dodaj na pocetak\n2. Ispisi listu\n3. Dodaj na kraj\n4. Pronadji po prezimenu\n5. Obrisi po prezimenu\n0. Izlaz\nIzbor: ");
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &izbor);

		switch (izbor) {
		case 1:
			printf("Unesite ime, prezime i god: ");
			fgets(buffer, sizeof(buffer), stdin);
			sscanf(buffer, "%s %s %d", ime, prezime, &godina_rodjenja);
			dodajNaPocetak(&head, ime, prezime, godina_rodjenja);
			break;
		case 2:
			ispisiListu(head);
			break;
		case 3:
			printf("Unesite ime, prezime i god: ");
			fgets(buffer, sizeof(buffer), stdin);
			sscanf(buffer, "%s %s %d", ime, prezime, &godina_rodjenja);
			dodajNaKraj(&head, ime, prezime, godina_rodjenja);
			break;
		case 4: {
			printf("Unesite prezime: ");
			fgets(prezime, sizeof(prezime), stdin);
			prezime[strcspn(prezime, "\n")] = 0;
			Osoba* pronadjena = pronadjiPoPrezimenu(head, prezime);
			if (pronadjena) {
				printf("Pronadjena osoba: %s %s %d\n", pronadjena->ime, pronadjena->prezime, pronadjena->godina_rodjenja);
			}
			else {
				printf("Osoba s prezimenom %s ne postoji\n", prezime);
			}
			break;
		}
		case 5:
			printf("za brisat: ");
			fgets(prezime, sizeof(prezime), stdin);
			prezime[strcspn(prezime, "\n")] = 0;
			brisiOsobu(&head, prezime);
			break;
		case 0: break;
		default: printf("Neispravan izbor\n");
		}
	} while (izbor != 0);

	while (head) {
		Osoba* temp = head;
		head = head->next;
		free(temp);
	}

	return 0;
}