#pragma once

void doProgramMPI(void (*programMPI)(void))
{
  MPI_Init(NULL, NULL);

  programMPI();

  MPI_Finalize();
}
