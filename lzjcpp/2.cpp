#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main()
{
	string fn1 = "out.txt"; //
	string fn2 = "pos_all.txt";       //所有条目
	FILE *f1 = fopen(fn1.c_str(),"r");
	FILE *f2 = fopen(fn2.c_str(),"r");
	// freopen("handin.txt","w",stdout);

	char all[18];
	char web[18], user[18];

	fscanf(f1,"%s%s",web,user);

	while(fscanf(f2,"%s",all) != EOF)
	{
		printf("%s",all);
		if(strcmp(web,all) == 0)
		{
			printf(",%s",user);
			while(fscanf(f1,"%s%s",web,user),!feof(f1))
			{
				if(strcmp(web,all) != 0)
					break;
				printf(",%s",user);
			}
		}
		printf("\n");
	}

	return 0;
}