
#include "res.h"
int test(){
	return 1;
}
int getinput(char *s,char str[15]){
	printf("%s\n",s);
	if(strcmp(s,"init")==0){
		//printf("yes\n");
		initpcb();
	}
	if(strcmp(s,"quit")==0){
		exit(0);
	}
	
}
int shell(){
	char *s;
	char str[15];
	s =str;
	printf("vic>$ ");
	scanf("%s",str);
	//test();
	getinput(s,str);
	//printf("%s",s);
	return 1;
}
int main(){
	//initpcb();
	//initrcb();
	/*rl_1 = initque();
	bl_1 = initque();
	createpcb(1001,1);
	createpcb(1002,1);
	createpcb(1003,1);
	createpcb(1004,1);
	//printque(rl_1);
	to();
	
	request("r2",1);
	to();
	request("r3",3);
	to();
	request("r4",3);
	
	to();
	to();
	request("r3",1);
	request("r4",2);
	request("r2",2);
	
	to();
	de(1003);
	to();
	to();*/
	while(true){	shell();continue;}
	//createpcb(1001,1);	
	
	
}
