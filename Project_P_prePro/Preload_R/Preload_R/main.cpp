#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define SLEN 20
using namespace std;
#include <fstream>
char *pool;
struct HASH_VALUE
{
    long long seg1,seg2;
};
struct Info
{
    HASH_VALUE id, ads_id, pos_id, ip_id;//16bytes HASH value
    int lang;//en OR zh , 0->zh, 1->en
    char OS_info[SLEN];//whose length is unknown
    long timeStamp;//Unix Time stamp
    int stable, click;//is stable , is clicked
};
Info *seq;
const long cache_size = 1100000000;
long frame_size = 0;

int main(int argc, char *argv[])
{
    pool = new char[cache_size];
    seq = new Info[cache_size];
    memset(seq, 0, sizeof(Info)*frame_size);
    
    string fn(argv[1]);
    string fnout(argv[2]);
    fstream fin(fn, ios::in|ios::binary);
    ofstream fout(fnout);
    
    //get the size of the file
    fin.seekg(0, fin.end);
    frame_size = fin.tellg();
    fin.seekg(0, fin.beg);
    cout<<"frame size : "<<frame_size<<endl;
    
    //parsing string
    char numberParsing[12]={0};
    fin.read(pool, frame_size);
    
    char *head=pool;
    int i = 0;
    for (i=0; head - pool <= frame_size; i++)
    {
        if(i==10000000)break;
        //id stable ads pos os lang ip time click
        Info &it = seq[i];
        
        //the first 16 bytes to id
        memcpy(&it.id, head, 16);
        //to get rid of the comma
        head+=17;
        //transform char '1' to (int)1
        it.stable = *head-'0';
        
        head+=2;
        memcpy(&it.ads_id, head, 16); head+=17;
        memcpy(&it.pos_id, head, 16); head+=17;
        //parsing system info
        int j=0; char c;
        while (c = *head, c!=',')
        {
            it.OS_info[j++] = c;
            head++;
        }
        
        //parsing language
        head++;
        if (*head <='z' && *head >= 'a')
        {
            it.lang = *head -'a' +1;
            head +=3;
        }
        else if (*head <='Z' && *head >= 'A')
        {
            it.lang = *head -'A' +1 + 26;
            head +=3;
        }
        else if (*head == ',')
        {
            it.lang = 0;
            head++;
        }
        else if(*head == -17)
        {
            cout << "Invalid character found in data but we ignored it" <<endl;
            it.lang = -1;
            head +=4;
        }
        else
        {
            cout<<"exp in lang "<<i<<' '<<*head<<endl;
            cout<<(int)*head<<endl;
            //return 0;
        }
        
        memcpy(&it.ip_id, head, 16);
        
        head+=17;
        memcpy(numberParsing, head, 10);
        it.timeStamp=atoi(numberParsing);
        
        head+=11;
        it.click = *head-'0';
        
        head+=3;
    }
    
    fout.write((char *)seq, sizeof(Info)*i);
    cout<<"wrote "<<i<<" records"<<endl;
    fin.close();
    fout.close();
    delete []seq;
    delete []pool;
    return 0;
}

