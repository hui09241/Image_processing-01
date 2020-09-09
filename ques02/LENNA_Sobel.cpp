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
    unsigned int **new_figure;
    new_figure = new unsigned int*[512];
    for(int i=0;i<512;i++)
    {
        new_figure[i]= new unsigned int[512];
    }
    unsigned int header[1078];
    int x,y,total;
    file = fopen("LENNA (1).bmp", "rb");
    filein = fopen("LENNA_Sobel.bmp", "wb");
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
        }
    }
    for(int i=1;i<511;i++)
    {
        for(int j=1;j<511;j++)
        {
            y = figure[i-1][j-1]*-1 + figure[i-1][j]*-2 + figure[i-1][j+1]*-1 + figure[i+1][j-1] + figure[i+1][j]*2 + figure[i+1][j+1];
            x = figure[i-1][j-1]*-1 + figure[i-1][j+1] + figure[i][j-1]*-2 + figure[i][j+1]*2 + figure[i+1][j-1]*-1 + figure[i+1][j+1];
            total = abs(x)+abs(y);
            if(total > 80)
            {
                new_figure[i][j] = 255;
            }
            else
            {
                new_figure[i][j] = 0;
            }
        }
    }
    for(int i=0;i<512;i++)
    {
        for(int j=0;j<512;j++)
        {
             fputc(new_figure[i][j], filein);
        }
    }
    fclose(filein);
    fclose(file);
    delete [] new_figure;
    return 0;
}

