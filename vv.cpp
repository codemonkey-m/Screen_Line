#include <unistd.h> 
#include <sys/ioctl.h> 
#include <iostream>
#include <string.h>
using namespace std;

int get_screen_col(){
    if (isatty(STDOUT_FILENO) == 0)  
        exit(1);

    struct winsize size;  
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size)<0) 
    {
        perror("ioctl TIOCGWINSZ error");
        exit(1);
    }

    return size.ws_col;
}

int main(int argc, char** argv){
    char c = '*';
    if (argc >= 2){
        if(strcmp(argv[1], "help") == 0){
            cout << "接受一个字符,输出整行,以区分上下的输出." << endl;
            cout << "默认以*字符填充." << endl;
            exit(0);
        }
        c = argv[1][0];
    }

    int col = get_screen_col();
    for (int i = 0; i < col; ++i)
        cout << c;
    cout << endl;

    return 0; 
}