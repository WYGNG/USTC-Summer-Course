#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000
#define MAXBIT 1000        //哈夫曼编码的最大长度
typedef struct HNode{
   char ch;//用于存放该节点字符
   int weight,parent,lchild,rchild;
}HNode;                //哈夫曼树结点
typedef struct HCode{
   int weight;
   int bit[MAXBIT];
   int start;
}HCode;                //哈夫曼编码类型
void HuffTree(HNode Huff[],int n){//生成哈夫曼树
   FILE *fp;
   char d;
   int i,j,w,m1,m2,x1,x2;
   for(i=0;i<2*n-1;i++)                  //数组初始化
   {
      Huff[i].ch=' ';
      Huff[i].weight=0;
      Huff[i].parent=-1;
      Huff[i].lchild=-1;
      Huff[i].rchild=-1;
   }
   printf("输入%d个字符及它的权值: \n",n);//读入数据
   getchar();
   for(i=0;i<n;i++){
       printf("请输入第%d个字符:",i+1);
       scanf("%c",&d);
       getchar();
       Huff[i].ch=d;
       printf("请输入第%d个字符的权值:",i+1);
       scanf("%d",&w);
       getchar();
       Huff[i].weight=w;
   }
   for(i=0;i<n-1;i++){//构造哈夫曼树并生成该树的n-1个分支结点
       m1=m2=32767;
       x1=x2=0;
       for(j=0;j<n+i;j++){//选取最小和次小两个权值结点并将其序号送x1和x2
          if(Huff[j].parent==-1&&Huff[j].weight<m1){
             m2=m1;
             x2=x1;
             m1=Huff[j].weight;
             x1=j;
          }
          else
             if(Huff[j].parent==-1&&Huff[j].weight<m2){
                m2=Huff[j].weight;
                x2=j;
             }
       }
       //将找出的两棵子树合并为一棵新的子树
      Huff[x1].parent=n+i;
      Huff[x2].parent=n+i;
      Huff[n+i].weight=Huff[x1].weight+Huff[x2].weight;
      Huff[n+i].lchild=x1;
      Huff[n+i].rchild=x2;
   }
   printf("哈夫曼树列表:\n");
   printf("\n_________________________________________________________|\n");
   printf("zifu | Huff| weight |    lchild  |     rchild|    parent | \n");
   for(i=0;i<2*n-1;i++){//输出哈夫曼树即数组Huff的信息
       printf("_____|_____|________|____________|___________|___________|\n");
       printf("%4c |%4d | %5d  | %10d |%10d |%10d |\n",Huff[i].ch, i, Huff[i].weight,
       Huff[i].lchild,Huff[i].rchild, Huff[i].parent);
   }
     printf("_________________________________________________________|\n");
     if((fp=fopen("d:\\hfmtree.txt","w"))==NULL)//建立hfmtree文件
        printf("cannot open the file of hfmtree\n");
     else{
        fprintf(fp,"zifu Huff weight     lchild      rchild     parent \n");
        for(i=0;i<2*n-1;i++){
            fprintf(fp,"%3c %3d %5d %10d %10d %10d \n",Huff[i].ch,i, Huff[i].weight,
            Huff[i].lchild,Huff[i].rchild, Huff[i].parent);
        }
        fclose(fp);
     }
}
void HuffmanCode(HNode Huff[],int n){//生成哈夫曼编码
   FILE *fw;
   HCode HuffCode[MAXSIZE/2],cd;        
// MAXSIZE/2为叶结点的最大个数
   int i,j,c,p;
   for(i=0;i<n;i++){//求每个叶结点的哈夫曼编码
      HuffCode[i].weight=Huff[i].weight;
      cd.start=MAXBIT-1;
      c=i;
      p=Huff[c].parent;
      while(p!=-1){
         if(Huff[p].lchild==c)
            cd.bit[cd.start]=0;
         else
            cd.bit[cd.start]=1;
         cd.start--;
         c=p;
         p=Huff[c].parent;
      }
      for(j=cd.start+1;j<MAXBIT;j++)//保存该叶结点字符的哈夫曼编码
          HuffCode[i].bit[j]=cd.bit[j];
      HuffCode[i].start=cd.start;//保存该编码在数组bit中的起始位置
   }
   printf("字母哈夫曼编码如下:\n");
   printf("-----|--------|--------|-------|\n");
   printf("zifu |HuffCode| weight |   bit |\n");       //输出数组HuffCode的有关信息
   printf("-----|--------|--------|-------|\n");
   for(i=0;i<n;i++){//输出各叶结点对应的哈夫曼编码   
       printf("%4c |%5d   |%4d    |     ",Huff[i].ch,i,HuffCode[i].weight);
       for(j=HuffCode[i].start+1;j<MAXBIT;j++)
           printf("%d |",HuffCode[i].bit[j]);
       printf("\n");
       printf("-----|--------|--------|-------|\n");
   }
   if((fw=fopen("d:\\CodeFile.txt","w"))==NULL)//建立codeFile文件
     printf("cannot open the file of CodeFile\n");
   else{
        fprintf(fw,"zifu HuffCode weight    bit \n");
        for(i=0;i<n;i++){
           fprintf(fw,"%4c%5d%8d     ",Huff[i].ch,i,HuffCode[i].weight);
           for(j=HuffCode[i].start+1;j<MAXBIT;j++)
              fprintf(fw,"%d",HuffCode[i].bit[j]);
           fprintf(fw,"\n");
        }
    }
    fclose(fw);
}
void decode(HNode Huff[],int n){//依次读入电文，根据哈夫曼树译码
    FILE *fs;
    int i,j=0;
    char b[MAXSIZE];
    i=2*n-2;             //从根结点开始往下搜索
    printf("【输入电文，并进行译码】\n");
    getchar();
    printf("输入发送的编码(以'2'为结束标志)：\n");
    gets(b);
    printf("译码后的字符为:\n");
    while(b[j]!='2'){
       if(b[j]=='0')
           i=Huff[i].lchild;   //走向左孩子
       else
           i=Huff[i].rchild;   //走向右孩子
       if(Huff[i].lchild==-1){//tree[i]是叶结点
          printf("%c",Huff[i].ch);
          i=2*n-2;      //回到根结点
       }
      j++;
   }
    printf("\n");
    if(Huff[i].lchild!=-1&&b[j]!='2')//电文读完，但尚未到叶子结点
         printf("\nERROR\n");  //输入电文有错
    else{
        if((fs=fopen("d:\\textFile.txt","w"))==NULL)//建立textFile文件
            printf("cannot open the textFile.txt of CodeFile\n");
        else{
            fprintf(fs,"译码后的字符为");
        while(b[j]!='2'){
            if(b[j]=='0')
              i=Huff[i].lchild;   //走向左孩子
            else
              i=Huff[i].rchild;   //走向右孩子
            if(Huff[i].lchild==-1){//tree[i]是叶结点
              fprintf(fs,"%c",Huff[i].ch);
              i=2*n-2;      //回到根结点
           }
           j++;
         }
       }
    }
}
void menu(){
    printf("菜单如下\n");
    printf("1-------建立哈夫曼树\n" );
    printf("2-------进行哈夫编码\n");
    printf("3-------进行哈夫译码\n");
    printf("0-------程序退出\n");
}
int main(){
    HNode Huff[MAXSIZE];
    int n,sel;
    printf("                            ——哈夫曼编码与译码——\n");
    printf("Input numbers of leaf :\n");    //n为叶结点个数
    scanf("%d",&n);
    do{
        menu();
        printf("请输入您的选择:\n");
        scanf("%d",&sel);
        switch(sel){
            case 1:
            HuffTree(Huff,n);//建立哈夫曼树
            break;
            case 2:
            HuffmanCode(Huff,n);  //生成哈夫曼编码
            break;
            case 3:
            decode(Huff,n);//译码变代码
            break;
        }
    }while(sel!=0);
    return 0;
}

