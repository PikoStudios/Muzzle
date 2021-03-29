#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void help();
void update();
void config();
void error(char** args);

int main(int argc, char** argv)
{
    if (strcmp(argv[1], "help") == 0) help();
    else if (strcmp(argv[1], "update") == 0) update();
    else if (strcmp(argv[1], "config") == 0) config();
    else error(argv);
}

void help()
{
    printf("muz -\n\thelp - Help Screen\n\tupdate- Update Muzzle\n\tconfig - Configure muz cli");
}

void config()
{
    fflush(stdin);
    FILE *file;
    char *location;
    printf("Where is your installion of Muzzle located at?: ");
    gets(location);
    printf("Saving Config file");
    file = fopen("config.muz", "w");

    if (file == NULL)
    {
        fprintf(stderr, "\e[0;31mError:\e[0;37m muz: config.muz failed to open");
        exit(1);
    }

    fprintf(file, location);
    fclose(file);
}
void update()
{
    char cmd[365];
    char buff[255];
    FILE *file = fopen("config.muz", "r");
    fgets(buff, 255, file);
    sprintf(cmd, "git clone https://github.com/pikostudios/muzzle %s", buff);
    system(cmd);
    fclose(file);
}

void error(char** args)
{
    fprintf(stderr, "\e[0;31mError:\e[0;37m muz: %s is not a valid command. To see all commands run 'muz help'", args[1]);
    exit(1);
}