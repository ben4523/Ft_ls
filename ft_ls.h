/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:39:32 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 13:50:03 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <pwd.h>
# include <time.h>
# include <grp.h>
# include "libft/ft_printf.h"

typedef struct		s_lsl
{
	char			*name;
	char			*permis;
	long			links;
	char			*owner;
	char			*group;
	long long		octets;
	long long		blocks_size;
	time_t			times_last_modif;
	time_t			times_last_acces;
	time_t			times_last_change;
	char			*times;
	int				type;
	char			*chemin;
	struct s_lsl	*next;
}					t_lsl;

typedef struct		s_ls
{
	unsigned int	flags;
	int				argc;
	char			**argv;
	int				argv_i;
	t_lsl			*first;
	t_lsl			*first_arg;
	t_lsl			*erorrs;
	int				numarg;
	int				pos;
}					t_ls;

typedef struct		s_size
{
	int				link_size;
	int				owner_size;
	int				group_size;
	int				octets_size;
	long long		total;
}					t_size;

# define FLAG_LV	0x00000001
# define FLAG_R		0x00000002
# define FLAG_A		0x00000004
# define FLAG_RR	0x00000008
# define FLAG_T		0x00000010
# define FLAG_F		0x00000040

void				*ft_ls_basicerror(char *name, char *error, int ex);
void				ft_ls_error_arg(char arg);
void				affichage_error_arg_lst(t_ls *ls);
t_lsl				*add_error_arg_lst(t_ls *ls, char *s);
void				listeinit(t_ls *ls, int argc, char **argv);
t_lsl				*ft_ls_delete_list(t_lsl *list);
int					ft_ls_pars(t_ls *ls);
void				ft_ls_pars_flags(t_ls *ls, int v);
void				ft_ls_pars_files(t_ls *ls);
void				ft_ls_pars_files_suite(t_ls *ls, int i);
void				ft_ls_pars_files_suite1(t_ls *ls, int i, t_lsl *tmp);
t_lsl				*put_in_list_first(t_ls *ls);
t_lsl				*put_in_list_first_suite(t_ls *ls, t_lsl *list,
												struct stat sb);
void				put_in_list_first_s1(t_lsl *list, struct stat sb);
t_lsl				*put_in_list(struct dirent *lu, t_lsl *list_off,
									t_ls *ls, char *chemin);
t_lsl				*put_in_list_suite(t_lsl *list, char *chemin,
										t_ls *ls, struct dirent *lu);
char				*get_name_link(char *chemin, struct stat sb,
										struct dirent *lu);
int					count_t_lsl(t_lsl *list);
char				*get_real_name(char *str);
char				*ft_ls_get_chemin(char *chemin, char *name);
char				*ft_ls_permisson(struct stat sb);
char				*ft_ls_permisson_suite(struct stat sb, char *s);
char				*ft_ls_times_l(time_t times);
int					ft_ls_type_files(struct stat sb);
int					affichageargg(t_ls *ls, char *chemin);
int					calc_size(t_lsl *list, char *champ);
long long			calc_total_blocks(t_lsl *list);
void				list_size_init(t_size *size_list, t_lsl *list);
int					space_one(int max_size, int space, int num_size);
void				affichagebig_l(t_lsl *list);
void				affichagebig_l_suite(t_lsl *list, t_size sizel, int i);
void				affichagebig_file_l(t_lsl *list);
int					affichagebig(t_ls *ls, t_lsl *list);
int					affichagebig_file(t_ls *ls, t_lsl *list);
void				ft_ls_open(t_ls *ls, char *chemin, char *name);
void				ft_ls_open_suite(t_ls *ls, char *chemin, t_lsl *list_cpy);
int					flag_sort(t_lsl **list_off, t_ls *ls);
t_lsl				*ft_ls_list_add(t_lsl *list_off, t_lsl *list);
void				help_sort(t_lsl **nd, t_lsl **nxt,
								t_lsl **prev, int *done);
void				ft_sort_folders_files(t_lsl **lst);
void				ft_sort_ascii(t_lsl **lst);
void				ft_sort_flag_t(t_lsl **lst);
void				reverse_list(t_lsl **ls);
#endif
