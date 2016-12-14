#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int randInt() {
    int fd = open("/dev/random", O_RDONLY);
    int buffer;
    
    read(fd, &buffer, 4);
    close(fd);
    
    return buffer;
}

int main() {
    umask(0000);
    int fd = open("numbers", O_CREAT | O_WRONLY, 0644);
    int arr[10];
    int arr2[10];

    printf("Generating random numbers: \n");
    for (int i = 0 ; i < 10 ; i++) {
        arr[i] = randInt();
        write(fd, arr + i, sizeof(int));
        printf("\trandom %d: %d \n", i, arr[i]);
    }

    printf("\nWriting to file...\n");
    //side note: i wrote to it earlier
    close(fd);

    printf("Reading from file...\n\n");
    //side note: i read later
    fd = open("numbers", O_RDONLY);

    printf("Verification that written values were the same: \n");
    for (int i = 0 ; i < 10 ; i++) {
        read(fd, arr2 + i, sizeof(int));
        printf("\trandom %d: %d \n", i, arr2[i]);
    }

    close(fd);

    return 0;
}
