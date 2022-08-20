#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

int start_list[15];
int waiting[4];

int passed;
int passed_count;


int tick;

int size;
int flag;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond4 = PTHREAD_COND_INITIALIZER;

void create_ran_num(int n){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        start_list[i] = rand()%4+1;
    }
}

void print_list(void){
    printf("Start point : ");
    for(int i=0;i<15;i++){
        if(start_list[i] == 0){
	    size = i;
            break;
	}
        printf("%3d",start_list[i]);
    }
    printf("\n");
}

void print_format(void){
	printf("tick : %d\n",tick+1);
	printf("---------------------------------------\n");
	printf("Passed Vehicle\n");
	printf("Car : ");
	if(passed != 0)
		printf("%d\n:",passed);
	else
		printf("\n");
	printf("Waiting Vehicle\n");
	printf("Car : ");
	for(int i = 0; i < 4;i++){
		if(waiting[i] != 0){
			for(int j= 0;j<waiting[i];j++){
				printf("%3d",i+1);
			}
		}
	}
	printf("\n---------------------------------------\n");
}
void *t_function1(void *data){
	srand(time(NULL));
	while(1){
		//printf("passed_count = %d size =%d\n",passed_count,size);
		pthread_mutex_lock(&mutex1);
		pthread_cond_wait(&cond1,&mutex1);
		if(flag == 1 ){
			pthread_exit(NULL);
		}
loop:		print_format();
		/*if(isemptywaiting && passed ==0 && tick!=0){
			flag =1;
			pthread_cond_signal(&cond2);
			pthread_cond_signal(&cond3);
			pthread_cond_signal(&cond4);
			pthread_exit(NULL);
		}*/
		sleep(1);
		tick++;
		passed = 1;
		passed_count++;
		if(passed_count == size){
			flag =1;
			print_format();
			tick++;
			passed = 0;
			print_format();
			pthread_cond_signal(&cond2);
			pthread_cond_signal(&cond3);
			pthread_cond_signal(&cond4);
			pthread_exit(NULL);
		}

		if(tick < size )
			waiting[start_list[tick]-1]++;
		if(waiting[2] !=0){
			//waiting[start_list[tick]-1]++;
			waiting[2]--;
			pthread_cond_signal(&cond3);
		}
		else{

			int temp;
			while(waiting[(temp = rand()%4)] == 0);
			print_format();
			passed = 0;
			sleep(1);
			tick++;
			if(tick<size){
				waiting[start_list[tick]-1]++;
			}
			waiting[temp]--;
			if(temp ==  0 ){
				goto loop;
			}
			else if(temp == 1){
				pthread_cond_signal(&cond2);
			}
			else if(temp == 2){
				pthread_cond_signal(&cond3);
			}
			else if(temp == 3){
				pthread_cond_signal(&cond4);
			}	
			
		}
		pthread_mutex_unlock(&mutex1);

	}
}


void *t_function2(void *data){
        srand(time(NULL));
        while(1){
                pthread_mutex_lock(&mutex2);
                pthread_cond_wait(&cond2,&mutex2);
		if(flag ==1)
			pthread_exit(NULL);

loop:           print_format();
		sleep(1);
                tick++;
                passed = 2;
		passed_count++;
		if(passed_count == size){
                        flag =1;
			print_format();
			tick++;
			passed= 0;
			print_format();
                        pthread_cond_signal(&cond1);
                        pthread_cond_signal(&cond3);
                        pthread_cond_signal(&cond4);
                        pthread_exit(NULL);
                }
		if(tick < size)
                	waiting[start_list[tick]-1]++;
                if(waiting[3] !=0){
                        //waiting[start_list[tick]-1]++;
                        waiting[3]--;
                        pthread_cond_signal(&cond4);
                }
                else{
                        int temp;
                        while(waiting[(temp = rand()%4)] == 0);
                        print_format();
			passed = 0;
                        sleep(1);
			tick++;
                        if(tick<size)	
				waiting[start_list[tick]-1]++;
                        waiting[temp]--;
                        if(temp ==  1 ){
                                goto loop;
                        }
                        else if(temp == 0){
                                pthread_cond_signal(&cond1);
                        }
                        else if(temp == 2){
                                pthread_cond_signal(&cond3);
                        }
                        else if(temp == 3){
                                pthread_cond_signal(&cond4);
                        }
                }
		pthread_mutex_unlock(&mutex2);
        }
}

