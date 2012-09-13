#include<string.h>
#include<sched.h>

cpu_set_t OriginalMask;
 int32_t _Affinity_ThreadContexts    = -1;
 int32_t socket_id_of_LinuxProcessor[1024];
 int32_t   core_id_of_LinuxProcessor[1024];
 int32_t      LinuxProcessor_of_rank[1024];

void Affinity_Init(void);
void Affinity_Bind_Thread(uint32_t thread);
void Affinity_Bind_Memory(uint32_t thread);
void Affinity_unBind(void);
