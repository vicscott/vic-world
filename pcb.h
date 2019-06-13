#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
enum state_type {
	ready,
	running,
	blcok
};

//队列
typedef struct pidNode {
	int pid;
	struct pidNode *next; 
}pidNode,*pque;

typedef struct readylist {
	pque head;
	pque tail;
}rl;
rl rl_1;
rl bl_1;

typedef struct pcb{
	unsigned int pid; //进程号
	enum state_type state; //进程状态
	unsigned int parent; //父进程
	unsigned int child;
	unsigned int priority; //优先级
	unsigned int time; //轮转的时间
	char *resource;
	int re_num;

}pcb_s;
typedef pcb_s * pcb_p;
pcb_p setup[511];//注册表，最多512个进程

pcb_p currentp;
//------------------------------------------------------------------------------------
int i=0;
rl initque(){/*初始空队列*/
	rl *que = (rl*)malloc(sizeof(rl));
	if(NULL ==que){return *que;}
	que->head=que->tail = NULL;
	return *que;
}
void in(rl *que, int p){/*入队*/
	pidNode *q = (pidNode*)malloc(sizeof(pidNode));
	q->pid = p;
	q->next = NULL;
	if(que->tail==NULL){
		que->head=que->tail=q;
	}else{
		que->tail->next=q;
		que->tail=q;
	}
}
int out(rl *que,int *y){/*出队*/
	pidNode *q = que->head;
	if(que->tail==NULL || que->head==NULL){
		return false;
	}
	if(que->head==que->tail){
		que->head=que->tail=NULL;
	}else{
		que->head=que->head->next;
	}
	*y = q->pid;
	free(q);
	return true;
}
int del(rl *que, int y){//删除元素
	pque p,first;
	first = que->head;
	if(y!=0){
		while(!(que->head->pid == y)){
			p = que->head;
			que->head = que->head->next;
		}
		p->next=que->head->next;
		que->head = first;
	}else{
		;
	}
	
}

pcb_p getp(int p){
	//根据pid获得其pcb
	for(int i=0;i<512;i++){
		if(setup[i]->pid == p){
			return setup[i];
		}
	}
}
void printque(rl que){
	//打印队列
	if(que.head==NULL || que.tail==NULL){
		return;
	}
	int m2[10];int m1[10];int m0[10];
	int n2=0;int n1=0;int n0=0;
	while(que.head!=NULL){
		if(getp(que.head->pid)->priority==2) {m2[n2]=que.head->pid;++n2;}
		if(getp(que.head->pid)->priority==1) {m1[n1]=que.head->pid;++n1;}
		if(getp(que.head->pid)->priority==0) {m0[n0]=que.head->pid;++n0;}
		que.head=que.head->next;
	}
	printf("2:");for(int z=0;z<n2;z++) printf("%d-",m2[z]);printf("\n");
	printf("1:");for(int z=0;z<n1;z++) printf("%d-",m1[z]);printf("\n");
	printf("0:");for(int z=0;z<n0;z++) printf("%d-",m0[z]);printf("\n");
}

int sort(pcb_p p,rl *que){
	//按优先级进行插入排序
	rl fuzhu=initque();//辅助队列
	pque tmp;
	int j(){
		int y=0;
		if(p->priority>getp(que->head->next->pid)->priority || que->head->next==NULL){
			in(&fuzhu,que->head->pid);
			out(que,&y);
			in(&fuzhu,p->pid);
			if(que->head != NULL){
				in(&fuzhu,que->head->pid);
				que->head = que->head->next;
			}
			
			*que = fuzhu;
			return 1;
		}else{
			in(&fuzhu,que->head->pid);
			que->head = que->head->next;
			return j();
		}
	}
	if(p->pid != 0 ){
		if(p->priority>getp(que->head->pid)->priority){
			in(&fuzhu,p->pid);
			if(que->head != NULL){
				in(&fuzhu,que->head->pid);
				que->head = que->head->next;
			}
			*que = fuzhu;
			return 1;
		}else{
			return j();
		}
	}
	else{
		in(&rl_1,p->pid);
		return 1;
	}
	
}

int initpcb(){/*初始进程*/
	pcb_p PCB = malloc(sizeof(struct pcb));
	if(PCB != NULL){
		PCB->pid = 0;
		PCB->priority =0;
		PCB->state = running;
		currentp = PCB;
	}
	printf("init process is %d\n",PCB->state);
	setup[i] = PCB;
	i++;
}

int createpcb(int newpid, int prio){/*创建进程*/
	pcb_p PCB = malloc(sizeof(struct pcb));
	if(PCB != NULL){
		PCB->pid = newpid;
		PCB->priority = prio;
		if (currentp->priority < prio){
			currentp->state = ready;
			currentp->child = PCB->pid;
			PCB->parent = currentp->pid;
			//把该pcb加入到RL中
			sort(currentp,&rl_1);
			
			PCB->state = running;
			currentp = PCB;
			printf("%d process is %d\n",currentp->pid,currentp->state);
			
		}else{
			//printf("nnnnn%d\n",PCB->pid);
			sort(PCB,&rl_1);
			printf("%d process is %d,%d is ready\n",currentp->pid,currentp->state,PCB->pid);		
		}
	}
	setup[i] = PCB;
	i++;
	return 1;
}

int killtree(int p){
	if(p !=0){
		//初始进程无法被杀死
		for(int w=0;w<510;w++){
			if(p == setup[w]->pid){
				int tmp = setup[w]->child;
				//printf("%d-0000\n",tmp);
				setup[w]=setup[511];//511不赋值
				//删除队列中的对应节点
				del(&rl_1,tmp);
				i--;
				if(tmp!=0){
					return killtree(tmp);
				}else{
					printf("done\n");
					return 1;
				}
			}
		}
	}else{
		printf("init can't be killed\n");
	}
}

int schedular(){
	int y=0;
	out(&rl_1,&y);
	for(int i=0;i<510;i++){
		if(y == setup[i]->pid){
			setup[i]->state = running;
			currentp = setup[i];
			printf("%d is run\n",currentp->pid);
			return 1;
		}		
	}
	
	
}
int destroypcb(){/*撤销当前进程*/
	int oldpid;
	pcb_p p = currentp;
	oldpid = currentp->pid;
	killtree(oldpid);//杀死所有子进程
	schedular();//调度下一个进程
}
int to(){
	//模拟时间片，结束当前进程，调用队列中下一个进程
	currentp->state = ready;
	sort(currentp,&rl_1);
	schedular();
	
}




