#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pcb.h"

int main(){
	initpcb();
	rl_1 = initque();
	createpcb(1001,1);
	createpcb(1002,1);
	createpcb(1003,1);
	createpcb(1004,1);
	printque(rl_1);
	del(&rl_1,1002);
	printque(rl_1);
	destroypcb();
	printque(rl_1);
}
