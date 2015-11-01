#include<malloc.h>
#include<stack>
#include<iostream>
using namespace std;

//===========================================================================================================//
typedef struct Pos{
	long position;				//存放单词在文档中相对于第一个字符的位置
	int DocumentID;				//文档的ID号
	int flag;					//标志
	struct Pos *next;		    //链表后继指针
}Pos,*PPos;

typedef struct Node2{
	PPos Location;				//单词的位置链表
	char letter;				//字母
	struct Node2 *next[26];	    //26个孩子指针
}Tree,*PTree,*PNode2;

//=============================初始化节点=============================================================================//
void InitialTNode2(PNode2 PTN, char word)   //初始化节点信息
{
	PTN->Location = NULL;                 //初始化单词位置链表
	PTN->letter = word;                   //初始化节点字母
	for (int i=0; i<26; i++)              //将节点后继全部初始化为空
	{
		PTN->next[i] = NULL;
	}
}
//==================================================================================================================//
//=======================第六、七、八问所用结构，文档树===============================================================//
void CreatDocumentTree(PTree DocTree)                      //建立DocumentTree
{
	FILE *Document = fopen("Document/Document.txt","r");        //打开文档文件
	if(!Document)                                               //打开失败输出错误信息
	{
		cerr<<"Open file \"Document.txt\" failed!"<<endl;
		exit(0);
	}
	int DocID = 0;                         //文档编号计数器
	while (!feof(Document))                //遍历整个文档
	{
		PTree CurrDoc = DocTree;
		char Temp0[100]="";                //保存文档编号字符串
		fgets(Temp0,100000,Document);      //一次性读取一个文档，Temp0保存“Document ID”
		long position0, position;          //记录单词在整个文档中的位置信息，即单词的位序
		position0 = ftell(Document);       //获取文件指针位置，每次返回的都是当前所读文档的以一个单词的首位置
		position = position0;              //获取每个文档的第一个单词位置
		char Temp[8000]="";                //Temp[]保存一个文档中的所有单词，与Temp0配合读取文件中的一个完整文档
		fgets(Temp,100000,Document);
		DocID++;                           //文档计数器自加一
		for (int i=0; Temp[i]!='\0' && Temp[i]!= '\n'; i++)  //对一个文档的内容进行遍历
		{
			if (Temp[i] == ' ')                              //读完一个单词
			{
				position = position0+i+1;                    //指针位置后移
				CurrDoc = DocTree;
				continue;
			}
			else  //1
			{
				int j = Temp[i] - 'a';                       //保存后继位次
				if (CurrDoc->next[j] == NULL)                //当前节点的对应后继还没有建立，即在此之前没有插入过该单词，第一次插入
				{
					PNode2 TempNode2 = new Node2;               //增加新节点
					InitialTNode2(TempNode2,Temp[i]);          //初始化新节点
					CurrDoc->next[j] = TempNode2;             //将新节点连接到DocumentTree中
					if (Temp[i+1]==' ' || Temp[i+1]=='\n')   //一个单词结束，或是一个文档中的单词都保存结束
					{
						PPos TempPos = new Pos;              //在当前节点保存单词的位置信息
						TempPos->position = position;        //保存单词在整个文档中的位置
						TempPos->DocumentID = DocID;         //保存单词所在文档编号
						TempPos->next = NULL;                //将位置的后继置为空
						TempNode2->Location = TempPos;        //位置信息链表的第一个节点
					}
					CurrDoc = CurrDoc->next[j]; 
				}//if(CurrDoc->next[j] == NULL)
				else   //2                                          //该单词之前插入过，有后继节点
				{
					if (Temp[i+1]==' '|| Temp[i+1]=='\n')           //一个单词解析完毕，或是一个完整的文档解析完毕
					{
						PPos TempPos = new Pos;                     //增加新节点
						TempPos->position = position;               //保存单词位置信息
						TempPos->DocumentID = DocID;                //保存文档编号
						TempPos->next = CurrDoc->next[j]->Location; //在位置信息中插入该节点，插入原则为
						CurrDoc->next[j]->Location = TempPos;
					}//if(Temp[i+1]==' '|| Temp[i+1]=='\n')
					else
					{
						CurrDoc = CurrDoc->next[j];                  //当前单词没有解析完，继续循环
					}
				}//else 2
			}//else 1
		}//for
	}//while
	fclose(Document);                 //关闭文件
}
//====================================================================================================================//
//===========================================第六问====================================================================//
void SearchInDocumentTree(PTree DocumentTree)                             //在DocumentTree中查找一个的单词情况
{
	FILE *WordInDoc = fopen("WordInDocument/WordInDocument.txt","r");     //将要查找的单词
	FILE *Result = fopen("WordInDocument/WordInDocument_Result.txt","w"); //存放查找结果
	if(!WordInDoc || !Result)                                             //打开文件失败
	{
		cerr<<"Open file \"WordInDocument\" failed!"<<endl;               //输出错误信息，在调试时用
		exit(0);
	}
	int times = 1;                                 //计数器，记录所要查询的单词次序
	while (!feof(WordInDoc))                       //遍历整个保存所要查询单词的文件
	{
		bool flag = true;                          //标记
		char Temp[50] = "";                        //临时保存所要查找的单词
		PTree TempDoc = DocumentTree;
		fscanf(WordInDoc,"%s",Temp);               //读入查找的单词
		fprintf(Result,"%s %d:\n","CASE",times);   //输入文件单词序号
		times++;                                   //单词编号自加一，为下次输出
		for (int i=0; Temp[i]!='\0';i++)           //对单词解析，
		{
			int j = Temp[i] - 'a';                 //保存后继分支序号
			if(TempDoc->next[j] == NULL)           //该字母所对应的分支没有插入过，即文档中没有该单词
			{
				flag = false;                      //标志置为fase
				break;                             //推出for循环
			}
			else
			{
				TempDoc = TempDoc->next[j];        //按照找后继向后找
			}
		}
		if (flag && TempDoc->Location != NULL)     //走到看单词所对应的最后一个节点位置,并且当前位置所对应单词在文档中的位置信息不空
		{                                          //如果位置信息为空，说明无此单词
			stack<int> TempStack;                  //保存文档编号的临时栈，由于建立文档树时单词出现的文档序号是倒序存储的，所以用栈实现
			PPos TempLoc = TempDoc->Location;      //转到该单词的位置信息链表
			int ID = TempLoc->DocumentID;          //保存单词所在文档编号
			TempStack.push(ID);                    //最后一次出现该单词的文档编号进栈
			//bool formate = true;
			while(TempLoc != NULL)                 //对单词的位置信息链表遍历
			{
				if (ID > TempLoc->DocumentID)      //一个单词在同一个文档中出现多次只保存一个
				{
					ID = TempLoc->DocumentID;      //更新当前文档ID
					TempStack.push(ID);            //文档ID进栈
			    }
				TempLoc = TempLoc->next;           //对位置信息链表遍历
			}
			while(!TempStack.empty())              //将栈中保存的单词位置信息写入文件
			{
				fprintf(Result,"%d ",TempStack.top());
				TempStack.pop();                   //输出后出栈
			}
			fprintf(Result,"\n");                  //控制输入文件中的格式
		}
	}
}

