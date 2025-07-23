/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:30:24 by odana             #+#    #+#             */
/*   Updated: 2025/07/23 14:53:24 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long long		start_time;
	int				simulation_end;
	int				competing_philos;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating_permission;
	pthread_mutex_t	death;
	pthread_mutex_t	log;
	pthread_mutex_t	meal;
	pthread_t		monitor_thread;
}	t_data;

// philosopher actions

int			philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

// cleanup functions

void		cleanup_mutexes(t_data *data, int count);
void 		cleanup_resources(t_data *data);

// utility functions

long long	get_timestamp(void);
long long	get_elapsed_time(t_data *data);
void		precise_sleep(int duration_ms);
void		safe_log(t_data *data, int philo_id, char *message);
int			ft_atoi(char *str);
// parsing and initialization

int			validate_arguments(int argc, char **argv);
t_data		*parse_arguments(int argc, char **argv);
int			allocate_philos(t_data *data);
void		initialize_philosophers(t_data *data);
int			initialize_mutexes(t_data *data);

// fork management

int			take_forks(t_philo *philo);
void		release_forks(t_philo *philo);

// routine and permissions

void		*philosopher_routine(void *arg);
int			request_eating_permission(t_philo *philo);
void		release_eating_permission(t_philo *philo);

// monitoring functions

void		*death_monitor(void *arg);
int			check_last_meal(t_data *data);
int			check_meal_count(t_data *data);

// thread creation and management

int			start_simulation(t_data *data);
void 		wait_for_completion(t_data *data);

#endif