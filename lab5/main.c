#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    #define FILENAME "lab5.txt"
    #define FILENAMEWRITE "lab5_result.txt"
    #define FILENAMEB "lab5_result_bin.bin"  // константa для запису та читання бінарних даних for write bin file and next read him

    FILE *ptr_file_source_arg;
    FILE *ptr_file_txt_dest;
    FILE *ptr_file_bin_dest;
    FILE *ptr_file_bin_source;

    unsigned int n;
    double x1, x2, delta, x;
    char group_shyfr[10];
    group_shyfr[9] = '\0';
    char student_name[30];
    student_name[29] = '\0';
    char line1[25];

    double f(double x)
        {
            return (x - 50)*cos(x/10) - 3*x + 500;
        }

    if ((ptr_file_source_arg = fopen(FILENAME, "r"))!=0) {
        fscanf(ptr_file_source_arg, "%lf", &x1);
        fscanf(ptr_file_source_arg, "%lf", &x2);
        fscanf(ptr_file_source_arg, "%u", &n);
        fscanf(ptr_file_source_arg, "%lf", &delta);
        fscanf(ptr_file_source_arg, "%s", &group_shyfr);
        fscanf(ptr_file_source_arg, "%s", &student_name);
        fclose(ptr_file_source_arg);
       } else {printf("Error! File cannot be opened (source file)");
       return 0;
       }
    printf("GROUP: %s, ", group_shyfr);
    printf("STUDENT: %s\n\n", student_name);
    printf("X1=%lf, ", x1);
    printf("X2=%lf, ", x2, "\n");
    printf("delta=%lf \n", delta, "\n");

    printf("\noverall points: %u\n\n", n);

     if ((ptr_file_txt_dest = fopen(FILENAMEWRITE, "w"))!=0) {

        for(int i=1; i<=25; i++)
            {printf("**");
            fprintf(ptr_file_txt_dest, "**"); }

        printf("\n*\tN\t*\tX\t*\tF(X)\t*\n");
        fprintf(ptr_file_txt_dest, "\n*\tN\t*\tX\t*\tF(X)\t*\n");

        for(int i=1; i<=25; i++)
            {printf("**");
            fprintf(ptr_file_txt_dest, "**");}
        printf("\n");
        fprintf(ptr_file_txt_dest, "\n");
        x = x1;
        for(unsigned int k=1; k<=n; k++)
            {
            printf("+---------------+---------------+----------------+");
            fprintf(ptr_file_txt_dest, "+---------------+---------------+----------------+");


            printf("\n|\t%8u|\t%8.4lf|\t%9.4lf|\n", k, x, f(x));
            fprintf(ptr_file_txt_dest, "\n|\t%8u|\t%8.4lf|\t%9.4lf|\n", k, x, f(x));

            x += delta;
            if (k%10 == 0)
                {
                printf("\nPress Any Key to Continue ...\n");
                getch();
                }
            }

        for(int i=1; i<=25; i++)
                {printf("--");
                fprintf(ptr_file_txt_dest, "--");}

        fprintf(ptr_file_txt_dest, "\n");
        fprintf(ptr_file_txt_dest, "GROUP: %s, ", group_shyfr);
        fprintf(ptr_file_txt_dest, "STUDENT: %s\n", student_name);

        fclose(ptr_file_txt_dest);
       } else {printf("Error! File cannot be writed (result file)");
       return 0;
      }


    if ((ptr_file_bin_dest = fopen(FILENAMEB, "wb"))!=0) {

            fwrite(&n, sizeof n, 1, ptr_file_bin_dest );
            x = x1;
            double func;
            for(unsigned int i=1; i<=n; i++)
                {

                    fwrite(&x, sizeof x, 1, ptr_file_bin_dest );
                    func = f(x);
                    fwrite(&func, sizeof func, 1, ptr_file_bin_dest );

                    x += delta;
                }
            fclose(ptr_file_bin_dest);
    } else {printf("Error! File cannot be writed (binary result file)");
       return 0;
      }


    if ((ptr_file_bin_source = fopen(FILENAMEB, "rb"))!=0) {

            unsigned int Size;

            fread(&Size, sizeof Size, 1, ptr_file_bin_source );
            printf("\nRead binary file, overall points: %u\n\n", Size);

            const int cols = 2, rows = Size;
            double ** matrix= (double**) malloc (sizeof (double*) * cols);
            for (int i = 0; i < cols; i++)
                {matrix[i] = (double*) malloc (sizeof (double)*rows );}

            for(int i=1; i<=25; i++)
                {printf("**");}

            printf("\n*\tN\t*\tX\t*\tF(X)\t*\n");

            for(int i=1; i<=25; i++)
                {printf("**");}

            printf("\n");

            for(unsigned int i=1; i<=Size; i++)
                {
                    fread(&matrix[0][i], sizeof matrix[0][i], 1, ptr_file_bin_source );
                    fread(&matrix[1][i], sizeof matrix[1][i], 1, ptr_file_bin_source );
                    printf("+---------------+---------------+----------------+");
                    printf("\n|\t%8u|\t%8.4lf|\t%9.4lf|\n", i, matrix[0][i], matrix[1][i]);

                    if (i%10 == 0)

                        {
                        printf("\nPress Any Key to Continue ...\n");
                        getch();
                        }
                }

            for(int i=1; i<=25; i++)
                {printf("--");}

                 clearMemory ( matrix,  Size);

            fclose(ptr_file_bin_source);
    } else {printf("Error! File cannot be read (binary result file)");
       return 0;
      }

    printf("\n\nAll done! Lab number %d \n", 5);

    return 0;
}
//--------------------------------------------------------------------------------------------------------

void  clearMemory ( double ** matrix,  unsigned int rows )
{
    unsigned int i;
    for( i = 0;  i < rows;  i++ )
    {
        free( matrix[ i ] );
    }
    free( matrix );
}

//--------------------------------------------------------------------------------------------------------
