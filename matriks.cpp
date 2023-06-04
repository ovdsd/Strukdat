/*
Nama program: matriks.cpp
Anggota:
- Muhammad Calvin (140810220061)
- Muhammad Is'ad (140810220065)
- Robert William (140810220087)

Tanggal mengerjakan:04-06-2023
Deskripsi: penjumlahan matriks sparse
*/

#include <iostream>
using namespace std;

struct elmtNode {
    int value;
    int column;
    int row;
    elmtNode* right;
    elmtNode* down;
};

struct headerNode {
    int index;
    headerNode* down;
    headerNode* right;
    elmtNode* next;
};

headerNode* create_header(int index) {
    headerNode* newNode = new headerNode;
    newNode->index = index;
    newNode->down = NULL;
    newNode->right = NULL;
    newNode->next = NULL;
    return newNode;
}

elmtNode* create_elmt(int row, int column, int value) {
    elmtNode* newNode = new elmtNode;
    newNode->row = row;
    newNode->column = column;
    newNode->value = value;
    newNode->right = NULL;
    newNode->down = NULL;
    return newNode;
}

void insertElement(headerNode* headerrow[], headerNode* headercolumn[], int row, int column, int value) {
    elmtNode* newNode = create_elmt(row, column, value);

    if (headerrow[row]->next == NULL || headercolumn[column]->next == NULL) {
        headerrow[row]->next = newNode;
        headercolumn[column]->next = newNode;
    } else {
        elmtNode* pBantu = headerrow[row]->next;
        while (pBantu->right != NULL) {
            pBantu = pBantu->right;
        }
        pBantu->right = newNode;
    }

    elmtNode* pBantu = headercolumn[column]->next;
    while (pBantu->down != NULL) {
        pBantu = pBantu->down;
    }
    pBantu->down = newNode;
}

void batasHorizontal(int jumlahColumn) {
    for (int i = 0; i < jumlahColumn * 5; i++) {
        cout << "-";
    }
    cout << endl;
}

void tampilkan(headerNode* headerrow[], headerNode* headercolumn[], int jumlahRow, int jumlahColumn) {
    batasHorizontal(jumlahColumn);

    for (int i = 0; i < jumlahRow; i++) {
        elmtNode* pBantu = headerrow[i]->next;
        cout << "| ";
        for (int j = 0; j < jumlahColumn; j++) {
            if (pBantu != NULL && pBantu->column == j) {
                cout << pBantu->value << " | ";
                pBantu = pBantu->right;
            } else {
                cout << "0 | ";
            }
        }
        cout << endl;
        batasHorizontal(jumlahColumn);
    }
}



void addMatriks(headerNode* headerrow1[], headerNode* headercolumn1[], headerNode* headerrow2[], headerNode* headercolumn2[], int jumlahRow, int jumlahColumn) {
    headerNode* headercolumnHasil[jumlahColumn];
    headerNode* headerrowHasil[jumlahRow];
    for (int i = 0; i < jumlahRow; i++) {
        headerrowHasil[i] = create_header(i);
    }

    for (int i = 0; i < jumlahColumn; i++) {
        headercolumnHasil[i] = create_header(i);
    }

    for (int i = 0; i < jumlahRow; i++) {
        elmtNode* pBantu1 = headerrow1[i]->next;
        elmtNode* pBantu2 = headerrow2[i]->next;
        while (pBantu1 != NULL || pBantu2 != NULL) {
            int row, column, value;

            if (pBantu1 == NULL) {
                row = pBantu2->row;
                column = pBantu2->column;
                value = pBantu2->value;
                pBantu2 = pBantu2->right;
            } else if (pBantu2 == NULL) {
                row = pBantu1->row;
                column = pBantu1->column;
                value = pBantu1->value;
                pBantu1 = pBantu1->right;
            } else {
                if (pBantu1->column < pBantu2->column) {
                    row = pBantu1->row;
                    column = pBantu1->column;
                    value = pBantu1->value;
                    pBantu1 = pBantu1->right;
                } else if (pBantu2->column < pBantu1->column) {
                    row = pBantu2->row;
                    column = pBantu2->column;
                    value = pBantu2->value;
                    pBantu2 = pBantu2->right;
                } else {
                    row = pBantu1->row;
                    column = pBantu1->column;
                    value = pBantu1->value + pBantu2->value;
                    pBantu1 = pBantu1->right;
                    pBantu2 = pBantu2->right;
                }
            }

            insertElement(headerrowHasil, headercolumnHasil, row, column, value);
        }
    }
    cout << "Hasil penjumlahan:" << endl;
    tampilkan(headerrowHasil, headercolumnHasil, jumlahRow, jumlahColumn);
}

int main() {
    int jumlahValue;
    int jumlahColumn;
    int jumlahRow;

    cout << "Masukkan jumlah row dan column: ";
    cin >> jumlahRow >> jumlahColumn;
    cout << endl;
    cout << "Masukkan banyak value matriks 1: ";
    cin >> jumlahValue;

    headerNode* headerrow1[jumlahRow];
    headerNode* headercolumn1[jumlahColumn];
    for (int i = 0; i < jumlahRow; i++) {
        headerrow1[i] = create_header(i);
    }
    for (int i = 0; i < jumlahColumn; i++) {
        headercolumn1[i] = create_header(i);
    }

    cout << "Masukkan elemen matriks 1:" << endl;
    for (int i = 0; i < jumlahValue; i++) {
        int row, column, value;
        cout << "Masukkan posisi row, column, dan value elemen ke-" << i+1 << ": ";
        cin >> row >> column >> value;
        insertElement(headerrow1, headercolumn1, row, column, value);
    }

    cout << "Masukkan banyak value matriks 2: ";
    cin >> jumlahValue;

    headerNode* headerrow2[jumlahRow];
    headerNode* headercolumn2[jumlahColumn];
    for (int i = 0; i < jumlahRow; i++) {
        headerrow2[i] = create_header(i);
    }
    for (int i = 0; i < jumlahColumn; i++) {
        headercolumn2[i] = create_header(i);
    }

    cout << "Masukkan elemen matriks 2:" << endl;
    for (int i = 0; i < jumlahValue; i++) {
        int row, column, value;
        cout << "Masukkan posisi row, column, dan value elemen ke-" << i+1 << ": ";
        cin >> row >> column >> value;
        insertElement(headerrow2, headercolumn2, row, column, value);
    }

    cout << "\nMatriks 1:" << endl;
    tampilkan(headerrow1, headercolumn1, jumlahRow, jumlahColumn);
    cout << endl;

    cout << "Matriks 2:" << endl;
    tampilkan(headerrow2, headercolumn2, jumlahRow, jumlahColumn);
    cout << endl;

    addMatriks(headerrow1, headercolumn1, headerrow2, headercolumn2, jumlahRow, jumlahColumn);

    return 0;
}
