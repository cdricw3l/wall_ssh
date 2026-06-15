#include "wall_ssh.h"

int get_fd(char *pts)
{
    int fd;

    fd = open(pts, O_RDWR);
    if(fd < 1)
    {
        perror("open");
        return (-1);
    }
    return(fd);
}

int check_pts_name(char *pts)
{
    while (*pts)
    {
        if(!isdigit(*pts))
            return(ERR);
        pts++;
    }
    return (OK);
}

int exec_prog(int fd)
{
    pid_t f;
    int status;

    f = fork();
    if(f < 0)
    {
        perror("fork");
        return(ERR);
    }
    if(f == 0)
    {
        dup2(fd, STDOUT_FILENO);
	write(fd, "\n", 1);
        char *arg[] = {"monitoring", NULL};
        if(execve(SCRIPT_PATH, arg, NULL) < 0)
        {
            perror("Excve");
            exit(errno);
        }
    }
    waitpid(f, &status, 0);
    return (OK);
}


int main(void)
{   
    DIR *dir;
    int i;
    struct dirent *d;
    char **arr;
    int fd;

    dir = opendir(PATH);
    if(!dir)
    {
        perror("open_dir");
        return (1);
    }
    i = 0;
    arr = malloc(sizeof(char *) * 512);
    if(!arr)
        return (1);
    while ((d = readdir(dir)) != NULL)
    {
        if(check_pts_name(d->d_name) == OK)
            arr[i++] = ft_strjoin(PATH,d->d_name);
    }
    arr[i] = NULL;
    closedir(dir);
    i = 0;
    while (arr[i])
    {
        fd = get_fd(arr[i]);
        if(fd < 0)
        {
            printf("ERROR\n");
            ft_split_clean(&arr);
            return (ERR);        
        }
        exec_prog(fd);
        write(fd, "\n", 1);
        close(fd);
        free(arr[i]);
        i++;
    }
    free(arr);
    return (0);
}
