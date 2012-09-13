void Affinity_Init(){ 
  uint32_t i;
  //  printf("implementing NUMA via <sys/processor.h>\n");
  //for(i=0;i<MAX_THREADS;i++)ApplicationToPhysicalMapping[i]=0;
  int NUMA_Cores=0;
  for(i=0;i<MAX_THREADS;i++)if(processor_bind(P_LWPID, P_MYID, i, NULL)>=0){
    //ApplicationToPhysicalMapping[NUMA_Cores]=i;
    NUMA_Cores++;
  }
                     NUMA_CoresPerNode = NUMA_Cores;  NUMA_Sockets=1;
  if(NUMA_Cores> 96){NUMA_CoresPerNode = NUMA_Cores/2;NUMA_Sockets=2;}
  if(NUMA_Cores>192){NUMA_CoresPerNode = NUMA_Cores/4;NUMA_Sockets=4;}
  //  printf("Found %d sockets each with %d cores(%d)\n",NUMA_Sockets,NUMA_CoresPerNode,NUMA_Cores);
  processor_bind(P_LWPID, P_MYID, PBIND_NONE, NULL);
  return;
}

void Affinity_Bind_Memory(uint32_t thread){
  //thread = ApplicationToPhysicalMapping[thread];
  if(processor_bind(P_LWPID, P_MYID, thread, NULL)<0){
    printf("Couldn't bind thread %d\n",thread);
  }
  return;
}

void Affinity_Bind_Thread(uint32_t thread){
  //thread = ApplicationToPhysicalMapping[thread];
  if(processor_bind(P_LWPID, P_MYID, thread, NULL)<0){
    printf("Couldn't bind thread %d\n",thread);
  }
  return;
}

void Affinity_unBind(){
  if(processor_bind(P_LWPID, P_MYID, PBIND_NONE, NULL)<0){
    printf("Couldn't unbind thread\n");
    exit(0);
  }
  return;
}
