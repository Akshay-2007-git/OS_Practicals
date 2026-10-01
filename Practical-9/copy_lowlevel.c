#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 8192

int main(int argc, char *argv[])
{
    int src_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    /* Open source file */
    src_fd = open(argv[1], O_RDONLY);

    if (src_fd == -1)
    {
        perror("open source");
        return 1;
    }

    /* Open/create destination file */
    dest_fd = open(argv[2],
                   O_WRONLY | O_CREAT | O_TRUNC,
                   0644);

    if (dest_fd == -1)
    {
        perror("open destination");
        close(src_fd);
        return 1;
    }

    /* Copy file */
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0)
    {
        char *ptr = buffer;
        ssize_t remaining = bytes_read;

        /*
         * write() may write fewer bytes than requested,
         * so continue until the entire buffer is written.
         */
        while (remaining > 0)
        {
            bytes_written = write(dest_fd, ptr, remaining);

            if (bytes_written == -1)
            {
                if (errno == EINTR)
                {
                    continue;
                }

                perror("write");
                close(src_fd);
                close(dest_fd);
                return 1;
            }

            ptr += bytes_written;
            remaining -= bytes_written;
        }
    }

    if (bytes_read == -1)
    {
        perror("read");
        close(src_fd);
        close(dest_fd);
        return 1;
    }

    /*
     * lseek() demonstration:
     * Move to the end of the source file and obtain its size.
     */
    off_t file_size = lseek(src_fd, 0, SEEK_END);

    if (file_size == (off_t)-1)
    {
        perror("lseek");
    }
    else
    {
        printf("Source file size: %lld bytes\n",
               (long long)file_size);
    }

    close(src_fd);
    close(dest_fd);

    printf("File copied successfully.\n");

    return 0;
}
