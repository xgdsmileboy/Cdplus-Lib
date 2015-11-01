#include<malloc.h>
#include<stack>
#include<iostream>
using namespace std;

//===========================================================================================================//
typedef struct Pos{
	long position;				//��ŵ������ĵ�������ڵ�һ���ַ���λ��
	int DocumentID;				//�ĵ���ID��
	int flag;					//��־
	struct Pos *next;		    //������ָ��
}Pos,*PPos;

typedef struct Node2{
	PPos Location;				//���ʵ�λ������
	char letter;				//��ĸ
	struct Node2 *next[26];	    //26������ָ��
}Tree,*PTree,*PNode2;

//=============================��ʼ���ڵ�=============================================================================//
void InitialTNode2(PNode2 PTN, char word)   //��ʼ���ڵ���Ϣ
{
	PTN->Location = NULL;                 //��ʼ������λ������
	PTN->letter = word;                   //��ʼ���ڵ���ĸ
	for (int i=0; i<26; i++)              //���ڵ���ȫ����ʼ��Ϊ��
	{
		PTN->next[i] = NULL;
	}
}
//==================================================================================================================//
//=======================�������ߡ��������ýṹ���ĵ���===============================================================//
void CreatDocumentTree(PTree DocTree)                      //����DocumentTree
{
	FILE *Document = fopen("Document/Document.txt","r");        //���ĵ��ļ�
	if(!Document)                                               //��ʧ�����������Ϣ
	{
		cerr<<"Open file \"Document.txt\" failed!"<<endl;
		exit(0);
	}
	int DocID = 0;                         //�ĵ���ż�����
	while (!feof(Document))                //���������ĵ�
	{
		PTree CurrDoc = DocTree;
		char Temp0[100]="";                //�����ĵ�����ַ���
		fgets(Temp0,100000,Document);      //һ���Զ�ȡһ���ĵ���Temp0���桰Document ID��
		long position0, position;          //��¼�����������ĵ��е�λ����Ϣ�������ʵ�λ��
		position0 = ftell(Document);       //��ȡ�ļ�ָ��λ�ã�ÿ�η��صĶ��ǵ�ǰ�����ĵ�����һ�����ʵ���λ��
		position = position0;              //��ȡÿ���ĵ��ĵ�һ������λ��
		char Temp[8000]="";                //Temp[]����һ���ĵ��е����е��ʣ���Temp0��϶�ȡ�ļ��е�һ�������ĵ�
		fgets(Temp,100000,Document);
		DocID++;                           //�ĵ��������Լ�һ
		for (int i=0; Temp[i]!='\0' && Temp[i]!= '\n'; i++)  //��һ���ĵ������ݽ��б���
		{
			if (Temp[i] == ' ')                              //����һ������
			{
				position = position0+i+1;                    //ָ��λ�ú���
				CurrDoc = DocTree;
				continue;
			}
			else  //1
			{
				int j = Temp[i] - 'a';                       //������λ��
				if (CurrDoc->next[j] == NULL)                //��ǰ�ڵ�Ķ�Ӧ��̻�û�н��������ڴ�֮ǰû�в�����õ��ʣ���һ�β���
				{
					PNode2 TempNode2 = new Node2;               //�����½ڵ�
					InitialTNode2(TempNode2,Temp[i]);          //��ʼ���½ڵ�
					CurrDoc->next[j] = TempNode2;             //���½ڵ����ӵ�DocumentTree��
					if (Temp[i+1]==' ' || Temp[i+1]=='\n')   //һ�����ʽ���������һ���ĵ��еĵ��ʶ��������
					{
						PPos TempPos = new Pos;              //�ڵ�ǰ�ڵ㱣�浥�ʵ�λ����Ϣ
						TempPos->position = position;        //���浥���������ĵ��е�λ��
						TempPos->DocumentID = DocID;         //���浥�������ĵ����
						TempPos->next = NULL;                //��λ�õĺ����Ϊ��
						TempNode2->Location = TempPos;        //λ����Ϣ����ĵ�һ���ڵ�
					}
					CurrDoc = CurrDoc->next[j]; 
				}//if(CurrDoc->next[j] == NULL)
				else   //2                                          //�õ���֮ǰ��������к�̽ڵ�
				{
					if (Temp[i+1]==' '|| Temp[i+1]=='\n')           //һ�����ʽ�����ϣ�����һ���������ĵ��������
					{
						PPos TempPos = new Pos;                     //�����½ڵ�
						TempPos->position = position;               //���浥��λ����Ϣ
						TempPos->DocumentID = DocID;                //�����ĵ����
						TempPos->next = CurrDoc->next[j]->Location; //��λ����Ϣ�в���ýڵ㣬����ԭ��Ϊ
						CurrDoc->next[j]->Location = TempPos;
					}//if(Temp[i+1]==' '|| Temp[i+1]=='\n')
					else
					{
						CurrDoc = CurrDoc->next[j];                  //��ǰ����û�н����꣬����ѭ��
					}
				}//else 2
			}//else 1
		}//for
	}//while
	fclose(Document);                 //�ر��ļ�
}
//====================================================================================================================//
//===========================================������====================================================================//
void SearchInDocumentTree(PTree DocumentTree)                             //��DocumentTree�в���һ���ĵ������
{
	FILE *WordInDoc = fopen("WordInDocument/WordInDocument.txt","r");     //��Ҫ���ҵĵ���
	FILE *Result = fopen("WordInDocument/WordInDocument_Result.txt","w"); //��Ų��ҽ��
	if(!WordInDoc || !Result)                                             //���ļ�ʧ��
	{
		cerr<<"Open file \"WordInDocument\" failed!"<<endl;               //���������Ϣ���ڵ���ʱ��
		exit(0);
	}
	int times = 1;                                 //����������¼��Ҫ��ѯ�ĵ��ʴ���
	while (!feof(WordInDoc))                       //��������������Ҫ��ѯ���ʵ��ļ�
	{
		bool flag = true;                          //���
		char Temp[50] = "";                        //��ʱ������Ҫ���ҵĵ���
		PTree TempDoc = DocumentTree;
		fscanf(WordInDoc,"%s",Temp);               //������ҵĵ���
		fprintf(Result,"%s %d:\n","CASE",times);   //�����ļ��������
		times++;                                   //���ʱ���Լ�һ��Ϊ�´����
		for (int i=0; Temp[i]!='\0';i++)           //�Ե��ʽ�����
		{
			int j = Temp[i] - 'a';                 //�����̷�֧���
			if(TempDoc->next[j] == NULL)           //����ĸ����Ӧ�ķ�֧û�в���������ĵ���û�иõ���
			{
				flag = false;                      //��־��Ϊfase
				break;                             //�Ƴ�forѭ��
			}
			else
			{
				TempDoc = TempDoc->next[j];        //�����Һ�������
			}
		}
		if (flag && TempDoc->Location != NULL)     //�ߵ�����������Ӧ�����һ���ڵ�λ��,���ҵ�ǰλ������Ӧ�������ĵ��е�λ����Ϣ����
		{                                          //���λ����ϢΪ�գ�˵���޴˵���
			stack<int> TempStack;                  //�����ĵ���ŵ���ʱջ�����ڽ����ĵ���ʱ���ʳ��ֵ��ĵ�����ǵ���洢�ģ�������ջʵ��
			PPos TempLoc = TempDoc->Location;      //ת���õ��ʵ�λ����Ϣ����
			int ID = TempLoc->DocumentID;          //���浥�������ĵ����
			TempStack.push(ID);                    //���һ�γ��ָõ��ʵ��ĵ���Ž�ջ
			//bool formate = true;
			while(TempLoc != NULL)                 //�Ե��ʵ�λ����Ϣ�������
			{
				if (ID > TempLoc->DocumentID)      //һ��������ͬһ���ĵ��г��ֶ��ֻ����һ��
				{
					ID = TempLoc->DocumentID;      //���µ�ǰ�ĵ�ID
					TempStack.push(ID);            //�ĵ�ID��ջ
			    }
				TempLoc = TempLoc->next;           //��λ����Ϣ�������
			}
			while(!TempStack.empty())              //��ջ�б���ĵ���λ����Ϣд���ļ�
			{
				fprintf(Result,"%d ",TempStack.top());
				TempStack.pop();                   //������ջ
			}
			fprintf(Result,"\n");                  //���������ļ��еĸ�ʽ
		}
	}
}

