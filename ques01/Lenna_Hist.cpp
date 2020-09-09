#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
using namespace std;
int main()
{
    FILE *file;
    FILE *filein;
    unsigned int figure[512][512];
    unsigned int header[1078];
    int origin[256];
    int new_o[256];
    int total=0;
    long double tmp;
    file = fopen("LENNA (1).bmp", "rb");
    filein = fopen("Lenna_Hist.bmp", "wb");
    for(int i=0;i<1078;i++)
    {
        header[i] = fgetc(file);
        fputc(header[i], filein);
    }
    for(int i=0;i<256;i++)
    {
        origin[i]=0;
    }
    for(int i=0;i<512;i++)
    {
        for(int j=0;j<512;j++)
        {
            figure[i][j] = fgetc(file);
            origin[figure[i][j]]++;
        }
    }
    for(int i=0;i<256;i++)
    {
        total=total+origin[i];
        tmp=round((((total*100)/(512*512))*255)/100);
        new_o[i]=tmp;
    }
    for(int i=0;i<512;i++)
    {
        for(int j=0;j<512;j++)
        {
            figure[i][j]=new_o[figure[i][j]];
        }
    }
    for(int i=0;i<512;i++)
    {
        for(int j=0;j<512;j++)
        {
            fputc(figure[i][j], filein);
        }
    }
    fclose(filein);
    fclose(file);
}
