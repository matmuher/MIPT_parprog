#pragma once
#include <mpi.h>

struct Worker
{
  int rank;
  int worldSize;
};

Worker initWorker()
{
  Worker worker;

  MPI_Comm_size(MPI_COMM_WORLD, &worker.worldSize);
  MPI_Comm_rank(MPI_COMM_WORLD, &worker.rank);

  return worker;
}
