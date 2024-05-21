#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double startTime, endTime;

    if (rank == 0) { // Process 0 sends a message
        std::cout << "Process " << rank << " sending message..." << std::endl;
        MPI_Send("Hello, World!", 13, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) { // Process 1 receives the message
        std::cout << "Process " << rank << " waiting to receive message..." << std::endl;
        MPI_Recv("Hello, World!", 13, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Measure the time taken for the send/receive operation
    if (rank == 0 || rank == 1) {
        startTime = MPI_Wtime();
        MPI_Send("Hello, World!", 13, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv("Hello, World!", 13, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        endTime = MPI_Wtime();

        double elapsedTime = endTime - startTime;
        std::cout << "Time taken for communication: " << elapsedTime << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
