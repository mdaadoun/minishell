/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:54:43 by pi                #+#    #+#             */
/*   Updated: 2022/07/14 11:35:18 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

// LIBFT
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_atoi(const char *nptr);
int				ft_isspace(int c);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
size_t			ft_char_in_set(char c, char const *set);

// LIST
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// LIST
typedef struct s_list_str
{
	char				*str;
	struct s_list_str	*next;
}	t_list_str;

t_list			*ft_lstnew(void *content);
t_list_str		*ft_lstnew_str(char *str);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_back_str(t_list_str **lst, t_list_str *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
t_list_str		*ft_lstlast_str(t_list_str *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstdelone_str(t_list_str *lst, void (*del) \
(char *));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstclear_str(t_list_str **lst, void (*del)(char *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del) \
(void *));

// DOUBLE LIST

typedef struct s_double_list
{
	int						value;
	struct s_double_list	*prev;
	struct s_double_list	*next;
}	t_double_list;

void			ft_dlstadd_back(t_double_list *lst, t_double_list *new);
t_double_list	*ft_dlstnew(int value);
t_double_list	*ft_dlstlast(t_double_list *lst);

// PRINTF
int				ft_printf(const char *format, ...);
int				ft_strlen_pf(const char *s);
int				ft_putchar_pf(char c, int *len);
int				ft_putstr_pf(char *s, int *len);
int				ft_putnbr_pf(int n, int *len);
int				ft_putpointer_pf(void *pointer, int base, int *len);
int				ft_putbase_pf(size_t nb, int base, bool uppercase, int *len);

// GNL
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024

char			*get_next_line(int fd);
size_t			eol_or_length(const char *str, int ignore);
void			*ft_memcpy_gnl(void *dest, const void *src, size_t n);
char			*ft_strjoin_gnl(char const *s1, char const *s2);
char			*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char			*free_and_return(char **storage, char **line, char **buffer);

#endif