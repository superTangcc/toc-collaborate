#include <sys/processor.h>
#include <sys/procset.h>

//int32_t ApplicationToPhysicalMapping[MaxThreads];
int32_t NUMA_Sockets      = -1;
int32_t NUMA_CoresPerNode = -1;
int32_t NUMA_Cores        = -1;

void Affinity_Init(void);
void Affinity_Bind_Memory(uint32_t thread);
void Affinity_Bind_Thread(uint32_t thread);
void Affinity_unBind(void);
