#include "pcb.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct RCB{
	char *rid;
	int status;//空闲单元数量
	rl waitlist;//被阻塞的进程
};
struct RCB r[]={{"r1",1,NULL},{"r2",2,NULL},{"r3",3,NULL},{"r4",4,NULL}};

int getr(char *rid){
	if(rid == "r1"){return 5;}
	else if(rid == "r2"){return 6;}
	else if(rid == "r3"){return 7;}
	else if(rid == "r4"){return 8;}
}
void request(char *rid,int n){
	//申请资源
	int tmp = getr(rid)-5;
	if(n <= r[tmp].status){
		in(&r[tmp].waitlist,currentp->pid);//只要申请该资源，就加到waitlist里
		r[tmp].status -= n;
		printf("process %d requests %d %s\n",currentp->pid,n,rid);
		currentp->resource = rid;
		currentp->re_num = n;
	}else{//如果申请资源小于自由资源，加入waitlist队列调度下一个进程
		in(&r[tmp].waitlist,currentp->pid);
		in(&bl_1,currentp->pid);
		printf("%d is blocked, ",currentp->pid);
		schedular();
	}
	//printf("%d\n",r[tmp].status);
}

int release(char *rid,int n){
	//释放资源，把该进程加入就绪队列，从阻塞队列中删除，并激活waitlist里的进程
	int y=0;
	r[getr(rid)-5].status += getp(r[getr(rid)-5].waitlist.head->pid)->re_num;
	out(&r[getr(rid)-5].waitlist,&y);
	printf("wake up process %d\n",r[getr(rid)-5].waitlist.head->pid);
	//此处作弊
	pque tmp = rl_1.head;
	rl_1.head = r[getr(rid)-5].waitlist.head;
	rl_1.head->next = tmp;
}
int de(int pid){//删除进程
	int n;
	char *m=getp(pid)->resource;
	release(m,n);
}
int printres(char* rid){
	int tmp = getr(rid)-5;
	printf("%s: %d\n",rid,r[tmp].status);
}
int printbl(char *rid){
	//打印阻塞队列，不打印头节点
	int tmp = getr(rid)-5;
	rl que=r[tmp].waitlist;
	if(que.head==NULL || que.tail==NULL){
		return 0;
	}
	while(que.head!=NULL&&que.head->next!=NULL){
		printf("%s:%d\n",rid,que.head->next->pid);
		que.head=que.head->next;
	}
}
