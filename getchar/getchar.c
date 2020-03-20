#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>

extern FILE *stdin;
static int m_termiosTcMode = TCSADRAIN;
static struct termios default_termios;

void tty_set_raw_mode(FILE* istream)
{
    struct termios new_termios;
    int fd = fileno(istream);
    int status;

    status = tcgetattr(fd, &new_termios);
    new_termios.c_iflag = 0;
    new_termios.c_oflag = OPOST | ONLCR;
    new_termios.c_lflag = 0;
    new_termios.c_cc[VMIN] = 1;

    new_termios.c_cc[VTIME] = 0;
    /* Do the mode switch */
    status = tcsetattr(fd, m_termiosTcMode, &new_termios);
    /* status = tcsetattr(fd, TCSANOW, &new_termios); */
}
void tty_restore_mode(FILE* istream)
{
    int fd = fileno(istream);
    //struct termios default_termios;
    /* Do the mode switch */
    (void)tcsetattr(fd, TCSANOW, &default_termios);
    /* (void)tcsetattr(fd, TCSANOW, &this->default_termios); */
/*  printf ("Restore terminal mode\n");*/
}

int tinyrl_getchar(FILE *istream)
{
    unsigned char c;
    int istream_fd;
    ssize_t res;

    istream_fd = fileno(istream);

    /* Just wait for the input if no timeout */
    while (((res = read(istream_fd, (char*)&c, 1)) < 0) &&
            (EAGAIN == errno));
    /* EOF or error */
    if (res < 0)
        return -1;
    if (!res)
        return -2;
    return c;
}

int main(void) {   
    FILE* istream = fdopen(dup(fileno(stdin)), "r");
    int fd = fileno(istream);
    tcgetattr(fd, &default_termios);
    tty_set_raw_mode(istream);

    while (1) {
        int key = -1;
        /* get a key */
        key = tinyrl_getchar(istream);
        if (key > 0){
            if (key == '?'){
                //printf("Help");
                printf("Help\n");
            }
            else if (key == 'q')
            {
                tty_restore_mode(istream);
                break;
            }
            else {
                //printf("%c", key);
                if (key == 8 || key == 127)
                    printf("%c[%dD", 27, 1);
                    //printf("Help1");
                else if (key > 31)
                    printf("%c", key);
                printf("%c[J", 27);
                fflush(stdout);
            }
        }
        else {
            printf("Err\n");
        }
    }
    printf("\n");
    return 0;
}
