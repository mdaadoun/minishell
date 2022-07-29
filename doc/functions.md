
## Fonction autorisées
* **readline** : Get a line from a user with editing. [man](https://www.man7.org/linux/man-pages/man3/readline.3.html)
* **rl_clear_history**
* **rl_on_new_line**
* **rl_replace_line**
* **rl_redisplay**
* **add_history** : *void add_history (const char* **string)* Place string at the end of the history list. [man](https://www.man7.org/linux/man-pages/man3/history.3.html)
* **printf**
* **malloc**
* **free**
* **write**
* **access**
* **open**
* **read**
* **close**
* **fork**
* **wait**
* **waitpid**
* **wait3**
* **wait4**
* **signal**
* **sigaction**
* **sigemptyset**
* **sigaddset**
* **kill**
* **exit** : Close the current program and return it's parameter to parent program. [man](https://man7.org/linux/man-pages/man2/execve.2.html)
* **getcwd**
* **chdir**
* **stat**
* **lstat**
* **fstat**
* **unlink**
* **execve** : Execute program passed in pathname. Close the current program. [man](https://man7.org/linux/man-pages/man2/execve.2.html)
* **dup** : Create a redicrection to the smallest fd possible. [man](https://man7.org/linux/man-pages/man2/dup.2.html)
* **dup2** : Create a redirection newfd to oldfd. [man](https://man7.org/linux/man-pages/man2/dup.2.html) 
* **pipe** : Take int[2] in parameter and link to it the read end and write end fd. [man](https://man7.org/linux/man-pages/man2/pipe.2.html) 
* **opendir** : Return a pointer to the directory stream name passed in parameter. [man](https://man7.org/linux/man-pages/man3/opendir.3.html) 
* **readdir** : Function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp. [man](https://man7.org/linux/man-pages/man3/readdir.3.html)
* **closedir** : Function close directory stream associated with Dirp. [man](https://man7.org/linux/man-pages/man3/closedir.3.html)
* **strerror** : Return a pointer to a string describing the code errno passed in parameter. [man](https://man7.org/linux/man-pages/man3/strerror.3.html)
* **perror** : Produce a error message on standart error (fd: 2) producing by multiple function library. [man](https://man7.org/linux/man-pages/man3/sys_nerr.3.html)
* **isatty** :
* **ttyname** :
* **ttyslot** :
* **ioctl** : [man](https://man7.org/linux/man-pages/man2/ioctl.2.html)
* **getenv** : Return a pointer to environement variable passed in parameter.  [man] (http://manpagesfr.free.fr/man/man3/getenv.3.html)
* **tcsetattr**
* **tcgetattr**
* **tgetent**
* **tgetflag**
* **tgetnum**
* **tgetstr**
* **tgoto**
* **tputs**
