#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

vector<string>animalSet;									//存储动物类别
vector<string>ruleSet;										//存储规则
vector<string>factSet;										//存储事实
vector<string>fact1Set;										//记录用户输入的事实
vector<string>resultSet;
map<string,bool>initFact;									//记录初始事实

/************************************************************************/
/*建立动物类别库、规则库、事实库                                        */
/************************************************************************/
void initial()
{
	ruleSet.clear();							//置初始状态
	animalSet.clear();
	factSet.clear();
	fact1Set.clear();
	initFact.clear();
	resultSet.clear();

	ifstream fin;
	string s;

	fin.open("animal.txt");									//读入动物类型到animal
	fin>>s;
	while(fin)
	{
		animalSet.push_back(s);
		fin>>s;
	}
	fin.close();
	fin.clear();

	fin.open("rule.txt");									//读入规则
	fin>>s;
	while(fin)
	{
		ruleSet.push_back(s);
		fin>>s;
	}
	fin.close();
	fin.clear();

	fin.open("fact.txt");									//建立事实库
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
/* 检查rule是否成立,若成立则返回推出的结论,否则返回一个空字符串         */
/************************************************************************/
string checkRule(string & rule)
{
	char s[]="and";
	int pos=0;
	string::size_type iter1,iter2;
	string temp;
	bool flag = false;

	cout<<"匹配规则:"<<rule<<endl;
	iter1=iter2=0;
	while(true)												//开始查找
	{
		iter1=rule.find(s,iter1,3);    //找到关键词的分界点
		if(iter1==string::npos)
		{
			iter1 = rule.find('-');    //非符合条件，同样查找关键词的分界点
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
		for(i=0;i<factSet.size();i++)							//与事实库匹配
		{
			if(temp.compare(factSet[i])==0)
			{
				break;
			}
		}
		if(i>=factSet.size())    //条件不满足，直接返回
		{
			cout<<"该规则不匹配"<<endl;
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
	cout<<"该规则匹配，推得结论："<<temp<<endl;
	return temp;
}

/************************************************************************/
/* 通过conclusion逆向推理将推得的前提条件加入到vs中                     */
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
		if(temp==conclusion)								//找到了可以扩展
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
					for(i=0;i<vs.size();i++)						//避免重复
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
					for(iter=0;iter!=vs.size();iter++)					//查找vs中是否有该元素
					{
						if(temp.compare(vs.at(iter))==0)
							break;
					}
					if(iter>=vs.size()||vs.empty())						//没有则加入
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
/* 检查conclusion是否为结论,若是则返回true,否则返回false                */
/************************************************************************/
bool isAnimal(string & conclusion)
{
	for(unsigned i=0;i<animalSet.size();i++)
		if(conclusion.compare(animalSet[i])==0)
			return true;
	return false;
}

/************************************************************************/
/* 逆向推理证明animal是否为正确答案                                     */
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
/* 向规则库中添加新规则                                                 */
/************************************************************************/
void newRules()
{
	string newRule("");
	vector<string>::size_type indexs;
	ofstream fout;
	cout<<"输入要增加的规则,格式如:"<<ruleSet.front()<<endl;
	cin>>newRule;
	for(indexs=0;indexs!=ruleSet.size();indexs++)
	{
		if(ruleSet[indexs]==newRule)
		{
			cout<<"规则库中已有该规则"<<endl;
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
		cout<<"添加成功"<<endl;
	}
}

/************************************************************************/
/* 删除规则库中的规则                                                   */
/************************************************************************/
void deleteRules()
{
	string deleteRule("");
	ofstream fout;
	vector<string>::size_type indexs;
	bool flag = false;
	vector<string>::iterator iter;
	cout<<"输入要删除的规则,格式如:"<<ruleSet.front()<<endl;
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
			cout<<"删除成功"<<endl;
			flag=true;
			break;
		}
	}
	if(flag==false)
	{
		cout<<"规则库中没有该规则"<<endl;
	}
}

/************************************************************************/
/* 正向推理函数                                                         */
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
	cout<<"\n选择事实编号建立事实库,以-1终止:";
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
		size_t count=0;										//计数器
		vector<string>::iterator iter;
		for(iter=ruleSet.begin();iter!=ruleSet.end();)
		{
			string conclusion;
			conclusion=checkRule(*iter);
			if(conclusion!=temp)							//返回一个结论，检查该结论是否为结果
			{
				count++;
				if(isAnimal(conclusion))
				resultSet.push_back(conclusion);
				factSet.push_back(conclusion);				//将推得的结论加入到事实库中
				ruleSet.erase(iter);                        //将规则从当前规则库中删除
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
		cout<<"匹配的动物是:"<<resultSet[0]<<endl;
	else
		cout<<"没有匹配的动物"<<endl;
}

/************************************************************************/
/* 主函数                                                               */
/************************************************************************/
int main()
{
	while(true)
	{
		initial();
		cout<<"选择要进行的操作:1.增加规则  2.删除规则  3.查询  4.结束"<<endl;
		int num;
		cin>>num;
		switch(num)
		{
		case 1:
			{
				newRules();  //增加新规则
				break;
			}
		case 2:
			{
				deleteRules();  //删除规则
				break;
			}
		case 3:
			{
				getResult();  //查询结果
				break;
			}
		case 4:
			{
				return 0;  //退出程序
			}
		}
	}
	return 0;
}