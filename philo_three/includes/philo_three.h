/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/31 12:04:08 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:25:20 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <sys/time.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <string.h>
# include <signal.h>

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
	sem_t				*forks;
	sem_t				*death;
	sem_t				*print;
	sem_t				*eat;
	int					pid;
}						t_data;

void					init(int argc, char **argv, t_data *guys);
int						sem_management(t_data *guys);
void					parse(int argc, char **argv);
unsigned long int		get_time(t_data *guy);
int						destroy(t_data *guys, pthread_t *newthread);
int						ft_atoi(const char *str);
int						message(int message, t_data *guy);
void					sleeeep(int time_to_sleep);
int						go_sleep(t_data *guy);
int						eat_or_die(t_data *guy, int nb);
int						eat(t_data *guy);
int						message(int message, t_data *guy);
int						ft_isdigit(int c);
void					join_and_wait(t_data *guys, int i);

#endif
