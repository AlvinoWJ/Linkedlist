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
    int cindyInFemaleCircle; // Penanda apakah Cindy sudah masuk ke lingkaran mahasiswi
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

void initCircle(Circle *circle)
{
    circle->last = NULL;
    circle->size = 0;
    circle->cindyInFemaleCircle = 0; // Default Cindy belum masuk
}

// Memeriksa apakah lingkaran sudah penuh
int isFull(Circle *circle)
{
    return circle->size >= MAX_CAPACITY;
}

// Memeriksa apakah nama mahasiswa sudah ada di lingkaran
int isNameExists(Circle *circle, const char *name)
{
    if (circle->last == NULL)
        return 0;

    node *curr = circle->last->next;
    do
    {
        if (strcmp(curr->name, name) == 0)
        {
            return 1; // Nama sudah ada
        }
        curr = curr->next;
    } while (curr != circle->last->next);
    return 0; // Nama tidak ada
}

// Menambahkan mahasiswa ke dalam lingkaran
void addToCircle(Circle *circle, const char *name, char gender)
{
    if (isFull(circle))
    {
        printf("Lingkaran sudah penuh. %s tidak bisa bergabung.\n", name);
        return;
    }

    if (isNameExists(circle, name))
    {
        return; // Nama sudah ada di lingkaran
    }

    // Kondisi khusus untuk Cindy
    if (strcmp(name, "Cindy") == 0 && !circle->cindyInFemaleCircle)
    {
        node *curr = circle->last ? circle->last->next : NULL;
        node *prev = NULL;
        int foundTwoFemales = 0;

        if (curr != NULL)
        {
            // Loop untuk mencari dua perempuan berurutan
            do
            {
                if (curr->gender == 'P' && curr->next->gender == 'P')
                {
                    foundTwoFemales = 1;
                    prev = curr;
                    break;
                }
                curr = curr->next;
            } while (curr != circle->last->next);
        }

        // Jika ditemukan dua perempuan, tambahkan Cindy di antaranya
        if (foundTwoFemales)
        {
            node *newNode = createNode(name, gender);
            newNode->next = prev->next;
            prev->next = newNode;
            if (prev == circle->last)
            {
                circle->last = newNode; // Jika Cindy ditempatkan di akhir lingkaran
            }
            circle->size++;
            circle->cindyInFemaleCircle = 1; // Penanda bahwa Cindy masuk lingkaran mahasiswi
        }
        else
        {
            printf("Cindy hanya ingin bergandengan dengan Perempuan.\n");
        }
        return;
    }

    // Penanganan Irsyad dan Arsyad
    if (strcmp(name, "Irsyad") == 0)
    {
        // Tambahkan Irsyad terlebih dahulu
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
        return;
    }
    else if (strcmp(name, "Arsyad") == 0)
    {
        // Tambahkan Arsyad di belakang Irsyad
        node *newNode = createNode(name, gender);

        if (circle->last != NULL)
        {
            // Tempatkan Arsyad setelah Irsyad
            node *curr = circle->last->next;
            do
            {
                if (strcmp(curr->name, "Irsyad") == 0)
                {
                    newNode->next = curr->next;
                    curr->next = newNode;
                    if (curr == circle->last)
                    {
                        circle->last = newNode; // Update last jika Arsyad ditambahkan di akhir
                    }
                    circle->size++;
                    return;
                }
                curr = curr->next;
            } while (curr != circle->last->next);
        }
    }

    // Penambahan normal jika bukan Cindy, Irsyad, atau Arsyad
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
    printf("NULL\n"); // Menandakan akhir dari lingkaran
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
        // Menambahkan ke lingkaran mahasiswa atau mahasiswi tanpa mengubah node
        if (curr->gender == 'L')
        {
            if (!isNameExists(maleCircle, curr->name))
                addToCircle(maleCircle, curr->name, curr->gender);
        }
        else
        {
            if (!isNameExists(femaleCircle, curr->name))
                addToCircle(femaleCircle, curr->name, curr->gender);
        }
        curr = curr->next;
    } while (curr != mainCircle->last->next);
}

// Menggabungkan lingkaran mahasiswa dan mahasiswi menjadi satu lingkaran besar
void mergeCircles(Circle *mainCircle, Circle *bigCircle)
{
    if (mainCircle->last == NULL)
    {
        printf("Lingkaran utama kosong.\n");
        return;
    }

    node *curr = mainCircle->last->next;

    // Pertama, tambahkan semua mahasiswa dan mahasiswi ke bigCircle
    do
    {
        if (!isFull(bigCircle) && !isNameExists(bigCircle, curr->name))
        {
            // Hanya tambahkan Cindy jika dia belum ada di lingkaran besar
            if (strcmp(curr->name, "Cindy") != 0)
            {
                addToCircle(bigCircle, curr->name, curr->gender);
            }
        }
        curr = curr->next;
    } while (curr != mainCircle->last->next);

    // Jika Cindy sudah masuk lingkaran mahasiswi dan belum ada di lingkaran besar, tambahkan Cindy ke lingkaran besar
    if (mainCircle->cindyInFemaleCircle && !isNameExists(bigCircle, "Cindy"))
    {
        addToCircle(bigCircle, "Cindy", 'P'); // Tambahkan Cindy ke lingkaran besar
    }
}

// Program utama
int main()
{
    Circle mainCircle, maleCircle, femaleCircle, bigCircle;
    initCircle(&mainCircle);
    initCircle(&maleCircle);
    initCircle(&femaleCircle);
    initCircle(&bigCircle);

    int option;
    char name[50];
    char gender;

    while (1)
    {
        printf("\n=== Menu ===\n");
        printf("1. Tambahkan mahasiswa\n");
        printf("2. Hapus mahasiswa\n");
        printf("3. Tampilkan lingkaran mahasiswa dan mahasiswi\n");
        printf("4. Tampilkan lingkaran besar\n");
        printf("5. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Masukkan nama mahasiswa: ");
            scanf("%s", name);
            printf("Masukkan jenis kelamin (L untuk laki-laki, P untuk perempuan): ");
            scanf(" %c", &gender);
            addToCircle(&mainCircle, name, gender);
            break;
        case 2:
            printf("Masukkan nama mahasiswa yang akan dihapus: ");
            scanf("%s", name);
            removeFromCircle(&mainCircle, name);
            break;
        case 3:
            initCircle(&maleCircle);
            initCircle(&femaleCircle);
            createTwoCircles(&mainCircle, &maleCircle, &femaleCircle);
            printf("Lingkaran mahasiswa:\n");
            displayCircle(&maleCircle);
            printf("Lingkaran mahasiswi:\n");
            displayCircle(&femaleCircle);
            break;
        case 4:
            initCircle(&bigCircle);                // Mengosongkan lingkaran besar sebelum penggabungan
            mergeCircles(&mainCircle, &bigCircle); // Hanya menggunakan 2 argumen
            printf("Lingkaran besar:\n");
            displayCircle(&bigCircle);
            break;

        case 5:
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
