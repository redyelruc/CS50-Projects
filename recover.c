#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for the existence of a filename
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    // check if memory card is successfully opened
    FILE *open_file = fopen(argv[1], "r");
    if (open_file == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        return 1;
    }

    //create variables for the filename and a pointer towards assigned memory
    FILE *img;
    char filename[7];
    unsigned char *block = malloc(512);
    int file_counter = 0;
    while (fread(block, 512, 1, open_file))
    {
        // if start of new jpeg
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // close previous jpg file if it exists
            if (file_counter != 0)
            {
                fclose(img);
            }
            // create new filename
            sprintf(filename, "%03d.jpg", file_counter);
            // open the new image file
            img = fopen(filename, "w");
            // check if successful
            if (img == NULL)
            {
                fclose(open_file);
                free(block);
                fprintf(stderr, "Could not create output JPG %s", filename);
                return 3;
            }
            file_counter++;
        }
        // make sure we have found the first file
        if (file_counter != 0)
        {
            //write the block to the file
            fwrite(block, 512, 1, img);
        }
    }

}
