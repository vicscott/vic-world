#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
#include<pwd.h>
#include<string.h>
#include<wait.h>
#include<sys/types.h>
#include"res.h"
int main()
{
    char* in = "init";
    while(1)
    {
        printf("hi,vic@ ");
        fflush(stdout);
        //读取字符串
        char buf[1024];
        int s = read(0,buf,1024);
        if(s > 0)//有读取到字符
        {
            int i = 0;
            for( i = 0; i < s; ++i)
            {
                if(buf[i] == '\b' && i >= 1)
                {
                //    printf("debug:%d\n",i);
                    int j = 0;
                    for( j = i+1; j < s; ++j)
                    {
                        buf[j-2] = buf[j];
                    }
                    buf[s-2] = 0;
                    i-=1;
                }
                else if(buf[i] == '\b' && i == 0)
                {
                //    printf("debug:%d\n",i);
                    int j = 0;
                    for( j = 1; j < s; ++j)
                    {
                        buf[j-1] = buf[j];
                    }
                    buf[s-1] = 0;
                //    i-=1;
                }
                else
                {
                    continue;
                }
            }
            buf[s] = 0;
        }
        else
        {
            continue;
        }
        //将读取到的字符串分成多个字符串
        char* start = buf;
        int i =1;
        unsigned char* MyArgv[10] = {0};
        MyArgv[0] = start;
        while(*start)
        {
            if(isspace(*start))
            {
                *start = 0;
                start++;
                MyArgv[i++] = start;
            }
            else
            {
                ++start;
            }
        }
        MyArgv[i-1] = NULL;
      
        if(*buf=='q'){
		exit(0);
	}else if(strcmp(MyArgv[0],"init")==0){
		initpcb();
		rl_1 = initque();
		bl_1 = initque();
	}else if(strcmp(MyArgv[0],"cr")==0){
		int m=atoi(MyArgv[1]);
		int n=atoi(MyArgv[2]);
		createpcb(m,n);
	}else if(strcmp(MyArgv[0],"to")==0){
		to();
	}else if(strcmp(MyArgv[0],"req")==0){
		//char *m=MyArgv[1];
		int n=atoi(MyArgv[2]);
		if(strcmp(MyArgv[1],"r1")==0) request("r1",n);
		else if(strcmp("r2",MyArgv[1])==0) request("r2",n);
		else if(strcmp("r3",MyArgv[1])==0) request("r3",n);
		else if(strcmp("r4",MyArgv[1])==0) request("r4",n);//直接使用MyArgv[1]1会发生段错误
	}else if(strcmp(MyArgv[0],"de")==0){
		int m=atoi(MyArgv[1]);
		de(m);
	}else if(strcmp(MyArgv[0],"list")==0){
		if(strcmp(MyArgv[1],"ready")==0) printque(rl_1);
		else if(strcmp(MyArgv[1],"block")==0) {printbl("r1");printbl("r2");printbl("r3");printbl("r4");}
		else if(strcmp(MyArgv[1],"res")==0) {printres("r1");printres("r2");printres("r3");printres("r4");}
		else printf("wrong in your command\n");
	}else{
		printf("wrong in your command\n");	
	}
       
    }
    return 0;
}

