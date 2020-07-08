#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if ( argc < 4 ) {
        printf("Usage : %s <filename1> <filename2> ... <directory name>\n", argv[0]);
        return 0;
    }
    char buf[257];
    char bufPath[255];
    int len;
    int lastIndex = argc-1;

    FILE *fd, *dest;
    for( int i=1; i < lastIndex; i++){
        fd = fopen(argv[i], "r");
        if( fd == NULL ){
            printf("File Descriptor Error\n");
            return 0;
        }
        if( (strlen(argv[lastIndex]) + strlen(argv[i])) > 254){
            printf("<Warning about Buffer Overflow>\nArguments Length is Too Long\n");
            return 0;
        }
        memset(bufPath, 0, 255);
        memcpy(bufPath, argv[lastIndex], strlen(argv[lastIndex]));
        strcat(bufPath, "/");
        strncat(bufPath, argv[i], strlen(argv[i]));
        printf("%s\n",bufPath);
        dest = fopen(bufPath, "w");

        while ( (len =fread(buf, 1, 256, fd))  )
        {
            buf[len] = '\0';
            fwrite(buf, 1, len, dest);
            printf("Length : %d\n", len);
            printf("%s\n", buf);
        }
        fclose(dest);
        fclose(fd);
    }

    return 0;
}
