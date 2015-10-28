float distance_matrix[ MAXNFRAME+1 ][ MAXNFRAME+1 ]; // �洢�������
float distortion_matrix[ MAXNFRAME+1 ][ MAXNFRAME+1 ]; // �洢�����ۼӾ���

int get_strs_from_file( string filename, string strs[] )
{
	ifstream fin( filename.c_str() );
	if( !fin )
	{
		cout << "file read error!" << endl;
		exit(-1);
	}

	int nstr=1;
	while( !fin.eof() )
	{
		getline( fin, strs[nstr++] );
	}
	fin.close();

	while( "" == strs[nstr-1] )nstr--;

	return nstr-1;
}

float CalculateDistance( float Vector1[], float Vector2[] ) // Note: ��Ҫ���б�д
{// ����������ŷ�Ͼ���
		float dDistance = 0.0f; //������������֮��ľ�����Ϣ

		for(int i = 1; i <= DVECTOR; i++)
		{
			dDistance += pow(Vector1[i] - Vector2[i],2);  //ѭ��������������Ӧ��֮�����ƽ��ֵ�����
		}

		return sqrt(dDistance);  //����ŷʽ���룺ƽ���Ϳ���
}

float Run_DTW( float TemplateV[][DVECTOR+1], int NFTemplate, float TestV[][DVECTOR+1], int NFTest )  // Note: ��Ҫ���б�д
{
	float D[MAXNFRAME + 1][MAXNFRAME + 1];//D ���Ǵ�������ʱ����������µ������ۻ�����
	float D1,D2,D3;
	float max = 100000.0f;
	float min;
	for(int i = 0; i < MAXNFRAME + 1; i++)  //��ʼ��D����
	{
		D[0][i] = max;
		D[i][0] = max;
	}
	D[0][0] = 0.0f;
	for(int i = 1; i <= NFTest; i++)
	{
		for(int j = 1; j <= NFTemplate; j++)
		{
			/*
			*  ѡ��(i-1,j),(i-1,j-1),(i,j-1)��������������С�ۼӾ���ĵ���Ϊǰ���
			*  ���㹫ʽ��
			*  D(i,j) = d(T(i), R(j)) + min{D(i-1, j), D(i-1, j-1), D(i, j-1)}
			*/
			D1 = D[i-1][j];
			D2 = D[i-1][j-1];
			D3 = D[i][j-1];
			min = D1 < (D2 < D3 ? D2 : D3) ? D1 : (D2 < D3 ? D2 : D3); //ȡ�����е���Сֵ
			D[i][j] = CalculateDistance(TestV[i],TemplateV[j]) + min;//֡���������С�ۼӾ���֮��
		}
	}
	return D[NFTest][NFTemplate]; // ���ز������ݺ�ģ������֮����ۼӾ����
}