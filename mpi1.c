#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mpi.h"

bool arraySortCheck(int arr[], int N){
    //Array has one or no element
    if (N == 0 || N == 1)
        return true;
 
    for (int i = 1; i < N; i++)
        //In case an unsorted pair is found
        if (arr[i - 1] > arr[i])
            return false;
 
    //In case no unsorted pair is found
    return true;
}

int falseElement(int arr[], int N){
    for (int i = 0; i < N; i++)
        if(arr[i] > arr[i+1])
            return arr[i];
}

int menuFunc(int rank){
    if(rank == 0){
        int option;
        do{
            printf("\n-======================-MENU-=======================-\n");
            printf(" 1. Συνέχεια\n 2. Έξοδος\n Επιλογή: ");
            scanf("%d", &option);
            printf("\n-====================================================-\n");
        }while(option <= 0 || option >= 3);
    return option;
    }
}



int main(int argc, char** argv){
    int rank, vote=0;
    int p, res, finres, num;
    int index; //δείκτης που δείχνει από που ξεκινάει η σύγκριση 
    int source, dest, option, flag=0;
    int tag1=100, tag2=200, tag3=300, tag4=400, tag5=500;
    int N;
    int* T;
    int* T_loc;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    if(rank == 0){
        option = menuFunc(rank);
        if(option == 2)
            printf("\nΈξοδος...\n");
        
    }
    
    while(option == 1){
        if(rank == 0){
            do{
                printf("\nΔώσε μέγεθος πίνακα:\n");
                scanf("%d", &N);
            }
            while(N < 0);
            
            T = (int*)malloc(N*sizeof(int));

            printf("\n-----------------------");
            for(index=0; index<N; index++){
                printf("\nΔώσε στοιχείο πίνακα: ");
                scanf("%d", &T[index]);
            }
            dest=1;
            if(arraySortCheck(T, num+1))
                vote++;
            
            MPI_Send(&N, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
            num=N/p;
            MPI_Send(&T, N, MPI_INT, dest, tag2, MPI_COMM_WORLD);
            MPI_Send(&index, 1, MPI_INT, dest, tag3, MPI_COMM_WORLD);
            MPI_Send(&vote, 1, MPI_INT, dest, tag4, MPI_COMM_WORLD);
			source = p-1;
            MPI_Recv(&vote, 1, MPI_INT, source, tag5, MPI_COMM_WORLD, &status); //τελικό vote
        }

        else{
            while(rank < p){
                source = rank-1;    // Η προηγούμενη σε σειρά διεργασία (πηγή).
                dest = rank+1;      // Η επόμενη σε σειρά διεργασία (πηγή).
                MPI_Recv(&N, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
                T_loc = (int*)malloc(N*sizeof(int));

                num=N/p;
                MPI_Recv(&T, N, MPI_INT, source, tag2, MPI_COMM_WORLD, &status);
                MPI_Recv(&index, 1, MPI_INT, source, tag3, MPI_COMM_WORLD, &status);
                MPI_Recv(&vote, 1, MPI_INT, source, tag4, MPI_COMM_WORLD, &status);

            
                if(arraySortCheck(T, num+1))
                    vote++;
                for(index; index<=index+num; index++)
                    printf("\nT[%d] = %d\n", index, T[index]);
                    
                    
                MPI_Send(&N, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
                MPI_Send(&T, N, MPI_INT, dest, tag2, MPI_COMM_WORLD);
                MPI_Send(&index, 1, MPI_INT, dest, tag3, MPI_COMM_WORLD);
                if(rank == p-1)
                    MPI_Send(&vote, 1, MPI_INT, 0, tag5, MPI_COMM_WORLD);
                else
                    MPI_Send(&vote, 1, MPI_INT, dest, tag4, MPI_COMM_WORLD);
            }
        }

        if(rank == 0){
            if(vote == p)
                printf("yes\n");
            else{
                printf("no\n");
                printf("Το στοιχείο στο οποίο χαλάει η ταξινόμηση είναι το: %d\n", falseElement(T, N));
            }
            option = menuFunc(rank);
            if(option == 2)
                printf("Έξοδος...\n");
        }
    }
    // free(T);
    // free(T_loc);
    MPI_Finalize();
    return 0;
}