//===============================================================================================================================//
//=================================第七问和第八问============================================================================//
void TwoAndMultiWordInDoc(PTree DocTree,FILE *Search, FILE *Result,int Num=2,bool flag=true)
{                                      //在文档中查找两个即两个以上的单词
	int times = 1;                     //保存所要查找的单词(两个或多个）次序
	while(!feof(Search))			   //遍历整个文件文件
	{
		PTree TempDoc = DocTree;       //指向DocumentTree，用于循环
		if (!flag)                     //设一个标志，一个函数实现两个和多个连续单词的查找
		{
			fscanf(Search,"%d",&Num);  //读取单词组包含的单词个数
		}
		fprintf(Result,"CASE %d:\n",times);
		times++;
		stack<int> TempStack;          //临时栈，保存单词出现的文档编号
		PPos Posit=new Pos;            //用于指向与第一个单词比较的单词其余单词的位置信息链表
		Posit->next = NULL;            //初始化指空
		Posit->position = -1;          //单词在文件的位置信息初始为-1，该信息不用
		Posit->flag = false;           //标志初始为false
		int Len[10];                   //记录查询单词长度，用于判断查到的单词是否连续的
		PPos Head = new Pos;           //指向词组中第一个单词的位置信息链表，如果第一个单词在文档中没有查到，Head指空
		PPos Final = Head;             //用Final保存Head节点位置，在一次词组查询后，方便将节点删除，因为在运行过程中Head指针会发生变化
		Head->position = -1;           //单词在文件的位置信息初始为-1，该信息不用
		Head->next = NULL;             //初始指空
		Head->DocumentID = 0;          //文档编号初始为空
		Head->flag = false;            //标记，初始为fase，当为true时，表示当前单词不在文档中
		int count = 0;                 //计数器，记录单词在文档中出现的次数
		int m;
		for (m=0; m<Num; m++)                           //一个一个从文件中读入要查找的Num个单词词组
		{
			char Temp[50] = "";                         //临时保存读入的一个单词
			fscanf(Search,"%s",Temp);			        //读入一个单词到Temp中
			TempDoc = DocTree;
			bool flag = false;
			for (int i=0;Temp[i]!='\0'; i++)            //解析单词，逐个字母查找
			{
				int j = Temp[i] - 'a';
				if(TempDoc->next[j] == NULL)            //DocumentTree走到了一个终端，说明文档中没有该单词
				{
					flag = true;                        //标记置为真
					break;                              //推出解析循环
				}
				else
				{
					TempDoc = TempDoc->next[j];         //解析单词下一位
				}
			}//for(int i=0)
			if (flag || TempDoc->Location == NULL)		//该单词不在文档中则进入下一个词组查找
			{
				m++;
				break;
			}
			if(m==0)		                            //记录第一个单词的出现位置信息链表
			{
				Head->next = TempDoc->Location;         //使Head指针指向词组中第一个单词的位置信息链表
				Head->next->flag = true;                //标志域标记为true
				count++;                                //包含词组的文档计数器加一
				PPos DocLoc = TempDoc->Location;
				while(DocLoc->next != NULL)             //将第一个单词的位置信息链表的标志域都置为true，当检索词组中剩余单词时以此为基准，
				{                                       //单词不连续，置flag为false，表示在该文档中不存在词组，但是只是该文档中的一处，并不是整个Document
					count++;                            //包含词组的文档计数器加一
					DocLoc->next->flag = true;
					DocLoc = DocLoc->next;
				}
			}//if(m==0)
			else                                        //当前解析的不是词组的第一个单词
				Posit->next = TempDoc->Location;        //Posit指针指向词组中剩下单词的位置信息链表，然后将其与第一个单词的位置信息链表比较
			Len[m] = strlen(Temp)+1;                    //计算两个单词相差位数
			if (m)                                      //不是第一个单词
			{
				Len[m] = strlen(Temp)+Len[m-1]+1;        //累加第m+1个单词与第一个单词相差位数
				PPos Curr_head = Head;                   //临时指向第一个单词的位置信息链表，用于循环
				bool flag = false;                        //标志
				while(Curr_head->next != NULL)           //对第一个单词的位置信息进行检索
				{
					if (!Curr_head->next->flag)          //该位置已经不满足单词连续，跳过
					{
						Curr_head = Curr_head->next;
						continue;
					}
					PPos Record_Pos = Posit;             //指向与第一个单词比较位置信息的单词位置信息链表头，Posit用于循环
					while (Posit->next!=NULL)            //对第一个单词的一个位置，在下一个单词位置信息链表中进行匹配
					{
						if (Posit->next->position - Curr_head->next->position == Len[m-1])         //两个单词位置连续情况
						{
							while(Curr_head->next->next != NULL && !Curr_head->next->next->flag)   //循环比较
							{
								Curr_head = Curr_head->next;
							}
							if (Curr_head->next->next != NULL)                                     //没有找到
							{
								Curr_head = Curr_head->next;
								Record_Pos = Posit;
								continue;
							}
							else
							{
								flag = true;
								break;
							}
						}//if
						if (Posit->next->position < Curr_head->next->position)
						{
							if (Curr_head->next->flag)
							{
								Curr_head->next->flag = false;
								count--;
								if(count==0)                                                      //该文档中没有该词组
									break;                                                        //继续查找下一个词组
							}
							while(Curr_head->next->next != NULL && !Curr_head->next->next->flag)  //同上
 							{
								Curr_head = Curr_head->next;
 							}
							if (Curr_head->next->next != NULL)
							{
								Curr_head = Curr_head->next;
								Posit = Record_Pos;
								continue;
							}
							else
							{
								flag = true;
								break;
							}
						}//if
						Record_Pos = Posit;
						Posit = Posit->next;
					}//while (Posit->next!=NULL)
					if (flag)
						break;
					if (Posit->next == NULL && Curr_head->next != NULL)
					{
						
						while (Curr_head->next->next != NULL)
						{
							if (Curr_head->next->flag)
							{
								count--;
								Curr_head->next->flag = false;
							}
							Curr_head = Curr_head->next;
						}//while
					}
					if(count==0)
						break;
					//异常情况处理
					if (Curr_head->next->flag)
					{
						count--;
						Curr_head->next->flag = false;
					}
					Curr_head = Curr_head->next;
				}
			}
			if(count==0)
			{
				m++;
				break;
			}
		}
		while(m<Num)                                         //词组没有读完，用于靠前的单词没有找到时将剩余的词组单词读完，
		{                                                    //以免影响下一次词组的读入
			char Temp[50];
			fscanf(Search,"%s",Temp);
			m++;
		}
		if(count)                                            //计数器不为零，说明在文档中找到了该词组
		 {
			 while(Head->next != NULL && !Head->next->flag)  //找到词组最后一次出现的文档号
				 Head=Head->next;
			 if(Head->next)                                  //文档号链表不空
			{
				TempStack.push(Head->next->DocumentID);      //最后一次出现文档号进栈
			    while(Head->next != NULL)                    //将链表中保存的文档ID转存到临时栈中，链表中存的是ID逆序
			   {
					if (Head->next->flag && TempStack.top() > Head->next->DocumentID)
						TempStack.push(Head->next->DocumentID);
				    Head = Head->next;
				}
			}
		}
		if(!TempStack.empty())                               //栈不空，说明文档中存在该词组
		{
			while(!TempStack.empty())                        //将所有存下来的出现要查询词组的Document ID写入文件
			{
				fprintf(Result,"%d ",TempStack.top());       //将栈中的文档编号写入文件
				//cout<<TempStack.top()<<endl;
				TempStack.pop();                             //将输出的文档号从栈中删除
			}
			fprintf(Result,"\n");                            //控制格式换行
		}
		delete(Final);                                       //将链表释放掉
	}
	fclose(Search);
	fclose(Result);
}
//===============================================================================================================//
