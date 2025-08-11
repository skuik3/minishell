/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:24:03 by skuik             #+#    #+#             */
/*   Updated: 2025/08/11 09:54:48 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_list_gnl
{
	char				*str_buf_g;
	struct s_list_gnl	*next_gnl;
}				t_list_gnl;

int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);

int			ft_tolower(int c);
int			ft_toupper(int c);
size_t		ft_strlen(const char *str);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);

void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strdup(const char *s1);
void		*ft_calloc(size_t count, size_t size);

char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *left_str, char *buff);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int			f_nline(t_list_gnl *list_gnl);
t_list_gnl	*f_last_node(t_list_gnl *s_list_gnl);
char		*get_line(t_list_gnl *list_gnl);
void		copy_str(t_list_gnl *s_list_gnl, char *str);
int			len_to_nline(t_list_gnl *s_list_gnl);
void		polish_list(t_list_gnl **s_list_gnl);
char		*get_next_line(int fd);
void		dealloc(t_list_gnl **list_gnl, t_list_gnl *clean_node, char *buf);
void		make_list(t_list_gnl **list_gnl, int fd);

#endif