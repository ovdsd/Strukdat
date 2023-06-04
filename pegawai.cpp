/*
Nama program: matriks.cpp
Anggota:
- Muhammad Calvin (140810220061)
- Muhammad Is'ad (140810220065)
- Robert William (140810220087)

Tanggal mengerjakan:04-06-2023
Deskripsi: Multilist Divisi, Pegawai, Anak
*/

#include <iostream>
using namespace std;

struct Anak {
    string namaAnak;
    Anak* nextAnak;
};

struct Pegawai {
    string namaPegawai;
    string jabatan;
    Pegawai* nextPegawai;
    Anak* listAnak;
};

struct Divisi {
    string namaDivisi;
    Pegawai* listPegawai;
    Divisi* nextDivisi;
};

using pointerPeg = Pegawai*;
using pointerDivisi = Divisi*;
using pointerAnak = Anak*;

// Membuat list divisi baru
void createListDiv(pointerDivisi& First) {
    First = NULL;
}

void createElementPeg(pointerPeg& pBaru) {
    pBaru = new Pegawai;
    cout << "Masukkan nama pegawai: ";
    cin >> pBaru->namaPegawai;
    pBaru->nextPegawai = NULL;
    pBaru->listAnak = NULL;
}

void createElementAnak(pointerAnak& pBaru) {
    pBaru = new Anak;
    cout << "Masukkan nama anak: ";
    cin >> pBaru->namaAnak;
    pBaru->nextAnak = NULL;
}

void traversalPeg(pointerPeg First) {
    if (First == NULL) {
        cout << "Tidak ada pegawai dalam divisi ini." << endl;
    } else {
        pointerPeg p = First;
        cout << "Daftar pegawai dalam divisi:" << endl;
        while (p != NULL) {
            cout << "- " << p->namaPegawai << endl;
            p = p->nextPegawai;
        }
    }
}

void linearSearch(pointerPeg First, string key, int& status, pointerPeg& pCari) {
    status = 0;  // status = 0 berarti tidak ditemukan
    pCari = First;
    while (pCari != NULL) {
        if (pCari->namaPegawai == key) {
            status = 1;  // status = 1 berarti ditemukan
            break;
        }
        pCari = pCari->nextPegawai;
    }
}

void insertFirstPeg(pointerPeg& First, pointerPeg pBaru) {
    if (First == NULL) {
        First = pBaru;
    } else {
        pBaru->nextPegawai = First;
        First = pBaru;
    }
}

void deleteFirstPeg(pointerPeg& First, pointerPeg& pHapus) {
    if (First == NULL) {
        pHapus = NULL;
        cout << "Tidak ada pegawai dalam divisi ini." << endl;
    } else if (First->nextPegawai == NULL) {
        pHapus = First;
        First = NULL;
    } else {
        pHapus = First;
        First = First->nextPegawai;
        pHapus->nextPegawai = NULL;
    }
}

void insertFirstAnak(pointerPeg& First, string key, pointerAnak pBaru) {
    pointerPeg pCari;
    int status;
    linearSearch(First, key, status, pCari);
    if (status == 1) {
        if (pCari->listAnak == NULL) {
            pCari->listAnak = pBaru;
        } else {
            pBaru->nextAnak = pCari->listAnak;
            pCari->listAnak = pBaru;
        }
        cout << "Anak berhasil ditambahkan." << endl;
    } else {
        cout << "Pegawai tidak ditemukan." << endl;
    }
}

void deleteFirstAnak(pointerPeg& First, string key, pointerAnak& pHapus) {
    pointerPeg pCari;
    int status;
    linearSearch(First, key, status, pCari);
    if (status == 1) {
        if (pCari->listAnak == NULL) {
            pHapus = NULL;
            cout << "Pegawai tidak memiliki anak." << endl;
        } else if (pCari->listAnak->nextAnak == NULL) {
            pHapus = pCari->listAnak;
            pCari->listAnak = NULL;
        } else {
            pHapus = pCari->listAnak;
            pCari->listAnak = pCari->listAnak->nextAnak;
            pHapus->nextAnak = NULL;
        }
        cout << "Anak berhasil dihapus." << endl;
    } else {
        cout << "Pegawai tidak ditemukan." << endl;
    }
}

