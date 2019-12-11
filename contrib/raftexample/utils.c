#include "utils.h"
PRT_PROCESS* ContainerProcess;
PRT_MACHINEINST* clusterManager;

PRT_STRING P_NMDTUP_N_20[] = { "Client", "Key", "Val" };
PRT_TYPE P_GEND_TYPE_R_2 = { PRT_KIND_MACHINE, { NULL } };
PRT_TYPE P_GEND_TYPE_r = { PRT_KIND_STRING, { NULL } };
PRT_TYPE* P_NMDTUP_T_20[] = { &P_GEND_TYPE_R_2, &P_GEND_TYPE_r, &P_GEND_TYPE_r };
PRT_NMDTUPTYPE P_NMDTUP_20 = { 3U, P_NMDTUP_N_20, P_NMDTUP_T_20 };
PRT_TYPE P_GEND_TYPE_T3Rrr = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_20 } };

PRT_EVENTDECL* P_ALL_EVENTS[] = { &_P_EVENT_NULL_STRUCT, &_P_EVENT_HALT_STRUCT, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_ShutDown, &P_EVENT_MakeUnavailable, &P_EVENT_LocalEvent, &P_EVENT_CConfigureEvent, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeFollower, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeLeader, &P_EVENT_ConfigureWallclock, &P_EVENT_TickEvent, &P_EVENT_CancelTimer, &P_EVENT_StartTimer, &P_EVENT_SentAllTicks, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_AddServerResponse, &P_EVENT_RemoveServerResponse, &P_EVENT_EMonitorInit, &P_EVENT_Request, &P_EVENT_AddServer, &P_EVENT_RemoveServer, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_M_LeaderCommitted, &P_EVENT_InjectFailure };
PRT_MACHINEDECL* P_ALL_MACHINES[] = { &P_MACHINE_ClusterManager, &P_MACHINE_SafetyMonitor, &P_MACHINE_Server, &P_MACHINE_TestDriver0, &P_MACHINE_TestDriver1, &P_MACHINE_FailureInjector, &P_MACHINE_TestDriver2, &P_MACHINE_WallclockTimer };
PRT_INTERFACEDECL* P_ALL_INTERFACES[] = { &P_I_ClusterManager, &P_I_Server, &P_I_TestDriver0, &P_I_TestDriver1, &P_I_FailureInjector, &P_I_TestDriver2, &P_I_WallclockTimer };
PRT_FUNDECL* P_ALL_FUNCTIONS[] = { NULL };
PRT_FOREIGNTYPEDECL* P_ALL_FOREIGN_TYPES[] = { NULL };

PRT_UINT32 P_INTERFACE_MAP[] = {0, 2, 3, 4, 5, 6, 7};

PRT_PROGRAMDECL PROGRAM_DECL = 
{
    35U,
    8U,
    7U,
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
    clusterManager = PrtMkMachine(ContainerProcess, 0, 0);
    return clusterManager;

	// PrtFreeValue(payload);
}

void sendAddMachineEvent(PRT_MACHINEINST* clusterMan, int numServers) {
    PRT_MACHINESTATE state;
    PrtGetMachineState(clusterMan, &state);
    int i;
    for (i = 0; i < numServers; i++) {
        PRT_MACHINEINST* server = PrtMkMachine(ContainerProcess, 1, 0);
        PRT_VALUE* PTMP_tmp13_1 = NULL;
        PRT_VALUE** P_LVALUE_76 = &(PTMP_tmp13_1);
        PrtFreeValue(*P_LVALUE_76);
        *P_LVALUE_76 = PrtCloneValue((server->id));

        PRT_VALUE* PTMP_tmp1_15 = NULL;
        PRT_VALUE** P_LVALUE_137 = &(PTMP_tmp1_15);
        PrtFreeValue(*P_LVALUE_137);
        *P_LVALUE_137 = PrtCloneValue((&P_EVENT_AddServer.value));

        PrtSend(&state, clusterMan, PTMP_tmp1_15, 1, &(PTMP_tmp13_1));
        printf("kdlfjlk\n");
    }
}

void sendClientRequest(char key[], char val[]) {
    sendClientRequest1(clusterManager, key, val);
}

// Causes clusterManager to send request to itself, simulating a client request
// Pass in clusterManager
void sendClientRequest1(PRT_MACHINEINST* context, char key[], char val[]) {
    printf("Key: %s\n", key);
    printf("Val: %s\n", val);


    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* PTMP_tmp0_74 = NULL;
    PRT_VALUE* PTMP_tmp1_62 = NULL;
    PRT_VALUE* PTMP_tmp2_55 = NULL;
    PRT_VALUE* PTMP_tmp3_51 = NULL;
    PRT_VALUE* PTMP_tmp4_43 = NULL;
    PRT_VALUE* PTMP_tmp5_32 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_STRING = { PRT_VALUE_KIND_STRING, { .str = key } };
    PRT_VALUE P_LIT_STRING_1 = { PRT_VALUE_KIND_STRING, { .str = val } };

    PRT_VALUE** P_LVALUE_1290 = &(PTMP_tmp1_62);
    PrtFreeValue(*P_LVALUE_1290);
    *P_LVALUE_1290 = PrtCloneValue((&P_EVENT_Request.value));
    
    PRT_VALUE** P_LVALUE_1291 = &(PTMP_tmp2_55);
    PrtFreeValue(*P_LVALUE_1291);
    *P_LVALUE_1291 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_1292 = &(PTMP_tmp3_51);
    PrtFreeValue(*P_LVALUE_1292);
    *P_LVALUE_1292 = PrtCloneValue((&P_LIT_STRING));

    PRT_VALUE** P_LVALUE_1293 = &(PTMP_tmp4_43);
    PrtFreeValue(*P_LVALUE_1293);
    *P_LVALUE_1293 = PrtCloneValue((&P_LIT_STRING_1));
    
    PRT_VALUE** P_LVALUE_1294 = &(PTMP_tmp5_32);
    PrtFreeValue(*P_LVALUE_1294);

    // generated type of tuple may change later!
    *P_LVALUE_1294 = (PrtMkTuple(P_GEND_TYPE_T3Rrr, &(PTMP_tmp2_55), &(PTMP_tmp3_51), &(PTMP_tmp4_43)));
    
    PRT_MACHINESTATE* state;
    PrtGetMachineState(context, state);

    printf("before PRTSEND\n");
    PrtSend(state, context, PTMP_tmp1_62, 1, &(PTMP_tmp5_32));
    printf("after PRTSEND\n");
}