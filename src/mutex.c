#include <windows.h>
#include <stdint.h>
#include <malloc.h>
#include <stdio.h>

#include "..\inc\mutex.h"

int SpinLock_TryLock(spinlock_t *lock)
{
	if (InterlockedExchange((volatile LONG*)lock, 1) == 1)
		return MUTEX_TIMEOUT;
	else
		return MUTEX_ACQUIRED;
}
void SpinLock_Lock(spinlock_t *lock)
{
	while (InterlockedExchange((volatile LONG*)lock, 1) == 1)
	{
	}
}
int SpinLock_LockTimeOut(spinlock_t *lock, uint32_t timeout_ms)
{
	uint64_t start;
	uint64_t current;
	uint64_t freq;
	uint64_t timeout_adj;

	if (timeout_ms == INFINITE)
	{
		SpinLock_Lock(lock);
		return MUTEX_ACQUIRED;
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&start);
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

	timeout_adj = (timeout_ms * freq) / 1000;

	while (InterlockedExchange((volatile LONG*)lock, 1) == 1)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&current);

		if ((current - start) > timeout_adj)
			return MUTEX_TIMEOUT;
	}
	return MUTEX_ACQUIRED;
}
void SpinLock_Unlock(spinlock_t *lock)
{
	InterlockedExchange((volatile LONG*)lock, 0);
}

void Mutex_Init(mutex_t *mutex)
{
	InitializeSRWLock(mutex);
}
void Mutex_Lock(mutex_t *mutex)
{
	AcquireSRWLockExclusive(mutex);
}
void Mutex_Unlock(mutex_t *mutex)
{
	ReleaseSRWLockExclusive(mutex);
}
void Mutex_Delete(mutex_t *mutex)
{
}
