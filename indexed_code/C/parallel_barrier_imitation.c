/*
 ============================================================================
 Name        : assignment_2.c
 Author      : david thompson
 Version     :
 Copyright   : Your copyright notice
 Description : MPI_barrier imitation
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

/*MPI standard variables*/
MPI_Status status ;   /* return status for receive */
MPI_Request request;    /* return request for receive */


/*process sync check in (pause) */
void my_reduce (int *rank,int *procs,int *flag,int *step){
    int buffer = 0;

    /*process 0 has recieved all flags from proc at barrier*/
    if(*flag == *procs)
        return;
    
    /*processes in odd position send*/
    if(((*rank/ *flag)%2)==1){
        MPI_Send(flag, 1 ,MPI_INT, (*rank - *flag) , 0, MPI_COMM_WORLD);
        return;          //process has sent its check in
    }
    
    /*processes in even position recieve*/
    else{
        MPI_Recv(&buffer, 1, MPI_INT, (*rank+ *flag), 0, MPI_COMM_WORLD, &status);
       
        *step = *step +1;
        //printf("process %d recieved %d flags from procces %d\n",*rank,buffer,(*rank+ *flag));
        *flag = *flag + buffer;
        
        /*recursive call for proc carrying flags*/
       my_reduce(rank,procs,flag,step);
        
    }
    
}

void my_bcast(int *rank,int *procs,int *flag,int *step){
    
    
}

int main(int argc, char* argv[]){
    
    /*MPI standard variables*/
    
	int  my_rank; /* rank of process */
	int  p;       /* number of processes */
	int source;   /* rank of sender */
	int dest;     /* rank of receiver */
	int tag=0;    /* tag for messages */
	
    
    /*our variables*/
    int nFlag = 1;
    int nStepCount = 0;
    int i = 0;
    
    /*MPI standard Init*/
    
	/* start up MPI */
	
	MPI_Init(&argc, &argv);
	
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	
	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &p); 
    
    
    if (my_rank==0) {
        printf("\nProcess 0 is carrying %d flags, # of processes is %d\nStep Count is %d\n\n", nFlag, p,nStepCount);
    }


    /*mpi barrier reached (simulate mpi_reduce to check in at barrier)*/
    my_reduce(&my_rank,&p,&nFlag,&nStepCount);

    
    if (my_rank == 0 && nFlag == p) {
        printf("\nProcess 0 is carrying %d flags, # of processes is %d\nAll processes accounted for at barrier\nStep Count is %d\n\n", nFlag, p,nStepCount);
         }
    
   /*proceed past barrier (simulate mpi_bcast to tell processes to resume)*/
    while(1){
        nStepCount++;
        
        
        if((my_rank/nFlag)%2 == 1 || my_rank%2 == 1)
            MPI_Recv(&nFlag, 1, MPI_INT, my_rank - nFlag, 0, MPI_COMM_WORLD, &status);

        /*break loop if process has no more flags to send*/
        if(nFlag == 1)
            break;
        
        if(my_rank%nFlag == 0 ){
            nFlag = nFlag/2;
            dest = my_rank + nFlag;
            MPI_Send(&nFlag, 1 ,MPI_INT, dest , 0, MPI_COMM_WORLD);
         	//printf("process %d sent %d flags to procces %d\n",my_rank,nFlag,my_rank + nFlag);
        }
         /*break loop if process has no more flags to send*/
        if(nFlag == 1)
            break;
    }
    
    
    if (my_rank==0) {
        printf("\nAll processes have resumed\nStep Count is %d\n",nStepCount);
    }
    
    
  	/* shut down MPI */
	MPI_Finalize(); 
	
	
	return 0;
}
