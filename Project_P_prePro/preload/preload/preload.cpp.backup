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
const long cache_size = 1000000000;
const long frame_size = cache_size/sizeof(Info);
const long frame_Number = 1; //num / frame_size;

int main()
{
    pool = new char[cache_size];
    seq = new Info[frame_size];
    memset(seq, 0, sizeof(Info)*frame_size);
    
    //Trying read in fstream
    fstream fin("train.data");
    ofstream fout("preprocessed.data");
    
    //parsing string
    char numberParsing[12]={0};
    for (int frame=0; frame<frame_Number; frame++)
    {
        
        fin.read(pool, cache_size);
        char *head=pool;
        for (int i=0; i<frame_size; i++)
        {
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
            else if (*head == ',')
            {
                it.lang = 0;
                head++;
            }
            else
            {
                cout<<"exp in lang "<<i<<' '<<*head<<endl;
                return 0;
            }
            
            memcpy(&it.ip_id, head, 16);
            
            head+=17;
            memcpy(numberParsing, head, 10);
            it.timeStamp=atoi(numberParsing);
            
            head+=11;
            it.click = *head-'0';
            
            head+=2;
        }
        fout.write((char *)seq, sizeof(Info)*frame_size);
    }
    fin.close();
    fout.close();
    delete []seq;
    delete []pool;
    cout<<frame_size<<" records"<<endl;
    return 0;
}
	
