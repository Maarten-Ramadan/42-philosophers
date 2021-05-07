/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/31 12:04:08 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:29:35 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_struct
{
	int					nb;
	unsigned long int	time_stamp;
	unsigned long int	start_time;
	int					total;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					limit;
	int					eat_count;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*print;
	pthread_mutex_t		*eat;
	int					*death;
}						t_data;

int						init(int argc, char **argv, t_data *guys, int i);
int						parse(int argc, char **argv);
unsigned long int		get_time(t_data *guys);
void					destroy(t_data *guys, pthread_t *newthread);
int						ft_atoi(const char *str);
int						message(int message, t_data *guy);
void					sleeeep(int time_to_sleep);
int						go_sleep(t_data *guy);
bool					check_deaths(t_data *guy);
int						eat_or_die(t_data *guy, int nb);
int						eat(t_data *guy);
int						mutex_management(t_data *guys, int i);

#endif
