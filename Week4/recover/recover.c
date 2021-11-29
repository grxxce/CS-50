#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    // Check the num arguments accepted
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file 
    char *in_file_name = argv[1];
    FILE *in_file  = fopen(in_file_name, "r");

    if (in_file == NULL)
    {
        printf("Could not open the file.\n");
        return 1;
    }

    BYTE buffer[512]; // Create a buffer array as unsigned char to store 512-byte blocks
    int image_num = 0; // Create an image number counter
    char file_name[8]; // Store name of to-be generated JPEGs
    FILE *out_file = NULL; // Initiate an output file to write to

    //Read new file in in 512-chunk bytes into buffer
    while (fread(&buffer, 512, 1, in_file))
    {
        // Use if statements to see if the file meets JPEG criteria, if so, start new JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close if this is not the first
            if (!(image_num == 0))
            {
                fclose(out_file);
            }
            
            // Write to a JPEG with the file name 3 digits
            sprintf(file_name, "%03i.jpg", image_num);

            // Open output file
            out_file = fopen(file_name, "w");

            // // Write to out file
            // fwrite(buffer, sizeof(buffer), 1, out_file);
            image_num++;
        }

        if (!(image_num == 0))
        {
            fwrite(&buffer, 512, 1, out_file);
        }
    }
    fclose(out_file);
    fclose(in_file);

    return 0;
}