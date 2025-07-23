/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:29:58 by odana             #+#    #+#             */
/*   Updated: 2025/07/21 23:28:52 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	validate_arguments(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: Argument %d must be a positive integer\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

t_data	*parse_arguments(int argc, char **argv)
{
	t_data	*data;

	if (!validate_arguments(argc, argv))
		return (NULL);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	data->simulation_end = 0;
	data->competing_philos = 0;
	data->start_time = 0;
	return (data);
}

int	allocate_philos(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (free(data->philos), 0);
	return (1);
}

int	initialize_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (cleanup_mutexes(data, i), 0);
		i++;
	}
	if (pthread_mutex_init(&data->permission, NULL) != 0
		|| pthread_mutex_init(&data->death, NULL) != 0
		|| pthread_mutex_init(&data->log, NULL) != 0
		|| pthread_mutex_init(&data->meal, NULL) != 0)
		return (cleanup_mutexes(data, data->num_philos), 0);
	return (1);
}

void	initialize_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
}
