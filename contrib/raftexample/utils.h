#include "Raft.h"
PRT_MACHINEINST* makeMainMachine();
void sendAddMachineEvent(PRT_MACHINEINST* clusterMan);
void sendClientRequest(char key[], char val[]);
void sendClientRequest1(PRT_MACHINEINST* context, char key[], char val[]);