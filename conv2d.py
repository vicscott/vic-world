class conv2d():
    def __init__(self,input_ch,output_ch,kernel_size,padding=False,stride=1):
#         pass
        self.input_ch=input_ch
        self.output_ch=output_ch
        self.kernel_size=kernel_size
        self.padding=padding
        self.stride=stride
    
    
    def __call__(self,x):
#         pass
        if self.padding:
            padding_size=(self.kernel_size-1)/2
            x=F.pad(x,[padding_size,padding_size,padding_size,padding_size,0,0,0,0])
        
        kernel = torch.ones(self.output_ch,self.input_ch,self.kernel_size,self.kernel_size)
#         kernel = torch.nn.init.normal_(kernel)
        conv_times = int((x.shape[2]-(self.kernel_size-1))*(x.shape[3]-(self.kernel_size-1)))
        
        kernel_mat = kernel.reshape(self.output_ch,self.input_ch,-1,1) #shape:[output_ch,input_ch,kernel_size^2,1]
#         feature_mat = torch.zeros([self.input_ch,conv_times,self.kernel_size^2]) #shape:[input_ch,conv_times,kernel_size^2]
        output=[]
        for i in range(x.shape[0]): # traverse batch_size
            out_list=[]
            tmp_input = x[i,:,:,:].squeeze(0).reshape(x.shape[1],-1)
#             feature_mat= torch.zeros(conv_times,self.kernel_size*self.kernel_size)
            feature_mat=[]

            for j in range(self.input_ch):
                feature_mat += [torch.stack([tmp_input[j,wj:wj+self.kernel_size,hj:hj+self.kernel_size].flatten() \
                                           for hj in range(x.shape[3]-self.kernel_size+1,self.stride) \
                                           for wj in range(x.shape[2]-self.kernel_size+1,self.stride)],0)]            
            feature_mat=torch.stack(feature_mat,0).reshape(self.input_ch,-1,self.kernel_size*self.kernel_size).repeat([6,1,1,1])

            feature_mat=feature_mat@kernel_mat

            output+=[torch.sum(feature_mat.reshape(self.output_ch,self.input_ch,x.shape[2]-self.kernel_size+1,-1),dim=1)]

        output=torch.stack(output,0)
            
        return output.transpose(-1,-2)
### the result had been proved to be same with torch.nn.Conv2d, but it is obviously slower and slower!            
### maybe flatten kernel will be faster using F.pad()
### this can also be done by torch.unfold()
