#include <mpi.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <array>

#include "Timer.h"

#include "../Worker.h"
#include "../MPIWrap.h"

enum class NodeType : int
{
  Sender = 0,
  Receiver = 1
};

void programMPI(int argc, char** argv)
{
  Worker worker = initWorker();

  constexpr int MaxPower = 7;
  const int StartN = 800000;
  int* arr = (int*) calloc(StartN << MaxPower, sizeof(int));

  assert(worker.worldSize == 2 && "Only two nodes available");

  Timer timer;

  std::array<double, MaxPower + 1> times;

  for (int power = 0; power <= MaxPower; power++)
  {
    int N = StartN << power;

    switch(worker.rank)
    {
      case int(NodeType::Sender):

        MPI_Send(arr, N, MPI_INT, int(NodeType::Receiver), 0, MPI_COMM_WORLD);
        break;

      case int(NodeType::Receiver):

        timer.start();
        MPI_Recv(arr, N, MPI_INT, int(NodeType::Sender), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double time = timer.elapsedMilliseconds() * 0.001;

        times[power] = time;
        
        int N_Mb = ((N * sizeof(int)) / (2<<20));

        std::cout << "N = " << N_Mb << " Mb\n";
        std::cout << "Run time = " << time << " s\n";

        constexpr double Epsilon = 0.00001;
        if (time > Epsilon)
        {
          double speed =  N_Mb / (time);
          std::cout << "Speed = " << speed << " Mb/s\n\n";
        }

        break; 
    }

    MPI_Barrier(MPI_COMM_WORLD);
  }
}

int main(int argc, char** argv)
{
  doProgramMPI(programMPI, argc, argv);
}
