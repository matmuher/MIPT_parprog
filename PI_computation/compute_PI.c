#include <mpi.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../Worker.h"
#include "../MPIWrap.h"
#include "Work.h"

const int RootRank = 0;

int* createRecvArray(Worker worker)
{
  int* arr = NULL;

  if (worker.rank == RootRank)
  {
    arr = (int*) calloc(worker.worldSize, sizeof(int));
    assert(arr != NULL);
  }

  return arr;
}

void programMPI(int argc, char** argv)
{
  Worker worker = initWorker();

  Work work = getWork(worker);

  int circleNum = doWork(work);

  int* arr = createRecvArray(worker);

  MPI_Gather(&circleNum, 1, MPI_INT,
              arr, 1, MPI_INT,
              RootRank,
              MPI_COMM_WORLD);

  if (worker.rank == RootRank)
  {
    int sum  = 0;
    for (int area_id = 0; area_id < worker.worldSize; area_id++)
    {
      sum += arr[area_id];
    }

    printf("SUM: %d\n", sum);

    double pi = SquareArea * (sum / double(GlobalSampleNum));

    printf("pi = %lg\n", pi);

    free(arr);
  }
}

int main(int argc, char** argv)
{
  doProgramMPI(programMPI, argc, argv);
}
