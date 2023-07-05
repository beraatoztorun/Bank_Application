#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char isim[50];
    int hesapNumarasi;
    float bakiye;
} Kullanici;

void kullaniciKaydet(Kullanici kullanici) {
    FILE *dosya = fopen("kullanici_verileri.txt", "a");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    fprintf(dosya, "%s %d %.2f\n", kullanici.isim, kullanici.hesapNumarasi, kullanici.bakiye);
    fclose(dosya);
}

void kullaniciGuncelle(int hesapNumarasi, float yeniBakiye) {
    FILE *dosya = fopen("kullanici_verileri.txt", "r+");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    int bulundu = 0;
    char isim[50];
    int hesap;
    float bakiye;

    while (fscanf(dosya, "%s %d %f", isim, &hesap, &bakiye) != EOF) {
        if (hesap == hesapNumarasi) {
            fseek(dosya, -strlen(isim) - sizeof(hesap) - sizeof(bakiye), SEEK_CUR);
            fprintf(dosya, "%s %d %.2f\n", isim, hesap, yeniBakiye);
            bulundu = 1;
            break;
        }
    }

    if (!bulundu) {
        printf("Hesap bulunamadi!\n");
    } else {
        printf("Hesap guncellendi!\n");
    }

    fclose(dosya);
}

void hesapSil(int hesapNumarasi) {
    FILE *dosya = fopen("kullanici_verileri.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    FILE *tempDosya = fopen("gecici_dosya.txt", "w");
    if (tempDosya == NULL) {
        printf("Gecici dosya olusturulamadi!\n");
        fclose(dosya);
        return;
    }

    int bulundu = 0;
    char isim[50];
    int hesap;
    float bakiye;

    while (fscanf(dosya, "%s %d %f", isim, &hesap, &bakiye) != EOF) {
        if (hesap != hesapNumarasi) {
            fprintf(tempDosya, "%s %d %.2f\n", isim, hesap, bakiye);
        } else {
            bulundu = 1;
        }
    }

    fclose(dosya);
    fclose(tempDosya);

    if (!bulundu) {
        printf("Hesap bulunamadi!\n");
        remove("gecici_dosya.txt");
    } else {
        remove("kullanici_verileri.txt");
        rename("gecici_dosya.txt", "kullanici_verileri.txt");
        printf("Hesap silindi!\n");
    }
}

void hesapBilgisiGoster(int hesapNumarasi) {
    FILE *dosya = fopen("kullanici_verileri.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    int bulundu = 0;
    char isim[50];
    int hesap;
    float bakiye;

    while (fscanf(dosya, "%s %d %f", isim, &hesap, &bakiye) != EOF) {
        if (hesap == hesapNumarasi) {
            printf("Isim: %s\nHesap Numarasi: %d\nBakiye: %.2f\n", isim, hesap, bakiye);
            bulundu = 1;
            break;
        }
    }

    if (!bulundu) {
        printf("Hesap bulunamadi!\n");
    }

    fclose(dosya);
}

void paraYatir(int hesapNumarasi, float miktar) {
    FILE *dosya = fopen("kullanici_verileri.txt", "r+");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    int bulundu = 0;
    char isim[50];
    int hesap;
    float bakiye;

    while (fscanf(dosya, "%s %d %f", isim, &hesap, &bakiye) != EOF) {
        if (hesap == hesapNumarasi) {
            fseek(dosya, -strlen(isim) - sizeof(hesap) - sizeof(bakiye), SEEK_CUR);
            fprintf(dosya, "%s %d %.2f\n", isim, hesap, bakiye + miktar);
            bulundu = 1;
            break;
        }
    }

    if (!bulundu) {
        printf("Hesap bulunamadi!\n");
    } else {
        printf("Para yatirildi!\n");
    }

    fclose(dosya);
}

void paraCek(int hesapNumarasi, float miktar) {
    FILE *dosya = fopen("kullanici_verileri.txt", "r+");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    int bulundu = 0;
    char isim[50];
    int hesap;
    float bakiye;

    while (fscanf(dosya, "%s %d %f", isim, &hesap, &bakiye) != EOF) {
        if (hesap == hesapNumarasi) {
            if (bakiye >= miktar) {
                fseek(dosya, -strlen(isim) - sizeof(hesap) - sizeof(bakiye), SEEK_CUR);
                fprintf(dosya, "%s %d %.2f\n", isim, hesap, bakiye - miktar);
                bulundu = 1;
                printf("Para cekildi!\n");
            } else {
                printf("Yetersiz bakiye!\n");
            }
            break;
        }
    }

    if (!bulundu) {
        printf("Hesap bulunamadi!\n");
    }

    fclose(dosya);
}

int main() {
    int secim;
    int hesapNumarasi;
    float miktar;
    Kullanici kullanici;

    printf("1- Yeni Hesap Olustur\n2- Hesap Guncelle\n3- Hesap Sil\n4- Hesap Bilgisi Goruntule\n5- Para Yatir\n6- Para Cek\n0- Cikis\n");

    do {
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("Isim: ");
                getchar(); // �nceki \n karakterini oku
                fgets(kullanici.isim, sizeof(kullanici.isim), stdin);
                kullanici.isim[strlen(kullanici.isim) - 1] = '\0'; // Son \n karakterini kald�r
                printf("Hesap Numarasi: ");
                scanf("%d", &kullanici.hesapNumarasi);
                printf("Baslangic Bakiyesi: ");
                scanf("%f", &kullanici.bakiye);
                kullaniciKaydet(kullanici);
                printf("Hesap olusturuldu!\n");
                break;
            case 2:
                printf("Hesap Numarasi: ");
                scanf("%d", &hesapNumarasi);
                printf("Yeni Bakiye: ");
                scanf("%f", &miktar);
                kullaniciGuncelle(hesapNumarasi, miktar);
                break;
            case 3:
                printf("Hesap Numarasi: ");
                scanf("%d", &hesapNumarasi);
                hesapSil(hesapNumarasi);
                break;
            case 4:
                printf("Hesap Numarasi: ");
                scanf("%d", &hesapNumarasi);
                hesapBilgisiGoster(hesapNumarasi);
                break;
            case 5:
                printf("Hesap Numarasi: ");
                scanf("%d", &hesapNumarasi);
                printf("Yatirilacak Miktar: ");
                scanf("%f", &miktar);
                paraYatir(hesapNumarasi, miktar);
                break;
            case 6:
                printf("Hesap Numarasi: ");
                scanf("%d", &hesapNumarasi);
                printf("Cekilecek Miktar: ");
                scanf("%f", &miktar);
                paraCek(hesapNumarasi, miktar);
                break;
            case 0:
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
                break;
        }
    } while (secim != 0);

    return 0;
}

