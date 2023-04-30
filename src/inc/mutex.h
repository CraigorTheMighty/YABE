typedef volatile int32_t spinlock_t;
typedef SRWLOCK mutex_t;

#define SPINLOCK_INIT	0

#define MUTEX_TIMEOUT				0
#define MUTEX_ACQUIRED				1	
#define MUTEX_ACQUIRED_ABANDONED	2	// mutex acquired, but previous holding thread/process terminated while holding the mutex	

// spinlocks that are locked can be released by ANY thread
int		SpinLock_TryLock(spinlock_t *lock);
int		SpinLock_LockTimeOut(spinlock_t *lock, uint32_t timeout_ms);
void	SpinLock_Lock(spinlock_t *lock);
void	SpinLock_Unlock(spinlock_t *lock);

// mutexes that are locked can be released by ANY thread
void	Mutex_Init(mutex_t *mutex);
int		Mutex_TryLock(mutex_t *mutex);
void	Mutex_Lock(mutex_t *mutex);
void	Mutex_Unlock(mutex_t *mutex);
void	Mutex_Delete(mutex_t *mutex);
