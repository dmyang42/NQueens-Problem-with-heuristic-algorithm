#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <cstdlib>
#include <fstream>
#include <random>
#include <stdio.h>
#include <time.h>
using namespace std;

const unsigned N = 80;

int print_queen_seq(vector<int> queen_seq)
{
    /*��ӡvector queen_seq*/
    for(int i = 0; i < N; ++i)
    {
        cout << queen_seq[i] <<" ";
    }
    cout << endl;
    return 0;
}

int random_start(vector<int> &queen_seq)
{
    /*�������*/
    for(int i = 0; i < N; ++i)
    {
        queen_seq[i] = rand() % N;
    }
    //print_queen_seq(queen_seq);
    return 0;
}

int find_queen_to_move(vector<int> queen_seq)
{
    /*�ҵ�ÿ���ʺ�ġ���ͻ���������س�ͻ�����Ļʺ�*/
	vector<int> hf(N, 0);
	vector<int> line(N, 0);
	vector<int> l_slope(2 * N - 1, 0);
	vector<int> r_slope(2 * N - 1, 0);
	int largest = 0;
    int ig = 0;

	for(int i = 0; i < N; ++i)
    {
        ++line[queen_seq[i]];
        ++l_slope[queen_seq[i] + i];
        ++r_slope[queen_seq[i] - i + N - 1];
    }//3n
    for(int i = 0; i < N; ++i)
    {
        hf[i] = hf[i] + line[queen_seq[i]] - 1 + l_slope[queen_seq[i] + i] + r_slope[queen_seq[i] - i + N - 1] -2;
    }//n
    for(int i = 0; i < N; ++i)
	{
		if(largest < hf[i])
		{
			largest = hf[i];
			ig = i;
		}
	}//n
    return ig;
}//5n

int get_conflict_num(vector<int> queen_seq, int spec_queen)
{
    int conflict_num = -1;
    for(int i = 0; i < N; ++i)
    {
        if(queen_seq[i] == queen_seq[spec_queen] || i + queen_seq[i] == spec_queen + queen_seq[spec_queen] || i - queen_seq[i] == spec_queen - queen_seq[spec_queen])
        {
            ++conflict_num;
        }
    }
    return conflict_num;
}

int find_aim_position(vector<int> queen_seq, int spec_queen)
{
	/*����ĳһ�ض��У��ҵ�����7�ֱ仯��H��С��һ��*/
	int dir_pos = 0;
	int min = INT_MAX;
	vector<int> temp(N, 0);
	int l,m,r;
	
	for (int i = 0; i < N; ++i) {
		if (i != spec_queen) {
			m = queen_seq[i];
			l = m - (i - spec_queen);
			r = m + (i - spec_queen);
			++temp[m];
			if (l >= 0 && l < N) {
				++temp[l];
			}
			if (r >= 0 && r < N) {
				++temp[r];
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		if (min > temp[i]) {
			dir_pos = i;
			min = temp[i];
		}
	}
	return dir_pos;
}

int queen()
{
    /*һ�Ρ���ɽ��*/
	vector<int> queen_seq(N, 0);
	int queen_to_move;
	int aim_pos;
    int approach = 1;

	do
    {
        random_start(queen_seq);
        queen_to_move = find_queen_to_move(queen_seq);//�ҵ���hf���Ļʺ���Ϊ��Ҫ�ƶ��Ļʺ�
        aim_pos = find_aim_position(queen_seq, queen_to_move);//�ҵ�����ʺ�Ӧ���ƶ�����λ��
        while(queen_seq[queen_to_move] != aim_pos)
        {
            queen_seq[queen_to_move] = aim_pos;
            queen_to_move = find_queen_to_move(queen_seq);
            aim_pos = find_aim_position(queen_seq, queen_to_move);
        }
        ++approach;
    }while(get_conflict_num(queen_seq, queen_to_move));
	return approach;
}

int main()
{
    int approach;
    int TIME = 0;
    clock_t start, stop;
    ofstream output_file("output_file.txt", ios::out | ios::trunc);

	srand((time(0)));
	for(int t = 0; t < 100; t++)//�����ҵ�100��ȫ�����Ž�
    {
        start = clock();
        approach = queen();
        stop = clock();

        output_file << "Approach" << approach << " : Derive global maxima, total time " << (double)(stop - start)/1000. << endl;//д������ļ�ÿ���ҵ��Ľ��ʱ��
        cout << t + 1 << " found.  used time : " << (double)(stop - start)/1000. << endl;//��ʾ����������ҵ���ĸ���
        cout << "used steps : " << approach << endl;
        TIME = TIME + stop - start;
    }
    output_file << "Average Time : " << (double)TIME / 100000.;//д������ļ�ƽ����ʱ
    output_file.close();
	return 0;
}

