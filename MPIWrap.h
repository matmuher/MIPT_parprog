#pragma once

typedef void (*programMPI_t)(int argc, char** argv);

void doProgramMPI(programMPI_t programMPI, int argc, char** argv)
{
  MPI_Init(&argc, &argv);

  programMPI(argc, argv);

  MPI_Finalize();
}
