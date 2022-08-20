#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sched.h>
#define childnum 21 

int main(){
	pid_t pids[childnum],pid,wpid;
	int status = 0;
	int processnum=0;
	int input;
	char buffer[20];
	printf("(1) basic CFS , (2) new CFS :");scanf("%d",&input);
	printf("parent process start!\n");

	int temp;
	nice(0);
	while(processnum < childnum){
		pids[processnum] =fork();

		if(pids[processnum]< 0){
			printf("error\n");
			return -1;
		}
		else if( pids[processnum] == 0){
			if(processnum <7){
				if(input==2)
					nice(-19);
				printf("[hard work] start %d ( %d )\n",getpid(),getpriority(PRIO_PROCESS,0));
				sprintf(buffer,"chrt -p %d",getpid());
				system(buffer);
				for(int i=0;i<100000;i++){
					for(int j=0;j<100000;j++){
						temp = i * j;
					}
				}
				printf("[hard work] end %d ( %d )\n",getpid(),getpriority(PRIO_PROCESS,0));
				return 0;
	                }

			else if(processnum >=7 && processnum <14){
				if(input ==2)
					nice(0);
				printf("[normal work] start %d ( %d )\n",getpid(),getpriority(PRIO_PROCESS,0));                               
				for(int i=0;i<100000;i++){
                                        for(int j=0;j<10000;j++){
                                                temp = i * j;
                                        }
                                }
                                printf("[normal work] end %d ( %d )\n",getpid(),getpriority(PRIO_PROCESS,0));
                                return 0;			
			}
			else{
				if(input ==2)
					nice(19);
				printf("[small work] start %d ( %d )\n",getpid(),getpriority(PRIO_PROCESS,0));                                
				for(int i=0;i<10000;i++){
                                        for(int j=0;j<10000;j++){
                                                temp = i * j;
                                        }
                                }
                                printf("[small work] end %d ( %d )\n", getpid(),getpriority(PRIO_PROCESS,0));
                                return 0;
			}
		}
		else{
			processnum++;
		}
	}
	while((wpid = wait(&status))>0);
	printf("parent process ends\n");
	return 0;

}
		
		
		
