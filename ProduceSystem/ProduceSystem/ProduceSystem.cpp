#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

vector<string>animalSet;									//�洢�������
vector<string>ruleSet;										//�洢����
vector<string>factSet;										//�洢��ʵ
vector<string>fact1Set;										//��¼�û��������ʵ
vector<string>resultSet;
map<string,bool>initFact;									//��¼��ʼ��ʵ

/************************************************************************/
/*�����������⡢����⡢��ʵ��                                        */
/************************************************************************/
void initial()
{
	ruleSet.clear();							//�ó�ʼ״̬
	animalSet.clear();
	factSet.clear();
	fact1Set.clear();
	initFact.clear();
	resultSet.clear();

	ifstream fin;
	string s;

	fin.open("animal.txt");									//���붯�����͵�animal
	fin>>s;
	while(fin)
	{
		animalSet.push_back(s);
		fin>>s;
	}
	fin.close();
	fin.clear();

	fin.open("rule.txt");									//�������
	fin>>s;
	while(fin)
	{
		ruleSet.push_back(s);
		fin>>s;
	}
	fin.close();
	fin.clear();

	fin.open("fact.txt");									//������ʵ��
	fin>>s;
	while(fin)
	{
		fact1Set.push_back(s);
		fin>>s;
	}
	fin.close();
	fin.clear();
}

/************************************************************************/
/* ���rule�Ƿ����,�������򷵻��Ƴ��Ľ���,���򷵻�һ�����ַ���         */
/************************************************************************/
string checkRule(string & rule)
{
	char s[]="and";
	int pos=0;
	string::size_type iter1,iter2;
	string temp;
	bool flag = false;

	cout<<"ƥ�����:"<<rule<<endl;
	iter1=iter2=0;
	while(true)												//��ʼ����
	{
		iter1=rule.find(s,iter1,3);    //�ҵ��ؼ��ʵķֽ��
		if(iter1==string::npos)
		{
			iter1 = rule.find('-');    //�Ƿ���������ͬ�����ҹؼ��ʵķֽ��
			if(iter1==string::npos)
				break;
			flag=true;
		}
		unsigned i;
		for(i=iter2;i<iter1;i++)
		{
			temp+=rule[i];
		}
		iter1=iter1+3;
		for(i=0;i<factSet.size();i++)							//����ʵ��ƥ��
		{
			if(temp.compare(factSet[i])==0)
			{
				break;
			}
		}
		if(i>=factSet.size())    //���������㣬ֱ�ӷ���
		{
			cout<<"�ù���ƥ��"<<endl;
			return string("");
		}
		if(flag)
		{
			break;
		}
		iter2=iter1;
		temp = "";
	}
	iter1=rule.find('-');
	iter1++;
	temp="";
	for(;iter1!=rule.size();iter1++)
		temp+=rule[iter1];
	cout<<"�ù���ƥ�䣬�Ƶý��ۣ�"<<temp<<endl;
	return temp;
}

/************************************************************************/
/* ͨ��conclusion���������Ƶõ�ǰ���������뵽vs��                     */
/************************************************************************/
void extendFact(string & conclusion,vector<string> & vs)
{
	string temp("");
	string rule("");
	vector<string>::size_type iter,iter1,iter2;
	for(vector<string>::size_type size = 0;size<ruleSet.size();size++)
	{
		rule = ruleSet.at(size);
		iter = rule.find('-');
		for(iter1=iter+1;iter1!=rule.size();iter1++)
		{
			temp+=rule[iter1];
		}
		if(temp==conclusion)								//�ҵ��˿�����չ
		{
			iter1=iter2 = 0;
			while(true)
			{
				iter1 = rule.find("and",iter1,3);
				if(iter1==string::npos)
				{
					temp="";
					unsigned i;
					for(i=iter2;i<rule.find('-');i++)
					{
						temp+=rule[i];
					}
					initFact[temp]=true;
					for(i=0;i<vs.size();i++)						//�����ظ�
					{
						if(vs[i].compare(temp)==0)
							break;
					}
					if(i>=vs.size()||vs.empty())
						vs.push_back(temp);
					break;
				}
				else
				{
					temp="";
					for(iter=iter2;iter<iter1;iter++)
						temp+=rule[iter];
					initFact[temp]=true;
					for(iter=0;iter!=vs.size();iter++)					//����vs���Ƿ��и�Ԫ��
					{
						if(temp.compare(vs.at(iter))==0)
							break;
					}
					if(iter>=vs.size()||vs.empty())						//û�������
					{
						vs.push_back(temp);
					}
					iter1=iter1+3;
					iter2=iter1;
				}
			}
		}
		temp="";
	}
}

/************************************************************************/
/* ���conclusion�Ƿ�Ϊ����,�����򷵻�true,���򷵻�false                */
/************************************************************************/
bool isAnimal(string & conclusion)
{
	for(unsigned i=0;i<animalSet.size();i++)
		if(conclusion.compare(animalSet[i])==0)
			return true;
	return false;
}

