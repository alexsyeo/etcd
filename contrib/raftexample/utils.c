#include "utils.h"
PRT_PROCESS* ContainerProcess;

PRT_EVENTDECL* P_ALL_EVENTS[] = { &_P_EVENT_NULL_STRUCT, &_P_EVENT_HALT_STRUCT, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_ShutDown, &P_EVENT_MakeUnavailable, &P_EVENT_LocalEvent, &P_EVENT_CConfigureEvent, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeFollower, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeLeader, &P_EVENT_ConfigureWallclock, &P_EVENT_TickEvent, &P_EVENT_CancelTimer, &P_EVENT_StartTimer, &P_EVENT_SentAllTicks, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_AddServerResponse, &P_EVENT_RemoveServerResponse, &P_EVENT_EMonitorInit, &P_EVENT_Request, &P_EVENT_AddServer, &P_EVENT_RemoveServer, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_M_LeaderCommitted, &P_EVENT_InjectFailure };
PRT_MACHINEDECL* P_ALL_MACHINES[] = { &P_MACHINE_ClusterManager, &P_MACHINE_SafetyMonitor, &P_MACHINE_Server, &P_MACHINE_TestDriver0, &P_MACHINE_TestDriver1, &P_MACHINE_FailureInjector, &P_MACHINE_TestDriver2, &P_MACHINE_WallclockTimer };
PRT_INTERFACEDECL* P_ALL_INTERFACES[] = { &P_I_ClusterManager, &P_I_Server, &P_I_TestDriver0, &P_I_TestDriver1, &P_I_FailureInjector, &P_I_TestDriver2, &P_I_WallclockTimer };
PRT_FUNDECL* P_ALL_FUNCTIONS[] = { NULL };
PRT_FOREIGNTYPEDECL* P_ALL_FOREIGN_TYPES[] = { NULL };

PRT_UINT32 P_INTERFACE_MAP[] = {0, 2, 3, 4, 5, 6, 7};

PRT_PROGRAMDECL PROGRAM_DECL = 
{
    32U,
    6U,
    5U,
    0U,
    0U,
    P_ALL_EVENTS,
    P_ALL_MACHINES,
    P_ALL_INTERFACES,
    P_ALL_FUNCTIONS,
    P_ALL_FOREIGN_TYPES,
    NULL,
    P_INTERFACE_MAP
};


PRT_MACHINEINST* makeMainMachine(){
    PRT_GUID processGuid;
	processGuid.data1 = 1;
	processGuid.data2 = 1; //nodeId
	processGuid.data3 = 0;
	processGuid.data4 = 0;

	ContainerProcess = PrtStartProcess(processGuid, &PROGRAM_DECL, NULL, NULL);

	//create main machine
	PRT_UINT32 machineId;
	PRT_BOOLEAN foundMainMachine = PrtLookupMachineByName("ClusterManager", &machineId);
	if (foundMainMachine == PRT_FALSE)
	{
		printf("%s\n", "FAILED TO FIND TestMachine");
		exit(1);
	}
    printf("\n\n\n\n\n\n\n\n\n\n\nhello\n");
	PRT_MACHINEINST* clusterManager = PrtMkMachine(ContainerProcess, 0, 0);
    printf("\n\n\n\n\n\n\n\n\nhello2\n");
    return clusterManager;

	// PrtFreeValue(payload);
}

void sendAddMachineEvent(PRT_MACHINEINST* clusterMan) {
    printf("\n\n\n\n\n\n\nclusterman %d\n", clusterMan->instanceOf);
    PRT_MACHINESTATE state;
    PrtGetMachineState(clusterMan, &state);
    PRT_UINT32 machineId;
	PRT_BOOLEAN foundMainMachine = PrtLookupMachineByName("Server", &machineId);
    if (foundMainMachine == PRT_FALSE)
	{
		printf("%s\n", "FAILED TO FIND TestMachine");
		exit(1);
	}
    PRT_MACHINEINST* server = PrtMkMachine(ContainerProcess, 2, 0);
    printf("server %d\n", machineId);
    PRT_VALUE* PTMP_tmp13_1 = NULL;
    PRT_VALUE** P_LVALUE_76 = &(PTMP_tmp13_1);
    PrtFreeValue(*P_LVALUE_76);
    *P_LVALUE_76 = PrtCloneValue((server->id));



    PRT_MACHINESTATE state2;
    PrtGetMachineState(clusterMan, &state2);
    PRT_UINT32 machineId2;
	PRT_BOOLEAN foundMainMachine2 = PrtLookupMachineByName("Server", &machineId2);
    if (foundMainMachine2 == PRT_FALSE)
	{
		printf("%s\n", "FAILED TO FIND TestMachine");
		exit(1);
	}
    PRT_MACHINEINST* server2 = PrtMkMachine(ContainerProcess, 2, 0);
    printf("server %d\n", machineId2);
    PRT_VALUE* PTMP_tmp14_1 = NULL;
    PRT_VALUE** P_LVALUE_75 = &(PTMP_tmp14_1);
    PrtFreeValue(*P_LVALUE_75);
    *P_LVALUE_75 = PrtCloneValue((server2->id));



    PrtSend(&state, clusterMan, &P_EVENT_AddServer.value, 1, &(PTMP_tmp13_1));
    PrtSend(&state2, clusterMan, &P_EVENT_AddServer.value, 1, &(PTMP_tmp14_1));
    printf("kdlfjlk\n");
}