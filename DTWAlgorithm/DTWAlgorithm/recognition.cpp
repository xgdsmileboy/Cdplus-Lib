#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


const int MAXNFRAME = 300; // max number of frames һ����Ƶ�������300֡����Լ3000ms
const int DVECTOR = 39; // dimension of a frame ÿһ֡��һ��39άMFCC������ʾ

#include "binaryRead.h"
#include "recognition.h"

float TemplateVectors[10][ MAXNFRAME+1 ][ DVECTOR+1 ]; // �洢10��template��֡����
int NFTemplate[10]; // number of frames in each template vector �洢10��template���Ե�֡��

//void main( int argc, char *argv[] )
//{
//	string TestFileList = "myTestFileList.txt"; // test list ���������б�
//	
//	/*----------------��ȡģ������---------------------*/
//	string TemplateFolder = "myTemplate";
//	//string TemplateFolder = "ld_template";
//	for( int i=0; i<10; i++ )
//	{
//		ostringstream number;
//		number << i;
//		string template_file = TemplateFolder + '\\' +  number.str() + "_template.mfc";
//		//cout<<template_file<<endl;
//		NFTemplate[i] = ReadHtk( template_file, TemplateVectors[i] );
//	}
//	
//	/*----------------��ȡ�������ݲ��ֱ���ģ�����ƥ��---------------*/
//	string *fileInfos = new string [100];
//	int nfiles = get_strs_from_file( TestFileList, fileInfos ); // ��ȡ�����ļ��б�����fileInfos����
//	float TestVector[MAXNFRAME+1][DVECTOR+1]; // �洢test��֡����
//	int NFTest = 0; // �洢test��֡��
//	for( int j=1; j<=nfiles; j++ )
//	{
//		float re = 0;
//		int k = 1;
//		float result = 1e+38f; //��ʾ������ 
//		NFTest = ReadHtk( fileInfos[j], TestVector );
//		for( int i=0; i<10; i++ )
//		{// ����������������10��ģ�����ƥ�䣬��¼ƥ�������С����һ��
//			re = Run_DTW( TemplateVectors[i], NFTemplate[i], TestVector, NFTest );
//			if( result > re )
//			{
//				result = re; 
//				k = i;
//			}
//		}
//		cout << fileInfos[j] << '\t' << k << endl;
//		if(j % 4 == 0)
//			cout<<endl;
//	}
//	delete [] fileInfos;
//}





void main( int argc, char *argv[] )
{
	//if(1 == argc)
	//{
	//	cout << "USAGE:\t TestFileList \n";
	//	exit(-1);
	//}

	//string TestFileList = argv[1]; // test list ���������б�

	//string TestFileList("test_filelist.txt");  //�γ̲�������
	string TestFileList("myTestFileList.txt"); //�Լ���������
	
	string TemplateFolder("template");  //�γ�ģ��
	//string TemplateFolder("myTemplate"); //�Լ�ģ��

	cout<<"ģ���ļ���"<<TemplateFolder<<endl;
	cout<<"�����ļ���"<<TestFileList<<endl;

	/*----------------��ȡģ������---------------------*/
	
	for( int i=0; i<10; i++ )
	{
		ostringstream number;
		number << i;
		string template_file = TemplateFolder + '\\' +  number.str() + "_template.mfc";
		NFTemplate[i] = ReadHtk( template_file, TemplateVectors[i] );
	}

	/*----------------��ȡ�������ݲ��ֱ���ģ�����ƥ��---------------*/
	string *fileInfos = new string [100];
	int nfiles = get_strs_from_file( TestFileList, fileInfos ); // ��ȡ�����ļ��б�����fileInfos����
	float TestVector[MAXNFRAME+1][DVECTOR+1]; // �洢test��֡����
	int NFTest = 0; // �洢test��֡��
	int identifyNum = 0;
	for( int j = 1; j <= nfiles; j ++ )
	{
		float re = 0;
		int k = 1;
		float result = 1e+38f; //��ʾ������ 
		NFTest = ReadHtk( fileInfos[j], TestVector );
		for( int i = 0; i < 10; i ++ )
		{// ����������������10��ģ�����ƥ�䣬��¼ƥ�������С����һ��
			re = Run_DTW( TemplateVectors[i], NFTemplate[i], TestVector, NFTest );
			if( result > re )
			{
				result = re; 
				k = i;
			}
		}

		if ( (j-1) % 4 == 0)
		{
			cout<<"ʶ������  "<< identifyNum <<"  �����"<<endl;
			identifyNum ++;
		}
		cout << fileInfos[j] << '\t' << k << endl;
	}
	delete [] fileInfos;
}
