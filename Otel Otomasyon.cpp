/* ELÝF ELÇÝN PARTÝGÖÇ
2212721059
OTEL REZERVASYON OTOMASYONU*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>

using namespace std;

struct Oda {
    char odaNo[10];
    char odaTipi[20];
    bool dolulukDurumu; 
    double fiyat;
};
void anaMenu();
void odaEkle();
void odaListele();
void odaArama();
void odaSil();
void odaDuzenle();
void odalariDosyayaYaz();

Oda oda;

int main() {
    char secim;
    do {
        anaMenu();
        secim = getche();
        cout << endl;

        switch (secim) {
            case '1':
                odaEkle();
                break;
            case '2':
                odaListele();
                break;
            case '3':
                odaArama();
                break;
            case '4':
                odaSil();
                break;
            case '5':
                odaDuzenle();
                break;
            case '6':
                cout << "Cikis yapiliyor" << endl;
                break;
            default:
                cout << "Gecersiz bir secim!" << endl;
        }
    } while (secim != '6');

    return 0;
}

void anaMenu() {
    cout << "|-------Otel Otomasyonu------|" << endl;
    cout << "|     1- Oda Ekle            |" << endl;
    cout << "|     2- Oda Listele         |" << endl;
    cout << "|     3- Oda Arama           |" << endl;
    cout << "|     4- Oda Sil             |" << endl;
    cout << "|     5- Oda Duzenle         |" << endl;
    cout << "|     6- Cikis               |" << endl;
    cout << "|----------------------------|" << endl;
    cout << "Seciminizi yapiniz: ";
}

void odaEkle() {
    ofstream yaz("oda.dat", ios::binary | ios::app);

    cout << "Oda Numarasini Giriniz: ";
    cin >> oda.odaNo;
    cout << "Oda Tipini Giriniz (Standart/Luks/Vip/Balayi): ";
    cin >> oda.odaTipi;
    cout << "Oda Fiyatini Giriniz: ";
    cin >> oda.fiyat;
    cout << "Odanin doluluk durumunu giriniz (0: Bos, 1: Dolu): ";
    cin >> oda.dolulukDurumu;

    yaz.write((char*)&oda, sizeof(oda));
    cout << "Oda ile ilgili kayit eklendi!" << endl;
    yaz.close();
}

void odaListele() {
    ifstream oku("oda.dat", ios::binary);

    if (!oku) {
        cout << "Oda kaydi bulunamadi!" << endl;
        return;
    }

    int i = 1;
    while (oku.read((char*)&oda, sizeof(oda))) {
        cout << "Oda No: " << oda.odaNo << endl;
        cout << "Oda Tipi: " << oda.odaTipi << endl;
        cout << "Oda Fiyati: " << oda.fiyat << endl;
        cout << "Doluluk Durumu: " << (oda.dolulukDurumu ? "Dolu" : "Bos") << endl;
        cout << "------------------------------" << endl;
        i++;
    }
    oku.close();
}

void odaArama() {
    ifstream oku("oda.dat", ios::binary);

    if (!oku) {
        cout << "Oda kaydi bulunamadi!" << endl;
        return;
    }

    char arananOdaNo[10];
    cout << "Istediginiz oda numarasini giriniz: ";
    cin >> arananOdaNo;

    bool bulundu = false;
    while (oku.read((char*)&oda, sizeof(oda))) {
        if (strcmp(oda.odaNo, arananOdaNo) == 0) {
            cout << "Oda Bulundu!" << endl;
            cout << "Oda No: " << oda.odaNo << endl;
            cout << "Oda Tipi: " << oda.odaTipi << endl;
            cout << "Oda Fiyati: " << oda.fiyat << endl;
            cout << "Doluluk Durumu: " << (oda.dolulukDurumu ? "Dolu" : "Bos") << endl;
            bulundu = true;
            break;
        }
    }

    if (!bulundu) {
        cout << "Aradiginiz oda bulunamadi!" << endl;
    }
    oku.close();
}

void odaSil() {
    ifstream oku("oda.dat", ios::binary);
    ofstream yedek("yedek.dat", ios::binary);

    if (!oku) {
        cout << "Oda kaydi bulunamadi!" << endl;
        return;
    }

    char silinecekOdaNo[10];
    cout << "Silmek istediginiz oda numarasini giriniz: ";
    cin >> silinecekOdaNo;

    bool bulundu = false;
    while (oku.read((char*)&oda, sizeof(oda))) {
        if (strcmp(oda.odaNo, silinecekOdaNo) != 0) {
            yedek.write((char*)&oda, sizeof(oda));
        } else {
            bulundu = true;
        }
    }

    oku.close();
    yedek.close();

    if (bulundu) {
        remove("oda.dat");
        rename("yedek.dat", "oda.dat");
        cout << "Oda basariyla silindi!" << endl;
    } else {
        remove("yedek.dat");
        cout << "Oda bulunamadi!" << endl;
    }
}

void odaDuzenle() {
    ifstream oku("oda.dat", ios::binary);
    ofstream yedek("yedek.dat", ios::binary);

    if (!oku) {
        cout << "Oda kaydi bulunamadi!" << endl;
        return;
    }

    char duzenlenecekOdaNo[10];
    cout << "Duzeltmek istediginiz oda numarasini giriniz: ";
    cin >> duzenlenecekOdaNo;

    bool bulundu = false;
    while (oku.read((char*)&oda, sizeof(oda))) {
        if (strcmp(oda.odaNo, duzenlenecekOdaNo) == 0) {
            cout << "Oda bulundu! Yeni bilgileri giriniz." << endl;
            cout << "Yeni Oda Numarasini Giriniz: ";
            cin >> oda.odaNo;
            cout << "Yeni Oda Tipini Giriniz (Standart/Luks/Vip/Balayi): ";
            cin >> oda.odaTipi;
            cout << "Yeni Oda Fiyatini Giriniz: ";
            cin >> oda.fiyat;
            cout << "Yeni Oda doluluk durumunu giriniz (0: Bos, 1: Dolu): ";
            cin >> oda.dolulukDurumu;
            bulundu = true;
        }
        yedek.write((char*)&oda, sizeof(oda));
    }
    oku.close();
    yedek.close();

    if (bulundu) {
        remove("oda.dat");
        rename("yedek.dat", "oda.dat");
        cout << "Oda bilgileri basariyla duzeltildi!" << endl;
    } else {
        remove("yedek.dat");
        cout << "Oda bulunamadi!" << endl;
    }
}
