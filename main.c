/*
Copyright (C) 2023 Nikolai Serafimovich
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define HELP_TXT "hexdiff v1.3\nUsage: hexdiff <file1> <file2>\n"
#define FILE_OPEN_ERROR "Error while opening the file.\n"

#define PRINT_DOUBLE_HEX "%08X: %02X %02X\n"
#define PRINT_SINGLE_HEX "%08X: %02X\n"

bool check_arg(int argc, char *argv[])
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

struct file {
    char *name;
    unsigned long size;
    FILE *file;
};

int main(int argc, char *argv[])
{
    if (!check_arg(argc, argv))
    {
        printf(HELP_TXT);
        return 0;
    }

    struct file f_a;
    struct file f_b;

    f_a.name = argv[1];
    f_b.name = argv[2];

    f_a.file = fopen(f_a.name, "rb");
    f_b.file = fopen(f_b.name, "rb");

    if (f_a.file == NULL || f_b.file == NULL)
    {
        perror(FILE_OPEN_ERROR);
        exit(EXIT_FAILURE);
    }

    f_a.size = fsize(f_a.file);
    f_b.size = fsize(f_b.file);

    if(f_a.size == f_b.size)
    {
        for ( int i = 0 ; i < f_a.size; i++ )
        {
            unsigned char data[2];

            fread(&data[0], 1, 1, f_a.file);
            fread(&data[1], 1, 1, f_b.file);

            if (data[0] != data[1])
            {
                printf(PRINT_DOUBLE_HEX, i, data[0], data[1]);
            }
        }

        fclose(f_a.file);
        fclose(f_b.file);
    }

    if(f_a.size > f_b.size)
    {
        for ( int i = 0 ; i < f_b.size; i++ )
        {
            unsigned char data[2];

            fread(&data[0], 1, 1, f_a.file);
            fread(&data[1], 1, 1, f_b.file);

            if (data[0] != data[1])
            {
                printf(PRINT_DOUBLE_HEX, i, data[0], data[1]);
            }
        }
        printf("%lu more bytes in %s:\n", f_a.size - f_b.size, f_a.name);
        for (int i = f_b.size; i < f_a.size; i++)
        {
            unsigned char data;

            fread(&data, 1, 1, f_a.file);
            printf(PRINT_SINGLE_HEX, i, data);
        }

        fclose(f_a.file);
        fclose(f_b.file);
    }

    if(f_a.size < f_b.size)
    {
        for ( int i = 0 ; i < f_a.size; i++ )
        {
            unsigned char data[2];

            fread(&data[0], 1, 1, f_a.file);
            fread(&data[1], 1, 1, f_b.file);

            if (data[0] != data[1])
            {
                printf(PRINT_DOUBLE_HEX, i, data[0], data[1]);
            }
        }
        printf("%lu more bytes in %s:\n", f_b.size - f_a.size, f_b.name);
        for (int i = f_a.size; i < f_b.size; i++)
        {
            unsigned char data;

            fread(&data, 1, 1, f_b.file);
            printf(PRINT_SINGLE_HEX, i, data);
        }

        fclose(f_a.file);
        fclose(f_b.file);
    }

    return 0;
}
