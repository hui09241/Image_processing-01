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
    int figure[512][512];
    int **new_figure;
    new_figure = new int*[512];
    for(int i=0;i<512;i++)
    {
        new_figure[i]= new int[512];
    }
    int **edgeimg;
    edgeimg = new int*[512];
    for(int i=0;i<512;i++)
    {
        edgeimg[i]= new int[512];
    }
    unsigned int header[1078];
    int Pixelcounter=0,TH,x;
    long long int summ;
    file = fopen("LENNA (1).bmp", "rb");
    filein = fopen("LENNA_mar.bmp", "wb");
    for(int i=0;i<1078;i++)
    {
        header[i] = fgetc(file);
        fputc(header[i], filein);
    }
    for(int i=0;i<512;i++)
    {
        for(int j=0;j<512;j++)
        {
            figure[i][j] = fgetc(file);
            new_figure[i][j] = figure[i][j];
            edgeimg[i][j] = figure[i][j];
        }
    }
    for(int i=2;i<510;i++)
    {
        for(int j=2;j<510;j++)
        {
            new_figure[i][j] = figure[i][j]*16-figure[i][j-1]*2-figure[i][j+1]*2-figure[i-1][j]*2-figure[i+1][j]*2-figure[i-1][j-1]-figure[i-1][j+1]-figure[i+1][j-1]-figure[i+1][j+1]-figure[i][j-2]-figure[i][j+2]-figure[i-2][j]-figure[i+2][j];
        }
    }
    summ = 0;
    for(int i=1;i<511;i++)
    {
        for(int j=1;j<511;j++)
        {
            Pixelcounter++;
            summ = summ + abs(new_figure[i][j]);
        }
    }
    TH = 2*(summ/Pixelcounter);
    for(int i=0;i<510;i++)


    {
        for(int j=0;j<510;j++)
        {
            edgeimg[i+1][j+1] = 255 ;
            if(((new_figure[i][j+1]>=0)&&(new_figure[i+2][j+1]<=0))&&((new_figure[i][j+1])-new_figure[i+2][j+1]>=TH))
               {
                   edgeimg[i+1][j+1] = 0;
                   continue;
               }
            if(((new_figure[i][j+1]<=0)&&(new_figure[i+2][j+1]>=0))&&((new_figure[i+2][j+1])-new_figure[i][j+1]>=TH))
               {
                   edgeimg[i+1][j+1] = 0;
                   continue;
               }
            if(((new_figure[i+1][j]>=0)&&(new_figure[i+1][j+2]<=0))&&((new_figure[i+1][j])-new_figure[i+1][j+2]>=TH))
               {
                   edgeimg[i+1][j+1] = 0;
                   continue;
               }
            if(((new_figure[i+1][j]>=0)&&(new_figure[i+1][j+2]<=0))&&((new_figure[i+1][j+2])-new_figure[i+1][j]>=TH))
               {
                   edgeimg[i+1][j+1] = 0;
                   continue;
               }
        }
    }
    for(int i=0;i<512;i++)
    {
        for(int j=0;j<512;j++)
        {
            fputc(edgeimg[i][j], filein);
        }
    }
    fclose(filein);
    fclose(file);
    delete [] new_figure;
    delete [] edgeimg;
    return 0;
}
