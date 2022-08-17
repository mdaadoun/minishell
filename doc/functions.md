
## Fonction autorisées

### readline and history library functions
* **readline** : 
```c
char *readline (const char *prompt);
```
> Get a line from a user with editing. [man](https://www.man7.org/linux/man-pages/man3/readline.3.html)
* **rl_clear_history**
* **rl_on_new_line**
* **rl_replace_line**
* **rl_redisplay**
* **add_history** : 
```c
void add_history (const char* **string)
```
> Place string at the end of the history list. [man](https://www.man7.org/linux/man-pages/man3/history.3.html)

### basic functions

* **printf**
* **malloc**
* **free**

* **write**
* **access**
* **open**
* **read** : 
```c
ssize_t read(int fildes, void *buf, size_t nbyte);
```
> attempt to read nbyte bytes from the       file associated with the open file descriptor. [man](https://man7.org/linux/man-pages/man2/read.2.html)
* **close**

### fork

* **fork**
* **wait**
* **waitpid**
* **wait3**
* **wait4**

### signal functions

* **signal**
> [man](https://man7.org/linux/man-pages/man7/signal.7.html)
* **sigaction**
> [man](https://man7.org/linux/man-pages/man2/sigaction.2.html)
* **sigemptyset**
* **sigaddset**
> Add a signal to the signal mask. [info](https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-sigaddset-add-signal-signal-mask) - [man](https://linux.die.net/man/3/sigaddset)
* **kill**


* **exit** : 
> Close the current program and return it's parameter to parent program. [man](https://man7.org/linux/man-pages/man2/execve.2.html)


* **getcwd** : 
```c
char *getcwd(char *buf, size_t size);
```
> Return a null-terminated string containing an absolute pathname that is the current working directory of the calling process. [man](https://www.man7.org/linux/man-pages/man3/getcwd.3.html)
* **chdir** : change working directory.

* **stat** : display file or file system status
* **lstat** : get file status 
* **fstat** : get file status

* **unlink** : delete a name and possibly the file it refers to

* **execve** : 
> Execute program passed in pathname. Close the current program. [man](https://man7.org/linux/man-pages/man2/execve.2.html)
* **dup** : 
> Create a redirection to the smallest fd possible. [man](https://man7.org/linux/man-pages/man2/dup.2.html)
* **dup2** : 
> Create a redirection newfd to oldfd. [man](https://man7.org/linux/man-pages/man2/dup.2.html) 
* **pipe** : 
> Take int[2] in parameter and link to it the read end and write end fd. [man](https://man7.org/linux/man-pages/man2/pipe.2.html) 
* **opendir** : 
> Return a pointer to the directory stream name passed in parameter. [man](https://man7.org/linux/man-pages/man3/opendir.3.html) 
* **readdir** : 
> Function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp. [man](https://man7.org/linux/man-pages/man3/readdir.3.html)
* **closedir** : 
> Function close directory stream associated with Dirp. [man](https://man7.org/linux/man-pages/man3/closedir.3.html)

### Error

* **errno list** : [man](https://man7.org/linux/man-pages/man3/errno.3.html)

* **strerror** : 
> Return a pointer to a string describing the code errno passed in parameter. [man](https://man7.org/linux/man-pages/man3/strerror.3.html)
* **perror** : 
> Produce a error message on standart error (fd: 2) producing by multiple function library. [man](https://man7.org/linux/man-pages/man3/sys_nerr.3.html)

### Terminal functions

* **isatty** :
> test whether a file descriptor refers to a terminal. [man](https://man7.org/linux/man-pages/man3/isatty.3.html)
* **ttyname** : 
> return name of a terminal. [man](https://www.man7.org/linux/man-pages/man3/ttyname.3.html)
* **ttyslot** :
> find the slot of the current user's terminal in some file. [man](https://man7.org/linux/man-pages/man3/ttyslot.3.html)
* **ioctl** : 
> control device. [man](https://man7.org/linux/man-pages/man2/ioctl.2.html)
* **getenv** : 
> Return a pointer to environment variable passed in parameter. [man](http://manpagesfr.free.fr/man/man3/getenv.3.html)
* **tcsetattr**
* **tcgetattr**
* **tgetent**
* **tgetflag**
* **tgetnum**
* **tgetstr**
* **tgoto**
* **tputs**