void *t_function3(void *data){
        srand(time(NULL));
        while(1){
                pthread_mutex_lock(&mutex3);
                pthread_cond_wait(&cond3,&mutex3);
		if(flag == 1)
			pthread_exit(NULL);
loop:           print_format();
		sleep(1);
                tick++;
                passed = 3;
		/*
		if(isemptywaiting && passed == 0  && tick !=0){
			flag= 1;
			pthread_cond_signal(&cond1);
			pthread_cond_signal(&cond2);
			pthread_cond_signal(&cond4);
			pthread_exit(NULL);
		}*/

		passed_count++;
		if(passed_count == size){
                        flag =1;
                        print_format();
			tick++;
			passed =0;
			print_format();
			pthread_cond_signal(&cond1);
                        pthread_cond_signal(&cond2);
                        pthread_cond_signal(&cond4);
                        pthread_exit(NULL);
                }
		
		if(tick<size)
                	waiting[start_list[tick]-1]++;
                if(waiting[0] !=0){
                        //waiting[start_list[tick]-1]++;
                        waiting[0]--;
                        pthread_cond_signal(&cond1);
                }
                else{
                        int temp;
                        while(waiting[(temp = rand()%4)] == 0);
                        print_format();

                        passed = 0;
			
			sleep(1);
			tick++;
			if(tick<size)
                        	waiting[start_list[tick]-1]++;
                        waiting[temp]--;
                        if(temp ==  2 ){
                                goto loop;
                        }
                        else if(temp == 0){
                                pthread_cond_signal(&cond1);
                        }
                        else if(temp == 1){
                                pthread_cond_signal(&cond2);
                        }
                        else if(temp == 3){
                                pthread_cond_signal(&cond4);
                        }
		}
                pthread_mutex_unlock(&mutex3);
                

        }
}


void *t_function4(void *data){
        srand(time(NULL));
        while(1){
                pthread_mutex_lock(&mutex4);
                pthread_cond_wait(&cond4,&mutex4);
		if(flag == 1)
			pthread_exit(NULL);
loop:           print_format();
		/*if(isemptywaiting && passed == 0 && tick !=0){
			flag =1;
			pthread_cond_signal(&cond1);
			pthread_cond_signal(&cond2);
			pthread_cond_signal(&cond3);
		}*/
		passed_count++;
		if(passed_count == size){
                        flag =1; 
			print_format();
			tick++;
			passed =0;
			print_format();
                        pthread_cond_signal(&cond1);
                        pthread_cond_signal(&cond2);
                        pthread_cond_signal(&cond3);
                        pthread_exit(NULL);
                }
		sleep(1);
                tick++;
                passed = 4;
		if(tick<size)
                	waiting[start_list[tick]-1]++;
                if(waiting[1] !=0){
                        //waiting[start_list[tick]-1]++;
                        waiting[1]--;
                        pthread_cond_signal(&cond2);
                }
                else{
                        int temp;
                        while(waiting[(temp = rand()%4)] == 0);
                        print_format();
			passed = 0;
			sleep(1);
			tick++;
                        if(tick<size)
				waiting[start_list[tick]-1]++;
                        waiting[temp]--;
                        if(temp ==  3 ){
                                goto loop;
                        }
                        else if(temp == 0){
                                pthread_cond_signal(&cond1);
                        }
                        else if(temp == 1){
                                pthread_cond_signal(&cond2);
                        }
                        else if(temp == 2){
                                pthread_cond_signal(&cond3);
                        }
		}
		pthread_mutex_unlock(&mutex4);
          }
}



int main(){
    int input_num;
    printf("total number of vehicles : ");
    scanf("%d",&input_num);
    create_ran_num(input_num);
    print_list();

    pthread_t p_thread[4];
    int thr_id;
    int status;

    char p1[] = "p1";
    char p2[] = "p2";
    char p3[] = "p3";
    char p4[] = "p4";

    thr_id = pthread_create(&p_thread[0],NULL,t_function1,(void *)p1);

    if(thr_id <0){
        perror("thread create error \n");
        exit(0);
    }

    thr_id = pthread_create(&p_thread[1],NULL,t_function2,(void *)p2);
    if(thr_id<0){
        perror("thread create error\n");
        exit(0);
    }

    thr_id = pthread_create(&p_thread[2],NULL,t_function3,(void *)p3);
    if(thr_id<0){
        perror("thread create error\n");
        exit(0);
    }

    thr_id = pthread_create(&p_thread[3],NULL,t_function4,(void *)p4);
    if(thr_id<0){
        perror("thread create error\n");
        exit(0);
    }

    sleep(1);


    if(start_list[tick] == 1){
	    pthread_cond_signal(&cond1);
    }
    else if(start_list[tick] == 2){
	    pthread_cond_signal(&cond2);
    }
    else if(start_list[tick] == 3){
	    pthread_cond_signal(&cond3);
    }
    else if(start_list[tick] == 4){
	    pthread_cond_signal(&cond4);
    }

    pthread_join(p_thread[0],(void **)&status);
    pthread_join(p_thread[1],(void **)&status);
    pthread_join(p_thread[2],(void **)&status);
    pthread_join(p_thread[3],(void **)&status);

    return 0;
}

