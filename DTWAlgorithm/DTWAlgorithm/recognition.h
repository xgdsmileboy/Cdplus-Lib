float distance_matrix[ MAXNFRAME+1 ][ MAXNFRAME+1 ]; // 存储距离矩阵
float distortion_matrix[ MAXNFRAME+1 ][ MAXNFRAME+1 ]; // 存储距离累加矩阵

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

float CalculateDistance( float Vector1[], float Vector2[] ) // Note: 需要自行编写
{// 计算向量间欧氏距离
		float dDistance = 0.0f; //保存两个向量之间的距离信息

		for(int i = 1; i <= DVECTOR; i++)
		{
			dDistance += pow(Vector1[i] - Vector2[i],2);  //循环计算两向量对应点之间距离平方值并求和
		}

		return sqrt(dDistance);  //返回欧式距离：平方和开方
}

float Run_DTW( float TemplateV[][DVECTOR+1], int NFTemplate, float TestV[][DVECTOR+1], int NFTest )  // Note: 需要自行编写
{
	float D[MAXNFRAME + 1][MAXNFRAME + 1];//D 则是处于最优时间规整条件下的向量累积距离
	float D1,D2,D3;
	float max = 100000.0f;
	float min;
	for(int i = 0; i < MAXNFRAME + 1; i++)  //初始化D矩阵
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
			*  选择(i-1,j),(i-1,j-1),(i,j-1)这三个点中有最小累加距离的点作为前向点
			*  计算公式：
			*  D(i,j) = d(T(i), R(j)) + min{D(i-1, j), D(i-1, j-1), D(i, j-1)}
			*/
			D1 = D[i-1][j];
			D2 = D[i-1][j-1];
			D3 = D[i][j-1];
			min = D1 < (D2 < D3 ? D2 : D3) ? D1 : (D2 < D3 ? D2 : D3); //取三者中的最小值
			D[i][j] = CalculateDistance(TestV[i],TemplateV[j]) + min;//帧间距离与最小累加距离之和
		}
	}
	return D[NFTest][NFTemplate]; // 返回测试数据和模板数据之间的累加距离和
}