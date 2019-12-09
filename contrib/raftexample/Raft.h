#pragma once
#ifndef P_RAFT_H_
#define P_RAFT_H_
#include "Prt.h"

PRT_MACHINEINST* makeMainMachine();
void sendAddMachineEvent(PRT_MACHINEINST* clusterMan);

#ifdef __cplusplus
extern "C" {
#endif
    
    extern PRT_EVENTDECL P_EVENT_NotifyLeaderUpdate;
    extern PRT_EVENTDECL P_EVENT_RedirectRequest;
    extern PRT_EVENTDECL P_EVENT_ShutDown;
    extern PRT_EVENTDECL P_EVENT_MakeUnavailable;
    extern PRT_EVENTDECL P_EVENT_LocalEvent;
    extern PRT_EVENTDECL P_EVENT_CConfigureEvent;
    extern PRT_EVENTDECL P_EVENT_Response;
    extern PRT_EVENTDECL P_EVENT_SConfigureEvent;
    extern PRT_EVENTDECL P_EVENT_VoteRequest;
    extern PRT_EVENTDECL P_EVENT_VoteResponse;
    extern PRT_EVENTDECL P_EVENT_AppendEntriesRequest;
    extern PRT_EVENTDECL P_EVENT_AppendEntriesResponse;
    extern PRT_EVENTDECL P_EVENT_BecomeFollower;
    extern PRT_EVENTDECL P_EVENT_BecomeCandidate;
    extern PRT_EVENTDECL P_EVENT_BecomeLeader;
    extern PRT_EVENTDECL P_EVENT_ConfigureWallclock;
    extern PRT_EVENTDECL P_EVENT_TickEvent;
    extern PRT_EVENTDECL P_EVENT_CancelTimer;
    extern PRT_EVENTDECL P_EVENT_StartTimer;
    extern PRT_EVENTDECL P_EVENT_SentAllTicks;
    extern PRT_EVENTDECL P_EVENT_CheckLogsOnShutDown;
    extern PRT_EVENTDECL P_EVENT_UpdateServers;
    extern PRT_EVENTDECL P_EVENT_UpdateServersResponse;
    extern PRT_EVENTDECL P_EVENT_AddServerResponse;
    extern PRT_EVENTDECL P_EVENT_RemoveServerResponse;
    extern PRT_EVENTDECL P_EVENT_EMonitorInit;
    extern PRT_EVENTDECL P_EVENT_Request;
    extern PRT_EVENTDECL P_EVENT_AddServer;
    extern PRT_EVENTDECL P_EVENT_RemoveServer;
    extern PRT_EVENTDECL P_EVENT_M_LogAppend;
    extern PRT_EVENTDECL P_EVENT_M_NotifyLeaderElected;
    extern PRT_EVENTDECL P_EVENT_M_LeaderCommitted;
    extern PRT_INTERFACEDECL P_I_Client;
    extern PRT_INTERFACEDECL P_I_ClusterManager;
    extern PRT_INTERFACEDECL P_I_Server;
    extern PRT_INTERFACEDECL P_I_TestDriver0;
    extern PRT_INTERFACEDECL P_I_WallclockTimer;
    extern PRT_MACHINEDECL P_MACHINE_Client;
    extern PRT_MACHINEDECL P_MACHINE_ClusterManager;
    extern PRT_MACHINEDECL P_MACHINE_SafetyMonitor;
    extern PRT_MACHINEDECL P_MACHINE_Server;
    extern PRT_MACHINEDECL P_MACHINE_TestDriver0;
    extern PRT_MACHINEDECL P_MACHINE_WallclockTimer;
    extern PRT_TYPE* P_TYPEDEF_Log;
    extern PRT_TYPE* P_TYPEDEF_Idxs;
    extern PRT_TYPE* P_TYPEDEF_Idxs2;
    extern PRT_TYPE* P_TYPEDEF_Idxs3;
    extern PRT_TYPE* P_TYPEDEF_Config;
    // DECL(SafetyTest, Test0) => P_SAFETY_TEST_Test0
    
#ifdef __cplusplus
}
#endif

#endif // P_RAFT_H_
