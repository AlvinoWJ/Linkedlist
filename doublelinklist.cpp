#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Node struct untuk double linked list
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahData(node **head);
void tambahakhir(node **head);
void hapusawal(node **head);
void hapustengah(node **head);
void hapusakhir(node **head);
void tranverse(node *head);
void tranverseReverse(node *head);
int caridata(node *head);
int jumlahdata(node *head);
int totaldata(node *head);

//========================================================

int main()
{
    node *head;
    char pilih;
    int hasil, jumlah, total;

    head = NULL;
    do
    {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. tambah data di awal\n");
        printf("2. tambah data di tengah list\n");
        printf("3. tambah data di akhir list\n");
        printf("4. hapus data di awal list\n");
        printf("5. hapus data di tengah list\n");
        printf("6. hapus data di akhir list\n");
        printf("7. cetak isi list (depan ke belakang)\n");
        printf("8. cetak isi list (belakang ke depan)\n"); // Tambahan baru
        printf("9. cari data di list\n");
        printf("0. jumlah data di list\n");
        printf("a. total seluruh data di list\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);
        fflush(stdin);

        if (pilih == '1')
        {
            tambahAwal(&head);
            getchar();
        }
        else if (pilih == '2')
        {
            tambahData(&head);
            getchar();
        }
        else if (pilih == '3')
        {
            tambahakhir(&head);
            getchar();
        }
        else if (pilih == '4')
        {
            hapusawal(&head);
            getchar();
        }
        else if (pilih == '5')
        {
            hapustengah(&head);
            getchar();
        }
        else if (pilih == '6')
        {
            hapusakhir(&head);
            getchar();
        }
        else if (pilih == '7')
        {
            tranverse(head);
            getchar();
        }
        else if (pilih == '8')
        {
            tranverseReverse(head);
            getchar();
        }
        else if (pilih == '9')
        {
            hasil = caridata(head);
            if (hasil != -1)
            {
                printf("\nData ditemukan di posisi: %d", hasil);
            }
            else
            {
                printf("\nData tidak ditemukan dalam linked list.");
            }
            getchar();
            getchar();
        }
        else if (pilih == '0')
        {
            system("cls");
            jumlah = jumlahdata(head);
            printf("Jumlah data di dalam list : %d", jumlah);
            getchar();
        }
        else if (pilih == 'a')
        {
            system("cls");
            total = totaldata(head);
            printf("total seluruh data di list : %d", total);
            getchar();
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head)
{
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL)
    {
        pNew->data = bil;
        pNew->next = *head;
        pNew->prev = NULL;
        if (*head != NULL)
        {
            (*head)->prev = pNew;
        }
        *head = pNew;
    }
    else
    {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head)
{
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos)
    {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL)
    {
        printf("\nnode tidak ditemukan");
        getch();
    }
    else if (pNew == NULL)
    {
        printf("\nalokasi memori gagal");
        getch();
    }
    else
    {
        pNew->data = bil;
        pNew->next = pCur->next;
        pNew->prev = pCur;
        if (pCur->next != NULL)
        {
            pCur->next->prev = pNew;
        }
        pCur->next = pNew;
    }
}

//========================================================

void tambahakhir(node **head)
{
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew == NULL)
    {
        printf("\nalokasi memori gagal");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->next = NULL;
    pNew->prev = NULL;

    if (*head == NULL)
    {
        *head = pNew;
    }
    else
    {
        pCur = *head;
        while (pCur->next != NULL)
        {
            pCur = pCur->next;
        }
        pCur->next = pNew;
        pNew->prev = pCur;
    }
}

//========================================================

void hapusawal(node **head)
{
    node *pTempt;

    system("cls");
    if (*head == NULL)
    {
        printf("List kosong, tidak ada yang bsa dihapus.\n");
        return;
    }

    pTempt = *head;
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    free(pTempt);
    printf("Data di awal list sudah terhapus\n");
}

//========================================================

void hapustengah(node **head)
{
    int bil;
    node *pCur;

    system("cls");
    tranverse(*head);
    printf("\nmasukkan data yang akan dihapus : ");
    scanf("%d", &bil);

    pCur = *head;

    while (pCur != NULL && pCur->data != bil)
    {
        pCur = pCur->next;
    }

    if (pCur == NULL)
    {
        printf("\ndata tidak ditemukan");
        getch();
    }
    else
    {
        if (pCur->prev != NULL)
        {
            pCur->prev->next = pCur->next;
        }
        else
        {
            *head = pCur->next;
        }
        if (pCur->next != NULL)
        {
            pCur->next->prev = pCur->prev;
        }
        free(pCur);
        printf("\ndata sudah terhapus");
        getch();
    }
}

//========================================================

void hapusakhir(node **head)
{
    node *pCur;

    system("cls");
    if (*head == NULL)
    {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    pCur = *head;
    while (pCur->next != NULL)
    {
        pCur = pCur->next;
    }

    if (pCur->prev != NULL)
    {
        pCur->prev->next = NULL;
    }
    else
    {
        *head = NULL;
    }
    free(pCur);
    printf("Node terakhir sudah terhapus.\n");
}

//========================================================

void tranverse(node *head)
{
    node *pWalker;

    system("cls");
    pWalker = head;
    while (pWalker != NULL)
    {
        printf("%d\t", pWalker->data);
        if (pWalker->next != NULL)
        {
            printf(" -> ");
        }
        pWalker = pWalker->next;
    }
    printf(" -> NULL\n");
}

//========================================================

void tranverseReverse(node *head)
{
    node *pCur = head;

    system("cls");
    if (pCur == NULL)
    {
        printf("List kosong.\n");
        return;
    }

    while (pCur->next != NULL)
    {
        pCur = pCur->next;
    }

    printf("NULL ");
    while (pCur != NULL)
    {
        printf(" <- %d", pCur->data);
        pCur = pCur->prev;
    }
    printf("\n");
}

//========================================================

int caridata(node *head)
{
    int bil;
    node *pCur = head;
    int pos = 1;

    system("cls");
    printf("Masukkan nilai yang dicari : ");
    scanf("%d", &bil);

    while (pCur != NULL)
    {
        if (pCur->data == bil)
        {
            return pos;
        }
        pCur = pCur->next;
        pos++;
    }
    return -1;
}

//========================================================

int jumlahdata(node *head)
{
    node *pCur = head;
    int count = 0;

    system("cls");
    while (pCur != NULL)
    {
        count++;
        pCur = pCur->next;
    }
    return count;
}

//========================================================

int totaldata(node *head)
{
    node *pCur = head;
    int total = 0;

    while (pCur != NULL)
    {
        total += pCur->data;
        pCur = pCur->next;
    }
    return total;
}
