#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

int prs[50];//input prs array
int prs_size;
int frame_num;
int *frame; // virtual frame array

typedef struct frame_struct{
	int bit;
}frame_st;

int *frame_input_time_arr; // FIFO_with_age  variable
void input_time(int index,int time){ // FIFO_circular_queue func
	frame_input_time_arr[index] = time;
}

void Second_Chance(void){
        memset(frame,0,sizeof(int)*frame_num); //init1
	frame_st *fst;// save ref bit about frame
	fst = (frame_st *)malloc(sizeof(frame_st) * frame_num);
        int page_fault=0;
        int flag =1;
	
	int pointer=0;//pointer for circular queue

        for(int i =0;i<frame_num;i++){
		fst[i].bit = 0;
        }//init

	//------------printing format
        printf("\tframe");
        for(int j =0;j<frame_num;j++){
                printf("\t%d",j+1);
        }printf("\tpage fault\ntime\n");
        //---------------------------
	
	for(int i =0;i<prs_size;i++){
                for(int j=0;j<frame_num;j++){
                        if(prs[i] == frame[j]){//already exist in virtual frame , change ref bit to 1
                                flag =0;
				fst[j].bit = 1;
				//frame_input_time_arr[j] = i;
                                break;
                        }
                }
                if(flag == 0)
                        ;//no page fault;
                else{ //page fault uppers
                        for(int j =0;j<frame_num;j++){
                                if(frame[j] == 0){ // nothing in virtual frame,
                                        frame[j] = prs[i];// just insert prs in virtual frame;
                                        //fst[j]->time = i;
                                        goto jump;
                                }
                        }
			while(1){
				if(fst[pointer].bit == 1 ){ //check if bit is 1;
					fst[pointer].bit =0; // change ref bit
					pointer++; 
					pointer%=(frame_num);//pointer should (0,1,2) if frame_num is 3
				}
				else{
					frame[pointer] = prs[i]; //insert
					pointer++;
					pointer%=(frame_num);
					break;
				}			
			}
		}
jump:
		//------------------printing 1 row
                printf("%3d.\t\t",i+1);
                for(int k=0;k<frame_num;k++){
                        if(frame[k]==0)
                                printf("  \t");
                        else
                                printf("%d\t",frame[k]);
                }
                if(flag==1){
                        page_fault++;
                        printf("F");
                }
                printf("\n");
                //------------------------------------
		flag = 1;
        }
        printf("Number of page faults : %d times\n\n",page_fault);
}

void LRU(void){
        memset(frame,0,sizeof(int)*frame_num);
	memset(frame_input_time_arr,0,sizeof(int)*frame_num);
	int page_fault=0;
        int flag =1;
        int index =0;
        int frame_index=0;;
        int max =0;
        for(int i =0;i<frame_num;i++){
                frame_input_time_arr[i] = 100;
        }
	printf("\tframe");
        for(int j =0;j<frame_num;j++){
                printf("\t%d",j+1);
        }printf("\tpage fault\ntime\n");
        for(int i =0;i<prs_size;i++){
                for(int j=0;j<frame_num;j++){
                        if(prs[i] == frame[j]){
                                flag =0;
				input_time(j,i);
                                break;
                        }
                }
                if(flag == 0)
                	;
		else{
                        for(int j =0;j<frame_num;j++){
                                if(frame[j] == 0){
                                        frame[j] = prs[i];
                                        input_time(j,i);
                                        goto jump;
                                }
                        }
                        for(int j = 0;j<frame_num;j++){
                                if( max< (i-frame_input_time_arr[j])){
                                        max =(i- frame_input_time_arr[j]);
                                        frame_index = j;
                                }

                        }
                        frame[frame_index] = prs[i];
                        input_time(frame_index,i);
                        max=0;
                        frame_index = 0;
                }
jump:
                printf("%3d.\t\t",i+1);
                for(int k=0;k<frame_num;k++){
                        if(frame[k]==0)
                                printf(" \t");
                        else
                                printf("%d\t",frame[k]);
                }
                if(flag==1){
                        
			page_fault++;
                        printf("F");
                }
                printf("\n");
                flag = 1;


        }
        printf("Number of page faults : %d times\n\n",page_fault);
}


