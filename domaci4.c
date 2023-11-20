#include <stdio.h>
#include <string.h>

typedef struct User {

    char name[40];
    char password[40];
    int birthDate;
    char email[40];
    double billState;
} User;

void ispisi_niz_korisnika(User arr[], int n) {
    for(int i = 0; i < n; i++) {
        printf("Korisniko Ime: %s\n, Godina rodjenja: %d\n, Email: %s\n, Stanje racuna: %lf\n",
        arr[i].name, arr[i].birthDate, arr[i].email, arr[i].billState);
    }
}

int toDouble(char* line) {
    double num = 0;
    int weight = 1;
    int i = strlen(line) - 1;
    while(i >= 0) {
        num += 1.0 * (line[i] - '0') * weight;
        weight *= 10;
        i--;
    }
    return num;
}

int ucitaj_niz_iz_fajla(User arr[], const char fileName) {

    FILE* fp;
    fp = fopen("korisnici.txt", "r");
    if(fp == NULL) {
        printf("Fajl ne postoji!");
        return 0;
    }
    
    int userCount = 0;
    char line[40];
    while(fgets(line, 40, fp) != NULL) {
        strcpy(arr[userCount].name, line);
        fgets(line, 40, fp);
        strcpy(arr[userCount].email, line);
        fgets(line, 40, fp);
        strcpy(arr[userCount].password, line);
        fgets(line, 40, fp);
        arr[userCount].billState = toDouble(line);
        userCount++;
    }

    return userCount;
}

int da_li_postoji_username(User arr[], int n, const char username[]) {
    for(int i = 0; i < n; i++) {
        if(strcmp(username, arr[i].name) == 0) {
            return 1;
        }
    }
    return 0;
}

int registruj_se(User arr[], int* n) {

    char newAccPass[40];
    char passConformation[40];
    char name[40];
    char email[40];
    int birthDate;
    double billState;

    printf("Unesite ime:\n");
    scanf("%s", name);
    printf("Unesite email:\n");
    scanf("%s", email);
    printf("Unesite godinu rodjenja:\n");
    scanf("%d", &birthDate);
    printf("Unesite stanje racuna:\n");
    scanf("%lf", &billState);
    printf("Unesite sifru:\n");
    scanf("%s", newAccPass);
    printf("Unesite sifru jos jednom:\n");
    scanf("%s", passConformation);

    if(strcmp(passConformation, newAccPass) != 0) {
        printf("Sifra i potvrda sifre se ne poklapaju!");
        return 0;
    }
    for(int i = 0; i < *n; i++) {
        if(strcmp(arr[i].name, name) == 0) {
            printf("User sa tim accountom vec postoji!");
            return 0;
        }
    }
    (*n)++;
    strcpy(arr[*n - 1].name, name);
    strcpy(arr[*n - 1].password, newAccPass);
    strcpy(arr[*n - 1].email, email);
    arr[*n - 1].birthDate = birthDate;
    arr[*n - 1].billState = billState;

    return 1;
}

int login(User arr[], int n, const char username[], const char password[]) {    
    for(int i = 0; i < n; i++) { 
        if(strcmp(username, arr[i].name) == 0 && strcmp(password, arr[i].password)) {
            return 1;
        }
    }
    return 0;
}

void snimi_u_fajl(User arr[], int n, const char fileName) {
    FILE* fp;
    fp = fopen(fileName, "w");
    for(int i = 0; i < n; i++) {
        fprintf(fileName, "%s\n%s\n%s\n%d\n%lf", arr[i].name, arr[i].email, arr[i].password, arr[i].billState, arr[i].birthDate);
    }
}

int main() {

    int arr[100];
    int n = ucitaj_niz_iz_fajla(arr, "korisnici.txt");

    int option;
    printf("1) Registracija\n2) Login\n3) Ispis svih Korsinika\n4) Snimanje u fajl\n");
    scanf("%d", &option);

    if(option == 1) {
        registruj_se(arr, &n);
    }
    else if(option == 2) {
        
        char name[40];
        char password[40];
        printf("Unesite ime: ");
        scanf("%s", name);
        printf("Unesite sifru: ");
        scanf("%s", password);
        if(login(arr, n, name, password) == 1) {
            printf("Uspesno ste se logovali!");
        }
    }
    else if(option == 3) {  
        ispisi_niz_korisnika(arr, n);
    }
    else if(option == 4) {
        snimi_u_fajl(arr, n, "korisnici.txt");
    }

    return 0;
}