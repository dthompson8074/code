/*
 ============================================================================
 Name        : assignment_1.c
 Author      : david thompson
 Version     :
 Copyright   : Your copyright notice
 Description : Matrix[1200][1200] parallel summation with latency masking
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


/*generate random row values for matrix*/
void row_gen(int *a){
    
    for(int i = 0; i < 1200;i++){
        a[i] = rand() %10;
     }
}
/*copy current row into prev row*/
void copy_row(int *cur,int *prev){
    
    for(int i = 0; i < 1200;i++){
        prev[i] = cur[i];
    }

    
}
/*locally sum row*/
void summation(int *a,int *sum,int *total,int *proc){
    *sum = 0;
    for(int i = 0; i < 1200;i++){
        *sum = *sum + a[i];
    }
    printf("process %d local sum: %d\n",*proc,*sum);
    *total = *total + *sum;
}

int main(int argc, char* argv[]){
    /*MPI standard variables*/
    
	int  my_rank; /* rank of process */
	int  p;       /* number of processes */
	int source;   /* rank of sender */
	int dest;     /* rank of receiver */
	int tag=0;    /* tag for messages */
	
	MPI_Status status ;   /* return status for receive */
    MPI_Request request;    /* return request for receive */
    
    /*our variables*/
    int total_sum = 0;
    int local_sum = 0;
    int local_total = 0;
    int count = 0;
    
    /*MPI standard Init*/
    
	/* start up MPI */
	
	MPI_Init(&argc, &argv);
	
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	
	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &p); 
    
    
    if (my_rank == 0){
        int matrix[1200][1200];
        int cur_row = 0;
        
        while(cur_row < 1200){
            
        row_gen(matrix[cur_row]);
        for (dest = 1; dest < p; dest++) {
            
            MPI_Isend(matrix[cur_row], 1200, MPI_INT,
                     dest, tag, MPI_COMM_WORLD,&request);
            /*overlap next row generation with previous row send*/
                cur_row++;
                row_gen(matrix[cur_row]);
            MPI_Wait(&request,&status);
            
        }
            /*process 0 summation*/
            
            summation(matrix[cur_row],&local_sum,&local_total,&my_rank);
            cur_row++;
        }
       

    }
    else if (my_rank !=0){
        int row[1200];
        int prev_row[1200];
        
        /*use blocking rec to recieve first row*/
        MPI_Recv(row, 1200, MPI_INT, 0, tag,
                  MPI_COMM_WORLD, &status);
        
        while(count < (1200/p) - 1){
            
        /*copy buffer*/
            copy_row(row,prev_row);
            
        /*overlap previous row computation with non blocking recieve of next row*/
            MPI_Irecv(row, 1200, MPI_INT, 0, tag,
                 MPI_COMM_WORLD, &request);
            
            summation(prev_row,&local_sum,&local_total,&my_rank);
            count++;
            MPI_Wait(&request,&status);
        
        }
        /*compute sum of last row*/
          summation(row,&local_sum,&local_total,&my_rank);
        }
    
    /* combine everyone's calculations */
    MPI_Reduce(&local_total, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (my_rank == 0) {
        printf("total sum is %d\n", total_sum);
         }

    
  	/* shut down MPI */
	MPI_Finalize(); 
	
	
	return 0;
}
