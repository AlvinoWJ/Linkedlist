#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 20

// Struktur Node untuk lingkaran
typedef struct node
{
    char name[50];
    char gender; // 'L' untuk laki-laki, 'P' untuk perempuan
    struct node *next;
} node;

// Struktur Circular Linked List
typedef struct Circle
{
    node *last;
    int size;
} Circle;

// Fungsi untuk membuat node baru
node *createNode(const char *name, char gender)
{
    node *newNode = (node *)malloc(sizeof(node));
    strcpy(newNode->name, name);
    newNode->gender = gender;
    newNode->next = NULL;
    return newNode;
}

// Inisialisasi lingkaran
void initCircle(Circle *circle)
{
    circle->last = NULL;
    circle->size = 0;
}

// Memeriksa apakah lingkaran sudah penuh
int isFull(Circle *circle)
{
    return circle->size >= MAX_CAPACITY;
}

// Menambahkan mahasiswa ke dalam lingkaran
void addToCircle(Circle *circle, const char *name, char gender)
{
    if (isFull(circle))
    {
        printf("Lingkaran sudah penuh. %s tidak bisa bergabung.\n", name);
        return;
    }

    if (strcmp(name, "Cindy") == 0)
    {
        node *curr = circle->last ? circle->last->next : NULL;
        int hasMale = 0;
        do
        {
            if (curr != NULL && curr->gender == 'L')
            {
                hasMale = 1;
                break;
            }
            curr = curr->next;
        } while (curr != circle->last->next);
        if (hasMale)
        {
            printf("Cindy tidak ingin bergabung karena ada mahasiswa laki-laki.\n");
            return;
        }
    }

    node *newNode = createNode(name, gender);

    if (circle->last == NULL)
    { // Lingkaran kosong
        circle->last = newNode;
        circle->last->next = newNode;
    }
    else
    {
        newNode->next = circle->last->next;
        circle->last->next = newNode;
        circle->last = newNode;
    }

    circle->size++;
    printf("%s berhasil masuk ke lingkaran.\n", name);
}

// Mengeluarkan mahasiswa dari lingkaran
void removeFromCircle(Circle *circle, const char *name)
{
    if (circle->last == NULL)
    {
        printf("Lingkaran kosong. %s tidak ditemukan.\n", name);
        return;
    }

    node *curr = circle->last->next;
    node *prev = circle->last;

    do
    {
        if (strcmp(curr->name, name) == 0)
        {
            if (curr == circle->last)
            {
                if (circle->size == 1)
                {
                    circle->last = NULL;
                }
                else
                {
                    prev->next = curr->next;
                    circle->last = prev;
                }
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            circle->size--;
            printf("%s telah keluar dari lingkaran.\n", name);
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != circle->last->next);

    printf("%s tidak ditemukan dalam lingkaran.\n", name);
}

// Menampilkan isi lingkaran
void displayCircle(Circle *circle)
{
    if (circle->last == NULL)
    {
        printf("Lingkaran kosong.\n");
        return;
    }

    node *curr = circle->last->next;
    do
    {
        printf("%s (%s) -> ", curr->name, (curr->gender == 'L') ? "Laki-laki" : "Perempuan");
        curr = curr->next;
    } while (curr != circle->last->next);
    printf("\n");
}

// Membagi lingkaran menjadi lingkaran mahasiswa dan mahasiswi
void createTwoCircles(Circle *mainCircle, Circle *maleCircle, Circle *femaleCircle)
{
    if (mainCircle->last == NULL)
    {
        printf("Lingkaran utama kosong.\n");
        return;
    }

    node *curr = mainCircle->last->next;
    do
    {
        if (curr->gender == 'L')
        {
            addToCircle(maleCircle, curr->name, curr->gender);
        }
        else
        {
            addToCircle(femaleCircle, curr->name, curr->gender);
        }
        curr = curr->next;
    } while (curr != mainCircle->last->next);
}

// Program utama
int main()
{
    Circle mainCircle, maleCircle, femaleCircle;
    initCircle(&mainCircle);
    initCircle(&maleCircle);
    initCircle(&femaleCircle);

    int option;
    char name[50];
    char gender;

    while (1)
    {
        printf("\n=== Menu ===\n");
        printf("1. Tambahkan mahasiswa\n");
        printf("2. Hapus mahasiswa\n");
        printf("3. Tampilkan lingkaran mahasiswa dan mahasiswi\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Masukkan nama mahasiswa: ");
            scanf("%s", name);
            if (strcmp(name, "Irsyad") == 0 || strcmp(name, "Arsyad") == 0)
            {
                addToCircle(&mainCircle, "Irsyad", 'L');
                addToCircle(&mainCircle, "Arsyad", 'L');
            }
            else
            {
                printf("Masukkan jenis kelamin (L untuk laki-laki, P untuk perempuan): ");
                scanf(" %c", &gender);
                addToCircle(&mainCircle, name, gender);
            }
            break;
        case 2:
            printf("Masukkan nama mahasiswa yang akan dihapus: ");
            scanf("%s", name);
            removeFromCircle(&mainCircle, name);
            break;
        case 3:
            createTwoCircles(&mainCircle, &maleCircle, &femaleCircle);
            printf("Lingkaran mahasiswa:\n");
            displayCircle(&maleCircle);
            printf("Lingkaran mahasiswi:\n");
            displayCircle(&femaleCircle);
            break;
        case 4:
            printf("Keluar dari program.\n");
            exit(0);
        default:
            printf("Opsi tidak valid. Silakan coba lagi.\n");
        }

        printf("\nTekan Enter untuk melanjutkan...");
        getchar(); // Menghapus newline dari buffer
        getchar(); // Menunggu input dari pengguna
    }

    return 0;
}