void FIFO_circular_queue(void){
	memset(frame,0,sizeof(int)*frame_num);
        memset(frame_input_time_arr,0,sizeof(int)*frame_num);
        int page_fault=0;
        int flag =1;
	int pointer =0;
        printf("\tframe");
        for(int j =0;j<frame_num;j++){
                printf("\t%d",j+1);
        }printf("\tpage fault\ntime\n");
        for(int i =0;i<prs_size;i++){
                for(int j=0;j<frame_num;j++){
                        if(prs[i] == frame[j]){
                                flag =0;
                                break;
                        }
                }
                if(flag == 0)
                        ;//no page fault;
                else{
                        for(int j =0;j<frame_num;j++){
                                if(frame[j] == 0){
                                        frame[j] = prs[i];
                                        goto jump;
                                }
			}
			frame[pointer] = prs[i];
			pointer++;
			pointer%=frame_num;
                }
jump:
                printf("%3d.\t\t",i+1);
                for(int k=0;k<frame_num;k++){
                        if(frame[k]==0)
                                printf(" \t");
                        else
                                printf("%d\t",frame[k]);
                }
                if(flag==1){
                        page_fault++;
                        printf("F");
                }
                printf("\n");
                flag = 1;


        }
        printf("Number of page faults : %d times\n\n",page_fault);
}
void FIFO_with_age(void){
	memset(frame,0,sizeof(int)*frame_num);
        memset(frame_input_time_arr,0,sizeof(int)*frame_num);
        int page_fault=0;
        int flag =1;
        int index =0;
        int frame_index=0;;
        int min =MAX_SIZE;
	for(int i =0;i<frame_num;i++){
		frame_input_time_arr[i] = 100;
	}
	printf("\tframe");
        for(int j =0;j<frame_num;j++){
                printf("\t%d",j+1);
        }printf("\tpage fault\ntime\n");
        for(int i =0;i<prs_size;i++){
                for(int j=0;j<frame_num;j++){
                        if(prs[i] == frame[j]){
                                flag =0;
                                break;
                        }
                }
                if(flag == 0)
                        ;//no page fault;
                else{
                        for(int j =0;j<frame_num;j++){
                                if(frame[j] == 0){ 
                                        frame[j] = prs[i];
					input_time(j,i);
					goto jump;
                                }
                        }
                        for(int j = 0;j<frame_num;j++){
                                if( min>frame_input_time_arr[j]){
                                        min = frame_input_time_arr[j]; 
                                        frame_index = j;
                                }

                        }
                        frame[frame_index] = prs[i];
			input_time(frame_index,i);
                        min=MAX_SIZE;
                        frame_index = 0;
                }
jump:
                printf("%3d.\t\t",i+1);
                for(int k=0;k<frame_num;k++){
                        if(frame[k]==0)
                                printf(" \t");
                        else
                                printf("%d\t",frame[k]);
                }
                if(flag==1){
                        page_fault++;
                        printf("F");
                }
		printf("\n");
                flag = 1;


        }
        printf("Number of page faults : %d times\n\n",page_fault);
}

int count_dist(int index,int dest){ 
	int distance =0;
	for(int i =index;i<prs_size;i++){
		if(prs[i] == dest){
		 	distance= i-index;
			return distance;
		}

	}
	distance = MAX_SIZE;
	return distance;
}

void opt(void){
	memset(frame,0,sizeof(int)*frame_num);
        memset(frame_input_time_arr,0,sizeof(int)*frame_num);
	int page_fault=0;
	int flag =1;
	int temp;
	int index =0;
	int frame_index=0;;
	int max =0;
	printf("\tframe");
	for(int j =0;j<frame_num;j++){
		printf("\t%d",j+1);
	}printf("\tpage fault\ntime\n");
	for(int i =0;i<prs_size;i++){
		for(int j=0;j<frame_num;j++){
			if(prs[i] == frame[j]){
				flag =0;
				break;
			}
		}
		if(flag == 0)
			;//no page fault;
		else{
			for(int j =0;j<frame_num;j++){
				if(frame[j] == 0){
					frame[j] = prs[i];
					goto jump;
				}
			}
			for(int j = 0;j<frame_num;j++){
				if( max<(temp= count_dist(i,frame[j]))){
					max = temp;
					frame_index = j;
				}

			}
			frame[frame_index] = prs[i];
			temp = 0 ;
			max=0;
			frame_index = 0;
		}
jump:
		printf("%3d.\t\t",i+1);
		for(int k=0;k<frame_num;k++){
			if(frame[k]==0)
				printf(" \t");
			else
				printf("%d\t",frame[k]);
		}
		if(flag==1){
			page_fault++;
			printf("F");
		}
		printf("\n");
		flag = 1;

	}
	printf("Number of page faults : %d times\n\n",page_fault);
}



int main(){
	char filename[MAX_SIZE];
	printf("input filename : ");scanf("%s",filename);
	FILE *fp;
	if((fp = fopen(filename,"r"))==NULL){
		printf("file open error\n");
		return -1;
	}
	char buffer[MAX_SIZE];
	fgets(buffer,sizeof(buffer),fp);
	buffer[strlen(buffer)-1] ='\0';
	frame_num = atoi(buffer);
	memset(buffer,0,sizeof(buffer));
	fgets(buffer,sizeof(buffer),fp);
	int index =0;
	for(int i =0;i<strlen(buffer);i+=2){
		prs[index]= buffer[i]-48;
		index++;
	}
	prs_size = index;
	frame = malloc(sizeof(int) *frame_num);
	frame_input_time_arr= malloc(sizeof(int) * frame_num);
		system("clear");
		printf("Used_method : OPT\n");
		printf("page reference string : ");
		for(int j=0;j<index;j++){	
			printf("%3d",prs[j] );
		}
		
		printf("\n\n");
		opt();	
                
		
		printf("Used_method : FIFO_age\n");
                printf("page reference string : ");
                for(int j=0;j<index;j++){
                        printf("%3d",prs[j] );
                }

                printf("\n\n");
                FIFO_with_age();

		printf("Used_method : FIFO_cicular_queue\n");
                printf("page reference string : ");
                for(int j=0;j<index;j++){
                        printf("%3d",prs[j] );
                }

                printf("\n\n");
                FIFO_circular_queue();

	
	
                printf("Used_method : LRU\n");
                printf("page reference string : ");
                for(int j=0;j<index;j++){
                        printf("%3d",prs[j] );
                }

                printf("\n\n");
                LRU();

		printf("Used_method : Second chance\n");
                printf("page reference string : ");
                for(int j=0;j<index;j++){
                        printf("%3d",prs[j] );
                }

                printf("\n\n");
                Second_Chance();


	fclose(fp);
	return 0;
}
		
	

