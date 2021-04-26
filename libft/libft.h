/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 23:17:50 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 23:17:53 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ntsid.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
void	*ft_memset (void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
int		*ft_memcpy (void *dest, const void *src, size_t num);
void	*ft_memccpy(void *dst, const void *src, int ch, size_t num);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *string, int character);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t num);
int		ft_strncmp(const char *s1, const char *s2, size_t num);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(char *s, int c);
void	*ft_calloc (size_t count, size_t size);
char	*ft_strdup(const char *string);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
