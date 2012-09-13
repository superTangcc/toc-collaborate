void Affinity_Init(){ 
    //  printf("implementing Affinity via <sched.h>\n");fflush(stdout);

  FILE *fp;
  fp = fopen("/proc/cpuinfo","r");
  if(fp!=NULL){
      //    printf("  using /proc/cpuinfo to reconstruct [Socket][Core][Thread] mapping.\n");fflush(stdout);

    char WorkingLine[1000];
    int LinuxProcessor=-1,socket=-1,core=-1,thread=-1,ThreadsPerCore=0,ThreadsPerSocket=0;
    int FirstSocket = 1024;
    int FirstCore   = 1024;
    while(!feof(fp)){
      fgets(WorkingLine,1000,fp);
      char* str_core      = strstr(WorkingLine,"core id");
      char* str_socket    = strstr(WorkingLine,"physical id");
      char* str_colon     = strstr(WorkingLine,":");
      if(str_socket   !=NULL){sscanf(str_colon+2,"%d",&socket);if(socket<FirstSocket)FirstSocket=socket;}
      if(str_core     !=NULL){sscanf(str_colon+2,"%d",&core);  if(core  <FirstCore  )FirstCore  =core;  }
    }
    if(FirstSocket)printf("  Sockets not 0-relative.  FirstSocket=%d\n",FirstSocket);
    if(FirstCore  )printf("  Core not 0-relative.  FirstCore=%d\n",FirstCore);
    fclose(fp);
    fp = fopen("/proc/cpuinfo","r");
    while(!feof(fp)){
      fgets(WorkingLine,1000,fp);
      char* str_processor = strstr(WorkingLine,"processor");
      char* str_core      = strstr(WorkingLine,"core id");
      char* str_socket    = strstr(WorkingLine,"physical id");
      char* str_colon     = strstr(WorkingLine,":");
      if(str_processor!=NULL){sscanf(str_colon+2,"%d",&LinuxProcessor);}
      if(str_socket   !=NULL){sscanf(str_colon+2,"%d",&socket);socket-=FirstSocket;socket_id_of_LinuxProcessor[LinuxProcessor]=socket;}
      if(str_core     !=NULL){sscanf(str_colon+2,"%d",&core);    core-=FirstCore;    core_id_of_LinuxProcessor[LinuxProcessor]=  core;
                              //printf("%2d -> [%d][%d][%d]\n",LinuxProcessor,socket,core,ThreadsPerCore);fflush(stdout);
                              if((socket==0)&&(core==0))ThreadsPerCore++;
                              if((socket==0)           )ThreadsPerSocket++;
                             }
    }
    fclose(fp);
    int SocketsPerSMP = socket+1;
    int CoresPerSocket = ThreadsPerSocket/ThreadsPerCore;
    //    if(ThreadsPerCore==1)printf("  found %d sockets each with %d cores\n"                     ,SocketsPerSMP,CoresPerSocket               );else
    //                         printf("  found %d sockets each with %d cores each with %d threads\n",SocketsPerSMP,CoresPerSocket,ThreadsPerCore);
    int rank=0;
    for(socket=0;socket< SocketsPerSMP;socket++)
    for(  core=0;  core<CoresPerSocket;  core++)
    for(thread=0;thread<ThreadsPerCore;thread++){
      int i,c=0;
      for(i=0;i<=LinuxProcessor;i++){
        if( (socket_id_of_LinuxProcessor[i]==socket) && (  core_id_of_LinuxProcessor[i]==  core) ){
          if(c==thread){
	    LinuxProcessor_of_rank[rank]=i;
	    //	    printf("  rank %3d -> linux %3d (socket%d,core%d)\n",rank,i,socket_id_of_LinuxProcessor[i],core_id_of_LinuxProcessor[i]);fflush(stdout);
	  }c++;
        }
      }
      rank++;
    }
    CPU_ZERO(&OriginalMask);
    sched_getaffinity(0, sizeof(OriginalMask), &OriginalMask);
    _Affinity_ThreadContexts = SocketsPerSMP*CoresPerSocket*ThreadsPerCore;
  }else{
    printf("  failed to open /proc/cpuinfo. Assuming [Socket][Core][Thread] mapping.\n");fflush(stdout);
    CPU_ZERO(&OriginalMask);
    sched_getaffinity(0, sizeof(OriginalMask), &OriginalMask);
    uint32_t i;
    for(i=0;i<1024;i++)if(CPU_ISSET(i,&OriginalMask)){
      if(_Affinity_ThreadContexts<0)_Affinity_ThreadContexts=0;_Affinity_ThreadContexts++;
    }
    printf("  found %d HW Thread Contexts\n",_Affinity_ThreadContexts);fflush(stdout);
    int rank=0;
    for(rank=0;rank<1024;rank++)LinuxProcessor_of_rank[rank]=rank;
    if(_Affinity_ThreadContexts <= 0)exit(0);
    return;
  }
}

void Affinity_Bind_Thread(uint32_t thread){
  uint32_t thread2=LinuxProcessor_of_rank[thread%_Affinity_ThreadContexts];
  //printf("Affinity: thread %3d is mapped to linux processor %3d\n",thread,thread2);
  cpu_set_t NewMask;
  CPU_ZERO(&NewMask);
  CPU_SET(thread2,&NewMask);
  if(sched_setaffinity(0, sizeof(NewMask), &NewMask)<0){
    printf("Affinity: Couldn't bind thread=%u to ThreadContext=%u\n",thread,thread2);
    exit(0);
  }
  sched_getaffinity(0, sizeof(NewMask), &NewMask);
  return;
}

void Affinity_Bind_Memory(uint32_t thread){
  Affinity_Bind_Thread(thread);
  return;
}

void Affinity_unBind(){
  cpu_set_t NewMask;
  CPU_ZERO(&NewMask);
  if(sched_setaffinity(0, sizeof(OriginalMask), &OriginalMask)<0){
    printf("Affinity: Couldn't unbind threads\n");exit(0);
  }
  sched_getaffinity(0, sizeof(NewMask), &NewMask);
  return;
}
