#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct
{
    node *top;
    int count;
} stack;

void inistack(stack *s)
{
    s->top = NULL;
    s->count = 0;
}

int empty(stack *s)
{
    return s->top == NULL;
}

int full()
{
    node *temp = (node *)malloc(sizeof(node));
    if (temp == NULL)
    {
        return 1;
    }
    free(temp);
    return 0;
}

void push(stack *s, int value)
{
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("Alokasi Memori gagal\n");
        return;
    }
    newnode->data = value;
    newnode->next = s->top;
    s->top = newnode;
    s->count++;
    printf("Angka %d telah ditambahkan ke stack\n", value);
}

void pop(stack *s)
{
    if (empty(s))
    {
        printf("Stack kosong, tidak ada angka yang bisa dihapus\n");
    }
    else
    {
        node *delt = s->top;
        printf("Angka %d berhasil dihapus dari stack\n", delt->data);
        s->top = s->top->next;
        s->count--;
        free(delt);
    }
}

int stacktop(stack *s)
{
    if (empty(s))
    {
        printf("Stack kosong\n");
        return -1;
    }
    return s->top->data;
}

void display(stack *s)
{
    if (empty(s))
    {
        printf("Stack kosong\n");
        return;
    }
    node *current = s->top;
    printf("Isi stack: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void destroystack(stack *s)
{
    while (!empty(s))
    {
        pop(s);
    }
    printf("Stack telah dihapus\n");
}

int main()
{
    stack s;
    inistack(&s);
    int choice, value;

    do
    {
        printf("\nMenu:\n");
        printf("1. Push (Tambahkan elemen)\n");
        printf("2. Pop (Hapus elemen)\n");
        printf("3. Stack Top\n");
        printf("4. Empty Stack\n");
        printf("5. Full Stack\n");
        printf("6. Stack Count\n");
        printf("7. Destroy Stack\n");
        printf("8. Tampilkan Stack\n");
        printf("9. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("Masukkan nilai yang akan ditambahkan: ");
            scanf("%d", &value);
            getchar();
            push(&s, value);
            break;
        case 2:
            pop(&s);
            break;
        case 3:
            value = stacktop(&s);
            if (value != -1)
            {
                printf("Elemen teratas: %d\n", value);
            }
            break;
        case 4:
            printf("Apakah stack kosong? %s\n", empty(&s) ? "Ya" : "Tidak");
            break;
        case 5:
            printf("Apakah stack penuh? %s\n", full() ? "Ya" : "Tidak");
            break;
        case 6:
            printf("Jumlah elemen di stack: %d\n", s.count);
            break;
        case 7:
            destroystack(&s);
            break;
        case 8:
            display(&s);
            break;
        case 9:
            printf("Keluar dari program\n");
            break;
        default:
            printf("Opsi tidak valid, coba lagi.\n");
        }
        printf("Tekan Enter untuk melanjutkan...");
        getchar();
    } while (choice != 9);

    return 0;
}
