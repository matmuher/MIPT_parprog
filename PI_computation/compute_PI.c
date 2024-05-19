#include <mpi.h>
#include <stdio.h>
#include <assert.h>

#include "Worker.h"
#include "Work.h"
#include "MPIWrap.h"

void programMPI(void)
{
  Worker worker = initWorker();

  Work work = getWork(worker);

  int circleNum = doWork(work);

  switch(worker.rank)
  {
    case 0:
    {
      int recvNum = 0;
      MPI_Recv(&recvNum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("recvNum = %d\n", recvNum);
      break;
    }
    case 1:
    {
      int sendNum = 25;
      MPI_Send(&sendNum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      printf("sendNum = %d\n", sendNum);
      break;
    }
    default:

      printf("Worker [%d] is unemployed\n", worker.rank);
  }
}

int main(int argc, char** argv)
{
  doProgramMPI(programMPI);
}
