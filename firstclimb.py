#首选爬山法
#与最陡爬山法的区别在于随机生成后继到优于前一个节点就停止
#最陡的是生成全部选择最陡的
import random
import time

fail=0
suc=0#求解失败和成功的次数
def collisionnum(s):
    num=0
    for i in range(len(s)):
        for j in range(i+1,len(s)):
            #同行或者在对角线上
            if s[i]==s[j] or abs(s[i]-s[j])==j-i:
                num+=1
    return num

def rdm():#随机生成一组数字
    col=random.randint(0,7)
    number=random.randint(0,7)
    return col,number

def FC(start,cost):
    global suc,fail
    flag=True
    maxcount=500#最大随机次数
    count=0
    std=collisionnum(start)#标准，一旦小于这个就结束循环
    if collisionnum(start)==0:
        #无需爬山
        suc+=1
        return start,cost
    else:
        #随机的生成后继
        while count<=maxcount:
            pair=rdm()
            if start[pair[0]]!=pair[1]:
                count+=1
                tmp=start[pair[0]]
                start[pair[0]]=pair[1]
                if collisionnum(start)<std:
                    cost+=1
                    return FC(start,cost)
                else:
                    start[pair[0]]=tmp
            
        #循环完一遍，若没有爬山的则宣告求解失败
        if collisionnum(start)==0:
            #无解
            suc+=1
            print('耗散值:'+str(cost)+'\n')
            return start,cost
        else:
            fail+=1
            print('耗散值:'+str(cost)+'\n')
            return start,cost

def main():
    global fail,suc
    begin=time.perf_counter()
    f=open('D:\\tx\\1600420654\\FileRecv\\homework\\AI\\8q_gtor.txt','r')
    dctnry=f.readlines()
    total=len(dctnry)
    k=0
    for i in dctnry:
        board=[]
        for j in i.split():
            board.append(int(j))
        sth=FC(board,k)
    end=time.perf_counter()
    print('总时间：'+str(end-begin)+'\n')
    print('成功率：'+str(suc/float(total))+'\n')
    print('失败率：'+str(fail/float(total))+'\n')
    f.close()



if __name__=='__main__':
    main()