//===============================================================================================================================//
//=================================�����ʺ͵ڰ���============================================================================//
void TwoAndMultiWordInDoc(PTree DocTree,FILE *Search, FILE *Result,int Num=2,bool flag=true)
{                                      //���ĵ��в����������������ϵĵ���
	int times = 1;                     //������Ҫ���ҵĵ���(��������������
	while(!feof(Search))			   //���������ļ��ļ�
	{
		PTree TempDoc = DocTree;       //ָ��DocumentTree������ѭ��
		if (!flag)                     //��һ����־��һ������ʵ�������Ͷ���������ʵĲ���
		{
			fscanf(Search,"%d",&Num);  //��ȡ����������ĵ��ʸ���
		}
		fprintf(Result,"CASE %d:\n",times);
		times++;
		stack<int> TempStack;          //��ʱջ�����浥�ʳ��ֵ��ĵ����
		PPos Posit=new Pos;            //����ָ�����һ�����ʱȽϵĵ������൥�ʵ�λ����Ϣ����
		Posit->next = NULL;            //��ʼ��ָ��
		Posit->position = -1;          //�������ļ���λ����Ϣ��ʼΪ-1������Ϣ����
		Posit->flag = false;           //��־��ʼΪfalse
		int Len[10];                   //��¼��ѯ���ʳ��ȣ������жϲ鵽�ĵ����Ƿ�������
		PPos Head = new Pos;           //ָ������е�һ�����ʵ�λ����Ϣ���������һ���������ĵ���û�в鵽��Headָ��
		PPos Final = Head;             //��Final����Head�ڵ�λ�ã���һ�δ����ѯ�󣬷��㽫�ڵ�ɾ������Ϊ�����й�����Headָ��ᷢ���仯
		Head->position = -1;           //�������ļ���λ����Ϣ��ʼΪ-1������Ϣ����
		Head->next = NULL;             //��ʼָ��
		Head->DocumentID = 0;          //�ĵ���ų�ʼΪ��
		Head->flag = false;            //��ǣ���ʼΪfase����Ϊtrueʱ����ʾ��ǰ���ʲ����ĵ���
		int count = 0;                 //����������¼�������ĵ��г��ֵĴ���
		int m;
		for (m=0; m<Num; m++)                           //һ��һ�����ļ��ж���Ҫ���ҵ�Num�����ʴ���
		{
			char Temp[50] = "";                         //��ʱ��������һ������
			fscanf(Search,"%s",Temp);			        //����һ�����ʵ�Temp��
			TempDoc = DocTree;
			bool flag = false;
			for (int i=0;Temp[i]!='\0'; i++)            //�������ʣ������ĸ����
			{
				int j = Temp[i] - 'a';
				if(TempDoc->next[j] == NULL)            //DocumentTree�ߵ���һ���նˣ�˵���ĵ���û�иõ���
				{
					flag = true;                        //�����Ϊ��
					break;                              //�Ƴ�����ѭ��
				}
				else
				{
					TempDoc = TempDoc->next[j];         //����������һλ
				}
			}//for(int i=0)
			if (flag || TempDoc->Location == NULL)		//�õ��ʲ����ĵ����������һ���������
			{
				m++;
				break;
			}
			if(m==0)		                            //��¼��һ�����ʵĳ���λ����Ϣ����
			{
				Head->next = TempDoc->Location;         //ʹHeadָ��ָ������е�һ�����ʵ�λ����Ϣ����
				Head->next->flag = true;                //��־����Ϊtrue
				count++;                                //����������ĵ���������һ
				PPos DocLoc = TempDoc->Location;
				while(DocLoc->next != NULL)             //����һ�����ʵ�λ����Ϣ����ı�־����Ϊtrue��������������ʣ�൥��ʱ�Դ�Ϊ��׼��
				{                                       //���ʲ���������flagΪfalse����ʾ�ڸ��ĵ��в����ڴ��飬����ֻ�Ǹ��ĵ��е�һ��������������Document
					count++;                            //����������ĵ���������һ
					DocLoc->next->flag = true;
					DocLoc = DocLoc->next;
				}
			}//if(m==0)
			else                                        //��ǰ�����Ĳ��Ǵ���ĵ�һ������
				Posit->next = TempDoc->Location;        //Positָ��ָ�������ʣ�µ��ʵ�λ����Ϣ����Ȼ�������һ�����ʵ�λ����Ϣ����Ƚ�
			Len[m] = strlen(Temp)+1;                    //���������������λ��
			if (m)                                      //���ǵ�һ������
			{
				Len[m] = strlen(Temp)+Len[m-1]+1;        //�ۼӵ�m+1���������һ���������λ��
				PPos Curr_head = Head;                   //��ʱָ���һ�����ʵ�λ����Ϣ��������ѭ��
				bool flag = false;                        //��־
				while(Curr_head->next != NULL)           //�Ե�һ�����ʵ�λ����Ϣ���м���
				{
					if (!Curr_head->next->flag)          //��λ���Ѿ������㵥������������
					{
						Curr_head = Curr_head->next;
						continue;
					}
					PPos Record_Pos = Posit;             //ָ�����һ�����ʱȽ�λ����Ϣ�ĵ���λ����Ϣ����ͷ��Posit����ѭ��
					while (Posit->next!=NULL)            //�Ե�һ�����ʵ�һ��λ�ã�����һ������λ����Ϣ�����н���ƥ��
					{
						if (Posit->next->position - Curr_head->next->position == Len[m-1])         //��������λ���������
						{
							while(Curr_head->next->next != NULL && !Curr_head->next->next->flag)   //ѭ���Ƚ�
							{
								Curr_head = Curr_head->next;
							}
							if (Curr_head->next->next != NULL)                                     //û���ҵ�
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
								if(count==0)                                                      //���ĵ���û�иô���
									break;                                                        //����������һ������
							}
							while(Curr_head->next->next != NULL && !Curr_head->next->next->flag)  //ͬ��
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
					//�쳣�������
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
		while(m<Num)                                         //����û�ж��꣬���ڿ�ǰ�ĵ���û���ҵ�ʱ��ʣ��Ĵ��鵥�ʶ��꣬
		{                                                    //����Ӱ����һ�δ���Ķ���
			char Temp[50];
			fscanf(Search,"%s",Temp);
			m++;
		}
		if(count)                                            //��������Ϊ�㣬˵�����ĵ����ҵ��˸ô���
		 {
			 while(Head->next != NULL && !Head->next->flag)  //�ҵ��������һ�γ��ֵ��ĵ���
				 Head=Head->next;
			 if(Head->next)                                  //�ĵ���������
			{
				TempStack.push(Head->next->DocumentID);      //���һ�γ����ĵ��Ž�ջ
			    while(Head->next != NULL)                    //�������б�����ĵ�IDת�浽��ʱջ�У������д����ID����
			   {
					if (Head->next->flag && TempStack.top() > Head->next->DocumentID)
						TempStack.push(Head->next->DocumentID);
				    Head = Head->next;
				}
			}
		}
		if(!TempStack.empty())                               //ջ���գ�˵���ĵ��д��ڸô���
		{
			while(!TempStack.empty())                        //�����д������ĳ���Ҫ��ѯ�����Document IDд���ļ�
			{
				fprintf(Result,"%d ",TempStack.top());       //��ջ�е��ĵ����д���ļ�
				//cout<<TempStack.top()<<endl;
				TempStack.pop();                             //��������ĵ��Ŵ�ջ��ɾ��
			}
			fprintf(Result,"\n");                            //���Ƹ�ʽ����
		}
		delete(Final);                                       //�������ͷŵ�
	}
	fclose(Search);
	fclose(Result);
}
//===============================================================================================================//
