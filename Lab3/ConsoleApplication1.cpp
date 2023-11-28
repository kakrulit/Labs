#include <iostream>
#include <mpi.h>
#include <Windows.h>
#include <string>

/*
О столовой. В столовой повар принимает заказы (название 1 блюда) от 15 изголодавшихся студентов, 
по 2 заказа от каждого (в произвольном порядке). После каждого принятого заказа повар готовит заказ 0,1 секунды, 
и выдает его (сообщается название блюда) заказчику. Смоделировать эту ситуацию с помощью MPI.
*/

#define NUM_STUDENTS 15
#define NUM_ORDERS_PER_STUDENT 2
#define ORDER_COUNTS (NUM_STUDENTS * NUM_ORDERS_PER_STUDENT)

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < ORDER_COUNTS; i++) {
            MPI_Status status;

            char order[12];

            MPI_Recv(order, 12, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            Sleep(100);

            std::cout << "Order received: " << order << " | From: " << status.MPI_SOURCE << std::endl;
        }
    }
    else {
        srand(rank * time(NULL));

        for (int i = 0; i < NUM_ORDERS_PER_STUDENT; i++) {

            std::string order = "dish" + std::to_string(i);

            std::cout << "Buyer " << rank << " make an order " << order << std::endl;
            
            MPI_Send(order.c_str(), 12, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}