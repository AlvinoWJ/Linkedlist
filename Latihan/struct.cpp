#include <stdio.h>

struct mahasiswa
{
    char nama[20];
    char NPM;
    float IPK;
};

int main()
{
    struct mahasiswa mahasiswa;

    printf("\nData Mahasiswa\n");
    printf("Masukkan nama : ");
    fgets(mahasiswa.nama, sizeof(mahasiswa.nama), stdin);
    printf("Masukkan NPM : ");
    fgets(mahasiswa.NPM, sizeof(mashasiswa.NPM), stdin);
    printf("Masukkan IPK : ");
    scanf("%f", &mahasiswa.IPK);

    printf("\nData Mahasiswa\n");
    printf("Nama : %s", mahasiswa.nama);
    printf("NPM : %s", mahasiswa.NPM);
    printf("\nIPK : %.2f", mahasiswa.IPK);

    return 0;
}