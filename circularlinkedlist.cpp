#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
typedef struct node node;

// node *createNode(void);
void tambahdata(node **head);
void tambahDatatengah(node **head);
void hapusawal(node **head);
void hapustengah(node **head);
void hapusakhir(node **head);
void tranverse(node *head);
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
        system("cls"); // Bisa di-comment sementara untuk debugging
        printf("masukkan pilihan\n");
        printf("1. tambah data \n");
        printf("2. tambah data di tengah list\n");
        printf("3. hapus data di awal list\n");
        printf("4. hapus data di tengah list\n");
        printf("5. hapus data di akhir list\n");
        printf("6. cetak isi list\n");
        printf("7. cari data di list\n");
        printf("8. jumlah data di list\n");
        printf("9. total seluruh data di list\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);
        fflush(stdin);

        if (pilih == '1')
        {
            tambahdata(&head);
            getchar();
        }
        else if (pilih == '2')
        {
            tambahDatatengah(&head);
            getchar();
        }
        else if (pilih == '3')
        {
            hapusawal(&head);
            getchar();
        }
        else if (pilih == '4')
        {
            hapustengah(&head);
            getchar();
        }
        else if (pilih == '5')
        {
            hapusakhir(&head);
            getchar();
        }
        else if (pilih == '6')
        {
            tranverse(head);
            getchar();
        }
        else if (pilih == '7')
        {
            hasil = caridata(head);
            if (hasil != -1)
            {
                printf("\nData ditemukan di posisi: %d", hasil);
            }
            else
            {
                printf("\nData tidak ditemukan dalam Circular linked list.");
            }
            getchar();
            getchar();
        }
        else if (pilih == '8')
        {
            system("cls");
            jumlah = jumlahdata(head);
            printf("Jumlah data di dalam list : %d", jumlah);
            getchar();
        }
        else if (pilih == '9')
        {
            system("cls");
            total = totaldata(head);
            printf("total seluruh data di list : %d", total);
            getchar();
        }
    } while (pilih != 'q');

    return 0;
}

void tambahdata(node **head)
{
    int bil;
    node *pNew, *pTemp;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL)
    {
        pNew->data = bil;
        if (*head == NULL)
        {
            *head = pNew;
            pNew->next = pNew;
        }

        else
        {
            pTemp = *head;
            while (pTemp->next != *head)
            {
                pTemp = pTemp->next;
            }
            pTemp->next = pNew;
            pNew->next = *head;
            *head = pNew;
        }
    }
    else
    {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahDatatengah(node **head)
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
    do
    {
        if (pCur->data == pos)
        {
            pNew = (node *)malloc(sizeof(node));
            if (pNew != NULL)
            {
                pNew->data = bil;
                pNew->next = pCur->next;
                pCur->next = pNew;
                return;
            }
            else
            {
                printf("\nalokasi memori gagal");
                getch();
                return;
            }
        }
        pCur = pCur->next;
    } while (pCur != *head);

    printf("\nnode tidak ditemukan");
    getch();
}

//========================================================

void hapusawal(node **head)
{
    node *pTemp, *pLast;

    system("cls");
    if (*head == NULL)
    {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    if ((*head)->next == *head)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        pLast = *head;
        while (pLast->next != *head)
        {
            pLast = pLast->next;
        }

        pTemp = *head;
        *head = (*head)->next;
        pLast->next = *head;
        free(pTemp);
    }
    printf("Data di awal list sudah terhapus\n");
}

//========================================================

void hapustengah(node **head)
{
    int bil;
    node *pPrev, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nmasukkan data yang akan dihapus : ");
    scanf("%d", &bil);

    pCur = *head;
    pPrev = NULL;

    do
    {
        if (pCur->data == bil)
        {
            if (pCur == *head)
            {
                hapusawal(head);
                return;
            }
            pPrev->next = pCur->next;
            free(pCur);
            printf("\ndata sudah terhapus");
            getch();
            return;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    printf("\ndata tidak ditemukan");
    getch();
}

//========================================================

void hapusakhir(node **head)
{
    node *pCur, *pPrev;

    system("cls");
    if (*head == NULL)
    {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    if ((*head)->next == *head)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        pCur = *head;
        while (pCur->next != *head)
        {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *head;
        free(pCur);
    }
    printf("Node terakhir sudah terhapus.\n");
}

//========================================================

void tranverse(node *head)
{
    node *pWalker;

    system("cls");
    if (head == NULL)
    {
        printf("List kosong.\n");
        return;
    }

    pWalker = head;
    do
    {
        printf("%d\t", pWalker->data);
        if (pWalker->next != head)
        {
            printf(" -> ");
        }
        pWalker = pWalker->next;
    } while (pWalker != head);
    printf(" -> (head)\n");
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

    if (head == NULL)
    {
        return -1;
    }

    do
    {
        if (pCur->data == bil)
        {
            return pos;
        }
        pCur = pCur->next;
        pos++;
    } while (pCur != head);

    return -1;
}

//========================================================

int jumlahdata(node *head)
{
    node *pCur = head;
    int count = 0;

    if (head == NULL)
    {
        return 0;
    }

    do
    {
        count++;
        pCur = pCur->next;
    } while (pCur != head);
    return count;
}

//========================================================

int totaldata(node *head)
{
    node *pCur = head;
    int total = 0;

    if (head == NULL)
    {
        return 0;
    }

    do
    {
        total += pCur->data;
        pCur = pCur->next;
    } while (pCur != head);
    return total;
}