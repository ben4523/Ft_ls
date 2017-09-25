/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:19:06 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 12:40:00 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*ft_ls_times_l(time_t times)
{
	time_t			now;
	char			*date;

	time(&now);
	date = ft_strdup(ctime(&times) + 4);
	if (ft_abs(now - times) > 15552000)
	{
		date[7] = ' ';
		ft_memmove(date + 8, date + 16, 4);
	}
	date[12] = 0;
	return (date);
}

int					ft_ls_type_files(struct stat sb)
{
	if (sb.st_mode & S_IFDIR)
		return (1);
	else if (sb.st_mode & S_IFREG)
		return (2);
	else if (sb.st_mode & S_IFLNK)
		return (3);
	else if (sb.st_mode & S_IFMT)
		return (4);
	else if (sb.st_mode & S_IFSOCK)
		return (5);
	else if (sb.st_mode & S_IFBLK)
		return (6);
	else if (sb.st_mode & S_IFCHR)
		return (7);
	else if (sb.st_mode & S_IFIFO)
		return (8);
	else
		return (0);
}

char				*ft_ls_permisson(struct stat sb)
{
	char			*s;

	s = malloc(sizeof(char *) * 10 + 1);
	s = NULL;
	if (S_ISDIR(sb.st_mode))
		s = ft_strjoin_free(s, "d", 1);
	else if (S_ISLNK(sb.st_mode))
		s = ft_strjoin_free(s, "l", 1);
	else if (S_ISSOCK(sb.st_mode))
		s = ft_strjoin_free(s, "s", 1);
	else if (S_ISBLK(sb.st_mode))
		s = ft_strjoin_free(s, "b", 1);
	else if (S_ISCHR(sb.st_mode))
		s = ft_strjoin_free(s, "c", 1);
	else if (S_ISFIFO(sb.st_mode))
		s = ft_strjoin_free(s, "p", 1);
	else
		s = ft_strjoin_free(s, "-", 1);
	s = ft_strjoin_free(s, (sb.st_mode & S_IRUSR) ? "r" : "-", 1);
	s = ft_strjoin_free(s, (sb.st_mode & S_IWUSR) ? "w" : "-", 1);
	if (sb.st_mode & S_ISUID)
		s = ft_strjoin_free(s, (S_IXUSR & sb.st_mode) ? "s" : "S", 1);
	else
		s = ft_strjoin_free(s, (sb.st_mode & S_IXUSR) ? "x" : "-", 1);
	return (ft_ls_permisson_suite(sb, s));
}

char				*ft_ls_permisson_suite(struct stat sb, char *s)
{
	s = ft_strjoin_free(s, (sb.st_mode & S_IRGRP) ? "r" : "-", 1);
	s = ft_strjoin_free(s, (sb.st_mode & S_IWGRP) ? "w" : "-", 1);
	if (sb.st_mode & S_ISGID)
		s = ft_strjoin_free(s, (S_IXGRP & sb.st_mode) ? "s" : "S", 1);
	else
		s = ft_strjoin_free(s, (sb.st_mode & S_IXGRP) ? "x" : "-", 1);
	s = ft_strjoin_free(s, (sb.st_mode & S_IROTH) ? "r" : "-", 1);
	s = ft_strjoin_free(s, (sb.st_mode & S_IWOTH) ? "w" : "-", 1);
	if (sb.st_mode & S_ISVTX)
		s = ft_strjoin_free(s, (S_IXOTH & sb.st_mode) ? "t" : "T", 1);
	else
		s = ft_strjoin_free(s, (sb.st_mode & S_IXOTH) ? "x" : "-", 1);
	s = ft_strjoin_free(s, "\0", 1);
	return (s);
}

char				*get_name_link(char *chemin, struct stat sb,
						struct dirent *lu)
{
	ssize_t			r;
	ssize_t			bufsiz;
	char			*linkname;
	char			*final;

	bufsiz = sb.st_size + 1;
	if (sb.st_size == 0)
		bufsiz = 4000;
	linkname = malloc(bufsiz);
	if (linkname == NULL)
		ft_ls_basicerror("ls: ", linkname, 0);
	r = readlink(chemin, linkname, bufsiz);
	if (r == -1)
		ft_ls_basicerror("ls: ", "readlink", 0);
	linkname[r] = '\0';
	final = ft_strjoin(lu->d_name, " -> ");
	final = ft_strjoin_free(final, linkname, 3);
	return (final);
}
