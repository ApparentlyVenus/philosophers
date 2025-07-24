/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:52:48 by odana             #+#    #+#             */
/*   Updated: 2025/07/24 14:48:59 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (printf("Error creating philosopher thread %d\n", i + 1), 0);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, death_monitor, data) != 0)
		return (printf("Error creating death monitor thread\n"), 0);
	return (1);
}

void	wait_for_completion(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->monitor_thread, NULL);
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = parse_arguments(argc, argv);
	if (!data)
		return (1);
	if (!allocate_philos(data))
	{
		printf("Error: Memory allocation failed\n");
		return (free(data), 1);
	}
	if (!initialize_mutexes(data))
	{
		printf("Error: Mutex initialization failed\n");
		return (cleanup_resources(data), 1);
	}
	initialize_philosophers(data);
	if (!start_simulation(data))
		return (cleanup_resources(data), 1);
	wait_for_completion(data);
	cleanup_resources(data);
	return (0);
}