/************************************************************************/
/* ��������֤��animal�Ƿ�Ϊ��ȷ��                                     */
/************************************************************************/
bool rcheckAnswer(string & animal)
{
	ifstream fin;
	string s;
	ruleSet.clear();
	fin.open("rule.txt");
	while(fin)
	{
		fin>>s;
		ruleSet.push_back(s);
	}
	fin.close();

	vector<string> vs;
	map<string,bool>::iterator iter;
	vector<string>::size_type indexs;
	vs.push_back(animal);

	for(indexs=0;indexs<vs.size();indexs++)
	{
		s=vs[indexs];
		extendFact(s,vs);
	}
	for(iter=initFact.begin();iter!=initFact.end();iter++)
		if(iter->second==false)
			return false;
	return true;
}

/************************************************************************/
/* ������������¹���                                                 */
/************************************************************************/
void newRules()
{
	string newRule("");
	vector<string>::size_type indexs;
	ofstream fout;
	cout<<"����Ҫ���ӵĹ���,��ʽ��:"<<ruleSet.front()<<endl;
	cin>>newRule;
	for(indexs=0;indexs!=ruleSet.size();indexs++)
	{
		if(ruleSet[indexs]==newRule)
		{
			cout<<"����������иù���"<<endl;
			break;
		}
	}
	if(indexs==ruleSet.size())
	{
		fout.open("rule.txt",ofstream::app);
		fout<<endl;
		fout<<newRule;
		fout.close();
		ruleSet.push_back(newRule);
		cout<<"��ӳɹ�"<<endl;
	}
}

/************************************************************************/
/* ɾ��������еĹ���                                                   */
/************************************************************************/
void deleteRules()
{
	string deleteRule("");
	ofstream fout;
	vector<string>::size_type indexs;
	bool flag = false;
	vector<string>::iterator iter;
	cout<<"����Ҫɾ���Ĺ���,��ʽ��:"<<ruleSet.front()<<endl;
	cin>>deleteRule;
	for(iter=ruleSet.begin();iter!=ruleSet.end();iter++)
	{
		if(deleteRule.compare(*iter)==0)
		{
			ruleSet.erase(iter);
			fout.open("rule.txt");
			for(indexs=0;indexs!=ruleSet.size();indexs++)
			{
				if(indexs!=0)
					fout<<endl;
				fout<<ruleSet[indexs];
			}
			fout.close();
			cout<<"ɾ���ɹ�"<<endl;
			flag=true;
			break;
		}
	}
	if(flag==false)
	{
		cout<<"�������û�иù���"<<endl;
	}
}

/************************************************************************/
/* ����������                                                         */
/************************************************************************/
void getResult()
{
	string temp("");
	vector<string>::size_type ix=0;
	for(ix=0;ix!=fact1Set.size();ix++)
	{
		cout<<ix+1<<":"<<setw(15)<<setiosflags(ios::left)<<fact1Set[ix]<<"\t";
		if((ix+1)%3==0)
			cout<<endl;
	}
	cout<<"\nѡ����ʵ��Ž�����ʵ��,��-1��ֹ:";
	int num;
	cin>>num;
	while(num!=-1)
	{
		factSet.push_back(fact1Set[num-1]);
		initFact[fact1Set[num-1]]=false;
		cin>>num;
	}
	while(true)
	{
		size_t count=0;										//������
		vector<string>::iterator iter;
		for(iter=ruleSet.begin();iter!=ruleSet.end();)
		{
			string conclusion;
			conclusion=checkRule(*iter);
			if(conclusion!=temp)							//����һ�����ۣ����ý����Ƿ�Ϊ���
			{
				count++;
				if(isAnimal(conclusion))
				resultSet.push_back(conclusion);
				factSet.push_back(conclusion);				//���ƵõĽ��ۼ��뵽��ʵ����
				ruleSet.erase(iter);                        //������ӵ�ǰ�������ɾ��
				iter = ruleSet.begin();
			}
			else
			{
				iter++;
			}
		}
		if(count==0)
			break;
		count = 0;
	}
	if(resultSet.size()==1&&rcheckAnswer(resultSet[0]))
		cout<<"ƥ��Ķ�����:"<<resultSet[0]<<endl;
	else
		cout<<"û��ƥ��Ķ���"<<endl;
}

/************************************************************************/
/* ������                                                               */
/************************************************************************/
int main()
{
	while(true)
	{
		initial();
		cout<<"ѡ��Ҫ���еĲ���:1.���ӹ���  2.ɾ������  3.��ѯ  4.����"<<endl;
		int num;
		cin>>num;
		switch(num)
		{
		case 1:
			{
				newRules();  //�����¹���
				break;
			}
		case 2:
			{
				deleteRules();  //ɾ������
				break;
			}
		case 3:
			{
				getResult();  //��ѯ���
				break;
			}
		case 4:
			{
				return 0;  //�˳�����
			}
		}
	}
	return 0;
}