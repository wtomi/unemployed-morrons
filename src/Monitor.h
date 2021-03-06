//
// Created by tommy on 10.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MONITOR_H
#define UNEMPLOYED_MORRONS_MONITOR_H

#include <sstream>
#include <mpi.h>
#include "Packet.h"

class Monitor {
public:
    typedef std::shared_ptr<Monitor> SharedPtr;
    static SharedPtr monitor;
    static const int ANY_SOURCE = MPI_ANY_SOURCE;
    static const int ANY_TAG = MPI_ANY_TAG;
    int rank;
    int size;
    MPI_Comm mpiComm;

    static SharedPtr getMonitor();
    ~Monitor();

    void send(Packet::SharedPtr package);
    void send(std::shared_ptr<std::stringstream> stringStreamMessage, int source, int tag);
    Packet::SharedPtr receive(int source = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG);
    MPI_Status probe(int source = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG);
    int getCount(MPI_Status &status);
    void synchronize();

private:
    Monitor(int *argc = nullptr, char ***argv = nullptr, MPI_Comm mpiComm = MPI_COMM_WORLD);
};

#endif //UNEMPLOYED_MORRONS_MONITOR_H
