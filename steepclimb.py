import random
import time
#局部搜索法不保留路径
#最陡上升爬山法
SOLUTION_collision_num=0
fail=0#求解失败次数
suc=0

def collisionnum(cols):#检测冲突的数量
    #将棋盘分成8列，每组值就是其在每列上的位置
    num=0
    for i in range(len(cols)):
        for j in range(i+1,len(cols)):
            #检测冲突，同行和在对角线上
            if cols[i]==cols[j] or abs(cols[i]-cols[j])==j-i:
                num+=1
    return num

def steepclimb(start,cost):
    collisionnumset={}
    std=collisionnum(start)
    #在所有后继中选择最小节点扩展
    if collisionnum(start)==0:
        #print('无需爬山')
        global suc
        suc+=1
        return start,cost
    else:
        for i in range(len(start)):#把start中的每一个值都在（0，7）中遍历一遍，找到最小的collisionnum
            for j in range(7):
                if start[i]==j:
                    continue
                tmp=start[i]
                start[i]=j
                collisionnumset[(i,j)]=collisionnum(start)
                start[i]=tmp
        #print(len(collisionnumset))
    
        for posi,value in collisionnumset.items():#找到最小的节点
            if value<std:
                std=value
                status=posi
        if std==collisionnum(start):
            #print('停止爬山')
            return start,cost
        else:
            #print(std)
            dau=start
            dau[status[0]]=status[1]
            cost+=1
            return steepclimb(dau,cost)##这里一定要用return返回，不能直接写steepclimb
            #由于return返回值会传递给上一层函数，而上一层函数没有return命令，故会返回None值给最外层，所以结果是None
                

def main():
    global fail,suc
    begin=time.perf_counter()
    f=open('D:\\tx\\1600420654\\FileRecv\\homework\\AI\\8q_gtor.txt','r')
    total=len(f.readlines())
    print(f.readlines())
    for line in f.readlines():
        k=0#爬山次数,即耗散值
        cols=[]
        print(line)
        for num in line.split():#得到一个棋盘
            cols.append(int(num))
            print('hhhhi')
        sth=steepclimb(cols,k)
        if collisionnum(sth[0])==0:
            suc+=1
        else:
            fail+=1
        
    end=time.perf_counter()
    print('总时间：'+str(end-begin)+'\n')
    print('总数：'+str(total)+'\n')
    print('成功率：'+str(suc/float(total))+'\n')
    print('失败率：'+str(fail/float(total))+'\n')
    f.close()

begin=time.perf_counter()
f=open('D:\\tx\\1600420654\\FileRecv\\homework\\AI\\8q_gtor.txt','r')
char=f.readlines()
total=len(char)
for line in char:
    k=0#爬山次数,即耗散值
    cols=[]
    for num in line.split():#得到一个棋盘
        cols.append(int(num))
        
    sth=steepclimb(cols,k)
    print('耗散值:'+str(sth[1])+'\n')
    if collisionnum(sth[0])==0:
            suc+=1
    else:
        fail+=1
        
end=time.perf_counter()
print('总时间：'+str(end-begin)+'\n')
print('总数：'+str(total)+'\n')
print('成功率：'+str(suc/float(total))+'\n')
print('失败率：'+str(fail/float(total))+'\n')
f.close()

    
