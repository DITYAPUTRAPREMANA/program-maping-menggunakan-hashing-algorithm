// #include <stdio.h>

// int M[6][6];
// int T[6];
// int v, vn, k, m, mst;

// void inputMatriks() {
//     printf("Masukkan elemen matriks 6x6:\n");
//     for (int i = 0; i < 6; i++) {
//         for (int j = 0; j < 6; j++) {
//             scanf("%d", &M[i][j]);
//         }
//     }
// }

// int main() {
//     int p;
//     inputMatriks(); // Memanggil fungsi untuk input matriks
//     v = 0;
//     T[0] = 1;
//     mst = 0;
//     k = 1;

//     while (k <= 5) {
//         m = 999;
//         p = 0;

//         while (p <= 5) {
//             if (T[p] == 1) {
//                 for (int i = 0; i <= 5; i++) {
//                     if ((M[p][i] < m) && (M[p][i] != 0) && (T[i] != 1) && (p != i)) {
//                         m = M[p][i];
//                         v = p;
//                         vn = i;
//                     }
//                 }
//             }
//             p++;
//         }

//         printf("%d - %d\n", v, vn);
//         mst += m;
//         T[vn] = 1;
//         k++;
//     }

//     printf("Berat Minimum Spanning Tree: %d\n", mst);

//     return 0;
// }




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
    char ip[15];
    char computerName[50];
    char location[100];
} Computer;

typedef struct Node {
    Computer data;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

unsigned int hash(char* ip) {
    unsigned int value = 0;
    for (int i = 0; ip[i] != '\0'; i++) {
        value = value * 37 + ip[i];
    }
    return value % TABLE_SIZE;
}

void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

void insertComputer(Computer comp) {
    unsigned int index = hash(comp.ip);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = comp;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}


void searchData(char* ip) {
    unsigned int index = hash(ip);
    Node* temp = hashTable[index];
    while (temp) {
        if (strcmp(temp->data.ip, ip) == 0) {
            printf("Data dengan IP %s ditemukan pada index ke %d\n", ip, index);
            return;
        }
        temp = temp->next;
    }
    printf("Data dengan IP %s tidak ditemukan\n", ip);
}

void displayTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = hashTable[i];
        printf("Slot %d: ", i);
        while (temp) {
            printf("(%s, %s, %s) -> ", temp->data.ip, temp->data.computerName, temp->data.location);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void deleteComputer(char* ip) {
    unsigned int index = hash(ip);
    Node* temp = hashTable[index];
    Node* prev = NULL;
    while (temp) {
        if (strcmp(temp->data.ip, ip) == 0) {
            if (prev == NULL) {
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Data berhasil dihapus.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("IP tidak ditemukan.\n");
}

void inputComputer() {
    Computer comp;
    printf("Masukkan IP: ");
    scanf("%s", comp.ip); // Membaca IP
    getchar(); // Membersihkan buffer input setelah scanf

    printf("Masukkan Nama Komputer: ");
    fgets(comp.computerName, sizeof(comp.computerName), stdin);
    comp.computerName[strcspn(comp.computerName, "\n")] = 0; // Menghapus newline di akhir string

    printf("Masukkan Lokasi: ");
    fgets(comp.location, sizeof(comp.location), stdin);
    comp.location[strcspn(comp.location, "\n")] = 0; // Menghapus newline di akhir string

    insertComputer(comp);
    printf("Data berhasil ditambahkan.\n");
}
int main() {
    initHashTable();
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Data Komputer\n");
        printf("2. Tampilkan Data\n");
        printf("3. Search data komputer\n");
        printf("4. Hapus Data Komputer\n");
        printf("5. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputComputer();
                break;
            case 2:
                displayTable();
                break;
            case 3:
            {
                char ip[15];
                printf("Masukkan IP yang akan dicari: ");
                scanf("%s", ip);
                searchData(ip);
            }
                break;
            case 4:
                {
                    char ip[15];
                    printf("Masukkan IP yang akan dihapus: ");
                    scanf("%s", ip);
                    deleteComputer(ip);
                }
                break;
            case 5:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 5);

    return 0;
}