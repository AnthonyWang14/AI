#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;
int board[9][9];
int havePut;
int needPut;
char *outfilename;
bool inpos(int num, int x, int y) 
{
	if (num > 9 && num < 1)
		return false;
	int hang = x/3;
	int lie = y/3;
	for (int i = 0; i < 9; i++)
		if (i != x && board[i][y] == num)
			return false;

	for (int j = 0; j < 9; j++) 
		if (j != y && board[x][j] == num)
			return false;

	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			if (i+hang*3 != x || j+lie*3 != y) 
			{
				if (board[i+hang*3][j+lie*3] == num)
					return false;
			}
		}
	}
	return true;
}
void dfs(int p)
{
	int x = p/9;
	int y = p%9;
	for (int i = 1; i < 10; i++) 
	{
		if (inpos(i, x, y))
		{
			board[x][y] = i;
			++havePut;
			if (havePut == needPut)
			{
				fstream output(outfilename, ios::app);
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
						cout << board[i][j];
					cout << endl;
				}
				return;
			}
			else 
			{
				for (int k = p+1; k < 9*9; ++k) 
				{
					if (!board[k/9][k%9]) 
					{
						dfs(k);
						break;
					}
				}
			}
			board[x][y] = 0;
			--havePut;
			return;
		}
	}
	return;
}

int main(int argc, char const *argv[]) 
{
	outfilename = (char*)argv[2];
	havePut = 0;
	needPut = 0;
	fstream input;
	input.open(argv[1],ios::in);
	if (!input) 
	{
		cout << "input error" << endl;
		return 0;
	}
	memset(board, 0, sizeof(board));
	string temp;
	for (int i = 0; i < 9; i++) 
	{
		input >> temp;
		for (int j = 0; j < 9; j++) 
		{
			board[i][j] = (int)(temp[j]-'0');
			if (!board[i][j])
				needPut++;
		}
	}
	for (int k = 0; k < 9*9; ++k) 
	{
		if (!board[k/9][k%9]) 
		{
			dfs(k);
			break;
		}
	}
	// for (int i = 0; i < 9; i ++) 
	// {
	// 	for (int j = 0; j < 9; j++) 
	// 	{
	// 		if (board[i][j] == 0) 
	// 		{
	// 			putNum(1,i,j);
	// 		}
	// 	}
	// }
	input.close();
	return 0;
}