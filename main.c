//version 1.1

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define HELP_TXT "hexdiff v1.0\nUsage: hexdiff <file1> <file2>\n"

bool check(int argc, char *argv[])
{
    if(argc != 3)
    {
        return false;
    }

    return true;
}

int fsize(FILE *fp)
{
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}

struct fl {
    int a;
};

int main(int argc, char *argv[])
{
    if (!check(argc, argv))
    {
        printf(HELP_TXT);
        return 0;
    }

    const char *fname1 = argv[1];
    const char *fname2 = argv[2];

    FILE *f1 = fopen(fname1, "rb");
    FILE *f2 = fopen(fname2, "rb");

    if (f1 == NULL || f2 == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    const unsigned long fsize1 = fsize(f1);
    const unsigned long fsize2 = fsize(f2);

    unsigned char *data1;
    unsigned char *data2;

    data1 = (char*) malloc(fsize1 * sizeof(char));
    data2 = (char*) malloc(fsize2 * sizeof(char));


    if(fsize1 == fsize2)
    {
        for ( int i = 0 ; i < fsize1 ; i++ ) 
        {
            fread(&data1[i], sizeof(data1[i]), 1, f1);
            fread(&data2[i], sizeof(data2[i]), 1, f2);
        }

        for (int i = 0; i < fsize1; i++)
        {
            if (data1[i] != data2[i])
            {
                printf("%08X: %02X %02X\n", i, data1[i], data2[i]);
            }
        }
        fclose(f1);
    }

    if(fsize1 < fsize2)
    {
        for ( int i = 0 ; i < fsize1 ; i++ ) 
        {
            fread(&data1[i], sizeof(data1[i]), 1, f1);
        }

        for ( int i = 0 ; i < fsize2 ; i++ )
        {
            fread(&data2[i], sizeof(data2[i]), 1, f2);
        }

        for (int i = 0; i < fsize1; i++)
        {
            if (data1[i] != data2[i])
            {
                printf("%08X: %X %X\n", i, data1[i], data2[i]);
            }
        }

        printf("add %d bytes in %s:\n", fsize2 - fsize1, fname2);
        for (int i = fsize1; i < fsize2; i++)
        {
            printf("%08X: %X\n", i, data2[i]);
        }

    }

    return 0;
}