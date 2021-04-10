#include<stdio.h>
#include<string.h>

int x[200], w[50][2], gab[200], sol[200][200];
int N, uang, Nsol;

int promising(int k, int W, int sisabobot){
    //mengecek kevalidan sisabobot dan jumlah uang
    return ((W + sisabobot >= uang) && (W == uang || W + gab[k+1] <= uang));
}

int notSame(int temp[200], int sol[200][200], int n){
    //Mengecek apakah solusi sudah ada atau belum
    int i, j, same, count;
    i = 0; same = 1;
    while(i<Nsol){
        j = 0;
        count = 0;
        while(j<n){
            if(temp[j]==sol[i][j+1]){
                count++;
            }
            j++;
        }
        if(count==n){
            same = 0;
        }
        i++;
    }
    return same;
}

void sumofsubsets(int k, int Wt, int sisabobot) {
    //Backtracking pencarian kombinasi pembelian cokelat
    int j, i, iter, temp[200];
    if (promising(k, Wt, sisabobot)){
        if (Wt==uang) {
            i = 0;
            for(j=0;j<=k;j++){
                if (x[j]==1){
                    temp[i] = gab[j];
                    i++;
                }
            }
            if(notSame(temp, sol, i)){
                sol[Nsol][0] = i;
                for(j=0; j<i; j++){
                    sol[Nsol][j+1] = temp[j];
                }
                Nsol++;
            }
        } else {
            x[k+1] = 1;
            sumofsubsets(k+1, Wt + gab[k+1], sisabobot - gab[k+1]);
            x[k+1] = 0;
            sumofsubsets(k+1, Wt, sisabobot - gab[k+1]);
        }
    }
}

void merge_sort(int gab[200], int w[50][2]){
    //menggabungkan data cokelat menjadi 1 dimensi array
    int i, j, n, temp;
    i=0; n=0;
    while(w[i][0]!=0){
        for(j=0; j<w[i][1]; j++){
            gab[n] = w[i][0];
            n++;
        }
        i++;
    }

    //Mengurutkan array dari yang terkecil ke terbesar
    for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
           if (gab[j] > gab[j+1]){
                temp = gab[j];
                gab[j] = gab[j+1];
                gab[j+1] = temp;
           }
    gab[n] = 0;
}

int maxCokelat(int sol[200][200]){
    //Mencari banyak cokelat terbanyak yang bisa dibeli
    int i, max;
    max = sol[0][0];
    for(i=1; i<Nsol; i++){
        if(sol[i][0]>max){
            max = sol[i][0];
        }
    }
    return max;
}

void print(int sol[200][200]){
    //Mencetak kombinasi pembelian cokelat secara terurut dari terkecil
    int i, j;
    printf("\nSolusi kombinasi pembelian cokelat ada %d\n", Nsol);
    for(i=0; i<Nsol; i++){
        for(j=0; j<sol[i][0]; j++){
            if (j != sol[i][0] - 1)
                printf("%d ", sol[i][j+1]);
            else
                printf("%d", sol[i][j+1]);
        }
        printf("\n");
    }
    printf("\n");

    //Mencetak jumlah anak yang bisa Pak Oden bahagiakan
    if(Nsol == 0){
        printf("Pak Oden tidak bisa membahagiakan anaknya satu pun\n");
    } else{
        printf("Pak Oden bisa membahagiakan maksimal %d anaknya\n", maxCokelat(sol));
    }
}

int main() {
    int i, j, total;
    printf("Masukkan banyaknya jenis cokelat: ");
    scanf("%d", &N);
    printf("\n");
    for(i=0; i<N; i++){
        printf("Masukkan harga cokelat ke-%d: ", i+1);
        scanf("%d", &w[i][0]);
        printf("Masukkan jumlah anak yang suka cokelat ke-%d: ", i+1);
        scanf("%d", &w[i][1]);
    }
    w[N][0] = 0;
    printf("\nMasukkan jumlah uang Pak Oden: ");
    scanf("%d", &uang);
    merge_sort(gab, w);
    total = 0; Nsol = 0;
    i = 0;
    while (gab[i]!=0) {
        total = total + gab[i];
        i++;
    }

    sumofsubsets(-1, 0, total);
    print(sol);
    return 0;
}
