//比较排序算法
//直接插入排序
void insertSORE(int arr[],int n){//arr[]待排序的关键字 n关键字的个数
    int temp,i,j;//temp暂存待插入的关键字
    for(i=1;i<n;i++){
        temp=arr[i];
        j=i-1;//j表示有序的序列
        while(j>=0 && temp<arr[j]){//扫描有序序列
        //当插入的元素大于当前扫描到的值循环停止
            arr[j+1]=arr[j];//j表示从后往前扫描有序序列   将有序序列中j所指元素往后移动
            --j;//j网前移动
        }
        arr[j+1]=temp;//将元素插在j所指向的后一个位置
    }
} 
//简单选择排序
void selectSort(int arr[],int n){
    int i,j,k;
    int temp;
    for(i=0;i<n;++i){//i表示无序序列的第一元素
    k=i;
    //求最值
    for(j=i+1;j<n;++j)
        if(arr[k]>arr[j])//K所取的值为最小值
            k=j;
    //将当前i所指元素与k所指元素交换
    temp=arr[i];
    arr[i]=arr[k];
    arr[k]=temp;
    }
}
//冒泡排序
void bubleSort(int arr[],int n){
    int i,j,flag;
    int temp;
    for(i=n-1;i>=1;--i){//当前无序序列的范围  i表示从后往前
        flag=0;
        for(j=1;j<=i;++j)//j指向当前的无序序列
            if(arr[j-1]>arr[j]){
                temp = arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=temp;
                flag=1;//发生交换则置为1
            }
            if(flag==0)
                return;
    }
}
//希尔排序   选取子序列进行直接插入排序
//通过增量的移动次数来减少关键字的插入
void shellSort(int arr[],int n){
    int temp;
    for(int gap=n/2;gap>0;gap/=2){//gap表示增量
        for(int i=gap;i<n;++i){//i用于选出无序序列的第一个关键字
            temp=arr[i];//temp用于暂存
            int j;//用于扫描有序序列的关键字
            for(j=i;j>=gap && arr[j-gap]>temp;j-=gap)//如果子序列的第一个元素大于无序的第一个元素则发生交换
                arr[j]=arr[j-gap];
            arr[j]=temp;
        }
    }
}
//快速排序  时间复杂度（nlog2n）
void quickSort(int arr[],int low,int hight){//arr[]关键字数组  low和hight当前处理的子序列的范围
    int temp;
    int i=low,j=hight;
    if(low<hight){//递归出口  子序列的长度大于才递归
    //子序列划分
        temp=arr[low];//用temp保存当前范围的第一个关键字
        //往前移动j
        while(i<j){
            while(j>i && arr[j]>=temp) --j;//当j所指元素大于temp时   j往前移动
            if(i<j){
                arr[i]=arr[j];
                ++i;
            }
            //往前移动i
            while(i<j && arr[i]<temp) ++i;
            if(i<j){
                arr[j]=arr[i];
                --j;
            }
            arr[i]=temp;
            quickSort(arr,low,i-1);//枢轴左边的范围
            quickSort(arr,i+1,hight);
        }
    }
}
//堆排序 时间复杂度（nlog2n）
//最后一个非叶节点的编号(n/2)-1
/*
建大顶堆：（1）找出最后一个非叶节点p
      （2）若p所指节点的关键字值小于其孩子节点的最大关键字值 则发生交换
插入节点：1.将该节点插入到所有整个堆的最后一个位置
        2.标记从新节点到根节点的路径，将其与其路径上的值进行比较
删除节点：1.将要删除的节点移除
        2.用堆中的最后一个节点填充到删除节点的位置
        3.对堆进行调整
*/
//调整函数
void sift(int arr[],int low,int high){//low和high表示调整的范围
    int i=low,j=2*i+1;//j找i节点的左孩子节点
    int temp=arr[i];
    while(j<=high){//
        if(j<high && arr[j]<arr[j+1])//i所指节点存在左右两个孩子  将j指向i所指孩子节点中最大的那个节点
            ++j;
        if(temp<arr[j]){//判断当前i所指节点的关键是否小于j所指节点的关键字
            arr[i]=arr[j];//如果小于  则将j所指向的关键字的值赋值到i所指向的那个值
            //将i和j都向下移动一位  也即将i移动到j的位置 将j移动到i所指节点的左孩子位置
            i=j;
            j=2*i+1;
        }
        else
            break;
    }
    arr[i]=temp;
}
void heapSort(int arr[],int n){
    int i;
    int temp;
    for(i=n/2-1;i>=0;--i)//从最后一个非叶节点向上调整
        sift(arr,i,n-1);//arr完全二叉树  
    for(i=n-1;i>0;--i){
        temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
        sift(arr,0,i-1);//low的位置为根节点的位置
    }
}
//如果从数组中0的位置开始编号  则左孩子为2*i+1 右孩子为2*i+2

//归并排序 时间复杂度（nlog2n） 

//归并操作
void merge(int arr[],int low,int mid,int high){
    int i,j,k;
    int n1=mid-low+1;
    int n2=high-mid;
    int L[n1],R[n2];
    //将arr[]里的数据赋值到L和R数组中
    for(i=0;i<n1;i++)
        L[i]=arr[low+i];
    for(j=0;j<n2;j++)
        R[j]=arr[mid+1+j];
    i=0;//指向L[]的第一存储单元位置
    j=0;//指向R[]的第一存储单元位置
    k=low;//指向arr[]的第一存储单元位置
    while(i<n1 && j<n2){
        if(L[i]<=R[j])
            arr[k]=L[i++];//将i所指的关键字指向k的位置  i向后移动
        else
            arr[k]=R[j++];
        k++;
    }
    //如果关键字数组还有剩余的话  就将剩余的关键字插入到结果数组中
    while(i<n1)
        arr[k++]=L[i++];
    while(j<n2)
        arr[k++]=R[j++];
}

void mergeSort(int arr[],int low,int high){
    if(low<high){//排序的关键字范围
        int mid=(low+high)/2;
        mergeSort(arr,low,mid);//归并前半部份
        mergeSort(arr,mid+1,high);//归并后半部份
        merge(arr,low,mid,high);//对结果数组进行归并
    }
}
//基数排序
/*要求：每个关键字的位数相同   桶的个数要与待排的每一位的最多的基本单元相一致
核心动作：不停地收集和分配  分配：将关键字中的其中一位按照其值放入对应的桶中
收集：桶要从左往右  桶内要从下往上收集*/

//外部排序
//多路归并排序  每次归并都执行两次I/O操作  所有关键字的I/O次数为该树的带权路径长度的2倍