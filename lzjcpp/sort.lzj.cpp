#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct User
{
	char userId[18];
	char webId[18];
}user[4346947 + 5];

bool operator<(const User & a, const User & b)
{
	int res1 = strcmp(a.webId,b.webId);
	if(res1 != 0)
		return res1 < 0;
	else
		return strcmp(a.userId,b.userId) < 0;
}

int main()
{
	freopen("clicked","r",stdin);
	freopen("out.txt","w",stdout);

	int cnt = 0;
	while(scanf("%s%s",user[cnt].userId,user[cnt].webId) != EOF)
		cnt++;
	
	sort(user,user+cnt);

	for(int i = 0; i < cnt; i++)
		printf("%s %s\n",user[i].webId,user[i].userId);

	return 0;
}