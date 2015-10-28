#include<iostream>
using namespace std;

#include <math.h>

#define PI 3.14159265

//bool bHasInit = false;
//double* C;
//void initDCTParam(int deg)
//{
//	// deg ΪDCT�任���ݳ��ȵ���
//
//	if(bHasInit)
//	{
//		return; //�����ټ�����ұ�
//	}
//
//	int total, halftotal, i, group, endstart, factor;
//
//	total = 1 << deg;
//
//	if(C != NULL) delete []C;
//
//	C = (double *)new double[total];
//
//	halftotal = total >> 1;
//
//	for(i=0; i < halftotal; i++)
//		C[total-i-1]=(double)(2*i+1);
//
//	for(group=0; group < deg-1; group++)
//	{ 
//
//		endstart=1 << (deg-1-group);
//
//		int len = endstart >> 1;
//
//		factor=1 << (group+1);
//
//		for(int j = 0;j < len; j++)
//			C[endstart-j-1] = factor*C[total-j-1];
//	}
//
//	for(i=1; i < total; i++)
//		C[i] = 2.0*cos(C[i]*PI/(total << 1)); ///C[0]���ţ�ûʹ��
//
//	bHasInit=true;
//}
////ǰ��׷��
//void dct_forward(double *f,int deg)
//{
//	// f�д洢DCT����
//
//	int i_deg, i_halfwing, total, wing, wings, winglen, halfwing;
//
//	double temp1,temp2;
//
//	total = 1 << deg;
//
//	for(i_deg = 0; i_deg < deg; i_deg++)
//	{
//		wings = 1 << i_deg;
//		winglen = total >> i_deg;
//		halfwing = winglen >> 1;
//		for(wing = 0; wing < wings; wing++)
//		{
//			for(i_halfwing = 0; i_halfwing < halfwing; i_halfwing++)
//			{
//				temp1 = f[wing*winglen+i_halfwing];
//				temp2 = f[(wing+1)*winglen-1-i_halfwing];
//				if(wing%2)
//					swap(temp1,temp2); // ����temp1��temp2��ֵ
//				f[wing*winglen+i_halfwing] =
//					temp1+temp2;
//				f[(wing+1)*winglen-1-i_halfwing] = 
//					(temp1-temp2)*
//					C[winglen-1-i_halfwing];
//			}
//		}
//	}
//}
//
////����ظ�
//void dct_backward(double *f,int deg)
//{
//	// f�д洢DCT����
//
//	int total,i_deg,wing,wings,halfwing,winglen,i_halfwing,
//		temp1,temp2;
//
//	total = 1 << deg;
//	for(i_deg = deg-1; i_deg >= 0; i_deg--)
//	{
//		wings = 1 << i_deg;
//		winglen = 1 << (deg-i_deg);
//
//		halfwing = winglen >> 1;
//
//		for(wing = 0; wing < wings; wing++)
//		{
//			for(i_halfwing = 0; i_halfwing < halfwing; i_halfwing++)
//			{  
//				//f[i_halfwing+wing*winglen] = f[i_halfwing+wing*winglen];
//				if(i_halfwing == 0)
//				{
//					f[halfwing+wing*winglen+i_halfwing] = 
//						0.5*f[halfwing+wing*winglen+i_halfwing];
//				}
//				else
//				{
//					temp1=bitrev(i_halfwing,deg-i_deg-1);   // bitrevΪλ����
//					temp2=bitrev(i_halfwing-1,deg-i_deg-1); // ��һ����ΪҪ�任����
//					// �ڶ�����Ϊ�����Ƴ���
//					f[halfwing+wing*winglen+temp1] =
//						f[halfwing+wing*winglen+temp1]-f[halfwing+wing*winglen+temp2];
//				}     
//			}
//		}
//	}
//}
//
////λ����������
//int bitrev(int bi,int deg)
//{    
//	int j = 1, temp = 0, degnum, halfnum;
//
//	degnum = deg;
//
//	//if(deg<0) return 0;
//
//	if(deg == 0) return bi;
//
//	halfnum = 1 << (deg-1);
//
//	while(halfnum)
//	{            
//		if(halfnum&bi)
//			temp += j;
//
//		j<<=1;
//
//		halfnum >>= 1;
//	}
//
//	return temp;
//}
//
//void fdct_1D_no_param(double *f,int deg)
//{
//	initDCTParam(deg);
//	dct_forward(f,deg);
//	dct_backward(f,deg);
//	bitrev(*f,deg);     // ʵ��λ��������
//	f[0] = 1/(sqrt(2.0))*f[0];
//}
//
//void fdct_1D(double *f,int deg)
//{
//	fdct_1D_no_param(f,deg);
//	int total = 1 << deg;
//	double param = sqrt(2.0/total);
//	for(int i = 0; i < total; i++)
//		f[i] = param*f[i];
//}
//
//void fdct_2D(double *f,int deg_row,int deg_col)
//{    
//	int rows,cols,i_row,i_col;
//	double two_div_sqrtcolrow;
//	rows=1 << deg_row;
//	cols=1 << deg_col;
//	init2D_Param(rows,cols);
//	two_div_sqrtcolrow = 2.0/(sqrt(double(rows*cols)));  
//
//	for(i_row = 0; i_row < rows; i_row++)
//	{
//		fdct_1D_no_param(f+i_row*cols,deg_col);
//	}
//
//	for(i_col = 0; i_col < cols; i_col++)
//	{
//		for(i_row = 0; i_row < rows; i_row++)
//		{
//			temp_2D[i_row] = f[i_row*cols+i_col];
//		}
//
//		fdct_1D_no_param(temp_2D, deg_row);
//
//		for(i_row = 0; i_row < rows; i_row++)
//		{
//			f[i_row*cols+i_col] = temp_2D[i_row]*two_div_sqrtcolrow;
//		}          
//	}
//
//	bHasInit = false;
//}
