/**
 * @file svc.h
 * @brief Syscall wrappers.
 */
#pragma once

#include "types.h"

/// Pseudo handle for the current process
#define CUR_PROCESS_HANDLE 0xFFFF8001

/// Pseudo handle for the current thread
#define CUR_THREAD_HANDLE 0xFFFF8000

static inline void* armGetTls(void) {
    void* ret;
    __asm__ ("mrs %x[data], tpidrro_el0" : [data] "=r" (ret));
    return ret;
}

Result svcQueryMemory(u32 *meminfo_ptr, u32 *pageinfo, u64 addr);
Result svcCloseHandle(Handle handle);
Result svcCreateTransferMemory(Handle* out, void* addr, size_t size, u32 perm);
Result svcWaitSynchronization(s32* index, const Handle* handles, s32 handleCount, u64 timeout);
Result svcConnectToNamedPort(Handle* session, const char* name);
Result svcSendSyncRequest(Handle session);
Result svcBreak(u32 breakReason, u64 inval1, u64 inval2);
Result svcAcceptSession(Handle *session_handle, Handle port_handle);
Result svcReplyAndReceive(s32* index, const Handle* handles, s32 handleCount, Handle replyTarget, u64 timeout);
Result svcQueryPhysicalAddress(u64 out[3], u64 virtaddr);
Result svcQueryIoMapping(u64* virtaddr, u64 physaddr, u64 size);
Result svcManageNamedPort(Handle* portServer, const char* name, s32 maxSessions);