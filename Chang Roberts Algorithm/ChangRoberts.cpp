#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>

int ring[7] = {14,7,25,4,91,17,32};
// int ring[7] = {91,17,32,14,7,25,4};
// int ring[7] = {1,2,3,4,5,6,7};
// int ring[2] = {1,2};

int main( int argc, char * argv[] ) {
    // initialize rank, which is ID of a process
    int rank, size;
    MPI_Init( &argc, &argv );
    // MPI_COM_WORLD is the standard communicator
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    // generate random initiators - indexes 0 to 6
    srand (time(0));
    int initiator1 = (rand() % 10 - 4);
    while (initiator1 < 0) {
        initiator1 = (rand() % 10 - 4);
    }

    int initiator2 = (rand() % 10 - 4);
    while (initiator1 == initiator2 || initiator2 < 0) {
        initiator2 = (rand() % 10 - 4);
    }           

    int initiator3 = (rand() % 10 - 4);
    while (initiator3 == initiator2 || initiator3 == initiator1 || initiator3 < 0) {
        initiator3 = (rand() % 10 - 4);
    }

    // Check input arguments for at least 3 processes as input to run algorithm
    if (size < 3) {
        std::cout << "To run the Chandy Roberts algorithm, at least 3 processes are necessary." << std::endl;
        MPI_Finalize();
        return 0;
    }

    // message array to hold contents of the elected message being sent around
    int message_container[3];
    // Store message ID of initiator once it is aboue to be elected leader
    int recvID;
    // Store initiator once it is about to be elected leader
    int initiatior_message;
    // Hold rank of process receiving the message next
    int receiver;
    // Keep track of step number in algorithm
    int current_step = 0;
    // If there is a new leader elected
    bool is_leader = false;
    // Used to begin or terminate algorithm
    bool algorithm_start = true;

    for (int i = 0; i < size; i++) {
        // Wait for all initial processes to be created
        if (rank == i) {
            std::cout << "Initial rank: " << rank << ", " << "Message ID: " << ring[rank] << std::endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Barrier to wait for all processes before starting Chandy Roberts algorithm
    MPI_Barrier(MPI_COMM_WORLD);

    // Create behavior for initiator processes
    // initiator 1
    if (rank == initiator1) {
        receiver = (rank + 1) % size;
        std::cout << "Process " << rank << " is an initiator.  It is sending message with ID " << ring[rank] << " to process " << receiver << std::endl;
        // This index will be if it is the elected initiator
        // 1 is elected initiator, 0 is non elected initiator
        message_container[0] = 0;
        // rank of elected initiator
        message_container[1] = rank;
        // message with ID to be sent
        message_container[2] = ring[rank];

        // Initial process to kick off Chandy Roberts election algorithm
        MPI_Send(&message_container, 3, MPI_INT, receiver, 0, MPI_COMM_WORLD);
    }

    if (rank == initiator2) {
        receiver = (rank + 1) % size;
        std::cout << "Process " << rank << " is an initiator.  It is sending message with ID " << ring[rank] << " to process " << receiver << std::endl;
    }

    if (rank == initiator3) {
        receiver = (rank + 1) % size;
        std::cout << "Process " << rank << " is an initiator.  It is sending message with ID " << ring[rank] << " to process " << receiver << std::endl;
    }

    // Wait for initial processes to be printed before starting the algorithm
    usleep(10000);

    // Start the Chang Roberts algorithm
    // begin with initiator 1 being passed
    while (algorithm_start) {
        MPI_Recv(&message_container, 3, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (rank == message_container[1]) {
            is_leader = true;
            message_container[0] = 1;
        }

        // if initiator receives back its own message, stop algorithm
        if (message_container[0] == 1) {
            // Store the initiator rank
            initiatior_message = message_container[1];
            // message ID of initiator
            recvID = message_container[2];
            // algorithm concludes, stop algorithm
            algorithm_start = false;
        }

        // if the current rank is an initiator
        if (rank == initiator2) {
            // if the ID at initiator process rank > ID of elected initiator process
            // elect new initiator process at rank
            if (ring[rank] > message_container[2]) {
                message_container[0] = 1;
                message_container[1] = rank;
                message_container[2] = ring[rank];
                std::cout << "Process " << message_container[1] << " is now the elected initiator with ID " << message_container[2] << "." << std::endl;
            }
        }
        
        if (rank == initiator3) {
            if (ring[rank] > message_container[2]) {
                message_container[0] = 1;
                message_container[1] = rank;
                message_container[2] = ring[rank];
                std::cout << "Process " << message_container[1] << " is now the elected initiator with ID " << message_container[2] << "." << std::endl;
            }
        }


        current_step++;
        if (is_leader == true)
            break;
        else
            std::cout << "Round number: " << current_step << ", Rank: " << rank << ", Message ID: " << ring[rank] << std::endl;

        // Wait for processes to finish printing
        usleep(100000);

        receiver = (rank + 1) % size;     
        // Send message to next process
        MPI_Send(&message_container, 3, MPI_INT, receiver, 0, MPI_COMM_WORLD);
    }
    
    // Wait for processes to finish printing from the Chandy Roberts algorithm
    usleep(1000000);

    // if we have a new leader elected
    if (rank == message_container[1])
        std::cout << "The process with rank " << message_container[1] << " has been elected as the leader with message ID " << message_container[2] << std::endl;
    
    // Wait for all processes to reach this point
    MPI_Barrier(MPI_COMM_WORLD);
    // Stop participating in any communicator (stop doing MPI work)
    MPI_Finalize();

    return 0;
}