void traversalOrtuAnak(pointerDivisi First) {
    pointerDivisi pDivisi = First;

    while (pDivisi != NULL) {
        cout << "Divisi: " << pDivisi->namaDivisi << endl;

        pointerPeg pPegawai = pDivisi->listPegawai;

        while (pPegawai != NULL) {
            cout << "  Pegawai: " << pPegawai->namaPegawai << endl;

            pointerAnak pAnak = pPegawai->listAnak;

            while (pAnak != NULL) {
                cout << "    Anak: " << pAnak->namaAnak << endl;
                pAnak = pAnak->nextAnak;
            }

            pPegawai = pPegawai->nextPegawai;
        }

        pDivisi = pDivisi->nextDivisi;
    }
}

void insertDivisi(pointerDivisi& First, const string& namaDivisi) {
    pointerDivisi pBaru = new Divisi;
    pBaru->namaDivisi = namaDivisi;
    pBaru->listPegawai = NULL;
    pBaru->nextDivisi = NULL;

    if (First == NULL) {
        First = pBaru;
    } else {
        pointerDivisi lastDivisi = First;
        while (lastDivisi->nextDivisi != NULL) {
            lastDivisi = lastDivisi->nextDivisi;
        }

        lastDivisi->nextDivisi = pBaru;
    }
}

void insertPegawai(pointerDivisi& First, const string& namaDivisi, pointerPeg pegawai) {
    pointerDivisi pDivisi = First;

    while (pDivisi != NULL) {
        if (pDivisi->namaDivisi == namaDivisi) {
            pegawai->nextPegawai = pDivisi->listPegawai;
            pDivisi->listPegawai = pegawai;
            break;
        }

        pDivisi = pDivisi->nextDivisi;
    }
}

void insertAnak(pointerDivisi& First, const string& namaPegawai, pointerAnak anak) {
    pointerDivisi pDivisi = First;

    while (pDivisi != NULL) {
        pointerPeg pPegawai = pDivisi->listPegawai;

        while (pPegawai != NULL) {
            if (pPegawai->namaPegawai == namaPegawai) {
                if (pPegawai->listAnak == NULL) {
                    pPegawai->listAnak = anak;
                } else {
                    anak->nextAnak = pPegawai->listAnak;
                    pPegawai->listAnak = anak;
                }
                break;
            }

            pPegawai = pPegawai->nextPegawai;
        }

        pDivisi = pDivisi->nextDivisi;
    }
}

void showMenu() {
    cout << "======== MENU ========" << endl;
    cout << "1. Tambah Divisi" << endl;
    cout << "2. Tambah Pegawai ke Divisi" << endl;
    cout << "3. Tambah Anak ke Pegawai" << endl;
    cout << "4. Tampilkan Orang Tua dan Anak" << endl;
    cout << "5. Keluar" << endl;
    cout << "======================" << endl;
    cout << "Pilihan: ";
}

int main() {
    pointerDivisi divisi = NULL;
    int pilihan = 0;
    string namaDivisi;
    string namaPegawai;
    string namaAnak;

    do {
        showMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                cout << "Nama Divisi: ";
                cin >> namaDivisi;
                insertDivisi(divisi, namaDivisi);
                cout << "Divisi " << namaDivisi << " ditambahkan." << endl;
                break;
            }
            case 2: {
                cout << "Nama Divisi: ";
                cin >> namaDivisi;
                cout << "Nama Pegawai: ";
                cin >> namaPegawai;
                pointerPeg pegawai = new Pegawai;
                pegawai->namaPegawai = namaPegawai;
                pegawai->listAnak = NULL;
                pegawai->nextPegawai = NULL;
                insertPegawai(divisi, namaDivisi, pegawai);
                cout << "Pegawai " << namaPegawai << " ditambahkan ke Divisi " << namaDivisi << "." << endl;
                break;
            }
            case 3: {
                cout << "Nama Pegawai: ";
                cin >> namaPegawai;
                cout << "Nama Anak: ";
                cin >> namaAnak;
                pointerAnak anak = new Anak;
                anak->namaAnak = namaAnak;
                anak->nextAnak = NULL;
                insertAnak(divisi, namaPegawai, anak);
                cout << "Anak " << namaAnak << " ditambahkan pada Pegawai " << namaPegawai << "." << endl;
                break;
            }
            case 4: {
                traversalOrtuAnak(divisi);
                break;
            }
            case 5: {
                cout << "Terima kasih. Program selesai." << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid." << endl;
                break;
            }
        }

        cout << endl;

    } while (pilihan != 5);

    return 0;
}