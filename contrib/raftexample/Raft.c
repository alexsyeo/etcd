#include "Raft.h"

// Type universe for program:
static PRT_STRING P_NMDTUP_N[] = { "Leader", "Term" };
static PRT_TYPE P_GEND_TYPE_m = { PRT_KIND_MACHINE, { NULL } };
static PRT_TYPE P_GEND_TYPE_i = { PRT_KIND_INT, { NULL } };
static PRT_TYPE* P_NMDTUP_T[] = { &P_GEND_TYPE_m, &P_GEND_TYPE_i };
static PRT_NMDTUPTYPE P_NMDTUP = { 2U, P_NMDTUP_N, P_NMDTUP_T };
static PRT_TYPE P_GEND_TYPE_T2mi = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP } };
static PRT_STRING P_NMDTUP_N_1[] = { "Client", "Key", "Val" };
static PRT_TYPE P_GEND_TYPE_r = { PRT_KIND_STRING, { NULL } };
static PRT_TYPE* P_NMDTUP_T_1[] = { &P_GEND_TYPE_m, &P_GEND_TYPE_r, &P_GEND_TYPE_r };
static PRT_NMDTUPTYPE P_NMDTUP_1 = { 3U, P_NMDTUP_N_1, P_NMDTUP_T_1 };
static PRT_TYPE P_GEND_TYPE_T3mrr = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_1 } };
static PRT_TYPE P_GEND_TYPE_n = { PRT_KIND_NULL, { NULL } };
static PRT_STRING P_NMDTUP_N_2[] = { "Servers", "ClusterManager" };
static PRT_SEQTYPE P_SEQTYPE = { &P_GEND_TYPE_m };
static PRT_TYPE P_GEND_TYPE_Sm = { PRT_KIND_SEQ, { .seq = &P_SEQTYPE } };
static PRT_TYPE* P_NMDTUP_T_2[] = { &P_GEND_TYPE_Sm, &P_GEND_TYPE_m };
static PRT_NMDTUPTYPE P_NMDTUP_2 = { 2U, P_NMDTUP_N_2, P_NMDTUP_T_2 };
static PRT_TYPE P_GEND_TYPE_T2Smm = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_2 } };
static PRT_STRING P_NMDTUP_N_3[] = { "Term", "CandidateId", "LastLogIndex", "LastLogTerm" };
static PRT_STRING P_NMDTUP_N_4[] = { "KV", "Cfg" };
static PRT_TYPE* P_NMDTUP_T_4[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_i };
static PRT_NMDTUPTYPE P_NMDTUP_4 = { 2U, P_NMDTUP_N_4, P_NMDTUP_T_4 };
static PRT_TYPE P_GEND_TYPE_T2ii = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_4 } };
static PRT_TYPE* P_NMDTUP_T_3[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_m, &P_GEND_TYPE_T2ii, &P_GEND_TYPE_T2ii };
static PRT_NMDTUPTYPE P_NMDTUP_3 = { 4U, P_NMDTUP_N_3, P_NMDTUP_T_3 };
static PRT_TYPE P_GEND_TYPE_T4imT2iiT2ii = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_3 } };
static PRT_STRING P_NMDTUP_N_5[] = { "Term", "VoteGranted" };
static PRT_TYPE P_GEND_TYPE_b = { PRT_KIND_BOOL, { NULL } };
static PRT_TYPE* P_NMDTUP_T_5[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_b };
static PRT_NMDTUPTYPE P_NMDTUP_5 = { 2U, P_NMDTUP_N_5, P_NMDTUP_T_5 };
static PRT_TYPE P_GEND_TYPE_T2ib = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_5 } };
static PRT_STRING P_NMDTUP_N_6[] = { "Term", "LeaderId", "PrevLogIndex", "PrevLogTerm", "Entries", "CfgEntries", "LeaderCommit", "ReceiverEndpoint" };
static PRT_STRING P_NMDTUP_N_7[] = { "Term", "Key", "Val" };
static PRT_TYPE* P_NMDTUP_T_7[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_r, &P_GEND_TYPE_r };
static PRT_NMDTUPTYPE P_NMDTUP_7 = { 3U, P_NMDTUP_N_7, P_NMDTUP_T_7 };
static PRT_TYPE P_GEND_TYPE_T3irr = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_7 } };
static PRT_SEQTYPE P_SEQTYPE_1 = { &P_GEND_TYPE_T3irr };
static PRT_TYPE P_GEND_TYPE_ST3irr = { PRT_KIND_SEQ, { .seq = &P_SEQTYPE_1 } };
static PRT_STRING P_NMDTUP_N_8[] = { "Term", "Servers" };
static PRT_TYPE* P_NMDTUP_T_8[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_Sm };
static PRT_NMDTUPTYPE P_NMDTUP_8 = { 2U, P_NMDTUP_N_8, P_NMDTUP_T_8 };
static PRT_TYPE P_GEND_TYPE_T2iSm = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_8 } };
static PRT_SEQTYPE P_SEQTYPE_2 = { &P_GEND_TYPE_T2iSm };
static PRT_TYPE P_GEND_TYPE_ST2iSm = { PRT_KIND_SEQ, { .seq = &P_SEQTYPE_2 } };
static PRT_TYPE* P_NMDTUP_T_6[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_m, &P_GEND_TYPE_T2ii, &P_GEND_TYPE_T2ii, &P_GEND_TYPE_ST3irr, &P_GEND_TYPE_ST2iSm, &P_GEND_TYPE_T2ii, &P_GEND_TYPE_m };
static PRT_NMDTUPTYPE P_NMDTUP_6 = { 8U, P_NMDTUP_N_6, P_NMDTUP_T_6 };
static PRT_TYPE P_GEND_TYPE_T8imT2iiT2iiST3irrST2iSmT2iim = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_6 } };
static PRT_STRING P_NMDTUP_N_9[] = { "Term", "Success", "KV", "Cfg", "Server", "ReceiverEndpoint" };
static PRT_TYPE* P_NMDTUP_T_9[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_b, &P_GEND_TYPE_b, &P_GEND_TYPE_b, &P_GEND_TYPE_m, &P_GEND_TYPE_m };
static PRT_NMDTUPTYPE P_NMDTUP_9 = { 6U, P_NMDTUP_N_9, P_NMDTUP_T_9 };
static PRT_TYPE P_GEND_TYPE_T6ibbbmm = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_9 } };
static PRT_STRING P_NMDTUP_N_10[] = { "Server", "ServerAdded" };
static PRT_TYPE* P_NMDTUP_T_10[] = { &P_GEND_TYPE_m, &P_GEND_TYPE_b };
static PRT_NMDTUPTYPE P_NMDTUP_10 = { 2U, P_NMDTUP_N_10, P_NMDTUP_T_10 };
static PRT_TYPE P_GEND_TYPE_T2mb = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_10 } };
static PRT_STRING P_NMDTUP_N_11[] = { "Server", "ServerRemoved" };
static PRT_TYPE* P_NMDTUP_T_11[] = { &P_GEND_TYPE_m, &P_GEND_TYPE_b };
static PRT_NMDTUPTYPE P_NMDTUP_11 = { 2U, P_NMDTUP_N_11, P_NMDTUP_T_11 };
static PRT_TYPE P_GEND_TYPE_T2mb_1 = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_11 } };
static PRT_STRING P_NMDTUP_N_12[] = { "Server", "Logs" };
static PRT_TYPE* P_NMDTUP_T_12[] = { &P_GEND_TYPE_m, &P_GEND_TYPE_ST3irr };
static PRT_NMDTUPTYPE P_NMDTUP_12 = { 2U, P_NMDTUP_N_12, P_NMDTUP_T_12 };
static PRT_TYPE P_GEND_TYPE_T2mST3irr = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_12 } };
static PRT_STRING P_NMDTUP_N_13[] = { "Term", "Logs" };
static PRT_TYPE* P_NMDTUP_T_13[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_ST3irr };
static PRT_NMDTUPTYPE P_NMDTUP_13 = { 2U, P_NMDTUP_N_13, P_NMDTUP_T_13 };
static PRT_TYPE P_GEND_TYPE_T2iST3irr = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_13 } };
static PRT_STRING P_NMDTUP_N_14[] = { "Servers", "ClusterManager" };
static PRT_TYPE P_GEND_TYPE_R = { PRT_KIND_MACHINE, { NULL } };
static PRT_TYPE* P_NMDTUP_T_14[] = { &P_GEND_TYPE_Sm, &P_GEND_TYPE_R };
static PRT_NMDTUPTYPE P_NMDTUP_14 = { 2U, P_NMDTUP_N_14, P_NMDTUP_T_14 };
static PRT_TYPE P_GEND_TYPE_T2SmR = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_14 } };
static PRT_MAPTYPE P_MAPTYPE = { &P_GEND_TYPE_i, &P_GEND_TYPE_b };
static PRT_TYPE P_GEND_TYPE_MKiVb = { PRT_KIND_MAP, { .map = &P_MAPTYPE } };
static PRT_MAPTYPE P_MAPTYPE_1 = { &P_GEND_TYPE_m, &P_GEND_TYPE_ST3irr };
static PRT_TYPE P_GEND_TYPE_MKmVST3irr = { PRT_KIND_MAP, { .map = &P_MAPTYPE_1 } };
static PRT_MAPTYPE P_MAPTYPE_2 = { &P_GEND_TYPE_i, &P_GEND_TYPE_ST3irr };
static PRT_TYPE P_GEND_TYPE_MKiVST3irr = { PRT_KIND_MAP, { .map = &P_MAPTYPE_2 } };
static PRT_SEQTYPE P_SEQTYPE_3 = { &P_GEND_TYPE_i };
static PRT_TYPE P_GEND_TYPE_Si = { PRT_KIND_SEQ, { .seq = &P_SEQTYPE_3 } };
static PRT_MAPTYPE P_MAPTYPE_3 = { &P_GEND_TYPE_m, &P_GEND_TYPE_T2ii };
static PRT_TYPE P_GEND_TYPE_MKmVT2ii = { PRT_KIND_MAP, { .map = &P_MAPTYPE_3 } };
static PRT_STRING P_NMDTUP_N_15[] = { "Term", "CandidateId", "LastLogIndex", "LastLogTerm" };
static PRT_TYPE P_GEND_TYPE_R_1 = { PRT_KIND_MACHINE, { NULL } };
static PRT_TYPE* P_NMDTUP_T_15[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_R_1, &P_GEND_TYPE_T2ii, &P_GEND_TYPE_T2ii };
static PRT_NMDTUPTYPE P_NMDTUP_15 = { 4U, P_NMDTUP_N_15, P_NMDTUP_T_15 };
static PRT_TYPE P_GEND_TYPE_T4iRT2iiT2ii = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_15 } };
static PRT_STRING P_NMDTUP_N_16[] = { "Leader", "Term" };
static PRT_TYPE* P_NMDTUP_T_16[] = { &P_GEND_TYPE_R_1, &P_GEND_TYPE_i };
static PRT_NMDTUPTYPE P_NMDTUP_16 = { 2U, P_NMDTUP_N_16, P_NMDTUP_T_16 };
static PRT_TYPE P_GEND_TYPE_T2Ri = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_16 } };
static PRT_STRING P_NMDTUP_N_17[] = { "Server", "Logs" };
static PRT_TYPE* P_NMDTUP_T_17[] = { &P_GEND_TYPE_R_1, &P_GEND_TYPE_ST3irr };
static PRT_NMDTUPTYPE P_NMDTUP_17 = { 2U, P_NMDTUP_N_17, P_NMDTUP_T_17 };
static PRT_TYPE P_GEND_TYPE_T2RST3irr = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_17 } };
static PRT_STRING P_NMDTUP_N_18[] = { "Term", "LeaderId", "PrevLogIndex", "PrevLogTerm", "Entries", "CfgEntries", "LeaderCommit", "ReceiverEndpoint" };
static PRT_TYPE* P_NMDTUP_T_18[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_R_1, &P_GEND_TYPE_T2ii, &P_GEND_TYPE_T2ii, &P_GEND_TYPE_ST3irr, &P_GEND_TYPE_ST2iSm, &P_GEND_TYPE_T2ii, &P_GEND_TYPE_m };
static PRT_NMDTUPTYPE P_NMDTUP_18 = { 8U, P_NMDTUP_N_18, P_NMDTUP_T_18 };
static PRT_TYPE P_GEND_TYPE_T8iRT2iiT2iiST3irrST2iSmT2iim = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_18 } };
static PRT_STRING P_NMDTUP_N_19[] = { "Term", "Success", "KV", "Cfg", "Server", "ReceiverEndpoint" };
static PRT_TYPE* P_NMDTUP_T_19[] = { &P_GEND_TYPE_i, &P_GEND_TYPE_b, &P_GEND_TYPE_b, &P_GEND_TYPE_b, &P_GEND_TYPE_R_1, &P_GEND_TYPE_m };
static PRT_NMDTUPTYPE P_NMDTUP_19 = { 6U, P_NMDTUP_N_19, P_NMDTUP_T_19 };
static PRT_TYPE P_GEND_TYPE_T6ibbbRm = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_19 } };
static PRT_STRING P_NMDTUP_N_20[] = { "Client", "Key", "Val" };
static PRT_TYPE P_GEND_TYPE_R_2 = { PRT_KIND_MACHINE, { NULL } };
static PRT_TYPE* P_NMDTUP_T_20[] = { &P_GEND_TYPE_R_2, &P_GEND_TYPE_r, &P_GEND_TYPE_r };
static PRT_NMDTUPTYPE P_NMDTUP_20 = { 3U, P_NMDTUP_N_20, P_NMDTUP_T_20 };
static PRT_TYPE P_GEND_TYPE_T3Rrr = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_20 } };
static PRT_STRING P_NMDTUP_N_21[] = { "Client", "Key", "Val" };
static PRT_TYPE P_GEND_TYPE_R_3 = { PRT_KIND_MACHINE, { NULL } };
static PRT_TYPE* P_NMDTUP_T_21[] = { &P_GEND_TYPE_R_3, &P_GEND_TYPE_r, &P_GEND_TYPE_r };
static PRT_NMDTUPTYPE P_NMDTUP_21 = { 3U, P_NMDTUP_N_21, P_NMDTUP_T_21 };
static PRT_TYPE P_GEND_TYPE_T3Rrr_1 = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_21 } };
static PRT_STRING P_NMDTUP_N_22[] = { "Client", "Key", "Val" };
static PRT_TYPE P_GEND_TYPE_R_4 = { PRT_KIND_MACHINE, { NULL } };
static PRT_TYPE* P_NMDTUP_T_22[] = { &P_GEND_TYPE_R_4, &P_GEND_TYPE_r, &P_GEND_TYPE_r };
static PRT_NMDTUPTYPE P_NMDTUP_22 = { 3U, P_NMDTUP_N_22, P_NMDTUP_T_22 };
static PRT_TYPE P_GEND_TYPE_T3Rrr_2 = { PRT_KIND_NMDTUP, { .nmTuple = &P_NMDTUP_22 } };

// Function implementation prototypes:
PRT_VALUE* P_Anon_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon;

PRT_VALUE* P_Anon_IMPL_1(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_1;

PRT_VALUE* P_Anon_IMPL_2(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_2;

PRT_VALUE* P_Anon_IMPL_3(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_3;

PRT_VALUE* P_Anon_IMPL_4(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_4;

PRT_VALUE* P_Anon_IMPL_5(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_5;

PRT_VALUE* P_UpdateLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_UpdateLeader;

PRT_VALUE* P_ShuttingDown_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_ShuttingDown;

PRT_VALUE* P_Anon_IMPL_6(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_6;

PRT_VALUE* P_Anon_IMPL_7(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_7;

PRT_VALUE* P_Anon_IMPL_8(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_8;

PRT_VALUE* P_Anon_IMPL_9(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_9;

PRT_VALUE* P_Anon_IMPL_10(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_10;

PRT_VALUE* P_Anon_IMPL_11(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_11;

PRT_VALUE* P_Anon_IMPL_12(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_12;

PRT_VALUE* P_Anon_IMPL_13(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_13;

PRT_VALUE* P_AddServerToCluster_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_AddServerToCluster;

PRT_VALUE* P_RemoveServerFromCluster_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_RemoveServerFromCluster;

PRT_VALUE* P_Anon_IMPL_14(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_14;

PRT_VALUE* P_Anon_IMPL_15(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_15;

PRT_VALUE* P_Anon_IMPL_16(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_16;

PRT_VALUE* P_Anon_IMPL_17(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_17;

PRT_VALUE* P_ProcessLeaderElected_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_ProcessLeaderElected;

PRT_VALUE* P_ProcessLogAppend_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_ProcessLogAppend;

PRT_VALUE* P_getSharedMinIndex_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_getSharedMinIndex;

PRT_VALUE* P_Anon_IMPL_18(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_18;

PRT_VALUE* P_Anon_IMPL_19(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_19;

PRT_VALUE* P_configServer_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_configServer;

PRT_VALUE* P_getMaxTickValue_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_getMaxTickValue;

PRT_VALUE* P_Anon_IMPL_20(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_20;

PRT_VALUE* P_Anon_IMPL_21(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_21;

PRT_VALUE* P_Anon_IMPL_22(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_22;

PRT_VALUE* P_Anon_IMPL_23(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_23;

PRT_VALUE* P_Anon_IMPL_24(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_24;

PRT_VALUE* P_Anon_IMPL_25(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_25;

PRT_VALUE* P_Anon_IMPL_26(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_26;

PRT_VALUE* P_Anon_IMPL_27(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_27;

PRT_VALUE* P_Anon_IMPL_28(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_28;

PRT_VALUE* P_Anon_IMPL_29(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_29;

PRT_VALUE* P_Anon_IMPL_30(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_30;

PRT_VALUE* P_Anon_IMPL_31(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_31;

PRT_VALUE* P_Anon_IMPL_32(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_32;

PRT_VALUE* P_Anon_IMPL_33(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_33;

PRT_VALUE* P_Anon_IMPL_34(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_34;

PRT_VALUE* P_Anon_IMPL_35(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_35;

PRT_VALUE* P_Anon_IMPL_36(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_36;

PRT_VALUE* P_Anon_IMPL_37(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_37;

PRT_VALUE* P_Anon_IMPL_38(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_38;

PRT_VALUE* P_BroadcastVoteRequests_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_BroadcastVoteRequests;

PRT_VALUE* P_RespondAppendEntriesAsCandidate_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_RespondAppendEntriesAsCandidate;

PRT_VALUE* P_Anon_IMPL_39(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_39;

PRT_VALUE* P_Anon_IMPL_40(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_40;

PRT_VALUE* P_Anon_IMPL_41(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_41;

PRT_VALUE* P_Anon_IMPL_42(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_42;

PRT_VALUE* P_Anon_IMPL_43(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_43;

PRT_VALUE* P_Anon_IMPL_44(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_44;

PRT_VALUE* P_Anon_IMPL_45(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_45;

PRT_VALUE* P_Anon_IMPL_46(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_46;

PRT_VALUE* P_Anon_IMPL_47(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_47;

PRT_VALUE* P_AddServerToConfig_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_AddServerToConfig;

PRT_VALUE* P_RemoveServerFromConfig_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_RemoveServerFromConfig;

PRT_VALUE* P_UpdateFollowerConfigs_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_UpdateFollowerConfigs;

PRT_VALUE* P_ProcessClientRequest_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_ProcessClientRequest;

PRT_VALUE* P_PrintLog_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_PrintLog;

PRT_VALUE* P_HeartbeatSendAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_HeartbeatSendAsLeader;

PRT_VALUE* P_VoteAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_VoteAsLeader;

PRT_VALUE* P_RespondVoteAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_RespondVoteAsLeader;

PRT_VALUE* P_AppendEntriesAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_AppendEntriesAsLeader;

PRT_VALUE* P_RespondAppendEntriesAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_RespondAppendEntriesAsLeader;

PRT_VALUE* P_Vote_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Vote;

PRT_VALUE* P_AppendEntries_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_AppendEntries;

PRT_VALUE* P_DeleteFromLog_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_DeleteFromLog;

PRT_VALUE* P_RedirectLastClientRequestToClusterManager_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_RedirectLastClientRequestToClusterManager;

PRT_VALUE* P_GetLogTermForIndex_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_GetLogTermForIndex;

PRT_VALUE* P_ShuttingDown_IMPL_1(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_ShuttingDown_1;

PRT_VALUE* P_Anon_IMPL_48(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_48;

PRT_VALUE* P_Anon_IMPL_49(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_49;

PRT_VALUE* P_Anon_IMPL_50(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_50;

PRT_VALUE* P_SendRequestToCluster_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_SendRequestToCluster;

PRT_VALUE* P_Anon_IMPL_51(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_51;

PRT_VALUE* P_Anon_IMPL_52(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_52;

PRT_VALUE* P_Anon_IMPL_53(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_53;

PRT_VALUE* P_SendRequestToCluster_IMPL_1(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_SendRequestToCluster_1;

PRT_VALUE* P_Anon_IMPL_54(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_54;

PRT_VALUE* P_Anon_IMPL_55(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_55;

PRT_VALUE* P_Anon_IMPL_56(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_56;

PRT_VALUE* P_Anon_IMPL_57(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_57;

PRT_VALUE* P_Anon_IMPL_58(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_58;

PRT_VALUE* P_SendRequestToCluster_IMPL_2(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_SendRequestToCluster_2;

PRT_VALUE* P_Anon_IMPL_59(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_59;

PRT_VALUE* P_Anon_IMPL_60(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_60;

PRT_VALUE* P_Anon_IMPL_61(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Anon_61;

PRT_VALUE* P_Tick_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs);
extern PRT_FUNDECL P_FUNCTION_Tick;


PRT_EVENTDECL P_EVENT_NotifyLeaderUpdate = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "NotifyLeaderUpdate",
    4294967295U,
    &P_GEND_TYPE_T2mi
};

PRT_EVENTDECL P_EVENT_RedirectRequest = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "RedirectRequest",
    4294967295U,
    &P_GEND_TYPE_T3mrr
};

PRT_EVENTDECL P_EVENT_ShutDown = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "ShutDown",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_MakeUnavailable = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "MakeUnavailable",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_LocalEvent = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "LocalEvent",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_CConfigureEvent = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "CConfigureEvent",
    4294967295U,
    &P_GEND_TYPE_m
};

PRT_EVENTDECL P_EVENT_Response = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "Response",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_SConfigureEvent = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "SConfigureEvent",
    4294967295U,
    &P_GEND_TYPE_T2Smm
};

PRT_EVENTDECL P_EVENT_VoteRequest = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "VoteRequest",
    4294967295U,
    &P_GEND_TYPE_T4imT2iiT2ii
};

PRT_EVENTDECL P_EVENT_VoteResponse = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "VoteResponse",
    4294967295U,
    &P_GEND_TYPE_T2ib
};

PRT_EVENTDECL P_EVENT_AppendEntriesRequest = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "AppendEntriesRequest",
    4294967295U,
    &P_GEND_TYPE_T8imT2iiT2iiST3irrST2iSmT2iim
};

PRT_EVENTDECL P_EVENT_AppendEntriesResponse = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "AppendEntriesResponse",
    4294967295U,
    &P_GEND_TYPE_T6ibbbmm
};

PRT_EVENTDECL P_EVENT_BecomeFollower = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "BecomeFollower",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_BecomeCandidate = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "BecomeCandidate",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_BecomeLeader = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "BecomeLeader",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_ConfigureWallclock = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "ConfigureWallclock",
    4294967295U,
    &P_GEND_TYPE_T2Smm
};

PRT_EVENTDECL P_EVENT_TickEvent = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "TickEvent",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_CancelTimer = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "CancelTimer",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_StartTimer = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "StartTimer",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_SentAllTicks = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "SentAllTicks",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_CheckLogsOnShutDown = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "CheckLogsOnShutDown",
    4294967295U,
    &P_GEND_TYPE_Sm
};

PRT_EVENTDECL P_EVENT_UpdateServers = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "UpdateServers",
    4294967295U,
    &P_GEND_TYPE_Sm
};

PRT_EVENTDECL P_EVENT_UpdateServersResponse = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "UpdateServersResponse",
    4294967295U,
    &P_GEND_TYPE_b
};

PRT_EVENTDECL P_EVENT_AddServerResponse = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "AddServerResponse",
    4294967295U,
    &P_GEND_TYPE_T2mb
};

PRT_EVENTDECL P_EVENT_RemoveServerResponse = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "RemoveServerResponse",
    4294967295U,
    &P_GEND_TYPE_T2mb_1
};

PRT_EVENTDECL P_EVENT_EMonitorInit = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "EMonitorInit",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL P_EVENT_Request = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "Request",
    4294967295U,
    &P_GEND_TYPE_T3mrr
};

PRT_EVENTDECL P_EVENT_AddServer = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "AddServer",
    4294967295U,
    &P_GEND_TYPE_m
};

PRT_EVENTDECL P_EVENT_RemoveServer = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "RemoveServer",
    4294967295U,
    &P_GEND_TYPE_m
};

PRT_EVENTDECL P_EVENT_M_LogAppend = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "M_LogAppend",
    4294967295U,
    &P_GEND_TYPE_T2mST3irr
};

PRT_EVENTDECL P_EVENT_M_NotifyLeaderElected = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "M_NotifyLeaderElected",
    4294967295U,
    &P_GEND_TYPE_T2iST3irr
};

PRT_EVENTDECL P_EVENT_M_LeaderCommitted = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "M_LeaderCommitted",
    4294967295U,
    &P_GEND_TYPE_ST3irr
};

PRT_EVENTDECL P_EVENT_InjectFailure = 
{
    { PRT_VALUE_KIND_EVENT, 0U },
    "InjectFailure",
    4294967295U,
    &P_GEND_TYPE_n
};

PRT_EVENTDECL* P_ClusterManager_RECV_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_ClusterManager_RECV =
{
    34U,
    P_ClusterManager_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_ClusterManager =
{
    0U,
    "ClusterManager",
    &P_GEND_TYPE_n,
    &P_EVENTSET_ClusterManager_RECV
};

PRT_EVENTDECL* P_Server_RECV_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_Server_RECV =
{
    34U,
    P_Server_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_Server =
{
    1U,
    "Server",
    &P_GEND_TYPE_n,
    &P_EVENTSET_Server_RECV
};

PRT_EVENTDECL* P_TestDriver0_RECV_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver0_RECV =
{
    34U,
    P_TestDriver0_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_TestDriver0 =
{
    2U,
    "TestDriver0",
    &P_GEND_TYPE_n,
    &P_EVENTSET_TestDriver0_RECV
};

PRT_EVENTDECL* P_TestDriver1_RECV_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver1_RECV =
{
    34U,
    P_TestDriver1_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_TestDriver1 =
{
    3U,
    "TestDriver1",
    &P_GEND_TYPE_n,
    &P_EVENTSET_TestDriver1_RECV
};

PRT_EVENTDECL* P_FailureInjector_RECV_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_FailureInjector_RECV =
{
    34U,
    P_FailureInjector_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_FailureInjector =
{
    4U,
    "FailureInjector",
    &P_GEND_TYPE_Sm,
    &P_EVENTSET_FailureInjector_RECV
};

PRT_EVENTDECL* P_TestDriver2_RECV_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver2_RECV =
{
    34U,
    P_TestDriver2_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_TestDriver2 =
{
    5U,
    "TestDriver2",
    &P_GEND_TYPE_n,
    &P_EVENTSET_TestDriver2_RECV
};

PRT_EVENTDECL* P_WallclockTimer_RECV_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_WallclockTimer_RECV =
{
    34U,
    P_WallclockTimer_RECV_INNER,
    NULL
};

PRT_INTERFACEDECL P_I_WallclockTimer =
{
    6U,
    "WallclockTimer",
    &P_GEND_TYPE_n,
    &P_EVENTSET_WallclockTimer_RECV
};

PRT_VARDECL P_ClusterManager_VARS[] = {
    { "Servers", &P_GEND_TYPE_Sm },
    { "NumberOfServers", &P_GEND_TYPE_i },
    { "Leader", &P_GEND_TYPE_m },
    { "LeaderTerm", &P_GEND_TYPE_i },
    { "Client", &P_GEND_TYPE_m },
    { "Timer", &P_GEND_TYPE_m },
    { "UpdatingConfig", &P_GEND_TYPE_b }
};

PRT_EVENTDECL* P_Init_DEFERS_INNER[] = { &P_EVENT_AddServer, &P_EVENT_RemoveServer, &P_EVENT_SentAllTicks };
PRT_EVENTSETDECL P_EVENTSET_Init_DEFERS =
{
    3U,
    P_Init_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Init_TRANS_INNER[] = { &P_EVENT_LocalEvent };
PRT_EVENTSETDECL P_EVENTSET_Init_TRANS =
{
    1U,
    P_Init_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Init_DOS_INNER[] = { &P_EVENT_MakeUnavailable };
PRT_EVENTSETDECL P_EVENTSET_Init_DOS =
{
    1U,
    P_Init_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS[] =
{
    { 0, &P_EVENT_LocalEvent, 1, &_P_NO_OP }
};

PRT_DODECL P_DOS[] =
{
    { 0, &P_EVENT_MakeUnavailable, NULL }
};

#define P_STATE_ClusterManager_Init \
{ \
    "ClusterManager.Init", \
    1U, \
    1U, \
    &P_EVENTSET_Init_DEFERS, \
    &P_EVENTSET_Init_TRANS, \
    &P_EVENTSET_Init_DOS, \
    P_TRANS, \
    P_DOS, \
    &P_FUNCTION_Anon, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Initialize_DEFERS_INNER[] = { &P_EVENT_RemoveServer };
PRT_EVENTSETDECL P_EVENTSET_Initialize_DEFERS =
{
    1U,
    P_Initialize_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Initialize_TRANS_INNER[] = { &P_EVENT_LocalEvent };
PRT_EVENTSETDECL P_EVENTSET_Initialize_TRANS =
{
    1U,
    P_Initialize_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Initialize_DOS_INNER[] = { &P_EVENT_AddServer, &P_EVENT_MakeUnavailable };
PRT_EVENTSETDECL P_EVENTSET_Initialize_DOS =
{
    2U,
    P_Initialize_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_1[] =
{
    { 1, &P_EVENT_LocalEvent, 2, &_P_NO_OP }
};

PRT_DODECL P_DOS_1[] =
{
    { 1, &P_EVENT_AddServer, &P_FUNCTION_Anon_2 },
    { 1, &P_EVENT_MakeUnavailable, NULL }
};

#define P_STATE_ClusterManager_Initialize \
{ \
    "ClusterManager.Initialize", \
    1U, \
    2U, \
    &P_EVENTSET_Initialize_DEFERS, \
    &P_EVENTSET_Initialize_TRANS, \
    &P_EVENTSET_Initialize_DOS, \
    P_TRANS_1, \
    P_DOS_1, \
    &P_FUNCTION_Anon_1, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Unavailable_DEFERS_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request };
PRT_EVENTSETDECL P_EVENTSET_Unavailable_DEFERS =
{
    5U,
    P_Unavailable_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Unavailable_TRANS_INNER[] = { &P_EVENT_LocalEvent };
PRT_EVENTSETDECL P_EVENTSET_Unavailable_TRANS =
{
    1U,
    P_Unavailable_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Unavailable_DOS_INNER[] = { &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown };
PRT_EVENTSETDECL P_EVENTSET_Unavailable_DOS =
{
    4U,
    P_Unavailable_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_2[] =
{
    { 2, &P_EVENT_LocalEvent, 3, &_P_NO_OP }
};

PRT_DODECL P_DOS_2[] =
{
    { 2, &P_EVENT_NotifyLeaderUpdate, &P_FUNCTION_Anon_4 },
    { 2, &P_EVENT_ShutDown, &P_FUNCTION_ShuttingDown },
    { 2, &P_EVENT_SentAllTicks, &P_FUNCTION_Anon_5 },
    { 2, &P_EVENT_MakeUnavailable, NULL }
};

#define P_STATE_ClusterManager_Unavailable \
{ \
    "ClusterManager.Unavailable", \
    1U, \
    4U, \
    &P_EVENTSET_Unavailable_DEFERS, \
    &P_EVENTSET_Unavailable_TRANS, \
    &P_EVENTSET_Unavailable_DOS, \
    P_TRANS_2, \
    P_DOS_2, \
    &P_FUNCTION_Anon_3, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Available_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Available_DEFERS =
{
    0U,
    P_Available_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Available_TRANS_INNER[] = { &P_EVENT_LocalEvent, &P_EVENT_MakeUnavailable };
PRT_EVENTSETDECL P_EVENTSET_Available_TRANS =
{
    2U,
    P_Available_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Available_DOS_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown };
PRT_EVENTSETDECL P_EVENTSET_Available_DOS =
{
    9U,
    P_Available_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_3[] =
{
    { 3, &P_EVENT_LocalEvent, 2, &_P_NO_OP },
    { 3, &P_EVENT_MakeUnavailable, 2, &_P_NO_OP }
};

PRT_DODECL P_DOS_3[] =
{
    { 3, &P_EVENT_Request, &P_FUNCTION_Anon_6 },
    { 3, &P_EVENT_RedirectRequest, &P_FUNCTION_Anon_7 },
    { 3, &P_EVENT_NotifyLeaderUpdate, &P_FUNCTION_Anon_8 },
    { 3, &P_EVENT_AddServer, &P_FUNCTION_Anon_9 },
    { 3, &P_EVENT_RemoveServer, &P_FUNCTION_Anon_10 },
    { 3, &P_EVENT_AddServerResponse, &P_FUNCTION_Anon_11 },
    { 3, &P_EVENT_RemoveServerResponse, &P_FUNCTION_Anon_12 },
    { 3, &P_EVENT_ShutDown, &P_FUNCTION_ShuttingDown },
    { 3, &P_EVENT_SentAllTicks, &P_FUNCTION_Anon_13 }
};

#define P_STATE_ClusterManager_Available \
{ \
    "ClusterManager.Available", \
    2U, \
    9U, \
    &P_EVENTSET_Available_DEFERS, \
    &P_EVENTSET_Available_TRANS, \
    &P_EVENTSET_Available_DOS, \
    P_TRANS_3, \
    P_DOS_3, \
    &_P_NO_OP, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_ClusterManager_STATES[] = { P_STATE_ClusterManager_Init, P_STATE_ClusterManager_Initialize, P_STATE_ClusterManager_Unavailable, P_STATE_ClusterManager_Available };

PRT_VALUE* P_Anon_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0 = NULL;
    PRT_VALUE* PTMP_tmp1 = NULL;
    PRT_VALUE* PTMP_tmp2 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_1 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE = &(p_this->varValues[1]);
    PrtFreeValue(*P_LVALUE);
    *P_LVALUE = PrtCloneValue((&P_LIT_INT32));
    
    PRT_VALUE** P_LVALUE_1 = &(PTMP_tmp0);
    PrtFreeValue(*P_LVALUE_1);
    *P_LVALUE_1 = PrtMkIntValue(-PrtPrimGetInt((&P_LIT_INT32_1)));
    
    {
        PRT_VALUE** P_LVALUE_2 = &(p_this->varValues[3]);
        PrtFreeValue(*P_LVALUE_2);
        *P_LVALUE_2 = PTMP_tmp0;
        PTMP_tmp0 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_3 = &(PTMP_tmp1);
    PrtFreeValue(*P_LVALUE_3);
    *P_LVALUE_3 = PrtMkDefaultValue(&P_GEND_TYPE_Sm);
    
    {
        PRT_VALUE** P_LVALUE_4 = &(p_this->varValues[0]);
        PrtFreeValue(*P_LVALUE_4);
        *P_LVALUE_4 = PTMP_tmp1;
        PTMP_tmp1 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_5 = &(p_this->varValues[6]);
    PrtFreeValue(*P_LVALUE_5);
    *P_LVALUE_5 = PrtCloneValue((&P_LIT_BOOLEAN));
    
    PRT_VALUE** P_LVALUE_6 = &(PTMP_tmp2);
    PrtFreeValue(*P_LVALUE_6);
    *P_LVALUE_6 = PrtCloneValue((&P_EVENT_LocalEvent.value));
    
    PrtRaise(p_this, PTMP_tmp2, 0);
    *(&(PTMP_tmp2)) = NULL;
    goto p_return;
    
p_return: ;
    PrtFreeValue(PTMP_tmp0); PTMP_tmp0 = NULL;
    PrtFreeValue(PTMP_tmp1); PTMP_tmp1 = NULL;
    PrtFreeValue(PTMP_tmp2); PTMP_tmp2 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon =
{
    NULL,
    &P_Anon_IMPL,
    NULL
};


PRT_VALUE* P_Anon_IMPL_1(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_idx = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_1 = NULL;
    PRT_VALUE* PTMP_tmp1_1 = NULL;
    PRT_VALUE* PTMP_tmp2_1 = NULL;
    PRT_VALUE* PTMP_tmp3 = NULL;
    PRT_VALUE* PTMP_tmp4 = NULL;
    PRT_VALUE* PTMP_tmp5 = NULL;
    PRT_VALUE* PTMP_tmp6 = NULL;
    PRT_VALUE* PTMP_tmp7 = NULL;
    PRT_VALUE* PTMP_tmp8 = NULL;
    PRT_VALUE* PTMP_tmp9 = NULL;
    PRT_VALUE* PTMP_tmp10 = NULL;
    PRT_VALUE* PTMP_tmp11 = NULL;
    PRT_VALUE* PTMP_tmp12 = NULL;
    PRT_VALUE* PTMP_tmp13 = NULL;
    PRT_VALUE* PTMP_tmp14 = NULL;
    PRT_VALUE* PTMP_tmp15 = NULL;
    PRT_VALUE* PTMP_tmp16 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_2 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_3 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_INT32_4 = { PRT_VALUE_KIND_INT, { .nt = 2 } };
    PRT_VALUE P_LIT_BOOLEAN_1 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_7 = &(P_VAR_idx);
    PrtFreeValue(*P_LVALUE_7);
    *P_LVALUE_7 = PrtCloneValue((&P_LIT_INT32_2));
    
    PRT_VALUE** P_LVALUE_8 = &(PTMP_tmp0_1);
    PrtFreeValue(*P_LVALUE_8);
    *P_LVALUE_8 = PrtCloneValue(PrtMkInterface(context, 6, 0)->id);
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_1;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_1;
    }
    
    {
        PRT_VALUE** P_LVALUE_9 = &(p_this->varValues[5]);
        PrtFreeValue(*P_LVALUE_9);
        *P_LVALUE_9 = PTMP_tmp0_1;
        PTMP_tmp0_1 = NULL;
    }
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_1)))
    {
        PRT_VALUE** P_LVALUE_10 = &(PTMP_tmp1_1);
        PrtFreeValue(*P_LVALUE_10);
        *P_LVALUE_10 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx) < PrtPrimGetInt(p_this->varValues[1]));
        
        PRT_VALUE** P_LVALUE_11 = &(PTMP_tmp2_1);
        PrtFreeValue(*P_LVALUE_11);
        *P_LVALUE_11 = PrtCloneValue(PTMP_tmp1_1);
        
        if (PrtPrimGetBool(PTMP_tmp2_1))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PrtFormatPrintf("[ClusterManager | Initialize] Initializing server ", 1, P_VAR_idx, 1, 0, "");
        
        PRT_VALUE** P_LVALUE_12 = &(PTMP_tmp3);
        PrtFreeValue(*P_LVALUE_12);
        *P_LVALUE_12 = PrtSeqGet(p_this->varValues[0], P_VAR_idx);
        
        PRT_VALUE** P_LVALUE_13 = &(PTMP_tmp4);
        PrtFreeValue(*P_LVALUE_13);
        *P_LVALUE_13 = PrtCloneValue(PTMP_tmp3);
        
        PRT_VALUE** P_LVALUE_14 = &(PTMP_tmp5);
        PrtFreeValue(*P_LVALUE_14);
        *P_LVALUE_14 = PrtCloneValue((&P_EVENT_SConfigureEvent.value));
        
        PRT_VALUE** P_LVALUE_15 = &(PTMP_tmp6);
        PrtFreeValue(*P_LVALUE_15);
        *P_LVALUE_15 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_16 = &(PTMP_tmp7);
        PrtFreeValue(*P_LVALUE_16);
        *P_LVALUE_16 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_17 = &(PTMP_tmp8);
        PrtFreeValue(*P_LVALUE_17);
        *P_LVALUE_17 = (PrtMkTuple(&P_GEND_TYPE_T2SmR, &(PTMP_tmp6), &(PTMP_tmp7)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp4), PTMP_tmp5, 1, &(PTMP_tmp8));
        *(&(PTMP_tmp5)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_1;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_1;
        }
        
        PRT_VALUE** P_LVALUE_18 = &(PTMP_tmp9);
        PrtFreeValue(*P_LVALUE_18);
        *P_LVALUE_18 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx) + PrtPrimGetInt((&P_LIT_INT32_3)));
        
        {
            PRT_VALUE** P_LVALUE_19 = &(P_VAR_idx);
            PrtFreeValue(*P_LVALUE_19);
            *P_LVALUE_19 = PTMP_tmp9;
            PTMP_tmp9 = NULL;
        }
        
    }
    
    
    PRT_VALUE** P_LVALUE_20 = &(PTMP_tmp10);
    PrtFreeValue(*P_LVALUE_20);
    *P_LVALUE_20 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[1]) > PrtPrimGetInt((&P_LIT_INT32_4)));
    
    if (PrtPrimGetBool(PTMP_tmp10))
    {
        PRT_VALUE** P_LVALUE_21 = &(PTMP_tmp11);
        PrtFreeValue(*P_LVALUE_21);
        *P_LVALUE_21 = PrtCloneValue(p_this->varValues[5]);
        
        PRT_VALUE** P_LVALUE_22 = &(PTMP_tmp12);
        PrtFreeValue(*P_LVALUE_22);
        *P_LVALUE_22 = PrtCloneValue((&P_EVENT_ConfigureWallclock.value));
        
        PRT_VALUE** P_LVALUE_23 = &(PTMP_tmp13);
        PrtFreeValue(*P_LVALUE_23);
        *P_LVALUE_23 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_24 = &(PTMP_tmp14);
        PrtFreeValue(*P_LVALUE_24);
        *P_LVALUE_24 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_25 = &(PTMP_tmp15);
        PrtFreeValue(*P_LVALUE_25);
        *P_LVALUE_25 = (PrtMkTuple(&P_GEND_TYPE_T2SmR, &(PTMP_tmp13), &(PTMP_tmp14)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp11), PTMP_tmp12, 1, &(PTMP_tmp15));
        *(&(PTMP_tmp12)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_1;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_1;
        }
        
        PRT_VALUE** P_LVALUE_26 = &(PTMP_tmp16);
        PrtFreeValue(*P_LVALUE_26);
        *P_LVALUE_26 = PrtCloneValue((&P_EVENT_LocalEvent.value));
        
        PrtRaise(p_this, PTMP_tmp16, 0);
        *(&(PTMP_tmp16)) = NULL;
        goto p_return_1;
        
    }
    
    else
    {
    }
    
    
p_return_1: ;
    PrtFreeValue(P_VAR_idx); P_VAR_idx = NULL;
    PrtFreeValue(PTMP_tmp0_1); PTMP_tmp0_1 = NULL;
    PrtFreeValue(PTMP_tmp1_1); PTMP_tmp1_1 = NULL;
    PrtFreeValue(PTMP_tmp2_1); PTMP_tmp2_1 = NULL;
    PrtFreeValue(PTMP_tmp3); PTMP_tmp3 = NULL;
    PrtFreeValue(PTMP_tmp4); PTMP_tmp4 = NULL;
    PrtFreeValue(PTMP_tmp5); PTMP_tmp5 = NULL;
    PrtFreeValue(PTMP_tmp6); PTMP_tmp6 = NULL;
    PrtFreeValue(PTMP_tmp7); PTMP_tmp7 = NULL;
    PrtFreeValue(PTMP_tmp8); PTMP_tmp8 = NULL;
    PrtFreeValue(PTMP_tmp9); PTMP_tmp9 = NULL;
    PrtFreeValue(PTMP_tmp10); PTMP_tmp10 = NULL;
    PrtFreeValue(PTMP_tmp11); PTMP_tmp11 = NULL;
    PrtFreeValue(PTMP_tmp12); PTMP_tmp12 = NULL;
    PrtFreeValue(PTMP_tmp13); PTMP_tmp13 = NULL;
    PrtFreeValue(PTMP_tmp14); PTMP_tmp14 = NULL;
    PrtFreeValue(PTMP_tmp15); PTMP_tmp15 = NULL;
    PrtFreeValue(PTMP_tmp16); PTMP_tmp16 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_1 =
{
    NULL,
    &P_Anon_IMPL_1,
    NULL
};


PRT_VALUE* P_Anon_IMPL_2(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server = argRefs[0];
    PRT_VALUE* P_VAR_idx_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_2 = NULL;
    PRT_VALUE* PTMP_tmp1_2 = NULL;
    PRT_VALUE* PTMP_tmp2_2 = NULL;
    PRT_VALUE* PTMP_tmp3_1 = NULL;
    PRT_VALUE* PTMP_tmp4_1 = NULL;
    PRT_VALUE* PTMP_tmp5_1 = NULL;
    PRT_VALUE* PTMP_tmp6_1 = NULL;
    PRT_VALUE* PTMP_tmp7_1 = NULL;
    PRT_VALUE* PTMP_tmp8_1 = NULL;
    PRT_VALUE* PTMP_tmp9_1 = NULL;
    PRT_VALUE* PTMP_tmp10_1 = NULL;
    PRT_VALUE* PTMP_tmp11_1 = NULL;
    PRT_VALUE* PTMP_tmp12_1 = NULL;
    PRT_VALUE* PTMP_tmp13_1 = NULL;
    PRT_VALUE* PTMP_tmp14_1 = NULL;
    PRT_VALUE* PTMP_tmp15_1 = NULL;
    PRT_VALUE* PTMP_tmp16_1 = NULL;
    PRT_VALUE* PTMP_tmp17 = NULL;
    PRT_VALUE* PTMP_tmp18 = NULL;
    PRT_VALUE* PTMP_tmp19 = NULL;
    PRT_VALUE* PTMP_tmp20 = NULL;
    PRT_VALUE* PTMP_tmp21 = NULL;
    PRT_VALUE* PTMP_tmp22 = NULL;
    PRT_VALUE* PTMP_tmp23 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_5 = { PRT_VALUE_KIND_INT, { .nt = 2 } };
    PRT_VALUE P_LIT_INT32_6 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_7 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_2 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_27 = &(PTMP_tmp0_2);
    PrtFreeValue(*P_LVALUE_27);
    *P_LVALUE_27 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[1]) > PrtPrimGetInt((&P_LIT_INT32_5)));
    
    if (PrtPrimGetBool(PTMP_tmp0_2))
    {
        PRT_VALUE** P_LVALUE_28 = &(PTMP_tmp1_2);
        PrtFreeValue(*P_LVALUE_28);
        *P_LVALUE_28 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_29 = &(PTMP_tmp2_2);
        PrtFreeValue(*P_LVALUE_29);
        *P_LVALUE_29 = PrtCloneValue((&P_EVENT_AddServer.value));
        
        PRT_VALUE** P_LVALUE_30 = &(PTMP_tmp3_1);
        PrtFreeValue(*P_LVALUE_30);
        *P_LVALUE_30 = PrtCloneValue(*P_VAR_server);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_2), PTMP_tmp2_2, 1, &(PTMP_tmp3_1));
        *(&(PTMP_tmp2_2)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_2;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_2;
        }
        
        PRT_VALUE** P_LVALUE_31 = &(PTMP_tmp4_1);
        PrtFreeValue(*P_LVALUE_31);
        *P_LVALUE_31 = PrtCloneValue((&P_EVENT_LocalEvent.value));
        
        PrtRaise(p_this, PTMP_tmp4_1, 0);
        *(&(PTMP_tmp4_1)) = NULL;
        goto p_return_2;
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_32 = &(P_VAR_idx_1);
        PrtFreeValue(*P_LVALUE_32);
        *P_LVALUE_32 = PrtCloneValue((&P_LIT_INT32_6));
        
        PRT_VALUE** P_LVALUE_33 = &(PTMP_tmp5_1);
        PrtFreeValue(*P_LVALUE_33);
        *P_LVALUE_33 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[0]));
        
        PRT_VALUE** P_LVALUE_34 = &(PTMP_tmp6_1);
        PrtFreeValue(*P_LVALUE_34);
        *P_LVALUE_34 = PrtCloneValue(*P_VAR_server);
        
        PrtSeqInsertEx(p_this->varValues[0], PTMP_tmp5_1, PTMP_tmp6_1, PRT_FALSE);
        *(&(PTMP_tmp6_1)) = NULL;
        
        PRT_VALUE** P_LVALUE_35 = &(PTMP_tmp7_1);
        PrtFreeValue(*P_LVALUE_35);
        *P_LVALUE_35 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[1]) + PrtPrimGetInt((&P_LIT_INT32_7)));
        
        {
            PRT_VALUE** P_LVALUE_36 = &(p_this->varValues[1]);
            PrtFreeValue(*P_LVALUE_36);
            *P_LVALUE_36 = PTMP_tmp7_1;
            PTMP_tmp7_1 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_37 = &(PTMP_tmp8_1);
        PrtFreeValue(*P_LVALUE_37);
        *P_LVALUE_37 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[1]) > PrtPrimGetInt((&P_LIT_INT32_5)));
        
        if (PrtPrimGetBool(PTMP_tmp8_1))
        {
            PRT_VALUE** P_LVALUE_38 = &(PTMP_tmp9_1);
            PrtFreeValue(*P_LVALUE_38);
            *P_LVALUE_38 = PrtCloneValue(p_this->varValues[5]);
            
            PRT_VALUE** P_LVALUE_39 = &(PTMP_tmp10_1);
            PrtFreeValue(*P_LVALUE_39);
            *P_LVALUE_39 = PrtCloneValue((&P_EVENT_ConfigureWallclock.value));
            
            PRT_VALUE** P_LVALUE_40 = &(PTMP_tmp11_1);
            PrtFreeValue(*P_LVALUE_40);
            *P_LVALUE_40 = PrtCloneValue(p_this->varValues[0]);
            
            PRT_VALUE** P_LVALUE_41 = &(PTMP_tmp12_1);
            PrtFreeValue(*P_LVALUE_41);
            *P_LVALUE_41 = PrtCloneValue((p_this->id));
            
            PRT_VALUE** P_LVALUE_42 = &(PTMP_tmp13_1);
            PrtFreeValue(*P_LVALUE_42);
            *P_LVALUE_42 = (PrtMkTuple(&P_GEND_TYPE_T2SmR, &(PTMP_tmp11_1), &(PTMP_tmp12_1)));
            
            PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp9_1), PTMP_tmp10_1, 1, &(PTMP_tmp13_1));
            *(&(PTMP_tmp10_1)) = NULL;
            if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                goto p_return_2;
            }
            if (p_this->isHalted == PRT_TRUE) {
                PrtFreeValue(_P_GEN_retval);
                _P_GEN_retval = NULL;
                goto p_return_2;
            }
            
            while (PrtPrimGetBool((&P_LIT_BOOLEAN_2)))
            {
                PRT_VALUE** P_LVALUE_43 = &(PTMP_tmp14_1);
                PrtFreeValue(*P_LVALUE_43);
                *P_LVALUE_43 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_1) < PrtPrimGetInt(p_this->varValues[1]));
                
                PRT_VALUE** P_LVALUE_44 = &(PTMP_tmp15_1);
                PrtFreeValue(*P_LVALUE_44);
                *P_LVALUE_44 = PrtCloneValue(PTMP_tmp14_1);
                
                if (PrtPrimGetBool(PTMP_tmp15_1))
                {
                }
                
                else
                {
                    break;
                    
                }
                
                
                PrtFormatPrintf("[ClusterManager | Initialize] Initializing server ", 1, P_VAR_idx_1, 1, 0, "");
                
                PRT_VALUE** P_LVALUE_45 = &(PTMP_tmp16_1);
                PrtFreeValue(*P_LVALUE_45);
                *P_LVALUE_45 = PrtSeqGet(p_this->varValues[0], P_VAR_idx_1);
                
                PRT_VALUE** P_LVALUE_46 = &(PTMP_tmp17);
                PrtFreeValue(*P_LVALUE_46);
                *P_LVALUE_46 = PrtCloneValue(PTMP_tmp16_1);
                
                PRT_VALUE** P_LVALUE_47 = &(PTMP_tmp18);
                PrtFreeValue(*P_LVALUE_47);
                *P_LVALUE_47 = PrtCloneValue((&P_EVENT_SConfigureEvent.value));
                
                PRT_VALUE** P_LVALUE_48 = &(PTMP_tmp19);
                PrtFreeValue(*P_LVALUE_48);
                *P_LVALUE_48 = PrtCloneValue(p_this->varValues[0]);
                
                PRT_VALUE** P_LVALUE_49 = &(PTMP_tmp20);
                PrtFreeValue(*P_LVALUE_49);
                *P_LVALUE_49 = PrtCloneValue((p_this->id));
                
                PRT_VALUE** P_LVALUE_50 = &(PTMP_tmp21);
                PrtFreeValue(*P_LVALUE_50);
                *P_LVALUE_50 = (PrtMkTuple(&P_GEND_TYPE_T2SmR, &(PTMP_tmp19), &(PTMP_tmp20)));
                
                PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp17), PTMP_tmp18, 1, &(PTMP_tmp21));
                *(&(PTMP_tmp18)) = NULL;
                if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                    goto p_return_2;
                }
                if (p_this->isHalted == PRT_TRUE) {
                    PrtFreeValue(_P_GEN_retval);
                    _P_GEN_retval = NULL;
                    goto p_return_2;
                }
                
                PRT_VALUE** P_LVALUE_51 = &(PTMP_tmp22);
                PrtFreeValue(*P_LVALUE_51);
                *P_LVALUE_51 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_1) + PrtPrimGetInt((&P_LIT_INT32_7)));
                
                {
                    PRT_VALUE** P_LVALUE_52 = &(P_VAR_idx_1);
                    PrtFreeValue(*P_LVALUE_52);
                    *P_LVALUE_52 = PTMP_tmp22;
                    PTMP_tmp22 = NULL;
                }
                
            }
            
            
            PRT_VALUE** P_LVALUE_53 = &(PTMP_tmp23);
            PrtFreeValue(*P_LVALUE_53);
            *P_LVALUE_53 = PrtCloneValue((&P_EVENT_LocalEvent.value));
            
            PrtRaise(p_this, PTMP_tmp23, 0);
            *(&(PTMP_tmp23)) = NULL;
            goto p_return_2;
            
        }
        
        else
        {
        }
        
        
    }
    
    
p_return_2: ;
    PrtFreeValue(P_VAR_idx_1); P_VAR_idx_1 = NULL;
    PrtFreeValue(PTMP_tmp0_2); PTMP_tmp0_2 = NULL;
    PrtFreeValue(PTMP_tmp1_2); PTMP_tmp1_2 = NULL;
    PrtFreeValue(PTMP_tmp2_2); PTMP_tmp2_2 = NULL;
    PrtFreeValue(PTMP_tmp3_1); PTMP_tmp3_1 = NULL;
    PrtFreeValue(PTMP_tmp4_1); PTMP_tmp4_1 = NULL;
    PrtFreeValue(PTMP_tmp5_1); PTMP_tmp5_1 = NULL;
    PrtFreeValue(PTMP_tmp6_1); PTMP_tmp6_1 = NULL;
    PrtFreeValue(PTMP_tmp7_1); PTMP_tmp7_1 = NULL;
    PrtFreeValue(PTMP_tmp8_1); PTMP_tmp8_1 = NULL;
    PrtFreeValue(PTMP_tmp9_1); PTMP_tmp9_1 = NULL;
    PrtFreeValue(PTMP_tmp10_1); PTMP_tmp10_1 = NULL;
    PrtFreeValue(PTMP_tmp11_1); PTMP_tmp11_1 = NULL;
    PrtFreeValue(PTMP_tmp12_1); PTMP_tmp12_1 = NULL;
    PrtFreeValue(PTMP_tmp13_1); PTMP_tmp13_1 = NULL;
    PrtFreeValue(PTMP_tmp14_1); PTMP_tmp14_1 = NULL;
    PrtFreeValue(PTMP_tmp15_1); PTMP_tmp15_1 = NULL;
    PrtFreeValue(PTMP_tmp16_1); PTMP_tmp16_1 = NULL;
    PrtFreeValue(PTMP_tmp17); PTMP_tmp17 = NULL;
    PrtFreeValue(PTMP_tmp18); PTMP_tmp18 = NULL;
    PrtFreeValue(PTMP_tmp19); PTMP_tmp19 = NULL;
    PrtFreeValue(PTMP_tmp20); PTMP_tmp20 = NULL;
    PrtFreeValue(PTMP_tmp21); PTMP_tmp21 = NULL;
    PrtFreeValue(PTMP_tmp22); PTMP_tmp22 = NULL;
    PrtFreeValue(PTMP_tmp23); PTMP_tmp23 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_2 =
{
    NULL,
    &P_Anon_IMPL_2,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_Anon_IMPL_3(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_3 = NULL;
    PRT_VALUE* PTMP_tmp1_3 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_54 = &(PTMP_tmp0_3);
    PrtFreeValue(*P_LVALUE_54);
    *P_LVALUE_54 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_55 = &(PTMP_tmp1_3);
    PrtFreeValue(*P_LVALUE_55);
    *P_LVALUE_55 = PrtCloneValue((&P_EVENT_StartTimer.value));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_3), PTMP_tmp1_3, 0);
    *(&(PTMP_tmp1_3)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_3;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_3;
    }
    
p_return_3: ;
    PrtFreeValue(PTMP_tmp0_3); PTMP_tmp0_3 = NULL;
    PrtFreeValue(PTMP_tmp1_3); PTMP_tmp1_3 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_3 =
{
    NULL,
    &P_Anon_IMPL_3,
    NULL
};


PRT_VALUE* P_Anon_IMPL_4(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload = argRefs[0];
    PRT_VALUE* PTMP_tmp0_4 = NULL;
    PRT_VALUE* PTMP_tmp1_4 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_56 = &(PTMP_tmp0_4);
    PrtFreeValue(*P_LVALUE_56);
    *P_LVALUE_56 = PrtCloneValue(*P_VAR_payload);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_4);
    PrtFreeValue(P_UpdateLeader_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_4);
    PTMP_tmp0_4 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_4;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_4;
    }
    
    PRT_VALUE** P_LVALUE_57 = &(PTMP_tmp1_4);
    PrtFreeValue(*P_LVALUE_57);
    *P_LVALUE_57 = PrtCloneValue((&P_EVENT_LocalEvent.value));
    
    PrtRaise(p_this, PTMP_tmp1_4, 0);
    *(&(PTMP_tmp1_4)) = NULL;
    goto p_return_4;
    
p_return_4: ;
    PrtFreeValue(PTMP_tmp0_4); PTMP_tmp0_4 = NULL;
    PrtFreeValue(PTMP_tmp1_4); PTMP_tmp1_4 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_4 =
{
    NULL,
    &P_Anon_IMPL_4,
    &P_GEND_TYPE_T2mi
};


PRT_VALUE* P_Anon_IMPL_5(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_5 = NULL;
    PRT_VALUE* PTMP_tmp1_5 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_58 = &(PTMP_tmp0_5);
    PrtFreeValue(*P_LVALUE_58);
    *P_LVALUE_58 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_59 = &(PTMP_tmp1_5);
    PrtFreeValue(*P_LVALUE_59);
    *P_LVALUE_59 = PrtCloneValue((&P_EVENT_TickEvent.value));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_5), PTMP_tmp1_5, 0);
    *(&(PTMP_tmp1_5)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_5;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_5;
    }
    
p_return_5: ;
    PrtFreeValue(PTMP_tmp0_5); PTMP_tmp0_5 = NULL;
    PrtFreeValue(PTMP_tmp1_5); PTMP_tmp1_5 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_5 =
{
    NULL,
    &P_Anon_IMPL_5,
    NULL
};


PRT_VALUE* P_UpdateLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request = argRefs[0];
    PRT_VALUE* PTMP_tmp0_6 = NULL;
    PRT_VALUE* PTMP_tmp1_6 = NULL;
    PRT_VALUE* PTMP_tmp2_3 = NULL;
    PRT_VALUE* PTMP_tmp3_2 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_60 = &(PTMP_tmp0_6);
    PrtFreeValue(*P_LVALUE_60);
    *P_LVALUE_60 = PrtTupleGet(*P_VAR_request, 1);
    
    PRT_VALUE** P_LVALUE_61 = &(PTMP_tmp1_6);
    PrtFreeValue(*P_LVALUE_61);
    *P_LVALUE_61 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[3]) < PrtPrimGetInt(PTMP_tmp0_6));
    
    if (PrtPrimGetBool(PTMP_tmp1_6))
    {
        PRT_VALUE** P_LVALUE_62 = &(PTMP_tmp2_3);
        PrtFreeValue(*P_LVALUE_62);
        *P_LVALUE_62 = PrtTupleGet(*P_VAR_request, 0);
        
        {
            PRT_VALUE** P_LVALUE_63 = &(p_this->varValues[2]);
            PrtFreeValue(*P_LVALUE_63);
            *P_LVALUE_63 = PTMP_tmp2_3;
            PTMP_tmp2_3 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_64 = &(PTMP_tmp3_2);
        PrtFreeValue(*P_LVALUE_64);
        *P_LVALUE_64 = PrtTupleGet(*P_VAR_request, 1);
        
        {
            PRT_VALUE** P_LVALUE_65 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_65);
            *P_LVALUE_65 = PTMP_tmp3_2;
            PTMP_tmp3_2 = NULL;
        }
        
    }
    
    else
    {
    }
    
    
p_return_6: ;
    PrtFreeValue(PTMP_tmp0_6); PTMP_tmp0_6 = NULL;
    PrtFreeValue(PTMP_tmp1_6); PTMP_tmp1_6 = NULL;
    PrtFreeValue(PTMP_tmp2_3); PTMP_tmp2_3 = NULL;
    PrtFreeValue(PTMP_tmp3_2); PTMP_tmp3_2 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_UpdateLeader =
{
    "UpdateLeader",
    &P_UpdateLeader_IMPL,
    NULL
};


PRT_VALUE* P_ShuttingDown_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_idx_2 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_7 = NULL;
    PRT_VALUE* PTMP_tmp1_7 = NULL;
    PRT_VALUE* PTMP_tmp2_4 = NULL;
    PRT_VALUE* PTMP_tmp3_3 = NULL;
    PRT_VALUE* PTMP_tmp4_2 = NULL;
    PRT_VALUE* PTMP_tmp5_2 = NULL;
    PRT_VALUE* PTMP_tmp6_2 = NULL;
    PRT_VALUE* PTMP_tmp7_2 = NULL;
    PRT_VALUE* PTMP_tmp8_2 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_8 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_9 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_3 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_66 = &(P_VAR_idx_2);
    PrtFreeValue(*P_LVALUE_66);
    *P_LVALUE_66 = PrtCloneValue((&P_LIT_INT32_8));
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_3)))
    {
        PRT_VALUE** P_LVALUE_67 = &(PTMP_tmp0_7);
        PrtFreeValue(*P_LVALUE_67);
        *P_LVALUE_67 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_2) < PrtPrimGetInt(p_this->varValues[1]));
        
        PRT_VALUE** P_LVALUE_68 = &(PTMP_tmp1_7);
        PrtFreeValue(*P_LVALUE_68);
        *P_LVALUE_68 = PrtCloneValue(PTMP_tmp0_7);
        
        if (PrtPrimGetBool(PTMP_tmp1_7))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_69 = &(PTMP_tmp2_4);
        PrtFreeValue(*P_LVALUE_69);
        *P_LVALUE_69 = PrtSeqGet(p_this->varValues[0], P_VAR_idx_2);
        
        PRT_VALUE** P_LVALUE_70 = &(PTMP_tmp3_3);
        PrtFreeValue(*P_LVALUE_70);
        *P_LVALUE_70 = PrtCloneValue(PTMP_tmp2_4);
        
        PRT_VALUE** P_LVALUE_71 = &(PTMP_tmp4_2);
        PrtFreeValue(*P_LVALUE_71);
        *P_LVALUE_71 = PrtCloneValue((&P_EVENT_ShutDown.value));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp3_3), PTMP_tmp4_2, 0);
        *(&(PTMP_tmp4_2)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_7;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_7;
        }
        
        PRT_VALUE** P_LVALUE_72 = &(PTMP_tmp5_2);
        PrtFreeValue(*P_LVALUE_72);
        *P_LVALUE_72 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_2) + PrtPrimGetInt((&P_LIT_INT32_9)));
        
        {
            PRT_VALUE** P_LVALUE_73 = &(P_VAR_idx_2);
            PrtFreeValue(*P_LVALUE_73);
            *P_LVALUE_73 = PTMP_tmp5_2;
            PTMP_tmp5_2 = NULL;
        }
        
    }
    
    
    PRT_VALUE** P_LVALUE_74 = &(PTMP_tmp6_2);
    PrtFreeValue(*P_LVALUE_74);
    *P_LVALUE_74 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_75 = &(PTMP_tmp7_2);
    PrtFreeValue(*P_LVALUE_75);
    *P_LVALUE_75 = PrtCloneValue((&_P_EVENT_HALT_STRUCT.value));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp6_2), PTMP_tmp7_2, 0);
    *(&(PTMP_tmp7_2)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_7;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_7;
    }
    
    PRT_VALUE** P_LVALUE_76 = &(PTMP_tmp8_2);
    PrtFreeValue(*P_LVALUE_76);
    *P_LVALUE_76 = PrtCloneValue((&_P_EVENT_HALT_STRUCT.value));
    
    PrtRaise(p_this, PTMP_tmp8_2, 0);
    *(&(PTMP_tmp8_2)) = NULL;
    goto p_return_7;
    
p_return_7: ;
    PrtFreeValue(P_VAR_idx_2); P_VAR_idx_2 = NULL;
    PrtFreeValue(PTMP_tmp0_7); PTMP_tmp0_7 = NULL;
    PrtFreeValue(PTMP_tmp1_7); PTMP_tmp1_7 = NULL;
    PrtFreeValue(PTMP_tmp2_4); PTMP_tmp2_4 = NULL;
    PrtFreeValue(PTMP_tmp3_3); PTMP_tmp3_3 = NULL;
    PrtFreeValue(PTMP_tmp4_2); PTMP_tmp4_2 = NULL;
    PrtFreeValue(PTMP_tmp5_2); PTMP_tmp5_2 = NULL;
    PrtFreeValue(PTMP_tmp6_2); PTMP_tmp6_2 = NULL;
    PrtFreeValue(PTMP_tmp7_2); PTMP_tmp7_2 = NULL;
    PrtFreeValue(PTMP_tmp8_2); PTMP_tmp8_2 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_ShuttingDown =
{
    "ShuttingDown",
    &P_ShuttingDown_IMPL,
    NULL
};


PRT_VALUE* P_Anon_IMPL_6(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_1 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_8 = NULL;
    PRT_VALUE* PTMP_tmp1_8 = NULL;
    PRT_VALUE* PTMP_tmp2_5 = NULL;
    PRT_VALUE* PTMP_tmp3_4 = NULL;
    PRT_VALUE* PTMP_tmp4_3 = NULL;
    PRT_VALUE* PTMP_tmp5_3 = NULL;
    PRT_VALUE* PTMP_tmp6_3 = NULL;
    PRT_VALUE* PTMP_tmp7_3 = NULL;
    PRT_VALUE* PTMP_tmp8_3 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_77 = &(PTMP_tmp0_8);
    PrtFreeValue(*P_LVALUE_77);
    *P_LVALUE_77 = PrtTupleGet(*P_VAR_payload_1, 1);
    
    PRT_VALUE** P_LVALUE_78 = &(PTMP_tmp1_8);
    PrtFreeValue(*P_LVALUE_78);
    *P_LVALUE_78 = PrtTupleGet(*P_VAR_payload_1, 2);
    
    PRT_VALUE** P_LVALUE_79 = &(PTMP_tmp2_5);
    PrtFreeValue(*P_LVALUE_79);
    *P_LVALUE_79 = PrtTupleGet(*P_VAR_payload_1, 0);
    
    PrtFormatPrintf("[ClusterManager] Request <", 3, PTMP_tmp0_8, PTMP_tmp1_8, PTMP_tmp2_5, 3, 0, ", ", 1, "> sent from client ", 2, "");
    
    PRT_VALUE** P_LVALUE_80 = &(PTMP_tmp3_4);
    PrtFreeValue(*P_LVALUE_80);
    *P_LVALUE_80 = PrtCloneValue(p_this->varValues[2]);
    
    PRT_VALUE** P_LVALUE_81 = &(PTMP_tmp4_3);
    PrtFreeValue(*P_LVALUE_81);
    *P_LVALUE_81 = PrtCloneValue((&P_EVENT_Request.value));
    
    PRT_VALUE** P_LVALUE_82 = &(PTMP_tmp5_3);
    PrtFreeValue(*P_LVALUE_82);
    *P_LVALUE_82 = PrtTupleGet(*P_VAR_payload_1, 0);
    
    PRT_VALUE** P_LVALUE_83 = &(PTMP_tmp6_3);
    PrtFreeValue(*P_LVALUE_83);
    *P_LVALUE_83 = PrtTupleGet(*P_VAR_payload_1, 1);
    
    PRT_VALUE** P_LVALUE_84 = &(PTMP_tmp7_3);
    PrtFreeValue(*P_LVALUE_84);
    *P_LVALUE_84 = PrtTupleGet(*P_VAR_payload_1, 2);
    
    PRT_VALUE** P_LVALUE_85 = &(PTMP_tmp8_3);
    PrtFreeValue(*P_LVALUE_85);
    *P_LVALUE_85 = (PrtMkTuple(&P_GEND_TYPE_T3mrr, &(PTMP_tmp5_3), &(PTMP_tmp6_3), &(PTMP_tmp7_3)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp3_4), PTMP_tmp4_3, 1, &(PTMP_tmp8_3));
    *(&(PTMP_tmp4_3)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_8;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_8;
    }
    
p_return_8: ;
    PrtFreeValue(PTMP_tmp0_8); PTMP_tmp0_8 = NULL;
    PrtFreeValue(PTMP_tmp1_8); PTMP_tmp1_8 = NULL;
    PrtFreeValue(PTMP_tmp2_5); PTMP_tmp2_5 = NULL;
    PrtFreeValue(PTMP_tmp3_4); PTMP_tmp3_4 = NULL;
    PrtFreeValue(PTMP_tmp4_3); PTMP_tmp4_3 = NULL;
    PrtFreeValue(PTMP_tmp5_3); PTMP_tmp5_3 = NULL;
    PrtFreeValue(PTMP_tmp6_3); PTMP_tmp6_3 = NULL;
    PrtFreeValue(PTMP_tmp7_3); PTMP_tmp7_3 = NULL;
    PrtFreeValue(PTMP_tmp8_3); PTMP_tmp8_3 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_6 =
{
    NULL,
    &P_Anon_IMPL_6,
    &P_GEND_TYPE_T3mrr
};


PRT_VALUE* P_Anon_IMPL_7(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_2 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_9 = NULL;
    PRT_VALUE* PTMP_tmp1_9 = NULL;
    PRT_VALUE* PTMP_tmp2_6 = NULL;
    PRT_VALUE* PTMP_tmp3_5 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_86 = &(PTMP_tmp0_9);
    PrtFreeValue(*P_LVALUE_86);
    *P_LVALUE_86 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_87 = &(PTMP_tmp1_9);
    PrtFreeValue(*P_LVALUE_87);
    *P_LVALUE_87 = PrtCloneValue((&P_EVENT_Request.value));
    
    PRT_VALUE** P_LVALUE_88 = &(PTMP_tmp2_6);
    PrtFreeValue(*P_LVALUE_88);
    *P_LVALUE_88 = PrtCloneValue(*P_VAR_payload_2);
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_9), PTMP_tmp1_9, 1, &(PTMP_tmp2_6));
    *(&(PTMP_tmp1_9)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_9;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_9;
    }
    
    PRT_VALUE** P_LVALUE_89 = &(PTMP_tmp3_5);
    PrtFreeValue(*P_LVALUE_89);
    *P_LVALUE_89 = PrtCloneValue((&P_EVENT_LocalEvent.value));
    
    PrtRaise(p_this, PTMP_tmp3_5, 0);
    *(&(PTMP_tmp3_5)) = NULL;
    goto p_return_9;
    
p_return_9: ;
    PrtFreeValue(PTMP_tmp0_9); PTMP_tmp0_9 = NULL;
    PrtFreeValue(PTMP_tmp1_9); PTMP_tmp1_9 = NULL;
    PrtFreeValue(PTMP_tmp2_6); PTMP_tmp2_6 = NULL;
    PrtFreeValue(PTMP_tmp3_5); PTMP_tmp3_5 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_7 =
{
    NULL,
    &P_Anon_IMPL_7,
    &P_GEND_TYPE_T3mrr
};


PRT_VALUE* P_Anon_IMPL_8(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_3 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_10 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_90 = &(PTMP_tmp0_10);
    PrtFreeValue(*P_LVALUE_90);
    *P_LVALUE_90 = PrtCloneValue(*P_VAR_payload_3);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_10);
    PrtFreeValue(P_UpdateLeader_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_10);
    PTMP_tmp0_10 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_10;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_10;
    }
    
p_return_10: ;
    PrtFreeValue(PTMP_tmp0_10); PTMP_tmp0_10 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_8 =
{
    NULL,
    &P_Anon_IMPL_8,
    &P_GEND_TYPE_T2mi
};


PRT_VALUE* P_Anon_IMPL_9(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_1 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_11 = NULL;
    PRT_VALUE* PTMP_tmp1_10 = NULL;
    PRT_VALUE* PTMP_tmp2_7 = NULL;
    PRT_VALUE* PTMP_tmp3_6 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    if (PrtPrimGetBool(p_this->varValues[6]))
    {
        PRT_VALUE** P_LVALUE_91 = &(PTMP_tmp0_11);
        PrtFreeValue(*P_LVALUE_91);
        *P_LVALUE_91 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_92 = &(PTMP_tmp1_10);
        PrtFreeValue(*P_LVALUE_92);
        *P_LVALUE_92 = PrtCloneValue((&P_EVENT_AddServer.value));
        
        PRT_VALUE** P_LVALUE_93 = &(PTMP_tmp2_7);
        PrtFreeValue(*P_LVALUE_93);
        *P_LVALUE_93 = PrtCloneValue(*P_VAR_server_1);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_11), PTMP_tmp1_10, 1, &(PTMP_tmp2_7));
        *(&(PTMP_tmp1_10)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_11;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_11;
        }
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_94 = &(PTMP_tmp3_6);
        PrtFreeValue(*P_LVALUE_94);
        *P_LVALUE_94 = PrtCloneValue(*P_VAR_server_1);
        
        _P_GEN_funargs[0] = &(PTMP_tmp3_6);
        PrtFreeValue(P_AddServerToCluster_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp3_6);
        PTMP_tmp3_6 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_11;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_11;
        }
        
    }
    
    
p_return_11: ;
    PrtFreeValue(PTMP_tmp0_11); PTMP_tmp0_11 = NULL;
    PrtFreeValue(PTMP_tmp1_10); PTMP_tmp1_10 = NULL;
    PrtFreeValue(PTMP_tmp2_7); PTMP_tmp2_7 = NULL;
    PrtFreeValue(PTMP_tmp3_6); PTMP_tmp3_6 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_9 =
{
    NULL,
    &P_Anon_IMPL_9,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_Anon_IMPL_10(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_2 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_12 = NULL;
    PRT_VALUE* PTMP_tmp1_11 = NULL;
    PRT_VALUE* PTMP_tmp2_8 = NULL;
    PRT_VALUE* PTMP_tmp3_7 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    if (PrtPrimGetBool(p_this->varValues[6]))
    {
        PRT_VALUE** P_LVALUE_95 = &(PTMP_tmp0_12);
        PrtFreeValue(*P_LVALUE_95);
        *P_LVALUE_95 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_96 = &(PTMP_tmp1_11);
        PrtFreeValue(*P_LVALUE_96);
        *P_LVALUE_96 = PrtCloneValue((&P_EVENT_RemoveServer.value));
        
        PRT_VALUE** P_LVALUE_97 = &(PTMP_tmp2_8);
        PrtFreeValue(*P_LVALUE_97);
        *P_LVALUE_97 = PrtCloneValue(*P_VAR_server_2);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_12), PTMP_tmp1_11, 1, &(PTMP_tmp2_8));
        *(&(PTMP_tmp1_11)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_12;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_12;
        }
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_98 = &(PTMP_tmp3_7);
        PrtFreeValue(*P_LVALUE_98);
        *P_LVALUE_98 = PrtCloneValue(*P_VAR_server_2);
        
        _P_GEN_funargs[0] = &(PTMP_tmp3_7);
        PrtFreeValue(P_RemoveServerFromCluster_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp3_7);
        PTMP_tmp3_7 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_12;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_12;
        }
        
    }
    
    
p_return_12: ;
    PrtFreeValue(PTMP_tmp0_12); PTMP_tmp0_12 = NULL;
    PrtFreeValue(PTMP_tmp1_11); PTMP_tmp1_11 = NULL;
    PrtFreeValue(PTMP_tmp2_8); PTMP_tmp2_8 = NULL;
    PrtFreeValue(PTMP_tmp3_7); PTMP_tmp3_7 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_10 =
{
    NULL,
    &P_Anon_IMPL_10,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_Anon_IMPL_11(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_4 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_13 = NULL;
    PRT_VALUE* PTMP_tmp1_12 = NULL;
    PRT_VALUE* PTMP_tmp2_9 = NULL;
    PRT_VALUE* PTMP_tmp3_8 = NULL;
    PRT_VALUE* PTMP_tmp4_4 = NULL;
    PRT_VALUE* PTMP_tmp5_4 = NULL;
    PRT_VALUE* PTMP_tmp6_4 = NULL;
    PRT_VALUE* PTMP_tmp7_4 = NULL;
    PRT_VALUE* PTMP_tmp8_4 = NULL;
    PRT_VALUE* PTMP_tmp9_2 = NULL;
    PRT_VALUE* PTMP_tmp10_2 = NULL;
    PRT_VALUE* PTMP_tmp11_2 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_10 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_4 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_99 = &(p_this->varValues[6]);
    PrtFreeValue(*P_LVALUE_99);
    *P_LVALUE_99 = PrtCloneValue((&P_LIT_BOOLEAN_4));
    
    PRT_VALUE** P_LVALUE_100 = &(PTMP_tmp0_13);
    PrtFreeValue(*P_LVALUE_100);
    *P_LVALUE_100 = PrtTupleGet(*P_VAR_payload_4, 1);
    
    PRT_VALUE** P_LVALUE_101 = &(PTMP_tmp1_12);
    PrtFreeValue(*P_LVALUE_101);
    *P_LVALUE_101 = PrtMkBoolValue(!PrtPrimGetBool(PTMP_tmp0_13));
    
    if (PrtPrimGetBool(PTMP_tmp1_12))
    {
        PRT_VALUE** P_LVALUE_102 = &(PTMP_tmp2_9);
        PrtFreeValue(*P_LVALUE_102);
        *P_LVALUE_102 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_103 = &(PTMP_tmp3_8);
        PrtFreeValue(*P_LVALUE_103);
        *P_LVALUE_103 = PrtCloneValue((&P_EVENT_AddServer.value));
        
        PRT_VALUE** P_LVALUE_104 = &(PTMP_tmp4_4);
        PrtFreeValue(*P_LVALUE_104);
        *P_LVALUE_104 = PrtTupleGet(*P_VAR_payload_4, 0);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp2_9), PTMP_tmp3_8, 1, &(PTMP_tmp4_4));
        *(&(PTMP_tmp3_8)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_13;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_13;
        }
        
        PRT_VALUE** P_LVALUE_105 = &(PTMP_tmp5_4);
        PrtFreeValue(*P_LVALUE_105);
        *P_LVALUE_105 = PrtCloneValue((&P_EVENT_LocalEvent.value));
        
        PrtRaise(p_this, PTMP_tmp5_4, 0);
        *(&(PTMP_tmp5_4)) = NULL;
        goto p_return_13;
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_106 = &(PTMP_tmp6_4);
        PrtFreeValue(*P_LVALUE_106);
        *P_LVALUE_106 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[0]));
        
        PRT_VALUE** P_LVALUE_107 = &(PTMP_tmp7_4);
        PrtFreeValue(*P_LVALUE_107);
        *P_LVALUE_107 = PrtTupleGet(*P_VAR_payload_4, 0);
        
        PrtSeqInsertEx(p_this->varValues[0], PTMP_tmp6_4, PTMP_tmp7_4, PRT_FALSE);
        *(&(PTMP_tmp7_4)) = NULL;
        
        PRT_VALUE** P_LVALUE_108 = &(PTMP_tmp8_4);
        PrtFreeValue(*P_LVALUE_108);
        *P_LVALUE_108 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[1]) + PrtPrimGetInt((&P_LIT_INT32_10)));
        
        {
            PRT_VALUE** P_LVALUE_109 = &(p_this->varValues[1]);
            PrtFreeValue(*P_LVALUE_109);
            *P_LVALUE_109 = PTMP_tmp8_4;
            PTMP_tmp8_4 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_110 = &(PTMP_tmp9_2);
        PrtFreeValue(*P_LVALUE_110);
        *P_LVALUE_110 = PrtCloneValue(p_this->varValues[5]);
        
        PRT_VALUE** P_LVALUE_111 = &(PTMP_tmp10_2);
        PrtFreeValue(*P_LVALUE_111);
        *P_LVALUE_111 = PrtCloneValue((&P_EVENT_UpdateServers.value));
        
        PRT_VALUE** P_LVALUE_112 = &(PTMP_tmp11_2);
        PrtFreeValue(*P_LVALUE_112);
        *P_LVALUE_112 = PrtCloneValue(p_this->varValues[0]);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp9_2), PTMP_tmp10_2, 1, &(PTMP_tmp11_2));
        *(&(PTMP_tmp10_2)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_13;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_13;
        }
        
    }
    
    
p_return_13: ;
    PrtFreeValue(PTMP_tmp0_13); PTMP_tmp0_13 = NULL;
    PrtFreeValue(PTMP_tmp1_12); PTMP_tmp1_12 = NULL;
    PrtFreeValue(PTMP_tmp2_9); PTMP_tmp2_9 = NULL;
    PrtFreeValue(PTMP_tmp3_8); PTMP_tmp3_8 = NULL;
    PrtFreeValue(PTMP_tmp4_4); PTMP_tmp4_4 = NULL;
    PrtFreeValue(PTMP_tmp5_4); PTMP_tmp5_4 = NULL;
    PrtFreeValue(PTMP_tmp6_4); PTMP_tmp6_4 = NULL;
    PrtFreeValue(PTMP_tmp7_4); PTMP_tmp7_4 = NULL;
    PrtFreeValue(PTMP_tmp8_4); PTMP_tmp8_4 = NULL;
    PrtFreeValue(PTMP_tmp9_2); PTMP_tmp9_2 = NULL;
    PrtFreeValue(PTMP_tmp10_2); PTMP_tmp10_2 = NULL;
    PrtFreeValue(PTMP_tmp11_2); PTMP_tmp11_2 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_11 =
{
    NULL,
    &P_Anon_IMPL_11,
    &P_GEND_TYPE_T2mb
};


PRT_VALUE* P_Anon_IMPL_12(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_5 = argRefs[0];
    PRT_VALUE* P_VAR_idx_3 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_14 = NULL;
    PRT_VALUE* PTMP_tmp1_13 = NULL;
    PRT_VALUE* PTMP_tmp2_10 = NULL;
    PRT_VALUE* PTMP_tmp3_9 = NULL;
    PRT_VALUE* PTMP_tmp4_5 = NULL;
    PRT_VALUE* PTMP_tmp5_5 = NULL;
    PRT_VALUE* PTMP_tmp6_5 = NULL;
    PRT_VALUE* PTMP_tmp7_5 = NULL;
    PRT_VALUE* PTMP_tmp8_5 = NULL;
    PRT_VALUE* PTMP_tmp9_3 = NULL;
    PRT_VALUE* PTMP_tmp10_3 = NULL;
    PRT_VALUE* PTMP_tmp11_3 = NULL;
    PRT_VALUE* PTMP_tmp12_2 = NULL;
    PRT_VALUE* PTMP_tmp13_2 = NULL;
    PRT_VALUE* PTMP_tmp14_2 = NULL;
    PRT_VALUE* PTMP_tmp15_2 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_11 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_12 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_5 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE P_LIT_BOOLEAN_6 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_113 = &(P_VAR_idx_3);
    PrtFreeValue(*P_LVALUE_113);
    *P_LVALUE_113 = PrtCloneValue((&P_LIT_INT32_11));
    
    PRT_VALUE** P_LVALUE_114 = &(p_this->varValues[6]);
    PrtFreeValue(*P_LVALUE_114);
    *P_LVALUE_114 = PrtCloneValue((&P_LIT_BOOLEAN_5));
    
    PRT_VALUE** P_LVALUE_115 = &(PTMP_tmp0_14);
    PrtFreeValue(*P_LVALUE_115);
    *P_LVALUE_115 = PrtTupleGet(*P_VAR_payload_5, 1);
    
    PRT_VALUE** P_LVALUE_116 = &(PTMP_tmp1_13);
    PrtFreeValue(*P_LVALUE_116);
    *P_LVALUE_116 = PrtMkBoolValue(!PrtPrimGetBool(PTMP_tmp0_14));
    
    if (PrtPrimGetBool(PTMP_tmp1_13))
    {
        PRT_VALUE** P_LVALUE_117 = &(PTMP_tmp2_10);
        PrtFreeValue(*P_LVALUE_117);
        *P_LVALUE_117 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_118 = &(PTMP_tmp3_9);
        PrtFreeValue(*P_LVALUE_118);
        *P_LVALUE_118 = PrtCloneValue((&P_EVENT_RemoveServer.value));
        
        PRT_VALUE** P_LVALUE_119 = &(PTMP_tmp4_5);
        PrtFreeValue(*P_LVALUE_119);
        *P_LVALUE_119 = PrtTupleGet(*P_VAR_payload_5, 0);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp2_10), PTMP_tmp3_9, 1, &(PTMP_tmp4_5));
        *(&(PTMP_tmp3_9)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_14;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_14;
        }
        
        PRT_VALUE** P_LVALUE_120 = &(PTMP_tmp5_5);
        PrtFreeValue(*P_LVALUE_120);
        *P_LVALUE_120 = PrtCloneValue((&P_EVENT_LocalEvent.value));
        
        PrtRaise(p_this, PTMP_tmp5_5, 0);
        *(&(PTMP_tmp5_5)) = NULL;
        goto p_return_14;
        
    }
    
    else
    {
        while (PrtPrimGetBool((&P_LIT_BOOLEAN_6)))
        {
            PRT_VALUE** P_LVALUE_121 = &(PTMP_tmp6_5);
            PrtFreeValue(*P_LVALUE_121);
            *P_LVALUE_121 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_3) < PrtPrimGetInt(p_this->varValues[1]));
            
            PRT_VALUE** P_LVALUE_122 = &(PTMP_tmp7_5);
            PrtFreeValue(*P_LVALUE_122);
            *P_LVALUE_122 = PrtCloneValue(PTMP_tmp6_5);
            
            if (PrtPrimGetBool(PTMP_tmp7_5))
            {
            }
            
            else
            {
                break;
                
            }
            
            
            PRT_VALUE** P_LVALUE_123 = &(PTMP_tmp8_5);
            PrtFreeValue(*P_LVALUE_123);
            *P_LVALUE_123 = PrtSeqGet(p_this->varValues[0], P_VAR_idx_3);
            
            PRT_VALUE** P_LVALUE_124 = &(PTMP_tmp9_3);
            PrtFreeValue(*P_LVALUE_124);
            *P_LVALUE_124 = PrtTupleGet(*P_VAR_payload_5, 0);
            
            PRT_VALUE** P_LVALUE_125 = &(PTMP_tmp10_3);
            PrtFreeValue(*P_LVALUE_125);
            *P_LVALUE_125 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp8_5, PTMP_tmp9_3));
            
            if (PrtPrimGetBool(PTMP_tmp10_3))
            {
                PrtRemoveByKey(p_this->varValues[0], P_VAR_idx_3);
                
                break;
                
            }
            
            else
            {
            }
            
            
            PRT_VALUE** P_LVALUE_126 = &(PTMP_tmp11_3);
            PrtFreeValue(*P_LVALUE_126);
            *P_LVALUE_126 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_3) + PrtPrimGetInt((&P_LIT_INT32_12)));
            
            {
                PRT_VALUE** P_LVALUE_127 = &(P_VAR_idx_3);
                PrtFreeValue(*P_LVALUE_127);
                *P_LVALUE_127 = PTMP_tmp11_3;
                PTMP_tmp11_3 = NULL;
            }
            
        }
        
        
        PRT_VALUE** P_LVALUE_128 = &(PTMP_tmp12_2);
        PrtFreeValue(*P_LVALUE_128);
        *P_LVALUE_128 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[1]) - PrtPrimGetInt((&P_LIT_INT32_12)));
        
        {
            PRT_VALUE** P_LVALUE_129 = &(p_this->varValues[1]);
            PrtFreeValue(*P_LVALUE_129);
            *P_LVALUE_129 = PTMP_tmp12_2;
            PTMP_tmp12_2 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_130 = &(PTMP_tmp13_2);
        PrtFreeValue(*P_LVALUE_130);
        *P_LVALUE_130 = PrtCloneValue(p_this->varValues[5]);
        
        PRT_VALUE** P_LVALUE_131 = &(PTMP_tmp14_2);
        PrtFreeValue(*P_LVALUE_131);
        *P_LVALUE_131 = PrtCloneValue((&P_EVENT_UpdateServers.value));
        
        PRT_VALUE** P_LVALUE_132 = &(PTMP_tmp15_2);
        PrtFreeValue(*P_LVALUE_132);
        *P_LVALUE_132 = PrtCloneValue(p_this->varValues[0]);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp13_2), PTMP_tmp14_2, 1, &(PTMP_tmp15_2));
        *(&(PTMP_tmp14_2)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_14;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_14;
        }
        
    }
    
    
p_return_14: ;
    PrtFreeValue(P_VAR_idx_3); P_VAR_idx_3 = NULL;
    PrtFreeValue(PTMP_tmp0_14); PTMP_tmp0_14 = NULL;
    PrtFreeValue(PTMP_tmp1_13); PTMP_tmp1_13 = NULL;
    PrtFreeValue(PTMP_tmp2_10); PTMP_tmp2_10 = NULL;
    PrtFreeValue(PTMP_tmp3_9); PTMP_tmp3_9 = NULL;
    PrtFreeValue(PTMP_tmp4_5); PTMP_tmp4_5 = NULL;
    PrtFreeValue(PTMP_tmp5_5); PTMP_tmp5_5 = NULL;
    PrtFreeValue(PTMP_tmp6_5); PTMP_tmp6_5 = NULL;
    PrtFreeValue(PTMP_tmp7_5); PTMP_tmp7_5 = NULL;
    PrtFreeValue(PTMP_tmp8_5); PTMP_tmp8_5 = NULL;
    PrtFreeValue(PTMP_tmp9_3); PTMP_tmp9_3 = NULL;
    PrtFreeValue(PTMP_tmp10_3); PTMP_tmp10_3 = NULL;
    PrtFreeValue(PTMP_tmp11_3); PTMP_tmp11_3 = NULL;
    PrtFreeValue(PTMP_tmp12_2); PTMP_tmp12_2 = NULL;
    PrtFreeValue(PTMP_tmp13_2); PTMP_tmp13_2 = NULL;
    PrtFreeValue(PTMP_tmp14_2); PTMP_tmp14_2 = NULL;
    PrtFreeValue(PTMP_tmp15_2); PTMP_tmp15_2 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_12 =
{
    NULL,
    &P_Anon_IMPL_12,
    &P_GEND_TYPE_T2mb_1
};


PRT_VALUE* P_Anon_IMPL_13(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_15 = NULL;
    PRT_VALUE* PTMP_tmp1_14 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_133 = &(PTMP_tmp0_15);
    PrtFreeValue(*P_LVALUE_133);
    *P_LVALUE_133 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_134 = &(PTMP_tmp1_14);
    PrtFreeValue(*P_LVALUE_134);
    *P_LVALUE_134 = PrtCloneValue((&P_EVENT_TickEvent.value));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_15), PTMP_tmp1_14, 0);
    *(&(PTMP_tmp1_14)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_15;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_15;
    }
    
p_return_15: ;
    PrtFreeValue(PTMP_tmp0_15); PTMP_tmp0_15 = NULL;
    PrtFreeValue(PTMP_tmp1_14); PTMP_tmp1_14 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_13 =
{
    NULL,
    &P_Anon_IMPL_13,
    NULL
};


PRT_VALUE* P_AddServerToCluster_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_3 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_16 = NULL;
    PRT_VALUE* PTMP_tmp1_15 = NULL;
    PRT_VALUE* PTMP_tmp2_11 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_BOOLEAN_7 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_135 = &(p_this->varValues[6]);
    PrtFreeValue(*P_LVALUE_135);
    *P_LVALUE_135 = PrtCloneValue((&P_LIT_BOOLEAN_7));
    
    PRT_VALUE** P_LVALUE_136 = &(PTMP_tmp0_16);
    PrtFreeValue(*P_LVALUE_136);
    *P_LVALUE_136 = PrtCloneValue(p_this->varValues[2]);
    
    PRT_VALUE** P_LVALUE_137 = &(PTMP_tmp1_15);
    PrtFreeValue(*P_LVALUE_137);
    *P_LVALUE_137 = PrtCloneValue((&P_EVENT_AddServer.value));
    
    PRT_VALUE** P_LVALUE_138 = &(PTMP_tmp2_11);
    PrtFreeValue(*P_LVALUE_138);
    *P_LVALUE_138 = PrtCloneValue(*P_VAR_server_3);
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_16), PTMP_tmp1_15, 1, &(PTMP_tmp2_11));
    *(&(PTMP_tmp1_15)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_16;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_16;
    }
    
p_return_16: ;
    PrtFreeValue(PTMP_tmp0_16); PTMP_tmp0_16 = NULL;
    PrtFreeValue(PTMP_tmp1_15); PTMP_tmp1_15 = NULL;
    PrtFreeValue(PTMP_tmp2_11); PTMP_tmp2_11 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_AddServerToCluster =
{
    "AddServerToCluster",
    &P_AddServerToCluster_IMPL,
    NULL
};


PRT_VALUE* P_RemoveServerFromCluster_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_4 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_17 = NULL;
    PRT_VALUE* PTMP_tmp1_16 = NULL;
    PRT_VALUE* PTMP_tmp2_12 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_BOOLEAN_8 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_139 = &(p_this->varValues[6]);
    PrtFreeValue(*P_LVALUE_139);
    *P_LVALUE_139 = PrtCloneValue((&P_LIT_BOOLEAN_8));
    
    PRT_VALUE** P_LVALUE_140 = &(PTMP_tmp0_17);
    PrtFreeValue(*P_LVALUE_140);
    *P_LVALUE_140 = PrtCloneValue(p_this->varValues[2]);
    
    PRT_VALUE** P_LVALUE_141 = &(PTMP_tmp1_16);
    PrtFreeValue(*P_LVALUE_141);
    *P_LVALUE_141 = PrtCloneValue((&P_EVENT_RemoveServer.value));
    
    PRT_VALUE** P_LVALUE_142 = &(PTMP_tmp2_12);
    PrtFreeValue(*P_LVALUE_142);
    *P_LVALUE_142 = PrtCloneValue(*P_VAR_server_4);
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_17), PTMP_tmp1_16, 1, &(PTMP_tmp2_12));
    *(&(PTMP_tmp1_16)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_17;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_17;
    }
    
p_return_17: ;
    PrtFreeValue(PTMP_tmp0_17); PTMP_tmp0_17 = NULL;
    PrtFreeValue(PTMP_tmp1_16); PTMP_tmp1_16 = NULL;
    PrtFreeValue(PTMP_tmp2_12); PTMP_tmp2_12 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_RemoveServerFromCluster =
{
    "RemoveServerFromCluster",
    &P_RemoveServerFromCluster_IMPL,
    NULL
};


PRT_FUNDECL* P_ClusterManager_METHODS[] = { &P_FUNCTION_Anon, &P_FUNCTION_Anon_1, &P_FUNCTION_Anon_2, &P_FUNCTION_Anon_3, &P_FUNCTION_Anon_4, &P_FUNCTION_Anon_5, &P_FUNCTION_UpdateLeader, &P_FUNCTION_ShuttingDown, &P_FUNCTION_Anon_6, &P_FUNCTION_Anon_7, &P_FUNCTION_Anon_8, &P_FUNCTION_Anon_9, &P_FUNCTION_Anon_10, &P_FUNCTION_Anon_11, &P_FUNCTION_Anon_12, &P_FUNCTION_Anon_13, &P_FUNCTION_AddServerToCluster, &P_FUNCTION_RemoveServerFromCluster };

PRT_EVENTDECL* P_ClusterManager_RECV_INNER_1[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_ClusterManager_RECV_1 =
{
    34U,
    P_ClusterManager_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_ClusterManager_SEND_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_ClusterManager_SEND =
{
    34U,
    P_ClusterManager_SEND_INNER,
    NULL
};

PRT_UINT32 P_ClusterManager_CREATES_ARR[] = { 6 };
PRT_INTERFACESETDECL P_ClusterManager_CREATES = { 1, P_ClusterManager_CREATES_ARR };
PRT_MACHINEDECL P_MACHINE_ClusterManager = 
{
    0U,
    "ClusterManager",
    &P_EVENTSET_ClusterManager_RECV_1,
    &P_EVENTSET_ClusterManager_SEND,
    &P_ClusterManager_CREATES,
    7U,
    4U,
    18U,
    4294967295U,
    0U,
    P_ClusterManager_VARS,
    P_ClusterManager_STATES,
    P_ClusterManager_METHODS
};

PRT_VARDECL P_SafetyMonitor_VARS[] = {
    { "CurrentTerm", &P_GEND_TYPE_i },
    { "TermsWithLeader", &P_GEND_TYPE_MKiVb },
    { "ServerLogs", &P_GEND_TYPE_MKmVST3irr },
    { "CommittedLogs", &P_GEND_TYPE_MKiVST3irr }
};

PRT_EVENTDECL* P_Init_DEFERS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DEFERS_1 =
{
    0U,
    P_Init_DEFERS_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Init_TRANS_INNER_1[] = { &P_EVENT_LocalEvent };
PRT_EVENTSETDECL P_EVENTSET_Init_TRANS_1 =
{
    1U,
    P_Init_TRANS_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Init_DOS_INNER_1[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DOS_1 =
{
    0U,
    P_Init_DOS_INNER_1,
    NULL
};

PRT_TRANSDECL P_TRANS_4[] =
{
    { 0, &P_EVENT_LocalEvent, 1, &_P_NO_OP }
};

#define P_STATE_SafetyMonitor_Init \
{ \
    "SafetyMonitor.Init", \
    1U, \
    0U, \
    &P_EVENTSET_Init_DEFERS_1, \
    &P_EVENTSET_Init_TRANS_1, \
    &P_EVENTSET_Init_DOS_1, \
    P_TRANS_4, \
    NULL, \
    &P_FUNCTION_Anon_14, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Monitoring_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Monitoring_DEFERS =
{
    0U,
    P_Monitoring_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Monitoring_TRANS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Monitoring_TRANS =
{
    0U,
    P_Monitoring_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Monitoring_DOS_INNER[] = { &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected };
PRT_EVENTSETDECL P_EVENTSET_Monitoring_DOS =
{
    3U,
    P_Monitoring_DOS_INNER,
    NULL
};

PRT_DODECL P_DOS_4[] =
{
    { 1, &P_EVENT_M_NotifyLeaderElected, &P_FUNCTION_Anon_15 },
    { 1, &P_EVENT_M_LogAppend, &P_FUNCTION_Anon_16 },
    { 1, &P_EVENT_M_LeaderCommitted, &P_FUNCTION_Anon_17 }
};

#define P_STATE_SafetyMonitor_Monitoring \
{ \
    "SafetyMonitor.Monitoring", \
    0U, \
    3U, \
    &P_EVENTSET_Monitoring_DEFERS, \
    &P_EVENTSET_Monitoring_TRANS, \
    &P_EVENTSET_Monitoring_DOS, \
    NULL, \
    P_DOS_4, \
    &_P_NO_OP, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_SafetyMonitor_STATES[] = { P_STATE_SafetyMonitor_Init, P_STATE_SafetyMonitor_Monitoring };

PRT_VALUE* P_Anon_IMPL_14(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_18 = NULL;
    PRT_VALUE* PTMP_tmp1_17 = NULL;
    PRT_VALUE* PTMP_tmp2_13 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_13 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE** P_LVALUE_143 = &(PTMP_tmp0_18);
    PrtFreeValue(*P_LVALUE_143);
    *P_LVALUE_143 = PrtMkIntValue(-PrtPrimGetInt((&P_LIT_INT32_13)));
    
    {
        PRT_VALUE** P_LVALUE_144 = &(p_this->varValues[0]);
        PrtFreeValue(*P_LVALUE_144);
        *P_LVALUE_144 = PTMP_tmp0_18;
        PTMP_tmp0_18 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_145 = &(PTMP_tmp1_17);
    PrtFreeValue(*P_LVALUE_145);
    *P_LVALUE_145 = PrtMkDefaultValue(&P_GEND_TYPE_MKiVb);
    
    {
        PRT_VALUE** P_LVALUE_146 = &(p_this->varValues[1]);
        PrtFreeValue(*P_LVALUE_146);
        *P_LVALUE_146 = PTMP_tmp1_17;
        PTMP_tmp1_17 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_147 = &(PTMP_tmp2_13);
    PrtFreeValue(*P_LVALUE_147);
    *P_LVALUE_147 = PrtCloneValue((&P_EVENT_LocalEvent.value));
    
    PrtRaise(p_this, PTMP_tmp2_13, 0);
    *(&(PTMP_tmp2_13)) = NULL;
    goto p_return_18;
    
p_return_18: ;
    PrtFreeValue(PTMP_tmp0_18); PTMP_tmp0_18 = NULL;
    PrtFreeValue(PTMP_tmp1_17); PTMP_tmp1_17 = NULL;
    PrtFreeValue(PTMP_tmp2_13); PTMP_tmp2_13 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_14 =
{
    NULL,
    &P_Anon_IMPL_14,
    NULL
};


PRT_VALUE* P_Anon_IMPL_15(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_6 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_19 = NULL;
    PRT_VALUE* PTMP_tmp1_18 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_148 = &(PTMP_tmp0_19);
    PrtFreeValue(*P_LVALUE_148);
    *P_LVALUE_148 = PrtTupleGet(*P_VAR_payload_6, 0);
    
    PRT_VALUE** P_LVALUE_149 = &(PTMP_tmp1_18);
    PrtFreeValue(*P_LVALUE_149);
    *P_LVALUE_149 = PrtTupleGet(*P_VAR_payload_6, 1);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_19);
    _P_GEN_funargs[1] = &(PTMP_tmp1_18);
    PrtFreeValue(P_ProcessLeaderElected_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_19);
    PTMP_tmp0_19 = NULL;
    PrtFreeValue(PTMP_tmp1_18);
    PTMP_tmp1_18 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_19;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_19;
    }
    
p_return_19: ;
    PrtFreeValue(PTMP_tmp0_19); PTMP_tmp0_19 = NULL;
    PrtFreeValue(PTMP_tmp1_18); PTMP_tmp1_18 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_15 =
{
    NULL,
    &P_Anon_IMPL_15,
    &P_GEND_TYPE_T2iST3irr
};


PRT_VALUE* P_Anon_IMPL_16(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_7 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_20 = NULL;
    PRT_VALUE* PTMP_tmp1_19 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_150 = &(PTMP_tmp0_20);
    PrtFreeValue(*P_LVALUE_150);
    *P_LVALUE_150 = PrtTupleGet(*P_VAR_payload_7, 0);
    
    PRT_VALUE** P_LVALUE_151 = &(PTMP_tmp1_19);
    PrtFreeValue(*P_LVALUE_151);
    *P_LVALUE_151 = PrtTupleGet(*P_VAR_payload_7, 1);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_20);
    _P_GEN_funargs[1] = &(PTMP_tmp1_19);
    PrtFreeValue(P_ProcessLogAppend_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_20);
    PTMP_tmp0_20 = NULL;
    PrtFreeValue(PTMP_tmp1_19);
    PTMP_tmp1_19 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_20;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_20;
    }
    
p_return_20: ;
    PrtFreeValue(PTMP_tmp0_20); PTMP_tmp0_20 = NULL;
    PrtFreeValue(PTMP_tmp1_19); PTMP_tmp1_19 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_16 =
{
    NULL,
    &P_Anon_IMPL_16,
    &P_GEND_TYPE_T2mST3irr
};


PRT_VALUE* P_Anon_IMPL_17(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_8 = argRefs[0];
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_152 = &(*(PrtMapGetLValue(p_this->varValues[3], p_this->varValues[0], PRT_TRUE, &P_GEND_TYPE_MKiVST3irr)));
    PrtFreeValue(*P_LVALUE_152);
    *P_LVALUE_152 = PrtCloneValue(*P_VAR_payload_8);
    
p_return_21: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_17 =
{
    NULL,
    &P_Anon_IMPL_17,
    &P_GEND_TYPE_ST3irr
};


PRT_VALUE* P_ProcessLeaderElected_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_Term = argRefs[0];
    PRT_VALUE** P_VAR_Logs = argRefs[1];
    PRT_VALUE* P_VAR_i = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_j = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_PrevCommitted = PrtMkDefaultValue(&P_GEND_TYPE_ST3irr);
    PRT_VALUE* P_VAR_terms = PrtMkDefaultValue(&P_GEND_TYPE_Si);
    PRT_VALUE* PTMP_tmp0_21 = NULL;
    PRT_VALUE* PTMP_tmp1_20 = NULL;
    PRT_VALUE* PTMP_tmp2_14 = NULL;
    PRT_VALUE* PTMP_tmp3_10 = NULL;
    PRT_VALUE* PTMP_tmp4_6 = NULL;
    PRT_VALUE* PTMP_tmp5_6 = NULL;
    PRT_VALUE* PTMP_tmp6_6 = NULL;
    PRT_VALUE* PTMP_tmp7_6 = NULL;
    PRT_VALUE* PTMP_tmp8_6 = NULL;
    PRT_VALUE* PTMP_tmp9_4 = NULL;
    PRT_VALUE* PTMP_tmp10_4 = NULL;
    PRT_VALUE* PTMP_tmp11_4 = NULL;
    PRT_VALUE* PTMP_tmp12_3 = NULL;
    PRT_VALUE* PTMP_tmp13_3 = NULL;
    PRT_VALUE* PTMP_tmp14_3 = NULL;
    PRT_VALUE* PTMP_tmp15_3 = NULL;
    PRT_VALUE* PTMP_tmp16_2 = NULL;
    PRT_VALUE* PTMP_tmp17_1 = NULL;
    PRT_VALUE* PTMP_tmp18_1 = NULL;
    PRT_VALUE* PTMP_tmp19_1 = NULL;
    PRT_VALUE* PTMP_tmp20_1 = NULL;
    PRT_VALUE* PTMP_tmp21_1 = NULL;
    PRT_VALUE* PTMP_tmp22_1 = NULL;
    PRT_VALUE* PTMP_tmp23_1 = NULL;
    PRT_VALUE* PTMP_tmp24 = NULL;
    PRT_VALUE* PTMP_tmp25 = NULL;
    PRT_VALUE* PTMP_tmp26 = NULL;
    PRT_VALUE* PTMP_tmp27 = NULL;
    PRT_VALUE* PTMP_tmp28 = NULL;
    PRT_VALUE* PTMP_tmp29 = NULL;
    PRT_VALUE* PTMP_tmp30 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_14 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_9 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_153 = &(PTMP_tmp0_21);
    PrtFreeValue(*P_LVALUE_153);
    *P_LVALUE_153 = PrtMkBoolValue(PrtPrimGetInt(*P_VAR_Term) <= PrtPrimGetInt(p_this->varValues[0]));
    
    if (PrtPrimGetBool(PTMP_tmp0_21))
    {
        PrtFormatPrintf("New term ", 2, *P_VAR_Term, p_this->varValues[0], 2, 0, " not greater than CurrentTerm ", 1, "");
        
    }
    
    else
    {
    }
    
    
    PRT_VALUE** P_LVALUE_154 = &(PTMP_tmp1_20);
    PrtFreeValue(*P_LVALUE_154);
    *P_LVALUE_154 = PrtMkBoolValue(PrtPrimGetInt(*P_VAR_Term) > PrtPrimGetInt(p_this->varValues[0]));
    
    PrtAssert(PrtPrimGetBool(PTMP_tmp1_20), "");
    
    PRT_VALUE** P_LVALUE_155 = &(p_this->varValues[0]);
    PrtFreeValue(*P_LVALUE_155);
    *P_LVALUE_155 = PrtCloneValue(*P_VAR_Term);
    
    PRT_VALUE** P_LVALUE_156 = &(PTMP_tmp2_14);
    PrtFreeValue(*P_LVALUE_156);
    *P_LVALUE_156 = PrtMkBoolValue(PrtMapExists(p_this->varValues[1], p_this->varValues[0]));;
    
    if (PrtPrimGetBool(PTMP_tmp2_14))
    {
        PrtFormatPrintf("Detected more than one leader in term ", 1, p_this->varValues[0], 1, 0, "");
        
    }
    
    else
    {
    }
    
    
    PRT_VALUE** P_LVALUE_157 = &(PTMP_tmp3_10);
    PrtFreeValue(*P_LVALUE_157);
    *P_LVALUE_157 = PrtMkBoolValue(PrtMapExists(p_this->varValues[1], p_this->varValues[0]));;
    
    PRT_VALUE** P_LVALUE_158 = &(PTMP_tmp4_6);
    PrtFreeValue(*P_LVALUE_158);
    *P_LVALUE_158 = PrtMkBoolValue(!PrtPrimGetBool(PTMP_tmp3_10));
    
    PrtAssert(PrtPrimGetBool(PTMP_tmp4_6), "");
    
    PRT_VALUE** P_LVALUE_159 = &(*(PrtMapGetLValue(p_this->varValues[1], p_this->varValues[0], PRT_TRUE, &P_GEND_TYPE_MKiVb)));
    PrtFreeValue(*P_LVALUE_159);
    *P_LVALUE_159 = PrtCloneValue((&P_LIT_BOOLEAN_9));
    
    PRT_VALUE** P_LVALUE_160 = &(PTMP_tmp5_6);
    PrtFreeValue(*P_LVALUE_160);
    *P_LVALUE_160 = PrtMapGetKeys(p_this->varValues[3]);
    
    {
        PRT_VALUE** P_LVALUE_161 = &(P_VAR_terms);
        PrtFreeValue(*P_LVALUE_161);
        *P_LVALUE_161 = PTMP_tmp5_6;
        PTMP_tmp5_6 = NULL;
    }
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_9)))
    {
        PRT_VALUE** P_LVALUE_162 = &(PTMP_tmp6_6);
        PrtFreeValue(*P_LVALUE_162);
        *P_LVALUE_162 = PrtMkIntValue(PrtSeqSizeOf(P_VAR_terms));
        
        PRT_VALUE** P_LVALUE_163 = &(PTMP_tmp7_6);
        PrtFreeValue(*P_LVALUE_163);
        *P_LVALUE_163 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_i) < PrtPrimGetInt(PTMP_tmp6_6));
        
        PRT_VALUE** P_LVALUE_164 = &(PTMP_tmp8_6);
        PrtFreeValue(*P_LVALUE_164);
        *P_LVALUE_164 = PrtCloneValue(PTMP_tmp7_6);
        
        if (PrtPrimGetBool(PTMP_tmp8_6))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_165 = &(PTMP_tmp9_4);
        PrtFreeValue(*P_LVALUE_165);
        *P_LVALUE_165 = PrtSeqGet(P_VAR_terms, P_VAR_i);
        
        PRT_VALUE** P_LVALUE_166 = &(PTMP_tmp10_4);
        PrtFreeValue(*P_LVALUE_166);
        *P_LVALUE_166 = PrtMapGet(p_this->varValues[3], PTMP_tmp9_4);
        
        {
            PRT_VALUE** P_LVALUE_167 = &(P_VAR_PrevCommitted);
            PrtFreeValue(*P_LVALUE_167);
            *P_LVALUE_167 = PTMP_tmp10_4;
            PTMP_tmp10_4 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_168 = &(PTMP_tmp11_4);
        PrtFreeValue(*P_LVALUE_168);
        *P_LVALUE_168 = PrtMkIntValue(PrtSeqSizeOf(*P_VAR_Logs));
        
        PRT_VALUE** P_LVALUE_169 = &(PTMP_tmp12_3);
        PrtFreeValue(*P_LVALUE_169);
        *P_LVALUE_169 = PrtMkIntValue(PrtSeqSizeOf(P_VAR_PrevCommitted));
        
        PRT_VALUE** P_LVALUE_170 = &(PTMP_tmp13_3);
        PrtFreeValue(*P_LVALUE_170);
        *P_LVALUE_170 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp11_4) < PrtPrimGetInt(PTMP_tmp12_3));
        
        if (PrtPrimGetBool(PTMP_tmp13_3))
        {
            PrtFormatPrintf("prevCommitted ", 1, P_VAR_PrevCommitted, 1, 0, "");
            
            PrtFormatPrintf("new leader log ", 1, *P_VAR_Logs, 1, 0, "");
            
            PRT_VALUE** P_LVALUE_171 = &(PTMP_tmp14_3);
            PrtFreeValue(*P_LVALUE_171);
            *P_LVALUE_171 = PrtMkIntValue(PrtSeqSizeOf(*P_VAR_Logs));
            
            PRT_VALUE** P_LVALUE_172 = &(PTMP_tmp15_3);
            PrtFreeValue(*P_LVALUE_172);
            *P_LVALUE_172 = PrtMkIntValue(PrtSeqSizeOf(P_VAR_PrevCommitted));
            
            PRT_VALUE** P_LVALUE_173 = &(PTMP_tmp16_2);
            PrtFreeValue(*P_LVALUE_173);
            *P_LVALUE_173 = PrtSeqGet(P_VAR_terms, P_VAR_i);
            
            PrtFormatPrintf("New Term ", 4, p_this->varValues[0], PTMP_tmp14_3, PTMP_tmp15_3, PTMP_tmp16_2, 4, 0, " leader's Log size ", 1, " is less than previously committed log size ", 2, " of term ", 3, "");
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_174 = &(PTMP_tmp17_1);
        PrtFreeValue(*P_LVALUE_174);
        *P_LVALUE_174 = PrtMkIntValue(PrtSeqSizeOf(*P_VAR_Logs));
        
        PRT_VALUE** P_LVALUE_175 = &(PTMP_tmp18_1);
        PrtFreeValue(*P_LVALUE_175);
        *P_LVALUE_175 = PrtMkIntValue(PrtSeqSizeOf(P_VAR_PrevCommitted));
        
        PRT_VALUE** P_LVALUE_176 = &(PTMP_tmp19_1);
        PrtFreeValue(*P_LVALUE_176);
        *P_LVALUE_176 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp17_1) >= PrtPrimGetInt(PTMP_tmp18_1));
        
        PrtAssert(PrtPrimGetBool(PTMP_tmp19_1), "");
        
        while (PrtPrimGetBool((&P_LIT_BOOLEAN_9)))
        {
            PRT_VALUE** P_LVALUE_177 = &(PTMP_tmp20_1);
            PrtFreeValue(*P_LVALUE_177);
            *P_LVALUE_177 = PrtMkIntValue(PrtSeqSizeOf(P_VAR_PrevCommitted));
            
            PRT_VALUE** P_LVALUE_178 = &(PTMP_tmp21_1);
            PrtFreeValue(*P_LVALUE_178);
            *P_LVALUE_178 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_j) < PrtPrimGetInt(PTMP_tmp20_1));
            
            PRT_VALUE** P_LVALUE_179 = &(PTMP_tmp22_1);
            PrtFreeValue(*P_LVALUE_179);
            *P_LVALUE_179 = PrtCloneValue(PTMP_tmp21_1);
            
            if (PrtPrimGetBool(PTMP_tmp22_1))
            {
            }
            
            else
            {
                break;
                
            }
            
            
            PRT_VALUE** P_LVALUE_180 = &(PTMP_tmp23_1);
            PrtFreeValue(*P_LVALUE_180);
            *P_LVALUE_180 = PrtSeqGet(P_VAR_PrevCommitted, P_VAR_j);
            
            PRT_VALUE** P_LVALUE_181 = &(PTMP_tmp24);
            PrtFreeValue(*P_LVALUE_181);
            *P_LVALUE_181 = PrtSeqGet(*P_VAR_Logs, P_VAR_j);
            
            PRT_VALUE** P_LVALUE_182 = &(PTMP_tmp25);
            PrtFreeValue(*P_LVALUE_182);
            *P_LVALUE_182 = PrtMkBoolValue(!PrtIsEqualValue(PTMP_tmp23_1, PTMP_tmp24));
            
            if (PrtPrimGetBool(PTMP_tmp25))
            {
                PrtPrintf("Newly elected leader should have all previously committed log entries from previous terms.");
                
            }
            
            else
            {
            }
            
            
            PRT_VALUE** P_LVALUE_183 = &(PTMP_tmp26);
            PrtFreeValue(*P_LVALUE_183);
            *P_LVALUE_183 = PrtSeqGet(P_VAR_PrevCommitted, P_VAR_j);
            
            PRT_VALUE** P_LVALUE_184 = &(PTMP_tmp27);
            PrtFreeValue(*P_LVALUE_184);
            *P_LVALUE_184 = PrtSeqGet(*P_VAR_Logs, P_VAR_j);
            
            PRT_VALUE** P_LVALUE_185 = &(PTMP_tmp28);
            PrtFreeValue(*P_LVALUE_185);
            *P_LVALUE_185 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp26, PTMP_tmp27));
            
            PrtAssert(PrtPrimGetBool(PTMP_tmp28), "");
            
            PRT_VALUE** P_LVALUE_186 = &(PTMP_tmp29);
            PrtFreeValue(*P_LVALUE_186);
            *P_LVALUE_186 = PrtMkIntValue(PrtPrimGetInt(P_VAR_j) + PrtPrimGetInt((&P_LIT_INT32_14)));
            
            {
                PRT_VALUE** P_LVALUE_187 = &(P_VAR_j);
                PrtFreeValue(*P_LVALUE_187);
                *P_LVALUE_187 = PTMP_tmp29;
                PTMP_tmp29 = NULL;
            }
            
        }
        
        
        PRT_VALUE** P_LVALUE_188 = &(PTMP_tmp30);
        PrtFreeValue(*P_LVALUE_188);
        *P_LVALUE_188 = PrtMkIntValue(PrtPrimGetInt(P_VAR_i) + PrtPrimGetInt((&P_LIT_INT32_14)));
        
        {
            PRT_VALUE** P_LVALUE_189 = &(P_VAR_i);
            PrtFreeValue(*P_LVALUE_189);
            *P_LVALUE_189 = PTMP_tmp30;
            PTMP_tmp30 = NULL;
        }
        
    }
    
    
p_return_22: ;
    PrtFreeValue(P_VAR_i); P_VAR_i = NULL;
    PrtFreeValue(P_VAR_j); P_VAR_j = NULL;
    PrtFreeValue(P_VAR_PrevCommitted); P_VAR_PrevCommitted = NULL;
    PrtFreeValue(P_VAR_terms); P_VAR_terms = NULL;
    PrtFreeValue(PTMP_tmp0_21); PTMP_tmp0_21 = NULL;
    PrtFreeValue(PTMP_tmp1_20); PTMP_tmp1_20 = NULL;
    PrtFreeValue(PTMP_tmp2_14); PTMP_tmp2_14 = NULL;
    PrtFreeValue(PTMP_tmp3_10); PTMP_tmp3_10 = NULL;
    PrtFreeValue(PTMP_tmp4_6); PTMP_tmp4_6 = NULL;
    PrtFreeValue(PTMP_tmp5_6); PTMP_tmp5_6 = NULL;
    PrtFreeValue(PTMP_tmp6_6); PTMP_tmp6_6 = NULL;
    PrtFreeValue(PTMP_tmp7_6); PTMP_tmp7_6 = NULL;
    PrtFreeValue(PTMP_tmp8_6); PTMP_tmp8_6 = NULL;
    PrtFreeValue(PTMP_tmp9_4); PTMP_tmp9_4 = NULL;
    PrtFreeValue(PTMP_tmp10_4); PTMP_tmp10_4 = NULL;
    PrtFreeValue(PTMP_tmp11_4); PTMP_tmp11_4 = NULL;
    PrtFreeValue(PTMP_tmp12_3); PTMP_tmp12_3 = NULL;
    PrtFreeValue(PTMP_tmp13_3); PTMP_tmp13_3 = NULL;
    PrtFreeValue(PTMP_tmp14_3); PTMP_tmp14_3 = NULL;
    PrtFreeValue(PTMP_tmp15_3); PTMP_tmp15_3 = NULL;
    PrtFreeValue(PTMP_tmp16_2); PTMP_tmp16_2 = NULL;
    PrtFreeValue(PTMP_tmp17_1); PTMP_tmp17_1 = NULL;
    PrtFreeValue(PTMP_tmp18_1); PTMP_tmp18_1 = NULL;
    PrtFreeValue(PTMP_tmp19_1); PTMP_tmp19_1 = NULL;
    PrtFreeValue(PTMP_tmp20_1); PTMP_tmp20_1 = NULL;
    PrtFreeValue(PTMP_tmp21_1); PTMP_tmp21_1 = NULL;
    PrtFreeValue(PTMP_tmp22_1); PTMP_tmp22_1 = NULL;
    PrtFreeValue(PTMP_tmp23_1); PTMP_tmp23_1 = NULL;
    PrtFreeValue(PTMP_tmp24); PTMP_tmp24 = NULL;
    PrtFreeValue(PTMP_tmp25); PTMP_tmp25 = NULL;
    PrtFreeValue(PTMP_tmp26); PTMP_tmp26 = NULL;
    PrtFreeValue(PTMP_tmp27); PTMP_tmp27 = NULL;
    PrtFreeValue(PTMP_tmp28); PTMP_tmp28 = NULL;
    PrtFreeValue(PTMP_tmp29); PTMP_tmp29 = NULL;
    PrtFreeValue(PTMP_tmp30); PTMP_tmp30 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_ProcessLeaderElected =
{
    "ProcessLeaderElected",
    &P_ProcessLeaderElected_IMPL,
    NULL
};


PRT_VALUE* P_ProcessLogAppend_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_Server = argRefs[0];
    PRT_VALUE** P_VAR_Logs_1 = argRefs[1];
    PRT_VALUE* P_VAR_i_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_j_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_sharedMinIndex = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_Servers = PrtMkDefaultValue(&P_GEND_TYPE_Sm);
    PRT_VALUE* PTMP_tmp0_22 = NULL;
    PRT_VALUE* PTMP_tmp1_21 = NULL;
    PRT_VALUE* PTMP_tmp2_15 = NULL;
    PRT_VALUE* PTMP_tmp3_11 = NULL;
    PRT_VALUE* PTMP_tmp4_7 = NULL;
    PRT_VALUE* PTMP_tmp5_7 = NULL;
    PRT_VALUE* PTMP_tmp6_7 = NULL;
    PRT_VALUE* PTMP_tmp7_7 = NULL;
    PRT_VALUE* PTMP_tmp8_7 = NULL;
    PRT_VALUE* PTMP_tmp9_5 = NULL;
    PRT_VALUE* PTMP_tmp10_5 = NULL;
    PRT_VALUE* PTMP_tmp11_5 = NULL;
    PRT_VALUE* PTMP_tmp12_4 = NULL;
    PRT_VALUE* PTMP_tmp13_4 = NULL;
    PRT_VALUE* PTMP_tmp14_4 = NULL;
    PRT_VALUE* PTMP_tmp15_4 = NULL;
    PRT_VALUE* PTMP_tmp16_3 = NULL;
    PRT_VALUE* PTMP_tmp17_2 = NULL;
    PRT_VALUE* PTMP_tmp18_2 = NULL;
    PRT_VALUE* PTMP_tmp19_2 = NULL;
    PRT_VALUE* PTMP_tmp20_2 = NULL;
    PRT_VALUE* PTMP_tmp21_2 = NULL;
    PRT_VALUE* PTMP_tmp22_2 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_15 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_16 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_10 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_190 = &(PTMP_tmp0_22);
    PrtFreeValue(*P_LVALUE_190);
    *P_LVALUE_190 = PrtMkBoolValue(PrtMapExists(p_this->varValues[2], *P_VAR_Server));;
    
    PRT_VALUE** P_LVALUE_191 = &(PTMP_tmp1_21);
    PrtFreeValue(*P_LVALUE_191);
    *P_LVALUE_191 = PrtMkBoolValue(!PrtPrimGetBool(PTMP_tmp0_22));
    
    if (PrtPrimGetBool(PTMP_tmp1_21))
    {
        PRT_VALUE** P_LVALUE_192 = &(*(PrtMapGetLValue(p_this->varValues[2], *P_VAR_Server, PRT_TRUE, &P_GEND_TYPE_MKmVST3irr)));
        PrtFreeValue(*P_LVALUE_192);
        *P_LVALUE_192 = PrtCloneValue(*P_VAR_Logs_1);
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_193 = &(P_VAR_i_1);
        PrtFreeValue(*P_LVALUE_193);
        *P_LVALUE_193 = PrtCloneValue((&P_LIT_INT32_15));
        
        PRT_VALUE** P_LVALUE_194 = &(*(PrtMapGetLValue(p_this->varValues[2], *P_VAR_Server, PRT_TRUE, &P_GEND_TYPE_MKmVST3irr)));
        PrtFreeValue(*P_LVALUE_194);
        *P_LVALUE_194 = PrtCloneValue(*P_VAR_Logs_1);
        
        PRT_VALUE** P_LVALUE_195 = &(PTMP_tmp2_15);
        PrtFreeValue(*P_LVALUE_195);
        *P_LVALUE_195 = PrtMapGetKeys(p_this->varValues[2]);
        
        {
            PRT_VALUE** P_LVALUE_196 = &(P_VAR_Servers);
            PrtFreeValue(*P_LVALUE_196);
            *P_LVALUE_196 = PTMP_tmp2_15;
            PTMP_tmp2_15 = NULL;
        }
        
        while (PrtPrimGetBool((&P_LIT_BOOLEAN_10)))
        {
            PRT_VALUE** P_LVALUE_197 = &(PTMP_tmp3_11);
            PrtFreeValue(*P_LVALUE_197);
            *P_LVALUE_197 = PrtMkIntValue(PrtSeqSizeOf(P_VAR_Servers));
            
            PRT_VALUE** P_LVALUE_198 = &(PTMP_tmp4_7);
            PrtFreeValue(*P_LVALUE_198);
            *P_LVALUE_198 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_i_1) < PrtPrimGetInt(PTMP_tmp3_11));
            
            PRT_VALUE** P_LVALUE_199 = &(PTMP_tmp5_7);
            PrtFreeValue(*P_LVALUE_199);
            *P_LVALUE_199 = PrtCloneValue(PTMP_tmp4_7);
            
            if (PrtPrimGetBool(PTMP_tmp5_7))
            {
            }
            
            else
            {
                break;
                
            }
            
            
            PRT_VALUE** P_LVALUE_200 = &(P_VAR_j_1);
            PrtFreeValue(*P_LVALUE_200);
            *P_LVALUE_200 = PrtCloneValue((&P_LIT_INT32_15));
            
            PRT_VALUE** P_LVALUE_201 = &(PTMP_tmp6_7);
            PrtFreeValue(*P_LVALUE_201);
            *P_LVALUE_201 = PrtSeqGet(P_VAR_Servers, P_VAR_i_1);
            
            PRT_VALUE** P_LVALUE_202 = &(PTMP_tmp7_7);
            PrtFreeValue(*P_LVALUE_202);
            *P_LVALUE_202 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp6_7, *P_VAR_Server));
            
            if (PrtPrimGetBool(PTMP_tmp7_7))
            {
                PRT_VALUE** P_LVALUE_203 = &(PTMP_tmp8_7);
                PrtFreeValue(*P_LVALUE_203);
                *P_LVALUE_203 = PrtMkIntValue(PrtPrimGetInt(P_VAR_i_1) + PrtPrimGetInt((&P_LIT_INT32_16)));
                
                {
                    PRT_VALUE** P_LVALUE_204 = &(P_VAR_i_1);
                    PrtFreeValue(*P_LVALUE_204);
                    *P_LVALUE_204 = PTMP_tmp8_7;
                    PTMP_tmp8_7 = NULL;
                }
                
                continue;
                
            }
            
            else
            {
            }
            
            
            PRT_VALUE** P_LVALUE_205 = &(PTMP_tmp9_5);
            PrtFreeValue(*P_LVALUE_205);
            *P_LVALUE_205 = PrtSeqGet(P_VAR_Servers, P_VAR_i_1);
            
            PRT_VALUE** P_LVALUE_206 = &(PTMP_tmp10_5);
            PrtFreeValue(*P_LVALUE_206);
            *P_LVALUE_206 = PrtMapGet(p_this->varValues[2], PTMP_tmp9_5);
            
            PRT_VALUE** P_LVALUE_207 = &(PTMP_tmp11_5);
            PrtFreeValue(*P_LVALUE_207);
            *P_LVALUE_207 = PrtCloneValue(*P_VAR_Logs_1);
            
            PRT_VALUE** P_LVALUE_208 = &(PTMP_tmp12_4);
            PrtFreeValue(*P_LVALUE_208);
            *P_LVALUE_208 = ((_P_GEN_funargs[0] = &(PTMP_tmp10_5)), (_P_GEN_funargs[1] = &(PTMP_tmp11_5)), (_P_GEN_funval = P_getSharedMinIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp10_5), PTMP_tmp10_5 = NULL), (PrtFreeValue(PTMP_tmp11_5), PTMP_tmp11_5 = NULL), (_P_GEN_funval));
            if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                goto p_return_23;
            }
            if (p_this->isHalted == PRT_TRUE) {
                PrtFreeValue(_P_GEN_retval);
                _P_GEN_retval = NULL;
                goto p_return_23;
            }
            
            {
                PRT_VALUE** P_LVALUE_209 = &(P_VAR_sharedMinIndex);
                PrtFreeValue(*P_LVALUE_209);
                *P_LVALUE_209 = PTMP_tmp12_4;
                PTMP_tmp12_4 = NULL;
            }
            
            PRT_VALUE** P_LVALUE_210 = &(PTMP_tmp13_4);
            PrtFreeValue(*P_LVALUE_210);
            *P_LVALUE_210 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_sharedMinIndex) >= PrtPrimGetInt((&P_LIT_INT32_15)));
            
            if (PrtPrimGetBool(PTMP_tmp13_4))
            {
                while (PrtPrimGetBool((&P_LIT_BOOLEAN_10)))
                {
                    PRT_VALUE** P_LVALUE_211 = &(PTMP_tmp14_4);
                    PrtFreeValue(*P_LVALUE_211);
                    *P_LVALUE_211 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_j_1) <= PrtPrimGetInt(P_VAR_sharedMinIndex));
                    
                    PRT_VALUE** P_LVALUE_212 = &(PTMP_tmp15_4);
                    PrtFreeValue(*P_LVALUE_212);
                    *P_LVALUE_212 = PrtCloneValue(PTMP_tmp14_4);
                    
                    if (PrtPrimGetBool(PTMP_tmp15_4))
                    {
                    }
                    
                    else
                    {
                        break;
                        
                    }
                    
                    
                    PRT_VALUE** P_LVALUE_213 = &(PTMP_tmp16_3);
                    PrtFreeValue(*P_LVALUE_213);
                    *P_LVALUE_213 = PrtSeqGet(P_VAR_Servers, P_VAR_i_1);
                    
                    PRT_VALUE** P_LVALUE_214 = &(PTMP_tmp17_2);
                    PrtFreeValue(*P_LVALUE_214);
                    *P_LVALUE_214 = PrtMapGet(p_this->varValues[2], PTMP_tmp16_3);
                    
                    PRT_VALUE** P_LVALUE_215 = &(PTMP_tmp18_2);
                    PrtFreeValue(*P_LVALUE_215);
                    *P_LVALUE_215 = PrtSeqGet(PTMP_tmp17_2, P_VAR_j_1);
                    
                    PRT_VALUE** P_LVALUE_216 = &(PTMP_tmp19_2);
                    PrtFreeValue(*P_LVALUE_216);
                    *P_LVALUE_216 = PrtSeqGet(*P_VAR_Logs_1, P_VAR_j_1);
                    
                    PRT_VALUE** P_LVALUE_217 = &(PTMP_tmp20_2);
                    PrtFreeValue(*P_LVALUE_217);
                    *P_LVALUE_217 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp18_2, PTMP_tmp19_2));
                    
                    PrtAssert(PrtPrimGetBool(PTMP_tmp20_2), "");
                    
                    PRT_VALUE** P_LVALUE_218 = &(PTMP_tmp21_2);
                    PrtFreeValue(*P_LVALUE_218);
                    *P_LVALUE_218 = PrtMkIntValue(PrtPrimGetInt(P_VAR_j_1) + PrtPrimGetInt((&P_LIT_INT32_16)));
                    
                    {
                        PRT_VALUE** P_LVALUE_219 = &(P_VAR_j_1);
                        PrtFreeValue(*P_LVALUE_219);
                        *P_LVALUE_219 = PTMP_tmp21_2;
                        PTMP_tmp21_2 = NULL;
                    }
                    
                }
                
                
            }
            
            else
            {
            }
            
            
            PRT_VALUE** P_LVALUE_220 = &(PTMP_tmp22_2);
            PrtFreeValue(*P_LVALUE_220);
            *P_LVALUE_220 = PrtMkIntValue(PrtPrimGetInt(P_VAR_i_1) + PrtPrimGetInt((&P_LIT_INT32_16)));
            
            {
                PRT_VALUE** P_LVALUE_221 = &(P_VAR_i_1);
                PrtFreeValue(*P_LVALUE_221);
                *P_LVALUE_221 = PTMP_tmp22_2;
                PTMP_tmp22_2 = NULL;
            }
            
        }
        
        
    }
    
    
p_return_23: ;
    PrtFreeValue(P_VAR_i_1); P_VAR_i_1 = NULL;
    PrtFreeValue(P_VAR_j_1); P_VAR_j_1 = NULL;
    PrtFreeValue(P_VAR_sharedMinIndex); P_VAR_sharedMinIndex = NULL;
    PrtFreeValue(P_VAR_Servers); P_VAR_Servers = NULL;
    PrtFreeValue(PTMP_tmp0_22); PTMP_tmp0_22 = NULL;
    PrtFreeValue(PTMP_tmp1_21); PTMP_tmp1_21 = NULL;
    PrtFreeValue(PTMP_tmp2_15); PTMP_tmp2_15 = NULL;
    PrtFreeValue(PTMP_tmp3_11); PTMP_tmp3_11 = NULL;
    PrtFreeValue(PTMP_tmp4_7); PTMP_tmp4_7 = NULL;
    PrtFreeValue(PTMP_tmp5_7); PTMP_tmp5_7 = NULL;
    PrtFreeValue(PTMP_tmp6_7); PTMP_tmp6_7 = NULL;
    PrtFreeValue(PTMP_tmp7_7); PTMP_tmp7_7 = NULL;
    PrtFreeValue(PTMP_tmp8_7); PTMP_tmp8_7 = NULL;
    PrtFreeValue(PTMP_tmp9_5); PTMP_tmp9_5 = NULL;
    PrtFreeValue(PTMP_tmp10_5); PTMP_tmp10_5 = NULL;
    PrtFreeValue(PTMP_tmp11_5); PTMP_tmp11_5 = NULL;
    PrtFreeValue(PTMP_tmp12_4); PTMP_tmp12_4 = NULL;
    PrtFreeValue(PTMP_tmp13_4); PTMP_tmp13_4 = NULL;
    PrtFreeValue(PTMP_tmp14_4); PTMP_tmp14_4 = NULL;
    PrtFreeValue(PTMP_tmp15_4); PTMP_tmp15_4 = NULL;
    PrtFreeValue(PTMP_tmp16_3); PTMP_tmp16_3 = NULL;
    PrtFreeValue(PTMP_tmp17_2); PTMP_tmp17_2 = NULL;
    PrtFreeValue(PTMP_tmp18_2); PTMP_tmp18_2 = NULL;
    PrtFreeValue(PTMP_tmp19_2); PTMP_tmp19_2 = NULL;
    PrtFreeValue(PTMP_tmp20_2); PTMP_tmp20_2 = NULL;
    PrtFreeValue(PTMP_tmp21_2); PTMP_tmp21_2 = NULL;
    PrtFreeValue(PTMP_tmp22_2); PTMP_tmp22_2 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_ProcessLogAppend =
{
    "ProcessLogAppend",
    &P_ProcessLogAppend_IMPL,
    NULL
};


PRT_VALUE* P_getSharedMinIndex_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE** P_VAR_Logs1 = argRefs[0];
    PRT_VALUE** P_VAR_Logs2 = argRefs[1];
    PRT_VALUE* P_VAR_idx_4 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_23 = NULL;
    PRT_VALUE* PTMP_tmp1_22 = NULL;
    PRT_VALUE* PTMP_tmp2_16 = NULL;
    PRT_VALUE* PTMP_tmp3_12 = NULL;
    PRT_VALUE* PTMP_tmp4_8 = NULL;
    PRT_VALUE* PTMP_tmp5_8 = NULL;
    PRT_VALUE* PTMP_tmp6_8 = NULL;
    PRT_VALUE* PTMP_tmp7_8 = NULL;
    PRT_VALUE* PTMP_tmp8_8 = NULL;
    PRT_VALUE* PTMP_tmp9_6 = NULL;
    PRT_VALUE* PTMP_tmp10_6 = NULL;
    PRT_VALUE* PTMP_tmp11_6 = NULL;
    PRT_VALUE* PTMP_tmp12_5 = NULL;
    PRT_VALUE* PTMP_tmp13_5 = NULL;
    PRT_VALUE* PTMP_tmp14_5 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_17 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_INT32_18 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_BOOLEAN_11 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_222 = &(PTMP_tmp0_23);
    PrtFreeValue(*P_LVALUE_222);
    *P_LVALUE_222 = PrtMkIntValue(PrtSeqSizeOf(*P_VAR_Logs1));
    
    PRT_VALUE** P_LVALUE_223 = &(PTMP_tmp1_22);
    PrtFreeValue(*P_LVALUE_223);
    *P_LVALUE_223 = PrtMkIntValue(PrtSeqSizeOf(*P_VAR_Logs2));
    
    PRT_VALUE** P_LVALUE_224 = &(PTMP_tmp2_16);
    PrtFreeValue(*P_LVALUE_224);
    *P_LVALUE_224 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_23) > PrtPrimGetInt(PTMP_tmp1_22));
    
    if (PrtPrimGetBool(PTMP_tmp2_16))
    {
        PRT_VALUE** P_LVALUE_225 = &(PTMP_tmp3_12);
        PrtFreeValue(*P_LVALUE_225);
        *P_LVALUE_225 = PrtMkIntValue(PrtSeqSizeOf(*P_VAR_Logs2));
        
        PRT_VALUE** P_LVALUE_226 = &(PTMP_tmp4_8);
        PrtFreeValue(*P_LVALUE_226);
        *P_LVALUE_226 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp3_12) - PrtPrimGetInt((&P_LIT_INT32_17)));
        
        {
            PRT_VALUE** P_LVALUE_227 = &(P_VAR_idx_4);
            PrtFreeValue(*P_LVALUE_227);
            *P_LVALUE_227 = PTMP_tmp4_8;
            PTMP_tmp4_8 = NULL;
        }
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_228 = &(PTMP_tmp5_8);
        PrtFreeValue(*P_LVALUE_228);
        *P_LVALUE_228 = PrtMkIntValue(PrtSeqSizeOf(*P_VAR_Logs1));
        
        PRT_VALUE** P_LVALUE_229 = &(PTMP_tmp6_8);
        PrtFreeValue(*P_LVALUE_229);
        *P_LVALUE_229 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp5_8) - PrtPrimGetInt((&P_LIT_INT32_17)));
        
        {
            PRT_VALUE** P_LVALUE_230 = &(P_VAR_idx_4);
            PrtFreeValue(*P_LVALUE_230);
            *P_LVALUE_230 = PTMP_tmp6_8;
            PTMP_tmp6_8 = NULL;
        }
        
    }
    
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_11)))
    {
        PRT_VALUE** P_LVALUE_231 = &(PTMP_tmp7_8);
        PrtFreeValue(*P_LVALUE_231);
        *P_LVALUE_231 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_4) >= PrtPrimGetInt((&P_LIT_INT32_18)));
        
        PRT_VALUE** P_LVALUE_232 = &(PTMP_tmp8_8);
        PrtFreeValue(*P_LVALUE_232);
        *P_LVALUE_232 = PrtCloneValue(PTMP_tmp7_8);
        
        if (PrtPrimGetBool(PTMP_tmp8_8))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_233 = &(PTMP_tmp9_6);
        PrtFreeValue(*P_LVALUE_233);
        *P_LVALUE_233 = PrtSeqGet(*P_VAR_Logs1, P_VAR_idx_4);
        
        PRT_VALUE** P_LVALUE_234 = &(PTMP_tmp10_6);
        PrtFreeValue(*P_LVALUE_234);
        *P_LVALUE_234 = PrtTupleGet(PTMP_tmp9_6, 0);
        
        PRT_VALUE** P_LVALUE_235 = &(PTMP_tmp11_6);
        PrtFreeValue(*P_LVALUE_235);
        *P_LVALUE_235 = PrtSeqGet(*P_VAR_Logs2, P_VAR_idx_4);
        
        PRT_VALUE** P_LVALUE_236 = &(PTMP_tmp12_5);
        PrtFreeValue(*P_LVALUE_236);
        *P_LVALUE_236 = PrtTupleGet(PTMP_tmp11_6, 0);
        
        PRT_VALUE** P_LVALUE_237 = &(PTMP_tmp13_5);
        PrtFreeValue(*P_LVALUE_237);
        *P_LVALUE_237 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp10_6, PTMP_tmp12_5));
        
        if (PrtPrimGetBool(PTMP_tmp13_5))
        {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = PrtCloneValue(P_VAR_idx_4);
            goto p_return_24;
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_238 = &(PTMP_tmp14_5);
        PrtFreeValue(*P_LVALUE_238);
        *P_LVALUE_238 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_4) - PrtPrimGetInt((&P_LIT_INT32_17)));
        
        {
            PRT_VALUE** P_LVALUE_239 = &(P_VAR_idx_4);
            PrtFreeValue(*P_LVALUE_239);
            *P_LVALUE_239 = PTMP_tmp14_5;
            PTMP_tmp14_5 = NULL;
        }
        
    }
    
    
    PrtFreeValue(_P_GEN_retval);
    _P_GEN_retval = PrtCloneValue(P_VAR_idx_4);
    goto p_return_24;
    
p_return_24: ;
    PrtFreeValue(P_VAR_idx_4); P_VAR_idx_4 = NULL;
    PrtFreeValue(PTMP_tmp0_23); PTMP_tmp0_23 = NULL;
    PrtFreeValue(PTMP_tmp1_22); PTMP_tmp1_22 = NULL;
    PrtFreeValue(PTMP_tmp2_16); PTMP_tmp2_16 = NULL;
    PrtFreeValue(PTMP_tmp3_12); PTMP_tmp3_12 = NULL;
    PrtFreeValue(PTMP_tmp4_8); PTMP_tmp4_8 = NULL;
    PrtFreeValue(PTMP_tmp5_8); PTMP_tmp5_8 = NULL;
    PrtFreeValue(PTMP_tmp6_8); PTMP_tmp6_8 = NULL;
    PrtFreeValue(PTMP_tmp7_8); PTMP_tmp7_8 = NULL;
    PrtFreeValue(PTMP_tmp8_8); PTMP_tmp8_8 = NULL;
    PrtFreeValue(PTMP_tmp9_6); PTMP_tmp9_6 = NULL;
    PrtFreeValue(PTMP_tmp10_6); PTMP_tmp10_6 = NULL;
    PrtFreeValue(PTMP_tmp11_6); PTMP_tmp11_6 = NULL;
    PrtFreeValue(PTMP_tmp12_5); PTMP_tmp12_5 = NULL;
    PrtFreeValue(PTMP_tmp13_5); PTMP_tmp13_5 = NULL;
    PrtFreeValue(PTMP_tmp14_5); PTMP_tmp14_5 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_getSharedMinIndex =
{
    "getSharedMinIndex",
    &P_getSharedMinIndex_IMPL,
    NULL
};


PRT_FUNDECL* P_SafetyMonitor_METHODS[] = { &P_FUNCTION_Anon_14, &P_FUNCTION_Anon_15, &P_FUNCTION_Anon_16, &P_FUNCTION_Anon_17, &P_FUNCTION_ProcessLeaderElected, &P_FUNCTION_ProcessLogAppend, &P_FUNCTION_getSharedMinIndex };

PRT_EVENTDECL* P_SafetyMonitor_RECV_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_SafetyMonitor_RECV =
{
    0U,
    P_SafetyMonitor_RECV_INNER,
    NULL
};

PRT_EVENTDECL* P_SafetyMonitor_SEND_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_SafetyMonitor_SEND =
{
    0U,
    P_SafetyMonitor_SEND_INNER,
    NULL
};

PRT_MACHINEDECL P_MACHINE_SafetyMonitor = 
{
    1U,
    "SafetyMonitor",
    &P_EVENTSET_SafetyMonitor_RECV,
    &P_EVENTSET_SafetyMonitor_SEND,
    NULL,
    4U,
    2U,
    7U,
    4294967295U,
    0U,
    P_SafetyMonitor_VARS,
    P_SafetyMonitor_STATES,
    P_SafetyMonitor_METHODS
};

PRT_VARDECL P_Server_VARS[] = {
    { "ClusterManager", &P_GEND_TYPE_m },
    { "Servers", &P_GEND_TYPE_Sm },
    { "LeaderId", &P_GEND_TYPE_m },
    { "CurrentTerm", &P_GEND_TYPE_i },
    { "VotedFor", &P_GEND_TYPE_m },
    { "Logs", &P_GEND_TYPE_ST3irr },
    { "ConfigLogs", &P_GEND_TYPE_ST2iSm },
    { "CommitServers", &P_GEND_TYPE_Sm },
    { "CommitIndex", &P_GEND_TYPE_T2ii },
    { "NextIndex", &P_GEND_TYPE_MKmVT2ii },
    { "MatchIndex", &P_GEND_TYPE_MKmVT2ii },
    { "VotesReceived", &P_GEND_TYPE_i },
    { "LastClientRequest", &P_GEND_TYPE_T3mrr },
    { "UpdateServer", &P_GEND_TYPE_m },
    { "UpdateType", &P_GEND_TYPE_i },
    { "MaxTicks", &P_GEND_TYPE_i },
    { "TickCounter", &P_GEND_TYPE_i },
    { "LeaderNotInCfg", &P_GEND_TYPE_b }
};

PRT_EVENTDECL* P_Init_DEFERS_INNER_2[] = { &P_EVENT_AppendEntriesRequest, &P_EVENT_VoteRequest };
PRT_EVENTSETDECL P_EVENTSET_Init_DEFERS_2 =
{
    2U,
    P_Init_DEFERS_INNER_2,
    NULL
};

PRT_EVENTDECL* P_Init_TRANS_INNER_2[] = { &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader };
PRT_EVENTSETDECL P_EVENTSET_Init_TRANS_2 =
{
    2U,
    P_Init_TRANS_INNER_2,
    NULL
};

PRT_EVENTDECL* P_Init_DOS_INNER_2[] = { &P_EVENT_SConfigureEvent };
PRT_EVENTSETDECL P_EVENTSET_Init_DOS_2 =
{
    1U,
    P_Init_DOS_INNER_2,
    NULL
};

PRT_TRANSDECL P_TRANS_5[] =
{
    { 0, &P_EVENT_BecomeFollower, 1, &_P_NO_OP },
    { 0, &P_EVENT_BecomeLeader, 2, &_P_NO_OP }
};

PRT_DODECL P_DOS_5[] =
{
    { 0, &P_EVENT_SConfigureEvent, &P_FUNCTION_Anon_19 }
};

#define P_STATE_Server_Init \
{ \
    "Server.Init", \
    2U, \
    1U, \
    &P_EVENTSET_Init_DEFERS_2, \
    &P_EVENTSET_Init_TRANS_2, \
    &P_EVENTSET_Init_DOS_2, \
    P_TRANS_5, \
    P_DOS_5, \
    &P_FUNCTION_Anon_18, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Follower_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Follower_DEFERS =
{
    0U,
    P_Follower_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Follower_TRANS_INNER[] = { &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower };
PRT_EVENTSETDECL P_EVENTSET_Follower_TRANS =
{
    2U,
    P_Follower_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Follower_DOS_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_RemoveServer, &P_EVENT_Request, &P_EVENT_SConfigureEvent, &P_EVENT_ShutDown, &P_EVENT_TickEvent, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse };
PRT_EVENTSETDECL P_EVENTSET_Follower_DOS =
{
    10U,
    P_Follower_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_6[] =
{
    { 1, &P_EVENT_BecomeFollower, 1, &_P_NO_OP },
    { 1, &P_EVENT_BecomeCandidate, 3, &_P_NO_OP }
};

PRT_DODECL P_DOS_6[] =
{
    { 1, &P_EVENT_Request, &P_FUNCTION_Anon_21 },
    { 1, &P_EVENT_VoteRequest, &P_FUNCTION_Anon_22 },
    { 1, &P_EVENT_VoteResponse, &P_FUNCTION_Anon_23 },
    { 1, &P_EVENT_AppendEntriesRequest, &P_FUNCTION_Anon_24 },
    { 1, &P_EVENT_AppendEntriesResponse, &P_FUNCTION_Anon_25 },
    { 1, &P_EVENT_TickEvent, &P_FUNCTION_Anon_26 },
    { 1, &P_EVENT_ShutDown, &P_FUNCTION_Anon_27 },
    { 1, &P_EVENT_AddServer, &P_FUNCTION_Anon_28 },
    { 1, &P_EVENT_RemoveServer, &P_FUNCTION_Anon_29 },
    { 1, &P_EVENT_SConfigureEvent, NULL }
};

#define P_STATE_Server_Follower \
{ \
    "Server.Follower", \
    2U, \
    10U, \
    &P_EVENTSET_Follower_DEFERS, \
    &P_EVENTSET_Follower_TRANS, \
    &P_EVENTSET_Follower_DOS, \
    P_TRANS_6, \
    P_DOS_6, \
    &P_FUNCTION_Anon_20, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Candidate_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Candidate_DEFERS =
{
    0U,
    P_Candidate_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Candidate_TRANS_INNER[] = { &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader };
PRT_EVENTSETDECL P_EVENTSET_Candidate_TRANS =
{
    3U,
    P_Candidate_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Candidate_DOS_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_RemoveServer, &P_EVENT_Request, &P_EVENT_SConfigureEvent, &P_EVENT_ShutDown, &P_EVENT_TickEvent, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse };
PRT_EVENTSETDECL P_EVENTSET_Candidate_DOS =
{
    10U,
    P_Candidate_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_7[] =
{
    { 3, &P_EVENT_BecomeLeader, 2, &_P_NO_OP },
    { 3, &P_EVENT_BecomeFollower, 1, &_P_NO_OP },
    { 3, &P_EVENT_BecomeCandidate, 3, &_P_NO_OP }
};

PRT_DODECL P_DOS_7[] =
{
    { 3, &P_EVENT_Request, &P_FUNCTION_Anon_31 },
    { 3, &P_EVENT_VoteRequest, &P_FUNCTION_Anon_32 },
    { 3, &P_EVENT_VoteResponse, &P_FUNCTION_Anon_33 },
    { 3, &P_EVENT_AppendEntriesRequest, &P_FUNCTION_Anon_34 },
    { 3, &P_EVENT_AppendEntriesResponse, &P_FUNCTION_Anon_35 },
    { 3, &P_EVENT_TickEvent, &P_FUNCTION_Anon_36 },
    { 3, &P_EVENT_AddServer, &P_FUNCTION_Anon_37 },
    { 3, &P_EVENT_RemoveServer, &P_FUNCTION_Anon_38 },
    { 3, &P_EVENT_ShutDown, &P_FUNCTION_ShuttingDown_1 },
    { 3, &P_EVENT_SConfigureEvent, NULL }
};

#define P_STATE_Server_Candidate \
{ \
    "Server.Candidate", \
    3U, \
    10U, \
    &P_EVENTSET_Candidate_DEFERS, \
    &P_EVENTSET_Candidate_TRANS, \
    &P_EVENTSET_Candidate_DOS, \
    P_TRANS_7, \
    P_DOS_7, \
    &P_FUNCTION_Anon_30, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Leader_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Leader_DEFERS =
{
    0U,
    P_Leader_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Leader_TRANS_INNER[] = { &P_EVENT_BecomeFollower };
PRT_EVENTSETDECL P_EVENTSET_Leader_TRANS =
{
    1U,
    P_Leader_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Leader_DOS_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_RemoveServer, &P_EVENT_Request, &P_EVENT_SConfigureEvent, &P_EVENT_ShutDown, &P_EVENT_TickEvent, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse };
PRT_EVENTSETDECL P_EVENTSET_Leader_DOS =
{
    10U,
    P_Leader_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_8[] =
{
    { 2, &P_EVENT_BecomeFollower, 1, &_P_NO_OP }
};

PRT_DODECL P_DOS_8[] =
{
    { 2, &P_EVENT_Request, &P_FUNCTION_Anon_40 },
    { 2, &P_EVENT_VoteRequest, &P_FUNCTION_Anon_41 },
    { 2, &P_EVENT_VoteResponse, &P_FUNCTION_Anon_42 },
    { 2, &P_EVENT_AppendEntriesRequest, &P_FUNCTION_Anon_43 },
    { 2, &P_EVENT_AppendEntriesResponse, &P_FUNCTION_Anon_44 },
    { 2, &P_EVENT_AddServer, &P_FUNCTION_Anon_45 },
    { 2, &P_EVENT_RemoveServer, &P_FUNCTION_Anon_46 },
    { 2, &P_EVENT_ShutDown, &P_FUNCTION_ShuttingDown_1 },
    { 2, &P_EVENT_TickEvent, &P_FUNCTION_Anon_47 },
    { 2, &P_EVENT_SConfigureEvent, NULL }
};

#define P_STATE_Server_Leader \
{ \
    "Server.Leader", \
    1U, \
    10U, \
    &P_EVENTSET_Leader_DEFERS, \
    &P_EVENTSET_Leader_TRANS, \
    &P_EVENTSET_Leader_DOS, \
    P_TRANS_8, \
    P_DOS_8, \
    &P_FUNCTION_Anon_39, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_Server_STATES[] = { P_STATE_Server_Init, P_STATE_Server_Follower, P_STATE_Server_Leader, P_STATE_Server_Candidate };

PRT_VALUE* P_Anon_IMPL_18(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_24 = NULL;
    PRT_VALUE* PTMP_tmp1_23 = NULL;
    PRT_VALUE* PTMP_tmp2_17 = NULL;
    PRT_VALUE* PTMP_tmp3_13 = NULL;
    PRT_VALUE* PTMP_tmp4_9 = NULL;
    PRT_VALUE* PTMP_tmp5_9 = NULL;
    PRT_VALUE* PTMP_tmp6_9 = NULL;
    PRT_VALUE* PTMP_tmp7_9 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_19 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_BOOLEAN_12 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_240 = &(p_this->varValues[3]);
    PrtFreeValue(*P_LVALUE_240);
    *P_LVALUE_240 = PrtCloneValue((&P_LIT_INT32_19));
    
    PRT_VALUE** P_LVALUE_241 = &(PTMP_tmp0_24);
    PrtFreeValue(*P_LVALUE_241);
    *P_LVALUE_241 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    
    {
        PRT_VALUE** P_LVALUE_242 = &(p_this->varValues[2]);
        PrtFreeValue(*P_LVALUE_242);
        *P_LVALUE_242 = PTMP_tmp0_24;
        PTMP_tmp0_24 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_243 = &(PTMP_tmp1_23);
    PrtFreeValue(*P_LVALUE_243);
    *P_LVALUE_243 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    
    {
        PRT_VALUE** P_LVALUE_244 = &(p_this->varValues[4]);
        PrtFreeValue(*P_LVALUE_244);
        *P_LVALUE_244 = PTMP_tmp1_23;
        PTMP_tmp1_23 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_245 = &(PTMP_tmp2_17);
    PrtFreeValue(*P_LVALUE_245);
    *P_LVALUE_245 = PrtMkDefaultValue(&P_GEND_TYPE_ST2iSm);
    
    {
        PRT_VALUE** P_LVALUE_246 = &(p_this->varValues[6]);
        PrtFreeValue(*P_LVALUE_246);
        *P_LVALUE_246 = PTMP_tmp2_17;
        PTMP_tmp2_17 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_247 = &(PTMP_tmp3_13);
    PrtFreeValue(*P_LVALUE_247);
    *P_LVALUE_247 = PrtMkDefaultValue(&P_GEND_TYPE_ST3irr);
    
    {
        PRT_VALUE** P_LVALUE_248 = &(p_this->varValues[5]);
        PrtFreeValue(*P_LVALUE_248);
        *P_LVALUE_248 = PTMP_tmp3_13;
        PTMP_tmp3_13 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_249 = &(PTMP_tmp4_9);
    PrtFreeValue(*P_LVALUE_249);
    *P_LVALUE_249 = PrtMkDefaultValue(&P_GEND_TYPE_T2ii);
    
    {
        PRT_VALUE** P_LVALUE_250 = &(p_this->varValues[8]);
        PrtFreeValue(*P_LVALUE_250);
        *P_LVALUE_250 = PTMP_tmp4_9;
        PTMP_tmp4_9 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_251 = &(PTMP_tmp5_9);
    PrtFreeValue(*P_LVALUE_251);
    *P_LVALUE_251 = PrtMkDefaultValue(&P_GEND_TYPE_MKmVT2ii);
    
    {
        PRT_VALUE** P_LVALUE_252 = &(p_this->varValues[9]);
        PrtFreeValue(*P_LVALUE_252);
        *P_LVALUE_252 = PTMP_tmp5_9;
        PTMP_tmp5_9 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_253 = &(PTMP_tmp6_9);
    PrtFreeValue(*P_LVALUE_253);
    *P_LVALUE_253 = PrtMkDefaultValue(&P_GEND_TYPE_MKmVT2ii);
    
    {
        PRT_VALUE** P_LVALUE_254 = &(p_this->varValues[10]);
        PrtFreeValue(*P_LVALUE_254);
        *P_LVALUE_254 = PTMP_tmp6_9;
        PTMP_tmp6_9 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_255 = &(PTMP_tmp7_9);
    PrtFreeValue(*P_LVALUE_255);
    *P_LVALUE_255 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    
    {
        PRT_VALUE** P_LVALUE_256 = &(p_this->varValues[13]);
        PrtFreeValue(*P_LVALUE_256);
        *P_LVALUE_256 = PTMP_tmp7_9;
        PTMP_tmp7_9 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_257 = &(p_this->varValues[14]);
    PrtFreeValue(*P_LVALUE_257);
    *P_LVALUE_257 = PrtCloneValue((&P_LIT_INT32_19));
    
    PRT_VALUE** P_LVALUE_258 = &(p_this->varValues[17]);
    PrtFreeValue(*P_LVALUE_258);
    *P_LVALUE_258 = PrtCloneValue((&P_LIT_BOOLEAN_12));
    
p_return_25: ;
    PrtFreeValue(PTMP_tmp0_24); PTMP_tmp0_24 = NULL;
    PrtFreeValue(PTMP_tmp1_23); PTMP_tmp1_23 = NULL;
    PrtFreeValue(PTMP_tmp2_17); PTMP_tmp2_17 = NULL;
    PrtFreeValue(PTMP_tmp3_13); PTMP_tmp3_13 = NULL;
    PrtFreeValue(PTMP_tmp4_9); PTMP_tmp4_9 = NULL;
    PrtFreeValue(PTMP_tmp5_9); PTMP_tmp5_9 = NULL;
    PrtFreeValue(PTMP_tmp6_9); PTMP_tmp6_9 = NULL;
    PrtFreeValue(PTMP_tmp7_9); PTMP_tmp7_9 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_18 =
{
    NULL,
    &P_Anon_IMPL_18,
    NULL
};


PRT_VALUE* P_Anon_IMPL_19(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_9 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_25 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_259 = &(PTMP_tmp0_25);
    PrtFreeValue(*P_LVALUE_259);
    *P_LVALUE_259 = PrtCloneValue(*P_VAR_payload_9);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_25);
    PrtFreeValue(P_configServer_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_25);
    PTMP_tmp0_25 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_26;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_26;
    }
    
p_return_26: ;
    PrtFreeValue(PTMP_tmp0_25); PTMP_tmp0_25 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_19 =
{
    NULL,
    &P_Anon_IMPL_19,
    &P_GEND_TYPE_T2Smm
};


PRT_VALUE* P_configServer_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_10 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_26 = NULL;
    PRT_VALUE* PTMP_tmp1_24 = NULL;
    PRT_VALUE* PTMP_tmp2_18 = NULL;
    PRT_VALUE* PTMP_tmp3_14 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_20 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE** P_LVALUE_260 = &(PTMP_tmp0_26);
    PrtFreeValue(*P_LVALUE_260);
    *P_LVALUE_260 = PrtTupleGet(*P_VAR_payload_10, 0);
    
    {
        PRT_VALUE** P_LVALUE_261 = &(p_this->varValues[1]);
        PrtFreeValue(*P_LVALUE_261);
        *P_LVALUE_261 = PTMP_tmp0_26;
        PTMP_tmp0_26 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_262 = &(PTMP_tmp1_24);
    PrtFreeValue(*P_LVALUE_262);
    *P_LVALUE_262 = PrtTupleGet(*P_VAR_payload_10, 1);
    
    {
        PRT_VALUE** P_LVALUE_263 = &(p_this->varValues[0]);
        PrtFreeValue(*P_LVALUE_263);
        *P_LVALUE_263 = PTMP_tmp1_24;
        PTMP_tmp1_24 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_264 = &(p_this->varValues[16]);
    PrtFreeValue(*P_LVALUE_264);
    *P_LVALUE_264 = PrtCloneValue((&P_LIT_INT32_20));
    
    PRT_VALUE** P_LVALUE_265 = &(PTMP_tmp2_18);
    PrtFreeValue(*P_LVALUE_265);
    *P_LVALUE_265 = ((_P_GEN_funval = P_getMaxTickValue_IMPL(context, _P_GEN_funargs)), (_P_GEN_funval));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_27;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_27;
    }
    
    {
        PRT_VALUE** P_LVALUE_266 = &(p_this->varValues[15]);
        PrtFreeValue(*P_LVALUE_266);
        *P_LVALUE_266 = PTMP_tmp2_18;
        PTMP_tmp2_18 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_267 = &(PTMP_tmp3_14);
    PrtFreeValue(*P_LVALUE_267);
    *P_LVALUE_267 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
    
    PrtRaise(p_this, PTMP_tmp3_14, 0);
    *(&(PTMP_tmp3_14)) = NULL;
    goto p_return_27;
    
p_return_27: ;
    PrtFreeValue(PTMP_tmp0_26); PTMP_tmp0_26 = NULL;
    PrtFreeValue(PTMP_tmp1_24); PTMP_tmp1_24 = NULL;
    PrtFreeValue(PTMP_tmp2_18); PTMP_tmp2_18 = NULL;
    PrtFreeValue(PTMP_tmp3_14); PTMP_tmp3_14 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_configServer =
{
    "configServer",
    &P_configServer_IMPL,
    NULL
};


PRT_VALUE* P_getMaxTickValue_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_i_2 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_27 = NULL;
    PRT_VALUE* PTMP_tmp1_25 = NULL;
    PRT_VALUE* PTMP_tmp2_19 = NULL;
    PRT_VALUE* PTMP_tmp3_15 = NULL;
    PRT_VALUE* PTMP_tmp4_10 = NULL;
    PRT_VALUE* PTMP_tmp5_10 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_21 = { PRT_VALUE_KIND_INT, { .nt = 350 } };
    PRT_VALUE P_LIT_INT32_22 = { PRT_VALUE_KIND_INT, { .nt = 250 } };
    PRT_VALUE P_LIT_INT32_23 = { PRT_VALUE_KIND_INT, { .nt = 5 } };
    PRT_VALUE P_LIT_BOOLEAN_13 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_268 = &(P_VAR_i_2);
    PrtFreeValue(*P_LVALUE_268);
    *P_LVALUE_268 = PrtCloneValue((&P_LIT_INT32_21));
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_13)))
    {
        PRT_VALUE** P_LVALUE_269 = &(PTMP_tmp0_27);
        PrtFreeValue(*P_LVALUE_269);
        *P_LVALUE_269 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_i_2) > PrtPrimGetInt((&P_LIT_INT32_22)));
        
        PRT_VALUE** P_LVALUE_270 = &(PTMP_tmp1_25);
        PrtFreeValue(*P_LVALUE_270);
        *P_LVALUE_270 = PrtCloneValue(PTMP_tmp0_27);
        
        if (PrtPrimGetBool(PTMP_tmp1_25))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_271 = &(PTMP_tmp2_19);
        PrtFreeValue(*P_LVALUE_271);
        *P_LVALUE_271 = PrtMkIntValue(PrtPrimGetInt(P_VAR_i_2) - PrtPrimGetInt((&P_LIT_INT32_23)));
        
        {
            PRT_VALUE** P_LVALUE_272 = &(P_VAR_i_2);
            PrtFreeValue(*P_LVALUE_272);
            *P_LVALUE_272 = PTMP_tmp2_19;
            PTMP_tmp2_19 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_273 = &(PTMP_tmp3_15);
        PrtFreeValue(*P_LVALUE_273);
        *P_LVALUE_273 = (PrtMkNondetBoolValue());
        
        if (PrtPrimGetBool(PTMP_tmp3_15))
        {
            PRT_VALUE** P_LVALUE_274 = &(PTMP_tmp4_10);
            PrtFreeValue(*P_LVALUE_274);
            *P_LVALUE_274 = (PrtMkNondetBoolValue());
            
            if (PrtPrimGetBool(PTMP_tmp4_10))
            {
                PRT_VALUE** P_LVALUE_275 = &(PTMP_tmp5_10);
                PrtFreeValue(*P_LVALUE_275);
                *P_LVALUE_275 = (PrtMkNondetBoolValue());
                
                if (PrtPrimGetBool(PTMP_tmp5_10))
                {
                    PrtFormatPrintf("MaxTicks ", 2, P_VAR_i_2, (p_this->id), 2, 0, " for ", 1, "");
                    
                    PrtFreeValue(_P_GEN_retval);
                    _P_GEN_retval = PrtCloneValue(P_VAR_i_2);
                    goto p_return_28;
                    
                }
                
                else
                {
                }
                
                
            }
            
            else
            {
            }
            
            
        }
        
        else
        {
        }
        
        
    }
    
    
    PrtFormatPrintf("MaxTicks ", 2, P_VAR_i_2, (p_this->id), 2, 0, " for ", 1, "");
    
    PrtFreeValue(_P_GEN_retval);
    _P_GEN_retval = PrtCloneValue(P_VAR_i_2);
    goto p_return_28;
    
p_return_28: ;
    PrtFreeValue(P_VAR_i_2); P_VAR_i_2 = NULL;
    PrtFreeValue(PTMP_tmp0_27); PTMP_tmp0_27 = NULL;
    PrtFreeValue(PTMP_tmp1_25); PTMP_tmp1_25 = NULL;
    PrtFreeValue(PTMP_tmp2_19); PTMP_tmp2_19 = NULL;
    PrtFreeValue(PTMP_tmp3_15); PTMP_tmp3_15 = NULL;
    PrtFreeValue(PTMP_tmp4_10); PTMP_tmp4_10 = NULL;
    PrtFreeValue(PTMP_tmp5_10); PTMP_tmp5_10 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_getMaxTickValue =
{
    "getMaxTickValue",
    &P_getMaxTickValue_IMPL,
    NULL
};


PRT_VALUE* P_Anon_IMPL_20(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_28 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_24 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PrtFormatPrintf("[Follower] ", 1, (p_this->id), 1, 0, " onEntry");
    
    PRT_VALUE** P_LVALUE_276 = &(PTMP_tmp0_28);
    PrtFreeValue(*P_LVALUE_276);
    *P_LVALUE_276 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    
    {
        PRT_VALUE** P_LVALUE_277 = &(p_this->varValues[2]);
        PrtFreeValue(*P_LVALUE_277);
        *P_LVALUE_277 = PTMP_tmp0_28;
        PTMP_tmp0_28 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_278 = &(p_this->varValues[11]);
    PrtFreeValue(*P_LVALUE_278);
    *P_LVALUE_278 = PrtCloneValue((&P_LIT_INT32_24));
    
    PRT_VALUE** P_LVALUE_279 = &(p_this->varValues[16]);
    PrtFreeValue(*P_LVALUE_279);
    *P_LVALUE_279 = PrtCloneValue((&P_LIT_INT32_24));
    
p_return_29: ;
    PrtFreeValue(PTMP_tmp0_28); PTMP_tmp0_28 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_20 =
{
    NULL,
    &P_Anon_IMPL_20,
    NULL
};


PRT_VALUE* P_Anon_IMPL_21(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_11 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_29 = NULL;
    PRT_VALUE* PTMP_tmp1_26 = NULL;
    PRT_VALUE* PTMP_tmp2_20 = NULL;
    PRT_VALUE* PTMP_tmp3_16 = NULL;
    PRT_VALUE* PTMP_tmp4_11 = NULL;
    PRT_VALUE* PTMP_tmp5_11 = NULL;
    PRT_VALUE* PTMP_tmp6_10 = NULL;
    PRT_VALUE* PTMP_tmp7_10 = NULL;
    PRT_VALUE* PTMP_tmp8_9 = NULL;
    PRT_VALUE* PTMP_tmp9_7 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_280 = &(PTMP_tmp0_29);
    PrtFreeValue(*P_LVALUE_280);
    *P_LVALUE_280 = PrtMkBoolValue(!PrtIsEqualValue(p_this->varValues[2], (&_P_GEN_null)));
    
    if (PrtPrimGetBool(PTMP_tmp0_29))
    {
        PrtFormatPrintf("[Follower | Request] ", 2, (p_this->id), p_this->varValues[2], 2, 0, " sends request to Leader ", 1, "");
        
        PRT_VALUE** P_LVALUE_281 = &(PTMP_tmp1_26);
        PrtFreeValue(*P_LVALUE_281);
        *P_LVALUE_281 = PrtCloneValue(p_this->varValues[2]);
        
        PRT_VALUE** P_LVALUE_282 = &(PTMP_tmp2_20);
        PrtFreeValue(*P_LVALUE_282);
        *P_LVALUE_282 = PrtCloneValue((&P_EVENT_Request.value));
        
        PRT_VALUE** P_LVALUE_283 = &(PTMP_tmp3_16);
        PrtFreeValue(*P_LVALUE_283);
        *P_LVALUE_283 = PrtTupleGet(*P_VAR_payload_11, 0);
        
        PRT_VALUE** P_LVALUE_284 = &(PTMP_tmp4_11);
        PrtFreeValue(*P_LVALUE_284);
        *P_LVALUE_284 = PrtTupleGet(*P_VAR_payload_11, 1);
        
        PRT_VALUE** P_LVALUE_285 = &(PTMP_tmp5_11);
        PrtFreeValue(*P_LVALUE_285);
        *P_LVALUE_285 = PrtTupleGet(*P_VAR_payload_11, 2);
        
        PRT_VALUE** P_LVALUE_286 = &(PTMP_tmp6_10);
        PrtFreeValue(*P_LVALUE_286);
        *P_LVALUE_286 = (PrtMkTuple(&P_GEND_TYPE_T3mrr, &(PTMP_tmp3_16), &(PTMP_tmp4_11), &(PTMP_tmp5_11)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_26), PTMP_tmp2_20, 1, &(PTMP_tmp6_10));
        *(&(PTMP_tmp2_20)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_30;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_30;
        }
        
    }
    
    else
    {
        PrtFormatPrintf("[Follower | Request] ", 1, (p_this->id), 1, 0, " no Leader, redirect to ClusterManager.");
        
        PRT_VALUE** P_LVALUE_287 = &(PTMP_tmp7_10);
        PrtFreeValue(*P_LVALUE_287);
        *P_LVALUE_287 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_288 = &(PTMP_tmp8_9);
        PrtFreeValue(*P_LVALUE_288);
        *P_LVALUE_288 = PrtCloneValue((&P_EVENT_RedirectRequest.value));
        
        PRT_VALUE** P_LVALUE_289 = &(PTMP_tmp9_7);
        PrtFreeValue(*P_LVALUE_289);
        *P_LVALUE_289 = PrtCloneValue(*P_VAR_payload_11);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp7_10), PTMP_tmp8_9, 1, &(PTMP_tmp9_7));
        *(&(PTMP_tmp8_9)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_30;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_30;
        }
        
    }
    
    
p_return_30: ;
    PrtFreeValue(PTMP_tmp0_29); PTMP_tmp0_29 = NULL;
    PrtFreeValue(PTMP_tmp1_26); PTMP_tmp1_26 = NULL;
    PrtFreeValue(PTMP_tmp2_20); PTMP_tmp2_20 = NULL;
    PrtFreeValue(PTMP_tmp3_16); PTMP_tmp3_16 = NULL;
    PrtFreeValue(PTMP_tmp4_11); PTMP_tmp4_11 = NULL;
    PrtFreeValue(PTMP_tmp5_11); PTMP_tmp5_11 = NULL;
    PrtFreeValue(PTMP_tmp6_10); PTMP_tmp6_10 = NULL;
    PrtFreeValue(PTMP_tmp7_10); PTMP_tmp7_10 = NULL;
    PrtFreeValue(PTMP_tmp8_9); PTMP_tmp8_9 = NULL;
    PrtFreeValue(PTMP_tmp9_7); PTMP_tmp9_7 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_21 =
{
    NULL,
    &P_Anon_IMPL_21,
    &P_GEND_TYPE_T3mrr
};


PRT_VALUE* P_Anon_IMPL_22(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_12 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_30 = NULL;
    PRT_VALUE* PTMP_tmp1_27 = NULL;
    PRT_VALUE* PTMP_tmp2_21 = NULL;
    PRT_VALUE* PTMP_tmp3_17 = NULL;
    PRT_VALUE* PTMP_tmp4_12 = NULL;
    PRT_VALUE* PTMP_tmp5_12 = NULL;
    PRT_VALUE* PTMP_tmp6_11 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_290 = &(PTMP_tmp0_30);
    PrtFreeValue(*P_LVALUE_290);
    *P_LVALUE_290 = PrtMkBoolValue(PrtIsEqualValue(p_this->varValues[2], (&_P_GEN_null)));
    
    if (PrtPrimGetBool(PTMP_tmp0_30))
    {
        PRT_VALUE** P_LVALUE_291 = &(PTMP_tmp1_27);
        PrtFreeValue(*P_LVALUE_291);
        *P_LVALUE_291 = PrtTupleGet(*P_VAR_payload_12, 0);
        
        PrtFormatPrintf("[Follower | VoteRequest] Server ", 3, (p_this->id), PTMP_tmp1_27, p_this->varValues[3], 3, 0, " | Payload Term ", 1, " | Current Term ", 2, "");
        
        PRT_VALUE** P_LVALUE_292 = &(PTMP_tmp2_21);
        PrtFreeValue(*P_LVALUE_292);
        *P_LVALUE_292 = PrtTupleGet(*P_VAR_payload_12, 0);
        
        PRT_VALUE** P_LVALUE_293 = &(PTMP_tmp3_17);
        PrtFreeValue(*P_LVALUE_293);
        *P_LVALUE_293 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp2_21) > PrtPrimGetInt(p_this->varValues[3]));
        
        if (PrtPrimGetBool(PTMP_tmp3_17))
        {
            PRT_VALUE** P_LVALUE_294 = &(PTMP_tmp4_12);
            PrtFreeValue(*P_LVALUE_294);
            *P_LVALUE_294 = PrtTupleGet(*P_VAR_payload_12, 0);
            
            {
                PRT_VALUE** P_LVALUE_295 = &(p_this->varValues[3]);
                PrtFreeValue(*P_LVALUE_295);
                *P_LVALUE_295 = PTMP_tmp4_12;
                PTMP_tmp4_12 = NULL;
            }
            
            PRT_VALUE** P_LVALUE_296 = &(PTMP_tmp5_12);
            PrtFreeValue(*P_LVALUE_296);
            *P_LVALUE_296 = PrtMkDefaultValue(&P_GEND_TYPE_m);
            
            {
                PRT_VALUE** P_LVALUE_297 = &(p_this->varValues[4]);
                PrtFreeValue(*P_LVALUE_297);
                *P_LVALUE_297 = PTMP_tmp5_12;
                PTMP_tmp5_12 = NULL;
            }
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_298 = &(PTMP_tmp6_11);
        PrtFreeValue(*P_LVALUE_298);
        *P_LVALUE_298 = PrtCloneValue(*P_VAR_payload_12);
        
        _P_GEN_funargs[0] = &(PTMP_tmp6_11);
        PrtFreeValue(P_Vote_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp6_11);
        PTMP_tmp6_11 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_31;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_31;
        }
        
    }
    
    else
    {
    }
    
    
p_return_31: ;
    PrtFreeValue(PTMP_tmp0_30); PTMP_tmp0_30 = NULL;
    PrtFreeValue(PTMP_tmp1_27); PTMP_tmp1_27 = NULL;
    PrtFreeValue(PTMP_tmp2_21); PTMP_tmp2_21 = NULL;
    PrtFreeValue(PTMP_tmp3_17); PTMP_tmp3_17 = NULL;
    PrtFreeValue(PTMP_tmp4_12); PTMP_tmp4_12 = NULL;
    PrtFreeValue(PTMP_tmp5_12); PTMP_tmp5_12 = NULL;
    PrtFreeValue(PTMP_tmp6_11); PTMP_tmp6_11 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_22 =
{
    NULL,
    &P_Anon_IMPL_22,
    &P_GEND_TYPE_T4imT2iiT2ii
};


PRT_VALUE* P_Anon_IMPL_23(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_1 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_31 = NULL;
    PRT_VALUE* PTMP_tmp1_28 = NULL;
    PRT_VALUE* PTMP_tmp2_22 = NULL;
    PRT_VALUE* PTMP_tmp3_18 = NULL;
    PRT_VALUE* PTMP_tmp4_13 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_299 = &(PTMP_tmp0_31);
    PrtFreeValue(*P_LVALUE_299);
    *P_LVALUE_299 = PrtTupleGet(*P_VAR_request_1, 0);
    
    PrtFormatPrintf("[Follower | VoteResponse] Server ", 3, (p_this->id), PTMP_tmp0_31, p_this->varValues[3], 3, 0, " | Payload Term ", 1, " | Current Term ", 2, "");
    
    PRT_VALUE** P_LVALUE_300 = &(PTMP_tmp1_28);
    PrtFreeValue(*P_LVALUE_300);
    *P_LVALUE_300 = PrtTupleGet(*P_VAR_request_1, 0);
    
    PRT_VALUE** P_LVALUE_301 = &(PTMP_tmp2_22);
    PrtFreeValue(*P_LVALUE_301);
    *P_LVALUE_301 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp1_28) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp2_22))
    {
        PRT_VALUE** P_LVALUE_302 = &(PTMP_tmp3_18);
        PrtFreeValue(*P_LVALUE_302);
        *P_LVALUE_302 = PrtTupleGet(*P_VAR_request_1, 0);
        
        {
            PRT_VALUE** P_LVALUE_303 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_303);
            *P_LVALUE_303 = PTMP_tmp3_18;
            PTMP_tmp3_18 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_304 = &(PTMP_tmp4_13);
        PrtFreeValue(*P_LVALUE_304);
        *P_LVALUE_304 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_305 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_305);
            *P_LVALUE_305 = PTMP_tmp4_13;
            PTMP_tmp4_13 = NULL;
        }
        
    }
    
    else
    {
    }
    
    
p_return_32: ;
    PrtFreeValue(PTMP_tmp0_31); PTMP_tmp0_31 = NULL;
    PrtFreeValue(PTMP_tmp1_28); PTMP_tmp1_28 = NULL;
    PrtFreeValue(PTMP_tmp2_22); PTMP_tmp2_22 = NULL;
    PrtFreeValue(PTMP_tmp3_18); PTMP_tmp3_18 = NULL;
    PrtFreeValue(PTMP_tmp4_13); PTMP_tmp4_13 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_23 =
{
    NULL,
    &P_Anon_IMPL_23,
    &P_GEND_TYPE_T2ib
};


PRT_VALUE* P_Anon_IMPL_24(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_2 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_32 = NULL;
    PRT_VALUE* PTMP_tmp1_29 = NULL;
    PRT_VALUE* PTMP_tmp2_23 = NULL;
    PRT_VALUE* PTMP_tmp3_19 = NULL;
    PRT_VALUE* PTMP_tmp4_14 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFormatPrintf("[Follower | AppendEntriesRequest] Server ", 1, (p_this->id), 1, 0, "");
    
    PRT_VALUE** P_LVALUE_306 = &(PTMP_tmp0_32);
    PrtFreeValue(*P_LVALUE_306);
    *P_LVALUE_306 = PrtTupleGet(*P_VAR_request_2, 0);
    
    PRT_VALUE** P_LVALUE_307 = &(PTMP_tmp1_29);
    PrtFreeValue(*P_LVALUE_307);
    *P_LVALUE_307 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_32) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp1_29))
    {
        PRT_VALUE** P_LVALUE_308 = &(PTMP_tmp2_23);
        PrtFreeValue(*P_LVALUE_308);
        *P_LVALUE_308 = PrtTupleGet(*P_VAR_request_2, 0);
        
        {
            PRT_VALUE** P_LVALUE_309 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_309);
            *P_LVALUE_309 = PTMP_tmp2_23;
            PTMP_tmp2_23 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_310 = &(PTMP_tmp3_19);
        PrtFreeValue(*P_LVALUE_310);
        *P_LVALUE_310 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_311 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_311);
            *P_LVALUE_311 = PTMP_tmp3_19;
            PTMP_tmp3_19 = NULL;
        }
        
    }
    
    else
    {
    }
    
    
    PRT_VALUE** P_LVALUE_312 = &(PTMP_tmp4_14);
    PrtFreeValue(*P_LVALUE_312);
    *P_LVALUE_312 = PrtCloneValue(*P_VAR_request_2);
    
    _P_GEN_funargs[0] = &(PTMP_tmp4_14);
    PrtFreeValue(P_AppendEntries_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp4_14);
    PTMP_tmp4_14 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_33;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_33;
    }
    
p_return_33: ;
    PrtFreeValue(PTMP_tmp0_32); PTMP_tmp0_32 = NULL;
    PrtFreeValue(PTMP_tmp1_29); PTMP_tmp1_29 = NULL;
    PrtFreeValue(PTMP_tmp2_23); PTMP_tmp2_23 = NULL;
    PrtFreeValue(PTMP_tmp3_19); PTMP_tmp3_19 = NULL;
    PrtFreeValue(PTMP_tmp4_14); PTMP_tmp4_14 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_24 =
{
    NULL,
    &P_Anon_IMPL_24,
    &P_GEND_TYPE_T8imT2iiT2iiST3irrST2iSmT2iim
};


PRT_VALUE* P_Anon_IMPL_25(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_3 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_33 = NULL;
    PRT_VALUE* PTMP_tmp1_30 = NULL;
    PRT_VALUE* PTMP_tmp2_24 = NULL;
    PRT_VALUE* PTMP_tmp3_20 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFormatPrintf("[Follower | AppendEntriesResponse] Server ", 1, (p_this->id), 1, 0, "");
    
    PRT_VALUE** P_LVALUE_313 = &(PTMP_tmp0_33);
    PrtFreeValue(*P_LVALUE_313);
    *P_LVALUE_313 = PrtTupleGet(*P_VAR_request_3, 0);
    
    PRT_VALUE** P_LVALUE_314 = &(PTMP_tmp1_30);
    PrtFreeValue(*P_LVALUE_314);
    *P_LVALUE_314 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_33) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp1_30))
    {
        PRT_VALUE** P_LVALUE_315 = &(PTMP_tmp2_24);
        PrtFreeValue(*P_LVALUE_315);
        *P_LVALUE_315 = PrtTupleGet(*P_VAR_request_3, 0);
        
        {
            PRT_VALUE** P_LVALUE_316 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_316);
            *P_LVALUE_316 = PTMP_tmp2_24;
            PTMP_tmp2_24 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_317 = &(PTMP_tmp3_20);
        PrtFreeValue(*P_LVALUE_317);
        *P_LVALUE_317 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_318 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_318);
            *P_LVALUE_318 = PTMP_tmp3_20;
            PTMP_tmp3_20 = NULL;
        }
        
    }
    
    else
    {
    }
    
    
p_return_34: ;
    PrtFreeValue(PTMP_tmp0_33); PTMP_tmp0_33 = NULL;
    PrtFreeValue(PTMP_tmp1_30); PTMP_tmp1_30 = NULL;
    PrtFreeValue(PTMP_tmp2_24); PTMP_tmp2_24 = NULL;
    PrtFreeValue(PTMP_tmp3_20); PTMP_tmp3_20 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_25 =
{
    NULL,
    &P_Anon_IMPL_25,
    &P_GEND_TYPE_T6ibbbmm
};


PRT_VALUE* P_Anon_IMPL_26(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_34 = NULL;
    PRT_VALUE* PTMP_tmp1_31 = NULL;
    PRT_VALUE* PTMP_tmp2_25 = NULL;
    PRT_VALUE* PTMP_tmp3_21 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_25 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE** P_LVALUE_319 = &(PTMP_tmp0_34);
    PrtFreeValue(*P_LVALUE_319);
    *P_LVALUE_319 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[16]) + PrtPrimGetInt((&P_LIT_INT32_25)));
    
    {
        PRT_VALUE** P_LVALUE_320 = &(p_this->varValues[16]);
        PrtFreeValue(*P_LVALUE_320);
        *P_LVALUE_320 = PTMP_tmp0_34;
        PTMP_tmp0_34 = NULL;
    }
    
    PrtFormatPrintf("[Follower] ", 3, (p_this->id), p_this->varValues[16], p_this->varValues[15], 3, 0, " TickCounter ", 1, ", MaxTicks ", 2, "");
    
    PRT_VALUE** P_LVALUE_321 = &(PTMP_tmp1_31);
    PrtFreeValue(*P_LVALUE_321);
    *P_LVALUE_321 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[16]) >= PrtPrimGetInt(p_this->varValues[15]));
    
    if (PrtPrimGetBool(PTMP_tmp1_31))
    {
        PRT_VALUE** P_LVALUE_322 = &(PTMP_tmp2_25);
        PrtFreeValue(*P_LVALUE_322);
        *P_LVALUE_322 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_323 = &(p_this->varValues[2]);
            PrtFreeValue(*P_LVALUE_323);
            *P_LVALUE_323 = PTMP_tmp2_25;
            PTMP_tmp2_25 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_324 = &(PTMP_tmp3_21);
        PrtFreeValue(*P_LVALUE_324);
        *P_LVALUE_324 = PrtCloneValue((&P_EVENT_BecomeCandidate.value));
        
        PrtRaise(p_this, PTMP_tmp3_21, 0);
        *(&(PTMP_tmp3_21)) = NULL;
        goto p_return_35;
        
    }
    
    else
    {
    }
    
    
p_return_35: ;
    PrtFreeValue(PTMP_tmp0_34); PTMP_tmp0_34 = NULL;
    PrtFreeValue(PTMP_tmp1_31); PTMP_tmp1_31 = NULL;
    PrtFreeValue(PTMP_tmp2_25); PTMP_tmp2_25 = NULL;
    PrtFreeValue(PTMP_tmp3_21); PTMP_tmp3_21 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_26 =
{
    NULL,
    &P_Anon_IMPL_26,
    NULL
};


PRT_VALUE* P_Anon_IMPL_27(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFreeValue(P_ShuttingDown_IMPL_1(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_36;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_36;
    }
    
p_return_36: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_27 =
{
    NULL,
    &P_Anon_IMPL_27,
    NULL
};


PRT_VALUE* P_Anon_IMPL_28(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_5 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_35 = NULL;
    PRT_VALUE* PTMP_tmp1_32 = NULL;
    PRT_VALUE* PTMP_tmp2_26 = NULL;
    PRT_VALUE* PTMP_tmp3_22 = NULL;
    PRT_VALUE* PTMP_tmp4_15 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_BOOLEAN_14 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_325 = &(PTMP_tmp0_35);
    PrtFreeValue(*P_LVALUE_325);
    *P_LVALUE_325 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_326 = &(PTMP_tmp1_32);
    PrtFreeValue(*P_LVALUE_326);
    *P_LVALUE_326 = PrtCloneValue((&P_EVENT_AddServerResponse.value));
    
    PRT_VALUE** P_LVALUE_327 = &(PTMP_tmp2_26);
    PrtFreeValue(*P_LVALUE_327);
    *P_LVALUE_327 = PrtCloneValue(*P_VAR_server_5);
    
    PRT_VALUE** P_LVALUE_328 = &(PTMP_tmp3_22);
    PrtFreeValue(*P_LVALUE_328);
    *P_LVALUE_328 = PrtCloneValue((&P_LIT_BOOLEAN_14));
    
    PRT_VALUE** P_LVALUE_329 = &(PTMP_tmp4_15);
    PrtFreeValue(*P_LVALUE_329);
    *P_LVALUE_329 = (PrtMkTuple(&P_GEND_TYPE_T2mb, &(PTMP_tmp2_26), &(PTMP_tmp3_22)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_35), PTMP_tmp1_32, 1, &(PTMP_tmp4_15));
    *(&(PTMP_tmp1_32)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_37;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_37;
    }
    
p_return_37: ;
    PrtFreeValue(PTMP_tmp0_35); PTMP_tmp0_35 = NULL;
    PrtFreeValue(PTMP_tmp1_32); PTMP_tmp1_32 = NULL;
    PrtFreeValue(PTMP_tmp2_26); PTMP_tmp2_26 = NULL;
    PrtFreeValue(PTMP_tmp3_22); PTMP_tmp3_22 = NULL;
    PrtFreeValue(PTMP_tmp4_15); PTMP_tmp4_15 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_28 =
{
    NULL,
    &P_Anon_IMPL_28,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_Anon_IMPL_29(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_6 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_36 = NULL;
    PRT_VALUE* PTMP_tmp1_33 = NULL;
    PRT_VALUE* PTMP_tmp2_27 = NULL;
    PRT_VALUE* PTMP_tmp3_23 = NULL;
    PRT_VALUE* PTMP_tmp4_16 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_BOOLEAN_15 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_330 = &(PTMP_tmp0_36);
    PrtFreeValue(*P_LVALUE_330);
    *P_LVALUE_330 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_331 = &(PTMP_tmp1_33);
    PrtFreeValue(*P_LVALUE_331);
    *P_LVALUE_331 = PrtCloneValue((&P_EVENT_RemoveServerResponse.value));
    
    PRT_VALUE** P_LVALUE_332 = &(PTMP_tmp2_27);
    PrtFreeValue(*P_LVALUE_332);
    *P_LVALUE_332 = PrtCloneValue(*P_VAR_server_6);
    
    PRT_VALUE** P_LVALUE_333 = &(PTMP_tmp3_23);
    PrtFreeValue(*P_LVALUE_333);
    *P_LVALUE_333 = PrtCloneValue((&P_LIT_BOOLEAN_15));
    
    PRT_VALUE** P_LVALUE_334 = &(PTMP_tmp4_16);
    PrtFreeValue(*P_LVALUE_334);
    *P_LVALUE_334 = (PrtMkTuple(&P_GEND_TYPE_T2mb_1, &(PTMP_tmp2_27), &(PTMP_tmp3_23)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_36), PTMP_tmp1_33, 1, &(PTMP_tmp4_16));
    *(&(PTMP_tmp1_33)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_38;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_38;
    }
    
p_return_38: ;
    PrtFreeValue(PTMP_tmp0_36); PTMP_tmp0_36 = NULL;
    PrtFreeValue(PTMP_tmp1_33); PTMP_tmp1_33 = NULL;
    PrtFreeValue(PTMP_tmp2_27); PTMP_tmp2_27 = NULL;
    PrtFreeValue(PTMP_tmp3_23); PTMP_tmp3_23 = NULL;
    PrtFreeValue(PTMP_tmp4_16); PTMP_tmp4_16 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_29 =
{
    NULL,
    &P_Anon_IMPL_29,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_Anon_IMPL_30(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_37 = NULL;
    PRT_VALUE* PTMP_tmp1_34 = NULL;
    PRT_VALUE* PTMP_tmp2_28 = NULL;
    PRT_VALUE* PTMP_tmp3_24 = NULL;
    PRT_VALUE* PTMP_tmp4_17 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_26 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_INT32_27 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE** P_LVALUE_335 = &(PTMP_tmp0_37);
    PrtFreeValue(*P_LVALUE_335);
    *P_LVALUE_335 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_336 = &(PTMP_tmp1_34);
    PrtFreeValue(*P_LVALUE_336);
    *P_LVALUE_336 = PrtCloneValue((&P_EVENT_MakeUnavailable.value));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_37), PTMP_tmp1_34, 0);
    *(&(PTMP_tmp1_34)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_39;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_39;
    }
    
    PRT_VALUE** P_LVALUE_337 = &(PTMP_tmp2_28);
    PrtFreeValue(*P_LVALUE_337);
    *P_LVALUE_337 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[3]) + PrtPrimGetInt((&P_LIT_INT32_26)));
    
    {
        PRT_VALUE** P_LVALUE_338 = &(p_this->varValues[3]);
        PrtFreeValue(*P_LVALUE_338);
        *P_LVALUE_338 = PTMP_tmp2_28;
        PTMP_tmp2_28 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_339 = &(p_this->varValues[4]);
    PrtFreeValue(*P_LVALUE_339);
    *P_LVALUE_339 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_340 = &(p_this->varValues[11]);
    PrtFreeValue(*P_LVALUE_340);
    *P_LVALUE_340 = PrtCloneValue((&P_LIT_INT32_26));
    
    PRT_VALUE** P_LVALUE_341 = &(p_this->varValues[16]);
    PrtFreeValue(*P_LVALUE_341);
    *P_LVALUE_341 = PrtCloneValue((&P_LIT_INT32_27));
    
    PRT_VALUE** P_LVALUE_342 = &(PTMP_tmp3_24);
    PrtFreeValue(*P_LVALUE_342);
    *P_LVALUE_342 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
    
    PRT_VALUE** P_LVALUE_343 = &(PTMP_tmp4_17);
    PrtFreeValue(*P_LVALUE_343);
    *P_LVALUE_343 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
    
    PrtFormatPrintf("\n [Candidate] ", 5, (p_this->id), p_this->varValues[3], p_this->varValues[11], PTMP_tmp3_24, PTMP_tmp4_17, 5, 0, " on Entry | Term ", 1, " | Votes Received ", 2, " | KV Log # entries: ", 3, " | Cfg Log # Entries ", 4, "\n");
    
    PrtFreeValue(P_BroadcastVoteRequests_IMPL(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_39;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_39;
    }
    
p_return_39: ;
    PrtFreeValue(PTMP_tmp0_37); PTMP_tmp0_37 = NULL;
    PrtFreeValue(PTMP_tmp1_34); PTMP_tmp1_34 = NULL;
    PrtFreeValue(PTMP_tmp2_28); PTMP_tmp2_28 = NULL;
    PrtFreeValue(PTMP_tmp3_24); PTMP_tmp3_24 = NULL;
    PrtFreeValue(PTMP_tmp4_17); PTMP_tmp4_17 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_30 =
{
    NULL,
    &P_Anon_IMPL_30,
    NULL
};


PRT_VALUE* P_Anon_IMPL_31(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_13 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_38 = NULL;
    PRT_VALUE* PTMP_tmp1_35 = NULL;
    PRT_VALUE* PTMP_tmp2_29 = NULL;
    PRT_VALUE* PTMP_tmp3_25 = NULL;
    PRT_VALUE* PTMP_tmp4_18 = NULL;
    PRT_VALUE* PTMP_tmp5_13 = NULL;
    PRT_VALUE* PTMP_tmp6_12 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_344 = &(PTMP_tmp0_38);
    PrtFreeValue(*P_LVALUE_344);
    *P_LVALUE_344 = PrtMkBoolValue(!PrtIsEqualValue(p_this->varValues[2], (&_P_GEN_null)));
    
    if (PrtPrimGetBool(PTMP_tmp0_38))
    {
        PrtFormatPrintf("[Candidate | Request] ", 2, (p_this->id), p_this->varValues[2], 2, 0, " sends request to Leader ", 1, "");
        
        PRT_VALUE** P_LVALUE_345 = &(PTMP_tmp1_35);
        PrtFreeValue(*P_LVALUE_345);
        *P_LVALUE_345 = PrtCloneValue(p_this->varValues[2]);
        
        PRT_VALUE** P_LVALUE_346 = &(PTMP_tmp2_29);
        PrtFreeValue(*P_LVALUE_346);
        *P_LVALUE_346 = PrtCloneValue((&P_EVENT_Request.value));
        
        PRT_VALUE** P_LVALUE_347 = &(PTMP_tmp3_25);
        PrtFreeValue(*P_LVALUE_347);
        *P_LVALUE_347 = PrtCloneValue(*P_VAR_payload_13);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_35), PTMP_tmp2_29, 1, &(PTMP_tmp3_25));
        *(&(PTMP_tmp2_29)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_40;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_40;
        }
        
    }
    
    else
    {
        PrtFormatPrintf("[Candidate | Request] ", 1, (p_this->id), 1, 0, " no leader, redirect to ClusterManager");
        
        PRT_VALUE** P_LVALUE_348 = &(PTMP_tmp4_18);
        PrtFreeValue(*P_LVALUE_348);
        *P_LVALUE_348 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_349 = &(PTMP_tmp5_13);
        PrtFreeValue(*P_LVALUE_349);
        *P_LVALUE_349 = PrtCloneValue((&P_EVENT_RedirectRequest.value));
        
        PRT_VALUE** P_LVALUE_350 = &(PTMP_tmp6_12);
        PrtFreeValue(*P_LVALUE_350);
        *P_LVALUE_350 = PrtCloneValue(*P_VAR_payload_13);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp4_18), PTMP_tmp5_13, 1, &(PTMP_tmp6_12));
        *(&(PTMP_tmp5_13)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_40;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_40;
        }
        
    }
    
    
p_return_40: ;
    PrtFreeValue(PTMP_tmp0_38); PTMP_tmp0_38 = NULL;
    PrtFreeValue(PTMP_tmp1_35); PTMP_tmp1_35 = NULL;
    PrtFreeValue(PTMP_tmp2_29); PTMP_tmp2_29 = NULL;
    PrtFreeValue(PTMP_tmp3_25); PTMP_tmp3_25 = NULL;
    PrtFreeValue(PTMP_tmp4_18); PTMP_tmp4_18 = NULL;
    PrtFreeValue(PTMP_tmp5_13); PTMP_tmp5_13 = NULL;
    PrtFreeValue(PTMP_tmp6_12); PTMP_tmp6_12 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_31 =
{
    NULL,
    &P_Anon_IMPL_31,
    &P_GEND_TYPE_T3mrr
};


PRT_VALUE* P_Anon_IMPL_32(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_4 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_39 = NULL;
    PRT_VALUE* PTMP_tmp1_36 = NULL;
    PRT_VALUE* PTMP_tmp2_30 = NULL;
    PRT_VALUE* PTMP_tmp3_26 = NULL;
    PRT_VALUE* PTMP_tmp4_19 = NULL;
    PRT_VALUE* PTMP_tmp5_14 = NULL;
    PRT_VALUE* PTMP_tmp6_13 = NULL;
    PRT_VALUE* PTMP_tmp7_11 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_351 = &(PTMP_tmp0_39);
    PrtFreeValue(*P_LVALUE_351);
    *P_LVALUE_351 = PrtTupleGet(*P_VAR_request_4, 0);
    
    PrtFormatPrintf("[Candidate | VoteRequest] Server ", 3, (p_this->id), PTMP_tmp0_39, p_this->varValues[3], 3, 0, " | Payload Term ", 1, " | Current Term ", 2, "");
    
    PRT_VALUE** P_LVALUE_352 = &(PTMP_tmp1_36);
    PrtFreeValue(*P_LVALUE_352);
    *P_LVALUE_352 = PrtTupleGet(*P_VAR_request_4, 0);
    
    PRT_VALUE** P_LVALUE_353 = &(PTMP_tmp2_30);
    PrtFreeValue(*P_LVALUE_353);
    *P_LVALUE_353 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp1_36) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp2_30))
    {
        PRT_VALUE** P_LVALUE_354 = &(PTMP_tmp3_26);
        PrtFreeValue(*P_LVALUE_354);
        *P_LVALUE_354 = PrtTupleGet(*P_VAR_request_4, 0);
        
        {
            PRT_VALUE** P_LVALUE_355 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_355);
            *P_LVALUE_355 = PTMP_tmp3_26;
            PTMP_tmp3_26 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_356 = &(PTMP_tmp4_19);
        PrtFreeValue(*P_LVALUE_356);
        *P_LVALUE_356 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_357 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_357);
            *P_LVALUE_357 = PTMP_tmp4_19;
            PTMP_tmp4_19 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_358 = &(PTMP_tmp5_14);
        PrtFreeValue(*P_LVALUE_358);
        *P_LVALUE_358 = PrtCloneValue(*P_VAR_request_4);
        
        _P_GEN_funargs[0] = &(PTMP_tmp5_14);
        PrtFreeValue(P_Vote_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp5_14);
        PTMP_tmp5_14 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_41;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_41;
        }
        
        PRT_VALUE** P_LVALUE_359 = &(PTMP_tmp6_13);
        PrtFreeValue(*P_LVALUE_359);
        *P_LVALUE_359 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
        
        PrtRaise(p_this, PTMP_tmp6_13, 0);
        *(&(PTMP_tmp6_13)) = NULL;
        goto p_return_41;
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_360 = &(PTMP_tmp7_11);
        PrtFreeValue(*P_LVALUE_360);
        *P_LVALUE_360 = PrtCloneValue(*P_VAR_request_4);
        
        _P_GEN_funargs[0] = &(PTMP_tmp7_11);
        PrtFreeValue(P_Vote_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp7_11);
        PTMP_tmp7_11 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_41;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_41;
        }
        
    }
    
    
p_return_41: ;
    PrtFreeValue(PTMP_tmp0_39); PTMP_tmp0_39 = NULL;
    PrtFreeValue(PTMP_tmp1_36); PTMP_tmp1_36 = NULL;
    PrtFreeValue(PTMP_tmp2_30); PTMP_tmp2_30 = NULL;
    PrtFreeValue(PTMP_tmp3_26); PTMP_tmp3_26 = NULL;
    PrtFreeValue(PTMP_tmp4_19); PTMP_tmp4_19 = NULL;
    PrtFreeValue(PTMP_tmp5_14); PTMP_tmp5_14 = NULL;
    PrtFreeValue(PTMP_tmp6_13); PTMP_tmp6_13 = NULL;
    PrtFreeValue(PTMP_tmp7_11); PTMP_tmp7_11 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_32 =
{
    NULL,
    &P_Anon_IMPL_32,
    &P_GEND_TYPE_T4imT2iiT2ii
};


PRT_VALUE* P_Anon_IMPL_33(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_5 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_40 = NULL;
    PRT_VALUE* PTMP_tmp1_37 = NULL;
    PRT_VALUE* PTMP_tmp2_31 = NULL;
    PRT_VALUE* PTMP_tmp3_27 = NULL;
    PRT_VALUE* PTMP_tmp4_20 = NULL;
    PRT_VALUE* PTMP_tmp5_15 = NULL;
    PRT_VALUE* PTMP_tmp6_14 = NULL;
    PRT_VALUE* PTMP_tmp7_12 = NULL;
    PRT_VALUE* PTMP_tmp8_10 = NULL;
    PRT_VALUE* PTMP_tmp9_8 = NULL;
    PRT_VALUE* PTMP_tmp10_7 = NULL;
    PRT_VALUE* PTMP_tmp11_7 = NULL;
    PRT_VALUE* PTMP_tmp12_6 = NULL;
    PRT_VALUE* PTMP_tmp13_6 = NULL;
    PRT_VALUE* PTMP_tmp14_6 = NULL;
    PRT_VALUE* PTMP_tmp15_5 = NULL;
    PRT_VALUE* PTMP_tmp16_4 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_28 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_INT32_29 = { PRT_VALUE_KIND_INT, { .nt = 2 } };
    PRT_VALUE P_LIT_INT32_30 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE** P_LVALUE_361 = &(PTMP_tmp0_40);
    PrtFreeValue(*P_LVALUE_361);
    *P_LVALUE_361 = PrtTupleGet(*P_VAR_request_5, 0);
    
    PrtFormatPrintf("[Candidate | VoteResponse] Server ", 3, (p_this->id), PTMP_tmp0_40, p_this->varValues[3], 3, 0, " | Payload Term ", 1, " | Current Term ", 2, "");
    
    PRT_VALUE** P_LVALUE_362 = &(PTMP_tmp1_37);
    PrtFreeValue(*P_LVALUE_362);
    *P_LVALUE_362 = PrtTupleGet(*P_VAR_request_5, 0);
    
    PRT_VALUE** P_LVALUE_363 = &(PTMP_tmp2_31);
    PrtFreeValue(*P_LVALUE_363);
    *P_LVALUE_363 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp1_37) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp2_31))
    {
        PRT_VALUE** P_LVALUE_364 = &(PTMP_tmp3_27);
        PrtFreeValue(*P_LVALUE_364);
        *P_LVALUE_364 = PrtTupleGet(*P_VAR_request_5, 0);
        
        {
            PRT_VALUE** P_LVALUE_365 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_365);
            *P_LVALUE_365 = PTMP_tmp3_27;
            PTMP_tmp3_27 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_366 = &(PTMP_tmp4_20);
        PrtFreeValue(*P_LVALUE_366);
        *P_LVALUE_366 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_367 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_367);
            *P_LVALUE_367 = PTMP_tmp4_20;
            PTMP_tmp4_20 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_368 = &(PTMP_tmp5_15);
        PrtFreeValue(*P_LVALUE_368);
        *P_LVALUE_368 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
        
        PrtRaise(p_this, PTMP_tmp5_15, 0);
        *(&(PTMP_tmp5_15)) = NULL;
        goto p_return_42;
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_369 = &(PTMP_tmp6_14);
        PrtFreeValue(*P_LVALUE_369);
        *P_LVALUE_369 = PrtTupleGet(*P_VAR_request_5, 0);
        
        PRT_VALUE** P_LVALUE_370 = &(PTMP_tmp7_12);
        PrtFreeValue(*P_LVALUE_370);
        *P_LVALUE_370 = PrtMkBoolValue(!PrtIsEqualValue(PTMP_tmp6_14, p_this->varValues[3]));
        
        if (PrtPrimGetBool(PTMP_tmp7_12))
        {
        }
        
        else
        {
            PRT_VALUE** P_LVALUE_371 = &(PTMP_tmp8_10);
            PrtFreeValue(*P_LVALUE_371);
            *P_LVALUE_371 = PrtTupleGet(*P_VAR_request_5, 1);
            
            if (PrtPrimGetBool(PTMP_tmp8_10))
            {
                PRT_VALUE** P_LVALUE_372 = &(PTMP_tmp9_8);
                PrtFreeValue(*P_LVALUE_372);
                *P_LVALUE_372 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[11]) + PrtPrimGetInt((&P_LIT_INT32_28)));
                
                {
                    PRT_VALUE** P_LVALUE_373 = &(p_this->varValues[11]);
                    PrtFreeValue(*P_LVALUE_373);
                    *P_LVALUE_373 = PTMP_tmp9_8;
                    PTMP_tmp9_8 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_374 = &(PTMP_tmp10_7);
                PrtFreeValue(*P_LVALUE_374);
                *P_LVALUE_374 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[1]));
                
                PRT_VALUE** P_LVALUE_375 = &(PTMP_tmp11_7);
                PrtFreeValue(*P_LVALUE_375);
                *P_LVALUE_375 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp10_7) / PrtPrimGetInt((&P_LIT_INT32_29)));
                
                PRT_VALUE** P_LVALUE_376 = &(PTMP_tmp12_6);
                PrtFreeValue(*P_LVALUE_376);
                *P_LVALUE_376 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp11_7) + PrtPrimGetInt((&P_LIT_INT32_28)));
                
                PRT_VALUE** P_LVALUE_377 = &(PTMP_tmp13_6);
                PrtFreeValue(*P_LVALUE_377);
                *P_LVALUE_377 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[11]) >= PrtPrimGetInt(PTMP_tmp12_6));
                
                if (PrtPrimGetBool(PTMP_tmp13_6))
                {
                    PRT_VALUE** P_LVALUE_378 = &(PTMP_tmp14_6);
                    PrtFreeValue(*P_LVALUE_378);
                    *P_LVALUE_378 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                    
                    PRT_VALUE** P_LVALUE_379 = &(PTMP_tmp15_5);
                    PrtFreeValue(*P_LVALUE_379);
                    *P_LVALUE_379 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                    
                    PrtFormatPrintf("\n [Leader] ", 5, (p_this->id), p_this->varValues[3], p_this->varValues[11], PTMP_tmp14_6, PTMP_tmp15_5, 5, 0, " | term ", 1, " | election votes ", 2, " | KV log size ", 3, " | Cfg Log size ", 4, " \n");
                    
                    PRT_VALUE** P_LVALUE_380 = &(p_this->varValues[11]);
                    PrtFreeValue(*P_LVALUE_380);
                    *P_LVALUE_380 = PrtCloneValue((&P_LIT_INT32_30));
                    
                    PRT_VALUE** P_LVALUE_381 = &(PTMP_tmp16_4);
                    PrtFreeValue(*P_LVALUE_381);
                    *P_LVALUE_381 = PrtCloneValue((&P_EVENT_BecomeLeader.value));
                    
                    PrtRaise(p_this, PTMP_tmp16_4, 0);
                    *(&(PTMP_tmp16_4)) = NULL;
                    goto p_return_42;
                    
                }
                
                else
                {
                }
                
                
            }
            
            else
            {
            }
            
            
        }
        
        
    }
    
    
p_return_42: ;
    PrtFreeValue(PTMP_tmp0_40); PTMP_tmp0_40 = NULL;
    PrtFreeValue(PTMP_tmp1_37); PTMP_tmp1_37 = NULL;
    PrtFreeValue(PTMP_tmp2_31); PTMP_tmp2_31 = NULL;
    PrtFreeValue(PTMP_tmp3_27); PTMP_tmp3_27 = NULL;
    PrtFreeValue(PTMP_tmp4_20); PTMP_tmp4_20 = NULL;
    PrtFreeValue(PTMP_tmp5_15); PTMP_tmp5_15 = NULL;
    PrtFreeValue(PTMP_tmp6_14); PTMP_tmp6_14 = NULL;
    PrtFreeValue(PTMP_tmp7_12); PTMP_tmp7_12 = NULL;
    PrtFreeValue(PTMP_tmp8_10); PTMP_tmp8_10 = NULL;
    PrtFreeValue(PTMP_tmp9_8); PTMP_tmp9_8 = NULL;
    PrtFreeValue(PTMP_tmp10_7); PTMP_tmp10_7 = NULL;
    PrtFreeValue(PTMP_tmp11_7); PTMP_tmp11_7 = NULL;
    PrtFreeValue(PTMP_tmp12_6); PTMP_tmp12_6 = NULL;
    PrtFreeValue(PTMP_tmp13_6); PTMP_tmp13_6 = NULL;
    PrtFreeValue(PTMP_tmp14_6); PTMP_tmp14_6 = NULL;
    PrtFreeValue(PTMP_tmp15_5); PTMP_tmp15_5 = NULL;
    PrtFreeValue(PTMP_tmp16_4); PTMP_tmp16_4 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_33 =
{
    NULL,
    &P_Anon_IMPL_33,
    &P_GEND_TYPE_T2ib
};


PRT_VALUE* P_Anon_IMPL_34(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_6 = argRefs[0];
    PRT_VALUE* P_VAR_success = PrtMkDefaultValue(&P_GEND_TYPE_b);
    PRT_VALUE* PTMP_tmp0_41 = NULL;
    PRT_VALUE* PTMP_tmp1_38 = NULL;
    PRT_VALUE* PTMP_tmp2_32 = NULL;
    PRT_VALUE* PTMP_tmp3_28 = NULL;
    PRT_VALUE* PTMP_tmp4_21 = NULL;
    PRT_VALUE* PTMP_tmp5_16 = NULL;
    PRT_VALUE* PTMP_tmp6_15 = NULL;
    PRT_VALUE* PTMP_tmp7_13 = NULL;
    PRT_VALUE* PTMP_tmp8_11 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFormatPrintf("[Candidate | AppendEntriesRequest] Server ", 1, (p_this->id), 1, 0, "");
    
    PRT_VALUE** P_LVALUE_382 = &(PTMP_tmp0_41);
    PrtFreeValue(*P_LVALUE_382);
    *P_LVALUE_382 = PrtTupleGet(*P_VAR_request_6, 0);
    
    PRT_VALUE** P_LVALUE_383 = &(PTMP_tmp1_38);
    PrtFreeValue(*P_LVALUE_383);
    *P_LVALUE_383 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_41) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp1_38))
    {
        PRT_VALUE** P_LVALUE_384 = &(PTMP_tmp2_32);
        PrtFreeValue(*P_LVALUE_384);
        *P_LVALUE_384 = PrtTupleGet(*P_VAR_request_6, 0);
        
        {
            PRT_VALUE** P_LVALUE_385 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_385);
            *P_LVALUE_385 = PTMP_tmp2_32;
            PTMP_tmp2_32 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_386 = &(PTMP_tmp3_28);
        PrtFreeValue(*P_LVALUE_386);
        *P_LVALUE_386 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_387 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_387);
            *P_LVALUE_387 = PTMP_tmp3_28;
            PTMP_tmp3_28 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_388 = &(PTMP_tmp4_21);
        PrtFreeValue(*P_LVALUE_388);
        *P_LVALUE_388 = PrtCloneValue(*P_VAR_request_6);
        
        _P_GEN_funargs[0] = &(PTMP_tmp4_21);
        PrtFreeValue(P_AppendEntries_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp4_21);
        PTMP_tmp4_21 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_43;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_43;
        }
        
        PRT_VALUE** P_LVALUE_389 = &(PTMP_tmp5_16);
        PrtFreeValue(*P_LVALUE_389);
        *P_LVALUE_389 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
        
        PrtRaise(p_this, PTMP_tmp5_16, 0);
        *(&(PTMP_tmp5_16)) = NULL;
        goto p_return_43;
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_390 = &(PTMP_tmp6_15);
        PrtFreeValue(*P_LVALUE_390);
        *P_LVALUE_390 = PrtCloneValue(*P_VAR_request_6);
        
        PRT_VALUE** P_LVALUE_391 = &(PTMP_tmp7_13);
        PrtFreeValue(*P_LVALUE_391);
        *P_LVALUE_391 = ((_P_GEN_funargs[0] = &(PTMP_tmp6_15)), (_P_GEN_funval = P_AppendEntries_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp6_15), PTMP_tmp6_15 = NULL), (_P_GEN_funval));
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_43;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_43;
        }
        
        {
            PRT_VALUE** P_LVALUE_392 = &(P_VAR_success);
            PrtFreeValue(*P_LVALUE_392);
            *P_LVALUE_392 = PTMP_tmp7_13;
            PTMP_tmp7_13 = NULL;
        }
        
        if (PrtPrimGetBool(P_VAR_success))
        {
            PRT_VALUE** P_LVALUE_393 = &(PTMP_tmp8_11);
            PrtFreeValue(*P_LVALUE_393);
            *P_LVALUE_393 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
            
            PrtRaise(p_this, PTMP_tmp8_11, 0);
            *(&(PTMP_tmp8_11)) = NULL;
            goto p_return_43;
            
        }
        
        else
        {
        }
        
        
    }
    
    
p_return_43: ;
    PrtFreeValue(P_VAR_success); P_VAR_success = NULL;
    PrtFreeValue(PTMP_tmp0_41); PTMP_tmp0_41 = NULL;
    PrtFreeValue(PTMP_tmp1_38); PTMP_tmp1_38 = NULL;
    PrtFreeValue(PTMP_tmp2_32); PTMP_tmp2_32 = NULL;
    PrtFreeValue(PTMP_tmp3_28); PTMP_tmp3_28 = NULL;
    PrtFreeValue(PTMP_tmp4_21); PTMP_tmp4_21 = NULL;
    PrtFreeValue(PTMP_tmp5_16); PTMP_tmp5_16 = NULL;
    PrtFreeValue(PTMP_tmp6_15); PTMP_tmp6_15 = NULL;
    PrtFreeValue(PTMP_tmp7_13); PTMP_tmp7_13 = NULL;
    PrtFreeValue(PTMP_tmp8_11); PTMP_tmp8_11 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_34 =
{
    NULL,
    &P_Anon_IMPL_34,
    &P_GEND_TYPE_T8imT2iiT2iiST3irrST2iSmT2iim
};


PRT_VALUE* P_Anon_IMPL_35(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_7 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_42 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFormatPrintf("[Candidate | AppendEntriesResponse] Server ", 1, (p_this->id), 1, 0, "");
    
    PRT_VALUE** P_LVALUE_394 = &(PTMP_tmp0_42);
    PrtFreeValue(*P_LVALUE_394);
    *P_LVALUE_394 = PrtCloneValue(*P_VAR_request_7);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_42);
    PrtFreeValue(P_RespondAppendEntriesAsCandidate_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_42);
    PTMP_tmp0_42 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_44;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_44;
    }
    
p_return_44: ;
    PrtFreeValue(PTMP_tmp0_42); PTMP_tmp0_42 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_35 =
{
    NULL,
    &P_Anon_IMPL_35,
    &P_GEND_TYPE_T6ibbbmm
};


PRT_VALUE* P_Anon_IMPL_36(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_43 = NULL;
    PRT_VALUE* PTMP_tmp1_39 = NULL;
    PRT_VALUE* PTMP_tmp2_33 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_31 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE** P_LVALUE_395 = &(PTMP_tmp0_43);
    PrtFreeValue(*P_LVALUE_395);
    *P_LVALUE_395 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[16]) + PrtPrimGetInt((&P_LIT_INT32_31)));
    
    {
        PRT_VALUE** P_LVALUE_396 = &(p_this->varValues[16]);
        PrtFreeValue(*P_LVALUE_396);
        *P_LVALUE_396 = PTMP_tmp0_43;
        PTMP_tmp0_43 = NULL;
    }
    
    PrtFormatPrintf("[Candidate] ", 3, (p_this->id), p_this->varValues[16], p_this->varValues[15], 3, 0, " TickCounter ", 1, ", MaxTicks ", 2, "");
    
    PRT_VALUE** P_LVALUE_397 = &(PTMP_tmp1_39);
    PrtFreeValue(*P_LVALUE_397);
    *P_LVALUE_397 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[16]) >= PrtPrimGetInt(p_this->varValues[15]));
    
    if (PrtPrimGetBool(PTMP_tmp1_39))
    {
        PRT_VALUE** P_LVALUE_398 = &(PTMP_tmp2_33);
        PrtFreeValue(*P_LVALUE_398);
        *P_LVALUE_398 = PrtCloneValue((&P_EVENT_BecomeCandidate.value));
        
        PrtRaise(p_this, PTMP_tmp2_33, 0);
        *(&(PTMP_tmp2_33)) = NULL;
        goto p_return_45;
        
    }
    
    else
    {
    }
    
    
p_return_45: ;
    PrtFreeValue(PTMP_tmp0_43); PTMP_tmp0_43 = NULL;
    PrtFreeValue(PTMP_tmp1_39); PTMP_tmp1_39 = NULL;
    PrtFreeValue(PTMP_tmp2_33); PTMP_tmp2_33 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_36 =
{
    NULL,
    &P_Anon_IMPL_36,
    NULL
};


PRT_VALUE* P_Anon_IMPL_37(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_7 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_44 = NULL;
    PRT_VALUE* PTMP_tmp1_40 = NULL;
    PRT_VALUE* PTMP_tmp2_34 = NULL;
    PRT_VALUE* PTMP_tmp3_29 = NULL;
    PRT_VALUE* PTMP_tmp4_22 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_BOOLEAN_16 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_399 = &(PTMP_tmp0_44);
    PrtFreeValue(*P_LVALUE_399);
    *P_LVALUE_399 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_400 = &(PTMP_tmp1_40);
    PrtFreeValue(*P_LVALUE_400);
    *P_LVALUE_400 = PrtCloneValue((&P_EVENT_AddServerResponse.value));
    
    PRT_VALUE** P_LVALUE_401 = &(PTMP_tmp2_34);
    PrtFreeValue(*P_LVALUE_401);
    *P_LVALUE_401 = PrtCloneValue(*P_VAR_server_7);
    
    PRT_VALUE** P_LVALUE_402 = &(PTMP_tmp3_29);
    PrtFreeValue(*P_LVALUE_402);
    *P_LVALUE_402 = PrtCloneValue((&P_LIT_BOOLEAN_16));
    
    PRT_VALUE** P_LVALUE_403 = &(PTMP_tmp4_22);
    PrtFreeValue(*P_LVALUE_403);
    *P_LVALUE_403 = (PrtMkTuple(&P_GEND_TYPE_T2mb, &(PTMP_tmp2_34), &(PTMP_tmp3_29)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_44), PTMP_tmp1_40, 1, &(PTMP_tmp4_22));
    *(&(PTMP_tmp1_40)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_46;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_46;
    }
    
p_return_46: ;
    PrtFreeValue(PTMP_tmp0_44); PTMP_tmp0_44 = NULL;
    PrtFreeValue(PTMP_tmp1_40); PTMP_tmp1_40 = NULL;
    PrtFreeValue(PTMP_tmp2_34); PTMP_tmp2_34 = NULL;
    PrtFreeValue(PTMP_tmp3_29); PTMP_tmp3_29 = NULL;
    PrtFreeValue(PTMP_tmp4_22); PTMP_tmp4_22 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_37 =
{
    NULL,
    &P_Anon_IMPL_37,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_Anon_IMPL_38(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_8 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_45 = NULL;
    PRT_VALUE* PTMP_tmp1_41 = NULL;
    PRT_VALUE* PTMP_tmp2_35 = NULL;
    PRT_VALUE* PTMP_tmp3_30 = NULL;
    PRT_VALUE* PTMP_tmp4_23 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_BOOLEAN_17 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_404 = &(PTMP_tmp0_45);
    PrtFreeValue(*P_LVALUE_404);
    *P_LVALUE_404 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_405 = &(PTMP_tmp1_41);
    PrtFreeValue(*P_LVALUE_405);
    *P_LVALUE_405 = PrtCloneValue((&P_EVENT_RemoveServerResponse.value));
    
    PRT_VALUE** P_LVALUE_406 = &(PTMP_tmp2_35);
    PrtFreeValue(*P_LVALUE_406);
    *P_LVALUE_406 = PrtCloneValue(*P_VAR_server_8);
    
    PRT_VALUE** P_LVALUE_407 = &(PTMP_tmp3_30);
    PrtFreeValue(*P_LVALUE_407);
    *P_LVALUE_407 = PrtCloneValue((&P_LIT_BOOLEAN_17));
    
    PRT_VALUE** P_LVALUE_408 = &(PTMP_tmp4_23);
    PrtFreeValue(*P_LVALUE_408);
    *P_LVALUE_408 = (PrtMkTuple(&P_GEND_TYPE_T2mb_1, &(PTMP_tmp2_35), &(PTMP_tmp3_30)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_45), PTMP_tmp1_41, 1, &(PTMP_tmp4_23));
    *(&(PTMP_tmp1_41)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_47;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_47;
    }
    
p_return_47: ;
    PrtFreeValue(PTMP_tmp0_45); PTMP_tmp0_45 = NULL;
    PrtFreeValue(PTMP_tmp1_41); PTMP_tmp1_41 = NULL;
    PrtFreeValue(PTMP_tmp2_35); PTMP_tmp2_35 = NULL;
    PrtFreeValue(PTMP_tmp3_30); PTMP_tmp3_30 = NULL;
    PrtFreeValue(PTMP_tmp4_23); PTMP_tmp4_23 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_38 =
{
    NULL,
    &P_Anon_IMPL_38,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_BroadcastVoteRequests_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_idx_5 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_lastLogIndex = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_lastLogTerm = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_lastCfgLogIndex = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_lastCfgLogTerm = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_46 = NULL;
    PRT_VALUE* PTMP_tmp1_42 = NULL;
    PRT_VALUE* PTMP_tmp2_36 = NULL;
    PRT_VALUE* PTMP_tmp3_31 = NULL;
    PRT_VALUE* PTMP_tmp4_24 = NULL;
    PRT_VALUE* PTMP_tmp5_17 = NULL;
    PRT_VALUE* PTMP_tmp6_16 = NULL;
    PRT_VALUE* PTMP_tmp7_14 = NULL;
    PRT_VALUE* PTMP_tmp8_12 = NULL;
    PRT_VALUE* PTMP_tmp9_9 = NULL;
    PRT_VALUE* PTMP_tmp10_8 = NULL;
    PRT_VALUE* PTMP_tmp11_8 = NULL;
    PRT_VALUE* PTMP_tmp12_7 = NULL;
    PRT_VALUE* PTMP_tmp13_7 = NULL;
    PRT_VALUE* PTMP_tmp14_7 = NULL;
    PRT_VALUE* PTMP_tmp15_6 = NULL;
    PRT_VALUE* PTMP_tmp16_5 = NULL;
    PRT_VALUE* PTMP_tmp17_3 = NULL;
    PRT_VALUE* PTMP_tmp18_3 = NULL;
    PRT_VALUE* PTMP_tmp19_3 = NULL;
    PRT_VALUE* PTMP_tmp20_3 = NULL;
    PRT_VALUE* PTMP_tmp21_3 = NULL;
    PRT_VALUE* PTMP_tmp22_3 = NULL;
    PRT_VALUE* PTMP_tmp23_2 = NULL;
    PRT_VALUE* PTMP_tmp24_1 = NULL;
    PRT_VALUE* PTMP_tmp25_1 = NULL;
    PRT_VALUE* PTMP_tmp26_1 = NULL;
    PRT_VALUE* PTMP_tmp27_1 = NULL;
    PRT_VALUE* PTMP_tmp28_1 = NULL;
    PRT_VALUE* PTMP_tmp29_1 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_32 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_33 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_18 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE P_LIT_BOOLEAN_19 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_409 = &(P_VAR_idx_5);
    PrtFreeValue(*P_LVALUE_409);
    *P_LVALUE_409 = PrtCloneValue((&P_LIT_INT32_32));
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_18)))
    {
        PRT_VALUE** P_LVALUE_410 = &(PTMP_tmp0_46);
        PrtFreeValue(*P_LVALUE_410);
        *P_LVALUE_410 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[1]));
        
        PRT_VALUE** P_LVALUE_411 = &(PTMP_tmp1_42);
        PrtFreeValue(*P_LVALUE_411);
        *P_LVALUE_411 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_5) < PrtPrimGetInt(PTMP_tmp0_46));
        
        PRT_VALUE** P_LVALUE_412 = &(PTMP_tmp2_36);
        PrtFreeValue(*P_LVALUE_412);
        *P_LVALUE_412 = PrtCloneValue(PTMP_tmp1_42);
        
        if (PrtPrimGetBool(PTMP_tmp2_36))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_413 = &(PTMP_tmp3_31);
        PrtFreeValue(*P_LVALUE_413);
        *P_LVALUE_413 = PrtSeqGet(p_this->varValues[1], P_VAR_idx_5);
        
        PRT_VALUE** P_LVALUE_414 = &(PTMP_tmp4_24);
        PrtFreeValue(*P_LVALUE_414);
        *P_LVALUE_414 = PrtMkBoolValue(PrtIsEqualValue((p_this->id), PTMP_tmp3_31));
        
        if (PrtPrimGetBool(PTMP_tmp4_24))
        {
            PRT_VALUE** P_LVALUE_415 = &(PTMP_tmp5_17);
            PrtFreeValue(*P_LVALUE_415);
            *P_LVALUE_415 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_5) + PrtPrimGetInt((&P_LIT_INT32_33)));
            
            {
                PRT_VALUE** P_LVALUE_416 = &(P_VAR_idx_5);
                PrtFreeValue(*P_LVALUE_416);
                *P_LVALUE_416 = PTMP_tmp5_17;
                PTMP_tmp5_17 = NULL;
            }
            
            continue;
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_417 = &(PTMP_tmp6_16);
        PrtFreeValue(*P_LVALUE_417);
        *P_LVALUE_417 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
        
        PRT_VALUE** P_LVALUE_418 = &(PTMP_tmp7_14);
        PrtFreeValue(*P_LVALUE_418);
        *P_LVALUE_418 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp6_16) - PrtPrimGetInt((&P_LIT_INT32_33)));
        
        {
            PRT_VALUE** P_LVALUE_419 = &(P_VAR_lastLogIndex);
            PrtFreeValue(*P_LVALUE_419);
            *P_LVALUE_419 = PTMP_tmp7_14;
            PTMP_tmp7_14 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_420 = &(PTMP_tmp8_12);
        PrtFreeValue(*P_LVALUE_420);
        *P_LVALUE_420 = PrtCloneValue(P_VAR_lastLogIndex);
        
        PRT_VALUE** P_LVALUE_421 = &(PTMP_tmp9_9);
        PrtFreeValue(*P_LVALUE_421);
        *P_LVALUE_421 = PrtCloneValue((&P_LIT_BOOLEAN_18));
        
        PRT_VALUE** P_LVALUE_422 = &(PTMP_tmp10_8);
        PrtFreeValue(*P_LVALUE_422);
        *P_LVALUE_422 = ((_P_GEN_funargs[0] = &(PTMP_tmp8_12)), (_P_GEN_funargs[1] = &(PTMP_tmp9_9)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp8_12), PTMP_tmp8_12 = NULL), (PrtFreeValue(PTMP_tmp9_9), PTMP_tmp9_9 = NULL), (_P_GEN_funval));
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_48;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_48;
        }
        
        {
            PRT_VALUE** P_LVALUE_423 = &(P_VAR_lastLogTerm);
            PrtFreeValue(*P_LVALUE_423);
            *P_LVALUE_423 = PTMP_tmp10_8;
            PTMP_tmp10_8 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_424 = &(PTMP_tmp11_8);
        PrtFreeValue(*P_LVALUE_424);
        *P_LVALUE_424 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
        
        PRT_VALUE** P_LVALUE_425 = &(PTMP_tmp12_7);
        PrtFreeValue(*P_LVALUE_425);
        *P_LVALUE_425 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp11_8) - PrtPrimGetInt((&P_LIT_INT32_33)));
        
        {
            PRT_VALUE** P_LVALUE_426 = &(P_VAR_lastCfgLogIndex);
            PrtFreeValue(*P_LVALUE_426);
            *P_LVALUE_426 = PTMP_tmp12_7;
            PTMP_tmp12_7 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_427 = &(PTMP_tmp13_7);
        PrtFreeValue(*P_LVALUE_427);
        *P_LVALUE_427 = PrtCloneValue(P_VAR_lastCfgLogIndex);
        
        PRT_VALUE** P_LVALUE_428 = &(PTMP_tmp14_7);
        PrtFreeValue(*P_LVALUE_428);
        *P_LVALUE_428 = PrtCloneValue((&P_LIT_BOOLEAN_19));
        
        PRT_VALUE** P_LVALUE_429 = &(PTMP_tmp15_6);
        PrtFreeValue(*P_LVALUE_429);
        *P_LVALUE_429 = ((_P_GEN_funargs[0] = &(PTMP_tmp13_7)), (_P_GEN_funargs[1] = &(PTMP_tmp14_7)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp13_7), PTMP_tmp13_7 = NULL), (PrtFreeValue(PTMP_tmp14_7), PTMP_tmp14_7 = NULL), (_P_GEN_funval));
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_48;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_48;
        }
        
        {
            PRT_VALUE** P_LVALUE_430 = &(P_VAR_lastCfgLogTerm);
            PrtFreeValue(*P_LVALUE_430);
            *P_LVALUE_430 = PTMP_tmp15_6;
            PTMP_tmp15_6 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_431 = &(PTMP_tmp16_5);
        PrtFreeValue(*P_LVALUE_431);
        *P_LVALUE_431 = PrtSeqGet(p_this->varValues[1], P_VAR_idx_5);
        
        PrtFormatPrintf("Sending VoteRequest from Server ", 2, (p_this->id), PTMP_tmp16_5, 2, 0, " to Server ", 1, "");
        
        PRT_VALUE** P_LVALUE_432 = &(PTMP_tmp17_3);
        PrtFreeValue(*P_LVALUE_432);
        *P_LVALUE_432 = PrtSeqGet(p_this->varValues[1], P_VAR_idx_5);
        
        PRT_VALUE** P_LVALUE_433 = &(PTMP_tmp18_3);
        PrtFreeValue(*P_LVALUE_433);
        *P_LVALUE_433 = PrtCloneValue(PTMP_tmp17_3);
        
        PRT_VALUE** P_LVALUE_434 = &(PTMP_tmp19_3);
        PrtFreeValue(*P_LVALUE_434);
        *P_LVALUE_434 = PrtCloneValue((&P_EVENT_VoteRequest.value));
        
        PRT_VALUE** P_LVALUE_435 = &(PTMP_tmp20_3);
        PrtFreeValue(*P_LVALUE_435);
        *P_LVALUE_435 = PrtCloneValue(p_this->varValues[3]);
        
        PRT_VALUE** P_LVALUE_436 = &(PTMP_tmp21_3);
        PrtFreeValue(*P_LVALUE_436);
        *P_LVALUE_436 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_437 = &(PTMP_tmp22_3);
        PrtFreeValue(*P_LVALUE_437);
        *P_LVALUE_437 = PrtCloneValue(P_VAR_lastLogIndex);
        
        PRT_VALUE** P_LVALUE_438 = &(PTMP_tmp23_2);
        PrtFreeValue(*P_LVALUE_438);
        *P_LVALUE_438 = PrtCloneValue(P_VAR_lastCfgLogIndex);
        
        PRT_VALUE** P_LVALUE_439 = &(PTMP_tmp24_1);
        PrtFreeValue(*P_LVALUE_439);
        *P_LVALUE_439 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp22_3), &(PTMP_tmp23_2)));
        
        PRT_VALUE** P_LVALUE_440 = &(PTMP_tmp25_1);
        PrtFreeValue(*P_LVALUE_440);
        *P_LVALUE_440 = PrtCloneValue(P_VAR_lastLogTerm);
        
        PRT_VALUE** P_LVALUE_441 = &(PTMP_tmp26_1);
        PrtFreeValue(*P_LVALUE_441);
        *P_LVALUE_441 = PrtCloneValue(P_VAR_lastCfgLogTerm);
        
        PRT_VALUE** P_LVALUE_442 = &(PTMP_tmp27_1);
        PrtFreeValue(*P_LVALUE_442);
        *P_LVALUE_442 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp25_1), &(PTMP_tmp26_1)));
        
        PRT_VALUE** P_LVALUE_443 = &(PTMP_tmp28_1);
        PrtFreeValue(*P_LVALUE_443);
        *P_LVALUE_443 = (PrtMkTuple(&P_GEND_TYPE_T4iRT2iiT2ii, &(PTMP_tmp20_3), &(PTMP_tmp21_3), &(PTMP_tmp24_1), &(PTMP_tmp27_1)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp18_3), PTMP_tmp19_3, 1, &(PTMP_tmp28_1));
        *(&(PTMP_tmp19_3)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_48;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_48;
        }
        
        PRT_VALUE** P_LVALUE_444 = &(PTMP_tmp29_1);
        PrtFreeValue(*P_LVALUE_444);
        *P_LVALUE_444 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_5) + PrtPrimGetInt((&P_LIT_INT32_33)));
        
        {
            PRT_VALUE** P_LVALUE_445 = &(P_VAR_idx_5);
            PrtFreeValue(*P_LVALUE_445);
            *P_LVALUE_445 = PTMP_tmp29_1;
            PTMP_tmp29_1 = NULL;
        }
        
    }
    
    
p_return_48: ;
    PrtFreeValue(P_VAR_idx_5); P_VAR_idx_5 = NULL;
    PrtFreeValue(P_VAR_lastLogIndex); P_VAR_lastLogIndex = NULL;
    PrtFreeValue(P_VAR_lastLogTerm); P_VAR_lastLogTerm = NULL;
    PrtFreeValue(P_VAR_lastCfgLogIndex); P_VAR_lastCfgLogIndex = NULL;
    PrtFreeValue(P_VAR_lastCfgLogTerm); P_VAR_lastCfgLogTerm = NULL;
    PrtFreeValue(PTMP_tmp0_46); PTMP_tmp0_46 = NULL;
    PrtFreeValue(PTMP_tmp1_42); PTMP_tmp1_42 = NULL;
    PrtFreeValue(PTMP_tmp2_36); PTMP_tmp2_36 = NULL;
    PrtFreeValue(PTMP_tmp3_31); PTMP_tmp3_31 = NULL;
    PrtFreeValue(PTMP_tmp4_24); PTMP_tmp4_24 = NULL;
    PrtFreeValue(PTMP_tmp5_17); PTMP_tmp5_17 = NULL;
    PrtFreeValue(PTMP_tmp6_16); PTMP_tmp6_16 = NULL;
    PrtFreeValue(PTMP_tmp7_14); PTMP_tmp7_14 = NULL;
    PrtFreeValue(PTMP_tmp8_12); PTMP_tmp8_12 = NULL;
    PrtFreeValue(PTMP_tmp9_9); PTMP_tmp9_9 = NULL;
    PrtFreeValue(PTMP_tmp10_8); PTMP_tmp10_8 = NULL;
    PrtFreeValue(PTMP_tmp11_8); PTMP_tmp11_8 = NULL;
    PrtFreeValue(PTMP_tmp12_7); PTMP_tmp12_7 = NULL;
    PrtFreeValue(PTMP_tmp13_7); PTMP_tmp13_7 = NULL;
    PrtFreeValue(PTMP_tmp14_7); PTMP_tmp14_7 = NULL;
    PrtFreeValue(PTMP_tmp15_6); PTMP_tmp15_6 = NULL;
    PrtFreeValue(PTMP_tmp16_5); PTMP_tmp16_5 = NULL;
    PrtFreeValue(PTMP_tmp17_3); PTMP_tmp17_3 = NULL;
    PrtFreeValue(PTMP_tmp18_3); PTMP_tmp18_3 = NULL;
    PrtFreeValue(PTMP_tmp19_3); PTMP_tmp19_3 = NULL;
    PrtFreeValue(PTMP_tmp20_3); PTMP_tmp20_3 = NULL;
    PrtFreeValue(PTMP_tmp21_3); PTMP_tmp21_3 = NULL;
    PrtFreeValue(PTMP_tmp22_3); PTMP_tmp22_3 = NULL;
    PrtFreeValue(PTMP_tmp23_2); PTMP_tmp23_2 = NULL;
    PrtFreeValue(PTMP_tmp24_1); PTMP_tmp24_1 = NULL;
    PrtFreeValue(PTMP_tmp25_1); PTMP_tmp25_1 = NULL;
    PrtFreeValue(PTMP_tmp26_1); PTMP_tmp26_1 = NULL;
    PrtFreeValue(PTMP_tmp27_1); PTMP_tmp27_1 = NULL;
    PrtFreeValue(PTMP_tmp28_1); PTMP_tmp28_1 = NULL;
    PrtFreeValue(PTMP_tmp29_1); PTMP_tmp29_1 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_BroadcastVoteRequests =
{
    "BroadcastVoteRequests",
    &P_BroadcastVoteRequests_IMPL,
    NULL
};


PRT_VALUE* P_RespondAppendEntriesAsCandidate_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_8 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_47 = NULL;
    PRT_VALUE* PTMP_tmp1_43 = NULL;
    PRT_VALUE* PTMP_tmp2_37 = NULL;
    PRT_VALUE* PTMP_tmp3_32 = NULL;
    PRT_VALUE* PTMP_tmp4_25 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_446 = &(PTMP_tmp0_47);
    PrtFreeValue(*P_LVALUE_446);
    *P_LVALUE_446 = PrtTupleGet(*P_VAR_request_8, 0);
    
    PRT_VALUE** P_LVALUE_447 = &(PTMP_tmp1_43);
    PrtFreeValue(*P_LVALUE_447);
    *P_LVALUE_447 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_47) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp1_43))
    {
        PRT_VALUE** P_LVALUE_448 = &(PTMP_tmp2_37);
        PrtFreeValue(*P_LVALUE_448);
        *P_LVALUE_448 = PrtTupleGet(*P_VAR_request_8, 0);
        
        {
            PRT_VALUE** P_LVALUE_449 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_449);
            *P_LVALUE_449 = PTMP_tmp2_37;
            PTMP_tmp2_37 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_450 = &(PTMP_tmp3_32);
        PrtFreeValue(*P_LVALUE_450);
        *P_LVALUE_450 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_451 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_451);
            *P_LVALUE_451 = PTMP_tmp3_32;
            PTMP_tmp3_32 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_452 = &(PTMP_tmp4_25);
        PrtFreeValue(*P_LVALUE_452);
        *P_LVALUE_452 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
        
        PrtRaise(p_this, PTMP_tmp4_25, 0);
        *(&(PTMP_tmp4_25)) = NULL;
        goto p_return_49;
        
    }
    
    else
    {
    }
    
    
p_return_49: ;
    PrtFreeValue(PTMP_tmp0_47); PTMP_tmp0_47 = NULL;
    PrtFreeValue(PTMP_tmp1_43); PTMP_tmp1_43 = NULL;
    PrtFreeValue(PTMP_tmp2_37); PTMP_tmp2_37 = NULL;
    PrtFreeValue(PTMP_tmp3_32); PTMP_tmp3_32 = NULL;
    PrtFreeValue(PTMP_tmp4_25); PTMP_tmp4_25 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_RespondAppendEntriesAsCandidate =
{
    "RespondAppendEntriesAsCandidate",
    &P_RespondAppendEntriesAsCandidate_IMPL,
    NULL
};


PRT_VALUE* P_Anon_IMPL_39(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_KVLogIndex = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_ConfigLogIndex = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_KVLogTerm = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_ConfigLogTerm = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_idx_6 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_48 = NULL;
    PRT_VALUE* PTMP_tmp1_44 = NULL;
    PRT_VALUE* PTMP_tmp2_38 = NULL;
    PRT_VALUE* PTMP_tmp3_33 = NULL;
    PRT_VALUE* PTMP_tmp4_26 = NULL;
    PRT_VALUE* PTMP_tmp5_18 = NULL;
    PRT_VALUE* PTMP_tmp6_17 = NULL;
    PRT_VALUE* PTMP_tmp7_15 = NULL;
    PRT_VALUE* PTMP_tmp8_13 = NULL;
    PRT_VALUE* PTMP_tmp9_10 = NULL;
    PRT_VALUE* PTMP_tmp10_9 = NULL;
    PRT_VALUE* PTMP_tmp11_9 = NULL;
    PRT_VALUE* PTMP_tmp12_8 = NULL;
    PRT_VALUE* PTMP_tmp13_8 = NULL;
    PRT_VALUE* PTMP_tmp14_8 = NULL;
    PRT_VALUE* PTMP_tmp15_7 = NULL;
    PRT_VALUE* PTMP_tmp16_6 = NULL;
    PRT_VALUE* PTMP_tmp17_4 = NULL;
    PRT_VALUE* PTMP_tmp18_4 = NULL;
    PRT_VALUE* PTMP_tmp19_4 = NULL;
    PRT_VALUE* PTMP_tmp20_4 = NULL;
    PRT_VALUE* PTMP_tmp21_4 = NULL;
    PRT_VALUE* PTMP_tmp22_4 = NULL;
    PRT_VALUE* PTMP_tmp23_3 = NULL;
    PRT_VALUE* PTMP_tmp24_2 = NULL;
    PRT_VALUE* PTMP_tmp25_2 = NULL;
    PRT_VALUE* PTMP_tmp26_2 = NULL;
    PRT_VALUE* PTMP_tmp27_2 = NULL;
    PRT_VALUE* PTMP_tmp28_2 = NULL;
    PRT_VALUE* PTMP_tmp29_2 = NULL;
    PRT_VALUE* PTMP_tmp30_1 = NULL;
    PRT_VALUE* PTMP_tmp31 = NULL;
    PRT_VALUE* PTMP_tmp32 = NULL;
    PRT_VALUE* PTMP_tmp33 = NULL;
    PRT_VALUE* PTMP_tmp34 = NULL;
    PRT_VALUE* PTMP_tmp35 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_34 = { PRT_VALUE_KIND_INT, { .nt = 5 } };
    PRT_VALUE P_LIT_INT32_35 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_INT32_36 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_BOOLEAN_20 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE P_LIT_BOOLEAN_21 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_453 = &(PTMP_tmp0_48);
    PrtFreeValue(*P_LVALUE_453);
    *P_LVALUE_453 = PrtMkDefaultValue(&P_GEND_TYPE_T2ii);
    
    {
        PRT_VALUE** P_LVALUE_454 = &(p_this->varValues[8]);
        PrtFreeValue(*P_LVALUE_454);
        *P_LVALUE_454 = PTMP_tmp0_48;
        PTMP_tmp0_48 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_455 = &(PTMP_tmp1_44);
    PrtFreeValue(*P_LVALUE_455);
    *P_LVALUE_455 = PrtCloneValue(p_this->varValues[3]);
    
    PRT_VALUE** P_LVALUE_456 = &(PTMP_tmp2_38);
    PrtFreeValue(*P_LVALUE_456);
    *P_LVALUE_456 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_457 = &(PTMP_tmp3_33);
    PrtFreeValue(*P_LVALUE_457);
    *P_LVALUE_457 = (PrtMkTuple(&P_GEND_TYPE_T2iST3irr, &(PTMP_tmp1_44), &(PTMP_tmp2_38)));
    
    
    PRT_VALUE** P_LVALUE_458 = &(PTMP_tmp4_26);
    PrtFreeValue(*P_LVALUE_458);
    *P_LVALUE_458 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_459 = &(PTMP_tmp5_18);
    PrtFreeValue(*P_LVALUE_459);
    *P_LVALUE_459 = PrtCloneValue((&P_EVENT_NotifyLeaderUpdate.value));
    
    PRT_VALUE** P_LVALUE_460 = &(PTMP_tmp6_17);
    PrtFreeValue(*P_LVALUE_460);
    *P_LVALUE_460 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_461 = &(PTMP_tmp7_15);
    PrtFreeValue(*P_LVALUE_461);
    *P_LVALUE_461 = PrtCloneValue(p_this->varValues[3]);
    
    PRT_VALUE** P_LVALUE_462 = &(PTMP_tmp8_13);
    PrtFreeValue(*P_LVALUE_462);
    *P_LVALUE_462 = (PrtMkTuple(&P_GEND_TYPE_T2Ri, &(PTMP_tmp6_17), &(PTMP_tmp7_15)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp4_26), PTMP_tmp5_18, 1, &(PTMP_tmp8_13));
    *(&(PTMP_tmp5_18)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_50;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_50;
    }
    
    PRT_VALUE** P_LVALUE_463 = &(p_this->varValues[15]);
    PrtFreeValue(*P_LVALUE_463);
    *P_LVALUE_463 = PrtCloneValue((&P_LIT_INT32_34));
    
    PRT_VALUE** P_LVALUE_464 = &(PTMP_tmp9_10);
    PrtFreeValue(*P_LVALUE_464);
    *P_LVALUE_464 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
    
    PRT_VALUE** P_LVALUE_465 = &(PTMP_tmp10_9);
    PrtFreeValue(*P_LVALUE_465);
    *P_LVALUE_465 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp9_10) - PrtPrimGetInt((&P_LIT_INT32_35)));
    
    {
        PRT_VALUE** P_LVALUE_466 = &(P_VAR_KVLogIndex);
        PrtFreeValue(*P_LVALUE_466);
        *P_LVALUE_466 = PTMP_tmp10_9;
        PTMP_tmp10_9 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_467 = &(PTMP_tmp11_9);
    PrtFreeValue(*P_LVALUE_467);
    *P_LVALUE_467 = PrtCloneValue(P_VAR_KVLogIndex);
    
    PRT_VALUE** P_LVALUE_468 = &(PTMP_tmp12_8);
    PrtFreeValue(*P_LVALUE_468);
    *P_LVALUE_468 = PrtCloneValue((&P_LIT_BOOLEAN_20));
    
    PRT_VALUE** P_LVALUE_469 = &(PTMP_tmp13_8);
    PrtFreeValue(*P_LVALUE_469);
    *P_LVALUE_469 = ((_P_GEN_funargs[0] = &(PTMP_tmp11_9)), (_P_GEN_funargs[1] = &(PTMP_tmp12_8)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp11_9), PTMP_tmp11_9 = NULL), (PrtFreeValue(PTMP_tmp12_8), PTMP_tmp12_8 = NULL), (_P_GEN_funval));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_50;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_50;
    }
    
    {
        PRT_VALUE** P_LVALUE_470 = &(P_VAR_KVLogTerm);
        PrtFreeValue(*P_LVALUE_470);
        *P_LVALUE_470 = PTMP_tmp13_8;
        PTMP_tmp13_8 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_471 = &(PTMP_tmp14_8);
    PrtFreeValue(*P_LVALUE_471);
    *P_LVALUE_471 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
    
    PRT_VALUE** P_LVALUE_472 = &(PTMP_tmp15_7);
    PrtFreeValue(*P_LVALUE_472);
    *P_LVALUE_472 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp14_8) - PrtPrimGetInt((&P_LIT_INT32_35)));
    
    {
        PRT_VALUE** P_LVALUE_473 = &(P_VAR_ConfigLogIndex);
        PrtFreeValue(*P_LVALUE_473);
        *P_LVALUE_473 = PTMP_tmp15_7;
        PTMP_tmp15_7 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_474 = &(PTMP_tmp16_6);
    PrtFreeValue(*P_LVALUE_474);
    *P_LVALUE_474 = PrtCloneValue(P_VAR_ConfigLogIndex);
    
    PRT_VALUE** P_LVALUE_475 = &(PTMP_tmp17_4);
    PrtFreeValue(*P_LVALUE_475);
    *P_LVALUE_475 = PrtCloneValue((&P_LIT_BOOLEAN_21));
    
    PRT_VALUE** P_LVALUE_476 = &(PTMP_tmp18_4);
    PrtFreeValue(*P_LVALUE_476);
    *P_LVALUE_476 = ((_P_GEN_funargs[0] = &(PTMP_tmp16_6)), (_P_GEN_funargs[1] = &(PTMP_tmp17_4)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp16_6), PTMP_tmp16_6 = NULL), (PrtFreeValue(PTMP_tmp17_4), PTMP_tmp17_4 = NULL), (_P_GEN_funval));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_50;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_50;
    }
    
    {
        PRT_VALUE** P_LVALUE_477 = &(P_VAR_ConfigLogTerm);
        PrtFreeValue(*P_LVALUE_477);
        *P_LVALUE_477 = PTMP_tmp18_4;
        PTMP_tmp18_4 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_478 = &(PTMP_tmp19_4);
    PrtFreeValue(*P_LVALUE_478);
    *P_LVALUE_478 = PrtMkDefaultValue(&P_GEND_TYPE_MKmVT2ii);
    
    {
        PRT_VALUE** P_LVALUE_479 = &(p_this->varValues[9]);
        PrtFreeValue(*P_LVALUE_479);
        *P_LVALUE_479 = PTMP_tmp19_4;
        PTMP_tmp19_4 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_480 = &(PTMP_tmp20_4);
    PrtFreeValue(*P_LVALUE_480);
    *P_LVALUE_480 = PrtMkDefaultValue(&P_GEND_TYPE_MKmVT2ii);
    
    {
        PRT_VALUE** P_LVALUE_481 = &(p_this->varValues[10]);
        PrtFreeValue(*P_LVALUE_481);
        *P_LVALUE_481 = PTMP_tmp20_4;
        PTMP_tmp20_4 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_482 = &(P_VAR_idx_6);
    PrtFreeValue(*P_LVALUE_482);
    *P_LVALUE_482 = PrtCloneValue((&P_LIT_INT32_36));
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_20)))
    {
        PRT_VALUE** P_LVALUE_483 = &(PTMP_tmp21_4);
        PrtFreeValue(*P_LVALUE_483);
        *P_LVALUE_483 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[1]));
        
        PRT_VALUE** P_LVALUE_484 = &(PTMP_tmp22_4);
        PrtFreeValue(*P_LVALUE_484);
        *P_LVALUE_484 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_6) < PrtPrimGetInt(PTMP_tmp21_4));
        
        PRT_VALUE** P_LVALUE_485 = &(PTMP_tmp23_3);
        PrtFreeValue(*P_LVALUE_485);
        *P_LVALUE_485 = PrtCloneValue(PTMP_tmp22_4);
        
        if (PrtPrimGetBool(PTMP_tmp23_3))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_486 = &(PTMP_tmp24_2);
        PrtFreeValue(*P_LVALUE_486);
        *P_LVALUE_486 = PrtSeqGet(p_this->varValues[1], P_VAR_idx_6);
        
        PRT_VALUE** P_LVALUE_487 = &(PTMP_tmp25_2);
        PrtFreeValue(*P_LVALUE_487);
        *P_LVALUE_487 = PrtMkBoolValue(PrtIsEqualValue((p_this->id), PTMP_tmp24_2));
        
        if (PrtPrimGetBool(PTMP_tmp25_2))
        {
            PRT_VALUE** P_LVALUE_488 = &(PTMP_tmp26_2);
            PrtFreeValue(*P_LVALUE_488);
            *P_LVALUE_488 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_6) + PrtPrimGetInt((&P_LIT_INT32_35)));
            
            {
                PRT_VALUE** P_LVALUE_489 = &(P_VAR_idx_6);
                PrtFreeValue(*P_LVALUE_489);
                *P_LVALUE_489 = PTMP_tmp26_2;
                PTMP_tmp26_2 = NULL;
            }
            
            continue;
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_490 = &(PTMP_tmp27_2);
        PrtFreeValue(*P_LVALUE_490);
        *P_LVALUE_490 = PrtSeqGet(p_this->varValues[1], P_VAR_idx_6);
        
        PRT_VALUE** P_LVALUE_491 = &(PTMP_tmp28_2);
        PrtFreeValue(*P_LVALUE_491);
        *P_LVALUE_491 = PrtMkIntValue(PrtPrimGetInt(P_VAR_KVLogIndex) + PrtPrimGetInt((&P_LIT_INT32_35)));
        
        PRT_VALUE** P_LVALUE_492 = &(PTMP_tmp29_2);
        PrtFreeValue(*P_LVALUE_492);
        *P_LVALUE_492 = PrtMkIntValue(PrtPrimGetInt(P_VAR_ConfigLogIndex) + PrtPrimGetInt((&P_LIT_INT32_35)));
        
        PRT_VALUE** P_LVALUE_493 = &(PTMP_tmp30_1);
        PrtFreeValue(*P_LVALUE_493);
        *P_LVALUE_493 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp28_2), &(PTMP_tmp29_2)));
        
        {
            PRT_VALUE** P_LVALUE_494 = &(*(PrtMapGetLValue(p_this->varValues[9], PTMP_tmp27_2, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)));
            PrtFreeValue(*P_LVALUE_494);
            *P_LVALUE_494 = PTMP_tmp30_1;
            PTMP_tmp30_1 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_495 = &(PTMP_tmp31);
        PrtFreeValue(*P_LVALUE_495);
        *P_LVALUE_495 = PrtSeqGet(p_this->varValues[1], P_VAR_idx_6);
        
        PRT_VALUE** P_LVALUE_496 = &(PTMP_tmp32);
        PrtFreeValue(*P_LVALUE_496);
        *P_LVALUE_496 = PrtCloneValue((&P_LIT_INT32_36));
        
        PRT_VALUE** P_LVALUE_497 = &(PTMP_tmp33);
        PrtFreeValue(*P_LVALUE_497);
        *P_LVALUE_497 = PrtCloneValue((&P_LIT_INT32_36));
        
        PRT_VALUE** P_LVALUE_498 = &(PTMP_tmp34);
        PrtFreeValue(*P_LVALUE_498);
        *P_LVALUE_498 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp32), &(PTMP_tmp33)));
        
        {
            PRT_VALUE** P_LVALUE_499 = &(*(PrtMapGetLValue(p_this->varValues[10], PTMP_tmp31, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)));
            PrtFreeValue(*P_LVALUE_499);
            *P_LVALUE_499 = PTMP_tmp34;
            PTMP_tmp34 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_500 = &(PTMP_tmp35);
        PrtFreeValue(*P_LVALUE_500);
        *P_LVALUE_500 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_6) + PrtPrimGetInt((&P_LIT_INT32_35)));
        
        {
            PRT_VALUE** P_LVALUE_501 = &(P_VAR_idx_6);
            PrtFreeValue(*P_LVALUE_501);
            *P_LVALUE_501 = PTMP_tmp35;
            PTMP_tmp35 = NULL;
        }
        
    }
    
    
p_return_50: ;
    PrtFreeValue(P_VAR_KVLogIndex); P_VAR_KVLogIndex = NULL;
    PrtFreeValue(P_VAR_ConfigLogIndex); P_VAR_ConfigLogIndex = NULL;
    PrtFreeValue(P_VAR_KVLogTerm); P_VAR_KVLogTerm = NULL;
    PrtFreeValue(P_VAR_ConfigLogTerm); P_VAR_ConfigLogTerm = NULL;
    PrtFreeValue(P_VAR_idx_6); P_VAR_idx_6 = NULL;
    PrtFreeValue(PTMP_tmp0_48); PTMP_tmp0_48 = NULL;
    PrtFreeValue(PTMP_tmp1_44); PTMP_tmp1_44 = NULL;
    PrtFreeValue(PTMP_tmp2_38); PTMP_tmp2_38 = NULL;
    PrtFreeValue(PTMP_tmp3_33); PTMP_tmp3_33 = NULL;
    PrtFreeValue(PTMP_tmp4_26); PTMP_tmp4_26 = NULL;
    PrtFreeValue(PTMP_tmp5_18); PTMP_tmp5_18 = NULL;
    PrtFreeValue(PTMP_tmp6_17); PTMP_tmp6_17 = NULL;
    PrtFreeValue(PTMP_tmp7_15); PTMP_tmp7_15 = NULL;
    PrtFreeValue(PTMP_tmp8_13); PTMP_tmp8_13 = NULL;
    PrtFreeValue(PTMP_tmp9_10); PTMP_tmp9_10 = NULL;
    PrtFreeValue(PTMP_tmp10_9); PTMP_tmp10_9 = NULL;
    PrtFreeValue(PTMP_tmp11_9); PTMP_tmp11_9 = NULL;
    PrtFreeValue(PTMP_tmp12_8); PTMP_tmp12_8 = NULL;
    PrtFreeValue(PTMP_tmp13_8); PTMP_tmp13_8 = NULL;
    PrtFreeValue(PTMP_tmp14_8); PTMP_tmp14_8 = NULL;
    PrtFreeValue(PTMP_tmp15_7); PTMP_tmp15_7 = NULL;
    PrtFreeValue(PTMP_tmp16_6); PTMP_tmp16_6 = NULL;
    PrtFreeValue(PTMP_tmp17_4); PTMP_tmp17_4 = NULL;
    PrtFreeValue(PTMP_tmp18_4); PTMP_tmp18_4 = NULL;
    PrtFreeValue(PTMP_tmp19_4); PTMP_tmp19_4 = NULL;
    PrtFreeValue(PTMP_tmp20_4); PTMP_tmp20_4 = NULL;
    PrtFreeValue(PTMP_tmp21_4); PTMP_tmp21_4 = NULL;
    PrtFreeValue(PTMP_tmp22_4); PTMP_tmp22_4 = NULL;
    PrtFreeValue(PTMP_tmp23_3); PTMP_tmp23_3 = NULL;
    PrtFreeValue(PTMP_tmp24_2); PTMP_tmp24_2 = NULL;
    PrtFreeValue(PTMP_tmp25_2); PTMP_tmp25_2 = NULL;
    PrtFreeValue(PTMP_tmp26_2); PTMP_tmp26_2 = NULL;
    PrtFreeValue(PTMP_tmp27_2); PTMP_tmp27_2 = NULL;
    PrtFreeValue(PTMP_tmp28_2); PTMP_tmp28_2 = NULL;
    PrtFreeValue(PTMP_tmp29_2); PTMP_tmp29_2 = NULL;
    PrtFreeValue(PTMP_tmp30_1); PTMP_tmp30_1 = NULL;
    PrtFreeValue(PTMP_tmp31); PTMP_tmp31 = NULL;
    PrtFreeValue(PTMP_tmp32); PTMP_tmp32 = NULL;
    PrtFreeValue(PTMP_tmp33); PTMP_tmp33 = NULL;
    PrtFreeValue(PTMP_tmp34); PTMP_tmp34 = NULL;
    PrtFreeValue(PTMP_tmp35); PTMP_tmp35 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_39 =
{
    NULL,
    &P_Anon_IMPL_39,
    NULL
};


PRT_VALUE* P_Anon_IMPL_40(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_14 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_49 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_502 = &(PTMP_tmp0_49);
    PrtFreeValue(*P_LVALUE_502);
    *P_LVALUE_502 = PrtCloneValue(*P_VAR_payload_14);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_49);
    PrtFreeValue(P_ProcessClientRequest_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_49);
    PTMP_tmp0_49 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_51;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_51;
    }
    
p_return_51: ;
    PrtFreeValue(PTMP_tmp0_49); PTMP_tmp0_49 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_40 =
{
    NULL,
    &P_Anon_IMPL_40,
    &P_GEND_TYPE_T3mrr
};


PRT_VALUE* P_Anon_IMPL_41(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_9 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_50 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_503 = &(PTMP_tmp0_50);
    PrtFreeValue(*P_LVALUE_503);
    *P_LVALUE_503 = PrtCloneValue(*P_VAR_request_9);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_50);
    PrtFreeValue(P_VoteAsLeader_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_50);
    PTMP_tmp0_50 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_52;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_52;
    }
    
p_return_52: ;
    PrtFreeValue(PTMP_tmp0_50); PTMP_tmp0_50 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_41 =
{
    NULL,
    &P_Anon_IMPL_41,
    &P_GEND_TYPE_T4imT2iiT2ii
};


PRT_VALUE* P_Anon_IMPL_42(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_10 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_51 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_504 = &(PTMP_tmp0_51);
    PrtFreeValue(*P_LVALUE_504);
    *P_LVALUE_504 = PrtCloneValue(*P_VAR_request_10);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_51);
    PrtFreeValue(P_RespondVoteAsLeader_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_51);
    PTMP_tmp0_51 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_53;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_53;
    }
    
p_return_53: ;
    PrtFreeValue(PTMP_tmp0_51); PTMP_tmp0_51 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_42 =
{
    NULL,
    &P_Anon_IMPL_42,
    &P_GEND_TYPE_T2ib
};


PRT_VALUE* P_Anon_IMPL_43(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_11 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_52 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_505 = &(PTMP_tmp0_52);
    PrtFreeValue(*P_LVALUE_505);
    *P_LVALUE_505 = PrtCloneValue(*P_VAR_request_11);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_52);
    PrtFreeValue(P_AppendEntriesAsLeader_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_52);
    PTMP_tmp0_52 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_54;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_54;
    }
    
p_return_54: ;
    PrtFreeValue(PTMP_tmp0_52); PTMP_tmp0_52 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_43 =
{
    NULL,
    &P_Anon_IMPL_43,
    &P_GEND_TYPE_T8imT2iiT2iiST3irrST2iSmT2iim
};


PRT_VALUE* P_Anon_IMPL_44(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_12 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_53 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_506 = &(PTMP_tmp0_53);
    PrtFreeValue(*P_LVALUE_506);
    *P_LVALUE_506 = PrtCloneValue(*P_VAR_request_12);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_53);
    PrtFreeValue(P_RespondAppendEntriesAsLeader_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_53);
    PTMP_tmp0_53 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_55;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_55;
    }
    
p_return_55: ;
    PrtFreeValue(PTMP_tmp0_53); PTMP_tmp0_53 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_44 =
{
    NULL,
    &P_Anon_IMPL_44,
    &P_GEND_TYPE_T6ibbbmm
};


PRT_VALUE* P_Anon_IMPL_45(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_9 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_54 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_37 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE** P_LVALUE_507 = &(p_this->varValues[13]);
    PrtFreeValue(*P_LVALUE_507);
    *P_LVALUE_507 = PrtCloneValue(*P_VAR_server_9);
    
    PRT_VALUE** P_LVALUE_508 = &(p_this->varValues[14]);
    PrtFreeValue(*P_LVALUE_508);
    *P_LVALUE_508 = PrtCloneValue((&P_LIT_INT32_37));
    
    PRT_VALUE** P_LVALUE_509 = &(PTMP_tmp0_54);
    PrtFreeValue(*P_LVALUE_509);
    *P_LVALUE_509 = PrtCloneValue(*P_VAR_server_9);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_54);
    PrtFreeValue(P_AddServerToConfig_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_54);
    PTMP_tmp0_54 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_56;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_56;
    }
    
p_return_56: ;
    PrtFreeValue(PTMP_tmp0_54); PTMP_tmp0_54 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_45 =
{
    NULL,
    &P_Anon_IMPL_45,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_Anon_IMPL_46(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_10 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_55 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_38 = { PRT_VALUE_KIND_INT, { .nt = 2 } };
    PRT_VALUE** P_LVALUE_510 = &(p_this->varValues[13]);
    PrtFreeValue(*P_LVALUE_510);
    *P_LVALUE_510 = PrtCloneValue(*P_VAR_server_10);
    
    PRT_VALUE** P_LVALUE_511 = &(p_this->varValues[14]);
    PrtFreeValue(*P_LVALUE_511);
    *P_LVALUE_511 = PrtCloneValue((&P_LIT_INT32_38));
    
    PRT_VALUE** P_LVALUE_512 = &(PTMP_tmp0_55);
    PrtFreeValue(*P_LVALUE_512);
    *P_LVALUE_512 = PrtCloneValue(*P_VAR_server_10);
    
    _P_GEN_funargs[0] = &(PTMP_tmp0_55);
    PrtFreeValue(P_RemoveServerFromConfig_IMPL(context, _P_GEN_funargs));
    PrtFreeValue(PTMP_tmp0_55);
    PTMP_tmp0_55 = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_57;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_57;
    }
    
p_return_57: ;
    PrtFreeValue(PTMP_tmp0_55); PTMP_tmp0_55 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_46 =
{
    NULL,
    &P_Anon_IMPL_46,
    &P_GEND_TYPE_m
};


PRT_VALUE* P_Anon_IMPL_47(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_56 = NULL;
    PRT_VALUE* PTMP_tmp1_45 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_39 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_INT32_40 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE** P_LVALUE_513 = &(PTMP_tmp0_56);
    PrtFreeValue(*P_LVALUE_513);
    *P_LVALUE_513 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[16]) + PrtPrimGetInt((&P_LIT_INT32_39)));
    
    {
        PRT_VALUE** P_LVALUE_514 = &(p_this->varValues[16]);
        PrtFreeValue(*P_LVALUE_514);
        *P_LVALUE_514 = PTMP_tmp0_56;
        PTMP_tmp0_56 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_515 = &(PTMP_tmp1_45);
    PrtFreeValue(*P_LVALUE_515);
    *P_LVALUE_515 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[16]) >= PrtPrimGetInt(p_this->varValues[15]));
    
    if (PrtPrimGetBool(PTMP_tmp1_45))
    {
        PrtFreeValue(P_HeartbeatSendAsLeader_IMPL(context, _P_GEN_funargs));
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_58;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_58;
        }
        
        PRT_VALUE** P_LVALUE_516 = &(p_this->varValues[16]);
        PrtFreeValue(*P_LVALUE_516);
        *P_LVALUE_516 = PrtCloneValue((&P_LIT_INT32_40));
        
    }
    
    else
    {
    }
    
    
p_return_58: ;
    PrtFreeValue(PTMP_tmp0_56); PTMP_tmp0_56 = NULL;
    PrtFreeValue(PTMP_tmp1_45); PTMP_tmp1_45 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_47 =
{
    NULL,
    &P_Anon_IMPL_47,
    NULL
};


PRT_VALUE* P_AddServerToConfig_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_11 = argRefs[0];
    PRT_VALUE* P_VAR_cfg = PrtMkDefaultValue(&P_GEND_TYPE_T2iSm);
    PRT_VALUE* PTMP_tmp0_57 = NULL;
    PRT_VALUE* PTMP_tmp1_46 = NULL;
    PRT_VALUE* PTMP_tmp2_39 = NULL;
    PRT_VALUE* PTMP_tmp3_34 = NULL;
    PRT_VALUE* PTMP_tmp4_27 = NULL;
    PRT_VALUE* PTMP_tmp5_19 = NULL;
    PRT_VALUE* PTMP_tmp6_18 = NULL;
    PRT_VALUE* PTMP_tmp7_16 = NULL;
    PRT_VALUE* PTMP_tmp8_14 = NULL;
    PRT_VALUE* PTMP_tmp9_11 = NULL;
    PRT_VALUE* PTMP_tmp10_10 = NULL;
    PRT_VALUE* PTMP_tmp11_10 = NULL;
    PRT_VALUE* PTMP_tmp12_9 = NULL;
    PRT_VALUE* PTMP_tmp13_9 = NULL;
    PRT_VALUE* PTMP_tmp14_9 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_41 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE** P_LVALUE_517 = &(PTMP_tmp0_57);
    PrtFreeValue(*P_LVALUE_517);
    *P_LVALUE_517 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[1]));
    
    PRT_VALUE** P_LVALUE_518 = &(PTMP_tmp1_46);
    PrtFreeValue(*P_LVALUE_518);
    *P_LVALUE_518 = PrtCloneValue(*P_VAR_server_11);
    
    PrtSeqInsertEx(p_this->varValues[1], PTMP_tmp0_57, PTMP_tmp1_46, PRT_FALSE);
    *(&(PTMP_tmp1_46)) = NULL;
    
    PRT_VALUE** P_LVALUE_519 = &(PTMP_tmp2_39);
    PrtFreeValue(*P_LVALUE_519);
    *P_LVALUE_519 = PrtCloneValue(*P_VAR_server_11);
    
    PRT_VALUE** P_LVALUE_520 = &(PTMP_tmp3_34);
    PrtFreeValue(*P_LVALUE_520);
    *P_LVALUE_520 = PrtCloneValue((&P_EVENT_SConfigureEvent.value));
    
    PRT_VALUE** P_LVALUE_521 = &(PTMP_tmp4_27);
    PrtFreeValue(*P_LVALUE_521);
    *P_LVALUE_521 = PrtCloneValue(p_this->varValues[1]);
    
    PRT_VALUE** P_LVALUE_522 = &(PTMP_tmp5_19);
    PrtFreeValue(*P_LVALUE_522);
    *P_LVALUE_522 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_523 = &(PTMP_tmp6_18);
    PrtFreeValue(*P_LVALUE_523);
    *P_LVALUE_523 = (PrtMkTuple(&P_GEND_TYPE_T2Smm, &(PTMP_tmp4_27), &(PTMP_tmp5_19)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp2_39), PTMP_tmp3_34, 1, &(PTMP_tmp6_18));
    *(&(PTMP_tmp3_34)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_59;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_59;
    }
    
    PRT_VALUE** P_LVALUE_524 = &(PTMP_tmp7_16);
    PrtFreeValue(*P_LVALUE_524);
    *P_LVALUE_524 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
    
    PRT_VALUE** P_LVALUE_525 = &(PTMP_tmp8_14);
    PrtFreeValue(*P_LVALUE_525);
    *P_LVALUE_525 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
    
    PRT_VALUE** P_LVALUE_526 = &(PTMP_tmp9_11);
    PrtFreeValue(*P_LVALUE_526);
    *P_LVALUE_526 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp7_16), &(PTMP_tmp8_14)));
    
    {
        PRT_VALUE** P_LVALUE_527 = &(*(PrtMapGetLValue(p_this->varValues[9], *P_VAR_server_11, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)));
        PrtFreeValue(*P_LVALUE_527);
        *P_LVALUE_527 = PTMP_tmp9_11;
        PTMP_tmp9_11 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_528 = &(PTMP_tmp10_10);
    PrtFreeValue(*P_LVALUE_528);
    *P_LVALUE_528 = PrtCloneValue((&P_LIT_INT32_41));
    
    PRT_VALUE** P_LVALUE_529 = &(PTMP_tmp11_10);
    PrtFreeValue(*P_LVALUE_529);
    *P_LVALUE_529 = PrtCloneValue((&P_LIT_INT32_41));
    
    PRT_VALUE** P_LVALUE_530 = &(PTMP_tmp12_9);
    PrtFreeValue(*P_LVALUE_530);
    *P_LVALUE_530 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp10_10), &(PTMP_tmp11_10)));
    
    {
        PRT_VALUE** P_LVALUE_531 = &(*(PrtMapGetLValue(p_this->varValues[10], *P_VAR_server_11, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)));
        PrtFreeValue(*P_LVALUE_531);
        *P_LVALUE_531 = PTMP_tmp12_9;
        PTMP_tmp12_9 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_532 = &(*(PrtTupleGetLValue(P_VAR_cfg, 0)));
    PrtFreeValue(*P_LVALUE_532);
    *P_LVALUE_532 = PrtCloneValue(p_this->varValues[3]);
    
    PRT_VALUE** P_LVALUE_533 = &(*(PrtTupleGetLValue(P_VAR_cfg, 1)));
    PrtFreeValue(*P_LVALUE_533);
    *P_LVALUE_533 = PrtCloneValue(p_this->varValues[1]);
    
    PRT_VALUE** P_LVALUE_534 = &(PTMP_tmp13_9);
    PrtFreeValue(*P_LVALUE_534);
    *P_LVALUE_534 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
    
    PRT_VALUE** P_LVALUE_535 = &(PTMP_tmp14_9);
    PrtFreeValue(*P_LVALUE_535);
    *P_LVALUE_535 = PrtCloneValue(P_VAR_cfg);
    
    PrtSeqInsertEx(p_this->varValues[6], PTMP_tmp13_9, PTMP_tmp14_9, PRT_FALSE);
    *(&(PTMP_tmp14_9)) = NULL;
    
p_return_59: ;
    PrtFreeValue(P_VAR_cfg); P_VAR_cfg = NULL;
    PrtFreeValue(PTMP_tmp0_57); PTMP_tmp0_57 = NULL;
    PrtFreeValue(PTMP_tmp1_46); PTMP_tmp1_46 = NULL;
    PrtFreeValue(PTMP_tmp2_39); PTMP_tmp2_39 = NULL;
    PrtFreeValue(PTMP_tmp3_34); PTMP_tmp3_34 = NULL;
    PrtFreeValue(PTMP_tmp4_27); PTMP_tmp4_27 = NULL;
    PrtFreeValue(PTMP_tmp5_19); PTMP_tmp5_19 = NULL;
    PrtFreeValue(PTMP_tmp6_18); PTMP_tmp6_18 = NULL;
    PrtFreeValue(PTMP_tmp7_16); PTMP_tmp7_16 = NULL;
    PrtFreeValue(PTMP_tmp8_14); PTMP_tmp8_14 = NULL;
    PrtFreeValue(PTMP_tmp9_11); PTMP_tmp9_11 = NULL;
    PrtFreeValue(PTMP_tmp10_10); PTMP_tmp10_10 = NULL;
    PrtFreeValue(PTMP_tmp11_10); PTMP_tmp11_10 = NULL;
    PrtFreeValue(PTMP_tmp12_9); PTMP_tmp12_9 = NULL;
    PrtFreeValue(PTMP_tmp13_9); PTMP_tmp13_9 = NULL;
    PrtFreeValue(PTMP_tmp14_9); PTMP_tmp14_9 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_AddServerToConfig =
{
    "AddServerToConfig",
    &P_AddServerToConfig_IMPL,
    NULL
};


PRT_VALUE* P_RemoveServerFromConfig_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_server_12 = argRefs[0];
    PRT_VALUE* P_VAR_idx_7 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_sIdx = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_cfg_1 = PrtMkDefaultValue(&P_GEND_TYPE_T2iSm);
    PRT_VALUE* PTMP_tmp0_58 = NULL;
    PRT_VALUE* PTMP_tmp1_47 = NULL;
    PRT_VALUE* PTMP_tmp2_40 = NULL;
    PRT_VALUE* PTMP_tmp3_35 = NULL;
    PRT_VALUE* PTMP_tmp4_28 = NULL;
    PRT_VALUE* PTMP_tmp5_20 = NULL;
    PRT_VALUE* PTMP_tmp6_19 = NULL;
    PRT_VALUE* PTMP_tmp7_17 = NULL;
    PRT_VALUE* PTMP_tmp8_15 = NULL;
    PRT_VALUE* PTMP_tmp9_12 = NULL;
    PRT_VALUE* PTMP_tmp10_11 = NULL;
    PRT_VALUE* PTMP_tmp11_11 = NULL;
    PRT_VALUE* PTMP_tmp12_10 = NULL;
    PRT_VALUE* PTMP_tmp13_10 = NULL;
    PRT_VALUE* PTMP_tmp14_10 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_42 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_43 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_22 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_536 = &(P_VAR_idx_7);
    PrtFreeValue(*P_LVALUE_536);
    *P_LVALUE_536 = PrtCloneValue((&P_LIT_INT32_42));
    
    PRT_VALUE** P_LVALUE_537 = &(PTMP_tmp0_58);
    PrtFreeValue(*P_LVALUE_537);
    *P_LVALUE_537 = PrtMkIntValue(-PrtPrimGetInt((&P_LIT_INT32_43)));
    
    {
        PRT_VALUE** P_LVALUE_538 = &(P_VAR_sIdx);
        PrtFreeValue(*P_LVALUE_538);
        *P_LVALUE_538 = PTMP_tmp0_58;
        PTMP_tmp0_58 = NULL;
    }
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_22)))
    {
        PRT_VALUE** P_LVALUE_539 = &(PTMP_tmp1_47);
        PrtFreeValue(*P_LVALUE_539);
        *P_LVALUE_539 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[1]));
        
        PRT_VALUE** P_LVALUE_540 = &(PTMP_tmp2_40);
        PrtFreeValue(*P_LVALUE_540);
        *P_LVALUE_540 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_7) < PrtPrimGetInt(PTMP_tmp1_47));
        
        PRT_VALUE** P_LVALUE_541 = &(PTMP_tmp3_35);
        PrtFreeValue(*P_LVALUE_541);
        *P_LVALUE_541 = PrtCloneValue(PTMP_tmp2_40);
        
        if (PrtPrimGetBool(PTMP_tmp3_35))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_542 = &(PTMP_tmp4_28);
        PrtFreeValue(*P_LVALUE_542);
        *P_LVALUE_542 = PrtSeqGet(p_this->varValues[1], P_VAR_idx_7);
        
        PRT_VALUE** P_LVALUE_543 = &(PTMP_tmp5_20);
        PrtFreeValue(*P_LVALUE_543);
        *P_LVALUE_543 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp4_28, *P_VAR_server_12));
        
        if (PrtPrimGetBool(PTMP_tmp5_20))
        {
            PRT_VALUE** P_LVALUE_544 = &(P_VAR_sIdx);
            PrtFreeValue(*P_LVALUE_544);
            *P_LVALUE_544 = PrtCloneValue(P_VAR_idx_7);
            
            break;
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_545 = &(PTMP_tmp6_19);
        PrtFreeValue(*P_LVALUE_545);
        *P_LVALUE_545 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_7) + PrtPrimGetInt((&P_LIT_INT32_43)));
        
        {
            PRT_VALUE** P_LVALUE_546 = &(P_VAR_idx_7);
            PrtFreeValue(*P_LVALUE_546);
            *P_LVALUE_546 = PTMP_tmp6_19;
            PTMP_tmp6_19 = NULL;
        }
        
    }
    
    
    PRT_VALUE** P_LVALUE_547 = &(PTMP_tmp7_17);
    PrtFreeValue(*P_LVALUE_547);
    *P_LVALUE_547 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_sIdx) >= PrtPrimGetInt((&P_LIT_INT32_42)));
    
    PRT_VALUE** P_LVALUE_548 = &(PTMP_tmp10_11);
    PrtFreeValue(*P_LVALUE_548);
    *P_LVALUE_548 = PrtCloneValue(PTMP_tmp7_17);
    
    if (PrtPrimGetBool(PTMP_tmp10_11))
    {
        PRT_VALUE** P_LVALUE_549 = &(PTMP_tmp8_15);
        PrtFreeValue(*P_LVALUE_549);
        *P_LVALUE_549 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[1]));
        
        PRT_VALUE** P_LVALUE_550 = &(PTMP_tmp9_12);
        PrtFreeValue(*P_LVALUE_550);
        *P_LVALUE_550 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_sIdx) < PrtPrimGetInt(PTMP_tmp8_15));
        
        PRT_VALUE** P_LVALUE_551 = &(PTMP_tmp10_11);
        PrtFreeValue(*P_LVALUE_551);
        *P_LVALUE_551 = PrtCloneValue(PTMP_tmp9_12);
        
    }
    
    
    if (PrtPrimGetBool(PTMP_tmp10_11))
    {
        PRT_VALUE** P_LVALUE_552 = &(PTMP_tmp11_11);
        PrtFreeValue(*P_LVALUE_552);
        *P_LVALUE_552 = PrtSeqGet(p_this->varValues[1], P_VAR_sIdx);
        
        PRT_VALUE** P_LVALUE_553 = &(PTMP_tmp12_10);
        PrtFreeValue(*P_LVALUE_553);
        *P_LVALUE_553 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp11_11, (p_this->id)));
        
        if (PrtPrimGetBool(PTMP_tmp12_10))
        {
            PRT_VALUE** P_LVALUE_554 = &(p_this->varValues[17]);
            PrtFreeValue(*P_LVALUE_554);
            *P_LVALUE_554 = PrtCloneValue((&P_LIT_BOOLEAN_22));
            
            PrtPrintf("\nSpecial case: removing the current leader from config");
            
        }
        
        else
        {
        }
        
        
        PrtRemoveByKey(p_this->varValues[1], P_VAR_sIdx);
        
    }
    
    else
    {
    }
    
    
    PRT_VALUE** P_LVALUE_555 = &(*(PrtTupleGetLValue(P_VAR_cfg_1, 0)));
    PrtFreeValue(*P_LVALUE_555);
    *P_LVALUE_555 = PrtCloneValue(p_this->varValues[3]);
    
    PRT_VALUE** P_LVALUE_556 = &(*(PrtTupleGetLValue(P_VAR_cfg_1, 1)));
    PrtFreeValue(*P_LVALUE_556);
    *P_LVALUE_556 = PrtCloneValue(p_this->varValues[1]);
    
    PRT_VALUE** P_LVALUE_557 = &(PTMP_tmp13_10);
    PrtFreeValue(*P_LVALUE_557);
    *P_LVALUE_557 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
    
    PRT_VALUE** P_LVALUE_558 = &(PTMP_tmp14_10);
    PrtFreeValue(*P_LVALUE_558);
    *P_LVALUE_558 = PrtCloneValue(P_VAR_cfg_1);
    
    PrtSeqInsertEx(p_this->varValues[6], PTMP_tmp13_10, PTMP_tmp14_10, PRT_FALSE);
    *(&(PTMP_tmp14_10)) = NULL;
    
p_return_60: ;
    PrtFreeValue(P_VAR_idx_7); P_VAR_idx_7 = NULL;
    PrtFreeValue(P_VAR_sIdx); P_VAR_sIdx = NULL;
    PrtFreeValue(P_VAR_cfg_1); P_VAR_cfg_1 = NULL;
    PrtFreeValue(PTMP_tmp0_58); PTMP_tmp0_58 = NULL;
    PrtFreeValue(PTMP_tmp1_47); PTMP_tmp1_47 = NULL;
    PrtFreeValue(PTMP_tmp2_40); PTMP_tmp2_40 = NULL;
    PrtFreeValue(PTMP_tmp3_35); PTMP_tmp3_35 = NULL;
    PrtFreeValue(PTMP_tmp4_28); PTMP_tmp4_28 = NULL;
    PrtFreeValue(PTMP_tmp5_20); PTMP_tmp5_20 = NULL;
    PrtFreeValue(PTMP_tmp6_19); PTMP_tmp6_19 = NULL;
    PrtFreeValue(PTMP_tmp7_17); PTMP_tmp7_17 = NULL;
    PrtFreeValue(PTMP_tmp8_15); PTMP_tmp8_15 = NULL;
    PrtFreeValue(PTMP_tmp9_12); PTMP_tmp9_12 = NULL;
    PrtFreeValue(PTMP_tmp10_11); PTMP_tmp10_11 = NULL;
    PrtFreeValue(PTMP_tmp11_11); PTMP_tmp11_11 = NULL;
    PrtFreeValue(PTMP_tmp12_10); PTMP_tmp12_10 = NULL;
    PrtFreeValue(PTMP_tmp13_10); PTMP_tmp13_10 = NULL;
    PrtFreeValue(PTMP_tmp14_10); PTMP_tmp14_10 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_RemoveServerFromConfig =
{
    "RemoveServerFromConfig",
    &P_RemoveServerFromConfig_IMPL,
    NULL
};


PRT_VALUE* P_UpdateFollowerConfigs_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
p_return_61: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_UpdateFollowerConfigs =
{
    "UpdateFollowerConfigs",
    &P_UpdateFollowerConfigs_IMPL,
    NULL
};


PRT_VALUE* P_ProcessClientRequest_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_trigger = argRefs[0];
    PRT_VALUE* P_VAR_log = PrtMkDefaultValue(&P_GEND_TYPE_T3irr);
    PRT_VALUE* P_VAR_cfg_2 = PrtMkDefaultValue(&P_GEND_TYPE_T2iSm);
    PRT_VALUE* PTMP_tmp0_59 = NULL;
    PRT_VALUE* PTMP_tmp1_48 = NULL;
    PRT_VALUE* PTMP_tmp2_41 = NULL;
    PRT_VALUE* PTMP_tmp3_36 = NULL;
    PRT_VALUE* PTMP_tmp4_29 = NULL;
    PRT_VALUE* PTMP_tmp5_21 = NULL;
    PRT_VALUE* PTMP_tmp6_20 = NULL;
    PRT_VALUE* PTMP_tmp7_18 = NULL;
    PRT_VALUE* PTMP_tmp8_16 = NULL;
    PRT_VALUE* PTMP_tmp9_13 = NULL;
    PRT_VALUE* PTMP_tmp10_12 = NULL;
    PRT_VALUE* PTMP_tmp11_12 = NULL;
    PRT_VALUE* PTMP_tmp12_11 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_44 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_45 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE** P_LVALUE_559 = &(PTMP_tmp0_59);
    PrtFreeValue(*P_LVALUE_559);
    *P_LVALUE_559 = PrtTupleGet(*P_VAR_trigger, 0);
    
    PrtFormatPrintf("[Leader | Request] Leader ", 2, (p_this->id), PTMP_tmp0_59, 2, 0, " processing Client ", 1, "");
    
    if (PrtPrimGetBool(p_this->varValues[17]))
    {
        PRT_VALUE** P_LVALUE_560 = &(p_this->varValues[11]);
        PrtFreeValue(*P_LVALUE_560);
        *P_LVALUE_560 = PrtCloneValue((&P_LIT_INT32_44));
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_561 = &(p_this->varValues[11]);
        PrtFreeValue(*P_LVALUE_561);
        *P_LVALUE_561 = PrtCloneValue((&P_LIT_INT32_45));
        
    }
    
    
    PRT_VALUE** P_LVALUE_562 = &(p_this->varValues[12]);
    PrtFreeValue(*P_LVALUE_562);
    *P_LVALUE_562 = PrtCloneValue(*P_VAR_trigger);
    
    PRT_VALUE** P_LVALUE_563 = &(PTMP_tmp1_48);
    PrtFreeValue(*P_LVALUE_563);
    *P_LVALUE_563 = PrtMkDefaultValue(&P_GEND_TYPE_T3irr);
    
    {
        PRT_VALUE** P_LVALUE_564 = &(P_VAR_log);
        PrtFreeValue(*P_LVALUE_564);
        *P_LVALUE_564 = PTMP_tmp1_48;
        PTMP_tmp1_48 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_565 = &(*(PrtTupleGetLValue(P_VAR_log, 0)));
    PrtFreeValue(*P_LVALUE_565);
    *P_LVALUE_565 = PrtCloneValue(p_this->varValues[3]);
    
    PRT_VALUE** P_LVALUE_566 = &(PTMP_tmp2_41);
    PrtFreeValue(*P_LVALUE_566);
    *P_LVALUE_566 = PrtTupleGet(p_this->varValues[12], 1);
    
    {
        PRT_VALUE** P_LVALUE_567 = &(*(PrtTupleGetLValue(P_VAR_log, 1)));
        PrtFreeValue(*P_LVALUE_567);
        *P_LVALUE_567 = PTMP_tmp2_41;
        PTMP_tmp2_41 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_568 = &(PTMP_tmp3_36);
    PrtFreeValue(*P_LVALUE_568);
    *P_LVALUE_568 = PrtTupleGet(p_this->varValues[12], 2);
    
    {
        PRT_VALUE** P_LVALUE_569 = &(*(PrtTupleGetLValue(P_VAR_log, 2)));
        PrtFreeValue(*P_LVALUE_569);
        *P_LVALUE_569 = PTMP_tmp3_36;
        PTMP_tmp3_36 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_570 = &(PTMP_tmp4_29);
    PrtFreeValue(*P_LVALUE_570);
    *P_LVALUE_570 = PrtTupleGet(P_VAR_log, 0);
    
    PRT_VALUE** P_LVALUE_571 = &(PTMP_tmp5_21);
    PrtFreeValue(*P_LVALUE_571);
    *P_LVALUE_571 = PrtTupleGet(P_VAR_log, 1);
    
    PRT_VALUE** P_LVALUE_572 = &(PTMP_tmp6_20);
    PrtFreeValue(*P_LVALUE_572);
    *P_LVALUE_572 = PrtTupleGet(P_VAR_log, 2);
    
    PRT_VALUE** P_LVALUE_573 = &(PTMP_tmp7_18);
    PrtFreeValue(*P_LVALUE_573);
    *P_LVALUE_573 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
    
    PrtFormatPrintf("[Leader | Request] Log Term: ", 4, PTMP_tmp4_29, PTMP_tmp5_21, PTMP_tmp6_20, PTMP_tmp7_18, 4, 0, ", Log Key: ", 1, ", Log Val: ", 2, ", idx: ", 3, "");
    
    PRT_VALUE** P_LVALUE_574 = &(PTMP_tmp8_16);
    PrtFreeValue(*P_LVALUE_574);
    *P_LVALUE_574 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
    
    PRT_VALUE** P_LVALUE_575 = &(PTMP_tmp9_13);
    PrtFreeValue(*P_LVALUE_575);
    *P_LVALUE_575 = PrtCloneValue(P_VAR_log);
    
    PrtSeqInsertEx(p_this->varValues[5], PTMP_tmp8_16, PTMP_tmp9_13, PRT_FALSE);
    *(&(PTMP_tmp9_13)) = NULL;
    
    PRT_VALUE** P_LVALUE_576 = &(PTMP_tmp10_12);
    PrtFreeValue(*P_LVALUE_576);
    *P_LVALUE_576 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_577 = &(PTMP_tmp11_12);
    PrtFreeValue(*P_LVALUE_577);
    *P_LVALUE_577 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_578 = &(PTMP_tmp12_11);
    PrtFreeValue(*P_LVALUE_578);
    *P_LVALUE_578 = (PrtMkTuple(&P_GEND_TYPE_T2RST3irr, &(PTMP_tmp10_12), &(PTMP_tmp11_12)));
    
    
    PrtPrintf("[Leader | Request] Printing Log");
    
    PrtFreeValue(P_PrintLog_IMPL(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_62;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_62;
    }
    
p_return_62: ;
    PrtFreeValue(P_VAR_log); P_VAR_log = NULL;
    PrtFreeValue(P_VAR_cfg_2); P_VAR_cfg_2 = NULL;
    PrtFreeValue(PTMP_tmp0_59); PTMP_tmp0_59 = NULL;
    PrtFreeValue(PTMP_tmp1_48); PTMP_tmp1_48 = NULL;
    PrtFreeValue(PTMP_tmp2_41); PTMP_tmp2_41 = NULL;
    PrtFreeValue(PTMP_tmp3_36); PTMP_tmp3_36 = NULL;
    PrtFreeValue(PTMP_tmp4_29); PTMP_tmp4_29 = NULL;
    PrtFreeValue(PTMP_tmp5_21); PTMP_tmp5_21 = NULL;
    PrtFreeValue(PTMP_tmp6_20); PTMP_tmp6_20 = NULL;
    PrtFreeValue(PTMP_tmp7_18); PTMP_tmp7_18 = NULL;
    PrtFreeValue(PTMP_tmp8_16); PTMP_tmp8_16 = NULL;
    PrtFreeValue(PTMP_tmp9_13); PTMP_tmp9_13 = NULL;
    PrtFreeValue(PTMP_tmp10_12); PTMP_tmp10_12 = NULL;
    PrtFreeValue(PTMP_tmp11_12); PTMP_tmp11_12 = NULL;
    PrtFreeValue(PTMP_tmp12_11); PTMP_tmp12_11 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_ProcessClientRequest =
{
    "ProcessClientRequest",
    &P_ProcessClientRequest_IMPL,
    NULL
};


PRT_VALUE* P_PrintLog_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_idx_8 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_60 = NULL;
    PRT_VALUE* PTMP_tmp1_49 = NULL;
    PRT_VALUE* PTMP_tmp2_42 = NULL;
    PRT_VALUE* PTMP_tmp3_37 = NULL;
    PRT_VALUE* PTMP_tmp4_30 = NULL;
    PRT_VALUE* PTMP_tmp5_22 = NULL;
    PRT_VALUE* PTMP_tmp6_21 = NULL;
    PRT_VALUE* PTMP_tmp7_19 = NULL;
    PRT_VALUE* PTMP_tmp8_17 = NULL;
    PRT_VALUE* PTMP_tmp9_14 = NULL;
    PRT_VALUE* PTMP_tmp10_13 = NULL;
    PRT_VALUE* PTMP_tmp11_13 = NULL;
    PRT_VALUE* PTMP_tmp12_12 = NULL;
    PRT_VALUE* PTMP_tmp13_11 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_46 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_47 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_23 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_579 = &(P_VAR_idx_8);
    PrtFreeValue(*P_LVALUE_579);
    *P_LVALUE_579 = PrtCloneValue((&P_LIT_INT32_46));
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_23)))
    {
        PRT_VALUE** P_LVALUE_580 = &(PTMP_tmp0_60);
        PrtFreeValue(*P_LVALUE_580);
        *P_LVALUE_580 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
        
        PRT_VALUE** P_LVALUE_581 = &(PTMP_tmp1_49);
        PrtFreeValue(*P_LVALUE_581);
        *P_LVALUE_581 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_8) < PrtPrimGetInt(PTMP_tmp0_60));
        
        PRT_VALUE** P_LVALUE_582 = &(PTMP_tmp2_42);
        PrtFreeValue(*P_LVALUE_582);
        *P_LVALUE_582 = PrtCloneValue(PTMP_tmp1_49);
        
        if (PrtPrimGetBool(PTMP_tmp2_42))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_583 = &(PTMP_tmp3_37);
        PrtFreeValue(*P_LVALUE_583);
        *P_LVALUE_583 = PrtSeqGet(p_this->varValues[5], P_VAR_idx_8);
        
        PrtFormatPrintf("[PrintLog] Log element ", 2, P_VAR_idx_8, PTMP_tmp3_37, 2, 0, ": ", 1, "");
        
        PRT_VALUE** P_LVALUE_584 = &(PTMP_tmp4_30);
        PrtFreeValue(*P_LVALUE_584);
        *P_LVALUE_584 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_8) + PrtPrimGetInt((&P_LIT_INT32_47)));
        
        {
            PRT_VALUE** P_LVALUE_585 = &(P_VAR_idx_8);
            PrtFreeValue(*P_LVALUE_585);
            *P_LVALUE_585 = PTMP_tmp4_30;
            PTMP_tmp4_30 = NULL;
        }
        
    }
    
    
    PRT_VALUE** P_LVALUE_586 = &(P_VAR_idx_8);
    PrtFreeValue(*P_LVALUE_586);
    *P_LVALUE_586 = PrtCloneValue((&P_LIT_INT32_46));
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_23)))
    {
        PRT_VALUE** P_LVALUE_587 = &(PTMP_tmp5_22);
        PrtFreeValue(*P_LVALUE_587);
        *P_LVALUE_587 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
        
        PRT_VALUE** P_LVALUE_588 = &(PTMP_tmp6_21);
        PrtFreeValue(*P_LVALUE_588);
        *P_LVALUE_588 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_8) < PrtPrimGetInt(PTMP_tmp5_22));
        
        PRT_VALUE** P_LVALUE_589 = &(PTMP_tmp7_19);
        PrtFreeValue(*P_LVALUE_589);
        *P_LVALUE_589 = PrtCloneValue(PTMP_tmp6_21);
        
        if (PrtPrimGetBool(PTMP_tmp7_19))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_590 = &(PTMP_tmp8_17);
        PrtFreeValue(*P_LVALUE_590);
        *P_LVALUE_590 = PrtSeqGet(p_this->varValues[6], P_VAR_idx_8);
        
        PrtFormatPrintf("[ConfigLog] Log element ", 2, P_VAR_idx_8, PTMP_tmp8_17, 2, 0, ": ", 1, "");
        
        PRT_VALUE** P_LVALUE_591 = &(PTMP_tmp9_14);
        PrtFreeValue(*P_LVALUE_591);
        *P_LVALUE_591 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_8) + PrtPrimGetInt((&P_LIT_INT32_47)));
        
        {
            PRT_VALUE** P_LVALUE_592 = &(P_VAR_idx_8);
            PrtFreeValue(*P_LVALUE_592);
            *P_LVALUE_592 = PTMP_tmp9_14;
            PTMP_tmp9_14 = NULL;
        }
        
    }
    
    
    PRT_VALUE** P_LVALUE_593 = &(PTMP_tmp10_13);
    PrtFreeValue(*P_LVALUE_593);
    *P_LVALUE_593 = PrtTupleGet(p_this->varValues[8], 0);
    
    PRT_VALUE** P_LVALUE_594 = &(PTMP_tmp11_13);
    PrtFreeValue(*P_LVALUE_594);
    *P_LVALUE_594 = PrtTupleGet(p_this->varValues[8], 1);
    
    PrtFormatPrintf("CommitIndex: KV: ", 2, PTMP_tmp10_13, PTMP_tmp11_13, 2, 0, ", CFG: ", 1, "");
    
    PRT_VALUE** P_LVALUE_595 = &(PTMP_tmp12_12);
    PrtFreeValue(*P_LVALUE_595);
    *P_LVALUE_595 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
    
    PRT_VALUE** P_LVALUE_596 = &(PTMP_tmp13_11);
    PrtFreeValue(*P_LVALUE_596);
    *P_LVALUE_596 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
    
    PrtFormatPrintf("\n\n SIZE OF KV: ", 2, PTMP_tmp12_12, PTMP_tmp13_11, 2, 0, ", CONFIG: ", 1, " \n\n");
    
p_return_63: ;
    PrtFreeValue(P_VAR_idx_8); P_VAR_idx_8 = NULL;
    PrtFreeValue(PTMP_tmp0_60); PTMP_tmp0_60 = NULL;
    PrtFreeValue(PTMP_tmp1_49); PTMP_tmp1_49 = NULL;
    PrtFreeValue(PTMP_tmp2_42); PTMP_tmp2_42 = NULL;
    PrtFreeValue(PTMP_tmp3_37); PTMP_tmp3_37 = NULL;
    PrtFreeValue(PTMP_tmp4_30); PTMP_tmp4_30 = NULL;
    PrtFreeValue(PTMP_tmp5_22); PTMP_tmp5_22 = NULL;
    PrtFreeValue(PTMP_tmp6_21); PTMP_tmp6_21 = NULL;
    PrtFreeValue(PTMP_tmp7_19); PTMP_tmp7_19 = NULL;
    PrtFreeValue(PTMP_tmp8_17); PTMP_tmp8_17 = NULL;
    PrtFreeValue(PTMP_tmp9_14); PTMP_tmp9_14 = NULL;
    PrtFreeValue(PTMP_tmp10_13); PTMP_tmp10_13 = NULL;
    PrtFreeValue(PTMP_tmp11_13); PTMP_tmp11_13 = NULL;
    PrtFreeValue(PTMP_tmp12_12); PTMP_tmp12_12 = NULL;
    PrtFreeValue(PTMP_tmp13_11); PTMP_tmp13_11 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_PrintLog =
{
    "PrintLog",
    &P_PrintLog_IMPL,
    NULL
};


PRT_VALUE* P_HeartbeatSendAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_lastLogIndex_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_lastCfgLogIndex_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_sIdx_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_logIdx = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_cfgLogIdx = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_server_13 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    PRT_VALUE* P_VAR_sendLog = PrtMkDefaultValue(&P_GEND_TYPE_ST3irr);
    PRT_VALUE* P_VAR_cfgSendLog = PrtMkDefaultValue(&P_GEND_TYPE_ST2iSm);
    PRT_VALUE* P_VAR_prevLogIndex = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_prevLogTerm = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_prevCfgLogIndex = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_prevCfgLogTerm = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_61 = NULL;
    PRT_VALUE* PTMP_tmp1_50 = NULL;
    PRT_VALUE* PTMP_tmp2_43 = NULL;
    PRT_VALUE* PTMP_tmp3_38 = NULL;
    PRT_VALUE* PTMP_tmp4_31 = NULL;
    PRT_VALUE* PTMP_tmp5_23 = NULL;
    PRT_VALUE* PTMP_tmp6_22 = NULL;
    PRT_VALUE* PTMP_tmp7_20 = NULL;
    PRT_VALUE* PTMP_tmp8_18 = NULL;
    PRT_VALUE* PTMP_tmp9_15 = NULL;
    PRT_VALUE* PTMP_tmp10_14 = NULL;
    PRT_VALUE* PTMP_tmp11_14 = NULL;
    PRT_VALUE* PTMP_tmp12_13 = NULL;
    PRT_VALUE* PTMP_tmp13_12 = NULL;
    PRT_VALUE* PTMP_tmp14_11 = NULL;
    PRT_VALUE* PTMP_tmp15_8 = NULL;
    PRT_VALUE* PTMP_tmp16_7 = NULL;
    PRT_VALUE* PTMP_tmp17_5 = NULL;
    PRT_VALUE* PTMP_tmp18_5 = NULL;
    PRT_VALUE* PTMP_tmp19_5 = NULL;
    PRT_VALUE* PTMP_tmp20_5 = NULL;
    PRT_VALUE* PTMP_tmp21_5 = NULL;
    PRT_VALUE* PTMP_tmp22_5 = NULL;
    PRT_VALUE* PTMP_tmp23_4 = NULL;
    PRT_VALUE* PTMP_tmp24_3 = NULL;
    PRT_VALUE* PTMP_tmp25_3 = NULL;
    PRT_VALUE* PTMP_tmp26_3 = NULL;
    PRT_VALUE* PTMP_tmp27_3 = NULL;
    PRT_VALUE* PTMP_tmp28_3 = NULL;
    PRT_VALUE* PTMP_tmp29_3 = NULL;
    PRT_VALUE* PTMP_tmp30_2 = NULL;
    PRT_VALUE* PTMP_tmp31_1 = NULL;
    PRT_VALUE* PTMP_tmp32_1 = NULL;
    PRT_VALUE* PTMP_tmp33_1 = NULL;
    PRT_VALUE* PTMP_tmp34_1 = NULL;
    PRT_VALUE* PTMP_tmp35_1 = NULL;
    PRT_VALUE* PTMP_tmp36 = NULL;
    PRT_VALUE* PTMP_tmp37 = NULL;
    PRT_VALUE* PTMP_tmp38 = NULL;
    PRT_VALUE* PTMP_tmp39 = NULL;
    PRT_VALUE* PTMP_tmp40 = NULL;
    PRT_VALUE* PTMP_tmp41 = NULL;
    PRT_VALUE* PTMP_tmp42 = NULL;
    PRT_VALUE* PTMP_tmp43 = NULL;
    PRT_VALUE* PTMP_tmp44 = NULL;
    PRT_VALUE* PTMP_tmp45 = NULL;
    PRT_VALUE* PTMP_tmp46 = NULL;
    PRT_VALUE* PTMP_tmp47 = NULL;
    PRT_VALUE* PTMP_tmp48 = NULL;
    PRT_VALUE* PTMP_tmp49 = NULL;
    PRT_VALUE* PTMP_tmp50 = NULL;
    PRT_VALUE* PTMP_tmp51 = NULL;
    PRT_VALUE* PTMP_tmp52 = NULL;
    PRT_VALUE* PTMP_tmp53 = NULL;
    PRT_VALUE* PTMP_tmp54 = NULL;
    PRT_VALUE* PTMP_tmp55 = NULL;
    PRT_VALUE* PTMP_tmp56 = NULL;
    PRT_VALUE* PTMP_tmp57 = NULL;
    PRT_VALUE* PTMP_tmp58 = NULL;
    PRT_VALUE* PTMP_tmp59 = NULL;
    PRT_VALUE* PTMP_tmp60 = NULL;
    PRT_VALUE* PTMP_tmp61 = NULL;
    PRT_VALUE* PTMP_tmp62 = NULL;
    PRT_VALUE* PTMP_tmp63 = NULL;
    PRT_VALUE* PTMP_tmp64 = NULL;
    PRT_VALUE* PTMP_tmp65 = NULL;
    PRT_VALUE* PTMP_tmp66 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_48 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_24 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE P_LIT_BOOLEAN_25 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_597 = &(PTMP_tmp0_61);
    PrtFreeValue(*P_LVALUE_597);
    *P_LVALUE_597 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
    
    PRT_VALUE** P_LVALUE_598 = &(PTMP_tmp1_50);
    PrtFreeValue(*P_LVALUE_598);
    *P_LVALUE_598 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp0_61) - PrtPrimGetInt((&P_LIT_INT32_48)));
    
    {
        PRT_VALUE** P_LVALUE_599 = &(P_VAR_lastLogIndex_1);
        PrtFreeValue(*P_LVALUE_599);
        *P_LVALUE_599 = PTMP_tmp1_50;
        PTMP_tmp1_50 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_600 = &(PTMP_tmp2_43);
    PrtFreeValue(*P_LVALUE_600);
    *P_LVALUE_600 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
    
    PRT_VALUE** P_LVALUE_601 = &(PTMP_tmp3_38);
    PrtFreeValue(*P_LVALUE_601);
    *P_LVALUE_601 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp2_43) - PrtPrimGetInt((&P_LIT_INT32_48)));
    
    {
        PRT_VALUE** P_LVALUE_602 = &(P_VAR_lastCfgLogIndex_1);
        PrtFreeValue(*P_LVALUE_602);
        *P_LVALUE_602 = PTMP_tmp3_38;
        PTMP_tmp3_38 = NULL;
    }
    
    PrtFormatPrintf("\n[Leader | PCR | HeartbeatSendAsLeader] [Leader] ", 3, (p_this->id), p_this->varValues[3], P_VAR_lastLogIndex_1, 3, 0, " sends append requests | term ", 1, " | lastLogIndex: ", 2, "\n");
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_24)))
    {
        PRT_VALUE** P_LVALUE_603 = &(PTMP_tmp4_31);
        PrtFreeValue(*P_LVALUE_603);
        *P_LVALUE_603 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[1]));
        
        PRT_VALUE** P_LVALUE_604 = &(PTMP_tmp5_23);
        PrtFreeValue(*P_LVALUE_604);
        *P_LVALUE_604 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_sIdx_1) < PrtPrimGetInt(PTMP_tmp4_31));
        
        PRT_VALUE** P_LVALUE_605 = &(PTMP_tmp6_22);
        PrtFreeValue(*P_LVALUE_605);
        *P_LVALUE_605 = PrtCloneValue(PTMP_tmp5_23);
        
        if (PrtPrimGetBool(PTMP_tmp6_22))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_606 = &(PTMP_tmp7_20);
        PrtFreeValue(*P_LVALUE_606);
        *P_LVALUE_606 = PrtSeqGet(p_this->varValues[1], P_VAR_sIdx_1);
        
        {
            PRT_VALUE** P_LVALUE_607 = &(P_VAR_server_13);
            PrtFreeValue(*P_LVALUE_607);
            *P_LVALUE_607 = PTMP_tmp7_20;
            PTMP_tmp7_20 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_608 = &(PTMP_tmp8_18);
        PrtFreeValue(*P_LVALUE_608);
        *P_LVALUE_608 = PrtSeqGet(p_this->varValues[1], P_VAR_sIdx_1);
        
        PRT_VALUE** P_LVALUE_609 = &(PTMP_tmp9_15);
        PrtFreeValue(*P_LVALUE_609);
        *P_LVALUE_609 = PrtMkBoolValue(PrtIsEqualValue((p_this->id), PTMP_tmp8_18));
        
        if (PrtPrimGetBool(PTMP_tmp9_15))
        {
            PRT_VALUE** P_LVALUE_610 = &(PTMP_tmp10_14);
            PrtFreeValue(*P_LVALUE_610);
            *P_LVALUE_610 = PrtMkIntValue(PrtPrimGetInt(P_VAR_sIdx_1) + PrtPrimGetInt((&P_LIT_INT32_48)));
            
            {
                PRT_VALUE** P_LVALUE_611 = &(P_VAR_sIdx_1);
                PrtFreeValue(*P_LVALUE_611);
                *P_LVALUE_611 = PTMP_tmp10_14;
                PTMP_tmp10_14 = NULL;
            }
            
            continue;
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_612 = &(PTMP_tmp11_14);
        PrtFreeValue(*P_LVALUE_612);
        *P_LVALUE_612 = PrtMkDefaultValue(&P_GEND_TYPE_ST3irr);
        
        {
            PRT_VALUE** P_LVALUE_613 = &(P_VAR_sendLog);
            PrtFreeValue(*P_LVALUE_613);
            *P_LVALUE_613 = PTMP_tmp11_14;
            PTMP_tmp11_14 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_614 = &(PTMP_tmp12_13);
        PrtFreeValue(*P_LVALUE_614);
        *P_LVALUE_614 = PrtMkDefaultValue(&P_GEND_TYPE_ST2iSm);
        
        {
            PRT_VALUE** P_LVALUE_615 = &(P_VAR_cfgSendLog);
            PrtFreeValue(*P_LVALUE_615);
            *P_LVALUE_615 = PTMP_tmp12_13;
            PTMP_tmp12_13 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_616 = &(PTMP_tmp13_12);
        PrtFreeValue(*P_LVALUE_616);
        *P_LVALUE_616 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
        
        PRT_VALUE** P_LVALUE_617 = &(PTMP_tmp14_11);
        PrtFreeValue(*P_LVALUE_617);
        *P_LVALUE_617 = PrtTupleGet(PTMP_tmp13_12, 0);
        
        PRT_VALUE** P_LVALUE_618 = &(PTMP_tmp15_8);
        PrtFreeValue(*P_LVALUE_618);
        *P_LVALUE_618 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_lastLogIndex_1) >= PrtPrimGetInt(PTMP_tmp14_11));
        
        if (PrtPrimGetBool(PTMP_tmp15_8))
        {
            PRT_VALUE** P_LVALUE_619 = &(PTMP_tmp16_7);
            PrtFreeValue(*P_LVALUE_619);
            *P_LVALUE_619 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
            
            PRT_VALUE** P_LVALUE_620 = &(PTMP_tmp17_5);
            PrtFreeValue(*P_LVALUE_620);
            *P_LVALUE_620 = PrtTupleGet(PTMP_tmp16_7, 0);
            
            {
                PRT_VALUE** P_LVALUE_621 = &(P_VAR_logIdx);
                PrtFreeValue(*P_LVALUE_621);
                *P_LVALUE_621 = PTMP_tmp17_5;
                PTMP_tmp17_5 = NULL;
            }
            
            while (PrtPrimGetBool((&P_LIT_BOOLEAN_24)))
            {
                PRT_VALUE** P_LVALUE_622 = &(PTMP_tmp18_5);
                PrtFreeValue(*P_LVALUE_622);
                *P_LVALUE_622 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_logIdx) <= PrtPrimGetInt(P_VAR_lastLogIndex_1));
                
                PRT_VALUE** P_LVALUE_623 = &(PTMP_tmp19_5);
                PrtFreeValue(*P_LVALUE_623);
                *P_LVALUE_623 = PrtCloneValue(PTMP_tmp18_5);
                
                if (PrtPrimGetBool(PTMP_tmp19_5))
                {
                }
                
                else
                {
                    break;
                    
                }
                
                
                PRT_VALUE** P_LVALUE_624 = &(PTMP_tmp20_5);
                PrtFreeValue(*P_LVALUE_624);
                *P_LVALUE_624 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
                
                PRT_VALUE** P_LVALUE_625 = &(PTMP_tmp21_5);
                PrtFreeValue(*P_LVALUE_625);
                *P_LVALUE_625 = PrtTupleGet(PTMP_tmp20_5, 0);
                
                PRT_VALUE** P_LVALUE_626 = &(PTMP_tmp22_5);
                PrtFreeValue(*P_LVALUE_626);
                *P_LVALUE_626 = PrtMkIntValue(PrtPrimGetInt(P_VAR_logIdx) - PrtPrimGetInt(PTMP_tmp21_5));
                
                PRT_VALUE** P_LVALUE_627 = &(PTMP_tmp23_4);
                PrtFreeValue(*P_LVALUE_627);
                *P_LVALUE_627 = PrtSeqGet(p_this->varValues[5], P_VAR_logIdx);
                
                PrtSeqInsertEx(P_VAR_sendLog, PTMP_tmp22_5, PTMP_tmp23_4, PRT_FALSE);
                *(&(PTMP_tmp23_4)) = NULL;
                
                PRT_VALUE** P_LVALUE_628 = &(PTMP_tmp24_3);
                PrtFreeValue(*P_LVALUE_628);
                *P_LVALUE_628 = PrtMkIntValue(PrtPrimGetInt(P_VAR_logIdx) + PrtPrimGetInt((&P_LIT_INT32_48)));
                
                {
                    PRT_VALUE** P_LVALUE_629 = &(P_VAR_logIdx);
                    PrtFreeValue(*P_LVALUE_629);
                    *P_LVALUE_629 = PTMP_tmp24_3;
                    PTMP_tmp24_3 = NULL;
                }
                
            }
            
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_630 = &(PTMP_tmp25_3);
        PrtFreeValue(*P_LVALUE_630);
        *P_LVALUE_630 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
        
        PRT_VALUE** P_LVALUE_631 = &(PTMP_tmp26_3);
        PrtFreeValue(*P_LVALUE_631);
        *P_LVALUE_631 = PrtTupleGet(PTMP_tmp25_3, 1);
        
        PRT_VALUE** P_LVALUE_632 = &(PTMP_tmp27_3);
        PrtFreeValue(*P_LVALUE_632);
        *P_LVALUE_632 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_lastCfgLogIndex_1) >= PrtPrimGetInt(PTMP_tmp26_3));
        
        if (PrtPrimGetBool(PTMP_tmp27_3))
        {
            PRT_VALUE** P_LVALUE_633 = &(PTMP_tmp28_3);
            PrtFreeValue(*P_LVALUE_633);
            *P_LVALUE_633 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
            
            PRT_VALUE** P_LVALUE_634 = &(PTMP_tmp29_3);
            PrtFreeValue(*P_LVALUE_634);
            *P_LVALUE_634 = PrtTupleGet(PTMP_tmp28_3, 1);
            
            {
                PRT_VALUE** P_LVALUE_635 = &(P_VAR_cfgLogIdx);
                PrtFreeValue(*P_LVALUE_635);
                *P_LVALUE_635 = PTMP_tmp29_3;
                PTMP_tmp29_3 = NULL;
            }
            
            while (PrtPrimGetBool((&P_LIT_BOOLEAN_24)))
            {
                PRT_VALUE** P_LVALUE_636 = &(PTMP_tmp30_2);
                PrtFreeValue(*P_LVALUE_636);
                *P_LVALUE_636 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_cfgLogIdx) <= PrtPrimGetInt(P_VAR_lastCfgLogIndex_1));
                
                PRT_VALUE** P_LVALUE_637 = &(PTMP_tmp31_1);
                PrtFreeValue(*P_LVALUE_637);
                *P_LVALUE_637 = PrtCloneValue(PTMP_tmp30_2);
                
                if (PrtPrimGetBool(PTMP_tmp31_1))
                {
                }
                
                else
                {
                    break;
                    
                }
                
                
                PRT_VALUE** P_LVALUE_638 = &(PTMP_tmp32_1);
                PrtFreeValue(*P_LVALUE_638);
                *P_LVALUE_638 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
                
                PRT_VALUE** P_LVALUE_639 = &(PTMP_tmp33_1);
                PrtFreeValue(*P_LVALUE_639);
                *P_LVALUE_639 = PrtTupleGet(PTMP_tmp32_1, 1);
                
                PRT_VALUE** P_LVALUE_640 = &(PTMP_tmp34_1);
                PrtFreeValue(*P_LVALUE_640);
                *P_LVALUE_640 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx) - PrtPrimGetInt(PTMP_tmp33_1));
                
                PRT_VALUE** P_LVALUE_641 = &(PTMP_tmp35_1);
                PrtFreeValue(*P_LVALUE_641);
                *P_LVALUE_641 = PrtSeqGet(p_this->varValues[6], P_VAR_cfgLogIdx);
                
                PrtSeqInsertEx(P_VAR_cfgSendLog, PTMP_tmp34_1, PTMP_tmp35_1, PRT_FALSE);
                *(&(PTMP_tmp35_1)) = NULL;
                
                PRT_VALUE** P_LVALUE_642 = &(PTMP_tmp36);
                PrtFreeValue(*P_LVALUE_642);
                *P_LVALUE_642 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx) + PrtPrimGetInt((&P_LIT_INT32_48)));
                
                {
                    PRT_VALUE** P_LVALUE_643 = &(P_VAR_cfgLogIdx);
                    PrtFreeValue(*P_LVALUE_643);
                    *P_LVALUE_643 = PTMP_tmp36;
                    PTMP_tmp36 = NULL;
                }
                
            }
            
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_644 = &(PTMP_tmp37);
        PrtFreeValue(*P_LVALUE_644);
        *P_LVALUE_644 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
        
        PRT_VALUE** P_LVALUE_645 = &(PTMP_tmp38);
        PrtFreeValue(*P_LVALUE_645);
        *P_LVALUE_645 = PrtMkIntValue(PrtSeqSizeOf(P_VAR_sendLog));
        
        PrtFormatPrintf("[Leader | PCR | HeartbeatSendAsLeader] Next index: ", 2, PTMP_tmp37, PTMP_tmp38, 2, 0, " | sendLog size: ", 1, "");
        
        PRT_VALUE** P_LVALUE_646 = &(PTMP_tmp39);
        PrtFreeValue(*P_LVALUE_646);
        *P_LVALUE_646 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
        
        PRT_VALUE** P_LVALUE_647 = &(PTMP_tmp40);
        PrtFreeValue(*P_LVALUE_647);
        *P_LVALUE_647 = PrtTupleGet(PTMP_tmp39, 0);
        
        PRT_VALUE** P_LVALUE_648 = &(PTMP_tmp41);
        PrtFreeValue(*P_LVALUE_648);
        *P_LVALUE_648 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp40) - PrtPrimGetInt((&P_LIT_INT32_48)));
        
        {
            PRT_VALUE** P_LVALUE_649 = &(P_VAR_prevLogIndex);
            PrtFreeValue(*P_LVALUE_649);
            *P_LVALUE_649 = PTMP_tmp41;
            PTMP_tmp41 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_650 = &(PTMP_tmp42);
        PrtFreeValue(*P_LVALUE_650);
        *P_LVALUE_650 = PrtCloneValue(P_VAR_prevLogIndex);
        
        PRT_VALUE** P_LVALUE_651 = &(PTMP_tmp43);
        PrtFreeValue(*P_LVALUE_651);
        *P_LVALUE_651 = PrtCloneValue((&P_LIT_BOOLEAN_24));
        
        PRT_VALUE** P_LVALUE_652 = &(PTMP_tmp44);
        PrtFreeValue(*P_LVALUE_652);
        *P_LVALUE_652 = ((_P_GEN_funargs[0] = &(PTMP_tmp42)), (_P_GEN_funargs[1] = &(PTMP_tmp43)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp42), PTMP_tmp42 = NULL), (PrtFreeValue(PTMP_tmp43), PTMP_tmp43 = NULL), (_P_GEN_funval));
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_64;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_64;
        }
        
        {
            PRT_VALUE** P_LVALUE_653 = &(P_VAR_prevLogTerm);
            PrtFreeValue(*P_LVALUE_653);
            *P_LVALUE_653 = PTMP_tmp44;
            PTMP_tmp44 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_654 = &(PTMP_tmp45);
        PrtFreeValue(*P_LVALUE_654);
        *P_LVALUE_654 = PrtMapGet(p_this->varValues[9], P_VAR_server_13);
        
        PRT_VALUE** P_LVALUE_655 = &(PTMP_tmp46);
        PrtFreeValue(*P_LVALUE_655);
        *P_LVALUE_655 = PrtTupleGet(PTMP_tmp45, 1);
        
        PRT_VALUE** P_LVALUE_656 = &(PTMP_tmp47);
        PrtFreeValue(*P_LVALUE_656);
        *P_LVALUE_656 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp46) - PrtPrimGetInt((&P_LIT_INT32_48)));
        
        {
            PRT_VALUE** P_LVALUE_657 = &(P_VAR_prevCfgLogIndex);
            PrtFreeValue(*P_LVALUE_657);
            *P_LVALUE_657 = PTMP_tmp47;
            PTMP_tmp47 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_658 = &(PTMP_tmp48);
        PrtFreeValue(*P_LVALUE_658);
        *P_LVALUE_658 = PrtCloneValue(P_VAR_prevCfgLogIndex);
        
        PRT_VALUE** P_LVALUE_659 = &(PTMP_tmp49);
        PrtFreeValue(*P_LVALUE_659);
        *P_LVALUE_659 = PrtCloneValue((&P_LIT_BOOLEAN_25));
        
        PRT_VALUE** P_LVALUE_660 = &(PTMP_tmp50);
        PrtFreeValue(*P_LVALUE_660);
        *P_LVALUE_660 = ((_P_GEN_funargs[0] = &(PTMP_tmp48)), (_P_GEN_funargs[1] = &(PTMP_tmp49)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp48), PTMP_tmp48 = NULL), (PrtFreeValue(PTMP_tmp49), PTMP_tmp49 = NULL), (_P_GEN_funval));
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_64;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_64;
        }
        
        {
            PRT_VALUE** P_LVALUE_661 = &(P_VAR_prevCfgLogTerm);
            PrtFreeValue(*P_LVALUE_661);
            *P_LVALUE_661 = PTMP_tmp50;
            PTMP_tmp50 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_662 = &(PTMP_tmp51);
        PrtFreeValue(*P_LVALUE_662);
        *P_LVALUE_662 = PrtCloneValue(P_VAR_server_13);
        
        PRT_VALUE** P_LVALUE_663 = &(PTMP_tmp52);
        PrtFreeValue(*P_LVALUE_663);
        *P_LVALUE_663 = PrtCloneValue((&P_EVENT_AppendEntriesRequest.value));
        
        PRT_VALUE** P_LVALUE_664 = &(PTMP_tmp53);
        PrtFreeValue(*P_LVALUE_664);
        *P_LVALUE_664 = PrtCloneValue(p_this->varValues[3]);
        
        PRT_VALUE** P_LVALUE_665 = &(PTMP_tmp54);
        PrtFreeValue(*P_LVALUE_665);
        *P_LVALUE_665 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_666 = &(PTMP_tmp55);
        PrtFreeValue(*P_LVALUE_666);
        *P_LVALUE_666 = PrtCloneValue(P_VAR_prevLogIndex);
        
        PRT_VALUE** P_LVALUE_667 = &(PTMP_tmp56);
        PrtFreeValue(*P_LVALUE_667);
        *P_LVALUE_667 = PrtCloneValue(P_VAR_prevCfgLogIndex);
        
        PRT_VALUE** P_LVALUE_668 = &(PTMP_tmp57);
        PrtFreeValue(*P_LVALUE_668);
        *P_LVALUE_668 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp55), &(PTMP_tmp56)));
        
        PRT_VALUE** P_LVALUE_669 = &(PTMP_tmp58);
        PrtFreeValue(*P_LVALUE_669);
        *P_LVALUE_669 = PrtCloneValue(P_VAR_prevLogTerm);
        
        PRT_VALUE** P_LVALUE_670 = &(PTMP_tmp59);
        PrtFreeValue(*P_LVALUE_670);
        *P_LVALUE_670 = PrtCloneValue(P_VAR_prevCfgLogTerm);
        
        PRT_VALUE** P_LVALUE_671 = &(PTMP_tmp60);
        PrtFreeValue(*P_LVALUE_671);
        *P_LVALUE_671 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp58), &(PTMP_tmp59)));
        
        PRT_VALUE** P_LVALUE_672 = &(PTMP_tmp61);
        PrtFreeValue(*P_LVALUE_672);
        *P_LVALUE_672 = PrtCloneValue(P_VAR_sendLog);
        
        PRT_VALUE** P_LVALUE_673 = &(PTMP_tmp62);
        PrtFreeValue(*P_LVALUE_673);
        *P_LVALUE_673 = PrtCloneValue(P_VAR_cfgSendLog);
        
        PRT_VALUE** P_LVALUE_674 = &(PTMP_tmp63);
        PrtFreeValue(*P_LVALUE_674);
        *P_LVALUE_674 = PrtCloneValue(p_this->varValues[8]);
        
        PRT_VALUE** P_LVALUE_675 = &(PTMP_tmp64);
        PrtFreeValue(*P_LVALUE_675);
        *P_LVALUE_675 = PrtTupleGet(p_this->varValues[12], 0);
        
        PRT_VALUE** P_LVALUE_676 = &(PTMP_tmp65);
        PrtFreeValue(*P_LVALUE_676);
        *P_LVALUE_676 = (PrtMkTuple(&P_GEND_TYPE_T8iRT2iiT2iiST3irrST2iSmT2iim, &(PTMP_tmp53), &(PTMP_tmp54), &(PTMP_tmp57), &(PTMP_tmp60), &(PTMP_tmp61), &(PTMP_tmp62), &(PTMP_tmp63), &(PTMP_tmp64)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp51), PTMP_tmp52, 1, &(PTMP_tmp65));
        *(&(PTMP_tmp52)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_64;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_64;
        }
        
        PRT_VALUE** P_LVALUE_677 = &(PTMP_tmp66);
        PrtFreeValue(*P_LVALUE_677);
        *P_LVALUE_677 = PrtMkIntValue(PrtPrimGetInt(P_VAR_sIdx_1) + PrtPrimGetInt((&P_LIT_INT32_48)));
        
        {
            PRT_VALUE** P_LVALUE_678 = &(P_VAR_sIdx_1);
            PrtFreeValue(*P_LVALUE_678);
            *P_LVALUE_678 = PTMP_tmp66;
            PTMP_tmp66 = NULL;
        }
        
    }
    
    
p_return_64: ;
    PrtFreeValue(P_VAR_lastLogIndex_1); P_VAR_lastLogIndex_1 = NULL;
    PrtFreeValue(P_VAR_lastCfgLogIndex_1); P_VAR_lastCfgLogIndex_1 = NULL;
    PrtFreeValue(P_VAR_sIdx_1); P_VAR_sIdx_1 = NULL;
    PrtFreeValue(P_VAR_logIdx); P_VAR_logIdx = NULL;
    PrtFreeValue(P_VAR_cfgLogIdx); P_VAR_cfgLogIdx = NULL;
    PrtFreeValue(P_VAR_server_13); P_VAR_server_13 = NULL;
    PrtFreeValue(P_VAR_sendLog); P_VAR_sendLog = NULL;
    PrtFreeValue(P_VAR_cfgSendLog); P_VAR_cfgSendLog = NULL;
    PrtFreeValue(P_VAR_prevLogIndex); P_VAR_prevLogIndex = NULL;
    PrtFreeValue(P_VAR_prevLogTerm); P_VAR_prevLogTerm = NULL;
    PrtFreeValue(P_VAR_prevCfgLogIndex); P_VAR_prevCfgLogIndex = NULL;
    PrtFreeValue(P_VAR_prevCfgLogTerm); P_VAR_prevCfgLogTerm = NULL;
    PrtFreeValue(PTMP_tmp0_61); PTMP_tmp0_61 = NULL;
    PrtFreeValue(PTMP_tmp1_50); PTMP_tmp1_50 = NULL;
    PrtFreeValue(PTMP_tmp2_43); PTMP_tmp2_43 = NULL;
    PrtFreeValue(PTMP_tmp3_38); PTMP_tmp3_38 = NULL;
    PrtFreeValue(PTMP_tmp4_31); PTMP_tmp4_31 = NULL;
    PrtFreeValue(PTMP_tmp5_23); PTMP_tmp5_23 = NULL;
    PrtFreeValue(PTMP_tmp6_22); PTMP_tmp6_22 = NULL;
    PrtFreeValue(PTMP_tmp7_20); PTMP_tmp7_20 = NULL;
    PrtFreeValue(PTMP_tmp8_18); PTMP_tmp8_18 = NULL;
    PrtFreeValue(PTMP_tmp9_15); PTMP_tmp9_15 = NULL;
    PrtFreeValue(PTMP_tmp10_14); PTMP_tmp10_14 = NULL;
    PrtFreeValue(PTMP_tmp11_14); PTMP_tmp11_14 = NULL;
    PrtFreeValue(PTMP_tmp12_13); PTMP_tmp12_13 = NULL;
    PrtFreeValue(PTMP_tmp13_12); PTMP_tmp13_12 = NULL;
    PrtFreeValue(PTMP_tmp14_11); PTMP_tmp14_11 = NULL;
    PrtFreeValue(PTMP_tmp15_8); PTMP_tmp15_8 = NULL;
    PrtFreeValue(PTMP_tmp16_7); PTMP_tmp16_7 = NULL;
    PrtFreeValue(PTMP_tmp17_5); PTMP_tmp17_5 = NULL;
    PrtFreeValue(PTMP_tmp18_5); PTMP_tmp18_5 = NULL;
    PrtFreeValue(PTMP_tmp19_5); PTMP_tmp19_5 = NULL;
    PrtFreeValue(PTMP_tmp20_5); PTMP_tmp20_5 = NULL;
    PrtFreeValue(PTMP_tmp21_5); PTMP_tmp21_5 = NULL;
    PrtFreeValue(PTMP_tmp22_5); PTMP_tmp22_5 = NULL;
    PrtFreeValue(PTMP_tmp23_4); PTMP_tmp23_4 = NULL;
    PrtFreeValue(PTMP_tmp24_3); PTMP_tmp24_3 = NULL;
    PrtFreeValue(PTMP_tmp25_3); PTMP_tmp25_3 = NULL;
    PrtFreeValue(PTMP_tmp26_3); PTMP_tmp26_3 = NULL;
    PrtFreeValue(PTMP_tmp27_3); PTMP_tmp27_3 = NULL;
    PrtFreeValue(PTMP_tmp28_3); PTMP_tmp28_3 = NULL;
    PrtFreeValue(PTMP_tmp29_3); PTMP_tmp29_3 = NULL;
    PrtFreeValue(PTMP_tmp30_2); PTMP_tmp30_2 = NULL;
    PrtFreeValue(PTMP_tmp31_1); PTMP_tmp31_1 = NULL;
    PrtFreeValue(PTMP_tmp32_1); PTMP_tmp32_1 = NULL;
    PrtFreeValue(PTMP_tmp33_1); PTMP_tmp33_1 = NULL;
    PrtFreeValue(PTMP_tmp34_1); PTMP_tmp34_1 = NULL;
    PrtFreeValue(PTMP_tmp35_1); PTMP_tmp35_1 = NULL;
    PrtFreeValue(PTMP_tmp36); PTMP_tmp36 = NULL;
    PrtFreeValue(PTMP_tmp37); PTMP_tmp37 = NULL;
    PrtFreeValue(PTMP_tmp38); PTMP_tmp38 = NULL;
    PrtFreeValue(PTMP_tmp39); PTMP_tmp39 = NULL;
    PrtFreeValue(PTMP_tmp40); PTMP_tmp40 = NULL;
    PrtFreeValue(PTMP_tmp41); PTMP_tmp41 = NULL;
    PrtFreeValue(PTMP_tmp42); PTMP_tmp42 = NULL;
    PrtFreeValue(PTMP_tmp43); PTMP_tmp43 = NULL;
    PrtFreeValue(PTMP_tmp44); PTMP_tmp44 = NULL;
    PrtFreeValue(PTMP_tmp45); PTMP_tmp45 = NULL;
    PrtFreeValue(PTMP_tmp46); PTMP_tmp46 = NULL;
    PrtFreeValue(PTMP_tmp47); PTMP_tmp47 = NULL;
    PrtFreeValue(PTMP_tmp48); PTMP_tmp48 = NULL;
    PrtFreeValue(PTMP_tmp49); PTMP_tmp49 = NULL;
    PrtFreeValue(PTMP_tmp50); PTMP_tmp50 = NULL;
    PrtFreeValue(PTMP_tmp51); PTMP_tmp51 = NULL;
    PrtFreeValue(PTMP_tmp52); PTMP_tmp52 = NULL;
    PrtFreeValue(PTMP_tmp53); PTMP_tmp53 = NULL;
    PrtFreeValue(PTMP_tmp54); PTMP_tmp54 = NULL;
    PrtFreeValue(PTMP_tmp55); PTMP_tmp55 = NULL;
    PrtFreeValue(PTMP_tmp56); PTMP_tmp56 = NULL;
    PrtFreeValue(PTMP_tmp57); PTMP_tmp57 = NULL;
    PrtFreeValue(PTMP_tmp58); PTMP_tmp58 = NULL;
    PrtFreeValue(PTMP_tmp59); PTMP_tmp59 = NULL;
    PrtFreeValue(PTMP_tmp60); PTMP_tmp60 = NULL;
    PrtFreeValue(PTMP_tmp61); PTMP_tmp61 = NULL;
    PrtFreeValue(PTMP_tmp62); PTMP_tmp62 = NULL;
    PrtFreeValue(PTMP_tmp63); PTMP_tmp63 = NULL;
    PrtFreeValue(PTMP_tmp64); PTMP_tmp64 = NULL;
    PrtFreeValue(PTMP_tmp65); PTMP_tmp65 = NULL;
    PrtFreeValue(PTMP_tmp66); PTMP_tmp66 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_HeartbeatSendAsLeader =
{
    "HeartbeatSendAsLeader",
    &P_HeartbeatSendAsLeader_IMPL,
    NULL
};


PRT_VALUE* P_VoteAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_13 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_62 = NULL;
    PRT_VALUE* PTMP_tmp1_51 = NULL;
    PRT_VALUE* PTMP_tmp2_44 = NULL;
    PRT_VALUE* PTMP_tmp3_39 = NULL;
    PRT_VALUE* PTMP_tmp4_32 = NULL;
    PRT_VALUE* PTMP_tmp5_24 = NULL;
    PRT_VALUE* PTMP_tmp6_23 = NULL;
    PRT_VALUE* PTMP_tmp7_21 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_679 = &(PTMP_tmp0_62);
    PrtFreeValue(*P_LVALUE_679);
    *P_LVALUE_679 = PrtTupleGet(*P_VAR_request_13, 0);
    
    PRT_VALUE** P_LVALUE_680 = &(PTMP_tmp1_51);
    PrtFreeValue(*P_LVALUE_680);
    *P_LVALUE_680 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_62) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp1_51))
    {
        PRT_VALUE** P_LVALUE_681 = &(PTMP_tmp2_44);
        PrtFreeValue(*P_LVALUE_681);
        *P_LVALUE_681 = PrtTupleGet(*P_VAR_request_13, 0);
        
        PrtFormatPrintf("[Leader | VoteAsLeader] Leader ", 3, (p_this->id), p_this->varValues[3], PTMP_tmp2_44, 3, 0, " term ", 1, " behind request term ", 2, ".");
        
        PRT_VALUE** P_LVALUE_682 = &(PTMP_tmp3_39);
        PrtFreeValue(*P_LVALUE_682);
        *P_LVALUE_682 = PrtTupleGet(*P_VAR_request_13, 0);
        
        {
            PRT_VALUE** P_LVALUE_683 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_683);
            *P_LVALUE_683 = PTMP_tmp3_39;
            PTMP_tmp3_39 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_684 = &(PTMP_tmp4_32);
        PrtFreeValue(*P_LVALUE_684);
        *P_LVALUE_684 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_685 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_685);
            *P_LVALUE_685 = PTMP_tmp4_32;
            PTMP_tmp4_32 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_686 = &(PTMP_tmp5_24);
        PrtFreeValue(*P_LVALUE_686);
        *P_LVALUE_686 = PrtCloneValue(*P_VAR_request_13);
        
        _P_GEN_funargs[0] = &(PTMP_tmp5_24);
        PrtFreeValue(P_Vote_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp5_24);
        PTMP_tmp5_24 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_65;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_65;
        }
        
        PRT_VALUE** P_LVALUE_687 = &(PTMP_tmp6_23);
        PrtFreeValue(*P_LVALUE_687);
        *P_LVALUE_687 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
        
        PrtRaise(p_this, PTMP_tmp6_23, 0);
        *(&(PTMP_tmp6_23)) = NULL;
        goto p_return_65;
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_688 = &(PTMP_tmp7_21);
        PrtFreeValue(*P_LVALUE_688);
        *P_LVALUE_688 = PrtCloneValue(*P_VAR_request_13);
        
        _P_GEN_funargs[0] = &(PTMP_tmp7_21);
        PrtFreeValue(P_Vote_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp7_21);
        PTMP_tmp7_21 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_65;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_65;
        }
        
    }
    
    
p_return_65: ;
    PrtFreeValue(PTMP_tmp0_62); PTMP_tmp0_62 = NULL;
    PrtFreeValue(PTMP_tmp1_51); PTMP_tmp1_51 = NULL;
    PrtFreeValue(PTMP_tmp2_44); PTMP_tmp2_44 = NULL;
    PrtFreeValue(PTMP_tmp3_39); PTMP_tmp3_39 = NULL;
    PrtFreeValue(PTMP_tmp4_32); PTMP_tmp4_32 = NULL;
    PrtFreeValue(PTMP_tmp5_24); PTMP_tmp5_24 = NULL;
    PrtFreeValue(PTMP_tmp6_23); PTMP_tmp6_23 = NULL;
    PrtFreeValue(PTMP_tmp7_21); PTMP_tmp7_21 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_VoteAsLeader =
{
    "VoteAsLeader",
    &P_VoteAsLeader_IMPL,
    NULL
};


PRT_VALUE* P_RespondVoteAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_14 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_63 = NULL;
    PRT_VALUE* PTMP_tmp1_52 = NULL;
    PRT_VALUE* PTMP_tmp2_45 = NULL;
    PRT_VALUE* PTMP_tmp3_40 = NULL;
    PRT_VALUE* PTMP_tmp4_33 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_689 = &(PTMP_tmp0_63);
    PrtFreeValue(*P_LVALUE_689);
    *P_LVALUE_689 = PrtTupleGet(*P_VAR_request_14, 0);
    
    PRT_VALUE** P_LVALUE_690 = &(PTMP_tmp1_52);
    PrtFreeValue(*P_LVALUE_690);
    *P_LVALUE_690 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_63) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp1_52))
    {
        PRT_VALUE** P_LVALUE_691 = &(PTMP_tmp2_45);
        PrtFreeValue(*P_LVALUE_691);
        *P_LVALUE_691 = PrtTupleGet(*P_VAR_request_14, 0);
        
        {
            PRT_VALUE** P_LVALUE_692 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_692);
            *P_LVALUE_692 = PTMP_tmp2_45;
            PTMP_tmp2_45 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_693 = &(PTMP_tmp3_40);
        PrtFreeValue(*P_LVALUE_693);
        *P_LVALUE_693 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_694 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_694);
            *P_LVALUE_694 = PTMP_tmp3_40;
            PTMP_tmp3_40 = NULL;
        }
        
        PrtFreeValue(P_RedirectLastClientRequestToClusterManager_IMPL(context, _P_GEN_funargs));
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_66;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_66;
        }
        
        PRT_VALUE** P_LVALUE_695 = &(PTMP_tmp4_33);
        PrtFreeValue(*P_LVALUE_695);
        *P_LVALUE_695 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
        
        PrtRaise(p_this, PTMP_tmp4_33, 0);
        *(&(PTMP_tmp4_33)) = NULL;
        goto p_return_66;
        
    }
    
    else
    {
    }
    
    
p_return_66: ;
    PrtFreeValue(PTMP_tmp0_63); PTMP_tmp0_63 = NULL;
    PrtFreeValue(PTMP_tmp1_52); PTMP_tmp1_52 = NULL;
    PrtFreeValue(PTMP_tmp2_45); PTMP_tmp2_45 = NULL;
    PrtFreeValue(PTMP_tmp3_40); PTMP_tmp3_40 = NULL;
    PrtFreeValue(PTMP_tmp4_33); PTMP_tmp4_33 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_RespondVoteAsLeader =
{
    "RespondVoteAsLeader",
    &P_RespondVoteAsLeader_IMPL,
    NULL
};


PRT_VALUE* P_AppendEntriesAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_15 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_64 = NULL;
    PRT_VALUE* PTMP_tmp1_53 = NULL;
    PRT_VALUE* PTMP_tmp2_46 = NULL;
    PRT_VALUE* PTMP_tmp3_41 = NULL;
    PRT_VALUE* PTMP_tmp4_34 = NULL;
    PRT_VALUE* PTMP_tmp5_25 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_696 = &(PTMP_tmp0_64);
    PrtFreeValue(*P_LVALUE_696);
    *P_LVALUE_696 = PrtTupleGet(*P_VAR_request_15, 0);
    
    PRT_VALUE** P_LVALUE_697 = &(PTMP_tmp1_53);
    PrtFreeValue(*P_LVALUE_697);
    *P_LVALUE_697 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_64) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp1_53))
    {
        PrtPrintf("AppendEntriesAsLeader");
        
        PRT_VALUE** P_LVALUE_698 = &(PTMP_tmp2_46);
        PrtFreeValue(*P_LVALUE_698);
        *P_LVALUE_698 = PrtTupleGet(*P_VAR_request_15, 0);
        
        {
            PRT_VALUE** P_LVALUE_699 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_699);
            *P_LVALUE_699 = PTMP_tmp2_46;
            PTMP_tmp2_46 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_700 = &(PTMP_tmp3_41);
        PrtFreeValue(*P_LVALUE_700);
        *P_LVALUE_700 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_701 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_701);
            *P_LVALUE_701 = PTMP_tmp3_41;
            PTMP_tmp3_41 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_702 = &(PTMP_tmp4_34);
        PrtFreeValue(*P_LVALUE_702);
        *P_LVALUE_702 = PrtCloneValue(*P_VAR_request_15);
        
        _P_GEN_funargs[0] = &(PTMP_tmp4_34);
        PrtFreeValue(P_AppendEntries_IMPL(context, _P_GEN_funargs));
        PrtFreeValue(PTMP_tmp4_34);
        PTMP_tmp4_34 = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_67;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_67;
        }
        
        PRT_VALUE** P_LVALUE_703 = &(PTMP_tmp5_25);
        PrtFreeValue(*P_LVALUE_703);
        *P_LVALUE_703 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
        
        PrtRaise(p_this, PTMP_tmp5_25, 0);
        *(&(PTMP_tmp5_25)) = NULL;
        goto p_return_67;
        
    }
    
    else
    {
    }
    
    
p_return_67: ;
    PrtFreeValue(PTMP_tmp0_64); PTMP_tmp0_64 = NULL;
    PrtFreeValue(PTMP_tmp1_53); PTMP_tmp1_53 = NULL;
    PrtFreeValue(PTMP_tmp2_46); PTMP_tmp2_46 = NULL;
    PrtFreeValue(PTMP_tmp3_41); PTMP_tmp3_41 = NULL;
    PrtFreeValue(PTMP_tmp4_34); PTMP_tmp4_34 = NULL;
    PrtFreeValue(PTMP_tmp5_25); PTMP_tmp5_25 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_AppendEntriesAsLeader =
{
    "AppendEntriesAsLeader",
    &P_AppendEntriesAsLeader_IMPL,
    NULL
};


PRT_VALUE* P_RespondAppendEntriesAsLeader_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_16 = argRefs[0];
    PRT_VALUE* P_VAR_logsAppend = PrtMkDefaultValue(&P_GEND_TYPE_ST3irr);
    PRT_VALUE* P_VAR_cfgLogsAppend = PrtMkDefaultValue(&P_GEND_TYPE_ST2iSm);
    PRT_VALUE* P_VAR_prevLogIndex_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_prevLogTerm_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_prevCfgLogIndex_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_prevCfgLogTerm_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_idx_9 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_cfgLogIdx_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_committedLogs = PrtMkDefaultValue(&P_GEND_TYPE_ST3irr);
    PRT_VALUE* PTMP_tmp0_65 = NULL;
    PRT_VALUE* PTMP_tmp1_54 = NULL;
    PRT_VALUE* PTMP_tmp2_47 = NULL;
    PRT_VALUE* PTMP_tmp3_42 = NULL;
    PRT_VALUE* PTMP_tmp4_35 = NULL;
    PRT_VALUE* PTMP_tmp5_26 = NULL;
    PRT_VALUE* PTMP_tmp6_24 = NULL;
    PRT_VALUE* PTMP_tmp7_22 = NULL;
    PRT_VALUE* PTMP_tmp8_19 = NULL;
    PRT_VALUE* PTMP_tmp9_16 = NULL;
    PRT_VALUE* PTMP_tmp10_15 = NULL;
    PRT_VALUE* PTMP_tmp11_15 = NULL;
    PRT_VALUE* PTMP_tmp12_14 = NULL;
    PRT_VALUE* PTMP_tmp13_13 = NULL;
    PRT_VALUE* PTMP_tmp14_12 = NULL;
    PRT_VALUE* PTMP_tmp15_9 = NULL;
    PRT_VALUE* PTMP_tmp16_8 = NULL;
    PRT_VALUE* PTMP_tmp17_6 = NULL;
    PRT_VALUE* PTMP_tmp18_6 = NULL;
    PRT_VALUE* PTMP_tmp19_6 = NULL;
    PRT_VALUE* PTMP_tmp20_6 = NULL;
    PRT_VALUE* PTMP_tmp21_6 = NULL;
    PRT_VALUE* PTMP_tmp22_6 = NULL;
    PRT_VALUE* PTMP_tmp23_5 = NULL;
    PRT_VALUE* PTMP_tmp24_4 = NULL;
    PRT_VALUE* PTMP_tmp25_4 = NULL;
    PRT_VALUE* PTMP_tmp26_4 = NULL;
    PRT_VALUE* PTMP_tmp27_4 = NULL;
    PRT_VALUE* PTMP_tmp28_4 = NULL;
    PRT_VALUE* PTMP_tmp29_4 = NULL;
    PRT_VALUE* PTMP_tmp30_3 = NULL;
    PRT_VALUE* PTMP_tmp31_2 = NULL;
    PRT_VALUE* PTMP_tmp32_2 = NULL;
    PRT_VALUE* PTMP_tmp33_2 = NULL;
    PRT_VALUE* PTMP_tmp34_2 = NULL;
    PRT_VALUE* PTMP_tmp35_2 = NULL;
    PRT_VALUE* PTMP_tmp36_1 = NULL;
    PRT_VALUE* PTMP_tmp37_1 = NULL;
    PRT_VALUE* PTMP_tmp38_1 = NULL;
    PRT_VALUE* PTMP_tmp39_1 = NULL;
    PRT_VALUE* PTMP_tmp40_1 = NULL;
    PRT_VALUE* PTMP_tmp41_1 = NULL;
    PRT_VALUE* PTMP_tmp42_1 = NULL;
    PRT_VALUE* PTMP_tmp43_1 = NULL;
    PRT_VALUE* PTMP_tmp44_1 = NULL;
    PRT_VALUE* PTMP_tmp45_1 = NULL;
    PRT_VALUE* PTMP_tmp46_1 = NULL;
    PRT_VALUE* PTMP_tmp47_1 = NULL;
    PRT_VALUE* PTMP_tmp48_1 = NULL;
    PRT_VALUE* PTMP_tmp49_1 = NULL;
    PRT_VALUE* PTMP_tmp50_1 = NULL;
    PRT_VALUE* PTMP_tmp51_1 = NULL;
    PRT_VALUE* PTMP_tmp52_1 = NULL;
    PRT_VALUE* PTMP_tmp53_1 = NULL;
    PRT_VALUE* PTMP_tmp54_1 = NULL;
    PRT_VALUE* PTMP_tmp55_1 = NULL;
    PRT_VALUE* PTMP_tmp56_1 = NULL;
    PRT_VALUE* PTMP_tmp57_1 = NULL;
    PRT_VALUE* PTMP_tmp58_1 = NULL;
    PRT_VALUE* PTMP_tmp59_1 = NULL;
    PRT_VALUE* PTMP_tmp60_1 = NULL;
    PRT_VALUE* PTMP_tmp61_1 = NULL;
    PRT_VALUE* PTMP_tmp62_1 = NULL;
    PRT_VALUE* PTMP_tmp63_1 = NULL;
    PRT_VALUE* PTMP_tmp64_1 = NULL;
    PRT_VALUE* PTMP_tmp65_1 = NULL;
    PRT_VALUE* PTMP_tmp66_1 = NULL;
    PRT_VALUE* PTMP_tmp67 = NULL;
    PRT_VALUE* PTMP_tmp68 = NULL;
    PRT_VALUE* PTMP_tmp69 = NULL;
    PRT_VALUE* PTMP_tmp70 = NULL;
    PRT_VALUE* PTMP_tmp71 = NULL;
    PRT_VALUE* PTMP_tmp72 = NULL;
    PRT_VALUE* PTMP_tmp73 = NULL;
    PRT_VALUE* PTMP_tmp74 = NULL;
    PRT_VALUE* PTMP_tmp75 = NULL;
    PRT_VALUE* PTMP_tmp76 = NULL;
    PRT_VALUE* PTMP_tmp77 = NULL;
    PRT_VALUE* PTMP_tmp78 = NULL;
    PRT_VALUE* PTMP_tmp79 = NULL;
    PRT_VALUE* PTMP_tmp80 = NULL;
    PRT_VALUE* PTMP_tmp81 = NULL;
    PRT_VALUE* PTMP_tmp82 = NULL;
    PRT_VALUE* PTMP_tmp83 = NULL;
    PRT_VALUE* PTMP_tmp84 = NULL;
    PRT_VALUE* PTMP_tmp85 = NULL;
    PRT_VALUE* PTMP_tmp86 = NULL;
    PRT_VALUE* PTMP_tmp87 = NULL;
    PRT_VALUE* PTMP_tmp88 = NULL;
    PRT_VALUE* PTMP_tmp89 = NULL;
    PRT_VALUE* PTMP_tmp90 = NULL;
    PRT_VALUE* PTMP_tmp91 = NULL;
    PRT_VALUE* PTMP_tmp92 = NULL;
    PRT_VALUE* PTMP_tmp93 = NULL;
    PRT_VALUE* PTMP_tmp94 = NULL;
    PRT_VALUE* PTMP_tmp95 = NULL;
    PRT_VALUE* PTMP_tmp96 = NULL;
    PRT_VALUE* PTMP_tmp97 = NULL;
    PRT_VALUE* PTMP_tmp98 = NULL;
    PRT_VALUE* PTMP_tmp99 = NULL;
    PRT_VALUE* PTMP_tmp100 = NULL;
    PRT_VALUE* PTMP_tmp101 = NULL;
    PRT_VALUE* PTMP_tmp102 = NULL;
    PRT_VALUE* PTMP_tmp103 = NULL;
    PRT_VALUE* PTMP_tmp104 = NULL;
    PRT_VALUE* PTMP_tmp105 = NULL;
    PRT_VALUE* PTMP_tmp106 = NULL;
    PRT_VALUE* PTMP_tmp107 = NULL;
    PRT_VALUE* PTMP_tmp108 = NULL;
    PRT_VALUE* PTMP_tmp109 = NULL;
    PRT_VALUE* PTMP_tmp110 = NULL;
    PRT_VALUE* PTMP_tmp111 = NULL;
    PRT_VALUE* PTMP_tmp112 = NULL;
    PRT_VALUE* PTMP_tmp113 = NULL;
    PRT_VALUE* PTMP_tmp114 = NULL;
    PRT_VALUE* PTMP_tmp115 = NULL;
    PRT_VALUE* PTMP_tmp116 = NULL;
    PRT_VALUE* PTMP_tmp117 = NULL;
    PRT_VALUE* PTMP_tmp118 = NULL;
    PRT_VALUE* PTMP_tmp119 = NULL;
    PRT_VALUE* PTMP_tmp120 = NULL;
    PRT_VALUE* PTMP_tmp121 = NULL;
    PRT_VALUE* PTMP_tmp122 = NULL;
    PRT_VALUE* PTMP_tmp123 = NULL;
    PRT_VALUE* PTMP_tmp124 = NULL;
    PRT_VALUE* PTMP_tmp125 = NULL;
    PRT_VALUE* PTMP_tmp126 = NULL;
    PRT_VALUE* PTMP_tmp127 = NULL;
    PRT_VALUE* PTMP_tmp128 = NULL;
    PRT_VALUE* PTMP_tmp129 = NULL;
    PRT_VALUE* PTMP_tmp130 = NULL;
    PRT_VALUE* PTMP_tmp131 = NULL;
    PRT_VALUE* PTMP_tmp132 = NULL;
    PRT_VALUE* PTMP_tmp133 = NULL;
    PRT_VALUE* PTMP_tmp134 = NULL;
    PRT_VALUE* PTMP_tmp135 = NULL;
    PRT_VALUE* PTMP_tmp136 = NULL;
    PRT_VALUE* PTMP_tmp137 = NULL;
    PRT_VALUE* PTMP_tmp138 = NULL;
    PRT_VALUE* PTMP_tmp139 = NULL;
    PRT_VALUE* PTMP_tmp140 = NULL;
    PRT_VALUE* PTMP_tmp141 = NULL;
    PRT_VALUE* PTMP_tmp142 = NULL;
    PRT_VALUE* PTMP_tmp143 = NULL;
    PRT_VALUE* PTMP_tmp144 = NULL;
    PRT_VALUE* PTMP_tmp145 = NULL;
    PRT_VALUE* PTMP_tmp146 = NULL;
    PRT_VALUE* PTMP_tmp147 = NULL;
    PRT_VALUE* PTMP_tmp148 = NULL;
    PRT_VALUE* PTMP_tmp149 = NULL;
    PRT_VALUE* PTMP_tmp150 = NULL;
    PRT_VALUE* PTMP_tmp151 = NULL;
    PRT_VALUE* PTMP_tmp152 = NULL;
    PRT_VALUE* PTMP_tmp153 = NULL;
    PRT_VALUE* PTMP_tmp154 = NULL;
    PRT_VALUE* PTMP_tmp155 = NULL;
    PRT_VALUE* PTMP_tmp156 = NULL;
    PRT_VALUE* PTMP_tmp157 = NULL;
    PRT_VALUE* PTMP_tmp158 = NULL;
    PRT_VALUE* PTMP_tmp159 = NULL;
    PRT_VALUE* PTMP_tmp160 = NULL;
    PRT_VALUE* PTMP_tmp161 = NULL;
    PRT_VALUE* PTMP_tmp162 = NULL;
    PRT_VALUE* PTMP_tmp163 = NULL;
    PRT_VALUE* PTMP_tmp164 = NULL;
    PRT_VALUE* PTMP_tmp165 = NULL;
    PRT_VALUE* PTMP_tmp166 = NULL;
    PRT_VALUE* PTMP_tmp167 = NULL;
    PRT_VALUE* PTMP_tmp168 = NULL;
    PRT_VALUE* PTMP_tmp169 = NULL;
    PRT_VALUE* PTMP_tmp170 = NULL;
    PRT_VALUE* PTMP_tmp171 = NULL;
    PRT_VALUE* PTMP_tmp172 = NULL;
    PRT_VALUE* PTMP_tmp173 = NULL;
    PRT_VALUE* PTMP_tmp174 = NULL;
    PRT_VALUE* PTMP_tmp175 = NULL;
    PRT_VALUE* PTMP_tmp176 = NULL;
    PRT_VALUE* PTMP_tmp177 = NULL;
    PRT_VALUE* PTMP_tmp178 = NULL;
    PRT_VALUE* PTMP_tmp179 = NULL;
    PRT_VALUE* PTMP_tmp180 = NULL;
    PRT_VALUE* PTMP_tmp181 = NULL;
    PRT_VALUE* PTMP_tmp182 = NULL;
    PRT_VALUE* PTMP_tmp183 = NULL;
    PRT_VALUE* PTMP_tmp184 = NULL;
    PRT_VALUE* PTMP_tmp185 = NULL;
    PRT_VALUE* PTMP_tmp186 = NULL;
    PRT_VALUE* PTMP_tmp187 = NULL;
    PRT_VALUE* PTMP_tmp188 = NULL;
    PRT_VALUE* PTMP_tmp189 = NULL;
    PRT_VALUE* PTMP_tmp190 = NULL;
    PRT_VALUE* PTMP_tmp191 = NULL;
    PRT_VALUE* PTMP_tmp192 = NULL;
    PRT_VALUE* PTMP_tmp193 = NULL;
    PRT_VALUE* PTMP_tmp194 = NULL;
    PRT_VALUE* PTMP_tmp195 = NULL;
    PRT_VALUE* PTMP_tmp196 = NULL;
    PRT_VALUE* PTMP_tmp197 = NULL;
    PRT_VALUE* PTMP_tmp198 = NULL;
    PRT_VALUE* PTMP_tmp199 = NULL;
    PRT_VALUE* PTMP_tmp200 = NULL;
    PRT_VALUE* PTMP_tmp201 = NULL;
    PRT_VALUE* PTMP_tmp202 = NULL;
    PRT_VALUE* PTMP_tmp203 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_49 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_INT32_50 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_51 = { PRT_VALUE_KIND_INT, { .nt = 2 } };
    PRT_VALUE P_LIT_BOOLEAN_26 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE P_LIT_BOOLEAN_27 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_704 = &(PTMP_tmp0_65);
    PrtFreeValue(*P_LVALUE_704);
    *P_LVALUE_704 = PrtTupleGet(*P_VAR_request_16, 1);
    
    PRT_VALUE** P_LVALUE_705 = &(PTMP_tmp1_54);
    PrtFreeValue(*P_LVALUE_705);
    *P_LVALUE_705 = PrtTupleGet(*P_VAR_request_16, 4);
    
    PrtFormatPrintf("[Leader | AppendEntriesResponse] ", 3, (p_this->id), PTMP_tmp0_65, PTMP_tmp1_54, 3, 0, " received response ", 1, " from server ", 2, "");
    
    PRT_VALUE** P_LVALUE_706 = &(PTMP_tmp2_47);
    PrtFreeValue(*P_LVALUE_706);
    *P_LVALUE_706 = PrtTupleGet(*P_VAR_request_16, 0);
    
    PrtFormatPrintf("[Leader | AppendEntriesResponse] Leader term: ", 2, p_this->varValues[3], PTMP_tmp2_47, 2, 0, ", follower term: ", 1, "");
    
    PRT_VALUE** P_LVALUE_707 = &(PTMP_tmp3_42);
    PrtFreeValue(*P_LVALUE_707);
    *P_LVALUE_707 = PrtTupleGet(*P_VAR_request_16, 0);
    
    PRT_VALUE** P_LVALUE_708 = &(PTMP_tmp4_35);
    PrtFreeValue(*P_LVALUE_708);
    *P_LVALUE_708 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp3_42) > PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp4_35))
    {
        PRT_VALUE** P_LVALUE_709 = &(PTMP_tmp5_26);
        PrtFreeValue(*P_LVALUE_709);
        *P_LVALUE_709 = PrtTupleGet(*P_VAR_request_16, 0);
        
        {
            PRT_VALUE** P_LVALUE_710 = &(p_this->varValues[3]);
            PrtFreeValue(*P_LVALUE_710);
            *P_LVALUE_710 = PTMP_tmp5_26;
            PTMP_tmp5_26 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_711 = &(PTMP_tmp6_24);
        PrtFreeValue(*P_LVALUE_711);
        *P_LVALUE_711 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_712 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_712);
            *P_LVALUE_712 = PTMP_tmp6_24;
            PTMP_tmp6_24 = NULL;
        }
        
        PrtFreeValue(P_RedirectLastClientRequestToClusterManager_IMPL(context, _P_GEN_funargs));
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_68;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_68;
        }
        
        PRT_VALUE** P_LVALUE_713 = &(PTMP_tmp7_22);
        PrtFreeValue(*P_LVALUE_713);
        *P_LVALUE_713 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
        
        PrtRaise(p_this, PTMP_tmp7_22, 0);
        *(&(PTMP_tmp7_22)) = NULL;
        goto p_return_68;
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_714 = &(PTMP_tmp8_19);
        PrtFreeValue(*P_LVALUE_714);
        *P_LVALUE_714 = PrtTupleGet(*P_VAR_request_16, 0);
        
        PRT_VALUE** P_LVALUE_715 = &(PTMP_tmp9_16);
        PrtFreeValue(*P_LVALUE_715);
        *P_LVALUE_715 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp8_19) < PrtPrimGetInt(p_this->varValues[3]));
        
        if (PrtPrimGetBool(PTMP_tmp9_16))
        {
        }
        
        else
        {
            PRT_VALUE** P_LVALUE_716 = &(PTMP_tmp10_15);
            PrtFreeValue(*P_LVALUE_716);
            *P_LVALUE_716 = PrtTupleGet(*P_VAR_request_16, 1);
            
            if (PrtPrimGetBool(PTMP_tmp10_15))
            {
                PrtPrintf("[Leader | AppendEntriesResponse] Success");
                
                PRT_VALUE** P_LVALUE_717 = &(PTMP_tmp11_15);
                PrtFreeValue(*P_LVALUE_717);
                *P_LVALUE_717 = PrtTupleGet(*P_VAR_request_16, 2);
                
                if (PrtPrimGetBool(PTMP_tmp11_15))
                {
                    PRT_VALUE** P_LVALUE_718 = &(PTMP_tmp12_14);
                    PrtFreeValue(*P_LVALUE_718);
                    *P_LVALUE_718 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_719 = &(PTMP_tmp13_13);
                    PrtFreeValue(*P_LVALUE_719);
                    *P_LVALUE_719 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                    
                    {
                        PRT_VALUE** P_LVALUE_720 = &(*(PrtTupleGetLValue(*(PrtMapGetLValue(p_this->varValues[9], PTMP_tmp12_14, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)), 0)));
                        PrtFreeValue(*P_LVALUE_720);
                        *P_LVALUE_720 = PTMP_tmp13_13;
                        PTMP_tmp13_13 = NULL;
                    }
                    
                    PRT_VALUE** P_LVALUE_721 = &(PTMP_tmp14_12);
                    PrtFreeValue(*P_LVALUE_721);
                    *P_LVALUE_721 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_722 = &(PTMP_tmp15_9);
                    PrtFreeValue(*P_LVALUE_722);
                    *P_LVALUE_722 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                    
                    PRT_VALUE** P_LVALUE_723 = &(PTMP_tmp16_8);
                    PrtFreeValue(*P_LVALUE_723);
                    *P_LVALUE_723 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp15_9) - PrtPrimGetInt((&P_LIT_INT32_49)));
                    
                    {
                        PRT_VALUE** P_LVALUE_724 = &(*(PrtTupleGetLValue(*(PrtMapGetLValue(p_this->varValues[10], PTMP_tmp14_12, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)), 0)));
                        PrtFreeValue(*P_LVALUE_724);
                        *P_LVALUE_724 = PTMP_tmp16_8;
                        PTMP_tmp16_8 = NULL;
                    }
                    
                }
                
                else
                {
                }
                
                
                PRT_VALUE** P_LVALUE_725 = &(PTMP_tmp17_6);
                PrtFreeValue(*P_LVALUE_725);
                *P_LVALUE_725 = PrtTupleGet(*P_VAR_request_16, 3);
                
                if (PrtPrimGetBool(PTMP_tmp17_6))
                {
                    PRT_VALUE** P_LVALUE_726 = &(PTMP_tmp18_6);
                    PrtFreeValue(*P_LVALUE_726);
                    *P_LVALUE_726 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_727 = &(PTMP_tmp19_6);
                    PrtFreeValue(*P_LVALUE_727);
                    *P_LVALUE_727 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                    
                    {
                        PRT_VALUE** P_LVALUE_728 = &(*(PrtTupleGetLValue(*(PrtMapGetLValue(p_this->varValues[9], PTMP_tmp18_6, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)), 1)));
                        PrtFreeValue(*P_LVALUE_728);
                        *P_LVALUE_728 = PTMP_tmp19_6;
                        PTMP_tmp19_6 = NULL;
                    }
                    
                    PRT_VALUE** P_LVALUE_729 = &(PTMP_tmp20_6);
                    PrtFreeValue(*P_LVALUE_729);
                    *P_LVALUE_729 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_730 = &(PTMP_tmp21_6);
                    PrtFreeValue(*P_LVALUE_730);
                    *P_LVALUE_730 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                    
                    PRT_VALUE** P_LVALUE_731 = &(PTMP_tmp22_6);
                    PrtFreeValue(*P_LVALUE_731);
                    *P_LVALUE_731 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp21_6) - PrtPrimGetInt((&P_LIT_INT32_49)));
                    
                    {
                        PRT_VALUE** P_LVALUE_732 = &(*(PrtTupleGetLValue(*(PrtMapGetLValue(p_this->varValues[10], PTMP_tmp20_6, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)), 1)));
                        PrtFreeValue(*P_LVALUE_732);
                        *P_LVALUE_732 = PTMP_tmp22_6;
                        PTMP_tmp22_6 = NULL;
                    }
                    
                }
                
                else
                {
                }
                
                
                PRT_VALUE** P_LVALUE_733 = &(PTMP_tmp23_5);
                PrtFreeValue(*P_LVALUE_733);
                *P_LVALUE_733 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_734 = &(PTMP_tmp24_4);
                PrtFreeValue(*P_LVALUE_734);
                *P_LVALUE_734 = PrtMapGet(p_this->varValues[9], PTMP_tmp23_5);
                
                PRT_VALUE** P_LVALUE_735 = &(PTMP_tmp25_4);
                PrtFreeValue(*P_LVALUE_735);
                *P_LVALUE_735 = PrtTupleGet(PTMP_tmp24_4, 0);
                
                PRT_VALUE** P_LVALUE_736 = &(PTMP_tmp26_4);
                PrtFreeValue(*P_LVALUE_736);
                *P_LVALUE_736 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_737 = &(PTMP_tmp27_4);
                PrtFreeValue(*P_LVALUE_737);
                *P_LVALUE_737 = PrtMapGet(p_this->varValues[10], PTMP_tmp26_4);
                
                PRT_VALUE** P_LVALUE_738 = &(PTMP_tmp28_4);
                PrtFreeValue(*P_LVALUE_738);
                *P_LVALUE_738 = PrtTupleGet(PTMP_tmp27_4, 0);
                
                PrtFormatPrintf("[Leader | AppendEntriesResponse] Updated KV Indices: NextIndex: ", 2, PTMP_tmp25_4, PTMP_tmp28_4, 2, 0, ", MatchIndex: ", 1, "");
                
                PRT_VALUE** P_LVALUE_739 = &(PTMP_tmp29_4);
                PrtFreeValue(*P_LVALUE_739);
                *P_LVALUE_739 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[11]) + PrtPrimGetInt((&P_LIT_INT32_49)));
                
                {
                    PRT_VALUE** P_LVALUE_740 = &(p_this->varValues[11]);
                    PrtFreeValue(*P_LVALUE_740);
                    *P_LVALUE_740 = PTMP_tmp29_4;
                    PTMP_tmp29_4 = NULL;
                }
                
                PrtFormatPrintf("[Leader | AppendEntriesResponse] VotesReceived: ", 1, p_this->varValues[11], 1, 0, "");
                
                PRT_VALUE** P_LVALUE_741 = &(PTMP_tmp30_3);
                PrtFreeValue(*P_LVALUE_741);
                *P_LVALUE_741 = PrtTupleGet(*P_VAR_request_16, 5);
                
                PRT_VALUE** P_LVALUE_742 = &(PTMP_tmp31_2);
                PrtFreeValue(*P_LVALUE_742);
                *P_LVALUE_742 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp30_3, (&_P_GEN_null)));
                
                if (PrtPrimGetBool(PTMP_tmp31_2))
                {
                    PRT_VALUE** P_LVALUE_743 = &(PTMP_tmp32_2);
                    PrtFreeValue(*P_LVALUE_743);
                    *P_LVALUE_743 = PrtTupleGet(*P_VAR_request_16, 3);
                    
                    PRT_VALUE** P_LVALUE_744 = &(PTMP_tmp33_2);
                    PrtFreeValue(*P_LVALUE_744);
                    *P_LVALUE_744 = PrtMkBoolValue(!PrtPrimGetBool(PTMP_tmp32_2));
                    
                    if (PrtPrimGetBool(PTMP_tmp33_2))
                    {
                        PRT_VALUE** P_LVALUE_745 = &(p_this->varValues[11]);
                        PrtFreeValue(*P_LVALUE_745);
                        *P_LVALUE_745 = PrtCloneValue((&P_LIT_INT32_50));
                        
                    }
                    
                    else
                    {
                    }
                    
                    
                    PrtPrintf("[Leader | AppendEntriesResponse] request.ReceiverEndpoint: null");
                    
                    goto p_return_68;
                    
                }
                
                else
                {
                    PRT_VALUE** P_LVALUE_746 = &(PTMP_tmp34_2);
                    PrtFreeValue(*P_LVALUE_746);
                    *P_LVALUE_746 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[1]));
                    
                    PRT_VALUE** P_LVALUE_747 = &(PTMP_tmp35_2);
                    PrtFreeValue(*P_LVALUE_747);
                    *P_LVALUE_747 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp34_2) - PrtPrimGetInt((&P_LIT_INT32_49)));
                    
                    PRT_VALUE** P_LVALUE_748 = &(PTMP_tmp36_1);
                    PrtFreeValue(*P_LVALUE_748);
                    *P_LVALUE_748 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp35_2) / PrtPrimGetInt((&P_LIT_INT32_51)));
                    
                    PRT_VALUE** P_LVALUE_749 = &(PTMP_tmp37_1);
                    PrtFreeValue(*P_LVALUE_749);
                    *P_LVALUE_749 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[11]) > PrtPrimGetInt(PTMP_tmp36_1));
                    
                    if (PrtPrimGetBool(PTMP_tmp37_1))
                    {
                        PrtFormatPrintf("\n[Leader] ", 3, (p_this->id), p_this->varValues[3], p_this->varValues[11], 3, 0, " | term ", 1, " | append votes ", 2, " | append success\n");
                        
                        PRT_VALUE** P_LVALUE_750 = &(PTMP_tmp38_1);
                        PrtFreeValue(*P_LVALUE_750);
                        *P_LVALUE_750 = PrtTupleGet(*P_VAR_request_16, 2);
                        
                        PRT_VALUE** P_LVALUE_751 = &(PTMP_tmp44_1);
                        PrtFreeValue(*P_LVALUE_751);
                        *P_LVALUE_751 = PrtCloneValue(PTMP_tmp38_1);
                        
                        if (PrtPrimGetBool(PTMP_tmp44_1))
                        {
                            PRT_VALUE** P_LVALUE_752 = &(PTMP_tmp39_1);
                            PrtFreeValue(*P_LVALUE_752);
                            *P_LVALUE_752 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_753 = &(PTMP_tmp40_1);
                            PrtFreeValue(*P_LVALUE_753);
                            *P_LVALUE_753 = PrtMapGet(p_this->varValues[10], PTMP_tmp39_1);
                            
                            PRT_VALUE** P_LVALUE_754 = &(PTMP_tmp41_1);
                            PrtFreeValue(*P_LVALUE_754);
                            *P_LVALUE_754 = PrtTupleGet(PTMP_tmp40_1, 0);
                            
                            PRT_VALUE** P_LVALUE_755 = &(PTMP_tmp42_1);
                            PrtFreeValue(*P_LVALUE_755);
                            *P_LVALUE_755 = PrtTupleGet(p_this->varValues[8], 0);
                            
                            PRT_VALUE** P_LVALUE_756 = &(PTMP_tmp43_1);
                            PrtFreeValue(*P_LVALUE_756);
                            *P_LVALUE_756 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp41_1) > PrtPrimGetInt(PTMP_tmp42_1));
                            
                            PRT_VALUE** P_LVALUE_757 = &(PTMP_tmp44_1);
                            PrtFreeValue(*P_LVALUE_757);
                            *P_LVALUE_757 = PrtCloneValue(PTMP_tmp43_1);
                            
                        }
                        
                        
                        PRT_VALUE** P_LVALUE_758 = &(PTMP_tmp52_1);
                        PrtFreeValue(*P_LVALUE_758);
                        *P_LVALUE_758 = PrtCloneValue(PTMP_tmp44_1);
                        
                        if (PrtPrimGetBool(PTMP_tmp52_1))
                        {
                            PRT_VALUE** P_LVALUE_759 = &(PTMP_tmp45_1);
                            PrtFreeValue(*P_LVALUE_759);
                            *P_LVALUE_759 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_760 = &(PTMP_tmp46_1);
                            PrtFreeValue(*P_LVALUE_760);
                            *P_LVALUE_760 = PrtMapGet(p_this->varValues[10], PTMP_tmp45_1);
                            
                            PRT_VALUE** P_LVALUE_761 = &(PTMP_tmp47_1);
                            PrtFreeValue(*P_LVALUE_761);
                            *P_LVALUE_761 = PrtTupleGet(PTMP_tmp46_1, 0);
                            
                            PRT_VALUE** P_LVALUE_762 = &(PTMP_tmp48_1);
                            PrtFreeValue(*P_LVALUE_762);
                            *P_LVALUE_762 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp47_1) - PrtPrimGetInt((&P_LIT_INT32_49)));
                            
                            PRT_VALUE** P_LVALUE_763 = &(PTMP_tmp49_1);
                            PrtFreeValue(*P_LVALUE_763);
                            *P_LVALUE_763 = PrtSeqGet(p_this->varValues[5], PTMP_tmp48_1);
                            
                            PRT_VALUE** P_LVALUE_764 = &(PTMP_tmp50_1);
                            PrtFreeValue(*P_LVALUE_764);
                            *P_LVALUE_764 = PrtTupleGet(PTMP_tmp49_1, 0);
                            
                            PRT_VALUE** P_LVALUE_765 = &(PTMP_tmp51_1);
                            PrtFreeValue(*P_LVALUE_765);
                            *P_LVALUE_765 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp50_1, p_this->varValues[3]));
                            
                            PRT_VALUE** P_LVALUE_766 = &(PTMP_tmp52_1);
                            PrtFreeValue(*P_LVALUE_766);
                            *P_LVALUE_766 = PrtCloneValue(PTMP_tmp51_1);
                            
                        }
                        
                        
                        if (PrtPrimGetBool(PTMP_tmp52_1))
                        {
                            PRT_VALUE** P_LVALUE_767 = &(PTMP_tmp53_1);
                            PrtFreeValue(*P_LVALUE_767);
                            *P_LVALUE_767 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_768 = &(PTMP_tmp54_1);
                            PrtFreeValue(*P_LVALUE_768);
                            *P_LVALUE_768 = PrtMapGet(p_this->varValues[10], PTMP_tmp53_1);
                            
                            PRT_VALUE** P_LVALUE_769 = &(PTMP_tmp55_1);
                            PrtFreeValue(*P_LVALUE_769);
                            *P_LVALUE_769 = PrtTupleGet(PTMP_tmp54_1, 0);
                            
                            {
                                PRT_VALUE** P_LVALUE_770 = &(*(PrtTupleGetLValue(p_this->varValues[8], 0)));
                                PrtFreeValue(*P_LVALUE_770);
                                *P_LVALUE_770 = PTMP_tmp55_1;
                                PTMP_tmp55_1 = NULL;
                            }
                            
                            PRT_VALUE** P_LVALUE_771 = &(PTMP_tmp56_1);
                            PrtFreeValue(*P_LVALUE_771);
                            *P_LVALUE_771 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                            
                            PRT_VALUE** P_LVALUE_772 = &(PTMP_tmp57_1);
                            PrtFreeValue(*P_LVALUE_772);
                            *P_LVALUE_772 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_773 = &(PTMP_tmp58_1);
                            PrtFreeValue(*P_LVALUE_773);
                            *P_LVALUE_773 = PrtMapGet(p_this->varValues[10], PTMP_tmp57_1);
                            
                            PRT_VALUE** P_LVALUE_774 = &(PTMP_tmp59_1);
                            PrtFreeValue(*P_LVALUE_774);
                            *P_LVALUE_774 = PrtTupleGet(PTMP_tmp58_1, 0);
                            
                            PRT_VALUE** P_LVALUE_775 = &(PTMP_tmp60_1);
                            PrtFreeValue(*P_LVALUE_775);
                            *P_LVALUE_775 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp59_1) - PrtPrimGetInt((&P_LIT_INT32_49)));
                            
                            PRT_VALUE** P_LVALUE_776 = &(PTMP_tmp61_1);
                            PrtFreeValue(*P_LVALUE_776);
                            *P_LVALUE_776 = PrtSeqGet(p_this->varValues[5], PTMP_tmp60_1);
                            
                            PRT_VALUE** P_LVALUE_777 = &(PTMP_tmp62_1);
                            PrtFreeValue(*P_LVALUE_777);
                            *P_LVALUE_777 = PrtTupleGet(PTMP_tmp61_1, 1);
                            
                            PRT_VALUE** P_LVALUE_778 = &(PTMP_tmp63_1);
                            PrtFreeValue(*P_LVALUE_778);
                            *P_LVALUE_778 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_779 = &(PTMP_tmp64_1);
                            PrtFreeValue(*P_LVALUE_779);
                            *P_LVALUE_779 = PrtMapGet(p_this->varValues[10], PTMP_tmp63_1);
                            
                            PRT_VALUE** P_LVALUE_780 = &(PTMP_tmp65_1);
                            PrtFreeValue(*P_LVALUE_780);
                            *P_LVALUE_780 = PrtTupleGet(PTMP_tmp64_1, 0);
                            
                            PRT_VALUE** P_LVALUE_781 = &(PTMP_tmp66_1);
                            PrtFreeValue(*P_LVALUE_781);
                            *P_LVALUE_781 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp65_1) - PrtPrimGetInt((&P_LIT_INT32_49)));
                            
                            PRT_VALUE** P_LVALUE_782 = &(PTMP_tmp67);
                            PrtFreeValue(*P_LVALUE_782);
                            *P_LVALUE_782 = PrtSeqGet(p_this->varValues[5], PTMP_tmp66_1);
                            
                            PRT_VALUE** P_LVALUE_783 = &(PTMP_tmp68);
                            PrtFreeValue(*P_LVALUE_783);
                            *P_LVALUE_783 = PrtTupleGet(PTMP_tmp67, 2);
                            
                            PrtFormatPrintf("\n[Leader] ", 5, (p_this->id), p_this->varValues[3], PTMP_tmp56_1, PTMP_tmp62_1, PTMP_tmp68, 5, 0, " | term ", 1, " | log ", 2, " | Key ", 3, " | Val ", 4, "\n");
                            
                        }
                        
                        else
                        {
                        }
                        
                        
                        PRT_VALUE** P_LVALUE_784 = &(PTMP_tmp69);
                        PrtFreeValue(*P_LVALUE_784);
                        *P_LVALUE_784 = PrtTupleGet(*P_VAR_request_16, 3);
                        
                        PRT_VALUE** P_LVALUE_785 = &(PTMP_tmp75);
                        PrtFreeValue(*P_LVALUE_785);
                        *P_LVALUE_785 = PrtCloneValue(PTMP_tmp69);
                        
                        if (PrtPrimGetBool(PTMP_tmp75))
                        {
                            PRT_VALUE** P_LVALUE_786 = &(PTMP_tmp70);
                            PrtFreeValue(*P_LVALUE_786);
                            *P_LVALUE_786 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_787 = &(PTMP_tmp71);
                            PrtFreeValue(*P_LVALUE_787);
                            *P_LVALUE_787 = PrtMapGet(p_this->varValues[10], PTMP_tmp70);
                            
                            PRT_VALUE** P_LVALUE_788 = &(PTMP_tmp72);
                            PrtFreeValue(*P_LVALUE_788);
                            *P_LVALUE_788 = PrtTupleGet(PTMP_tmp71, 1);
                            
                            PRT_VALUE** P_LVALUE_789 = &(PTMP_tmp73);
                            PrtFreeValue(*P_LVALUE_789);
                            *P_LVALUE_789 = PrtTupleGet(p_this->varValues[8], 1);
                            
                            PRT_VALUE** P_LVALUE_790 = &(PTMP_tmp74);
                            PrtFreeValue(*P_LVALUE_790);
                            *P_LVALUE_790 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp72) > PrtPrimGetInt(PTMP_tmp73));
                            
                            PRT_VALUE** P_LVALUE_791 = &(PTMP_tmp75);
                            PrtFreeValue(*P_LVALUE_791);
                            *P_LVALUE_791 = PrtCloneValue(PTMP_tmp74);
                            
                        }
                        
                        
                        PRT_VALUE** P_LVALUE_792 = &(PTMP_tmp83);
                        PrtFreeValue(*P_LVALUE_792);
                        *P_LVALUE_792 = PrtCloneValue(PTMP_tmp75);
                        
                        if (PrtPrimGetBool(PTMP_tmp83))
                        {
                            PRT_VALUE** P_LVALUE_793 = &(PTMP_tmp76);
                            PrtFreeValue(*P_LVALUE_793);
                            *P_LVALUE_793 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_794 = &(PTMP_tmp77);
                            PrtFreeValue(*P_LVALUE_794);
                            *P_LVALUE_794 = PrtMapGet(p_this->varValues[10], PTMP_tmp76);
                            
                            PRT_VALUE** P_LVALUE_795 = &(PTMP_tmp78);
                            PrtFreeValue(*P_LVALUE_795);
                            *P_LVALUE_795 = PrtTupleGet(PTMP_tmp77, 1);
                            
                            PRT_VALUE** P_LVALUE_796 = &(PTMP_tmp79);
                            PrtFreeValue(*P_LVALUE_796);
                            *P_LVALUE_796 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp78) - PrtPrimGetInt((&P_LIT_INT32_49)));
                            
                            PRT_VALUE** P_LVALUE_797 = &(PTMP_tmp80);
                            PrtFreeValue(*P_LVALUE_797);
                            *P_LVALUE_797 = PrtSeqGet(p_this->varValues[6], PTMP_tmp79);
                            
                            PRT_VALUE** P_LVALUE_798 = &(PTMP_tmp81);
                            PrtFreeValue(*P_LVALUE_798);
                            *P_LVALUE_798 = PrtTupleGet(PTMP_tmp80, 0);
                            
                            PRT_VALUE** P_LVALUE_799 = &(PTMP_tmp82);
                            PrtFreeValue(*P_LVALUE_799);
                            *P_LVALUE_799 = PrtMkBoolValue(PrtIsEqualValue(PTMP_tmp81, p_this->varValues[3]));
                            
                            PRT_VALUE** P_LVALUE_800 = &(PTMP_tmp83);
                            PrtFreeValue(*P_LVALUE_800);
                            *P_LVALUE_800 = PrtCloneValue(PTMP_tmp82);
                            
                        }
                        
                        
                        if (PrtPrimGetBool(PTMP_tmp83))
                        {
                            PRT_VALUE** P_LVALUE_801 = &(PTMP_tmp84);
                            PrtFreeValue(*P_LVALUE_801);
                            *P_LVALUE_801 = PrtTupleGet(p_this->varValues[8], 1);
                            
                            PRT_VALUE** P_LVALUE_802 = &(PTMP_tmp85);
                            PrtFreeValue(*P_LVALUE_802);
                            *P_LVALUE_802 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_803 = &(PTMP_tmp86);
                            PrtFreeValue(*P_LVALUE_803);
                            *P_LVALUE_803 = PrtMapGet(p_this->varValues[10], PTMP_tmp85);
                            
                            PRT_VALUE** P_LVALUE_804 = &(PTMP_tmp87);
                            PrtFreeValue(*P_LVALUE_804);
                            *P_LVALUE_804 = PrtTupleGet(PTMP_tmp86, 1);
                            
                            PrtFormatPrintf("[Leader] Config CommitIndex updated from ", 2, PTMP_tmp84, PTMP_tmp87, 2, 0, " to ", 1, "");
                            
                            PRT_VALUE** P_LVALUE_805 = &(PTMP_tmp88);
                            PrtFreeValue(*P_LVALUE_805);
                            *P_LVALUE_805 = PrtTupleGet(*P_VAR_request_16, 4);
                            
                            PRT_VALUE** P_LVALUE_806 = &(PTMP_tmp89);
                            PrtFreeValue(*P_LVALUE_806);
                            *P_LVALUE_806 = PrtMapGet(p_this->varValues[10], PTMP_tmp88);
                            
                            PRT_VALUE** P_LVALUE_807 = &(PTMP_tmp90);
                            PrtFreeValue(*P_LVALUE_807);
                            *P_LVALUE_807 = PrtTupleGet(PTMP_tmp89, 1);
                            
                            {
                                PRT_VALUE** P_LVALUE_808 = &(*(PrtTupleGetLValue(p_this->varValues[8], 1)));
                                PrtFreeValue(*P_LVALUE_808);
                                *P_LVALUE_808 = PTMP_tmp90;
                                PTMP_tmp90 = NULL;
                            }
                            
                        }
                        
                        else
                        {
                        }
                        
                        
                        PRT_VALUE** P_LVALUE_809 = &(p_this->varValues[11]);
                        PrtFreeValue(*P_LVALUE_809);
                        *P_LVALUE_809 = PrtCloneValue((&P_LIT_INT32_50));
                        
                        PRT_VALUE** P_LVALUE_810 = &(PTMP_tmp91);
                        PrtFreeValue(*P_LVALUE_810);
                        *P_LVALUE_810 = PrtTupleGet(*P_VAR_request_16, 5);
                        
                        PRT_VALUE** P_LVALUE_811 = &(PTMP_tmp92);
                        PrtFreeValue(*P_LVALUE_811);
                        *P_LVALUE_811 = PrtTupleGet(p_this->varValues[8], 0);
                        
                        PRT_VALUE** P_LVALUE_812 = &(PTMP_tmp93);
                        PrtFreeValue(*P_LVALUE_812);
                        *P_LVALUE_812 = PrtSeqGet(p_this->varValues[5], PTMP_tmp92);
                        
                        PRT_VALUE** P_LVALUE_813 = &(PTMP_tmp94);
                        PrtFreeValue(*P_LVALUE_813);
                        *P_LVALUE_813 = PrtTupleGet(PTMP_tmp93, 1);
                        
                        PRT_VALUE** P_LVALUE_814 = &(PTMP_tmp95);
                        PrtFreeValue(*P_LVALUE_814);
                        *P_LVALUE_814 = PrtTupleGet(p_this->varValues[8], 0);
                        
                        PRT_VALUE** P_LVALUE_815 = &(PTMP_tmp96);
                        PrtFreeValue(*P_LVALUE_815);
                        *P_LVALUE_815 = PrtSeqGet(p_this->varValues[5], PTMP_tmp95);
                        
                        PRT_VALUE** P_LVALUE_816 = &(PTMP_tmp97);
                        PrtFreeValue(*P_LVALUE_816);
                        *P_LVALUE_816 = PrtTupleGet(PTMP_tmp96, 2);
                        
                        PRT_VALUE** P_LVALUE_817 = &(PTMP_tmp98);
                        PrtFreeValue(*P_LVALUE_817);
                        *P_LVALUE_817 = (PrtMkTuple(&P_GEND_TYPE_T3mrr, &(PTMP_tmp91), &(PTMP_tmp94), &(PTMP_tmp97)));
                        
                        {
                            PRT_VALUE** P_LVALUE_818 = &(p_this->varValues[12]);
                            PrtFreeValue(*P_LVALUE_818);
                            *P_LVALUE_818 = PTMP_tmp98;
                            PTMP_tmp98 = NULL;
                        }
                        
                        PRT_VALUE** P_LVALUE_819 = &(PTMP_tmp99);
                        PrtFreeValue(*P_LVALUE_819);
                        *P_LVALUE_819 = PrtTupleGet(*P_VAR_request_16, 5);
                        
                        PRT_VALUE** P_LVALUE_820 = &(PTMP_tmp100);
                        PrtFreeValue(*P_LVALUE_820);
                        *P_LVALUE_820 = PrtCloneValue(PTMP_tmp99);
                        
                        PRT_VALUE** P_LVALUE_821 = &(PTMP_tmp101);
                        PrtFreeValue(*P_LVALUE_821);
                        *P_LVALUE_821 = PrtCloneValue((&P_EVENT_Response.value));
                        
                        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp100), PTMP_tmp101, 0);
                        *(&(PTMP_tmp101)) = NULL;
                        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                            goto p_return_68;
                        }
                        if (p_this->isHalted == PRT_TRUE) {
                            PrtFreeValue(_P_GEN_retval);
                            _P_GEN_retval = NULL;
                            goto p_return_68;
                        }
                        
                        PRT_VALUE** P_LVALUE_822 = &(P_VAR_idx_9);
                        PrtFreeValue(*P_LVALUE_822);
                        *P_LVALUE_822 = PrtCloneValue((&P_LIT_INT32_50));
                        
                        while (PrtPrimGetBool((&P_LIT_BOOLEAN_26)))
                        {
                            PRT_VALUE** P_LVALUE_823 = &(PTMP_tmp102);
                            PrtFreeValue(*P_LVALUE_823);
                            *P_LVALUE_823 = PrtTupleGet(p_this->varValues[8], 0);
                            
                            PRT_VALUE** P_LVALUE_824 = &(PTMP_tmp103);
                            PrtFreeValue(*P_LVALUE_824);
                            *P_LVALUE_824 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_9) < PrtPrimGetInt(PTMP_tmp102));
                            
                            PRT_VALUE** P_LVALUE_825 = &(PTMP_tmp104);
                            PrtFreeValue(*P_LVALUE_825);
                            *P_LVALUE_825 = PrtCloneValue(PTMP_tmp103);
                            
                            if (PrtPrimGetBool(PTMP_tmp104))
                            {
                            }
                            
                            else
                            {
                                break;
                                
                            }
                            
                            
                            PRT_VALUE** P_LVALUE_826 = &(PTMP_tmp105);
                            PrtFreeValue(*P_LVALUE_826);
                            *P_LVALUE_826 = PrtSeqGet(p_this->varValues[5], P_VAR_idx_9);
                            
                            PrtSeqInsertEx(P_VAR_committedLogs, P_VAR_idx_9, PTMP_tmp105, PRT_FALSE);
                            *(&(PTMP_tmp105)) = NULL;
                            
                            PRT_VALUE** P_LVALUE_827 = &(PTMP_tmp106);
                            PrtFreeValue(*P_LVALUE_827);
                            *P_LVALUE_827 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_9) + PrtPrimGetInt((&P_LIT_INT32_49)));
                            
                            {
                                PRT_VALUE** P_LVALUE_828 = &(P_VAR_idx_9);
                                PrtFreeValue(*P_LVALUE_828);
                                *P_LVALUE_828 = PTMP_tmp106;
                                PTMP_tmp106 = NULL;
                            }
                            
                        }
                        
                        
                        
                        PRT_VALUE** P_LVALUE_829 = &(PTMP_tmp107);
                        PrtFreeValue(*P_LVALUE_829);
                        *P_LVALUE_829 = PrtTupleGet(*P_VAR_request_16, 3);
                        
                        if (PrtPrimGetBool(PTMP_tmp107))
                        {
                            PRT_VALUE** P_LVALUE_830 = &(PTMP_tmp108);
                            PrtFreeValue(*P_LVALUE_830);
                            *P_LVALUE_830 = PrtMkBoolValue(PrtIsEqualValue(p_this->varValues[14], (&P_LIT_INT32_49)));
                            
                            if (PrtPrimGetBool(PTMP_tmp108))
                            {
                                PRT_VALUE** P_LVALUE_831 = &(PTMP_tmp109);
                                PrtFreeValue(*P_LVALUE_831);
                                *P_LVALUE_831 = PrtCloneValue(p_this->varValues[0]);
                                
                                PRT_VALUE** P_LVALUE_832 = &(PTMP_tmp110);
                                PrtFreeValue(*P_LVALUE_832);
                                *P_LVALUE_832 = PrtCloneValue((&P_EVENT_AddServerResponse.value));
                                
                                PRT_VALUE** P_LVALUE_833 = &(PTMP_tmp111);
                                PrtFreeValue(*P_LVALUE_833);
                                *P_LVALUE_833 = PrtCloneValue(p_this->varValues[13]);
                                
                                PRT_VALUE** P_LVALUE_834 = &(PTMP_tmp112);
                                PrtFreeValue(*P_LVALUE_834);
                                *P_LVALUE_834 = PrtCloneValue((&P_LIT_BOOLEAN_26));
                                
                                PRT_VALUE** P_LVALUE_835 = &(PTMP_tmp113);
                                PrtFreeValue(*P_LVALUE_835);
                                *P_LVALUE_835 = (PrtMkTuple(&P_GEND_TYPE_T2mb, &(PTMP_tmp111), &(PTMP_tmp112)));
                                
                                PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp109), PTMP_tmp110, 1, &(PTMP_tmp113));
                                *(&(PTMP_tmp110)) = NULL;
                                if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                                    goto p_return_68;
                                }
                                if (p_this->isHalted == PRT_TRUE) {
                                    PrtFreeValue(_P_GEN_retval);
                                    _P_GEN_retval = NULL;
                                    goto p_return_68;
                                }
                                
                            }
                            
                            else
                            {
                            }
                            
                            
                            PRT_VALUE** P_LVALUE_836 = &(PTMP_tmp114);
                            PrtFreeValue(*P_LVALUE_836);
                            *P_LVALUE_836 = PrtMkBoolValue(PrtIsEqualValue(p_this->varValues[14], (&P_LIT_INT32_51)));
                            
                            if (PrtPrimGetBool(PTMP_tmp114))
                            {
                                PRT_VALUE** P_LVALUE_837 = &(PTMP_tmp115);
                                PrtFreeValue(*P_LVALUE_837);
                                *P_LVALUE_837 = PrtCloneValue(p_this->varValues[0]);
                                
                                PRT_VALUE** P_LVALUE_838 = &(PTMP_tmp116);
                                PrtFreeValue(*P_LVALUE_838);
                                *P_LVALUE_838 = PrtCloneValue((&P_EVENT_RemoveServerResponse.value));
                                
                                PRT_VALUE** P_LVALUE_839 = &(PTMP_tmp117);
                                PrtFreeValue(*P_LVALUE_839);
                                *P_LVALUE_839 = PrtCloneValue(p_this->varValues[13]);
                                
                                PRT_VALUE** P_LVALUE_840 = &(PTMP_tmp118);
                                PrtFreeValue(*P_LVALUE_840);
                                *P_LVALUE_840 = PrtCloneValue((&P_LIT_BOOLEAN_26));
                                
                                PRT_VALUE** P_LVALUE_841 = &(PTMP_tmp119);
                                PrtFreeValue(*P_LVALUE_841);
                                *P_LVALUE_841 = (PrtMkTuple(&P_GEND_TYPE_T2mb_1, &(PTMP_tmp117), &(PTMP_tmp118)));
                                
                                PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp115), PTMP_tmp116, 1, &(PTMP_tmp119));
                                *(&(PTMP_tmp116)) = NULL;
                                if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                                    goto p_return_68;
                                }
                                if (p_this->isHalted == PRT_TRUE) {
                                    PrtFreeValue(_P_GEN_retval);
                                    _P_GEN_retval = NULL;
                                    goto p_return_68;
                                }
                                
                            }
                            
                            else
                            {
                            }
                            
                            
                            PRT_VALUE** P_LVALUE_842 = &(PTMP_tmp120);
                            PrtFreeValue(*P_LVALUE_842);
                            *P_LVALUE_842 = PrtMkDefaultValue(&P_GEND_TYPE_m);
                            
                            {
                                PRT_VALUE** P_LVALUE_843 = &(p_this->varValues[13]);
                                PrtFreeValue(*P_LVALUE_843);
                                *P_LVALUE_843 = PTMP_tmp120;
                                PTMP_tmp120 = NULL;
                            }
                            
                            PRT_VALUE** P_LVALUE_844 = &(p_this->varValues[14]);
                            PrtFreeValue(*P_LVALUE_844);
                            *P_LVALUE_844 = PrtCloneValue((&P_LIT_INT32_50));
                            
                            if (PrtPrimGetBool(p_this->varValues[17]))
                            {
                                PrtPrintf("[LeaderNotInCfg] New configuration should have committed, now becoming follower.");
                                
                                PRT_VALUE** P_LVALUE_845 = &(p_this->varValues[17]);
                                PrtFreeValue(*P_LVALUE_845);
                                *P_LVALUE_845 = PrtCloneValue((&P_LIT_BOOLEAN_27));
                                
                                PRT_VALUE** P_LVALUE_846 = &(PTMP_tmp121);
                                PrtFreeValue(*P_LVALUE_846);
                                *P_LVALUE_846 = PrtCloneValue((&P_EVENT_BecomeFollower.value));
                                
                                PrtRaise(p_this, PTMP_tmp121, 0);
                                *(&(PTMP_tmp121)) = NULL;
                                goto p_return_68;
                                
                            }
                            
                            else
                            {
                            }
                            
                            
                        }
                        
                        else
                        {
                        }
                        
                        
                    }
                    
                    else
                    {
                    }
                    
                    
                }
                
                
            }
            
            else
            {
                PRT_VALUE** P_LVALUE_847 = &(PTMP_tmp122);
                PrtFreeValue(*P_LVALUE_847);
                *P_LVALUE_847 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_848 = &(PTMP_tmp123);
                PrtFreeValue(*P_LVALUE_848);
                *P_LVALUE_848 = PrtMapGet(p_this->varValues[9], PTMP_tmp122);
                
                PRT_VALUE** P_LVALUE_849 = &(PTMP_tmp124);
                PrtFreeValue(*P_LVALUE_849);
                *P_LVALUE_849 = PrtTupleGet(PTMP_tmp123, 0);
                
                PRT_VALUE** P_LVALUE_850 = &(PTMP_tmp125);
                PrtFreeValue(*P_LVALUE_850);
                *P_LVALUE_850 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp124) > PrtPrimGetInt((&P_LIT_INT32_50)));
                
                if (PrtPrimGetBool(PTMP_tmp125))
                {
                    PRT_VALUE** P_LVALUE_851 = &(PTMP_tmp126);
                    PrtFreeValue(*P_LVALUE_851);
                    *P_LVALUE_851 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_852 = &(PTMP_tmp127);
                    PrtFreeValue(*P_LVALUE_852);
                    *P_LVALUE_852 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_853 = &(PTMP_tmp128);
                    PrtFreeValue(*P_LVALUE_853);
                    *P_LVALUE_853 = PrtMapGet(p_this->varValues[9], PTMP_tmp127);
                    
                    PRT_VALUE** P_LVALUE_854 = &(PTMP_tmp129);
                    PrtFreeValue(*P_LVALUE_854);
                    *P_LVALUE_854 = PrtTupleGet(PTMP_tmp128, 0);
                    
                    PRT_VALUE** P_LVALUE_855 = &(PTMP_tmp130);
                    PrtFreeValue(*P_LVALUE_855);
                    *P_LVALUE_855 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp129) - PrtPrimGetInt((&P_LIT_INT32_49)));
                    
                    {
                        PRT_VALUE** P_LVALUE_856 = &(*(PrtTupleGetLValue(*(PrtMapGetLValue(p_this->varValues[9], PTMP_tmp126, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)), 0)));
                        PrtFreeValue(*P_LVALUE_856);
                        *P_LVALUE_856 = PTMP_tmp130;
                        PTMP_tmp130 = NULL;
                    }
                    
                    PRT_VALUE** P_LVALUE_857 = &(PTMP_tmp131);
                    PrtFreeValue(*P_LVALUE_857);
                    *P_LVALUE_857 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_858 = &(PTMP_tmp132);
                    PrtFreeValue(*P_LVALUE_858);
                    *P_LVALUE_858 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_859 = &(PTMP_tmp133);
                    PrtFreeValue(*P_LVALUE_859);
                    *P_LVALUE_859 = PrtMapGet(p_this->varValues[9], PTMP_tmp132);
                    
                    PRT_VALUE** P_LVALUE_860 = &(PTMP_tmp134);
                    PrtFreeValue(*P_LVALUE_860);
                    *P_LVALUE_860 = PrtTupleGet(PTMP_tmp133, 0);
                    
                    PrtFormatPrintf("NextIndex for ", 2, PTMP_tmp131, PTMP_tmp134, 2, 0, " is ", 1, "");
                    
                }
                
                else
                {
                }
                
                
                PRT_VALUE** P_LVALUE_861 = &(PTMP_tmp135);
                PrtFreeValue(*P_LVALUE_861);
                *P_LVALUE_861 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_862 = &(PTMP_tmp136);
                PrtFreeValue(*P_LVALUE_862);
                *P_LVALUE_862 = PrtMapGet(p_this->varValues[9], PTMP_tmp135);
                
                PRT_VALUE** P_LVALUE_863 = &(PTMP_tmp137);
                PrtFreeValue(*P_LVALUE_863);
                *P_LVALUE_863 = PrtTupleGet(PTMP_tmp136, 1);
                
                PRT_VALUE** P_LVALUE_864 = &(PTMP_tmp138);
                PrtFreeValue(*P_LVALUE_864);
                *P_LVALUE_864 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp137) > PrtPrimGetInt((&P_LIT_INT32_50)));
                
                if (PrtPrimGetBool(PTMP_tmp138))
                {
                    PRT_VALUE** P_LVALUE_865 = &(PTMP_tmp139);
                    PrtFreeValue(*P_LVALUE_865);
                    *P_LVALUE_865 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_866 = &(PTMP_tmp140);
                    PrtFreeValue(*P_LVALUE_866);
                    *P_LVALUE_866 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_867 = &(PTMP_tmp141);
                    PrtFreeValue(*P_LVALUE_867);
                    *P_LVALUE_867 = PrtMapGet(p_this->varValues[9], PTMP_tmp140);
                    
                    PRT_VALUE** P_LVALUE_868 = &(PTMP_tmp142);
                    PrtFreeValue(*P_LVALUE_868);
                    *P_LVALUE_868 = PrtTupleGet(PTMP_tmp141, 1);
                    
                    PRT_VALUE** P_LVALUE_869 = &(PTMP_tmp143);
                    PrtFreeValue(*P_LVALUE_869);
                    *P_LVALUE_869 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp142) - PrtPrimGetInt((&P_LIT_INT32_49)));
                    
                    {
                        PRT_VALUE** P_LVALUE_870 = &(*(PrtTupleGetLValue(*(PrtMapGetLValue(p_this->varValues[9], PTMP_tmp139, PRT_TRUE, &P_GEND_TYPE_MKmVT2ii)), 1)));
                        PrtFreeValue(*P_LVALUE_870);
                        *P_LVALUE_870 = PTMP_tmp143;
                        PTMP_tmp143 = NULL;
                    }
                    
                }
                
                else
                {
                }
                
                
                PRT_VALUE** P_LVALUE_871 = &(PTMP_tmp144);
                PrtFreeValue(*P_LVALUE_871);
                *P_LVALUE_871 = PrtMkDefaultValue(&P_GEND_TYPE_ST3irr);
                
                {
                    PRT_VALUE** P_LVALUE_872 = &(P_VAR_logsAppend);
                    PrtFreeValue(*P_LVALUE_872);
                    *P_LVALUE_872 = PTMP_tmp144;
                    PTMP_tmp144 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_873 = &(PTMP_tmp145);
                PrtFreeValue(*P_LVALUE_873);
                *P_LVALUE_873 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_874 = &(PTMP_tmp146);
                PrtFreeValue(*P_LVALUE_874);
                *P_LVALUE_874 = PrtMapGet(p_this->varValues[9], PTMP_tmp145);
                
                PRT_VALUE** P_LVALUE_875 = &(PTMP_tmp147);
                PrtFreeValue(*P_LVALUE_875);
                *P_LVALUE_875 = PrtTupleGet(PTMP_tmp146, 0);
                
                PRT_VALUE** P_LVALUE_876 = &(PTMP_tmp148);
                PrtFreeValue(*P_LVALUE_876);
                *P_LVALUE_876 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp147) - PrtPrimGetInt((&P_LIT_INT32_49)));
                
                {
                    PRT_VALUE** P_LVALUE_877 = &(P_VAR_prevLogIndex_1);
                    PrtFreeValue(*P_LVALUE_877);
                    *P_LVALUE_877 = PTMP_tmp148;
                    PTMP_tmp148 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_878 = &(PTMP_tmp149);
                PrtFreeValue(*P_LVALUE_878);
                *P_LVALUE_878 = PrtCloneValue(P_VAR_prevLogIndex_1);
                
                PRT_VALUE** P_LVALUE_879 = &(PTMP_tmp150);
                PrtFreeValue(*P_LVALUE_879);
                *P_LVALUE_879 = PrtCloneValue((&P_LIT_BOOLEAN_26));
                
                PRT_VALUE** P_LVALUE_880 = &(PTMP_tmp151);
                PrtFreeValue(*P_LVALUE_880);
                *P_LVALUE_880 = ((_P_GEN_funargs[0] = &(PTMP_tmp149)), (_P_GEN_funargs[1] = &(PTMP_tmp150)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp149), PTMP_tmp149 = NULL), (PrtFreeValue(PTMP_tmp150), PTMP_tmp150 = NULL), (_P_GEN_funval));
                if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                    goto p_return_68;
                }
                if (p_this->isHalted == PRT_TRUE) {
                    PrtFreeValue(_P_GEN_retval);
                    _P_GEN_retval = NULL;
                    goto p_return_68;
                }
                
                {
                    PRT_VALUE** P_LVALUE_881 = &(P_VAR_prevLogTerm_1);
                    PrtFreeValue(*P_LVALUE_881);
                    *P_LVALUE_881 = PTMP_tmp151;
                    PTMP_tmp151 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_882 = &(PTMP_tmp152);
                PrtFreeValue(*P_LVALUE_882);
                *P_LVALUE_882 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_883 = &(PTMP_tmp153);
                PrtFreeValue(*P_LVALUE_883);
                *P_LVALUE_883 = PrtMapGet(p_this->varValues[9], PTMP_tmp152);
                
                PRT_VALUE** P_LVALUE_884 = &(PTMP_tmp154);
                PrtFreeValue(*P_LVALUE_884);
                *P_LVALUE_884 = PrtTupleGet(PTMP_tmp153, 1);
                
                PRT_VALUE** P_LVALUE_885 = &(PTMP_tmp155);
                PrtFreeValue(*P_LVALUE_885);
                *P_LVALUE_885 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp154) - PrtPrimGetInt((&P_LIT_INT32_49)));
                
                {
                    PRT_VALUE** P_LVALUE_886 = &(P_VAR_prevCfgLogIndex_1);
                    PrtFreeValue(*P_LVALUE_886);
                    *P_LVALUE_886 = PTMP_tmp155;
                    PTMP_tmp155 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_887 = &(PTMP_tmp156);
                PrtFreeValue(*P_LVALUE_887);
                *P_LVALUE_887 = PrtCloneValue(P_VAR_prevCfgLogIndex_1);
                
                PRT_VALUE** P_LVALUE_888 = &(PTMP_tmp157);
                PrtFreeValue(*P_LVALUE_888);
                *P_LVALUE_888 = PrtCloneValue((&P_LIT_BOOLEAN_27));
                
                PRT_VALUE** P_LVALUE_889 = &(PTMP_tmp158);
                PrtFreeValue(*P_LVALUE_889);
                *P_LVALUE_889 = ((_P_GEN_funargs[0] = &(PTMP_tmp156)), (_P_GEN_funargs[1] = &(PTMP_tmp157)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp156), PTMP_tmp156 = NULL), (PrtFreeValue(PTMP_tmp157), PTMP_tmp157 = NULL), (_P_GEN_funval));
                if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                    goto p_return_68;
                }
                if (p_this->isHalted == PRT_TRUE) {
                    PrtFreeValue(_P_GEN_retval);
                    _P_GEN_retval = NULL;
                    goto p_return_68;
                }
                
                {
                    PRT_VALUE** P_LVALUE_890 = &(P_VAR_prevCfgLogTerm_1);
                    PrtFreeValue(*P_LVALUE_890);
                    *P_LVALUE_890 = PTMP_tmp158;
                    PTMP_tmp158 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_891 = &(PTMP_tmp159);
                PrtFreeValue(*P_LVALUE_891);
                *P_LVALUE_891 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_892 = &(PTMP_tmp160);
                PrtFreeValue(*P_LVALUE_892);
                *P_LVALUE_892 = PrtMapGet(p_this->varValues[9], PTMP_tmp159);
                
                PRT_VALUE** P_LVALUE_893 = &(PTMP_tmp161);
                PrtFreeValue(*P_LVALUE_893);
                *P_LVALUE_893 = PrtTupleGet(PTMP_tmp160, 0);
                
                {
                    PRT_VALUE** P_LVALUE_894 = &(P_VAR_idx_9);
                    PrtFreeValue(*P_LVALUE_894);
                    *P_LVALUE_894 = PTMP_tmp161;
                    PTMP_tmp161 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_895 = &(PTMP_tmp162);
                PrtFreeValue(*P_LVALUE_895);
                *P_LVALUE_895 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_896 = &(PTMP_tmp163);
                PrtFreeValue(*P_LVALUE_896);
                *P_LVALUE_896 = PrtMapGet(p_this->varValues[9], PTMP_tmp162);
                
                PRT_VALUE** P_LVALUE_897 = &(PTMP_tmp164);
                PrtFreeValue(*P_LVALUE_897);
                *P_LVALUE_897 = PrtTupleGet(PTMP_tmp163, 1);
                
                {
                    PRT_VALUE** P_LVALUE_898 = &(P_VAR_cfgLogIdx_1);
                    PrtFreeValue(*P_LVALUE_898);
                    *P_LVALUE_898 = PTMP_tmp164;
                    PTMP_tmp164 = NULL;
                }
                
                while (PrtPrimGetBool((&P_LIT_BOOLEAN_26)))
                {
                    PRT_VALUE** P_LVALUE_899 = &(PTMP_tmp165);
                    PrtFreeValue(*P_LVALUE_899);
                    *P_LVALUE_899 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                    
                    PRT_VALUE** P_LVALUE_900 = &(PTMP_tmp166);
                    PrtFreeValue(*P_LVALUE_900);
                    *P_LVALUE_900 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_9) < PrtPrimGetInt(PTMP_tmp165));
                    
                    PRT_VALUE** P_LVALUE_901 = &(PTMP_tmp167);
                    PrtFreeValue(*P_LVALUE_901);
                    *P_LVALUE_901 = PrtCloneValue(PTMP_tmp166);
                    
                    if (PrtPrimGetBool(PTMP_tmp167))
                    {
                    }
                    
                    else
                    {
                        break;
                        
                    }
                    
                    
                    PRT_VALUE** P_LVALUE_902 = &(PTMP_tmp168);
                    PrtFreeValue(*P_LVALUE_902);
                    *P_LVALUE_902 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_903 = &(PTMP_tmp169);
                    PrtFreeValue(*P_LVALUE_903);
                    *P_LVALUE_903 = PrtMapGet(p_this->varValues[9], PTMP_tmp168);
                    
                    PRT_VALUE** P_LVALUE_904 = &(PTMP_tmp170);
                    PrtFreeValue(*P_LVALUE_904);
                    *P_LVALUE_904 = PrtTupleGet(PTMP_tmp169, 0);
                    
                    PRT_VALUE** P_LVALUE_905 = &(PTMP_tmp171);
                    PrtFreeValue(*P_LVALUE_905);
                    *P_LVALUE_905 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_9) - PrtPrimGetInt(PTMP_tmp170));
                    
                    PRT_VALUE** P_LVALUE_906 = &(PTMP_tmp172);
                    PrtFreeValue(*P_LVALUE_906);
                    *P_LVALUE_906 = PrtSeqGet(p_this->varValues[5], P_VAR_idx_9);
                    
                    PrtSeqInsertEx(P_VAR_logsAppend, PTMP_tmp171, PTMP_tmp172, PRT_FALSE);
                    *(&(PTMP_tmp172)) = NULL;
                    
                    PRT_VALUE** P_LVALUE_907 = &(PTMP_tmp173);
                    PrtFreeValue(*P_LVALUE_907);
                    *P_LVALUE_907 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_9) + PrtPrimGetInt((&P_LIT_INT32_49)));
                    
                    {
                        PRT_VALUE** P_LVALUE_908 = &(P_VAR_idx_9);
                        PrtFreeValue(*P_LVALUE_908);
                        *P_LVALUE_908 = PTMP_tmp173;
                        PTMP_tmp173 = NULL;
                    }
                    
                }
                
                
                while (PrtPrimGetBool((&P_LIT_BOOLEAN_26)))
                {
                    PRT_VALUE** P_LVALUE_909 = &(PTMP_tmp174);
                    PrtFreeValue(*P_LVALUE_909);
                    *P_LVALUE_909 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                    
                    PRT_VALUE** P_LVALUE_910 = &(PTMP_tmp175);
                    PrtFreeValue(*P_LVALUE_910);
                    *P_LVALUE_910 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_cfgLogIdx_1) < PrtPrimGetInt(PTMP_tmp174));
                    
                    PRT_VALUE** P_LVALUE_911 = &(PTMP_tmp176);
                    PrtFreeValue(*P_LVALUE_911);
                    *P_LVALUE_911 = PrtCloneValue(PTMP_tmp175);
                    
                    if (PrtPrimGetBool(PTMP_tmp176))
                    {
                    }
                    
                    else
                    {
                        break;
                        
                    }
                    
                    
                    PRT_VALUE** P_LVALUE_912 = &(PTMP_tmp177);
                    PrtFreeValue(*P_LVALUE_912);
                    *P_LVALUE_912 = PrtTupleGet(*P_VAR_request_16, 4);
                    
                    PRT_VALUE** P_LVALUE_913 = &(PTMP_tmp178);
                    PrtFreeValue(*P_LVALUE_913);
                    *P_LVALUE_913 = PrtMapGet(p_this->varValues[9], PTMP_tmp177);
                    
                    PRT_VALUE** P_LVALUE_914 = &(PTMP_tmp179);
                    PrtFreeValue(*P_LVALUE_914);
                    *P_LVALUE_914 = PrtTupleGet(PTMP_tmp178, 1);
                    
                    PRT_VALUE** P_LVALUE_915 = &(PTMP_tmp180);
                    PrtFreeValue(*P_LVALUE_915);
                    *P_LVALUE_915 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_1) - PrtPrimGetInt(PTMP_tmp179));
                    
                    PRT_VALUE** P_LVALUE_916 = &(PTMP_tmp181);
                    PrtFreeValue(*P_LVALUE_916);
                    *P_LVALUE_916 = PrtSeqGet(p_this->varValues[6], P_VAR_cfgLogIdx_1);
                    
                    PrtSeqInsertEx(P_VAR_cfgLogsAppend, PTMP_tmp180, PTMP_tmp181, PRT_FALSE);
                    *(&(PTMP_tmp181)) = NULL;
                    
                    PRT_VALUE** P_LVALUE_917 = &(PTMP_tmp182);
                    PrtFreeValue(*P_LVALUE_917);
                    *P_LVALUE_917 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_1) + PrtPrimGetInt((&P_LIT_INT32_49)));
                    
                    {
                        PRT_VALUE** P_LVALUE_918 = &(P_VAR_cfgLogIdx_1);
                        PrtFreeValue(*P_LVALUE_918);
                        *P_LVALUE_918 = PTMP_tmp182;
                        PTMP_tmp182 = NULL;
                    }
                    
                }
                
                
                PRT_VALUE** P_LVALUE_919 = &(PTMP_tmp183);
                PrtFreeValue(*P_LVALUE_919);
                *P_LVALUE_919 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                
                PRT_VALUE** P_LVALUE_920 = &(PTMP_tmp184);
                PrtFreeValue(*P_LVALUE_920);
                *P_LVALUE_920 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_921 = &(PTMP_tmp185);
                PrtFreeValue(*P_LVALUE_921);
                *P_LVALUE_921 = PrtMapGet(p_this->varValues[9], PTMP_tmp184);
                
                PRT_VALUE** P_LVALUE_922 = &(PTMP_tmp186);
                PrtFreeValue(*P_LVALUE_922);
                *P_LVALUE_922 = PrtTupleGet(PTMP_tmp185, 0);
                
                PrtFormatPrintf("\n[Leader] ", 5, (p_this->id), p_this->varValues[3], PTMP_tmp183, p_this->varValues[11], PTMP_tmp186, 5, 0, " | term ", 1, " | log ", 2, " | append votes ", 3, " | append fail (next idx = ", 4, ")\n");
                
                PRT_VALUE** P_LVALUE_923 = &(PTMP_tmp187);
                PrtFreeValue(*P_LVALUE_923);
                *P_LVALUE_923 = PrtTupleGet(*P_VAR_request_16, 4);
                
                PRT_VALUE** P_LVALUE_924 = &(PTMP_tmp188);
                PrtFreeValue(*P_LVALUE_924);
                *P_LVALUE_924 = PrtCloneValue(PTMP_tmp187);
                
                PRT_VALUE** P_LVALUE_925 = &(PTMP_tmp189);
                PrtFreeValue(*P_LVALUE_925);
                *P_LVALUE_925 = PrtCloneValue((&P_EVENT_AppendEntriesRequest.value));
                
                PRT_VALUE** P_LVALUE_926 = &(PTMP_tmp190);
                PrtFreeValue(*P_LVALUE_926);
                *P_LVALUE_926 = PrtCloneValue(p_this->varValues[3]);
                
                PRT_VALUE** P_LVALUE_927 = &(PTMP_tmp191);
                PrtFreeValue(*P_LVALUE_927);
                *P_LVALUE_927 = PrtCloneValue((p_this->id));
                
                PRT_VALUE** P_LVALUE_928 = &(PTMP_tmp192);
                PrtFreeValue(*P_LVALUE_928);
                *P_LVALUE_928 = PrtCloneValue(P_VAR_prevLogIndex_1);
                
                PRT_VALUE** P_LVALUE_929 = &(PTMP_tmp193);
                PrtFreeValue(*P_LVALUE_929);
                *P_LVALUE_929 = PrtCloneValue(P_VAR_prevCfgLogIndex_1);
                
                PRT_VALUE** P_LVALUE_930 = &(PTMP_tmp194);
                PrtFreeValue(*P_LVALUE_930);
                *P_LVALUE_930 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp192), &(PTMP_tmp193)));
                
                PRT_VALUE** P_LVALUE_931 = &(PTMP_tmp195);
                PrtFreeValue(*P_LVALUE_931);
                *P_LVALUE_931 = PrtCloneValue(P_VAR_prevLogTerm_1);
                
                PRT_VALUE** P_LVALUE_932 = &(PTMP_tmp196);
                PrtFreeValue(*P_LVALUE_932);
                *P_LVALUE_932 = PrtCloneValue(P_VAR_prevCfgLogTerm_1);
                
                PRT_VALUE** P_LVALUE_933 = &(PTMP_tmp197);
                PrtFreeValue(*P_LVALUE_933);
                *P_LVALUE_933 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp195), &(PTMP_tmp196)));
                
                PRT_VALUE** P_LVALUE_934 = &(PTMP_tmp198);
                PrtFreeValue(*P_LVALUE_934);
                *P_LVALUE_934 = PrtCloneValue(P_VAR_logsAppend);
                
                PRT_VALUE** P_LVALUE_935 = &(PTMP_tmp199);
                PrtFreeValue(*P_LVALUE_935);
                *P_LVALUE_935 = PrtCloneValue(P_VAR_cfgLogsAppend);
                
                PRT_VALUE** P_LVALUE_936 = &(PTMP_tmp200);
                PrtFreeValue(*P_LVALUE_936);
                *P_LVALUE_936 = PrtCloneValue(p_this->varValues[8]);
                
                PRT_VALUE** P_LVALUE_937 = &(PTMP_tmp201);
                PrtFreeValue(*P_LVALUE_937);
                *P_LVALUE_937 = PrtTupleGet(p_this->varValues[12], 0);
                
                PRT_VALUE** P_LVALUE_938 = &(PTMP_tmp202);
                PrtFreeValue(*P_LVALUE_938);
                *P_LVALUE_938 = (PrtMkTuple(&P_GEND_TYPE_T8iRT2iiT2iiST3irrST2iSmT2iim, &(PTMP_tmp190), &(PTMP_tmp191), &(PTMP_tmp194), &(PTMP_tmp197), &(PTMP_tmp198), &(PTMP_tmp199), &(PTMP_tmp200), &(PTMP_tmp201)));
                
                PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp188), PTMP_tmp189, 1, &(PTMP_tmp202));
                *(&(PTMP_tmp189)) = NULL;
                if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                    goto p_return_68;
                }
                if (p_this->isHalted == PRT_TRUE) {
                    PrtFreeValue(_P_GEN_retval);
                    _P_GEN_retval = NULL;
                    goto p_return_68;
                }
                
            }
            
            
        }
        
        
    }
    
    
    PRT_VALUE** P_LVALUE_939 = &(PTMP_tmp203);
    PrtFreeValue(*P_LVALUE_939);
    *P_LVALUE_939 = PrtTupleGet(p_this->varValues[8], 0);
    
    PrtFormatPrintf("[Leader | AppendEntriesResponse] CommitIndex: ", 1, PTMP_tmp203, 1, 0, "");
    
p_return_68: ;
    PrtFreeValue(P_VAR_logsAppend); P_VAR_logsAppend = NULL;
    PrtFreeValue(P_VAR_cfgLogsAppend); P_VAR_cfgLogsAppend = NULL;
    PrtFreeValue(P_VAR_prevLogIndex_1); P_VAR_prevLogIndex_1 = NULL;
    PrtFreeValue(P_VAR_prevLogTerm_1); P_VAR_prevLogTerm_1 = NULL;
    PrtFreeValue(P_VAR_prevCfgLogIndex_1); P_VAR_prevCfgLogIndex_1 = NULL;
    PrtFreeValue(P_VAR_prevCfgLogTerm_1); P_VAR_prevCfgLogTerm_1 = NULL;
    PrtFreeValue(P_VAR_idx_9); P_VAR_idx_9 = NULL;
    PrtFreeValue(P_VAR_cfgLogIdx_1); P_VAR_cfgLogIdx_1 = NULL;
    PrtFreeValue(P_VAR_committedLogs); P_VAR_committedLogs = NULL;
    PrtFreeValue(PTMP_tmp0_65); PTMP_tmp0_65 = NULL;
    PrtFreeValue(PTMP_tmp1_54); PTMP_tmp1_54 = NULL;
    PrtFreeValue(PTMP_tmp2_47); PTMP_tmp2_47 = NULL;
    PrtFreeValue(PTMP_tmp3_42); PTMP_tmp3_42 = NULL;
    PrtFreeValue(PTMP_tmp4_35); PTMP_tmp4_35 = NULL;
    PrtFreeValue(PTMP_tmp5_26); PTMP_tmp5_26 = NULL;
    PrtFreeValue(PTMP_tmp6_24); PTMP_tmp6_24 = NULL;
    PrtFreeValue(PTMP_tmp7_22); PTMP_tmp7_22 = NULL;
    PrtFreeValue(PTMP_tmp8_19); PTMP_tmp8_19 = NULL;
    PrtFreeValue(PTMP_tmp9_16); PTMP_tmp9_16 = NULL;
    PrtFreeValue(PTMP_tmp10_15); PTMP_tmp10_15 = NULL;
    PrtFreeValue(PTMP_tmp11_15); PTMP_tmp11_15 = NULL;
    PrtFreeValue(PTMP_tmp12_14); PTMP_tmp12_14 = NULL;
    PrtFreeValue(PTMP_tmp13_13); PTMP_tmp13_13 = NULL;
    PrtFreeValue(PTMP_tmp14_12); PTMP_tmp14_12 = NULL;
    PrtFreeValue(PTMP_tmp15_9); PTMP_tmp15_9 = NULL;
    PrtFreeValue(PTMP_tmp16_8); PTMP_tmp16_8 = NULL;
    PrtFreeValue(PTMP_tmp17_6); PTMP_tmp17_6 = NULL;
    PrtFreeValue(PTMP_tmp18_6); PTMP_tmp18_6 = NULL;
    PrtFreeValue(PTMP_tmp19_6); PTMP_tmp19_6 = NULL;
    PrtFreeValue(PTMP_tmp20_6); PTMP_tmp20_6 = NULL;
    PrtFreeValue(PTMP_tmp21_6); PTMP_tmp21_6 = NULL;
    PrtFreeValue(PTMP_tmp22_6); PTMP_tmp22_6 = NULL;
    PrtFreeValue(PTMP_tmp23_5); PTMP_tmp23_5 = NULL;
    PrtFreeValue(PTMP_tmp24_4); PTMP_tmp24_4 = NULL;
    PrtFreeValue(PTMP_tmp25_4); PTMP_tmp25_4 = NULL;
    PrtFreeValue(PTMP_tmp26_4); PTMP_tmp26_4 = NULL;
    PrtFreeValue(PTMP_tmp27_4); PTMP_tmp27_4 = NULL;
    PrtFreeValue(PTMP_tmp28_4); PTMP_tmp28_4 = NULL;
    PrtFreeValue(PTMP_tmp29_4); PTMP_tmp29_4 = NULL;
    PrtFreeValue(PTMP_tmp30_3); PTMP_tmp30_3 = NULL;
    PrtFreeValue(PTMP_tmp31_2); PTMP_tmp31_2 = NULL;
    PrtFreeValue(PTMP_tmp32_2); PTMP_tmp32_2 = NULL;
    PrtFreeValue(PTMP_tmp33_2); PTMP_tmp33_2 = NULL;
    PrtFreeValue(PTMP_tmp34_2); PTMP_tmp34_2 = NULL;
    PrtFreeValue(PTMP_tmp35_2); PTMP_tmp35_2 = NULL;
    PrtFreeValue(PTMP_tmp36_1); PTMP_tmp36_1 = NULL;
    PrtFreeValue(PTMP_tmp37_1); PTMP_tmp37_1 = NULL;
    PrtFreeValue(PTMP_tmp38_1); PTMP_tmp38_1 = NULL;
    PrtFreeValue(PTMP_tmp39_1); PTMP_tmp39_1 = NULL;
    PrtFreeValue(PTMP_tmp40_1); PTMP_tmp40_1 = NULL;
    PrtFreeValue(PTMP_tmp41_1); PTMP_tmp41_1 = NULL;
    PrtFreeValue(PTMP_tmp42_1); PTMP_tmp42_1 = NULL;
    PrtFreeValue(PTMP_tmp43_1); PTMP_tmp43_1 = NULL;
    PrtFreeValue(PTMP_tmp44_1); PTMP_tmp44_1 = NULL;
    PrtFreeValue(PTMP_tmp45_1); PTMP_tmp45_1 = NULL;
    PrtFreeValue(PTMP_tmp46_1); PTMP_tmp46_1 = NULL;
    PrtFreeValue(PTMP_tmp47_1); PTMP_tmp47_1 = NULL;
    PrtFreeValue(PTMP_tmp48_1); PTMP_tmp48_1 = NULL;
    PrtFreeValue(PTMP_tmp49_1); PTMP_tmp49_1 = NULL;
    PrtFreeValue(PTMP_tmp50_1); PTMP_tmp50_1 = NULL;
    PrtFreeValue(PTMP_tmp51_1); PTMP_tmp51_1 = NULL;
    PrtFreeValue(PTMP_tmp52_1); PTMP_tmp52_1 = NULL;
    PrtFreeValue(PTMP_tmp53_1); PTMP_tmp53_1 = NULL;
    PrtFreeValue(PTMP_tmp54_1); PTMP_tmp54_1 = NULL;
    PrtFreeValue(PTMP_tmp55_1); PTMP_tmp55_1 = NULL;
    PrtFreeValue(PTMP_tmp56_1); PTMP_tmp56_1 = NULL;
    PrtFreeValue(PTMP_tmp57_1); PTMP_tmp57_1 = NULL;
    PrtFreeValue(PTMP_tmp58_1); PTMP_tmp58_1 = NULL;
    PrtFreeValue(PTMP_tmp59_1); PTMP_tmp59_1 = NULL;
    PrtFreeValue(PTMP_tmp60_1); PTMP_tmp60_1 = NULL;
    PrtFreeValue(PTMP_tmp61_1); PTMP_tmp61_1 = NULL;
    PrtFreeValue(PTMP_tmp62_1); PTMP_tmp62_1 = NULL;
    PrtFreeValue(PTMP_tmp63_1); PTMP_tmp63_1 = NULL;
    PrtFreeValue(PTMP_tmp64_1); PTMP_tmp64_1 = NULL;
    PrtFreeValue(PTMP_tmp65_1); PTMP_tmp65_1 = NULL;
    PrtFreeValue(PTMP_tmp66_1); PTMP_tmp66_1 = NULL;
    PrtFreeValue(PTMP_tmp67); PTMP_tmp67 = NULL;
    PrtFreeValue(PTMP_tmp68); PTMP_tmp68 = NULL;
    PrtFreeValue(PTMP_tmp69); PTMP_tmp69 = NULL;
    PrtFreeValue(PTMP_tmp70); PTMP_tmp70 = NULL;
    PrtFreeValue(PTMP_tmp71); PTMP_tmp71 = NULL;
    PrtFreeValue(PTMP_tmp72); PTMP_tmp72 = NULL;
    PrtFreeValue(PTMP_tmp73); PTMP_tmp73 = NULL;
    PrtFreeValue(PTMP_tmp74); PTMP_tmp74 = NULL;
    PrtFreeValue(PTMP_tmp75); PTMP_tmp75 = NULL;
    PrtFreeValue(PTMP_tmp76); PTMP_tmp76 = NULL;
    PrtFreeValue(PTMP_tmp77); PTMP_tmp77 = NULL;
    PrtFreeValue(PTMP_tmp78); PTMP_tmp78 = NULL;
    PrtFreeValue(PTMP_tmp79); PTMP_tmp79 = NULL;
    PrtFreeValue(PTMP_tmp80); PTMP_tmp80 = NULL;
    PrtFreeValue(PTMP_tmp81); PTMP_tmp81 = NULL;
    PrtFreeValue(PTMP_tmp82); PTMP_tmp82 = NULL;
    PrtFreeValue(PTMP_tmp83); PTMP_tmp83 = NULL;
    PrtFreeValue(PTMP_tmp84); PTMP_tmp84 = NULL;
    PrtFreeValue(PTMP_tmp85); PTMP_tmp85 = NULL;
    PrtFreeValue(PTMP_tmp86); PTMP_tmp86 = NULL;
    PrtFreeValue(PTMP_tmp87); PTMP_tmp87 = NULL;
    PrtFreeValue(PTMP_tmp88); PTMP_tmp88 = NULL;
    PrtFreeValue(PTMP_tmp89); PTMP_tmp89 = NULL;
    PrtFreeValue(PTMP_tmp90); PTMP_tmp90 = NULL;
    PrtFreeValue(PTMP_tmp91); PTMP_tmp91 = NULL;
    PrtFreeValue(PTMP_tmp92); PTMP_tmp92 = NULL;
    PrtFreeValue(PTMP_tmp93); PTMP_tmp93 = NULL;
    PrtFreeValue(PTMP_tmp94); PTMP_tmp94 = NULL;
    PrtFreeValue(PTMP_tmp95); PTMP_tmp95 = NULL;
    PrtFreeValue(PTMP_tmp96); PTMP_tmp96 = NULL;
    PrtFreeValue(PTMP_tmp97); PTMP_tmp97 = NULL;
    PrtFreeValue(PTMP_tmp98); PTMP_tmp98 = NULL;
    PrtFreeValue(PTMP_tmp99); PTMP_tmp99 = NULL;
    PrtFreeValue(PTMP_tmp100); PTMP_tmp100 = NULL;
    PrtFreeValue(PTMP_tmp101); PTMP_tmp101 = NULL;
    PrtFreeValue(PTMP_tmp102); PTMP_tmp102 = NULL;
    PrtFreeValue(PTMP_tmp103); PTMP_tmp103 = NULL;
    PrtFreeValue(PTMP_tmp104); PTMP_tmp104 = NULL;
    PrtFreeValue(PTMP_tmp105); PTMP_tmp105 = NULL;
    PrtFreeValue(PTMP_tmp106); PTMP_tmp106 = NULL;
    PrtFreeValue(PTMP_tmp107); PTMP_tmp107 = NULL;
    PrtFreeValue(PTMP_tmp108); PTMP_tmp108 = NULL;
    PrtFreeValue(PTMP_tmp109); PTMP_tmp109 = NULL;
    PrtFreeValue(PTMP_tmp110); PTMP_tmp110 = NULL;
    PrtFreeValue(PTMP_tmp111); PTMP_tmp111 = NULL;
    PrtFreeValue(PTMP_tmp112); PTMP_tmp112 = NULL;
    PrtFreeValue(PTMP_tmp113); PTMP_tmp113 = NULL;
    PrtFreeValue(PTMP_tmp114); PTMP_tmp114 = NULL;
    PrtFreeValue(PTMP_tmp115); PTMP_tmp115 = NULL;
    PrtFreeValue(PTMP_tmp116); PTMP_tmp116 = NULL;
    PrtFreeValue(PTMP_tmp117); PTMP_tmp117 = NULL;
    PrtFreeValue(PTMP_tmp118); PTMP_tmp118 = NULL;
    PrtFreeValue(PTMP_tmp119); PTMP_tmp119 = NULL;
    PrtFreeValue(PTMP_tmp120); PTMP_tmp120 = NULL;
    PrtFreeValue(PTMP_tmp121); PTMP_tmp121 = NULL;
    PrtFreeValue(PTMP_tmp122); PTMP_tmp122 = NULL;
    PrtFreeValue(PTMP_tmp123); PTMP_tmp123 = NULL;
    PrtFreeValue(PTMP_tmp124); PTMP_tmp124 = NULL;
    PrtFreeValue(PTMP_tmp125); PTMP_tmp125 = NULL;
    PrtFreeValue(PTMP_tmp126); PTMP_tmp126 = NULL;
    PrtFreeValue(PTMP_tmp127); PTMP_tmp127 = NULL;
    PrtFreeValue(PTMP_tmp128); PTMP_tmp128 = NULL;
    PrtFreeValue(PTMP_tmp129); PTMP_tmp129 = NULL;
    PrtFreeValue(PTMP_tmp130); PTMP_tmp130 = NULL;
    PrtFreeValue(PTMP_tmp131); PTMP_tmp131 = NULL;
    PrtFreeValue(PTMP_tmp132); PTMP_tmp132 = NULL;
    PrtFreeValue(PTMP_tmp133); PTMP_tmp133 = NULL;
    PrtFreeValue(PTMP_tmp134); PTMP_tmp134 = NULL;
    PrtFreeValue(PTMP_tmp135); PTMP_tmp135 = NULL;
    PrtFreeValue(PTMP_tmp136); PTMP_tmp136 = NULL;
    PrtFreeValue(PTMP_tmp137); PTMP_tmp137 = NULL;
    PrtFreeValue(PTMP_tmp138); PTMP_tmp138 = NULL;
    PrtFreeValue(PTMP_tmp139); PTMP_tmp139 = NULL;
    PrtFreeValue(PTMP_tmp140); PTMP_tmp140 = NULL;
    PrtFreeValue(PTMP_tmp141); PTMP_tmp141 = NULL;
    PrtFreeValue(PTMP_tmp142); PTMP_tmp142 = NULL;
    PrtFreeValue(PTMP_tmp143); PTMP_tmp143 = NULL;
    PrtFreeValue(PTMP_tmp144); PTMP_tmp144 = NULL;
    PrtFreeValue(PTMP_tmp145); PTMP_tmp145 = NULL;
    PrtFreeValue(PTMP_tmp146); PTMP_tmp146 = NULL;
    PrtFreeValue(PTMP_tmp147); PTMP_tmp147 = NULL;
    PrtFreeValue(PTMP_tmp148); PTMP_tmp148 = NULL;
    PrtFreeValue(PTMP_tmp149); PTMP_tmp149 = NULL;
    PrtFreeValue(PTMP_tmp150); PTMP_tmp150 = NULL;
    PrtFreeValue(PTMP_tmp151); PTMP_tmp151 = NULL;
    PrtFreeValue(PTMP_tmp152); PTMP_tmp152 = NULL;
    PrtFreeValue(PTMP_tmp153); PTMP_tmp153 = NULL;
    PrtFreeValue(PTMP_tmp154); PTMP_tmp154 = NULL;
    PrtFreeValue(PTMP_tmp155); PTMP_tmp155 = NULL;
    PrtFreeValue(PTMP_tmp156); PTMP_tmp156 = NULL;
    PrtFreeValue(PTMP_tmp157); PTMP_tmp157 = NULL;
    PrtFreeValue(PTMP_tmp158); PTMP_tmp158 = NULL;
    PrtFreeValue(PTMP_tmp159); PTMP_tmp159 = NULL;
    PrtFreeValue(PTMP_tmp160); PTMP_tmp160 = NULL;
    PrtFreeValue(PTMP_tmp161); PTMP_tmp161 = NULL;
    PrtFreeValue(PTMP_tmp162); PTMP_tmp162 = NULL;
    PrtFreeValue(PTMP_tmp163); PTMP_tmp163 = NULL;
    PrtFreeValue(PTMP_tmp164); PTMP_tmp164 = NULL;
    PrtFreeValue(PTMP_tmp165); PTMP_tmp165 = NULL;
    PrtFreeValue(PTMP_tmp166); PTMP_tmp166 = NULL;
    PrtFreeValue(PTMP_tmp167); PTMP_tmp167 = NULL;
    PrtFreeValue(PTMP_tmp168); PTMP_tmp168 = NULL;
    PrtFreeValue(PTMP_tmp169); PTMP_tmp169 = NULL;
    PrtFreeValue(PTMP_tmp170); PTMP_tmp170 = NULL;
    PrtFreeValue(PTMP_tmp171); PTMP_tmp171 = NULL;
    PrtFreeValue(PTMP_tmp172); PTMP_tmp172 = NULL;
    PrtFreeValue(PTMP_tmp173); PTMP_tmp173 = NULL;
    PrtFreeValue(PTMP_tmp174); PTMP_tmp174 = NULL;
    PrtFreeValue(PTMP_tmp175); PTMP_tmp175 = NULL;
    PrtFreeValue(PTMP_tmp176); PTMP_tmp176 = NULL;
    PrtFreeValue(PTMP_tmp177); PTMP_tmp177 = NULL;
    PrtFreeValue(PTMP_tmp178); PTMP_tmp178 = NULL;
    PrtFreeValue(PTMP_tmp179); PTMP_tmp179 = NULL;
    PrtFreeValue(PTMP_tmp180); PTMP_tmp180 = NULL;
    PrtFreeValue(PTMP_tmp181); PTMP_tmp181 = NULL;
    PrtFreeValue(PTMP_tmp182); PTMP_tmp182 = NULL;
    PrtFreeValue(PTMP_tmp183); PTMP_tmp183 = NULL;
    PrtFreeValue(PTMP_tmp184); PTMP_tmp184 = NULL;
    PrtFreeValue(PTMP_tmp185); PTMP_tmp185 = NULL;
    PrtFreeValue(PTMP_tmp186); PTMP_tmp186 = NULL;
    PrtFreeValue(PTMP_tmp187); PTMP_tmp187 = NULL;
    PrtFreeValue(PTMP_tmp188); PTMP_tmp188 = NULL;
    PrtFreeValue(PTMP_tmp189); PTMP_tmp189 = NULL;
    PrtFreeValue(PTMP_tmp190); PTMP_tmp190 = NULL;
    PrtFreeValue(PTMP_tmp191); PTMP_tmp191 = NULL;
    PrtFreeValue(PTMP_tmp192); PTMP_tmp192 = NULL;
    PrtFreeValue(PTMP_tmp193); PTMP_tmp193 = NULL;
    PrtFreeValue(PTMP_tmp194); PTMP_tmp194 = NULL;
    PrtFreeValue(PTMP_tmp195); PTMP_tmp195 = NULL;
    PrtFreeValue(PTMP_tmp196); PTMP_tmp196 = NULL;
    PrtFreeValue(PTMP_tmp197); PTMP_tmp197 = NULL;
    PrtFreeValue(PTMP_tmp198); PTMP_tmp198 = NULL;
    PrtFreeValue(PTMP_tmp199); PTMP_tmp199 = NULL;
    PrtFreeValue(PTMP_tmp200); PTMP_tmp200 = NULL;
    PrtFreeValue(PTMP_tmp201); PTMP_tmp201 = NULL;
    PrtFreeValue(PTMP_tmp202); PTMP_tmp202 = NULL;
    PrtFreeValue(PTMP_tmp203); PTMP_tmp203 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_RespondAppendEntriesAsLeader =
{
    "RespondAppendEntriesAsLeader",
    &P_RespondAppendEntriesAsLeader_IMPL,
    NULL
};


PRT_VALUE* P_Vote_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_request_17 = argRefs[0];
    PRT_VALUE* P_VAR_lastLogIndex_2 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_lastLogTerm_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_lastCfgLogIndex_2 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_lastCfgLogTerm_1 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_66 = NULL;
    PRT_VALUE* PTMP_tmp1_55 = NULL;
    PRT_VALUE* PTMP_tmp2_48 = NULL;
    PRT_VALUE* PTMP_tmp3_43 = NULL;
    PRT_VALUE* PTMP_tmp4_36 = NULL;
    PRT_VALUE* PTMP_tmp5_27 = NULL;
    PRT_VALUE* PTMP_tmp6_25 = NULL;
    PRT_VALUE* PTMP_tmp7_23 = NULL;
    PRT_VALUE* PTMP_tmp8_20 = NULL;
    PRT_VALUE* PTMP_tmp9_17 = NULL;
    PRT_VALUE* PTMP_tmp10_16 = NULL;
    PRT_VALUE* PTMP_tmp11_16 = NULL;
    PRT_VALUE* PTMP_tmp12_15 = NULL;
    PRT_VALUE* PTMP_tmp13_14 = NULL;
    PRT_VALUE* PTMP_tmp14_13 = NULL;
    PRT_VALUE* PTMP_tmp15_10 = NULL;
    PRT_VALUE* PTMP_tmp16_9 = NULL;
    PRT_VALUE* PTMP_tmp17_7 = NULL;
    PRT_VALUE* PTMP_tmp18_7 = NULL;
    PRT_VALUE* PTMP_tmp19_7 = NULL;
    PRT_VALUE* PTMP_tmp20_7 = NULL;
    PRT_VALUE* PTMP_tmp21_7 = NULL;
    PRT_VALUE* PTMP_tmp22_7 = NULL;
    PRT_VALUE* PTMP_tmp23_6 = NULL;
    PRT_VALUE* PTMP_tmp24_5 = NULL;
    PRT_VALUE* PTMP_tmp25_5 = NULL;
    PRT_VALUE* PTMP_tmp26_5 = NULL;
    PRT_VALUE* PTMP_tmp27_5 = NULL;
    PRT_VALUE* PTMP_tmp28_5 = NULL;
    PRT_VALUE* PTMP_tmp29_5 = NULL;
    PRT_VALUE* PTMP_tmp30_4 = NULL;
    PRT_VALUE* PTMP_tmp31_3 = NULL;
    PRT_VALUE* PTMP_tmp32_3 = NULL;
    PRT_VALUE* PTMP_tmp33_3 = NULL;
    PRT_VALUE* PTMP_tmp34_3 = NULL;
    PRT_VALUE* PTMP_tmp35_3 = NULL;
    PRT_VALUE* PTMP_tmp36_2 = NULL;
    PRT_VALUE* PTMP_tmp37_2 = NULL;
    PRT_VALUE* PTMP_tmp38_2 = NULL;
    PRT_VALUE* PTMP_tmp39_2 = NULL;
    PRT_VALUE* PTMP_tmp40_2 = NULL;
    PRT_VALUE* PTMP_tmp41_2 = NULL;
    PRT_VALUE* PTMP_tmp42_2 = NULL;
    PRT_VALUE* PTMP_tmp43_2 = NULL;
    PRT_VALUE* PTMP_tmp44_2 = NULL;
    PRT_VALUE* PTMP_tmp45_2 = NULL;
    PRT_VALUE* PTMP_tmp46_2 = NULL;
    PRT_VALUE* PTMP_tmp47_2 = NULL;
    PRT_VALUE* PTMP_tmp48_2 = NULL;
    PRT_VALUE* PTMP_tmp49_2 = NULL;
    PRT_VALUE* PTMP_tmp50_2 = NULL;
    PRT_VALUE* PTMP_tmp51_2 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_52 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_INT32_53 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_BOOLEAN_28 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE P_LIT_BOOLEAN_29 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE** P_LVALUE_940 = &(PTMP_tmp0_66);
    PrtFreeValue(*P_LVALUE_940);
    *P_LVALUE_940 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
    
    PRT_VALUE** P_LVALUE_941 = &(PTMP_tmp1_55);
    PrtFreeValue(*P_LVALUE_941);
    *P_LVALUE_941 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp0_66) - PrtPrimGetInt((&P_LIT_INT32_52)));
    
    {
        PRT_VALUE** P_LVALUE_942 = &(P_VAR_lastLogIndex_2);
        PrtFreeValue(*P_LVALUE_942);
        *P_LVALUE_942 = PTMP_tmp1_55;
        PTMP_tmp1_55 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_943 = &(PTMP_tmp2_48);
    PrtFreeValue(*P_LVALUE_943);
    *P_LVALUE_943 = PrtCloneValue(P_VAR_lastLogIndex_2);
    
    PRT_VALUE** P_LVALUE_944 = &(PTMP_tmp3_43);
    PrtFreeValue(*P_LVALUE_944);
    *P_LVALUE_944 = PrtCloneValue((&P_LIT_BOOLEAN_28));
    
    PRT_VALUE** P_LVALUE_945 = &(PTMP_tmp4_36);
    PrtFreeValue(*P_LVALUE_945);
    *P_LVALUE_945 = ((_P_GEN_funargs[0] = &(PTMP_tmp2_48)), (_P_GEN_funargs[1] = &(PTMP_tmp3_43)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp2_48), PTMP_tmp2_48 = NULL), (PrtFreeValue(PTMP_tmp3_43), PTMP_tmp3_43 = NULL), (_P_GEN_funval));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_69;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_69;
    }
    
    {
        PRT_VALUE** P_LVALUE_946 = &(P_VAR_lastLogTerm_1);
        PrtFreeValue(*P_LVALUE_946);
        *P_LVALUE_946 = PTMP_tmp4_36;
        PTMP_tmp4_36 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_947 = &(PTMP_tmp5_27);
    PrtFreeValue(*P_LVALUE_947);
    *P_LVALUE_947 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
    
    PRT_VALUE** P_LVALUE_948 = &(PTMP_tmp6_25);
    PrtFreeValue(*P_LVALUE_948);
    *P_LVALUE_948 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp5_27) - PrtPrimGetInt((&P_LIT_INT32_52)));
    
    {
        PRT_VALUE** P_LVALUE_949 = &(P_VAR_lastCfgLogIndex_2);
        PrtFreeValue(*P_LVALUE_949);
        *P_LVALUE_949 = PTMP_tmp6_25;
        PTMP_tmp6_25 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_950 = &(PTMP_tmp7_23);
    PrtFreeValue(*P_LVALUE_950);
    *P_LVALUE_950 = PrtCloneValue(P_VAR_lastCfgLogIndex_2);
    
    PRT_VALUE** P_LVALUE_951 = &(PTMP_tmp8_20);
    PrtFreeValue(*P_LVALUE_951);
    *P_LVALUE_951 = PrtCloneValue((&P_LIT_BOOLEAN_29));
    
    PRT_VALUE** P_LVALUE_952 = &(PTMP_tmp9_17);
    PrtFreeValue(*P_LVALUE_952);
    *P_LVALUE_952 = ((_P_GEN_funargs[0] = &(PTMP_tmp7_23)), (_P_GEN_funargs[1] = &(PTMP_tmp8_20)), (_P_GEN_funval = P_GetLogTermForIndex_IMPL(context, _P_GEN_funargs)), (PrtFreeValue(PTMP_tmp7_23), PTMP_tmp7_23 = NULL), (PrtFreeValue(PTMP_tmp8_20), PTMP_tmp8_20 = NULL), (_P_GEN_funval));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_69;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_69;
    }
    
    {
        PRT_VALUE** P_LVALUE_953 = &(P_VAR_lastCfgLogTerm_1);
        PrtFreeValue(*P_LVALUE_953);
        *P_LVALUE_953 = PTMP_tmp9_17;
        PTMP_tmp9_17 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_954 = &(PTMP_tmp10_16);
    PrtFreeValue(*P_LVALUE_954);
    *P_LVALUE_954 = PrtTupleGet(*P_VAR_request_17, 0);
    
    PRT_VALUE** P_LVALUE_955 = &(PTMP_tmp11_16);
    PrtFreeValue(*P_LVALUE_955);
    *P_LVALUE_955 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp10_16) < PrtPrimGetInt(p_this->varValues[3]));
    
    PRT_VALUE** P_LVALUE_956 = &(PTMP_tmp17_7);
    PrtFreeValue(*P_LVALUE_956);
    *P_LVALUE_956 = PrtCloneValue(PTMP_tmp11_16);
    
    if (PrtPrimGetBool(PTMP_tmp17_7))
    {
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_957 = &(PTMP_tmp12_15);
        PrtFreeValue(*P_LVALUE_957);
        *P_LVALUE_957 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        PRT_VALUE** P_LVALUE_958 = &(PTMP_tmp13_14);
        PrtFreeValue(*P_LVALUE_958);
        *P_LVALUE_958 = PrtMkBoolValue(!PrtIsEqualValue(p_this->varValues[4], PTMP_tmp12_15));
        
        PRT_VALUE** P_LVALUE_959 = &(PTMP_tmp16_9);
        PrtFreeValue(*P_LVALUE_959);
        *P_LVALUE_959 = PrtCloneValue(PTMP_tmp13_14);
        
        if (PrtPrimGetBool(PTMP_tmp16_9))
        {
            PRT_VALUE** P_LVALUE_960 = &(PTMP_tmp14_13);
            PrtFreeValue(*P_LVALUE_960);
            *P_LVALUE_960 = PrtTupleGet(*P_VAR_request_17, 1);
            
            PRT_VALUE** P_LVALUE_961 = &(PTMP_tmp15_10);
            PrtFreeValue(*P_LVALUE_961);
            *P_LVALUE_961 = PrtMkBoolValue(!PrtIsEqualValue(p_this->varValues[4], PTMP_tmp14_13));
            
            PRT_VALUE** P_LVALUE_962 = &(PTMP_tmp16_9);
            PrtFreeValue(*P_LVALUE_962);
            *P_LVALUE_962 = PrtCloneValue(PTMP_tmp15_10);
            
        }
        
        
        PRT_VALUE** P_LVALUE_963 = &(PTMP_tmp17_7);
        PrtFreeValue(*P_LVALUE_963);
        *P_LVALUE_963 = PrtCloneValue(PTMP_tmp16_9);
        
    }
    
    
    PRT_VALUE** P_LVALUE_964 = &(PTMP_tmp21_7);
    PrtFreeValue(*P_LVALUE_964);
    *P_LVALUE_964 = PrtCloneValue(PTMP_tmp17_7);
    
    if (PrtPrimGetBool(PTMP_tmp21_7))
    {
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_965 = &(PTMP_tmp18_7);
        PrtFreeValue(*P_LVALUE_965);
        *P_LVALUE_965 = PrtTupleGet(*P_VAR_request_17, 2);
        
        PRT_VALUE** P_LVALUE_966 = &(PTMP_tmp19_7);
        PrtFreeValue(*P_LVALUE_966);
        *P_LVALUE_966 = PrtTupleGet(PTMP_tmp18_7, 0);
        
        PRT_VALUE** P_LVALUE_967 = &(PTMP_tmp20_7);
        PrtFreeValue(*P_LVALUE_967);
        *P_LVALUE_967 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_lastLogIndex_2) > PrtPrimGetInt(PTMP_tmp19_7));
        
        PRT_VALUE** P_LVALUE_968 = &(PTMP_tmp21_7);
        PrtFreeValue(*P_LVALUE_968);
        *P_LVALUE_968 = PrtCloneValue(PTMP_tmp20_7);
        
    }
    
    
    PRT_VALUE** P_LVALUE_969 = &(PTMP_tmp25_5);
    PrtFreeValue(*P_LVALUE_969);
    *P_LVALUE_969 = PrtCloneValue(PTMP_tmp21_7);
    
    if (PrtPrimGetBool(PTMP_tmp25_5))
    {
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_970 = &(PTMP_tmp22_7);
        PrtFreeValue(*P_LVALUE_970);
        *P_LVALUE_970 = PrtTupleGet(*P_VAR_request_17, 3);
        
        PRT_VALUE** P_LVALUE_971 = &(PTMP_tmp23_6);
        PrtFreeValue(*P_LVALUE_971);
        *P_LVALUE_971 = PrtTupleGet(PTMP_tmp22_7, 0);
        
        PRT_VALUE** P_LVALUE_972 = &(PTMP_tmp24_5);
        PrtFreeValue(*P_LVALUE_972);
        *P_LVALUE_972 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_lastLogTerm_1) > PrtPrimGetInt(PTMP_tmp23_6));
        
        PRT_VALUE** P_LVALUE_973 = &(PTMP_tmp25_5);
        PrtFreeValue(*P_LVALUE_973);
        *P_LVALUE_973 = PrtCloneValue(PTMP_tmp24_5);
        
    }
    
    
    PRT_VALUE** P_LVALUE_974 = &(PTMP_tmp29_5);
    PrtFreeValue(*P_LVALUE_974);
    *P_LVALUE_974 = PrtCloneValue(PTMP_tmp25_5);
    
    if (PrtPrimGetBool(PTMP_tmp29_5))
    {
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_975 = &(PTMP_tmp26_5);
        PrtFreeValue(*P_LVALUE_975);
        *P_LVALUE_975 = PrtTupleGet(*P_VAR_request_17, 2);
        
        PRT_VALUE** P_LVALUE_976 = &(PTMP_tmp27_5);
        PrtFreeValue(*P_LVALUE_976);
        *P_LVALUE_976 = PrtTupleGet(PTMP_tmp26_5, 1);
        
        PRT_VALUE** P_LVALUE_977 = &(PTMP_tmp28_5);
        PrtFreeValue(*P_LVALUE_977);
        *P_LVALUE_977 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_lastCfgLogIndex_2) > PrtPrimGetInt(PTMP_tmp27_5));
        
        PRT_VALUE** P_LVALUE_978 = &(PTMP_tmp29_5);
        PrtFreeValue(*P_LVALUE_978);
        *P_LVALUE_978 = PrtCloneValue(PTMP_tmp28_5);
        
    }
    
    
    PRT_VALUE** P_LVALUE_979 = &(PTMP_tmp33_3);
    PrtFreeValue(*P_LVALUE_979);
    *P_LVALUE_979 = PrtCloneValue(PTMP_tmp29_5);
    
    if (PrtPrimGetBool(PTMP_tmp33_3))
    {
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_980 = &(PTMP_tmp30_4);
        PrtFreeValue(*P_LVALUE_980);
        *P_LVALUE_980 = PrtTupleGet(*P_VAR_request_17, 3);
        
        PRT_VALUE** P_LVALUE_981 = &(PTMP_tmp31_3);
        PrtFreeValue(*P_LVALUE_981);
        *P_LVALUE_981 = PrtTupleGet(PTMP_tmp30_4, 1);
        
        PRT_VALUE** P_LVALUE_982 = &(PTMP_tmp32_3);
        PrtFreeValue(*P_LVALUE_982);
        *P_LVALUE_982 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_lastCfgLogTerm_1) > PrtPrimGetInt(PTMP_tmp31_3));
        
        PRT_VALUE** P_LVALUE_983 = &(PTMP_tmp33_3);
        PrtFreeValue(*P_LVALUE_983);
        *P_LVALUE_983 = PrtCloneValue(PTMP_tmp32_3);
        
    }
    
    
    if (PrtPrimGetBool(PTMP_tmp33_3))
    {
        PRT_VALUE** P_LVALUE_984 = &(PTMP_tmp34_3);
        PrtFreeValue(*P_LVALUE_984);
        *P_LVALUE_984 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
        
        PRT_VALUE** P_LVALUE_985 = &(PTMP_tmp35_3);
        PrtFreeValue(*P_LVALUE_985);
        *P_LVALUE_985 = PrtTupleGet(*P_VAR_request_17, 1);
        
        PrtFormatPrintf("\n [Server] ", 4, (p_this->id), p_this->varValues[3], PTMP_tmp34_3, PTMP_tmp35_3, 4, 0, " | term ", 1, " | log ", 2, " | Reject ", 3, "");
        
        PRT_VALUE** P_LVALUE_986 = &(PTMP_tmp36_2);
        PrtFreeValue(*P_LVALUE_986);
        *P_LVALUE_986 = PrtTupleGet(*P_VAR_request_17, 1);
        
        PRT_VALUE** P_LVALUE_987 = &(PTMP_tmp37_2);
        PrtFreeValue(*P_LVALUE_987);
        *P_LVALUE_987 = PrtCloneValue(PTMP_tmp36_2);
        
        PRT_VALUE** P_LVALUE_988 = &(PTMP_tmp38_2);
        PrtFreeValue(*P_LVALUE_988);
        *P_LVALUE_988 = PrtCloneValue((&P_EVENT_VoteResponse.value));
        
        PRT_VALUE** P_LVALUE_989 = &(PTMP_tmp39_2);
        PrtFreeValue(*P_LVALUE_989);
        *P_LVALUE_989 = PrtCloneValue(p_this->varValues[3]);
        
        PRT_VALUE** P_LVALUE_990 = &(PTMP_tmp40_2);
        PrtFreeValue(*P_LVALUE_990);
        *P_LVALUE_990 = PrtCloneValue((&P_LIT_BOOLEAN_29));
        
        PRT_VALUE** P_LVALUE_991 = &(PTMP_tmp41_2);
        PrtFreeValue(*P_LVALUE_991);
        *P_LVALUE_991 = (PrtMkTuple(&P_GEND_TYPE_T2ib, &(PTMP_tmp39_2), &(PTMP_tmp40_2)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp37_2), PTMP_tmp38_2, 1, &(PTMP_tmp41_2));
        *(&(PTMP_tmp38_2)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_69;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_69;
        }
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_992 = &(PTMP_tmp42_2);
        PrtFreeValue(*P_LVALUE_992);
        *P_LVALUE_992 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
        
        PRT_VALUE** P_LVALUE_993 = &(PTMP_tmp43_2);
        PrtFreeValue(*P_LVALUE_993);
        *P_LVALUE_993 = PrtTupleGet(*P_VAR_request_17, 1);
        
        PrtFormatPrintf("\n [Server] ", 4, (p_this->id), p_this->varValues[3], PTMP_tmp42_2, PTMP_tmp43_2, 4, 0, " | term ", 1, " | log ", 2, " | Approve ", 3, "");
        
        PRT_VALUE** P_LVALUE_994 = &(p_this->varValues[16]);
        PrtFreeValue(*P_LVALUE_994);
        *P_LVALUE_994 = PrtCloneValue((&P_LIT_INT32_53));
        
        PRT_VALUE** P_LVALUE_995 = &(PTMP_tmp44_2);
        PrtFreeValue(*P_LVALUE_995);
        *P_LVALUE_995 = PrtTupleGet(*P_VAR_request_17, 1);
        
        {
            PRT_VALUE** P_LVALUE_996 = &(p_this->varValues[4]);
            PrtFreeValue(*P_LVALUE_996);
            *P_LVALUE_996 = PTMP_tmp44_2;
            PTMP_tmp44_2 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_997 = &(PTMP_tmp45_2);
        PrtFreeValue(*P_LVALUE_997);
        *P_LVALUE_997 = PrtMkDefaultValue(&P_GEND_TYPE_m);
        
        {
            PRT_VALUE** P_LVALUE_998 = &(p_this->varValues[2]);
            PrtFreeValue(*P_LVALUE_998);
            *P_LVALUE_998 = PTMP_tmp45_2;
            PTMP_tmp45_2 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_999 = &(PTMP_tmp46_2);
        PrtFreeValue(*P_LVALUE_999);
        *P_LVALUE_999 = PrtTupleGet(*P_VAR_request_17, 1);
        
        PRT_VALUE** P_LVALUE_1000 = &(PTMP_tmp47_2);
        PrtFreeValue(*P_LVALUE_1000);
        *P_LVALUE_1000 = PrtCloneValue(PTMP_tmp46_2);
        
        PRT_VALUE** P_LVALUE_1001 = &(PTMP_tmp48_2);
        PrtFreeValue(*P_LVALUE_1001);
        *P_LVALUE_1001 = PrtCloneValue((&P_EVENT_VoteResponse.value));
        
        PRT_VALUE** P_LVALUE_1002 = &(PTMP_tmp49_2);
        PrtFreeValue(*P_LVALUE_1002);
        *P_LVALUE_1002 = PrtCloneValue(p_this->varValues[3]);
        
        PRT_VALUE** P_LVALUE_1003 = &(PTMP_tmp50_2);
        PrtFreeValue(*P_LVALUE_1003);
        *P_LVALUE_1003 = PrtCloneValue((&P_LIT_BOOLEAN_28));
        
        PRT_VALUE** P_LVALUE_1004 = &(PTMP_tmp51_2);
        PrtFreeValue(*P_LVALUE_1004);
        *P_LVALUE_1004 = (PrtMkTuple(&P_GEND_TYPE_T2ib, &(PTMP_tmp49_2), &(PTMP_tmp50_2)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp47_2), PTMP_tmp48_2, 1, &(PTMP_tmp51_2));
        *(&(PTMP_tmp48_2)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_69;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_69;
        }
        
    }
    
    
p_return_69: ;
    PrtFreeValue(P_VAR_lastLogIndex_2); P_VAR_lastLogIndex_2 = NULL;
    PrtFreeValue(P_VAR_lastLogTerm_1); P_VAR_lastLogTerm_1 = NULL;
    PrtFreeValue(P_VAR_lastCfgLogIndex_2); P_VAR_lastCfgLogIndex_2 = NULL;
    PrtFreeValue(P_VAR_lastCfgLogTerm_1); P_VAR_lastCfgLogTerm_1 = NULL;
    PrtFreeValue(PTMP_tmp0_66); PTMP_tmp0_66 = NULL;
    PrtFreeValue(PTMP_tmp1_55); PTMP_tmp1_55 = NULL;
    PrtFreeValue(PTMP_tmp2_48); PTMP_tmp2_48 = NULL;
    PrtFreeValue(PTMP_tmp3_43); PTMP_tmp3_43 = NULL;
    PrtFreeValue(PTMP_tmp4_36); PTMP_tmp4_36 = NULL;
    PrtFreeValue(PTMP_tmp5_27); PTMP_tmp5_27 = NULL;
    PrtFreeValue(PTMP_tmp6_25); PTMP_tmp6_25 = NULL;
    PrtFreeValue(PTMP_tmp7_23); PTMP_tmp7_23 = NULL;
    PrtFreeValue(PTMP_tmp8_20); PTMP_tmp8_20 = NULL;
    PrtFreeValue(PTMP_tmp9_17); PTMP_tmp9_17 = NULL;
    PrtFreeValue(PTMP_tmp10_16); PTMP_tmp10_16 = NULL;
    PrtFreeValue(PTMP_tmp11_16); PTMP_tmp11_16 = NULL;
    PrtFreeValue(PTMP_tmp12_15); PTMP_tmp12_15 = NULL;
    PrtFreeValue(PTMP_tmp13_14); PTMP_tmp13_14 = NULL;
    PrtFreeValue(PTMP_tmp14_13); PTMP_tmp14_13 = NULL;
    PrtFreeValue(PTMP_tmp15_10); PTMP_tmp15_10 = NULL;
    PrtFreeValue(PTMP_tmp16_9); PTMP_tmp16_9 = NULL;
    PrtFreeValue(PTMP_tmp17_7); PTMP_tmp17_7 = NULL;
    PrtFreeValue(PTMP_tmp18_7); PTMP_tmp18_7 = NULL;
    PrtFreeValue(PTMP_tmp19_7); PTMP_tmp19_7 = NULL;
    PrtFreeValue(PTMP_tmp20_7); PTMP_tmp20_7 = NULL;
    PrtFreeValue(PTMP_tmp21_7); PTMP_tmp21_7 = NULL;
    PrtFreeValue(PTMP_tmp22_7); PTMP_tmp22_7 = NULL;
    PrtFreeValue(PTMP_tmp23_6); PTMP_tmp23_6 = NULL;
    PrtFreeValue(PTMP_tmp24_5); PTMP_tmp24_5 = NULL;
    PrtFreeValue(PTMP_tmp25_5); PTMP_tmp25_5 = NULL;
    PrtFreeValue(PTMP_tmp26_5); PTMP_tmp26_5 = NULL;
    PrtFreeValue(PTMP_tmp27_5); PTMP_tmp27_5 = NULL;
    PrtFreeValue(PTMP_tmp28_5); PTMP_tmp28_5 = NULL;
    PrtFreeValue(PTMP_tmp29_5); PTMP_tmp29_5 = NULL;
    PrtFreeValue(PTMP_tmp30_4); PTMP_tmp30_4 = NULL;
    PrtFreeValue(PTMP_tmp31_3); PTMP_tmp31_3 = NULL;
    PrtFreeValue(PTMP_tmp32_3); PTMP_tmp32_3 = NULL;
    PrtFreeValue(PTMP_tmp33_3); PTMP_tmp33_3 = NULL;
    PrtFreeValue(PTMP_tmp34_3); PTMP_tmp34_3 = NULL;
    PrtFreeValue(PTMP_tmp35_3); PTMP_tmp35_3 = NULL;
    PrtFreeValue(PTMP_tmp36_2); PTMP_tmp36_2 = NULL;
    PrtFreeValue(PTMP_tmp37_2); PTMP_tmp37_2 = NULL;
    PrtFreeValue(PTMP_tmp38_2); PTMP_tmp38_2 = NULL;
    PrtFreeValue(PTMP_tmp39_2); PTMP_tmp39_2 = NULL;
    PrtFreeValue(PTMP_tmp40_2); PTMP_tmp40_2 = NULL;
    PrtFreeValue(PTMP_tmp41_2); PTMP_tmp41_2 = NULL;
    PrtFreeValue(PTMP_tmp42_2); PTMP_tmp42_2 = NULL;
    PrtFreeValue(PTMP_tmp43_2); PTMP_tmp43_2 = NULL;
    PrtFreeValue(PTMP_tmp44_2); PTMP_tmp44_2 = NULL;
    PrtFreeValue(PTMP_tmp45_2); PTMP_tmp45_2 = NULL;
    PrtFreeValue(PTMP_tmp46_2); PTMP_tmp46_2 = NULL;
    PrtFreeValue(PTMP_tmp47_2); PTMP_tmp47_2 = NULL;
    PrtFreeValue(PTMP_tmp48_2); PTMP_tmp48_2 = NULL;
    PrtFreeValue(PTMP_tmp49_2); PTMP_tmp49_2 = NULL;
    PrtFreeValue(PTMP_tmp50_2); PTMP_tmp50_2 = NULL;
    PrtFreeValue(PTMP_tmp51_2); PTMP_tmp51_2 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Vote =
{
    "Vote",
    &P_Vote_IMPL,
    NULL
};


PRT_VALUE* P_AppendEntries_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = PrtMkDefaultValue(&P_GEND_TYPE_b);
    PRT_VALUE** P_VAR_request_18 = argRefs[0];
    PRT_VALUE* P_VAR_idx_10 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_cfgLogIdx_2 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* P_VAR_cfg_success = PrtMkDefaultValue(&P_GEND_TYPE_b);
    PRT_VALUE* P_VAR_kv_success = PrtMkDefaultValue(&P_GEND_TYPE_b);
    PRT_VALUE* PTMP_tmp0_67 = NULL;
    PRT_VALUE* PTMP_tmp1_56 = NULL;
    PRT_VALUE* PTMP_tmp2_49 = NULL;
    PRT_VALUE* PTMP_tmp3_44 = NULL;
    PRT_VALUE* PTMP_tmp4_37 = NULL;
    PRT_VALUE* PTMP_tmp5_28 = NULL;
    PRT_VALUE* PTMP_tmp6_26 = NULL;
    PRT_VALUE* PTMP_tmp7_24 = NULL;
    PRT_VALUE* PTMP_tmp8_21 = NULL;
    PRT_VALUE* PTMP_tmp9_18 = NULL;
    PRT_VALUE* PTMP_tmp10_17 = NULL;
    PRT_VALUE* PTMP_tmp11_17 = NULL;
    PRT_VALUE* PTMP_tmp12_16 = NULL;
    PRT_VALUE* PTMP_tmp13_15 = NULL;
    PRT_VALUE* PTMP_tmp14_14 = NULL;
    PRT_VALUE* PTMP_tmp15_11 = NULL;
    PRT_VALUE* PTMP_tmp16_10 = NULL;
    PRT_VALUE* PTMP_tmp17_8 = NULL;
    PRT_VALUE* PTMP_tmp18_8 = NULL;
    PRT_VALUE* PTMP_tmp19_8 = NULL;
    PRT_VALUE* PTMP_tmp20_8 = NULL;
    PRT_VALUE* PTMP_tmp21_8 = NULL;
    PRT_VALUE* PTMP_tmp22_8 = NULL;
    PRT_VALUE* PTMP_tmp23_7 = NULL;
    PRT_VALUE* PTMP_tmp24_6 = NULL;
    PRT_VALUE* PTMP_tmp25_6 = NULL;
    PRT_VALUE* PTMP_tmp26_6 = NULL;
    PRT_VALUE* PTMP_tmp27_6 = NULL;
    PRT_VALUE* PTMP_tmp28_6 = NULL;
    PRT_VALUE* PTMP_tmp29_6 = NULL;
    PRT_VALUE* PTMP_tmp30_5 = NULL;
    PRT_VALUE* PTMP_tmp31_4 = NULL;
    PRT_VALUE* PTMP_tmp32_4 = NULL;
    PRT_VALUE* PTMP_tmp33_4 = NULL;
    PRT_VALUE* PTMP_tmp34_4 = NULL;
    PRT_VALUE* PTMP_tmp35_4 = NULL;
    PRT_VALUE* PTMP_tmp36_3 = NULL;
    PRT_VALUE* PTMP_tmp37_3 = NULL;
    PRT_VALUE* PTMP_tmp38_3 = NULL;
    PRT_VALUE* PTMP_tmp39_3 = NULL;
    PRT_VALUE* PTMP_tmp40_3 = NULL;
    PRT_VALUE* PTMP_tmp41_3 = NULL;
    PRT_VALUE* PTMP_tmp42_3 = NULL;
    PRT_VALUE* PTMP_tmp43_3 = NULL;
    PRT_VALUE* PTMP_tmp44_3 = NULL;
    PRT_VALUE* PTMP_tmp45_3 = NULL;
    PRT_VALUE* PTMP_tmp46_3 = NULL;
    PRT_VALUE* PTMP_tmp47_3 = NULL;
    PRT_VALUE* PTMP_tmp48_3 = NULL;
    PRT_VALUE* PTMP_tmp49_3 = NULL;
    PRT_VALUE* PTMP_tmp50_3 = NULL;
    PRT_VALUE* PTMP_tmp51_3 = NULL;
    PRT_VALUE* PTMP_tmp52_2 = NULL;
    PRT_VALUE* PTMP_tmp53_2 = NULL;
    PRT_VALUE* PTMP_tmp54_2 = NULL;
    PRT_VALUE* PTMP_tmp55_2 = NULL;
    PRT_VALUE* PTMP_tmp56_2 = NULL;
    PRT_VALUE* PTMP_tmp57_2 = NULL;
    PRT_VALUE* PTMP_tmp58_2 = NULL;
    PRT_VALUE* PTMP_tmp59_2 = NULL;
    PRT_VALUE* PTMP_tmp60_2 = NULL;
    PRT_VALUE* PTMP_tmp61_2 = NULL;
    PRT_VALUE* PTMP_tmp62_2 = NULL;
    PRT_VALUE* PTMP_tmp63_2 = NULL;
    PRT_VALUE* PTMP_tmp64_2 = NULL;
    PRT_VALUE* PTMP_tmp65_2 = NULL;
    PRT_VALUE* PTMP_tmp66_2 = NULL;
    PRT_VALUE* PTMP_tmp67_1 = NULL;
    PRT_VALUE* PTMP_tmp68_1 = NULL;
    PRT_VALUE* PTMP_tmp69_1 = NULL;
    PRT_VALUE* PTMP_tmp70_1 = NULL;
    PRT_VALUE* PTMP_tmp71_1 = NULL;
    PRT_VALUE* PTMP_tmp72_1 = NULL;
    PRT_VALUE* PTMP_tmp73_1 = NULL;
    PRT_VALUE* PTMP_tmp74_1 = NULL;
    PRT_VALUE* PTMP_tmp75_1 = NULL;
    PRT_VALUE* PTMP_tmp76_1 = NULL;
    PRT_VALUE* PTMP_tmp77_1 = NULL;
    PRT_VALUE* PTMP_tmp78_1 = NULL;
    PRT_VALUE* PTMP_tmp79_1 = NULL;
    PRT_VALUE* PTMP_tmp80_1 = NULL;
    PRT_VALUE* PTMP_tmp81_1 = NULL;
    PRT_VALUE* PTMP_tmp82_1 = NULL;
    PRT_VALUE* PTMP_tmp83_1 = NULL;
    PRT_VALUE* PTMP_tmp84_1 = NULL;
    PRT_VALUE* PTMP_tmp85_1 = NULL;
    PRT_VALUE* PTMP_tmp86_1 = NULL;
    PRT_VALUE* PTMP_tmp87_1 = NULL;
    PRT_VALUE* PTMP_tmp88_1 = NULL;
    PRT_VALUE* PTMP_tmp89_1 = NULL;
    PRT_VALUE* PTMP_tmp90_1 = NULL;
    PRT_VALUE* PTMP_tmp91_1 = NULL;
    PRT_VALUE* PTMP_tmp92_1 = NULL;
    PRT_VALUE* PTMP_tmp93_1 = NULL;
    PRT_VALUE* PTMP_tmp94_1 = NULL;
    PRT_VALUE* PTMP_tmp95_1 = NULL;
    PRT_VALUE* PTMP_tmp96_1 = NULL;
    PRT_VALUE* PTMP_tmp97_1 = NULL;
    PRT_VALUE* PTMP_tmp98_1 = NULL;
    PRT_VALUE* PTMP_tmp99_1 = NULL;
    PRT_VALUE* PTMP_tmp100_1 = NULL;
    PRT_VALUE* PTMP_tmp101_1 = NULL;
    PRT_VALUE* PTMP_tmp102_1 = NULL;
    PRT_VALUE* PTMP_tmp103_1 = NULL;
    PRT_VALUE* PTMP_tmp104_1 = NULL;
    PRT_VALUE* PTMP_tmp105_1 = NULL;
    PRT_VALUE* PTMP_tmp106_1 = NULL;
    PRT_VALUE* PTMP_tmp107_1 = NULL;
    PRT_VALUE* PTMP_tmp108_1 = NULL;
    PRT_VALUE* PTMP_tmp109_1 = NULL;
    PRT_VALUE* PTMP_tmp110_1 = NULL;
    PRT_VALUE* PTMP_tmp111_1 = NULL;
    PRT_VALUE* PTMP_tmp112_1 = NULL;
    PRT_VALUE* PTMP_tmp113_1 = NULL;
    PRT_VALUE* PTMP_tmp114_1 = NULL;
    PRT_VALUE* PTMP_tmp115_1 = NULL;
    PRT_VALUE* PTMP_tmp116_1 = NULL;
    PRT_VALUE* PTMP_tmp117_1 = NULL;
    PRT_VALUE* PTMP_tmp118_1 = NULL;
    PRT_VALUE* PTMP_tmp119_1 = NULL;
    PRT_VALUE* PTMP_tmp120_1 = NULL;
    PRT_VALUE* PTMP_tmp121_1 = NULL;
    PRT_VALUE* PTMP_tmp122_1 = NULL;
    PRT_VALUE* PTMP_tmp123_1 = NULL;
    PRT_VALUE* PTMP_tmp124_1 = NULL;
    PRT_VALUE* PTMP_tmp125_1 = NULL;
    PRT_VALUE* PTMP_tmp126_1 = NULL;
    PRT_VALUE* PTMP_tmp127_1 = NULL;
    PRT_VALUE* PTMP_tmp128_1 = NULL;
    PRT_VALUE* PTMP_tmp129_1 = NULL;
    PRT_VALUE* PTMP_tmp130_1 = NULL;
    PRT_VALUE* PTMP_tmp131_1 = NULL;
    PRT_VALUE* PTMP_tmp132_1 = NULL;
    PRT_VALUE* PTMP_tmp133_1 = NULL;
    PRT_VALUE* PTMP_tmp134_1 = NULL;
    PRT_VALUE* PTMP_tmp135_1 = NULL;
    PRT_VALUE* PTMP_tmp136_1 = NULL;
    PRT_VALUE* PTMP_tmp137_1 = NULL;
    PRT_VALUE* PTMP_tmp138_1 = NULL;
    PRT_VALUE* PTMP_tmp139_1 = NULL;
    PRT_VALUE* PTMP_tmp140_1 = NULL;
    PRT_VALUE* PTMP_tmp141_1 = NULL;
    PRT_VALUE* PTMP_tmp142_1 = NULL;
    PRT_VALUE* PTMP_tmp143_1 = NULL;
    PRT_VALUE* PTMP_tmp144_1 = NULL;
    PRT_VALUE* PTMP_tmp145_1 = NULL;
    PRT_VALUE* PTMP_tmp146_1 = NULL;
    PRT_VALUE* PTMP_tmp147_1 = NULL;
    PRT_VALUE* PTMP_tmp148_1 = NULL;
    PRT_VALUE* PTMP_tmp149_1 = NULL;
    PRT_VALUE* PTMP_tmp150_1 = NULL;
    PRT_VALUE* PTMP_tmp151_1 = NULL;
    PRT_VALUE* PTMP_tmp152_1 = NULL;
    PRT_VALUE* PTMP_tmp153_1 = NULL;
    PRT_VALUE* PTMP_tmp154_1 = NULL;
    PRT_VALUE* PTMP_tmp155_1 = NULL;
    PRT_VALUE* PTMP_tmp156_1 = NULL;
    PRT_VALUE* PTMP_tmp157_1 = NULL;
    PRT_VALUE* PTMP_tmp158_1 = NULL;
    PRT_VALUE* PTMP_tmp159_1 = NULL;
    PRT_VALUE* PTMP_tmp160_1 = NULL;
    PRT_VALUE* PTMP_tmp161_1 = NULL;
    PRT_VALUE* PTMP_tmp162_1 = NULL;
    PRT_VALUE* PTMP_tmp163_1 = NULL;
    PRT_VALUE* PTMP_tmp164_1 = NULL;
    PRT_VALUE* PTMP_tmp165_1 = NULL;
    PRT_VALUE* PTMP_tmp166_1 = NULL;
    PRT_VALUE* PTMP_tmp167_1 = NULL;
    PRT_VALUE* PTMP_tmp168_1 = NULL;
    PRT_VALUE* PTMP_tmp169_1 = NULL;
    PRT_VALUE* PTMP_tmp170_1 = NULL;
    PRT_VALUE* PTMP_tmp171_1 = NULL;
    PRT_VALUE* PTMP_tmp172_1 = NULL;
    PRT_VALUE* PTMP_tmp173_1 = NULL;
    PRT_VALUE* PTMP_tmp174_1 = NULL;
    PRT_VALUE* PTMP_tmp175_1 = NULL;
    PRT_VALUE* PTMP_tmp176_1 = NULL;
    PRT_VALUE* PTMP_tmp177_1 = NULL;
    PRT_VALUE* PTMP_tmp178_1 = NULL;
    PRT_VALUE* PTMP_tmp179_1 = NULL;
    PRT_VALUE* PTMP_tmp180_1 = NULL;
    PRT_VALUE* PTMP_tmp181_1 = NULL;
    PRT_VALUE* PTMP_tmp182_1 = NULL;
    PRT_VALUE* PTMP_tmp183_1 = NULL;
    PRT_VALUE* PTMP_tmp184_1 = NULL;
    PRT_VALUE* PTMP_tmp185_1 = NULL;
    PRT_VALUE* PTMP_tmp186_1 = NULL;
    PRT_VALUE* PTMP_tmp187_1 = NULL;
    PRT_VALUE* PTMP_tmp188_1 = NULL;
    PRT_VALUE* PTMP_tmp189_1 = NULL;
    PRT_VALUE* PTMP_tmp190_1 = NULL;
    PRT_VALUE* PTMP_tmp191_1 = NULL;
    PRT_VALUE* PTMP_tmp192_1 = NULL;
    PRT_VALUE* PTMP_tmp193_1 = NULL;
    PRT_VALUE* PTMP_tmp194_1 = NULL;
    PRT_VALUE* PTMP_tmp195_1 = NULL;
    PRT_VALUE* PTMP_tmp196_1 = NULL;
    PRT_VALUE* PTMP_tmp197_1 = NULL;
    PRT_VALUE* PTMP_tmp198_1 = NULL;
    PRT_VALUE* PTMP_tmp199_1 = NULL;
    PRT_VALUE* PTMP_tmp200_1 = NULL;
    PRT_VALUE* PTMP_tmp201_1 = NULL;
    PRT_VALUE* PTMP_tmp202_1 = NULL;
    PRT_VALUE* PTMP_tmp203_1 = NULL;
    PRT_VALUE* PTMP_tmp204 = NULL;
    PRT_VALUE* PTMP_tmp205 = NULL;
    PRT_VALUE* PTMP_tmp206 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_54 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_55 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_30 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_FALSE } };
    PRT_VALUE P_LIT_BOOLEAN_31 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_1005 = &(P_VAR_cfg_success);
    PrtFreeValue(*P_LVALUE_1005);
    *P_LVALUE_1005 = PrtCloneValue((&P_LIT_BOOLEAN_30));
    
    PRT_VALUE** P_LVALUE_1006 = &(P_VAR_kv_success);
    PrtFreeValue(*P_LVALUE_1006);
    *P_LVALUE_1006 = PrtCloneValue((&P_LIT_BOOLEAN_30));
    
    PRT_VALUE** P_LVALUE_1007 = &(PTMP_tmp0_67);
    PrtFreeValue(*P_LVALUE_1007);
    *P_LVALUE_1007 = PrtTupleGet(*P_VAR_request_18, 0);
    
    PRT_VALUE** P_LVALUE_1008 = &(PTMP_tmp1_56);
    PrtFreeValue(*P_LVALUE_1008);
    *P_LVALUE_1008 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp0_67) < PrtPrimGetInt(p_this->varValues[3]));
    
    if (PrtPrimGetBool(PTMP_tmp1_56))
    {
        PRT_VALUE** P_LVALUE_1009 = &(PTMP_tmp2_49);
        PrtFreeValue(*P_LVALUE_1009);
        *P_LVALUE_1009 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
        
        PrtFormatPrintf("\n[Server] ", 3, (p_this->id), p_this->varValues[3], PTMP_tmp2_49, 3, 0, " | term ", 1, " | log ", 2, " | append false (<term) \n");
        
        PRT_VALUE** P_LVALUE_1010 = &(PTMP_tmp3_44);
        PrtFreeValue(*P_LVALUE_1010);
        *P_LVALUE_1010 = PrtTupleGet(*P_VAR_request_18, 1);
        
        PRT_VALUE** P_LVALUE_1011 = &(PTMP_tmp4_37);
        PrtFreeValue(*P_LVALUE_1011);
        *P_LVALUE_1011 = PrtCloneValue(PTMP_tmp3_44);
        
        PRT_VALUE** P_LVALUE_1012 = &(PTMP_tmp5_28);
        PrtFreeValue(*P_LVALUE_1012);
        *P_LVALUE_1012 = PrtCloneValue((&P_EVENT_AppendEntriesResponse.value));
        
        PRT_VALUE** P_LVALUE_1013 = &(PTMP_tmp6_26);
        PrtFreeValue(*P_LVALUE_1013);
        *P_LVALUE_1013 = PrtCloneValue(p_this->varValues[3]);
        
        PRT_VALUE** P_LVALUE_1014 = &(PTMP_tmp7_24);
        PrtFreeValue(*P_LVALUE_1014);
        *P_LVALUE_1014 = PrtCloneValue((&P_LIT_BOOLEAN_30));
        
        PRT_VALUE** P_LVALUE_1015 = &(PTMP_tmp8_21);
        PrtFreeValue(*P_LVALUE_1015);
        *P_LVALUE_1015 = PrtCloneValue((&P_LIT_BOOLEAN_30));
        
        PRT_VALUE** P_LVALUE_1016 = &(PTMP_tmp9_18);
        PrtFreeValue(*P_LVALUE_1016);
        *P_LVALUE_1016 = PrtCloneValue((&P_LIT_BOOLEAN_30));
        
        PRT_VALUE** P_LVALUE_1017 = &(PTMP_tmp10_17);
        PrtFreeValue(*P_LVALUE_1017);
        *P_LVALUE_1017 = PrtCloneValue((p_this->id));
        
        PRT_VALUE** P_LVALUE_1018 = &(PTMP_tmp11_17);
        PrtFreeValue(*P_LVALUE_1018);
        *P_LVALUE_1018 = PrtTupleGet(*P_VAR_request_18, 7);
        
        PRT_VALUE** P_LVALUE_1019 = &(PTMP_tmp12_16);
        PrtFreeValue(*P_LVALUE_1019);
        *P_LVALUE_1019 = (PrtMkTuple(&P_GEND_TYPE_T6ibbbRm, &(PTMP_tmp6_26), &(PTMP_tmp7_24), &(PTMP_tmp8_21), &(PTMP_tmp9_18), &(PTMP_tmp10_17), &(PTMP_tmp11_17)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp4_37), PTMP_tmp5_28, 1, &(PTMP_tmp12_16));
        *(&(PTMP_tmp5_28)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_70;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_70;
        }
        
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = PrtCloneValue((&P_LIT_BOOLEAN_30));
        goto p_return_70;
        
    }
    
    else
    {
        PRT_VALUE** P_LVALUE_1020 = &(PTMP_tmp13_15);
        PrtFreeValue(*P_LVALUE_1020);
        *P_LVALUE_1020 = PrtTupleGet(*P_VAR_request_18, 2);
        
        PRT_VALUE** P_LVALUE_1021 = &(PTMP_tmp14_14);
        PrtFreeValue(*P_LVALUE_1021);
        *P_LVALUE_1021 = PrtTupleGet(PTMP_tmp13_15, 0);
        
        PRT_VALUE** P_LVALUE_1022 = &(PTMP_tmp15_11);
        PrtFreeValue(*P_LVALUE_1022);
        *P_LVALUE_1022 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp14_14) >= PrtPrimGetInt((&P_LIT_INT32_54)));
        
        PRT_VALUE** P_LVALUE_1023 = &(PTMP_tmp20_8);
        PrtFreeValue(*P_LVALUE_1023);
        *P_LVALUE_1023 = PrtCloneValue(PTMP_tmp15_11);
        
        if (PrtPrimGetBool(PTMP_tmp20_8))
        {
            PRT_VALUE** P_LVALUE_1024 = &(PTMP_tmp16_10);
            PrtFreeValue(*P_LVALUE_1024);
            *P_LVALUE_1024 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
            
            PRT_VALUE** P_LVALUE_1025 = &(PTMP_tmp17_8);
            PrtFreeValue(*P_LVALUE_1025);
            *P_LVALUE_1025 = PrtTupleGet(*P_VAR_request_18, 2);
            
            PRT_VALUE** P_LVALUE_1026 = &(PTMP_tmp18_8);
            PrtFreeValue(*P_LVALUE_1026);
            *P_LVALUE_1026 = PrtTupleGet(PTMP_tmp17_8, 0);
            
            PRT_VALUE** P_LVALUE_1027 = &(PTMP_tmp19_8);
            PrtFreeValue(*P_LVALUE_1027);
            *P_LVALUE_1027 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp16_10) <= PrtPrimGetInt(PTMP_tmp18_8));
            
            PRT_VALUE** P_LVALUE_1028 = &(PTMP_tmp20_8);
            PrtFreeValue(*P_LVALUE_1028);
            *P_LVALUE_1028 = PrtCloneValue(PTMP_tmp19_8);
            
        }
        
        
        PRT_VALUE** P_LVALUE_1029 = &(PTMP_tmp29_6);
        PrtFreeValue(*P_LVALUE_1029);
        *P_LVALUE_1029 = PrtCloneValue(PTMP_tmp20_8);
        
        if (PrtPrimGetBool(PTMP_tmp29_6))
        {
        }
        
        else
        {
            PRT_VALUE** P_LVALUE_1030 = &(PTMP_tmp21_8);
            PrtFreeValue(*P_LVALUE_1030);
            *P_LVALUE_1030 = PrtTupleGet(*P_VAR_request_18, 2);
            
            PRT_VALUE** P_LVALUE_1031 = &(PTMP_tmp22_8);
            PrtFreeValue(*P_LVALUE_1031);
            *P_LVALUE_1031 = PrtTupleGet(PTMP_tmp21_8, 1);
            
            PRT_VALUE** P_LVALUE_1032 = &(PTMP_tmp23_7);
            PrtFreeValue(*P_LVALUE_1032);
            *P_LVALUE_1032 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp22_8) >= PrtPrimGetInt((&P_LIT_INT32_54)));
            
            PRT_VALUE** P_LVALUE_1033 = &(PTMP_tmp28_6);
            PrtFreeValue(*P_LVALUE_1033);
            *P_LVALUE_1033 = PrtCloneValue(PTMP_tmp23_7);
            
            if (PrtPrimGetBool(PTMP_tmp28_6))
            {
                PRT_VALUE** P_LVALUE_1034 = &(PTMP_tmp24_6);
                PrtFreeValue(*P_LVALUE_1034);
                *P_LVALUE_1034 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                
                PRT_VALUE** P_LVALUE_1035 = &(PTMP_tmp25_6);
                PrtFreeValue(*P_LVALUE_1035);
                *P_LVALUE_1035 = PrtTupleGet(*P_VAR_request_18, 2);
                
                PRT_VALUE** P_LVALUE_1036 = &(PTMP_tmp26_6);
                PrtFreeValue(*P_LVALUE_1036);
                *P_LVALUE_1036 = PrtTupleGet(PTMP_tmp25_6, 1);
                
                PRT_VALUE** P_LVALUE_1037 = &(PTMP_tmp27_6);
                PrtFreeValue(*P_LVALUE_1037);
                *P_LVALUE_1037 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp24_6) <= PrtPrimGetInt(PTMP_tmp26_6));
                
                PRT_VALUE** P_LVALUE_1038 = &(PTMP_tmp28_6);
                PrtFreeValue(*P_LVALUE_1038);
                *P_LVALUE_1038 = PrtCloneValue(PTMP_tmp27_6);
                
            }
            
            
            PRT_VALUE** P_LVALUE_1039 = &(PTMP_tmp29_6);
            PrtFreeValue(*P_LVALUE_1039);
            *P_LVALUE_1039 = PrtCloneValue(PTMP_tmp28_6);
            
        }
        
        
        PRT_VALUE** P_LVALUE_1040 = &(PTMP_tmp41_3);
        PrtFreeValue(*P_LVALUE_1040);
        *P_LVALUE_1040 = PrtCloneValue(PTMP_tmp29_6);
        
        if (PrtPrimGetBool(PTMP_tmp41_3))
        {
        }
        
        else
        {
            PRT_VALUE** P_LVALUE_1041 = &(PTMP_tmp30_5);
            PrtFreeValue(*P_LVALUE_1041);
            *P_LVALUE_1041 = PrtTupleGet(*P_VAR_request_18, 2);
            
            PRT_VALUE** P_LVALUE_1042 = &(PTMP_tmp31_4);
            PrtFreeValue(*P_LVALUE_1042);
            *P_LVALUE_1042 = PrtTupleGet(PTMP_tmp30_5, 0);
            
            PRT_VALUE** P_LVALUE_1043 = &(PTMP_tmp32_4);
            PrtFreeValue(*P_LVALUE_1043);
            *P_LVALUE_1043 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp31_4) >= PrtPrimGetInt((&P_LIT_INT32_54)));
            
            PRT_VALUE** P_LVALUE_1044 = &(PTMP_tmp40_3);
            PrtFreeValue(*P_LVALUE_1044);
            *P_LVALUE_1044 = PrtCloneValue(PTMP_tmp32_4);
            
            if (PrtPrimGetBool(PTMP_tmp40_3))
            {
                PRT_VALUE** P_LVALUE_1045 = &(PTMP_tmp33_4);
                PrtFreeValue(*P_LVALUE_1045);
                *P_LVALUE_1045 = PrtTupleGet(*P_VAR_request_18, 2);
                
                PRT_VALUE** P_LVALUE_1046 = &(PTMP_tmp34_4);
                PrtFreeValue(*P_LVALUE_1046);
                *P_LVALUE_1046 = PrtTupleGet(PTMP_tmp33_4, 0);
                
                PRT_VALUE** P_LVALUE_1047 = &(PTMP_tmp35_4);
                PrtFreeValue(*P_LVALUE_1047);
                *P_LVALUE_1047 = PrtSeqGet(p_this->varValues[5], PTMP_tmp34_4);
                
                PRT_VALUE** P_LVALUE_1048 = &(PTMP_tmp36_3);
                PrtFreeValue(*P_LVALUE_1048);
                *P_LVALUE_1048 = PrtTupleGet(PTMP_tmp35_4, 0);
                
                PRT_VALUE** P_LVALUE_1049 = &(PTMP_tmp37_3);
                PrtFreeValue(*P_LVALUE_1049);
                *P_LVALUE_1049 = PrtTupleGet(*P_VAR_request_18, 3);
                
                PRT_VALUE** P_LVALUE_1050 = &(PTMP_tmp38_3);
                PrtFreeValue(*P_LVALUE_1050);
                *P_LVALUE_1050 = PrtTupleGet(PTMP_tmp37_3, 0);
                
                PRT_VALUE** P_LVALUE_1051 = &(PTMP_tmp39_3);
                PrtFreeValue(*P_LVALUE_1051);
                *P_LVALUE_1051 = PrtMkBoolValue(!PrtIsEqualValue(PTMP_tmp36_3, PTMP_tmp38_3));
                
                PRT_VALUE** P_LVALUE_1052 = &(PTMP_tmp40_3);
                PrtFreeValue(*P_LVALUE_1052);
                *P_LVALUE_1052 = PrtCloneValue(PTMP_tmp39_3);
                
            }
            
            
            PRT_VALUE** P_LVALUE_1053 = &(PTMP_tmp41_3);
            PrtFreeValue(*P_LVALUE_1053);
            *P_LVALUE_1053 = PrtCloneValue(PTMP_tmp40_3);
            
        }
        
        
        PRT_VALUE** P_LVALUE_1054 = &(PTMP_tmp53_2);
        PrtFreeValue(*P_LVALUE_1054);
        *P_LVALUE_1054 = PrtCloneValue(PTMP_tmp41_3);
        
        if (PrtPrimGetBool(PTMP_tmp53_2))
        {
        }
        
        else
        {
            PRT_VALUE** P_LVALUE_1055 = &(PTMP_tmp42_3);
            PrtFreeValue(*P_LVALUE_1055);
            *P_LVALUE_1055 = PrtTupleGet(*P_VAR_request_18, 2);
            
            PRT_VALUE** P_LVALUE_1056 = &(PTMP_tmp43_3);
            PrtFreeValue(*P_LVALUE_1056);
            *P_LVALUE_1056 = PrtTupleGet(PTMP_tmp42_3, 1);
            
            PRT_VALUE** P_LVALUE_1057 = &(PTMP_tmp44_3);
            PrtFreeValue(*P_LVALUE_1057);
            *P_LVALUE_1057 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp43_3) >= PrtPrimGetInt((&P_LIT_INT32_54)));
            
            PRT_VALUE** P_LVALUE_1058 = &(PTMP_tmp52_2);
            PrtFreeValue(*P_LVALUE_1058);
            *P_LVALUE_1058 = PrtCloneValue(PTMP_tmp44_3);
            
            if (PrtPrimGetBool(PTMP_tmp52_2))
            {
                PRT_VALUE** P_LVALUE_1059 = &(PTMP_tmp45_3);
                PrtFreeValue(*P_LVALUE_1059);
                *P_LVALUE_1059 = PrtTupleGet(*P_VAR_request_18, 2);
                
                PRT_VALUE** P_LVALUE_1060 = &(PTMP_tmp46_3);
                PrtFreeValue(*P_LVALUE_1060);
                *P_LVALUE_1060 = PrtTupleGet(PTMP_tmp45_3, 1);
                
                PRT_VALUE** P_LVALUE_1061 = &(PTMP_tmp47_3);
                PrtFreeValue(*P_LVALUE_1061);
                *P_LVALUE_1061 = PrtSeqGet(p_this->varValues[6], PTMP_tmp46_3);
                
                PRT_VALUE** P_LVALUE_1062 = &(PTMP_tmp48_3);
                PrtFreeValue(*P_LVALUE_1062);
                *P_LVALUE_1062 = PrtTupleGet(PTMP_tmp47_3, 0);
                
                PRT_VALUE** P_LVALUE_1063 = &(PTMP_tmp49_3);
                PrtFreeValue(*P_LVALUE_1063);
                *P_LVALUE_1063 = PrtTupleGet(*P_VAR_request_18, 3);
                
                PRT_VALUE** P_LVALUE_1064 = &(PTMP_tmp50_3);
                PrtFreeValue(*P_LVALUE_1064);
                *P_LVALUE_1064 = PrtTupleGet(PTMP_tmp49_3, 1);
                
                PRT_VALUE** P_LVALUE_1065 = &(PTMP_tmp51_3);
                PrtFreeValue(*P_LVALUE_1065);
                *P_LVALUE_1065 = PrtMkBoolValue(!PrtIsEqualValue(PTMP_tmp48_3, PTMP_tmp50_3));
                
                PRT_VALUE** P_LVALUE_1066 = &(PTMP_tmp52_2);
                PrtFreeValue(*P_LVALUE_1066);
                *P_LVALUE_1066 = PrtCloneValue(PTMP_tmp51_3);
                
            }
            
            
            PRT_VALUE** P_LVALUE_1067 = &(PTMP_tmp53_2);
            PrtFreeValue(*P_LVALUE_1067);
            *P_LVALUE_1067 = PrtCloneValue(PTMP_tmp52_2);
            
        }
        
        
        if (PrtPrimGetBool(PTMP_tmp53_2))
        {
            PRT_VALUE** P_LVALUE_1068 = &(PTMP_tmp54_2);
            PrtFreeValue(*P_LVALUE_1068);
            *P_LVALUE_1068 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
            
            PrtFormatPrintf("\n[Leader] ", 3, (p_this->id), p_this->varValues[3], PTMP_tmp54_2, 3, 0, " | term ", 1, " | log ", 2, " | append false (not in log)\n");
            
            PRT_VALUE** P_LVALUE_1069 = &(PTMP_tmp55_2);
            PrtFreeValue(*P_LVALUE_1069);
            *P_LVALUE_1069 = PrtTupleGet(*P_VAR_request_18, 1);
            
            PRT_VALUE** P_LVALUE_1070 = &(PTMP_tmp56_2);
            PrtFreeValue(*P_LVALUE_1070);
            *P_LVALUE_1070 = PrtCloneValue(PTMP_tmp55_2);
            
            PRT_VALUE** P_LVALUE_1071 = &(PTMP_tmp57_2);
            PrtFreeValue(*P_LVALUE_1071);
            *P_LVALUE_1071 = PrtCloneValue((&P_EVENT_AppendEntriesResponse.value));
            
            PRT_VALUE** P_LVALUE_1072 = &(PTMP_tmp58_2);
            PrtFreeValue(*P_LVALUE_1072);
            *P_LVALUE_1072 = PrtCloneValue(p_this->varValues[3]);
            
            PRT_VALUE** P_LVALUE_1073 = &(PTMP_tmp59_2);
            PrtFreeValue(*P_LVALUE_1073);
            *P_LVALUE_1073 = PrtCloneValue((&P_LIT_BOOLEAN_30));
            
            PRT_VALUE** P_LVALUE_1074 = &(PTMP_tmp60_2);
            PrtFreeValue(*P_LVALUE_1074);
            *P_LVALUE_1074 = PrtCloneValue((&P_LIT_BOOLEAN_30));
            
            PRT_VALUE** P_LVALUE_1075 = &(PTMP_tmp61_2);
            PrtFreeValue(*P_LVALUE_1075);
            *P_LVALUE_1075 = PrtCloneValue((&P_LIT_BOOLEAN_30));
            
            PRT_VALUE** P_LVALUE_1076 = &(PTMP_tmp62_2);
            PrtFreeValue(*P_LVALUE_1076);
            *P_LVALUE_1076 = PrtCloneValue((p_this->id));
            
            PRT_VALUE** P_LVALUE_1077 = &(PTMP_tmp63_2);
            PrtFreeValue(*P_LVALUE_1077);
            *P_LVALUE_1077 = PrtTupleGet(*P_VAR_request_18, 7);
            
            PRT_VALUE** P_LVALUE_1078 = &(PTMP_tmp64_2);
            PrtFreeValue(*P_LVALUE_1078);
            *P_LVALUE_1078 = (PrtMkTuple(&P_GEND_TYPE_T6ibbbRm, &(PTMP_tmp58_2), &(PTMP_tmp59_2), &(PTMP_tmp60_2), &(PTMP_tmp61_2), &(PTMP_tmp62_2), &(PTMP_tmp63_2)));
            
            PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp56_2), PTMP_tmp57_2, 1, &(PTMP_tmp64_2));
            *(&(PTMP_tmp57_2)) = NULL;
            if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                goto p_return_70;
            }
            if (p_this->isHalted == PRT_TRUE) {
                PrtFreeValue(_P_GEN_retval);
                _P_GEN_retval = NULL;
                goto p_return_70;
            }
            
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = PrtCloneValue((&P_LIT_BOOLEAN_30));
            goto p_return_70;
            
        }
        
        else
        {
            PRT_VALUE** P_LVALUE_1079 = &(P_VAR_idx_10);
            PrtFreeValue(*P_LVALUE_1079);
            *P_LVALUE_1079 = PrtCloneValue((&P_LIT_INT32_54));
            
            PRT_VALUE** P_LVALUE_1080 = &(PTMP_tmp65_2);
            PrtFreeValue(*P_LVALUE_1080);
            *P_LVALUE_1080 = PrtTupleGet(*P_VAR_request_18, 1);
            
            PRT_VALUE** P_LVALUE_1081 = &(PTMP_tmp66_2);
            PrtFreeValue(*P_LVALUE_1081);
            *P_LVALUE_1081 = PrtMkBoolValue(PrtIsEqualValue(p_this->varValues[2], PTMP_tmp65_2));
            
            if (PrtPrimGetBool(PTMP_tmp66_2))
            {
                PRT_VALUE** P_LVALUE_1082 = &(p_this->varValues[16]);
                PrtFreeValue(*P_LVALUE_1082);
                *P_LVALUE_1082 = PrtCloneValue((&P_LIT_INT32_54));
                
            }
            
            else
            {
            }
            
            
            while (PrtPrimGetBool((&P_LIT_BOOLEAN_31)))
            {
                PRT_VALUE** P_LVALUE_1083 = &(PTMP_tmp67_1);
                PrtFreeValue(*P_LVALUE_1083);
                *P_LVALUE_1083 = PrtTupleGet(*P_VAR_request_18, 4);
                
                PRT_VALUE** P_LVALUE_1084 = &(PTMP_tmp68_1);
                PrtFreeValue(*P_LVALUE_1084);
                *P_LVALUE_1084 = PrtMkIntValue(PrtSeqSizeOf(PTMP_tmp67_1));
                
                PRT_VALUE** P_LVALUE_1085 = &(PTMP_tmp69_1);
                PrtFreeValue(*P_LVALUE_1085);
                *P_LVALUE_1085 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_10) < PrtPrimGetInt(PTMP_tmp68_1));
                
                PRT_VALUE** P_LVALUE_1086 = &(PTMP_tmp76_1);
                PrtFreeValue(*P_LVALUE_1086);
                *P_LVALUE_1086 = PrtCloneValue(PTMP_tmp69_1);
                
                if (PrtPrimGetBool(PTMP_tmp76_1))
                {
                    PRT_VALUE** P_LVALUE_1087 = &(PTMP_tmp70_1);
                    PrtFreeValue(*P_LVALUE_1087);
                    *P_LVALUE_1087 = PrtTupleGet(*P_VAR_request_18, 2);
                    
                    PRT_VALUE** P_LVALUE_1088 = &(PTMP_tmp71_1);
                    PrtFreeValue(*P_LVALUE_1088);
                    *P_LVALUE_1088 = PrtTupleGet(PTMP_tmp70_1, 0);
                    
                    PRT_VALUE** P_LVALUE_1089 = &(PTMP_tmp72_1);
                    PrtFreeValue(*P_LVALUE_1089);
                    *P_LVALUE_1089 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_10) + PrtPrimGetInt(PTMP_tmp71_1));
                    
                    PRT_VALUE** P_LVALUE_1090 = &(PTMP_tmp73_1);
                    PrtFreeValue(*P_LVALUE_1090);
                    *P_LVALUE_1090 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp72_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                    
                    PRT_VALUE** P_LVALUE_1091 = &(PTMP_tmp74_1);
                    PrtFreeValue(*P_LVALUE_1091);
                    *P_LVALUE_1091 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                    
                    PRT_VALUE** P_LVALUE_1092 = &(PTMP_tmp75_1);
                    PrtFreeValue(*P_LVALUE_1092);
                    *P_LVALUE_1092 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp73_1) < PrtPrimGetInt(PTMP_tmp74_1));
                    
                    PRT_VALUE** P_LVALUE_1093 = &(PTMP_tmp76_1);
                    PrtFreeValue(*P_LVALUE_1093);
                    *P_LVALUE_1093 = PrtCloneValue(PTMP_tmp75_1);
                    
                }
                
                
                PRT_VALUE** P_LVALUE_1094 = &(PTMP_tmp77_1);
                PrtFreeValue(*P_LVALUE_1094);
                *P_LVALUE_1094 = PrtCloneValue(PTMP_tmp76_1);
                
                if (PrtPrimGetBool(PTMP_tmp77_1))
                {
                }
                
                else
                {
                    break;
                    
                }
                
                
                PRT_VALUE** P_LVALUE_1095 = &(PTMP_tmp78_1);
                PrtFreeValue(*P_LVALUE_1095);
                *P_LVALUE_1095 = PrtTupleGet(*P_VAR_request_18, 2);
                
                PRT_VALUE** P_LVALUE_1096 = &(PTMP_tmp79_1);
                PrtFreeValue(*P_LVALUE_1096);
                *P_LVALUE_1096 = PrtTupleGet(PTMP_tmp78_1, 0);
                
                PRT_VALUE** P_LVALUE_1097 = &(PTMP_tmp80_1);
                PrtFreeValue(*P_LVALUE_1097);
                *P_LVALUE_1097 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_10) + PrtPrimGetInt(PTMP_tmp79_1));
                
                PRT_VALUE** P_LVALUE_1098 = &(PTMP_tmp81_1);
                PrtFreeValue(*P_LVALUE_1098);
                *P_LVALUE_1098 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp80_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                
                PRT_VALUE** P_LVALUE_1099 = &(PTMP_tmp82_1);
                PrtFreeValue(*P_LVALUE_1099);
                *P_LVALUE_1099 = PrtSeqGet(p_this->varValues[5], PTMP_tmp81_1);
                
                PRT_VALUE** P_LVALUE_1100 = &(PTMP_tmp83_1);
                PrtFreeValue(*P_LVALUE_1100);
                *P_LVALUE_1100 = PrtTupleGet(*P_VAR_request_18, 4);
                
                PRT_VALUE** P_LVALUE_1101 = &(PTMP_tmp84_1);
                PrtFreeValue(*P_LVALUE_1101);
                *P_LVALUE_1101 = PrtSeqGet(PTMP_tmp83_1, P_VAR_idx_10);
                
                PRT_VALUE** P_LVALUE_1102 = &(PTMP_tmp85_1);
                PrtFreeValue(*P_LVALUE_1102);
                *P_LVALUE_1102 = PrtMkBoolValue(!PrtIsEqualValue(PTMP_tmp82_1, PTMP_tmp84_1));
                
                if (PrtPrimGetBool(PTMP_tmp85_1))
                {
                    PRT_VALUE** P_LVALUE_1103 = &(PTMP_tmp86_1);
                    PrtFreeValue(*P_LVALUE_1103);
                    *P_LVALUE_1103 = PrtTupleGet(*P_VAR_request_18, 2);
                    
                    PRT_VALUE** P_LVALUE_1104 = &(PTMP_tmp87_1);
                    PrtFreeValue(*P_LVALUE_1104);
                    *P_LVALUE_1104 = PrtTupleGet(PTMP_tmp86_1, 0);
                    
                    PRT_VALUE** P_LVALUE_1105 = &(PTMP_tmp88_1);
                    PrtFreeValue(*P_LVALUE_1105);
                    *P_LVALUE_1105 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_10) + PrtPrimGetInt(PTMP_tmp87_1));
                    
                    PRT_VALUE** P_LVALUE_1106 = &(PTMP_tmp89_1);
                    PrtFreeValue(*P_LVALUE_1106);
                    *P_LVALUE_1106 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp88_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                    
                    PrtFormatPrintf("[Follower | AppendEntries] Conflict: Deleting from log entry ", 1, PTMP_tmp89_1, 1, 0, " on");
                    
                    PRT_VALUE** P_LVALUE_1107 = &(PTMP_tmp90_1);
                    PrtFreeValue(*P_LVALUE_1107);
                    *P_LVALUE_1107 = PrtTupleGet(*P_VAR_request_18, 2);
                    
                    PRT_VALUE** P_LVALUE_1108 = &(PTMP_tmp91_1);
                    PrtFreeValue(*P_LVALUE_1108);
                    *P_LVALUE_1108 = PrtTupleGet(PTMP_tmp90_1, 0);
                    
                    PRT_VALUE** P_LVALUE_1109 = &(PTMP_tmp92_1);
                    PrtFreeValue(*P_LVALUE_1109);
                    *P_LVALUE_1109 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_10) + PrtPrimGetInt(PTMP_tmp91_1));
                    
                    PRT_VALUE** P_LVALUE_1110 = &(PTMP_tmp93_1);
                    PrtFreeValue(*P_LVALUE_1110);
                    *P_LVALUE_1110 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp92_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                    
                    PRT_VALUE** P_LVALUE_1111 = &(PTMP_tmp94_1);
                    PrtFreeValue(*P_LVALUE_1111);
                    *P_LVALUE_1111 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                    
                    PRT_VALUE** P_LVALUE_1112 = &(PTMP_tmp95_1);
                    PrtFreeValue(*P_LVALUE_1112);
                    *P_LVALUE_1112 = PrtCloneValue((&P_LIT_BOOLEAN_31));
                    
                    _P_GEN_funargs[0] = &(PTMP_tmp93_1);
                    _P_GEN_funargs[1] = &(PTMP_tmp94_1);
                    _P_GEN_funargs[2] = &(PTMP_tmp95_1);
                    PrtFreeValue(P_DeleteFromLog_IMPL(context, _P_GEN_funargs));
                    PrtFreeValue(PTMP_tmp93_1);
                    PTMP_tmp93_1 = NULL;
                    PrtFreeValue(PTMP_tmp94_1);
                    PTMP_tmp94_1 = NULL;
                    PrtFreeValue(PTMP_tmp95_1);
                    PTMP_tmp95_1 = NULL;
                    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                        goto p_return_70;
                    }
                    if (p_this->isHalted == PRT_TRUE) {
                        PrtFreeValue(_P_GEN_retval);
                        _P_GEN_retval = NULL;
                        goto p_return_70;
                    }
                    
                    break;
                    
                }
                
                else
                {
                }
                
                
                PRT_VALUE** P_LVALUE_1113 = &(PTMP_tmp96_1);
                PrtFreeValue(*P_LVALUE_1113);
                *P_LVALUE_1113 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_10) + PrtPrimGetInt((&P_LIT_INT32_55)));
                
                {
                    PRT_VALUE** P_LVALUE_1114 = &(P_VAR_idx_10);
                    PrtFreeValue(*P_LVALUE_1114);
                    *P_LVALUE_1114 = PTMP_tmp96_1;
                    PTMP_tmp96_1 = NULL;
                }
                
            }
            
            
            while (PrtPrimGetBool((&P_LIT_BOOLEAN_31)))
            {
                PRT_VALUE** P_LVALUE_1115 = &(PTMP_tmp97_1);
                PrtFreeValue(*P_LVALUE_1115);
                *P_LVALUE_1115 = PrtTupleGet(*P_VAR_request_18, 5);
                
                PRT_VALUE** P_LVALUE_1116 = &(PTMP_tmp98_1);
                PrtFreeValue(*P_LVALUE_1116);
                *P_LVALUE_1116 = PrtMkIntValue(PrtSeqSizeOf(PTMP_tmp97_1));
                
                PRT_VALUE** P_LVALUE_1117 = &(PTMP_tmp99_1);
                PrtFreeValue(*P_LVALUE_1117);
                *P_LVALUE_1117 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) < PrtPrimGetInt(PTMP_tmp98_1));
                
                PRT_VALUE** P_LVALUE_1118 = &(PTMP_tmp106_1);
                PrtFreeValue(*P_LVALUE_1118);
                *P_LVALUE_1118 = PrtCloneValue(PTMP_tmp99_1);
                
                if (PrtPrimGetBool(PTMP_tmp106_1))
                {
                    PRT_VALUE** P_LVALUE_1119 = &(PTMP_tmp100_1);
                    PrtFreeValue(*P_LVALUE_1119);
                    *P_LVALUE_1119 = PrtTupleGet(*P_VAR_request_18, 2);
                    
                    PRT_VALUE** P_LVALUE_1120 = &(PTMP_tmp101_1);
                    PrtFreeValue(*P_LVALUE_1120);
                    *P_LVALUE_1120 = PrtTupleGet(PTMP_tmp100_1, 1);
                    
                    PRT_VALUE** P_LVALUE_1121 = &(PTMP_tmp102_1);
                    PrtFreeValue(*P_LVALUE_1121);
                    *P_LVALUE_1121 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) + PrtPrimGetInt(PTMP_tmp101_1));
                    
                    PRT_VALUE** P_LVALUE_1122 = &(PTMP_tmp103_1);
                    PrtFreeValue(*P_LVALUE_1122);
                    *P_LVALUE_1122 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp102_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                    
                    PRT_VALUE** P_LVALUE_1123 = &(PTMP_tmp104_1);
                    PrtFreeValue(*P_LVALUE_1123);
                    *P_LVALUE_1123 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                    
                    PRT_VALUE** P_LVALUE_1124 = &(PTMP_tmp105_1);
                    PrtFreeValue(*P_LVALUE_1124);
                    *P_LVALUE_1124 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp103_1) < PrtPrimGetInt(PTMP_tmp104_1));
                    
                    PRT_VALUE** P_LVALUE_1125 = &(PTMP_tmp106_1);
                    PrtFreeValue(*P_LVALUE_1125);
                    *P_LVALUE_1125 = PrtCloneValue(PTMP_tmp105_1);
                    
                }
                
                
                PRT_VALUE** P_LVALUE_1126 = &(PTMP_tmp107_1);
                PrtFreeValue(*P_LVALUE_1126);
                *P_LVALUE_1126 = PrtCloneValue(PTMP_tmp106_1);
                
                if (PrtPrimGetBool(PTMP_tmp107_1))
                {
                }
                
                else
                {
                    break;
                    
                }
                
                
                PRT_VALUE** P_LVALUE_1127 = &(PTMP_tmp108_1);
                PrtFreeValue(*P_LVALUE_1127);
                *P_LVALUE_1127 = PrtTupleGet(*P_VAR_request_18, 2);
                
                PRT_VALUE** P_LVALUE_1128 = &(PTMP_tmp109_1);
                PrtFreeValue(*P_LVALUE_1128);
                *P_LVALUE_1128 = PrtTupleGet(PTMP_tmp108_1, 1);
                
                PRT_VALUE** P_LVALUE_1129 = &(PTMP_tmp110_1);
                PrtFreeValue(*P_LVALUE_1129);
                *P_LVALUE_1129 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) + PrtPrimGetInt(PTMP_tmp109_1));
                
                PRT_VALUE** P_LVALUE_1130 = &(PTMP_tmp111_1);
                PrtFreeValue(*P_LVALUE_1130);
                *P_LVALUE_1130 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp110_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                
                PRT_VALUE** P_LVALUE_1131 = &(PTMP_tmp112_1);
                PrtFreeValue(*P_LVALUE_1131);
                *P_LVALUE_1131 = PrtSeqGet(p_this->varValues[6], PTMP_tmp111_1);
                
                PRT_VALUE** P_LVALUE_1132 = &(PTMP_tmp113_1);
                PrtFreeValue(*P_LVALUE_1132);
                *P_LVALUE_1132 = PrtTupleGet(*P_VAR_request_18, 5);
                
                PRT_VALUE** P_LVALUE_1133 = &(PTMP_tmp114_1);
                PrtFreeValue(*P_LVALUE_1133);
                *P_LVALUE_1133 = PrtSeqGet(PTMP_tmp113_1, P_VAR_cfgLogIdx_2);
                
                PRT_VALUE** P_LVALUE_1134 = &(PTMP_tmp115_1);
                PrtFreeValue(*P_LVALUE_1134);
                *P_LVALUE_1134 = PrtMkBoolValue(!PrtIsEqualValue(PTMP_tmp112_1, PTMP_tmp114_1));
                
                if (PrtPrimGetBool(PTMP_tmp115_1))
                {
                    PRT_VALUE** P_LVALUE_1135 = &(PTMP_tmp116_1);
                    PrtFreeValue(*P_LVALUE_1135);
                    *P_LVALUE_1135 = PrtTupleGet(*P_VAR_request_18, 2);
                    
                    PRT_VALUE** P_LVALUE_1136 = &(PTMP_tmp117_1);
                    PrtFreeValue(*P_LVALUE_1136);
                    *P_LVALUE_1136 = PrtTupleGet(PTMP_tmp116_1, 1);
                    
                    PRT_VALUE** P_LVALUE_1137 = &(PTMP_tmp118_1);
                    PrtFreeValue(*P_LVALUE_1137);
                    *P_LVALUE_1137 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) + PrtPrimGetInt(PTMP_tmp117_1));
                    
                    PRT_VALUE** P_LVALUE_1138 = &(PTMP_tmp119_1);
                    PrtFreeValue(*P_LVALUE_1138);
                    *P_LVALUE_1138 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp118_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                    
                    PrtFormatPrintf("[Follower | AppendEntries] Conflict: Deleting from config log entry ", 1, PTMP_tmp119_1, 1, 0, " on");
                    
                    PRT_VALUE** P_LVALUE_1139 = &(PTMP_tmp120_1);
                    PrtFreeValue(*P_LVALUE_1139);
                    *P_LVALUE_1139 = PrtTupleGet(*P_VAR_request_18, 2);
                    
                    PRT_VALUE** P_LVALUE_1140 = &(PTMP_tmp121_1);
                    PrtFreeValue(*P_LVALUE_1140);
                    *P_LVALUE_1140 = PrtTupleGet(PTMP_tmp120_1, 1);
                    
                    PRT_VALUE** P_LVALUE_1141 = &(PTMP_tmp122_1);
                    PrtFreeValue(*P_LVALUE_1141);
                    *P_LVALUE_1141 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) + PrtPrimGetInt(PTMP_tmp121_1));
                    
                    PRT_VALUE** P_LVALUE_1142 = &(PTMP_tmp123_1);
                    PrtFreeValue(*P_LVALUE_1142);
                    *P_LVALUE_1142 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp122_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                    
                    PRT_VALUE** P_LVALUE_1143 = &(PTMP_tmp124_1);
                    PrtFreeValue(*P_LVALUE_1143);
                    *P_LVALUE_1143 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                    
                    PRT_VALUE** P_LVALUE_1144 = &(PTMP_tmp125_1);
                    PrtFreeValue(*P_LVALUE_1144);
                    *P_LVALUE_1144 = PrtCloneValue((&P_LIT_BOOLEAN_30));
                    
                    _P_GEN_funargs[0] = &(PTMP_tmp123_1);
                    _P_GEN_funargs[1] = &(PTMP_tmp124_1);
                    _P_GEN_funargs[2] = &(PTMP_tmp125_1);
                    PrtFreeValue(P_DeleteFromLog_IMPL(context, _P_GEN_funargs));
                    PrtFreeValue(PTMP_tmp123_1);
                    PTMP_tmp123_1 = NULL;
                    PrtFreeValue(PTMP_tmp124_1);
                    PTMP_tmp124_1 = NULL;
                    PrtFreeValue(PTMP_tmp125_1);
                    PTMP_tmp125_1 = NULL;
                    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                        goto p_return_70;
                    }
                    if (p_this->isHalted == PRT_TRUE) {
                        PrtFreeValue(_P_GEN_retval);
                        _P_GEN_retval = NULL;
                        goto p_return_70;
                    }
                    
                    break;
                    
                }
                
                else
                {
                }
                
                
                PRT_VALUE** P_LVALUE_1145 = &(PTMP_tmp126_1);
                PrtFreeValue(*P_LVALUE_1145);
                *P_LVALUE_1145 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) + PrtPrimGetInt((&P_LIT_INT32_55)));
                
                {
                    PRT_VALUE** P_LVALUE_1146 = &(P_VAR_cfgLogIdx_2);
                    PrtFreeValue(*P_LVALUE_1146);
                    *P_LVALUE_1146 = PTMP_tmp126_1;
                    PTMP_tmp126_1 = NULL;
                }
                
            }
            
            
            while (PrtPrimGetBool((&P_LIT_BOOLEAN_31)))
            {
                PRT_VALUE** P_LVALUE_1147 = &(PTMP_tmp127_1);
                PrtFreeValue(*P_LVALUE_1147);
                *P_LVALUE_1147 = PrtTupleGet(*P_VAR_request_18, 4);
                
                PRT_VALUE** P_LVALUE_1148 = &(PTMP_tmp128_1);
                PrtFreeValue(*P_LVALUE_1148);
                *P_LVALUE_1148 = PrtMkIntValue(PrtSeqSizeOf(PTMP_tmp127_1));
                
                PRT_VALUE** P_LVALUE_1149 = &(PTMP_tmp129_1);
                PrtFreeValue(*P_LVALUE_1149);
                *P_LVALUE_1149 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_10) < PrtPrimGetInt(PTMP_tmp128_1));
                
                PRT_VALUE** P_LVALUE_1150 = &(PTMP_tmp130_1);
                PrtFreeValue(*P_LVALUE_1150);
                *P_LVALUE_1150 = PrtCloneValue(PTMP_tmp129_1);
                
                if (PrtPrimGetBool(PTMP_tmp130_1))
                {
                }
                
                else
                {
                    break;
                    
                }
                
                
                PRT_VALUE** P_LVALUE_1151 = &(PTMP_tmp131_1);
                PrtFreeValue(*P_LVALUE_1151);
                *P_LVALUE_1151 = PrtTupleGet(*P_VAR_request_18, 2);
                
                PRT_VALUE** P_LVALUE_1152 = &(PTMP_tmp132_1);
                PrtFreeValue(*P_LVALUE_1152);
                *P_LVALUE_1152 = PrtTupleGet(PTMP_tmp131_1, 0);
                
                PRT_VALUE** P_LVALUE_1153 = &(PTMP_tmp133_1);
                PrtFreeValue(*P_LVALUE_1153);
                *P_LVALUE_1153 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_10) + PrtPrimGetInt(PTMP_tmp132_1));
                
                PRT_VALUE** P_LVALUE_1154 = &(PTMP_tmp134_1);
                PrtFreeValue(*P_LVALUE_1154);
                *P_LVALUE_1154 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp133_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                
                PRT_VALUE** P_LVALUE_1155 = &(PTMP_tmp135_1);
                PrtFreeValue(*P_LVALUE_1155);
                *P_LVALUE_1155 = PrtTupleGet(*P_VAR_request_18, 4);
                
                PRT_VALUE** P_LVALUE_1156 = &(PTMP_tmp136_1);
                PrtFreeValue(*P_LVALUE_1156);
                *P_LVALUE_1156 = PrtSeqGet(PTMP_tmp135_1, P_VAR_idx_10);
                
                PrtSeqInsertEx(p_this->varValues[5], PTMP_tmp134_1, PTMP_tmp136_1, PRT_FALSE);
                *(&(PTMP_tmp136_1)) = NULL;
                
                PRT_VALUE** P_LVALUE_1157 = &(PTMP_tmp137_1);
                PrtFreeValue(*P_LVALUE_1157);
                *P_LVALUE_1157 = PrtCloneValue((p_this->id));
                
                PRT_VALUE** P_LVALUE_1158 = &(PTMP_tmp138_1);
                PrtFreeValue(*P_LVALUE_1158);
                *P_LVALUE_1158 = PrtCloneValue(p_this->varValues[5]);
                
                PRT_VALUE** P_LVALUE_1159 = &(PTMP_tmp139_1);
                PrtFreeValue(*P_LVALUE_1159);
                *P_LVALUE_1159 = (PrtMkTuple(&P_GEND_TYPE_T2RST3irr, &(PTMP_tmp137_1), &(PTMP_tmp138_1)));
                
                
                PRT_VALUE** P_LVALUE_1160 = &(PTMP_tmp140_1);
                PrtFreeValue(*P_LVALUE_1160);
                *P_LVALUE_1160 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_10) + PrtPrimGetInt((&P_LIT_INT32_55)));
                
                {
                    PRT_VALUE** P_LVALUE_1161 = &(P_VAR_idx_10);
                    PrtFreeValue(*P_LVALUE_1161);
                    *P_LVALUE_1161 = PTMP_tmp140_1;
                    PTMP_tmp140_1 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_1162 = &(P_VAR_kv_success);
                PrtFreeValue(*P_LVALUE_1162);
                *P_LVALUE_1162 = PrtCloneValue((&P_LIT_BOOLEAN_31));
                
            }
            
            
            while (PrtPrimGetBool((&P_LIT_BOOLEAN_31)))
            {
                PRT_VALUE** P_LVALUE_1163 = &(PTMP_tmp141_1);
                PrtFreeValue(*P_LVALUE_1163);
                *P_LVALUE_1163 = PrtTupleGet(*P_VAR_request_18, 5);
                
                PRT_VALUE** P_LVALUE_1164 = &(PTMP_tmp142_1);
                PrtFreeValue(*P_LVALUE_1164);
                *P_LVALUE_1164 = PrtMkIntValue(PrtSeqSizeOf(PTMP_tmp141_1));
                
                PRT_VALUE** P_LVALUE_1165 = &(PTMP_tmp143_1);
                PrtFreeValue(*P_LVALUE_1165);
                *P_LVALUE_1165 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) < PrtPrimGetInt(PTMP_tmp142_1));
                
                PRT_VALUE** P_LVALUE_1166 = &(PTMP_tmp144_1);
                PrtFreeValue(*P_LVALUE_1166);
                *P_LVALUE_1166 = PrtCloneValue(PTMP_tmp143_1);
                
                if (PrtPrimGetBool(PTMP_tmp144_1))
                {
                }
                
                else
                {
                    break;
                    
                }
                
                
                PRT_VALUE** P_LVALUE_1167 = &(PTMP_tmp145_1);
                PrtFreeValue(*P_LVALUE_1167);
                *P_LVALUE_1167 = PrtTupleGet(*P_VAR_request_18, 2);
                
                PRT_VALUE** P_LVALUE_1168 = &(PTMP_tmp146_1);
                PrtFreeValue(*P_LVALUE_1168);
                *P_LVALUE_1168 = PrtTupleGet(PTMP_tmp145_1, 1);
                
                PRT_VALUE** P_LVALUE_1169 = &(PTMP_tmp147_1);
                PrtFreeValue(*P_LVALUE_1169);
                *P_LVALUE_1169 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) + PrtPrimGetInt(PTMP_tmp146_1));
                
                PRT_VALUE** P_LVALUE_1170 = &(PTMP_tmp148_1);
                PrtFreeValue(*P_LVALUE_1170);
                *P_LVALUE_1170 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp147_1) + PrtPrimGetInt((&P_LIT_INT32_55)));
                
                PRT_VALUE** P_LVALUE_1171 = &(PTMP_tmp149_1);
                PrtFreeValue(*P_LVALUE_1171);
                *P_LVALUE_1171 = PrtTupleGet(*P_VAR_request_18, 5);
                
                PRT_VALUE** P_LVALUE_1172 = &(PTMP_tmp150_1);
                PrtFreeValue(*P_LVALUE_1172);
                *P_LVALUE_1172 = PrtSeqGet(PTMP_tmp149_1, P_VAR_cfgLogIdx_2);
                
                PrtSeqInsertEx(p_this->varValues[6], PTMP_tmp148_1, PTMP_tmp150_1, PRT_FALSE);
                *(&(PTMP_tmp150_1)) = NULL;
                
                PRT_VALUE** P_LVALUE_1173 = &(PTMP_tmp151_1);
                PrtFreeValue(*P_LVALUE_1173);
                *P_LVALUE_1173 = PrtMkIntValue(PrtPrimGetInt(P_VAR_cfgLogIdx_2) + PrtPrimGetInt((&P_LIT_INT32_55)));
                
                {
                    PRT_VALUE** P_LVALUE_1174 = &(P_VAR_cfgLogIdx_2);
                    PrtFreeValue(*P_LVALUE_1174);
                    *P_LVALUE_1174 = PTMP_tmp151_1;
                    PTMP_tmp151_1 = NULL;
                }
                
                PRT_VALUE** P_LVALUE_1175 = &(P_VAR_cfg_success);
                PrtFreeValue(*P_LVALUE_1175);
                *P_LVALUE_1175 = PrtCloneValue((&P_LIT_BOOLEAN_31));
                
            }
            
            
            PRT_VALUE** P_LVALUE_1176 = &(PTMP_tmp152_1);
            PrtFreeValue(*P_LVALUE_1176);
            *P_LVALUE_1176 = PrtTupleGet(*P_VAR_request_18, 5);
            
            PRT_VALUE** P_LVALUE_1177 = &(PTMP_tmp153_1);
            PrtFreeValue(*P_LVALUE_1177);
            *P_LVALUE_1177 = PrtMkIntValue(PrtSeqSizeOf(PTMP_tmp152_1));
            
            PRT_VALUE** P_LVALUE_1178 = &(PTMP_tmp154_1);
            PrtFreeValue(*P_LVALUE_1178);
            *P_LVALUE_1178 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp153_1) > PrtPrimGetInt((&P_LIT_INT32_54)));
            
            if (PrtPrimGetBool(PTMP_tmp154_1))
            {
                PRT_VALUE** P_LVALUE_1179 = &(PTMP_tmp155_1);
                PrtFreeValue(*P_LVALUE_1179);
                *P_LVALUE_1179 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                
                PRT_VALUE** P_LVALUE_1180 = &(PTMP_tmp156_1);
                PrtFreeValue(*P_LVALUE_1180);
                *P_LVALUE_1180 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp155_1) - PrtPrimGetInt((&P_LIT_INT32_55)));
                
                PRT_VALUE** P_LVALUE_1181 = &(PTMP_tmp157_1);
                PrtFreeValue(*P_LVALUE_1181);
                *P_LVALUE_1181 = PrtSeqGet(p_this->varValues[6], PTMP_tmp156_1);
                
                PRT_VALUE** P_LVALUE_1182 = &(PTMP_tmp158_1);
                PrtFreeValue(*P_LVALUE_1182);
                *P_LVALUE_1182 = PrtTupleGet(PTMP_tmp157_1, 1);
                
                {
                    PRT_VALUE** P_LVALUE_1183 = &(p_this->varValues[1]);
                    PrtFreeValue(*P_LVALUE_1183);
                    *P_LVALUE_1183 = PTMP_tmp158_1;
                    PTMP_tmp158_1 = NULL;
                }
                
            }
            
            else
            {
            }
            
            
            PrtPrintf("finishedloop");
            
            PRT_VALUE** P_LVALUE_1184 = &(PTMP_tmp159_1);
            PrtFreeValue(*P_LVALUE_1184);
            *P_LVALUE_1184 = PrtTupleGet(*P_VAR_request_18, 6);
            
            PRT_VALUE** P_LVALUE_1185 = &(PTMP_tmp160_1);
            PrtFreeValue(*P_LVALUE_1185);
            *P_LVALUE_1185 = PrtTupleGet(PTMP_tmp159_1, 0);
            
            PRT_VALUE** P_LVALUE_1186 = &(PTMP_tmp161_1);
            PrtFreeValue(*P_LVALUE_1186);
            *P_LVALUE_1186 = PrtTupleGet(p_this->varValues[8], 0);
            
            PRT_VALUE** P_LVALUE_1187 = &(PTMP_tmp162_1);
            PrtFreeValue(*P_LVALUE_1187);
            *P_LVALUE_1187 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp160_1) > PrtPrimGetInt(PTMP_tmp161_1));
            
            PRT_VALUE** P_LVALUE_1188 = &(PTMP_tmp167_1);
            PrtFreeValue(*P_LVALUE_1188);
            *P_LVALUE_1188 = PrtCloneValue(PTMP_tmp162_1);
            
            if (PrtPrimGetBool(PTMP_tmp167_1))
            {
                PRT_VALUE** P_LVALUE_1189 = &(PTMP_tmp163_1);
                PrtFreeValue(*P_LVALUE_1189);
                *P_LVALUE_1189 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                
                PRT_VALUE** P_LVALUE_1190 = &(PTMP_tmp164_1);
                PrtFreeValue(*P_LVALUE_1190);
                *P_LVALUE_1190 = PrtTupleGet(*P_VAR_request_18, 6);
                
                PRT_VALUE** P_LVALUE_1191 = &(PTMP_tmp165_1);
                PrtFreeValue(*P_LVALUE_1191);
                *P_LVALUE_1191 = PrtTupleGet(PTMP_tmp164_1, 0);
                
                PRT_VALUE** P_LVALUE_1192 = &(PTMP_tmp166_1);
                PrtFreeValue(*P_LVALUE_1192);
                *P_LVALUE_1192 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp163_1) <= PrtPrimGetInt(PTMP_tmp165_1));
                
                PRT_VALUE** P_LVALUE_1193 = &(PTMP_tmp167_1);
                PrtFreeValue(*P_LVALUE_1193);
                *P_LVALUE_1193 = PrtCloneValue(PTMP_tmp166_1);
                
            }
            
            
            PRT_VALUE** P_LVALUE_1194 = &(PTMP_tmp177_1);
            PrtFreeValue(*P_LVALUE_1194);
            *P_LVALUE_1194 = PrtCloneValue(PTMP_tmp167_1);
            
            if (PrtPrimGetBool(PTMP_tmp177_1))
            {
            }
            
            else
            {
                PRT_VALUE** P_LVALUE_1195 = &(PTMP_tmp168_1);
                PrtFreeValue(*P_LVALUE_1195);
                *P_LVALUE_1195 = PrtTupleGet(*P_VAR_request_18, 6);
                
                PRT_VALUE** P_LVALUE_1196 = &(PTMP_tmp169_1);
                PrtFreeValue(*P_LVALUE_1196);
                *P_LVALUE_1196 = PrtTupleGet(PTMP_tmp168_1, 1);
                
                PRT_VALUE** P_LVALUE_1197 = &(PTMP_tmp170_1);
                PrtFreeValue(*P_LVALUE_1197);
                *P_LVALUE_1197 = PrtTupleGet(p_this->varValues[8], 1);
                
                PRT_VALUE** P_LVALUE_1198 = &(PTMP_tmp171_1);
                PrtFreeValue(*P_LVALUE_1198);
                *P_LVALUE_1198 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp169_1) > PrtPrimGetInt(PTMP_tmp170_1));
                
                PRT_VALUE** P_LVALUE_1199 = &(PTMP_tmp176_1);
                PrtFreeValue(*P_LVALUE_1199);
                *P_LVALUE_1199 = PrtCloneValue(PTMP_tmp171_1);
                
                if (PrtPrimGetBool(PTMP_tmp176_1))
                {
                    PRT_VALUE** P_LVALUE_1200 = &(PTMP_tmp172_1);
                    PrtFreeValue(*P_LVALUE_1200);
                    *P_LVALUE_1200 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                    
                    PRT_VALUE** P_LVALUE_1201 = &(PTMP_tmp173_1);
                    PrtFreeValue(*P_LVALUE_1201);
                    *P_LVALUE_1201 = PrtTupleGet(*P_VAR_request_18, 6);
                    
                    PRT_VALUE** P_LVALUE_1202 = &(PTMP_tmp174_1);
                    PrtFreeValue(*P_LVALUE_1202);
                    *P_LVALUE_1202 = PrtTupleGet(PTMP_tmp173_1, 1);
                    
                    PRT_VALUE** P_LVALUE_1203 = &(PTMP_tmp175_1);
                    PrtFreeValue(*P_LVALUE_1203);
                    *P_LVALUE_1203 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp172_1) <= PrtPrimGetInt(PTMP_tmp174_1));
                    
                    PRT_VALUE** P_LVALUE_1204 = &(PTMP_tmp176_1);
                    PrtFreeValue(*P_LVALUE_1204);
                    *P_LVALUE_1204 = PrtCloneValue(PTMP_tmp175_1);
                    
                }
                
                
                PRT_VALUE** P_LVALUE_1205 = &(PTMP_tmp177_1);
                PrtFreeValue(*P_LVALUE_1205);
                *P_LVALUE_1205 = PrtCloneValue(PTMP_tmp176_1);
                
            }
            
            
            if (PrtPrimGetBool(PTMP_tmp177_1))
            {
                PRT_VALUE** P_LVALUE_1206 = &(PTMP_tmp178_1);
                PrtFreeValue(*P_LVALUE_1206);
                *P_LVALUE_1206 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
                
                PRT_VALUE** P_LVALUE_1207 = &(PTMP_tmp179_1);
                PrtFreeValue(*P_LVALUE_1207);
                *P_LVALUE_1207 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp178_1) - PrtPrimGetInt((&P_LIT_INT32_55)));
                
                PRT_VALUE** P_LVALUE_1208 = &(PTMP_tmp180_1);
                PrtFreeValue(*P_LVALUE_1208);
                *P_LVALUE_1208 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[6]));
                
                PRT_VALUE** P_LVALUE_1209 = &(PTMP_tmp181_1);
                PrtFreeValue(*P_LVALUE_1209);
                *P_LVALUE_1209 = PrtMkIntValue(PrtPrimGetInt(PTMP_tmp180_1) - PrtPrimGetInt((&P_LIT_INT32_55)));
                
                PRT_VALUE** P_LVALUE_1210 = &(PTMP_tmp182_1);
                PrtFreeValue(*P_LVALUE_1210);
                *P_LVALUE_1210 = (PrtMkTuple(&P_GEND_TYPE_T2ii, &(PTMP_tmp179_1), &(PTMP_tmp181_1)));
                
                {
                    PRT_VALUE** P_LVALUE_1211 = &(p_this->varValues[8]);
                    PrtFreeValue(*P_LVALUE_1211);
                    *P_LVALUE_1211 = PTMP_tmp182_1;
                    PTMP_tmp182_1 = NULL;
                }
                
            }
            
            else
            {
                PRT_VALUE** P_LVALUE_1212 = &(PTMP_tmp183_1);
                PrtFreeValue(*P_LVALUE_1212);
                *P_LVALUE_1212 = PrtTupleGet(*P_VAR_request_18, 6);
                
                PRT_VALUE** P_LVALUE_1213 = &(PTMP_tmp184_1);
                PrtFreeValue(*P_LVALUE_1213);
                *P_LVALUE_1213 = PrtTupleGet(PTMP_tmp183_1, 0);
                
                PRT_VALUE** P_LVALUE_1214 = &(PTMP_tmp185_1);
                PrtFreeValue(*P_LVALUE_1214);
                *P_LVALUE_1214 = PrtTupleGet(p_this->varValues[8], 0);
                
                PRT_VALUE** P_LVALUE_1215 = &(PTMP_tmp186_1);
                PrtFreeValue(*P_LVALUE_1215);
                *P_LVALUE_1215 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp184_1) > PrtPrimGetInt(PTMP_tmp185_1));
                
                PRT_VALUE** P_LVALUE_1216 = &(PTMP_tmp191_1);
                PrtFreeValue(*P_LVALUE_1216);
                *P_LVALUE_1216 = PrtCloneValue(PTMP_tmp186_1);
                
                if (PrtPrimGetBool(PTMP_tmp191_1))
                {
                    PRT_VALUE** P_LVALUE_1217 = &(PTMP_tmp187_1);
                    PrtFreeValue(*P_LVALUE_1217);
                    *P_LVALUE_1217 = PrtTupleGet(*P_VAR_request_18, 6);
                    
                    PRT_VALUE** P_LVALUE_1218 = &(PTMP_tmp188_1);
                    PrtFreeValue(*P_LVALUE_1218);
                    *P_LVALUE_1218 = PrtTupleGet(PTMP_tmp187_1, 1);
                    
                    PRT_VALUE** P_LVALUE_1219 = &(PTMP_tmp189_1);
                    PrtFreeValue(*P_LVALUE_1219);
                    *P_LVALUE_1219 = PrtTupleGet(p_this->varValues[8], 1);
                    
                    PRT_VALUE** P_LVALUE_1220 = &(PTMP_tmp190_1);
                    PrtFreeValue(*P_LVALUE_1220);
                    *P_LVALUE_1220 = PrtMkBoolValue(PrtPrimGetInt(PTMP_tmp188_1) > PrtPrimGetInt(PTMP_tmp189_1));
                    
                    PRT_VALUE** P_LVALUE_1221 = &(PTMP_tmp191_1);
                    PrtFreeValue(*P_LVALUE_1221);
                    *P_LVALUE_1221 = PrtCloneValue(PTMP_tmp190_1);
                    
                }
                
                
                if (PrtPrimGetBool(PTMP_tmp191_1))
                {
                    PRT_VALUE** P_LVALUE_1222 = &(PTMP_tmp192_1);
                    PrtFreeValue(*P_LVALUE_1222);
                    *P_LVALUE_1222 = PrtTupleGet(*P_VAR_request_18, 6);
                    
                    {
                        PRT_VALUE** P_LVALUE_1223 = &(p_this->varValues[8]);
                        PrtFreeValue(*P_LVALUE_1223);
                        *P_LVALUE_1223 = PTMP_tmp192_1;
                        PTMP_tmp192_1 = NULL;
                    }
                    
                }
                
                else
                {
                }
                
                
            }
            
            
            PRT_VALUE** P_LVALUE_1224 = &(PTMP_tmp193_1);
            PrtFreeValue(*P_LVALUE_1224);
            *P_LVALUE_1224 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[5]));
            
            PRT_VALUE** P_LVALUE_1225 = &(PTMP_tmp194_1);
            PrtFreeValue(*P_LVALUE_1225);
            *P_LVALUE_1225 = PrtTupleGet(*P_VAR_request_18, 4);
            
            PRT_VALUE** P_LVALUE_1226 = &(PTMP_tmp195_1);
            PrtFreeValue(*P_LVALUE_1226);
            *P_LVALUE_1226 = PrtMkIntValue(PrtSeqSizeOf(PTMP_tmp194_1));
            
            PrtFormatPrintf("\n[Server] ", 4, (p_this->id), p_this->varValues[3], PTMP_tmp193_1, PTMP_tmp195_1, 4, 0, " | term ", 1, " | log ", 2, " | entries received ", 3, " | append true\n");
            
            PRT_VALUE** P_LVALUE_1227 = &(PTMP_tmp196_1);
            PrtFreeValue(*P_LVALUE_1227);
            *P_LVALUE_1227 = PrtTupleGet(*P_VAR_request_18, 1);
            
            {
                PRT_VALUE** P_LVALUE_1228 = &(p_this->varValues[2]);
                PrtFreeValue(*P_LVALUE_1228);
                *P_LVALUE_1228 = PTMP_tmp196_1;
                PTMP_tmp196_1 = NULL;
            }
            
            PRT_VALUE** P_LVALUE_1229 = &(PTMP_tmp197_1);
            PrtFreeValue(*P_LVALUE_1229);
            *P_LVALUE_1229 = PrtTupleGet(*P_VAR_request_18, 1);
            
            PRT_VALUE** P_LVALUE_1230 = &(PTMP_tmp198_1);
            PrtFreeValue(*P_LVALUE_1230);
            *P_LVALUE_1230 = PrtCloneValue(PTMP_tmp197_1);
            
            PRT_VALUE** P_LVALUE_1231 = &(PTMP_tmp199_1);
            PrtFreeValue(*P_LVALUE_1231);
            *P_LVALUE_1231 = PrtCloneValue((&P_EVENT_AppendEntriesResponse.value));
            
            PRT_VALUE** P_LVALUE_1232 = &(PTMP_tmp200_1);
            PrtFreeValue(*P_LVALUE_1232);
            *P_LVALUE_1232 = PrtCloneValue(p_this->varValues[3]);
            
            PRT_VALUE** P_LVALUE_1233 = &(PTMP_tmp201_1);
            PrtFreeValue(*P_LVALUE_1233);
            *P_LVALUE_1233 = PrtCloneValue((&P_LIT_BOOLEAN_31));
            
            PRT_VALUE** P_LVALUE_1234 = &(PTMP_tmp202_1);
            PrtFreeValue(*P_LVALUE_1234);
            *P_LVALUE_1234 = PrtCloneValue(P_VAR_kv_success);
            
            PRT_VALUE** P_LVALUE_1235 = &(PTMP_tmp203_1);
            PrtFreeValue(*P_LVALUE_1235);
            *P_LVALUE_1235 = PrtCloneValue(P_VAR_cfg_success);
            
            PRT_VALUE** P_LVALUE_1236 = &(PTMP_tmp204);
            PrtFreeValue(*P_LVALUE_1236);
            *P_LVALUE_1236 = PrtCloneValue((p_this->id));
            
            PRT_VALUE** P_LVALUE_1237 = &(PTMP_tmp205);
            PrtFreeValue(*P_LVALUE_1237);
            *P_LVALUE_1237 = PrtTupleGet(*P_VAR_request_18, 7);
            
            PRT_VALUE** P_LVALUE_1238 = &(PTMP_tmp206);
            PrtFreeValue(*P_LVALUE_1238);
            *P_LVALUE_1238 = (PrtMkTuple(&P_GEND_TYPE_T6ibbbRm, &(PTMP_tmp200_1), &(PTMP_tmp201_1), &(PTMP_tmp202_1), &(PTMP_tmp203_1), &(PTMP_tmp204), &(PTMP_tmp205)));
            
            PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp198_1), PTMP_tmp199_1, 1, &(PTMP_tmp206));
            *(&(PTMP_tmp199_1)) = NULL;
            if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                goto p_return_70;
            }
            if (p_this->isHalted == PRT_TRUE) {
                PrtFreeValue(_P_GEN_retval);
                _P_GEN_retval = NULL;
                goto p_return_70;
            }
            
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = PrtCloneValue((&P_LIT_BOOLEAN_31));
            goto p_return_70;
            
        }
        
        
    }
    
    
p_return_70: ;
    PrtFreeValue(P_VAR_idx_10); P_VAR_idx_10 = NULL;
    PrtFreeValue(P_VAR_cfgLogIdx_2); P_VAR_cfgLogIdx_2 = NULL;
    PrtFreeValue(P_VAR_cfg_success); P_VAR_cfg_success = NULL;
    PrtFreeValue(P_VAR_kv_success); P_VAR_kv_success = NULL;
    PrtFreeValue(PTMP_tmp0_67); PTMP_tmp0_67 = NULL;
    PrtFreeValue(PTMP_tmp1_56); PTMP_tmp1_56 = NULL;
    PrtFreeValue(PTMP_tmp2_49); PTMP_tmp2_49 = NULL;
    PrtFreeValue(PTMP_tmp3_44); PTMP_tmp3_44 = NULL;
    PrtFreeValue(PTMP_tmp4_37); PTMP_tmp4_37 = NULL;
    PrtFreeValue(PTMP_tmp5_28); PTMP_tmp5_28 = NULL;
    PrtFreeValue(PTMP_tmp6_26); PTMP_tmp6_26 = NULL;
    PrtFreeValue(PTMP_tmp7_24); PTMP_tmp7_24 = NULL;
    PrtFreeValue(PTMP_tmp8_21); PTMP_tmp8_21 = NULL;
    PrtFreeValue(PTMP_tmp9_18); PTMP_tmp9_18 = NULL;
    PrtFreeValue(PTMP_tmp10_17); PTMP_tmp10_17 = NULL;
    PrtFreeValue(PTMP_tmp11_17); PTMP_tmp11_17 = NULL;
    PrtFreeValue(PTMP_tmp12_16); PTMP_tmp12_16 = NULL;
    PrtFreeValue(PTMP_tmp13_15); PTMP_tmp13_15 = NULL;
    PrtFreeValue(PTMP_tmp14_14); PTMP_tmp14_14 = NULL;
    PrtFreeValue(PTMP_tmp15_11); PTMP_tmp15_11 = NULL;
    PrtFreeValue(PTMP_tmp16_10); PTMP_tmp16_10 = NULL;
    PrtFreeValue(PTMP_tmp17_8); PTMP_tmp17_8 = NULL;
    PrtFreeValue(PTMP_tmp18_8); PTMP_tmp18_8 = NULL;
    PrtFreeValue(PTMP_tmp19_8); PTMP_tmp19_8 = NULL;
    PrtFreeValue(PTMP_tmp20_8); PTMP_tmp20_8 = NULL;
    PrtFreeValue(PTMP_tmp21_8); PTMP_tmp21_8 = NULL;
    PrtFreeValue(PTMP_tmp22_8); PTMP_tmp22_8 = NULL;
    PrtFreeValue(PTMP_tmp23_7); PTMP_tmp23_7 = NULL;
    PrtFreeValue(PTMP_tmp24_6); PTMP_tmp24_6 = NULL;
    PrtFreeValue(PTMP_tmp25_6); PTMP_tmp25_6 = NULL;
    PrtFreeValue(PTMP_tmp26_6); PTMP_tmp26_6 = NULL;
    PrtFreeValue(PTMP_tmp27_6); PTMP_tmp27_6 = NULL;
    PrtFreeValue(PTMP_tmp28_6); PTMP_tmp28_6 = NULL;
    PrtFreeValue(PTMP_tmp29_6); PTMP_tmp29_6 = NULL;
    PrtFreeValue(PTMP_tmp30_5); PTMP_tmp30_5 = NULL;
    PrtFreeValue(PTMP_tmp31_4); PTMP_tmp31_4 = NULL;
    PrtFreeValue(PTMP_tmp32_4); PTMP_tmp32_4 = NULL;
    PrtFreeValue(PTMP_tmp33_4); PTMP_tmp33_4 = NULL;
    PrtFreeValue(PTMP_tmp34_4); PTMP_tmp34_4 = NULL;
    PrtFreeValue(PTMP_tmp35_4); PTMP_tmp35_4 = NULL;
    PrtFreeValue(PTMP_tmp36_3); PTMP_tmp36_3 = NULL;
    PrtFreeValue(PTMP_tmp37_3); PTMP_tmp37_3 = NULL;
    PrtFreeValue(PTMP_tmp38_3); PTMP_tmp38_3 = NULL;
    PrtFreeValue(PTMP_tmp39_3); PTMP_tmp39_3 = NULL;
    PrtFreeValue(PTMP_tmp40_3); PTMP_tmp40_3 = NULL;
    PrtFreeValue(PTMP_tmp41_3); PTMP_tmp41_3 = NULL;
    PrtFreeValue(PTMP_tmp42_3); PTMP_tmp42_3 = NULL;
    PrtFreeValue(PTMP_tmp43_3); PTMP_tmp43_3 = NULL;
    PrtFreeValue(PTMP_tmp44_3); PTMP_tmp44_3 = NULL;
    PrtFreeValue(PTMP_tmp45_3); PTMP_tmp45_3 = NULL;
    PrtFreeValue(PTMP_tmp46_3); PTMP_tmp46_3 = NULL;
    PrtFreeValue(PTMP_tmp47_3); PTMP_tmp47_3 = NULL;
    PrtFreeValue(PTMP_tmp48_3); PTMP_tmp48_3 = NULL;
    PrtFreeValue(PTMP_tmp49_3); PTMP_tmp49_3 = NULL;
    PrtFreeValue(PTMP_tmp50_3); PTMP_tmp50_3 = NULL;
    PrtFreeValue(PTMP_tmp51_3); PTMP_tmp51_3 = NULL;
    PrtFreeValue(PTMP_tmp52_2); PTMP_tmp52_2 = NULL;
    PrtFreeValue(PTMP_tmp53_2); PTMP_tmp53_2 = NULL;
    PrtFreeValue(PTMP_tmp54_2); PTMP_tmp54_2 = NULL;
    PrtFreeValue(PTMP_tmp55_2); PTMP_tmp55_2 = NULL;
    PrtFreeValue(PTMP_tmp56_2); PTMP_tmp56_2 = NULL;
    PrtFreeValue(PTMP_tmp57_2); PTMP_tmp57_2 = NULL;
    PrtFreeValue(PTMP_tmp58_2); PTMP_tmp58_2 = NULL;
    PrtFreeValue(PTMP_tmp59_2); PTMP_tmp59_2 = NULL;
    PrtFreeValue(PTMP_tmp60_2); PTMP_tmp60_2 = NULL;
    PrtFreeValue(PTMP_tmp61_2); PTMP_tmp61_2 = NULL;
    PrtFreeValue(PTMP_tmp62_2); PTMP_tmp62_2 = NULL;
    PrtFreeValue(PTMP_tmp63_2); PTMP_tmp63_2 = NULL;
    PrtFreeValue(PTMP_tmp64_2); PTMP_tmp64_2 = NULL;
    PrtFreeValue(PTMP_tmp65_2); PTMP_tmp65_2 = NULL;
    PrtFreeValue(PTMP_tmp66_2); PTMP_tmp66_2 = NULL;
    PrtFreeValue(PTMP_tmp67_1); PTMP_tmp67_1 = NULL;
    PrtFreeValue(PTMP_tmp68_1); PTMP_tmp68_1 = NULL;
    PrtFreeValue(PTMP_tmp69_1); PTMP_tmp69_1 = NULL;
    PrtFreeValue(PTMP_tmp70_1); PTMP_tmp70_1 = NULL;
    PrtFreeValue(PTMP_tmp71_1); PTMP_tmp71_1 = NULL;
    PrtFreeValue(PTMP_tmp72_1); PTMP_tmp72_1 = NULL;
    PrtFreeValue(PTMP_tmp73_1); PTMP_tmp73_1 = NULL;
    PrtFreeValue(PTMP_tmp74_1); PTMP_tmp74_1 = NULL;
    PrtFreeValue(PTMP_tmp75_1); PTMP_tmp75_1 = NULL;
    PrtFreeValue(PTMP_tmp76_1); PTMP_tmp76_1 = NULL;
    PrtFreeValue(PTMP_tmp77_1); PTMP_tmp77_1 = NULL;
    PrtFreeValue(PTMP_tmp78_1); PTMP_tmp78_1 = NULL;
    PrtFreeValue(PTMP_tmp79_1); PTMP_tmp79_1 = NULL;
    PrtFreeValue(PTMP_tmp80_1); PTMP_tmp80_1 = NULL;
    PrtFreeValue(PTMP_tmp81_1); PTMP_tmp81_1 = NULL;
    PrtFreeValue(PTMP_tmp82_1); PTMP_tmp82_1 = NULL;
    PrtFreeValue(PTMP_tmp83_1); PTMP_tmp83_1 = NULL;
    PrtFreeValue(PTMP_tmp84_1); PTMP_tmp84_1 = NULL;
    PrtFreeValue(PTMP_tmp85_1); PTMP_tmp85_1 = NULL;
    PrtFreeValue(PTMP_tmp86_1); PTMP_tmp86_1 = NULL;
    PrtFreeValue(PTMP_tmp87_1); PTMP_tmp87_1 = NULL;
    PrtFreeValue(PTMP_tmp88_1); PTMP_tmp88_1 = NULL;
    PrtFreeValue(PTMP_tmp89_1); PTMP_tmp89_1 = NULL;
    PrtFreeValue(PTMP_tmp90_1); PTMP_tmp90_1 = NULL;
    PrtFreeValue(PTMP_tmp91_1); PTMP_tmp91_1 = NULL;
    PrtFreeValue(PTMP_tmp92_1); PTMP_tmp92_1 = NULL;
    PrtFreeValue(PTMP_tmp93_1); PTMP_tmp93_1 = NULL;
    PrtFreeValue(PTMP_tmp94_1); PTMP_tmp94_1 = NULL;
    PrtFreeValue(PTMP_tmp95_1); PTMP_tmp95_1 = NULL;
    PrtFreeValue(PTMP_tmp96_1); PTMP_tmp96_1 = NULL;
    PrtFreeValue(PTMP_tmp97_1); PTMP_tmp97_1 = NULL;
    PrtFreeValue(PTMP_tmp98_1); PTMP_tmp98_1 = NULL;
    PrtFreeValue(PTMP_tmp99_1); PTMP_tmp99_1 = NULL;
    PrtFreeValue(PTMP_tmp100_1); PTMP_tmp100_1 = NULL;
    PrtFreeValue(PTMP_tmp101_1); PTMP_tmp101_1 = NULL;
    PrtFreeValue(PTMP_tmp102_1); PTMP_tmp102_1 = NULL;
    PrtFreeValue(PTMP_tmp103_1); PTMP_tmp103_1 = NULL;
    PrtFreeValue(PTMP_tmp104_1); PTMP_tmp104_1 = NULL;
    PrtFreeValue(PTMP_tmp105_1); PTMP_tmp105_1 = NULL;
    PrtFreeValue(PTMP_tmp106_1); PTMP_tmp106_1 = NULL;
    PrtFreeValue(PTMP_tmp107_1); PTMP_tmp107_1 = NULL;
    PrtFreeValue(PTMP_tmp108_1); PTMP_tmp108_1 = NULL;
    PrtFreeValue(PTMP_tmp109_1); PTMP_tmp109_1 = NULL;
    PrtFreeValue(PTMP_tmp110_1); PTMP_tmp110_1 = NULL;
    PrtFreeValue(PTMP_tmp111_1); PTMP_tmp111_1 = NULL;
    PrtFreeValue(PTMP_tmp112_1); PTMP_tmp112_1 = NULL;
    PrtFreeValue(PTMP_tmp113_1); PTMP_tmp113_1 = NULL;
    PrtFreeValue(PTMP_tmp114_1); PTMP_tmp114_1 = NULL;
    PrtFreeValue(PTMP_tmp115_1); PTMP_tmp115_1 = NULL;
    PrtFreeValue(PTMP_tmp116_1); PTMP_tmp116_1 = NULL;
    PrtFreeValue(PTMP_tmp117_1); PTMP_tmp117_1 = NULL;
    PrtFreeValue(PTMP_tmp118_1); PTMP_tmp118_1 = NULL;
    PrtFreeValue(PTMP_tmp119_1); PTMP_tmp119_1 = NULL;
    PrtFreeValue(PTMP_tmp120_1); PTMP_tmp120_1 = NULL;
    PrtFreeValue(PTMP_tmp121_1); PTMP_tmp121_1 = NULL;
    PrtFreeValue(PTMP_tmp122_1); PTMP_tmp122_1 = NULL;
    PrtFreeValue(PTMP_tmp123_1); PTMP_tmp123_1 = NULL;
    PrtFreeValue(PTMP_tmp124_1); PTMP_tmp124_1 = NULL;
    PrtFreeValue(PTMP_tmp125_1); PTMP_tmp125_1 = NULL;
    PrtFreeValue(PTMP_tmp126_1); PTMP_tmp126_1 = NULL;
    PrtFreeValue(PTMP_tmp127_1); PTMP_tmp127_1 = NULL;
    PrtFreeValue(PTMP_tmp128_1); PTMP_tmp128_1 = NULL;
    PrtFreeValue(PTMP_tmp129_1); PTMP_tmp129_1 = NULL;
    PrtFreeValue(PTMP_tmp130_1); PTMP_tmp130_1 = NULL;
    PrtFreeValue(PTMP_tmp131_1); PTMP_tmp131_1 = NULL;
    PrtFreeValue(PTMP_tmp132_1); PTMP_tmp132_1 = NULL;
    PrtFreeValue(PTMP_tmp133_1); PTMP_tmp133_1 = NULL;
    PrtFreeValue(PTMP_tmp134_1); PTMP_tmp134_1 = NULL;
    PrtFreeValue(PTMP_tmp135_1); PTMP_tmp135_1 = NULL;
    PrtFreeValue(PTMP_tmp136_1); PTMP_tmp136_1 = NULL;
    PrtFreeValue(PTMP_tmp137_1); PTMP_tmp137_1 = NULL;
    PrtFreeValue(PTMP_tmp138_1); PTMP_tmp138_1 = NULL;
    PrtFreeValue(PTMP_tmp139_1); PTMP_tmp139_1 = NULL;
    PrtFreeValue(PTMP_tmp140_1); PTMP_tmp140_1 = NULL;
    PrtFreeValue(PTMP_tmp141_1); PTMP_tmp141_1 = NULL;
    PrtFreeValue(PTMP_tmp142_1); PTMP_tmp142_1 = NULL;
    PrtFreeValue(PTMP_tmp143_1); PTMP_tmp143_1 = NULL;
    PrtFreeValue(PTMP_tmp144_1); PTMP_tmp144_1 = NULL;
    PrtFreeValue(PTMP_tmp145_1); PTMP_tmp145_1 = NULL;
    PrtFreeValue(PTMP_tmp146_1); PTMP_tmp146_1 = NULL;
    PrtFreeValue(PTMP_tmp147_1); PTMP_tmp147_1 = NULL;
    PrtFreeValue(PTMP_tmp148_1); PTMP_tmp148_1 = NULL;
    PrtFreeValue(PTMP_tmp149_1); PTMP_tmp149_1 = NULL;
    PrtFreeValue(PTMP_tmp150_1); PTMP_tmp150_1 = NULL;
    PrtFreeValue(PTMP_tmp151_1); PTMP_tmp151_1 = NULL;
    PrtFreeValue(PTMP_tmp152_1); PTMP_tmp152_1 = NULL;
    PrtFreeValue(PTMP_tmp153_1); PTMP_tmp153_1 = NULL;
    PrtFreeValue(PTMP_tmp154_1); PTMP_tmp154_1 = NULL;
    PrtFreeValue(PTMP_tmp155_1); PTMP_tmp155_1 = NULL;
    PrtFreeValue(PTMP_tmp156_1); PTMP_tmp156_1 = NULL;
    PrtFreeValue(PTMP_tmp157_1); PTMP_tmp157_1 = NULL;
    PrtFreeValue(PTMP_tmp158_1); PTMP_tmp158_1 = NULL;
    PrtFreeValue(PTMP_tmp159_1); PTMP_tmp159_1 = NULL;
    PrtFreeValue(PTMP_tmp160_1); PTMP_tmp160_1 = NULL;
    PrtFreeValue(PTMP_tmp161_1); PTMP_tmp161_1 = NULL;
    PrtFreeValue(PTMP_tmp162_1); PTMP_tmp162_1 = NULL;
    PrtFreeValue(PTMP_tmp163_1); PTMP_tmp163_1 = NULL;
    PrtFreeValue(PTMP_tmp164_1); PTMP_tmp164_1 = NULL;
    PrtFreeValue(PTMP_tmp165_1); PTMP_tmp165_1 = NULL;
    PrtFreeValue(PTMP_tmp166_1); PTMP_tmp166_1 = NULL;
    PrtFreeValue(PTMP_tmp167_1); PTMP_tmp167_1 = NULL;
    PrtFreeValue(PTMP_tmp168_1); PTMP_tmp168_1 = NULL;
    PrtFreeValue(PTMP_tmp169_1); PTMP_tmp169_1 = NULL;
    PrtFreeValue(PTMP_tmp170_1); PTMP_tmp170_1 = NULL;
    PrtFreeValue(PTMP_tmp171_1); PTMP_tmp171_1 = NULL;
    PrtFreeValue(PTMP_tmp172_1); PTMP_tmp172_1 = NULL;
    PrtFreeValue(PTMP_tmp173_1); PTMP_tmp173_1 = NULL;
    PrtFreeValue(PTMP_tmp174_1); PTMP_tmp174_1 = NULL;
    PrtFreeValue(PTMP_tmp175_1); PTMP_tmp175_1 = NULL;
    PrtFreeValue(PTMP_tmp176_1); PTMP_tmp176_1 = NULL;
    PrtFreeValue(PTMP_tmp177_1); PTMP_tmp177_1 = NULL;
    PrtFreeValue(PTMP_tmp178_1); PTMP_tmp178_1 = NULL;
    PrtFreeValue(PTMP_tmp179_1); PTMP_tmp179_1 = NULL;
    PrtFreeValue(PTMP_tmp180_1); PTMP_tmp180_1 = NULL;
    PrtFreeValue(PTMP_tmp181_1); PTMP_tmp181_1 = NULL;
    PrtFreeValue(PTMP_tmp182_1); PTMP_tmp182_1 = NULL;
    PrtFreeValue(PTMP_tmp183_1); PTMP_tmp183_1 = NULL;
    PrtFreeValue(PTMP_tmp184_1); PTMP_tmp184_1 = NULL;
    PrtFreeValue(PTMP_tmp185_1); PTMP_tmp185_1 = NULL;
    PrtFreeValue(PTMP_tmp186_1); PTMP_tmp186_1 = NULL;
    PrtFreeValue(PTMP_tmp187_1); PTMP_tmp187_1 = NULL;
    PrtFreeValue(PTMP_tmp188_1); PTMP_tmp188_1 = NULL;
    PrtFreeValue(PTMP_tmp189_1); PTMP_tmp189_1 = NULL;
    PrtFreeValue(PTMP_tmp190_1); PTMP_tmp190_1 = NULL;
    PrtFreeValue(PTMP_tmp191_1); PTMP_tmp191_1 = NULL;
    PrtFreeValue(PTMP_tmp192_1); PTMP_tmp192_1 = NULL;
    PrtFreeValue(PTMP_tmp193_1); PTMP_tmp193_1 = NULL;
    PrtFreeValue(PTMP_tmp194_1); PTMP_tmp194_1 = NULL;
    PrtFreeValue(PTMP_tmp195_1); PTMP_tmp195_1 = NULL;
    PrtFreeValue(PTMP_tmp196_1); PTMP_tmp196_1 = NULL;
    PrtFreeValue(PTMP_tmp197_1); PTMP_tmp197_1 = NULL;
    PrtFreeValue(PTMP_tmp198_1); PTMP_tmp198_1 = NULL;
    PrtFreeValue(PTMP_tmp199_1); PTMP_tmp199_1 = NULL;
    PrtFreeValue(PTMP_tmp200_1); PTMP_tmp200_1 = NULL;
    PrtFreeValue(PTMP_tmp201_1); PTMP_tmp201_1 = NULL;
    PrtFreeValue(PTMP_tmp202_1); PTMP_tmp202_1 = NULL;
    PrtFreeValue(PTMP_tmp203_1); PTMP_tmp203_1 = NULL;
    PrtFreeValue(PTMP_tmp204); PTMP_tmp204 = NULL;
    PrtFreeValue(PTMP_tmp205); PTMP_tmp205 = NULL;
    PrtFreeValue(PTMP_tmp206); PTMP_tmp206 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_AppendEntries =
{
    "AppendEntries",
    &P_AppendEntries_IMPL,
    NULL
};


PRT_VALUE* P_DeleteFromLog_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_startIndex = argRefs[0];
    PRT_VALUE** P_VAR_endIndex = argRefs[1];
    PRT_VALUE** P_VAR_isKV = argRefs[2];
    PRT_VALUE* P_VAR_idx_11 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_68 = NULL;
    PRT_VALUE* PTMP_tmp1_57 = NULL;
    PRT_VALUE* PTMP_tmp2_50 = NULL;
    PRT_VALUE* PTMP_tmp3_45 = NULL;
    PRT_VALUE* PTMP_tmp4_38 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_56 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_32 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_1239 = &(PTMP_tmp0_68);
    PrtFreeValue(*P_LVALUE_1239);
    *P_LVALUE_1239 = PrtMkIntValue(PrtPrimGetInt(*P_VAR_endIndex) - PrtPrimGetInt((&P_LIT_INT32_56)));
    
    {
        PRT_VALUE** P_LVALUE_1240 = &(P_VAR_idx_11);
        PrtFreeValue(*P_LVALUE_1240);
        *P_LVALUE_1240 = PTMP_tmp0_68;
        PTMP_tmp0_68 = NULL;
    }
    
    if (PrtPrimGetBool(*P_VAR_isKV))
    {
        while (PrtPrimGetBool((&P_LIT_BOOLEAN_32)))
        {
            PRT_VALUE** P_LVALUE_1241 = &(PTMP_tmp1_57);
            PrtFreeValue(*P_LVALUE_1241);
            *P_LVALUE_1241 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_11) >= PrtPrimGetInt(*P_VAR_startIndex));
            
            PRT_VALUE** P_LVALUE_1242 = &(PTMP_tmp2_50);
            PrtFreeValue(*P_LVALUE_1242);
            *P_LVALUE_1242 = PrtCloneValue(PTMP_tmp1_57);
            
            if (PrtPrimGetBool(PTMP_tmp2_50))
            {
            }
            
            else
            {
                break;
                
            }
            
            
            PrtRemoveByKey(p_this->varValues[5], P_VAR_idx_11);
            
        }
        
        
    }
    
    else
    {
        while (PrtPrimGetBool((&P_LIT_BOOLEAN_32)))
        {
            PRT_VALUE** P_LVALUE_1243 = &(PTMP_tmp3_45);
            PrtFreeValue(*P_LVALUE_1243);
            *P_LVALUE_1243 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_11) >= PrtPrimGetInt(*P_VAR_startIndex));
            
            PRT_VALUE** P_LVALUE_1244 = &(PTMP_tmp4_38);
            PrtFreeValue(*P_LVALUE_1244);
            *P_LVALUE_1244 = PrtCloneValue(PTMP_tmp3_45);
            
            if (PrtPrimGetBool(PTMP_tmp4_38))
            {
            }
            
            else
            {
                break;
                
            }
            
            
            PrtRemoveByKey(p_this->varValues[6], P_VAR_idx_11);
            
        }
        
        
    }
    
    
p_return_71: ;
    PrtFreeValue(P_VAR_idx_11); P_VAR_idx_11 = NULL;
    PrtFreeValue(PTMP_tmp0_68); PTMP_tmp0_68 = NULL;
    PrtFreeValue(PTMP_tmp1_57); PTMP_tmp1_57 = NULL;
    PrtFreeValue(PTMP_tmp2_50); PTMP_tmp2_50 = NULL;
    PrtFreeValue(PTMP_tmp3_45); PTMP_tmp3_45 = NULL;
    PrtFreeValue(PTMP_tmp4_38); PTMP_tmp4_38 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_DeleteFromLog =
{
    "DeleteFromLog",
    &P_DeleteFromLog_IMPL,
    NULL
};


PRT_VALUE* P_RedirectLastClientRequestToClusterManager_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_69 = NULL;
    PRT_VALUE* PTMP_tmp1_58 = NULL;
    PRT_VALUE* PTMP_tmp2_51 = NULL;
    PRT_VALUE* PTMP_tmp3_46 = NULL;
    PRT_VALUE* PTMP_tmp4_39 = NULL;
    PRT_VALUE* PTMP_tmp5_29 = NULL;
    PRT_VALUE* PTMP_tmp6_27 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_1245 = &(PTMP_tmp0_69);
    PrtFreeValue(*P_LVALUE_1245);
    *P_LVALUE_1245 = PrtMkBoolValue(!PrtIsEqualValue(p_this->varValues[12], (&_P_GEN_null)));
    
    if (PrtPrimGetBool(PTMP_tmp0_69))
    {
        PRT_VALUE** P_LVALUE_1246 = &(PTMP_tmp1_58);
        PrtFreeValue(*P_LVALUE_1246);
        *P_LVALUE_1246 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_1247 = &(PTMP_tmp2_51);
        PrtFreeValue(*P_LVALUE_1247);
        *P_LVALUE_1247 = PrtCloneValue((&P_EVENT_Request.value));
        
        PRT_VALUE** P_LVALUE_1248 = &(PTMP_tmp3_46);
        PrtFreeValue(*P_LVALUE_1248);
        *P_LVALUE_1248 = PrtTupleGet(p_this->varValues[12], 0);
        
        PRT_VALUE** P_LVALUE_1249 = &(PTMP_tmp4_39);
        PrtFreeValue(*P_LVALUE_1249);
        *P_LVALUE_1249 = PrtTupleGet(p_this->varValues[12], 1);
        
        PRT_VALUE** P_LVALUE_1250 = &(PTMP_tmp5_29);
        PrtFreeValue(*P_LVALUE_1250);
        *P_LVALUE_1250 = PrtTupleGet(p_this->varValues[12], 2);
        
        PRT_VALUE** P_LVALUE_1251 = &(PTMP_tmp6_27);
        PrtFreeValue(*P_LVALUE_1251);
        *P_LVALUE_1251 = (PrtMkTuple(&P_GEND_TYPE_T3mrr, &(PTMP_tmp3_46), &(PTMP_tmp4_39), &(PTMP_tmp5_29)));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_58), PTMP_tmp2_51, 1, &(PTMP_tmp6_27));
        *(&(PTMP_tmp2_51)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_72;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_72;
        }
        
    }
    
    else
    {
    }
    
    
p_return_72: ;
    PrtFreeValue(PTMP_tmp0_69); PTMP_tmp0_69 = NULL;
    PrtFreeValue(PTMP_tmp1_58); PTMP_tmp1_58 = NULL;
    PrtFreeValue(PTMP_tmp2_51); PTMP_tmp2_51 = NULL;
    PrtFreeValue(PTMP_tmp3_46); PTMP_tmp3_46 = NULL;
    PrtFreeValue(PTMP_tmp4_39); PTMP_tmp4_39 = NULL;
    PrtFreeValue(PTMP_tmp5_29); PTMP_tmp5_29 = NULL;
    PrtFreeValue(PTMP_tmp6_27); PTMP_tmp6_27 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_RedirectLastClientRequestToClusterManager =
{
    "RedirectLastClientRequestToClusterManager",
    &P_RedirectLastClientRequestToClusterManager_IMPL,
    NULL
};


PRT_VALUE* P_GetLogTermForIndex_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE** P_VAR_logIndex = argRefs[0];
    PRT_VALUE** P_VAR_isKV_1 = argRefs[1];
    PRT_VALUE* P_VAR_logTerm = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_70 = NULL;
    PRT_VALUE* PTMP_tmp1_59 = NULL;
    PRT_VALUE* PTMP_tmp2_52 = NULL;
    PRT_VALUE* PTMP_tmp3_47 = NULL;
    PRT_VALUE* PTMP_tmp4_40 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_57 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE** P_LVALUE_1252 = &(P_VAR_logTerm);
    PrtFreeValue(*P_LVALUE_1252);
    *P_LVALUE_1252 = PrtCloneValue((&P_LIT_INT32_57));
    
    PrtFormatPrintf("LogIndex: ", 1, *P_VAR_logIndex, 1, 0, "");
    
    PRT_VALUE** P_LVALUE_1253 = &(PTMP_tmp0_70);
    PrtFreeValue(*P_LVALUE_1253);
    *P_LVALUE_1253 = PrtMkBoolValue(PrtPrimGetInt(*P_VAR_logIndex) >= PrtPrimGetInt((&P_LIT_INT32_57)));
    
    if (PrtPrimGetBool(PTMP_tmp0_70))
    {
        if (PrtPrimGetBool(*P_VAR_isKV_1))
        {
            PRT_VALUE** P_LVALUE_1254 = &(PTMP_tmp1_59);
            PrtFreeValue(*P_LVALUE_1254);
            *P_LVALUE_1254 = PrtSeqGet(p_this->varValues[5], *P_VAR_logIndex);
            
            PRT_VALUE** P_LVALUE_1255 = &(PTMP_tmp2_52);
            PrtFreeValue(*P_LVALUE_1255);
            *P_LVALUE_1255 = PrtTupleGet(PTMP_tmp1_59, 0);
            
            {
                PRT_VALUE** P_LVALUE_1256 = &(P_VAR_logTerm);
                PrtFreeValue(*P_LVALUE_1256);
                *P_LVALUE_1256 = PTMP_tmp2_52;
                PTMP_tmp2_52 = NULL;
            }
            
        }
        
        else
        {
            PRT_VALUE** P_LVALUE_1257 = &(PTMP_tmp3_47);
            PrtFreeValue(*P_LVALUE_1257);
            *P_LVALUE_1257 = PrtSeqGet(p_this->varValues[6], *P_VAR_logIndex);
            
            PRT_VALUE** P_LVALUE_1258 = &(PTMP_tmp4_40);
            PrtFreeValue(*P_LVALUE_1258);
            *P_LVALUE_1258 = PrtTupleGet(PTMP_tmp3_47, 0);
            
            {
                PRT_VALUE** P_LVALUE_1259 = &(P_VAR_logTerm);
                PrtFreeValue(*P_LVALUE_1259);
                *P_LVALUE_1259 = PTMP_tmp4_40;
                PTMP_tmp4_40 = NULL;
            }
            
        }
        
        
    }
    
    else
    {
    }
    
    
    PrtFreeValue(_P_GEN_retval);
    _P_GEN_retval = PrtCloneValue(P_VAR_logTerm);
    goto p_return_73;
    
p_return_73: ;
    PrtFreeValue(P_VAR_logTerm); P_VAR_logTerm = NULL;
    PrtFreeValue(PTMP_tmp0_70); PTMP_tmp0_70 = NULL;
    PrtFreeValue(PTMP_tmp1_59); PTMP_tmp1_59 = NULL;
    PrtFreeValue(PTMP_tmp2_52); PTMP_tmp2_52 = NULL;
    PrtFreeValue(PTMP_tmp3_47); PTMP_tmp3_47 = NULL;
    PrtFreeValue(PTMP_tmp4_40); PTMP_tmp4_40 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_GetLogTermForIndex =
{
    "GetLogTermForIndex",
    &P_GetLogTermForIndex_IMPL,
    NULL
};


PRT_VALUE* P_ShuttingDown_IMPL_1(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_71 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_1260 = &(PTMP_tmp0_71);
    PrtFreeValue(*P_LVALUE_1260);
    *P_LVALUE_1260 = PrtCloneValue((&_P_EVENT_HALT_STRUCT.value));
    
    PrtRaise(p_this, PTMP_tmp0_71, 0);
    *(&(PTMP_tmp0_71)) = NULL;
    goto p_return_74;
    
p_return_74: ;
    PrtFreeValue(PTMP_tmp0_71); PTMP_tmp0_71 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_ShuttingDown_1 =
{
    "ShuttingDown",
    &P_ShuttingDown_IMPL_1,
    NULL
};


PRT_FUNDECL* P_Server_METHODS[] = { &P_FUNCTION_Anon_18, &P_FUNCTION_Anon_19, &P_FUNCTION_configServer, &P_FUNCTION_getMaxTickValue, &P_FUNCTION_Anon_20, &P_FUNCTION_Anon_21, &P_FUNCTION_Anon_22, &P_FUNCTION_Anon_23, &P_FUNCTION_Anon_24, &P_FUNCTION_Anon_25, &P_FUNCTION_Anon_26, &P_FUNCTION_Anon_27, &P_FUNCTION_Anon_28, &P_FUNCTION_Anon_29, &P_FUNCTION_Anon_30, &P_FUNCTION_Anon_31, &P_FUNCTION_Anon_32, &P_FUNCTION_Anon_33, &P_FUNCTION_Anon_34, &P_FUNCTION_Anon_35, &P_FUNCTION_Anon_36, &P_FUNCTION_Anon_37, &P_FUNCTION_Anon_38, &P_FUNCTION_BroadcastVoteRequests, &P_FUNCTION_RespondAppendEntriesAsCandidate, &P_FUNCTION_Anon_39, &P_FUNCTION_Anon_40, &P_FUNCTION_Anon_41, &P_FUNCTION_Anon_42, &P_FUNCTION_Anon_43, &P_FUNCTION_Anon_44, &P_FUNCTION_Anon_45, &P_FUNCTION_Anon_46, &P_FUNCTION_Anon_47, &P_FUNCTION_AddServerToConfig, &P_FUNCTION_RemoveServerFromConfig, &P_FUNCTION_UpdateFollowerConfigs, &P_FUNCTION_ProcessClientRequest, &P_FUNCTION_PrintLog, &P_FUNCTION_HeartbeatSendAsLeader, &P_FUNCTION_VoteAsLeader, &P_FUNCTION_RespondVoteAsLeader, &P_FUNCTION_AppendEntriesAsLeader, &P_FUNCTION_RespondAppendEntriesAsLeader, &P_FUNCTION_Vote, &P_FUNCTION_AppendEntries, &P_FUNCTION_DeleteFromLog, &P_FUNCTION_RedirectLastClientRequestToClusterManager, &P_FUNCTION_GetLogTermForIndex, &P_FUNCTION_ShuttingDown_1 };

PRT_EVENTDECL* P_Server_RECV_INNER_1[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_Server_RECV_1 =
{
    34U,
    P_Server_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_Server_SEND_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_Server_SEND =
{
    34U,
    P_Server_SEND_INNER,
    NULL
};

PRT_MACHINEDECL P_MACHINE_Server = 
{
    2U,
    "Server",
    &P_EVENTSET_Server_RECV_1,
    &P_EVENTSET_Server_SEND,
    NULL,
    18U,
    4U,
    50U,
    4294967295U,
    0U,
    P_Server_VARS,
    P_Server_STATES,
    P_Server_METHODS
};

PRT_VARDECL P_TestDriver0_VARS[] = {
    { "Cluster", &P_GEND_TYPE_m },
    { "Counter", &P_GEND_TYPE_i },
    { "Servers", &P_GEND_TYPE_Sm },
    { "NumServers", &P_GEND_TYPE_i },
    { "LatestKey", &P_GEND_TYPE_r },
    { "LatestVal", &P_GEND_TYPE_r }
};

PRT_EVENTDECL* P_Init_DEFERS_INNER_3[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DEFERS_3 =
{
    0U,
    P_Init_DEFERS_INNER_3,
    NULL
};

PRT_EVENTDECL* P_Init_TRANS_INNER_3[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_TRANS_3 =
{
    0U,
    P_Init_TRANS_INNER_3,
    NULL
};

PRT_EVENTDECL* P_Init_DOS_INNER_3[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DOS_3 =
{
    0U,
    P_Init_DOS_INNER_3,
    NULL
};

#define P_STATE_TestDriver0_Init \
{ \
    "TestDriver0.Init", \
    0U, \
    0U, \
    &P_EVENTSET_Init_DEFERS_3, \
    &P_EVENTSET_Init_TRANS_3, \
    &P_EVENTSET_Init_DOS_3, \
    NULL, \
    NULL, \
    &P_FUNCTION_Anon_48, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Running_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Running_DEFERS =
{
    0U,
    P_Running_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Running_TRANS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Running_TRANS =
{
    0U,
    P_Running_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Running_DOS_INNER[] = { &P_EVENT_Response };
PRT_EVENTSETDECL P_EVENTSET_Running_DOS =
{
    1U,
    P_Running_DOS_INNER,
    NULL
};

PRT_DODECL P_DOS_9[] =
{
    { 1, &P_EVENT_Response, &P_FUNCTION_Anon_50 }
};

#define P_STATE_TestDriver0_Running \
{ \
    "TestDriver0.Running", \
    0U, \
    1U, \
    &P_EVENTSET_Running_DEFERS, \
    &P_EVENTSET_Running_TRANS, \
    &P_EVENTSET_Running_DOS, \
    NULL, \
    P_DOS_9, \
    &P_FUNCTION_Anon_49, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_TestDriver0_STATES[] = { P_STATE_TestDriver0_Init, P_STATE_TestDriver0_Running };

PRT_VALUE* P_Anon_IMPL_48(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_Server_1 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    PRT_VALUE* P_VAR_idx_12 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_72 = NULL;
    PRT_VALUE* PTMP_tmp1_60 = NULL;
    PRT_VALUE* PTMP_tmp2_53 = NULL;
    PRT_VALUE* PTMP_tmp3_48 = NULL;
    PRT_VALUE* PTMP_tmp4_41 = NULL;
    PRT_VALUE* PTMP_tmp5_30 = NULL;
    PRT_VALUE* PTMP_tmp6_28 = NULL;
    PRT_VALUE* PTMP_tmp7_25 = NULL;
    PRT_VALUE* PTMP_tmp8_22 = NULL;
    PRT_VALUE* PTMP_tmp9_19 = NULL;
    PRT_VALUE* PTMP_tmp10_18 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_58 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_59 = { PRT_VALUE_KIND_INT, { .nt = 3 } };
    PRT_VALUE P_LIT_INT32_60 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_33 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_1261 = &(p_this->varValues[1]);
    PrtFreeValue(*P_LVALUE_1261);
    *P_LVALUE_1261 = PrtCloneValue((&P_LIT_INT32_58));
    
    PRT_VALUE** P_LVALUE_1262 = &(p_this->varValues[3]);
    PrtFreeValue(*P_LVALUE_1262);
    *P_LVALUE_1262 = PrtCloneValue((&P_LIT_INT32_59));
    
    PRT_VALUE** P_LVALUE_1263 = &(PTMP_tmp0_72);
    PrtFreeValue(*P_LVALUE_1263);
    *P_LVALUE_1263 = PrtMkDefaultValue(&P_GEND_TYPE_r);
    
    {
        PRT_VALUE** P_LVALUE_1264 = &(p_this->varValues[4]);
        PrtFreeValue(*P_LVALUE_1264);
        *P_LVALUE_1264 = PTMP_tmp0_72;
        PTMP_tmp0_72 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_1265 = &(PTMP_tmp1_60);
    PrtFreeValue(*P_LVALUE_1265);
    *P_LVALUE_1265 = PrtMkDefaultValue(&P_GEND_TYPE_r);
    
    {
        PRT_VALUE** P_LVALUE_1266 = &(p_this->varValues[5]);
        PrtFreeValue(*P_LVALUE_1266);
        *P_LVALUE_1266 = PTMP_tmp1_60;
        PTMP_tmp1_60 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_1267 = &(P_VAR_idx_12);
    PrtFreeValue(*P_LVALUE_1267);
    *P_LVALUE_1267 = PrtCloneValue((&P_LIT_INT32_58));
    
    PRT_VALUE** P_LVALUE_1268 = &(PTMP_tmp2_53);
    PrtFreeValue(*P_LVALUE_1268);
    *P_LVALUE_1268 = PrtCloneValue(PrtMkInterface(context, 0, 0)->id);
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_75;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_75;
    }
    
    {
        PRT_VALUE** P_LVALUE_1269 = &(p_this->varValues[0]);
        PrtFreeValue(*P_LVALUE_1269);
        *P_LVALUE_1269 = PTMP_tmp2_53;
        PTMP_tmp2_53 = NULL;
    }
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_33)))
    {
        PRT_VALUE** P_LVALUE_1270 = &(PTMP_tmp3_48);
        PrtFreeValue(*P_LVALUE_1270);
        *P_LVALUE_1270 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_12) < PrtPrimGetInt(p_this->varValues[3]));
        
        PRT_VALUE** P_LVALUE_1271 = &(PTMP_tmp4_41);
        PrtFreeValue(*P_LVALUE_1271);
        *P_LVALUE_1271 = PrtCloneValue(PTMP_tmp3_48);
        
        if (PrtPrimGetBool(PTMP_tmp4_41))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_1272 = &(PTMP_tmp5_30);
        PrtFreeValue(*P_LVALUE_1272);
        *P_LVALUE_1272 = PrtCloneValue(PrtMkInterface(context, 1, 0)->id);
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_75;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_75;
        }
        
        {
            PRT_VALUE** P_LVALUE_1273 = &(P_VAR_Server_1);
            PrtFreeValue(*P_LVALUE_1273);
            *P_LVALUE_1273 = PTMP_tmp5_30;
            PTMP_tmp5_30 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_1274 = &(PTMP_tmp6_28);
        PrtFreeValue(*P_LVALUE_1274);
        *P_LVALUE_1274 = PrtCloneValue(P_VAR_Server_1);
        
        PrtSeqInsertEx(p_this->varValues[2], P_VAR_idx_12, PTMP_tmp6_28, PRT_FALSE);
        *(&(PTMP_tmp6_28)) = NULL;
        
        PRT_VALUE** P_LVALUE_1275 = &(PTMP_tmp7_25);
        PrtFreeValue(*P_LVALUE_1275);
        *P_LVALUE_1275 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_1276 = &(PTMP_tmp8_22);
        PrtFreeValue(*P_LVALUE_1276);
        *P_LVALUE_1276 = PrtCloneValue((&P_EVENT_AddServer.value));
        
        PRT_VALUE** P_LVALUE_1277 = &(PTMP_tmp9_19);
        PrtFreeValue(*P_LVALUE_1277);
        *P_LVALUE_1277 = PrtCloneValue(P_VAR_Server_1);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp7_25), PTMP_tmp8_22, 1, &(PTMP_tmp9_19));
        *(&(PTMP_tmp8_22)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_75;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_75;
        }
        
        PRT_VALUE** P_LVALUE_1278 = &(PTMP_tmp10_18);
        PrtFreeValue(*P_LVALUE_1278);
        *P_LVALUE_1278 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_12) + PrtPrimGetInt((&P_LIT_INT32_60)));
        
        {
            PRT_VALUE** P_LVALUE_1279 = &(P_VAR_idx_12);
            PrtFreeValue(*P_LVALUE_1279);
            *P_LVALUE_1279 = PTMP_tmp10_18;
            PTMP_tmp10_18 = NULL;
        }
        
    }
    
    
    PrtGoto(p_this, 1U, 0);
    
p_return_75: ;
    PrtFreeValue(P_VAR_Server_1); P_VAR_Server_1 = NULL;
    PrtFreeValue(P_VAR_idx_12); P_VAR_idx_12 = NULL;
    PrtFreeValue(PTMP_tmp0_72); PTMP_tmp0_72 = NULL;
    PrtFreeValue(PTMP_tmp1_60); PTMP_tmp1_60 = NULL;
    PrtFreeValue(PTMP_tmp2_53); PTMP_tmp2_53 = NULL;
    PrtFreeValue(PTMP_tmp3_48); PTMP_tmp3_48 = NULL;
    PrtFreeValue(PTMP_tmp4_41); PTMP_tmp4_41 = NULL;
    PrtFreeValue(PTMP_tmp5_30); PTMP_tmp5_30 = NULL;
    PrtFreeValue(PTMP_tmp6_28); PTMP_tmp6_28 = NULL;
    PrtFreeValue(PTMP_tmp7_25); PTMP_tmp7_25 = NULL;
    PrtFreeValue(PTMP_tmp8_22); PTMP_tmp8_22 = NULL;
    PrtFreeValue(PTMP_tmp9_19); PTMP_tmp9_19 = NULL;
    PrtFreeValue(PTMP_tmp10_18); PTMP_tmp10_18 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_48 =
{
    NULL,
    &P_Anon_IMPL_48,
    NULL
};


PRT_VALUE* P_Anon_IMPL_49(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFreeValue(P_SendRequestToCluster_IMPL(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_76;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_76;
    }
    
p_return_76: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_49 =
{
    NULL,
    &P_Anon_IMPL_49,
    NULL
};


PRT_VALUE* P_Anon_IMPL_50(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_73 = NULL;
    PRT_VALUE* PTMP_tmp1_61 = NULL;
    PRT_VALUE* PTMP_tmp2_54 = NULL;
    PRT_VALUE* PTMP_tmp3_49 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_61 = { PRT_VALUE_KIND_INT, { .nt = 100 } };
    PRT_VALUE** P_LVALUE_1280 = &(PTMP_tmp0_73);
    PrtFreeValue(*P_LVALUE_1280);
    *P_LVALUE_1280 = PrtMkBoolValue(PrtIsEqualValue(p_this->varValues[1], (&P_LIT_INT32_61)));
    
    if (PrtPrimGetBool(PTMP_tmp0_73))
    {
        PRT_VALUE** P_LVALUE_1281 = &(PTMP_tmp1_61);
        PrtFreeValue(*P_LVALUE_1281);
        *P_LVALUE_1281 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_1282 = &(PTMP_tmp2_54);
        PrtFreeValue(*P_LVALUE_1282);
        *P_LVALUE_1282 = PrtCloneValue((&P_EVENT_ShutDown.value));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_61), PTMP_tmp2_54, 0);
        *(&(PTMP_tmp2_54)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_77;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_77;
        }
        
        PRT_VALUE** P_LVALUE_1283 = &(PTMP_tmp3_49);
        PrtFreeValue(*P_LVALUE_1283);
        *P_LVALUE_1283 = PrtCloneValue((&_P_EVENT_HALT_STRUCT.value));
        
        PrtRaise(p_this, PTMP_tmp3_49, 0);
        *(&(PTMP_tmp3_49)) = NULL;
        goto p_return_77;
        
    }
    
    else
    {
    }
    
    
    PrtFreeValue(P_SendRequestToCluster_IMPL(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_77;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_77;
    }
    
p_return_77: ;
    PrtFreeValue(PTMP_tmp0_73); PTMP_tmp0_73 = NULL;
    PrtFreeValue(PTMP_tmp1_61); PTMP_tmp1_61 = NULL;
    PrtFreeValue(PTMP_tmp2_54); PTMP_tmp2_54 = NULL;
    PrtFreeValue(PTMP_tmp3_49); PTMP_tmp3_49 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_50 =
{
    NULL,
    &P_Anon_IMPL_50,
    NULL
};


PRT_VALUE* P_SendRequestToCluster_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_74 = NULL;
    PRT_VALUE* PTMP_tmp1_62 = NULL;
    PRT_VALUE* PTMP_tmp2_55 = NULL;
    PRT_VALUE* PTMP_tmp3_50 = NULL;
    PRT_VALUE* PTMP_tmp4_42 = NULL;
    PRT_VALUE* PTMP_tmp5_31 = NULL;
    PRT_VALUE* PTMP_tmp6_29 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_62 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE** P_LVALUE_1284 = &(p_this->varValues[4]);
    PrtFreeValue(*P_LVALUE_1284);
    *P_LVALUE_1284 = PrtMkStringValue(PrtFormatString("k", 1, p_this->varValues[1], 1, 0, ""));
    
    PRT_VALUE** P_LVALUE_1285 = &(p_this->varValues[5]);
    PrtFreeValue(*P_LVALUE_1285);
    *P_LVALUE_1285 = PrtMkStringValue(PrtFormatString("v", 1, p_this->varValues[1], 1, 0, ""));
    
    PRT_VALUE** P_LVALUE_1286 = &(PTMP_tmp0_74);
    PrtFreeValue(*P_LVALUE_1286);
    *P_LVALUE_1286 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[1]) + PrtPrimGetInt((&P_LIT_INT32_62)));
    
    {
        PRT_VALUE** P_LVALUE_1287 = &(p_this->varValues[1]);
        PrtFreeValue(*P_LVALUE_1287);
        *P_LVALUE_1287 = PTMP_tmp0_74;
        PTMP_tmp0_74 = NULL;
    }
    
    PrtFormatPrintf("\n\n\n[Client] new request <", 2, p_this->varValues[4], p_this->varValues[5], 2, 0, ", ", 1, ">\n");
    
    PRT_VALUE** P_LVALUE_1288 = &(PTMP_tmp1_62);
    PrtFreeValue(*P_LVALUE_1288);
    *P_LVALUE_1288 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_1289 = &(PTMP_tmp2_55);
    PrtFreeValue(*P_LVALUE_1289);
    *P_LVALUE_1289 = PrtCloneValue((&P_EVENT_Request.value));
    
    PRT_VALUE** P_LVALUE_1290 = &(PTMP_tmp3_50);
    PrtFreeValue(*P_LVALUE_1290);
    *P_LVALUE_1290 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_1291 = &(PTMP_tmp4_42);
    PrtFreeValue(*P_LVALUE_1291);
    *P_LVALUE_1291 = PrtCloneValue(p_this->varValues[4]);
    
    PRT_VALUE** P_LVALUE_1292 = &(PTMP_tmp5_31);
    PrtFreeValue(*P_LVALUE_1292);
    *P_LVALUE_1292 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_1293 = &(PTMP_tmp6_29);
    PrtFreeValue(*P_LVALUE_1293);
    *P_LVALUE_1293 = (PrtMkTuple(&P_GEND_TYPE_T3Rrr, &(PTMP_tmp3_50), &(PTMP_tmp4_42), &(PTMP_tmp5_31)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_62), PTMP_tmp2_55, 1, &(PTMP_tmp6_29));
    *(&(PTMP_tmp2_55)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_78;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_78;
    }
    
p_return_78: ;
    PrtFreeValue(PTMP_tmp0_74); PTMP_tmp0_74 = NULL;
    PrtFreeValue(PTMP_tmp1_62); PTMP_tmp1_62 = NULL;
    PrtFreeValue(PTMP_tmp2_55); PTMP_tmp2_55 = NULL;
    PrtFreeValue(PTMP_tmp3_50); PTMP_tmp3_50 = NULL;
    PrtFreeValue(PTMP_tmp4_42); PTMP_tmp4_42 = NULL;
    PrtFreeValue(PTMP_tmp5_31); PTMP_tmp5_31 = NULL;
    PrtFreeValue(PTMP_tmp6_29); PTMP_tmp6_29 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_SendRequestToCluster =
{
    "SendRequestToCluster",
    &P_SendRequestToCluster_IMPL,
    NULL
};


PRT_FUNDECL* P_TestDriver0_METHODS[] = { &P_FUNCTION_Anon_48, &P_FUNCTION_Anon_49, &P_FUNCTION_Anon_50, &P_FUNCTION_SendRequestToCluster };

PRT_EVENTDECL* P_TestDriver0_RECV_INNER_1[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver0_RECV_1 =
{
    34U,
    P_TestDriver0_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_TestDriver0_SEND_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver0_SEND =
{
    34U,
    P_TestDriver0_SEND_INNER,
    NULL
};

PRT_UINT32 P_TestDriver0_CREATES_ARR[] = { 0, 1 };
PRT_INTERFACESETDECL P_TestDriver0_CREATES = { 2, P_TestDriver0_CREATES_ARR };
PRT_MACHINEDECL P_MACHINE_TestDriver0 = 
{
    3U,
    "TestDriver0",
    &P_EVENTSET_TestDriver0_RECV_1,
    &P_EVENTSET_TestDriver0_SEND,
    &P_TestDriver0_CREATES,
    6U,
    2U,
    4U,
    4294967295U,
    0U,
    P_TestDriver0_VARS,
    P_TestDriver0_STATES,
    P_TestDriver0_METHODS
};

PRT_VARDECL P_TestDriver1_VARS[] = {
    { "Cluster", &P_GEND_TYPE_m },
    { "Counter", &P_GEND_TYPE_i },
    { "Servers", &P_GEND_TYPE_Sm },
    { "NumServers", &P_GEND_TYPE_i },
    { "LatestKey", &P_GEND_TYPE_r },
    { "LatestVal", &P_GEND_TYPE_r }
};

PRT_EVENTDECL* P_Init_DEFERS_INNER_4[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DEFERS_4 =
{
    0U,
    P_Init_DEFERS_INNER_4,
    NULL
};

PRT_EVENTDECL* P_Init_TRANS_INNER_4[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_TRANS_4 =
{
    0U,
    P_Init_TRANS_INNER_4,
    NULL
};

PRT_EVENTDECL* P_Init_DOS_INNER_4[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DOS_4 =
{
    0U,
    P_Init_DOS_INNER_4,
    NULL
};

#define P_STATE_TestDriver1_Init \
{ \
    "TestDriver1.Init", \
    0U, \
    0U, \
    &P_EVENTSET_Init_DEFERS_4, \
    &P_EVENTSET_Init_TRANS_4, \
    &P_EVENTSET_Init_DOS_4, \
    NULL, \
    NULL, \
    &P_FUNCTION_Anon_51, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Running1_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Running1_DEFERS =
{
    0U,
    P_Running1_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Running1_TRANS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Running1_TRANS =
{
    0U,
    P_Running1_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Running1_DOS_INNER[] = { &P_EVENT_Response };
PRT_EVENTSETDECL P_EVENTSET_Running1_DOS =
{
    1U,
    P_Running1_DOS_INNER,
    NULL
};

PRT_DODECL P_DOS_10[] =
{
    { 1, &P_EVENT_Response, &P_FUNCTION_Anon_53 }
};

#define P_STATE_TestDriver1_Running1 \
{ \
    "TestDriver1.Running1", \
    0U, \
    1U, \
    &P_EVENTSET_Running1_DEFERS, \
    &P_EVENTSET_Running1_TRANS, \
    &P_EVENTSET_Running1_DOS, \
    NULL, \
    P_DOS_10, \
    &P_FUNCTION_Anon_52, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_TestDriver1_STATES[] = { P_STATE_TestDriver1_Init, P_STATE_TestDriver1_Running1 };

PRT_VALUE* P_Anon_IMPL_51(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_Server_2 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    PRT_VALUE* P_VAR_idx_13 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_75 = NULL;
    PRT_VALUE* PTMP_tmp1_63 = NULL;
    PRT_VALUE* PTMP_tmp2_56 = NULL;
    PRT_VALUE* PTMP_tmp3_51 = NULL;
    PRT_VALUE* PTMP_tmp4_43 = NULL;
    PRT_VALUE* PTMP_tmp5_32 = NULL;
    PRT_VALUE* PTMP_tmp6_30 = NULL;
    PRT_VALUE* PTMP_tmp7_26 = NULL;
    PRT_VALUE* PTMP_tmp8_23 = NULL;
    PRT_VALUE* PTMP_tmp9_20 = NULL;
    PRT_VALUE* PTMP_tmp10_19 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_63 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_64 = { PRT_VALUE_KIND_INT, { .nt = 5 } };
    PRT_VALUE P_LIT_INT32_65 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_34 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_1294 = &(p_this->varValues[1]);
    PrtFreeValue(*P_LVALUE_1294);
    *P_LVALUE_1294 = PrtCloneValue((&P_LIT_INT32_63));
    
    PRT_VALUE** P_LVALUE_1295 = &(p_this->varValues[3]);
    PrtFreeValue(*P_LVALUE_1295);
    *P_LVALUE_1295 = PrtCloneValue((&P_LIT_INT32_64));
    
    PRT_VALUE** P_LVALUE_1296 = &(PTMP_tmp0_75);
    PrtFreeValue(*P_LVALUE_1296);
    *P_LVALUE_1296 = PrtMkDefaultValue(&P_GEND_TYPE_r);
    
    {
        PRT_VALUE** P_LVALUE_1297 = &(p_this->varValues[4]);
        PrtFreeValue(*P_LVALUE_1297);
        *P_LVALUE_1297 = PTMP_tmp0_75;
        PTMP_tmp0_75 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_1298 = &(PTMP_tmp1_63);
    PrtFreeValue(*P_LVALUE_1298);
    *P_LVALUE_1298 = PrtMkDefaultValue(&P_GEND_TYPE_r);
    
    {
        PRT_VALUE** P_LVALUE_1299 = &(p_this->varValues[5]);
        PrtFreeValue(*P_LVALUE_1299);
        *P_LVALUE_1299 = PTMP_tmp1_63;
        PTMP_tmp1_63 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_1300 = &(P_VAR_idx_13);
    PrtFreeValue(*P_LVALUE_1300);
    *P_LVALUE_1300 = PrtCloneValue((&P_LIT_INT32_63));
    
    PRT_VALUE** P_LVALUE_1301 = &(PTMP_tmp2_56);
    PrtFreeValue(*P_LVALUE_1301);
    *P_LVALUE_1301 = PrtCloneValue(PrtMkInterface(context, 0, 0)->id);
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_79;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_79;
    }
    
    {
        PRT_VALUE** P_LVALUE_1302 = &(p_this->varValues[0]);
        PrtFreeValue(*P_LVALUE_1302);
        *P_LVALUE_1302 = PTMP_tmp2_56;
        PTMP_tmp2_56 = NULL;
    }
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_34)))
    {
        PRT_VALUE** P_LVALUE_1303 = &(PTMP_tmp3_51);
        PrtFreeValue(*P_LVALUE_1303);
        *P_LVALUE_1303 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_13) < PrtPrimGetInt(p_this->varValues[3]));
        
        PRT_VALUE** P_LVALUE_1304 = &(PTMP_tmp4_43);
        PrtFreeValue(*P_LVALUE_1304);
        *P_LVALUE_1304 = PrtCloneValue(PTMP_tmp3_51);
        
        if (PrtPrimGetBool(PTMP_tmp4_43))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_1305 = &(PTMP_tmp5_32);
        PrtFreeValue(*P_LVALUE_1305);
        *P_LVALUE_1305 = PrtCloneValue(PrtMkInterface(context, 1, 0)->id);
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_79;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_79;
        }
        
        {
            PRT_VALUE** P_LVALUE_1306 = &(P_VAR_Server_2);
            PrtFreeValue(*P_LVALUE_1306);
            *P_LVALUE_1306 = PTMP_tmp5_32;
            PTMP_tmp5_32 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_1307 = &(PTMP_tmp6_30);
        PrtFreeValue(*P_LVALUE_1307);
        *P_LVALUE_1307 = PrtCloneValue(P_VAR_Server_2);
        
        PrtSeqInsertEx(p_this->varValues[2], P_VAR_idx_13, PTMP_tmp6_30, PRT_FALSE);
        *(&(PTMP_tmp6_30)) = NULL;
        
        PRT_VALUE** P_LVALUE_1308 = &(PTMP_tmp7_26);
        PrtFreeValue(*P_LVALUE_1308);
        *P_LVALUE_1308 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_1309 = &(PTMP_tmp8_23);
        PrtFreeValue(*P_LVALUE_1309);
        *P_LVALUE_1309 = PrtCloneValue((&P_EVENT_AddServer.value));
        
        PRT_VALUE** P_LVALUE_1310 = &(PTMP_tmp9_20);
        PrtFreeValue(*P_LVALUE_1310);
        *P_LVALUE_1310 = PrtCloneValue(P_VAR_Server_2);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp7_26), PTMP_tmp8_23, 1, &(PTMP_tmp9_20));
        *(&(PTMP_tmp8_23)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_79;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_79;
        }
        
        PRT_VALUE** P_LVALUE_1311 = &(PTMP_tmp10_19);
        PrtFreeValue(*P_LVALUE_1311);
        *P_LVALUE_1311 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_13) + PrtPrimGetInt((&P_LIT_INT32_65)));
        
        {
            PRT_VALUE** P_LVALUE_1312 = &(P_VAR_idx_13);
            PrtFreeValue(*P_LVALUE_1312);
            *P_LVALUE_1312 = PTMP_tmp10_19;
            PTMP_tmp10_19 = NULL;
        }
        
    }
    
    
    PrtGoto(p_this, 1U, 0);
    
p_return_79: ;
    PrtFreeValue(P_VAR_Server_2); P_VAR_Server_2 = NULL;
    PrtFreeValue(P_VAR_idx_13); P_VAR_idx_13 = NULL;
    PrtFreeValue(PTMP_tmp0_75); PTMP_tmp0_75 = NULL;
    PrtFreeValue(PTMP_tmp1_63); PTMP_tmp1_63 = NULL;
    PrtFreeValue(PTMP_tmp2_56); PTMP_tmp2_56 = NULL;
    PrtFreeValue(PTMP_tmp3_51); PTMP_tmp3_51 = NULL;
    PrtFreeValue(PTMP_tmp4_43); PTMP_tmp4_43 = NULL;
    PrtFreeValue(PTMP_tmp5_32); PTMP_tmp5_32 = NULL;
    PrtFreeValue(PTMP_tmp6_30); PTMP_tmp6_30 = NULL;
    PrtFreeValue(PTMP_tmp7_26); PTMP_tmp7_26 = NULL;
    PrtFreeValue(PTMP_tmp8_23); PTMP_tmp8_23 = NULL;
    PrtFreeValue(PTMP_tmp9_20); PTMP_tmp9_20 = NULL;
    PrtFreeValue(PTMP_tmp10_19); PTMP_tmp10_19 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_51 =
{
    NULL,
    &P_Anon_IMPL_51,
    NULL
};


PRT_VALUE* P_Anon_IMPL_52(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFreeValue(P_SendRequestToCluster_IMPL_1(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_80;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_80;
    }
    
p_return_80: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_52 =
{
    NULL,
    &P_Anon_IMPL_52,
    NULL
};


PRT_VALUE* P_Anon_IMPL_53(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_Server_3 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    PRT_VALUE* PTMP_tmp0_76 = NULL;
    PRT_VALUE* PTMP_tmp1_64 = NULL;
    PRT_VALUE* PTMP_tmp2_57 = NULL;
    PRT_VALUE* PTMP_tmp3_52 = NULL;
    PRT_VALUE* PTMP_tmp4_44 = NULL;
    PRT_VALUE* PTMP_tmp5_33 = NULL;
    PRT_VALUE* PTMP_tmp6_31 = NULL;
    PRT_VALUE* PTMP_tmp7_27 = NULL;
    PRT_VALUE* PTMP_tmp8_24 = NULL;
    PRT_VALUE* PTMP_tmp9_21 = NULL;
    PRT_VALUE* PTMP_tmp10_20 = NULL;
    PRT_VALUE* PTMP_tmp11_18 = NULL;
    PRT_VALUE* PTMP_tmp12_17 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_66 = { PRT_VALUE_KIND_INT, { .nt = 100 } };
    PRT_VALUE P_LIT_INT32_67 = { PRT_VALUE_KIND_INT, { .nt = 2 } };
    PRT_VALUE** P_LVALUE_1313 = &(PTMP_tmp0_76);
    PrtFreeValue(*P_LVALUE_1313);
    *P_LVALUE_1313 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[1]) >= PrtPrimGetInt((&P_LIT_INT32_66)));
    
    if (PrtPrimGetBool(PTMP_tmp0_76))
    {
        PRT_VALUE** P_LVALUE_1314 = &(PTMP_tmp1_64);
        PrtFreeValue(*P_LVALUE_1314);
        *P_LVALUE_1314 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_1315 = &(PTMP_tmp2_57);
        PrtFreeValue(*P_LVALUE_1315);
        *P_LVALUE_1315 = PrtCloneValue((&P_EVENT_ShutDown.value));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_64), PTMP_tmp2_57, 0);
        *(&(PTMP_tmp2_57)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_81;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_81;
        }
        
        PRT_VALUE** P_LVALUE_1316 = &(PTMP_tmp3_52);
        PrtFreeValue(*P_LVALUE_1316);
        *P_LVALUE_1316 = PrtCloneValue((&_P_EVENT_HALT_STRUCT.value));
        
        PrtRaise(p_this, PTMP_tmp3_52, 0);
        *(&(PTMP_tmp3_52)) = NULL;
        goto p_return_81;
        
    }
    
    else
    {
    }
    
    
    PRT_VALUE** P_LVALUE_1317 = &(PTMP_tmp4_44);
    PrtFreeValue(*P_LVALUE_1317);
    *P_LVALUE_1317 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_1318 = &(PTMP_tmp5_33);
    PrtFreeValue(*P_LVALUE_1318);
    *P_LVALUE_1318 = PrtCloneValue((&P_EVENT_RemoveServer.value));
    
    PRT_VALUE** P_LVALUE_1319 = &(PTMP_tmp6_31);
    PrtFreeValue(*P_LVALUE_1319);
    *P_LVALUE_1319 = PrtSeqGet(p_this->varValues[2], (&P_LIT_INT32_67));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp4_44), PTMP_tmp5_33, 1, &(PTMP_tmp6_31));
    *(&(PTMP_tmp5_33)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_81;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_81;
    }
    
    PrtRemoveByKey(p_this->varValues[2], (&P_LIT_INT32_67));
    
    PrtFreeValue(P_SendRequestToCluster_IMPL_1(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_81;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_81;
    }
    
    PRT_VALUE** P_LVALUE_1320 = &(PTMP_tmp7_27);
    PrtFreeValue(*P_LVALUE_1320);
    *P_LVALUE_1320 = PrtCloneValue(PrtMkInterface(context, 1, 0)->id);
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_81;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_81;
    }
    
    {
        PRT_VALUE** P_LVALUE_1321 = &(P_VAR_Server_3);
        PrtFreeValue(*P_LVALUE_1321);
        *P_LVALUE_1321 = PTMP_tmp7_27;
        PTMP_tmp7_27 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_1322 = &(PTMP_tmp8_24);
    PrtFreeValue(*P_LVALUE_1322);
    *P_LVALUE_1322 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[2]));
    
    PRT_VALUE** P_LVALUE_1323 = &(PTMP_tmp9_21);
    PrtFreeValue(*P_LVALUE_1323);
    *P_LVALUE_1323 = PrtCloneValue(P_VAR_Server_3);
    
    PrtSeqInsertEx(p_this->varValues[2], PTMP_tmp8_24, PTMP_tmp9_21, PRT_FALSE);
    *(&(PTMP_tmp9_21)) = NULL;
    
    PRT_VALUE** P_LVALUE_1324 = &(PTMP_tmp10_20);
    PrtFreeValue(*P_LVALUE_1324);
    *P_LVALUE_1324 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_1325 = &(PTMP_tmp11_18);
    PrtFreeValue(*P_LVALUE_1325);
    *P_LVALUE_1325 = PrtCloneValue((&P_EVENT_AddServer.value));
    
    PRT_VALUE** P_LVALUE_1326 = &(PTMP_tmp12_17);
    PrtFreeValue(*P_LVALUE_1326);
    *P_LVALUE_1326 = PrtCloneValue(P_VAR_Server_3);
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp10_20), PTMP_tmp11_18, 1, &(PTMP_tmp12_17));
    *(&(PTMP_tmp11_18)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_81;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_81;
    }
    
    PrtFreeValue(P_SendRequestToCluster_IMPL_1(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_81;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_81;
    }
    
p_return_81: ;
    PrtFreeValue(P_VAR_Server_3); P_VAR_Server_3 = NULL;
    PrtFreeValue(PTMP_tmp0_76); PTMP_tmp0_76 = NULL;
    PrtFreeValue(PTMP_tmp1_64); PTMP_tmp1_64 = NULL;
    PrtFreeValue(PTMP_tmp2_57); PTMP_tmp2_57 = NULL;
    PrtFreeValue(PTMP_tmp3_52); PTMP_tmp3_52 = NULL;
    PrtFreeValue(PTMP_tmp4_44); PTMP_tmp4_44 = NULL;
    PrtFreeValue(PTMP_tmp5_33); PTMP_tmp5_33 = NULL;
    PrtFreeValue(PTMP_tmp6_31); PTMP_tmp6_31 = NULL;
    PrtFreeValue(PTMP_tmp7_27); PTMP_tmp7_27 = NULL;
    PrtFreeValue(PTMP_tmp8_24); PTMP_tmp8_24 = NULL;
    PrtFreeValue(PTMP_tmp9_21); PTMP_tmp9_21 = NULL;
    PrtFreeValue(PTMP_tmp10_20); PTMP_tmp10_20 = NULL;
    PrtFreeValue(PTMP_tmp11_18); PTMP_tmp11_18 = NULL;
    PrtFreeValue(PTMP_tmp12_17); PTMP_tmp12_17 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_53 =
{
    NULL,
    &P_Anon_IMPL_53,
    NULL
};


PRT_VALUE* P_SendRequestToCluster_IMPL_1(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_77 = NULL;
    PRT_VALUE* PTMP_tmp1_65 = NULL;
    PRT_VALUE* PTMP_tmp2_58 = NULL;
    PRT_VALUE* PTMP_tmp3_53 = NULL;
    PRT_VALUE* PTMP_tmp4_45 = NULL;
    PRT_VALUE* PTMP_tmp5_34 = NULL;
    PRT_VALUE* PTMP_tmp6_32 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_68 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE** P_LVALUE_1327 = &(p_this->varValues[4]);
    PrtFreeValue(*P_LVALUE_1327);
    *P_LVALUE_1327 = PrtMkStringValue(PrtFormatString("k", 1, p_this->varValues[1], 1, 0, ""));
    
    PRT_VALUE** P_LVALUE_1328 = &(p_this->varValues[5]);
    PrtFreeValue(*P_LVALUE_1328);
    *P_LVALUE_1328 = PrtMkStringValue(PrtFormatString("v", 1, p_this->varValues[1], 1, 0, ""));
    
    PRT_VALUE** P_LVALUE_1329 = &(PTMP_tmp0_77);
    PrtFreeValue(*P_LVALUE_1329);
    *P_LVALUE_1329 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[1]) + PrtPrimGetInt((&P_LIT_INT32_68)));
    
    {
        PRT_VALUE** P_LVALUE_1330 = &(p_this->varValues[1]);
        PrtFreeValue(*P_LVALUE_1330);
        *P_LVALUE_1330 = PTMP_tmp0_77;
        PTMP_tmp0_77 = NULL;
    }
    
    PrtFormatPrintf("\n\n\n[Client] new request <", 2, p_this->varValues[4], p_this->varValues[5], 2, 0, ", ", 1, ">\n");
    
    PRT_VALUE** P_LVALUE_1331 = &(PTMP_tmp1_65);
    PrtFreeValue(*P_LVALUE_1331);
    *P_LVALUE_1331 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_1332 = &(PTMP_tmp2_58);
    PrtFreeValue(*P_LVALUE_1332);
    *P_LVALUE_1332 = PrtCloneValue((&P_EVENT_Request.value));
    
    PRT_VALUE** P_LVALUE_1333 = &(PTMP_tmp3_53);
    PrtFreeValue(*P_LVALUE_1333);
    *P_LVALUE_1333 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_1334 = &(PTMP_tmp4_45);
    PrtFreeValue(*P_LVALUE_1334);
    *P_LVALUE_1334 = PrtCloneValue(p_this->varValues[4]);
    
    PRT_VALUE** P_LVALUE_1335 = &(PTMP_tmp5_34);
    PrtFreeValue(*P_LVALUE_1335);
    *P_LVALUE_1335 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_1336 = &(PTMP_tmp6_32);
    PrtFreeValue(*P_LVALUE_1336);
    *P_LVALUE_1336 = (PrtMkTuple(&P_GEND_TYPE_T3Rrr_1, &(PTMP_tmp3_53), &(PTMP_tmp4_45), &(PTMP_tmp5_34)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_65), PTMP_tmp2_58, 1, &(PTMP_tmp6_32));
    *(&(PTMP_tmp2_58)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_82;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_82;
    }
    
p_return_82: ;
    PrtFreeValue(PTMP_tmp0_77); PTMP_tmp0_77 = NULL;
    PrtFreeValue(PTMP_tmp1_65); PTMP_tmp1_65 = NULL;
    PrtFreeValue(PTMP_tmp2_58); PTMP_tmp2_58 = NULL;
    PrtFreeValue(PTMP_tmp3_53); PTMP_tmp3_53 = NULL;
    PrtFreeValue(PTMP_tmp4_45); PTMP_tmp4_45 = NULL;
    PrtFreeValue(PTMP_tmp5_34); PTMP_tmp5_34 = NULL;
    PrtFreeValue(PTMP_tmp6_32); PTMP_tmp6_32 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_SendRequestToCluster_1 =
{
    "SendRequestToCluster",
    &P_SendRequestToCluster_IMPL_1,
    NULL
};


PRT_FUNDECL* P_TestDriver1_METHODS[] = { &P_FUNCTION_Anon_51, &P_FUNCTION_Anon_52, &P_FUNCTION_Anon_53, &P_FUNCTION_SendRequestToCluster_1 };

PRT_EVENTDECL* P_TestDriver1_RECV_INNER_1[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver1_RECV_1 =
{
    34U,
    P_TestDriver1_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_TestDriver1_SEND_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver1_SEND =
{
    34U,
    P_TestDriver1_SEND_INNER,
    NULL
};

PRT_UINT32 P_TestDriver1_CREATES_ARR[] = { 0, 1 };
PRT_INTERFACESETDECL P_TestDriver1_CREATES = { 2, P_TestDriver1_CREATES_ARR };
PRT_MACHINEDECL P_MACHINE_TestDriver1 = 
{
    4U,
    "TestDriver1",
    &P_EVENTSET_TestDriver1_RECV_1,
    &P_EVENTSET_TestDriver1_SEND,
    &P_TestDriver1_CREATES,
    6U,
    2U,
    4U,
    4294967295U,
    0U,
    P_TestDriver1_VARS,
    P_TestDriver1_STATES,
    P_TestDriver1_METHODS
};

PRT_VARDECL P_FailureInjector_VARS[] = {
    { "Participants", &P_GEND_TYPE_Sm },
    { "FailedSoFar", &P_GEND_TYPE_i }
};

PRT_EVENTDECL* P_Init_DEFERS_INNER_5[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DEFERS_5 =
{
    0U,
    P_Init_DEFERS_INNER_5,
    NULL
};

PRT_EVENTDECL* P_Init_TRANS_INNER_5[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_TRANS_5 =
{
    0U,
    P_Init_TRANS_INNER_5,
    NULL
};

PRT_EVENTDECL* P_Init_DOS_INNER_5[] = { &P_EVENT_InjectFailure };
PRT_EVENTSETDECL P_EVENTSET_Init_DOS_5 =
{
    1U,
    P_Init_DOS_INNER_5,
    NULL
};

PRT_DODECL P_DOS_11[] =
{
    { 0, &P_EVENT_InjectFailure, &P_FUNCTION_Anon_55 }
};

#define P_STATE_FailureInjector_Init \
{ \
    "FailureInjector.Init", \
    0U, \
    1U, \
    &P_EVENTSET_Init_DEFERS_5, \
    &P_EVENTSET_Init_TRANS_5, \
    &P_EVENTSET_Init_DOS_5, \
    NULL, \
    P_DOS_11, \
    &P_FUNCTION_Anon_54, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_FailureInjector_STATES[] = { P_STATE_FailureInjector_Init };

PRT_VALUE* P_Anon_IMPL_54(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_participants = argRefs[0];
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_69 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE** P_LVALUE_1337 = &(p_this->varValues[0]);
    PrtFreeValue(*P_LVALUE_1337);
    *P_LVALUE_1337 = PrtCloneValue(*P_VAR_participants);
    
    PRT_VALUE** P_LVALUE_1338 = &(p_this->varValues[1]);
    PrtFreeValue(*P_LVALUE_1338);
    *P_LVALUE_1338 = PrtCloneValue((&P_LIT_INT32_69));
    
p_return_83: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_54 =
{
    NULL,
    &P_Anon_IMPL_54,
    &P_GEND_TYPE_Sm
};


PRT_VALUE* P_Anon_IMPL_55(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_i_3 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_78 = NULL;
    PRT_VALUE* PTMP_tmp1_66 = NULL;
    PRT_VALUE* PTMP_tmp2_59 = NULL;
    PRT_VALUE* PTMP_tmp3_54 = NULL;
    PRT_VALUE* PTMP_tmp4_46 = NULL;
    PRT_VALUE* PTMP_tmp5_35 = NULL;
    PRT_VALUE* PTMP_tmp6_33 = NULL;
    PRT_VALUE* PTMP_tmp7_28 = NULL;
    PRT_VALUE* PTMP_tmp8_25 = NULL;
    PRT_VALUE* PTMP_tmp9_22 = NULL;
    PRT_VALUE* PTMP_tmp10_21 = NULL;
    PRT_VALUE* PTMP_tmp11_19 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_70 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_71 = { PRT_VALUE_KIND_INT, { .nt = 5 } };
    PRT_VALUE P_LIT_INT32_72 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_35 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_1339 = &(P_VAR_i_3);
    PrtFreeValue(*P_LVALUE_1339);
    *P_LVALUE_1339 = PrtCloneValue((&P_LIT_INT32_70));
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_35)))
    {
        PRT_VALUE** P_LVALUE_1340 = &(PTMP_tmp0_78);
        PrtFreeValue(*P_LVALUE_1340);
        *P_LVALUE_1340 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[0]));
        
        PRT_VALUE** P_LVALUE_1341 = &(PTMP_tmp1_66);
        PrtFreeValue(*P_LVALUE_1341);
        *P_LVALUE_1341 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_i_3) < PrtPrimGetInt(PTMP_tmp0_78));
        
        PRT_VALUE** P_LVALUE_1342 = &(PTMP_tmp2_59);
        PrtFreeValue(*P_LVALUE_1342);
        *P_LVALUE_1342 = PrtCloneValue(PTMP_tmp1_66);
        
        if (PrtPrimGetBool(PTMP_tmp2_59))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_1343 = &(PTMP_tmp3_54);
        PrtFreeValue(*P_LVALUE_1343);
        *P_LVALUE_1343 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[1]) < PrtPrimGetInt((&P_LIT_INT32_71)));
        
        PRT_VALUE** P_LVALUE_1344 = &(PTMP_tmp5_35);
        PrtFreeValue(*P_LVALUE_1344);
        *P_LVALUE_1344 = PrtCloneValue(PTMP_tmp3_54);
        
        if (PrtPrimGetBool(PTMP_tmp5_35))
        {
            PRT_VALUE** P_LVALUE_1345 = &(PTMP_tmp4_46);
            PrtFreeValue(*P_LVALUE_1345);
            *P_LVALUE_1345 = (PrtMkNondetBoolValue());
            
            PRT_VALUE** P_LVALUE_1346 = &(PTMP_tmp5_35);
            PrtFreeValue(*P_LVALUE_1346);
            *P_LVALUE_1346 = PrtCloneValue(PTMP_tmp4_46);
            
        }
        
        
        if (PrtPrimGetBool(PTMP_tmp5_35))
        {
            PRT_VALUE** P_LVALUE_1347 = &(PTMP_tmp6_33);
            PrtFreeValue(*P_LVALUE_1347);
            *P_LVALUE_1347 = (PrtMkNondetBoolValue());
            
            if (PrtPrimGetBool(PTMP_tmp6_33))
            {
                PRT_VALUE** P_LVALUE_1348 = &(PTMP_tmp7_28);
                PrtFreeValue(*P_LVALUE_1348);
                *P_LVALUE_1348 = PrtSeqGet(p_this->varValues[0], P_VAR_i_3);
                
                PRT_VALUE** P_LVALUE_1349 = &(PTMP_tmp8_25);
                PrtFreeValue(*P_LVALUE_1349);
                *P_LVALUE_1349 = PrtCloneValue(PTMP_tmp7_28);
                
                PRT_VALUE** P_LVALUE_1350 = &(PTMP_tmp9_22);
                PrtFreeValue(*P_LVALUE_1350);
                *P_LVALUE_1350 = PrtCloneValue((&_P_EVENT_HALT_STRUCT.value));
                
                PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp8_25), PTMP_tmp9_22, 0);
                *(&(PTMP_tmp9_22)) = NULL;
                if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
                    goto p_return_84;
                }
                if (p_this->isHalted == PRT_TRUE) {
                    PrtFreeValue(_P_GEN_retval);
                    _P_GEN_retval = NULL;
                    goto p_return_84;
                }
                
                PRT_VALUE** P_LVALUE_1351 = &(PTMP_tmp10_21);
                PrtFreeValue(*P_LVALUE_1351);
                *P_LVALUE_1351 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[1]) + PrtPrimGetInt((&P_LIT_INT32_72)));
                
                {
                    PRT_VALUE** P_LVALUE_1352 = &(p_this->varValues[1]);
                    PrtFreeValue(*P_LVALUE_1352);
                    *P_LVALUE_1352 = PTMP_tmp10_21;
                    PTMP_tmp10_21 = NULL;
                }
                
                break;
                
            }
            
            else
            {
            }
            
            
        }
        
        else
        {
        }
        
        
        PRT_VALUE** P_LVALUE_1353 = &(PTMP_tmp11_19);
        PrtFreeValue(*P_LVALUE_1353);
        *P_LVALUE_1353 = PrtMkIntValue(PrtPrimGetInt(P_VAR_i_3) + PrtPrimGetInt((&P_LIT_INT32_72)));
        
        {
            PRT_VALUE** P_LVALUE_1354 = &(P_VAR_i_3);
            PrtFreeValue(*P_LVALUE_1354);
            *P_LVALUE_1354 = PTMP_tmp11_19;
            PTMP_tmp11_19 = NULL;
        }
        
    }
    
    
p_return_84: ;
    PrtFreeValue(P_VAR_i_3); P_VAR_i_3 = NULL;
    PrtFreeValue(PTMP_tmp0_78); PTMP_tmp0_78 = NULL;
    PrtFreeValue(PTMP_tmp1_66); PTMP_tmp1_66 = NULL;
    PrtFreeValue(PTMP_tmp2_59); PTMP_tmp2_59 = NULL;
    PrtFreeValue(PTMP_tmp3_54); PTMP_tmp3_54 = NULL;
    PrtFreeValue(PTMP_tmp4_46); PTMP_tmp4_46 = NULL;
    PrtFreeValue(PTMP_tmp5_35); PTMP_tmp5_35 = NULL;
    PrtFreeValue(PTMP_tmp6_33); PTMP_tmp6_33 = NULL;
    PrtFreeValue(PTMP_tmp7_28); PTMP_tmp7_28 = NULL;
    PrtFreeValue(PTMP_tmp8_25); PTMP_tmp8_25 = NULL;
    PrtFreeValue(PTMP_tmp9_22); PTMP_tmp9_22 = NULL;
    PrtFreeValue(PTMP_tmp10_21); PTMP_tmp10_21 = NULL;
    PrtFreeValue(PTMP_tmp11_19); PTMP_tmp11_19 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_55 =
{
    NULL,
    &P_Anon_IMPL_55,
    NULL
};


PRT_FUNDECL* P_FailureInjector_METHODS[] = { &P_FUNCTION_Anon_54, &P_FUNCTION_Anon_55 };

PRT_EVENTDECL* P_FailureInjector_RECV_INNER_1[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_FailureInjector_RECV_1 =
{
    34U,
    P_FailureInjector_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_FailureInjector_SEND_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_FailureInjector_SEND =
{
    34U,
    P_FailureInjector_SEND_INNER,
    NULL
};

PRT_MACHINEDECL P_MACHINE_FailureInjector = 
{
    5U,
    "FailureInjector",
    &P_EVENTSET_FailureInjector_RECV_1,
    &P_EVENTSET_FailureInjector_SEND,
    NULL,
    2U,
    1U,
    2U,
    4294967295U,
    0U,
    P_FailureInjector_VARS,
    P_FailureInjector_STATES,
    P_FailureInjector_METHODS
};

PRT_VARDECL P_TestDriver2_VARS[] = {
    { "Cluster", &P_GEND_TYPE_m },
    { "Counter", &P_GEND_TYPE_i },
    { "Servers", &P_GEND_TYPE_Sm },
    { "NumServers", &P_GEND_TYPE_i },
    { "LatestKey", &P_GEND_TYPE_r },
    { "LatestVal", &P_GEND_TYPE_r },
    { "FailureInjector", &P_GEND_TYPE_m }
};

PRT_EVENTDECL* P_Init_DEFERS_INNER_6[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DEFERS_6 =
{
    0U,
    P_Init_DEFERS_INNER_6,
    NULL
};

PRT_EVENTDECL* P_Init_TRANS_INNER_6[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_TRANS_6 =
{
    0U,
    P_Init_TRANS_INNER_6,
    NULL
};

PRT_EVENTDECL* P_Init_DOS_INNER_6[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DOS_6 =
{
    0U,
    P_Init_DOS_INNER_6,
    NULL
};

#define P_STATE_TestDriver2_Init \
{ \
    "TestDriver2.Init", \
    0U, \
    0U, \
    &P_EVENTSET_Init_DEFERS_6, \
    &P_EVENTSET_Init_TRANS_6, \
    &P_EVENTSET_Init_DOS_6, \
    NULL, \
    NULL, \
    &P_FUNCTION_Anon_56, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Running2_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Running2_DEFERS =
{
    0U,
    P_Running2_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Running2_TRANS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Running2_TRANS =
{
    0U,
    P_Running2_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Running2_DOS_INNER[] = { &P_EVENT_Response };
PRT_EVENTSETDECL P_EVENTSET_Running2_DOS =
{
    1U,
    P_Running2_DOS_INNER,
    NULL
};

PRT_DODECL P_DOS_12[] =
{
    { 1, &P_EVENT_Response, &P_FUNCTION_Anon_58 }
};

#define P_STATE_TestDriver2_Running2 \
{ \
    "TestDriver2.Running2", \
    0U, \
    1U, \
    &P_EVENTSET_Running2_DEFERS, \
    &P_EVENTSET_Running2_TRANS, \
    &P_EVENTSET_Running2_DOS, \
    NULL, \
    P_DOS_12, \
    &P_FUNCTION_Anon_57, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_TestDriver2_STATES[] = { P_STATE_TestDriver2_Init, P_STATE_TestDriver2_Running2 };

PRT_VALUE* P_Anon_IMPL_56(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_Server_4 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    PRT_VALUE* P_VAR_idx_14 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_79 = NULL;
    PRT_VALUE* PTMP_tmp1_67 = NULL;
    PRT_VALUE* PTMP_tmp2_60 = NULL;
    PRT_VALUE* PTMP_tmp3_55 = NULL;
    PRT_VALUE* PTMP_tmp4_47 = NULL;
    PRT_VALUE* PTMP_tmp5_36 = NULL;
    PRT_VALUE* PTMP_tmp6_34 = NULL;
    PRT_VALUE* PTMP_tmp7_29 = NULL;
    PRT_VALUE* PTMP_tmp8_26 = NULL;
    PRT_VALUE* PTMP_tmp9_23 = NULL;
    PRT_VALUE* PTMP_tmp10_22 = NULL;
    PRT_VALUE* PTMP_tmp11_20 = NULL;
    PRT_VALUE* PTMP_tmp12_18 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_73 = { PRT_VALUE_KIND_INT, { .nt = 0 } };
    PRT_VALUE P_LIT_INT32_74 = { PRT_VALUE_KIND_INT, { .nt = 10 } };
    PRT_VALUE P_LIT_INT32_75 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_36 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    PRT_VALUE** P_LVALUE_1355 = &(p_this->varValues[1]);
    PrtFreeValue(*P_LVALUE_1355);
    *P_LVALUE_1355 = PrtCloneValue((&P_LIT_INT32_73));
    
    PRT_VALUE** P_LVALUE_1356 = &(p_this->varValues[3]);
    PrtFreeValue(*P_LVALUE_1356);
    *P_LVALUE_1356 = PrtCloneValue((&P_LIT_INT32_74));
    
    PRT_VALUE** P_LVALUE_1357 = &(PTMP_tmp0_79);
    PrtFreeValue(*P_LVALUE_1357);
    *P_LVALUE_1357 = PrtMkDefaultValue(&P_GEND_TYPE_r);
    
    {
        PRT_VALUE** P_LVALUE_1358 = &(p_this->varValues[4]);
        PrtFreeValue(*P_LVALUE_1358);
        *P_LVALUE_1358 = PTMP_tmp0_79;
        PTMP_tmp0_79 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_1359 = &(PTMP_tmp1_67);
    PrtFreeValue(*P_LVALUE_1359);
    *P_LVALUE_1359 = PrtMkDefaultValue(&P_GEND_TYPE_r);
    
    {
        PRT_VALUE** P_LVALUE_1360 = &(p_this->varValues[5]);
        PrtFreeValue(*P_LVALUE_1360);
        *P_LVALUE_1360 = PTMP_tmp1_67;
        PTMP_tmp1_67 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_1361 = &(P_VAR_idx_14);
    PrtFreeValue(*P_LVALUE_1361);
    *P_LVALUE_1361 = PrtCloneValue((&P_LIT_INT32_73));
    
    PRT_VALUE** P_LVALUE_1362 = &(PTMP_tmp2_60);
    PrtFreeValue(*P_LVALUE_1362);
    *P_LVALUE_1362 = PrtCloneValue(PrtMkInterface(context, 0, 0)->id);
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_85;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_85;
    }
    
    {
        PRT_VALUE** P_LVALUE_1363 = &(p_this->varValues[0]);
        PrtFreeValue(*P_LVALUE_1363);
        *P_LVALUE_1363 = PTMP_tmp2_60;
        PTMP_tmp2_60 = NULL;
    }
    
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_36)))
    {
        PRT_VALUE** P_LVALUE_1364 = &(PTMP_tmp3_55);
        PrtFreeValue(*P_LVALUE_1364);
        *P_LVALUE_1364 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_idx_14) < PrtPrimGetInt(p_this->varValues[3]));
        
        PRT_VALUE** P_LVALUE_1365 = &(PTMP_tmp4_47);
        PrtFreeValue(*P_LVALUE_1365);
        *P_LVALUE_1365 = PrtCloneValue(PTMP_tmp3_55);
        
        if (PrtPrimGetBool(PTMP_tmp4_47))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_1366 = &(PTMP_tmp5_36);
        PrtFreeValue(*P_LVALUE_1366);
        *P_LVALUE_1366 = PrtCloneValue(PrtMkInterface(context, 1, 0)->id);
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_85;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_85;
        }
        
        {
            PRT_VALUE** P_LVALUE_1367 = &(P_VAR_Server_4);
            PrtFreeValue(*P_LVALUE_1367);
            *P_LVALUE_1367 = PTMP_tmp5_36;
            PTMP_tmp5_36 = NULL;
        }
        
        PRT_VALUE** P_LVALUE_1368 = &(PTMP_tmp6_34);
        PrtFreeValue(*P_LVALUE_1368);
        *P_LVALUE_1368 = PrtCloneValue(P_VAR_Server_4);
        
        PrtSeqInsertEx(p_this->varValues[2], P_VAR_idx_14, PTMP_tmp6_34, PRT_FALSE);
        *(&(PTMP_tmp6_34)) = NULL;
        
        PRT_VALUE** P_LVALUE_1369 = &(PTMP_tmp7_29);
        PrtFreeValue(*P_LVALUE_1369);
        *P_LVALUE_1369 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_1370 = &(PTMP_tmp8_26);
        PrtFreeValue(*P_LVALUE_1370);
        *P_LVALUE_1370 = PrtCloneValue((&P_EVENT_AddServer.value));
        
        PRT_VALUE** P_LVALUE_1371 = &(PTMP_tmp9_23);
        PrtFreeValue(*P_LVALUE_1371);
        *P_LVALUE_1371 = PrtCloneValue(P_VAR_Server_4);
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp7_29), PTMP_tmp8_26, 1, &(PTMP_tmp9_23));
        *(&(PTMP_tmp8_26)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_85;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_85;
        }
        
        PRT_VALUE** P_LVALUE_1372 = &(PTMP_tmp10_22);
        PrtFreeValue(*P_LVALUE_1372);
        *P_LVALUE_1372 = PrtMkIntValue(PrtPrimGetInt(P_VAR_idx_14) + PrtPrimGetInt((&P_LIT_INT32_75)));
        
        {
            PRT_VALUE** P_LVALUE_1373 = &(P_VAR_idx_14);
            PrtFreeValue(*P_LVALUE_1373);
            *P_LVALUE_1373 = PTMP_tmp10_22;
            PTMP_tmp10_22 = NULL;
        }
        
    }
    
    
    PRT_VALUE** P_LVALUE_1374 = &(PTMP_tmp11_20);
    PrtFreeValue(*P_LVALUE_1374);
    *P_LVALUE_1374 = PrtCloneValue(p_this->varValues[2]);
    
    PRT_VALUE** P_LVALUE_1375 = &(PTMP_tmp12_18);
    PrtFreeValue(*P_LVALUE_1375);
    *P_LVALUE_1375 = PrtCloneValue(PrtMkInterface(context, 4, 1, &(PTMP_tmp11_20))->id);
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_85;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_85;
    }
    
    {
        PRT_VALUE** P_LVALUE_1376 = &(p_this->varValues[6]);
        PrtFreeValue(*P_LVALUE_1376);
        *P_LVALUE_1376 = PTMP_tmp12_18;
        PTMP_tmp12_18 = NULL;
    }
    
    PrtGoto(p_this, 1U, 0);
    
p_return_85: ;
    PrtFreeValue(P_VAR_Server_4); P_VAR_Server_4 = NULL;
    PrtFreeValue(P_VAR_idx_14); P_VAR_idx_14 = NULL;
    PrtFreeValue(PTMP_tmp0_79); PTMP_tmp0_79 = NULL;
    PrtFreeValue(PTMP_tmp1_67); PTMP_tmp1_67 = NULL;
    PrtFreeValue(PTMP_tmp2_60); PTMP_tmp2_60 = NULL;
    PrtFreeValue(PTMP_tmp3_55); PTMP_tmp3_55 = NULL;
    PrtFreeValue(PTMP_tmp4_47); PTMP_tmp4_47 = NULL;
    PrtFreeValue(PTMP_tmp5_36); PTMP_tmp5_36 = NULL;
    PrtFreeValue(PTMP_tmp6_34); PTMP_tmp6_34 = NULL;
    PrtFreeValue(PTMP_tmp7_29); PTMP_tmp7_29 = NULL;
    PrtFreeValue(PTMP_tmp8_26); PTMP_tmp8_26 = NULL;
    PrtFreeValue(PTMP_tmp9_23); PTMP_tmp9_23 = NULL;
    PrtFreeValue(PTMP_tmp10_22); PTMP_tmp10_22 = NULL;
    PrtFreeValue(PTMP_tmp11_20); PTMP_tmp11_20 = NULL;
    PrtFreeValue(PTMP_tmp12_18); PTMP_tmp12_18 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_56 =
{
    NULL,
    &P_Anon_IMPL_56,
    NULL
};


PRT_VALUE* P_Anon_IMPL_57(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PrtFreeValue(P_SendRequestToCluster_IMPL_2(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_86;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_86;
    }
    
p_return_86: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_57 =
{
    NULL,
    &P_Anon_IMPL_57,
    NULL
};


PRT_VALUE* P_Anon_IMPL_58(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_Server_5 = PrtMkDefaultValue(&P_GEND_TYPE_m);
    PRT_VALUE* PTMP_tmp0_80 = NULL;
    PRT_VALUE* PTMP_tmp1_68 = NULL;
    PRT_VALUE* PTMP_tmp2_61 = NULL;
    PRT_VALUE* PTMP_tmp3_56 = NULL;
    PRT_VALUE* PTMP_tmp4_48 = NULL;
    PRT_VALUE* PTMP_tmp5_37 = NULL;
    PRT_VALUE* PTMP_tmp6_35 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_76 = { PRT_VALUE_KIND_INT, { .nt = 100 } };
    PRT_VALUE** P_LVALUE_1377 = &(PTMP_tmp0_80);
    PrtFreeValue(*P_LVALUE_1377);
    *P_LVALUE_1377 = PrtMkBoolValue(PrtPrimGetInt(p_this->varValues[1]) >= PrtPrimGetInt((&P_LIT_INT32_76)));
    
    if (PrtPrimGetBool(PTMP_tmp0_80))
    {
        PRT_VALUE** P_LVALUE_1378 = &(PTMP_tmp1_68);
        PrtFreeValue(*P_LVALUE_1378);
        *P_LVALUE_1378 = PrtCloneValue(p_this->varValues[0]);
        
        PRT_VALUE** P_LVALUE_1379 = &(PTMP_tmp2_61);
        PrtFreeValue(*P_LVALUE_1379);
        *P_LVALUE_1379 = PrtCloneValue((&P_EVENT_ShutDown.value));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_68), PTMP_tmp2_61, 0);
        *(&(PTMP_tmp2_61)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_87;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_87;
        }
        
        PRT_VALUE** P_LVALUE_1380 = &(PTMP_tmp3_56);
        PrtFreeValue(*P_LVALUE_1380);
        *P_LVALUE_1380 = PrtCloneValue((&_P_EVENT_HALT_STRUCT.value));
        
        PrtRaise(p_this, PTMP_tmp3_56, 0);
        *(&(PTMP_tmp3_56)) = NULL;
        goto p_return_87;
        
    }
    
    else
    {
    }
    
    
    PRT_VALUE** P_LVALUE_1381 = &(PTMP_tmp4_48);
    PrtFreeValue(*P_LVALUE_1381);
    *P_LVALUE_1381 = (PrtMkNondetBoolValue());
    
    if (PrtPrimGetBool(PTMP_tmp4_48))
    {
        PRT_VALUE** P_LVALUE_1382 = &(PTMP_tmp5_37);
        PrtFreeValue(*P_LVALUE_1382);
        *P_LVALUE_1382 = PrtCloneValue(p_this->varValues[6]);
        
        PRT_VALUE** P_LVALUE_1383 = &(PTMP_tmp6_35);
        PrtFreeValue(*P_LVALUE_1383);
        *P_LVALUE_1383 = PrtCloneValue((&P_EVENT_InjectFailure.value));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp5_37), PTMP_tmp6_35, 0);
        *(&(PTMP_tmp6_35)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_87;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_87;
        }
        
    }
    
    else
    {
    }
    
    
    PrtFreeValue(P_SendRequestToCluster_IMPL_2(context, _P_GEN_funargs));
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_87;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_87;
    }
    
p_return_87: ;
    PrtFreeValue(P_VAR_Server_5); P_VAR_Server_5 = NULL;
    PrtFreeValue(PTMP_tmp0_80); PTMP_tmp0_80 = NULL;
    PrtFreeValue(PTMP_tmp1_68); PTMP_tmp1_68 = NULL;
    PrtFreeValue(PTMP_tmp2_61); PTMP_tmp2_61 = NULL;
    PrtFreeValue(PTMP_tmp3_56); PTMP_tmp3_56 = NULL;
    PrtFreeValue(PTMP_tmp4_48); PTMP_tmp4_48 = NULL;
    PrtFreeValue(PTMP_tmp5_37); PTMP_tmp5_37 = NULL;
    PrtFreeValue(PTMP_tmp6_35); PTMP_tmp6_35 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_58 =
{
    NULL,
    &P_Anon_IMPL_58,
    NULL
};


PRT_VALUE* P_SendRequestToCluster_IMPL_2(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_81 = NULL;
    PRT_VALUE* PTMP_tmp1_69 = NULL;
    PRT_VALUE* PTMP_tmp2_62 = NULL;
    PRT_VALUE* PTMP_tmp3_57 = NULL;
    PRT_VALUE* PTMP_tmp4_49 = NULL;
    PRT_VALUE* PTMP_tmp5_38 = NULL;
    PRT_VALUE* PTMP_tmp6_36 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_77 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE** P_LVALUE_1384 = &(p_this->varValues[4]);
    PrtFreeValue(*P_LVALUE_1384);
    *P_LVALUE_1384 = PrtMkStringValue(PrtFormatString("k", 1, p_this->varValues[1], 1, 0, ""));
    
    PRT_VALUE** P_LVALUE_1385 = &(p_this->varValues[5]);
    PrtFreeValue(*P_LVALUE_1385);
    *P_LVALUE_1385 = PrtMkStringValue(PrtFormatString("v", 1, p_this->varValues[1], 1, 0, ""));
    
    PRT_VALUE** P_LVALUE_1386 = &(PTMP_tmp0_81);
    PrtFreeValue(*P_LVALUE_1386);
    *P_LVALUE_1386 = PrtMkIntValue(PrtPrimGetInt(p_this->varValues[1]) + PrtPrimGetInt((&P_LIT_INT32_77)));
    
    {
        PRT_VALUE** P_LVALUE_1387 = &(p_this->varValues[1]);
        PrtFreeValue(*P_LVALUE_1387);
        *P_LVALUE_1387 = PTMP_tmp0_81;
        PTMP_tmp0_81 = NULL;
    }
    
    PrtFormatPrintf("\n\n\n[Client] new request <", 2, p_this->varValues[4], p_this->varValues[5], 2, 0, ", ", 1, ">\n");
    
    PRT_VALUE** P_LVALUE_1388 = &(PTMP_tmp1_69);
    PrtFreeValue(*P_LVALUE_1388);
    *P_LVALUE_1388 = PrtCloneValue(p_this->varValues[0]);
    
    PRT_VALUE** P_LVALUE_1389 = &(PTMP_tmp2_62);
    PrtFreeValue(*P_LVALUE_1389);
    *P_LVALUE_1389 = PrtCloneValue((&P_EVENT_Request.value));
    
    PRT_VALUE** P_LVALUE_1390 = &(PTMP_tmp3_57);
    PrtFreeValue(*P_LVALUE_1390);
    *P_LVALUE_1390 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_1391 = &(PTMP_tmp4_49);
    PrtFreeValue(*P_LVALUE_1391);
    *P_LVALUE_1391 = PrtCloneValue(p_this->varValues[4]);
    
    PRT_VALUE** P_LVALUE_1392 = &(PTMP_tmp5_38);
    PrtFreeValue(*P_LVALUE_1392);
    *P_LVALUE_1392 = PrtCloneValue(p_this->varValues[5]);
    
    PRT_VALUE** P_LVALUE_1393 = &(PTMP_tmp6_36);
    PrtFreeValue(*P_LVALUE_1393);
    *P_LVALUE_1393 = (PrtMkTuple(&P_GEND_TYPE_T3Rrr_2, &(PTMP_tmp3_57), &(PTMP_tmp4_49), &(PTMP_tmp5_38)));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp1_69), PTMP_tmp2_62, 1, &(PTMP_tmp6_36));
    *(&(PTMP_tmp2_62)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_88;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_88;
    }
    
p_return_88: ;
    PrtFreeValue(PTMP_tmp0_81); PTMP_tmp0_81 = NULL;
    PrtFreeValue(PTMP_tmp1_69); PTMP_tmp1_69 = NULL;
    PrtFreeValue(PTMP_tmp2_62); PTMP_tmp2_62 = NULL;
    PrtFreeValue(PTMP_tmp3_57); PTMP_tmp3_57 = NULL;
    PrtFreeValue(PTMP_tmp4_49); PTMP_tmp4_49 = NULL;
    PrtFreeValue(PTMP_tmp5_38); PTMP_tmp5_38 = NULL;
    PrtFreeValue(PTMP_tmp6_36); PTMP_tmp6_36 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_SendRequestToCluster_2 =
{
    "SendRequestToCluster",
    &P_SendRequestToCluster_IMPL_2,
    NULL
};


PRT_FUNDECL* P_TestDriver2_METHODS[] = { &P_FUNCTION_Anon_56, &P_FUNCTION_Anon_57, &P_FUNCTION_Anon_58, &P_FUNCTION_SendRequestToCluster_2 };

PRT_EVENTDECL* P_TestDriver2_RECV_INNER_1[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver2_RECV_1 =
{
    34U,
    P_TestDriver2_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_TestDriver2_SEND_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_TestDriver2_SEND =
{
    34U,
    P_TestDriver2_SEND_INNER,
    NULL
};

PRT_UINT32 P_TestDriver2_CREATES_ARR[] = { 0, 4, 1 };
PRT_INTERFACESETDECL P_TestDriver2_CREATES = { 3, P_TestDriver2_CREATES_ARR };
PRT_MACHINEDECL P_MACHINE_TestDriver2 = 
{
    6U,
    "TestDriver2",
    &P_EVENTSET_TestDriver2_RECV_1,
    &P_EVENTSET_TestDriver2_SEND,
    &P_TestDriver2_CREATES,
    7U,
    2U,
    4U,
    4294967295U,
    0U,
    P_TestDriver2_VARS,
    P_TestDriver2_STATES,
    P_TestDriver2_METHODS
};

PRT_VARDECL P_WallclockTimer_VARS[] = {
    { "Servers", &P_GEND_TYPE_Sm },
    { "ClusterManager", &P_GEND_TYPE_m }
};

PRT_EVENTDECL* P_Init_DEFERS_INNER_7[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Init_DEFERS_7 =
{
    0U,
    P_Init_DEFERS_INNER_7,
    NULL
};

PRT_EVENTDECL* P_Init_TRANS_INNER_7[] = { &P_EVENT_StartTimer };
PRT_EVENTSETDECL P_EVENTSET_Init_TRANS_7 =
{
    1U,
    P_Init_TRANS_INNER_7,
    NULL
};

PRT_EVENTDECL* P_Init_DOS_INNER_7[] = { &P_EVENT_ConfigureWallclock };
PRT_EVENTSETDECL P_EVENTSET_Init_DOS_7 =
{
    1U,
    P_Init_DOS_INNER_7,
    NULL
};

PRT_TRANSDECL P_TRANS_9[] =
{
    { 0, &P_EVENT_StartTimer, 1, &_P_NO_OP }
};

PRT_DODECL P_DOS_13[] =
{
    { 0, &P_EVENT_ConfigureWallclock, &P_FUNCTION_Anon_59 }
};

#define P_STATE_WallclockTimer_Init \
{ \
    "WallclockTimer.Init", \
    1U, \
    1U, \
    &P_EVENTSET_Init_DEFERS_7, \
    &P_EVENTSET_Init_TRANS_7, \
    &P_EVENTSET_Init_DOS_7, \
    P_TRANS_9, \
    P_DOS_13, \
    &_P_NO_OP, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Active_DEFERS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Active_DEFERS =
{
    0U,
    P_Active_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Active_TRANS_INNER[] = { &P_EVENT_CancelTimer };
PRT_EVENTSETDECL P_EVENTSET_Active_TRANS =
{
    1U,
    P_Active_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Active_DOS_INNER[] = { &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers };
PRT_EVENTSETDECL P_EVENTSET_Active_DOS =
{
    3U,
    P_Active_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_10[] =
{
    { 1, &P_EVENT_CancelTimer, 2, &_P_NO_OP }
};

PRT_DODECL P_DOS_14[] =
{
    { 1, &P_EVENT_UpdateServers, &P_FUNCTION_Anon_61 },
    { 1, &P_EVENT_TickEvent, &P_FUNCTION_Tick },
    { 1, &P_EVENT_StartTimer, NULL }
};

#define P_STATE_WallclockTimer_Active \
{ \
    "WallclockTimer.Active", \
    1U, \
    3U, \
    &P_EVENTSET_Active_DEFERS, \
    &P_EVENTSET_Active_TRANS, \
    &P_EVENTSET_Active_DOS, \
    P_TRANS_10, \
    P_DOS_14, \
    &P_FUNCTION_Anon_60, \
    &_P_NO_OP, \
}

PRT_EVENTDECL* P_Inactive_DEFERS_INNER[] = { &P_EVENT_CancelTimer, &P_EVENT_TickEvent };
PRT_EVENTSETDECL P_EVENTSET_Inactive_DEFERS =
{
    2U,
    P_Inactive_DEFERS_INNER,
    NULL
};

PRT_EVENTDECL* P_Inactive_TRANS_INNER[] = { &P_EVENT_StartTimer };
PRT_EVENTSETDECL P_EVENTSET_Inactive_TRANS =
{
    1U,
    P_Inactive_TRANS_INNER,
    NULL
};

PRT_EVENTDECL* P_Inactive_DOS_INNER[] = { NULL };
PRT_EVENTSETDECL P_EVENTSET_Inactive_DOS =
{
    0U,
    P_Inactive_DOS_INNER,
    NULL
};

PRT_TRANSDECL P_TRANS_11[] =
{
    { 2, &P_EVENT_StartTimer, 1, &_P_NO_OP }
};

#define P_STATE_WallclockTimer_Inactive \
{ \
    "WallclockTimer.Inactive", \
    1U, \
    0U, \
    &P_EVENTSET_Inactive_DEFERS, \
    &P_EVENTSET_Inactive_TRANS, \
    &P_EVENTSET_Inactive_DOS, \
    P_TRANS_11, \
    NULL, \
    &_P_NO_OP, \
    &_P_NO_OP, \
}

PRT_STATEDECL P_WallclockTimer_STATES[] = { P_STATE_WallclockTimer_Init, P_STATE_WallclockTimer_Active, P_STATE_WallclockTimer_Inactive };

PRT_VALUE* P_Anon_IMPL_59(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_payload_15 = argRefs[0];
    PRT_VALUE* PTMP_tmp0_82 = NULL;
    PRT_VALUE* PTMP_tmp1_70 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_1394 = &(PTMP_tmp0_82);
    PrtFreeValue(*P_LVALUE_1394);
    *P_LVALUE_1394 = PrtTupleGet(*P_VAR_payload_15, 0);
    
    {
        PRT_VALUE** P_LVALUE_1395 = &(p_this->varValues[0]);
        PrtFreeValue(*P_LVALUE_1395);
        *P_LVALUE_1395 = PTMP_tmp0_82;
        PTMP_tmp0_82 = NULL;
    }
    
    PRT_VALUE** P_LVALUE_1396 = &(PTMP_tmp1_70);
    PrtFreeValue(*P_LVALUE_1396);
    *P_LVALUE_1396 = PrtTupleGet(*P_VAR_payload_15, 1);
    
    {
        PRT_VALUE** P_LVALUE_1397 = &(p_this->varValues[1]);
        PrtFreeValue(*P_LVALUE_1397);
        *P_LVALUE_1397 = PTMP_tmp1_70;
        PTMP_tmp1_70 = NULL;
    }
    
p_return_89: ;
    PrtFreeValue(PTMP_tmp0_82); PTMP_tmp0_82 = NULL;
    PrtFreeValue(PTMP_tmp1_70); PTMP_tmp1_70 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_59 =
{
    NULL,
    &P_Anon_IMPL_59,
    &P_GEND_TYPE_T2Smm
};


PRT_VALUE* P_Anon_IMPL_60(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* PTMP_tmp0_83 = NULL;
    PRT_VALUE* PTMP_tmp1_71 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_1398 = &(PTMP_tmp0_83);
    PrtFreeValue(*P_LVALUE_1398);
    *P_LVALUE_1398 = PrtCloneValue((p_this->id));
    
    PRT_VALUE** P_LVALUE_1399 = &(PTMP_tmp1_71);
    PrtFreeValue(*P_LVALUE_1399);
    *P_LVALUE_1399 = PrtCloneValue((&P_EVENT_TickEvent.value));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp0_83), PTMP_tmp1_71, 0);
    *(&(PTMP_tmp1_71)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_90;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_90;
    }
    
p_return_90: ;
    PrtFreeValue(PTMP_tmp0_83); PTMP_tmp0_83 = NULL;
    PrtFreeValue(PTMP_tmp1_71); PTMP_tmp1_71 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_60 =
{
    NULL,
    &P_Anon_IMPL_60,
    NULL
};


PRT_VALUE* P_Anon_IMPL_61(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE** P_VAR_Svrs = argRefs[0];
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE** P_LVALUE_1400 = &(p_this->varValues[0]);
    PrtFreeValue(*P_LVALUE_1400);
    *P_LVALUE_1400 = PrtCloneValue(*P_VAR_Svrs);
    
p_return_91: ;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Anon_61 =
{
    NULL,
    &P_Anon_IMPL_61,
    &P_GEND_TYPE_Sm
};


PRT_VALUE* P_Tick_IMPL(PRT_MACHINEINST* context, PRT_VALUE*** argRefs)
{
    PRT_VALUE* _P_GEN_funval = NULL;
    PRT_VALUE** _P_GEN_funargs[32];
    PRT_MACHINEINST_PRIV* p_this = (PRT_MACHINEINST_PRIV*)context;
    PRT_VALUE* _P_GEN_retval = NULL;
    PRT_VALUE* P_VAR_i_4 = PrtMkDefaultValue(&P_GEND_TYPE_i);
    PRT_VALUE* PTMP_tmp0_84 = NULL;
    PRT_VALUE* PTMP_tmp1_72 = NULL;
    PRT_VALUE* PTMP_tmp2_63 = NULL;
    PRT_VALUE* PTMP_tmp3_58 = NULL;
    PRT_VALUE* PTMP_tmp4_50 = NULL;
    PRT_VALUE* PTMP_tmp5_39 = NULL;
    PRT_VALUE* PTMP_tmp6_37 = NULL;
    PRT_VALUE* PTMP_tmp7_30 = NULL;
    PRT_VALUE* PTMP_tmp8_27 = NULL;
    
    PRT_VALUE _P_GEN_null = { PRT_VALUE_KIND_NULL, { .ev = PRT_SPECIAL_EVENT_NULL } };
    PRT_VALUE P_LIT_INT32_78 = { PRT_VALUE_KIND_INT, { .nt = 1 } };
    PRT_VALUE P_LIT_BOOLEAN_37 = { PRT_VALUE_KIND_BOOL, { .bl = PRT_TRUE } };
    while (PrtPrimGetBool((&P_LIT_BOOLEAN_37)))
    {
        PRT_VALUE** P_LVALUE_1401 = &(PTMP_tmp0_84);
        PrtFreeValue(*P_LVALUE_1401);
        *P_LVALUE_1401 = PrtMkIntValue(PrtSeqSizeOf(p_this->varValues[0]));
        
        PRT_VALUE** P_LVALUE_1402 = &(PTMP_tmp1_72);
        PrtFreeValue(*P_LVALUE_1402);
        *P_LVALUE_1402 = PrtMkBoolValue(PrtPrimGetInt(P_VAR_i_4) < PrtPrimGetInt(PTMP_tmp0_84));
        
        PRT_VALUE** P_LVALUE_1403 = &(PTMP_tmp2_63);
        PrtFreeValue(*P_LVALUE_1403);
        *P_LVALUE_1403 = PrtCloneValue(PTMP_tmp1_72);
        
        if (PrtPrimGetBool(PTMP_tmp2_63))
        {
        }
        
        else
        {
            break;
            
        }
        
        
        PRT_VALUE** P_LVALUE_1404 = &(PTMP_tmp3_58);
        PrtFreeValue(*P_LVALUE_1404);
        *P_LVALUE_1404 = PrtSeqGet(p_this->varValues[0], P_VAR_i_4);
        
        PRT_VALUE** P_LVALUE_1405 = &(PTMP_tmp4_50);
        PrtFreeValue(*P_LVALUE_1405);
        *P_LVALUE_1405 = PrtCloneValue(PTMP_tmp3_58);
        
        PRT_VALUE** P_LVALUE_1406 = &(PTMP_tmp5_39);
        PrtFreeValue(*P_LVALUE_1406);
        *P_LVALUE_1406 = PrtCloneValue((&P_EVENT_TickEvent.value));
        
        PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp4_50), PTMP_tmp5_39, 0);
        *(&(PTMP_tmp5_39)) = NULL;
        if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
            goto p_return_92;
        }
        if (p_this->isHalted == PRT_TRUE) {
            PrtFreeValue(_P_GEN_retval);
            _P_GEN_retval = NULL;
            goto p_return_92;
        }
        
        PRT_VALUE** P_LVALUE_1407 = &(PTMP_tmp6_37);
        PrtFreeValue(*P_LVALUE_1407);
        *P_LVALUE_1407 = PrtMkIntValue(PrtPrimGetInt(P_VAR_i_4) + PrtPrimGetInt((&P_LIT_INT32_78)));
        
        {
            PRT_VALUE** P_LVALUE_1408 = &(P_VAR_i_4);
            PrtFreeValue(*P_LVALUE_1408);
            *P_LVALUE_1408 = PTMP_tmp6_37;
            PTMP_tmp6_37 = NULL;
        }
        
    }
    
    
    PRT_VALUE** P_LVALUE_1409 = &(PTMP_tmp7_30);
    PrtFreeValue(*P_LVALUE_1409);
    *P_LVALUE_1409 = PrtCloneValue(p_this->varValues[1]);
    
    PRT_VALUE** P_LVALUE_1410 = &(PTMP_tmp8_27);
    PrtFreeValue(*P_LVALUE_1410);
    *P_LVALUE_1410 = PrtCloneValue((&P_EVENT_SentAllTicks.value));
    
    PrtSendInternal(context, PrtGetMachine(context->process, PTMP_tmp7_30), PTMP_tmp8_27, 0);
    *(&(PTMP_tmp8_27)) = NULL;
    if (p_this->returnKind != ReturnStatement && p_this->returnKind != ReceiveStatement) {
        goto p_return_92;
    }
    if (p_this->isHalted == PRT_TRUE) {
        PrtFreeValue(_P_GEN_retval);
        _P_GEN_retval = NULL;
        goto p_return_92;
    }
    
p_return_92: ;
    PrtFreeValue(P_VAR_i_4); P_VAR_i_4 = NULL;
    PrtFreeValue(PTMP_tmp0_84); PTMP_tmp0_84 = NULL;
    PrtFreeValue(PTMP_tmp1_72); PTMP_tmp1_72 = NULL;
    PrtFreeValue(PTMP_tmp2_63); PTMP_tmp2_63 = NULL;
    PrtFreeValue(PTMP_tmp3_58); PTMP_tmp3_58 = NULL;
    PrtFreeValue(PTMP_tmp4_50); PTMP_tmp4_50 = NULL;
    PrtFreeValue(PTMP_tmp5_39); PTMP_tmp5_39 = NULL;
    PrtFreeValue(PTMP_tmp6_37); PTMP_tmp6_37 = NULL;
    PrtFreeValue(PTMP_tmp7_30); PTMP_tmp7_30 = NULL;
    PrtFreeValue(PTMP_tmp8_27); PTMP_tmp8_27 = NULL;
    return _P_GEN_retval;
}

PRT_FUNDECL P_FUNCTION_Tick =
{
    "Tick",
    &P_Tick_IMPL,
    NULL
};


PRT_FUNDECL* P_WallclockTimer_METHODS[] = { &P_FUNCTION_Anon_59, &P_FUNCTION_Anon_60, &P_FUNCTION_Anon_61, &P_FUNCTION_Tick };

PRT_EVENTDECL* P_WallclockTimer_RECV_INNER_1[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_WallclockTimer_RECV_1 =
{
    34U,
    P_WallclockTimer_RECV_INNER_1,
    NULL
};

PRT_EVENTDECL* P_WallclockTimer_SEND_INNER[] = { &P_EVENT_AddServer, &P_EVENT_AddServerResponse, &P_EVENT_AppendEntriesRequest, &P_EVENT_AppendEntriesResponse, &P_EVENT_BecomeCandidate, &P_EVENT_BecomeFollower, &P_EVENT_BecomeLeader, &P_EVENT_CConfigureEvent, &P_EVENT_CancelTimer, &P_EVENT_CheckLogsOnShutDown, &P_EVENT_ConfigureWallclock, &P_EVENT_EMonitorInit, &P_EVENT_InjectFailure, &P_EVENT_LocalEvent, &P_EVENT_M_LeaderCommitted, &P_EVENT_M_LogAppend, &P_EVENT_M_NotifyLeaderElected, &P_EVENT_MakeUnavailable, &P_EVENT_NotifyLeaderUpdate, &P_EVENT_RedirectRequest, &P_EVENT_RemoveServer, &P_EVENT_RemoveServerResponse, &P_EVENT_Request, &P_EVENT_Response, &P_EVENT_SConfigureEvent, &P_EVENT_SentAllTicks, &P_EVENT_ShutDown, &P_EVENT_StartTimer, &P_EVENT_TickEvent, &P_EVENT_UpdateServers, &P_EVENT_UpdateServersResponse, &P_EVENT_VoteRequest, &P_EVENT_VoteResponse, &_P_EVENT_HALT_STRUCT };
PRT_EVENTSETDECL P_EVENTSET_WallclockTimer_SEND =
{
    34U,
    P_WallclockTimer_SEND_INNER,
    NULL
};

PRT_MACHINEDECL P_MACHINE_WallclockTimer = 
{
    7U,
    "WallclockTimer",
    &P_EVENTSET_WallclockTimer_RECV_1,
    &P_EVENTSET_WallclockTimer_SEND,
    NULL,
    2U,
    3U,
    4U,
    4294967295U,
    0U,
    P_WallclockTimer_VARS,
    P_WallclockTimer_STATES,
    P_WallclockTimer_METHODS
};

PRT_TYPE* P_TYPEDEF_Log = &P_GEND_TYPE_T3irr;
PRT_TYPE* P_TYPEDEF_Idxs = &P_GEND_TYPE_T2ii;
PRT_TYPE* P_TYPEDEF_Idxs2 = &P_GEND_TYPE_T2ii;
PRT_TYPE* P_TYPEDEF_Idxs3 = &P_GEND_TYPE_T2ii;
PRT_TYPE* P_TYPEDEF_Config = &P_GEND_TYPE_T2iSm;
