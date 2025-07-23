/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:34:13 by odana             #+#    #+#             */
/*   Updated: 2025/07/23 13:49:12 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void *philosopher_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		philo_think(philo);
		usleep(1000);
	}
	while (!philo->data->simulation_end)
	{
		if (philo->data->meals_required != -1 && 
		philo->meals_eaten >= philo->data->meals_required)
			break ;
		// SYNCHRONIZATION POINT 1: Request permission to compete for forks
		if (!request_eating_permission(philo))
		{
		    philo_think(philo);
		    continue ;
		}
		// SYNCHRONIZATION POINT 2: Try to get both forks and eat
		if (!philo_eat(philo))
		{
		    release_eating_permission(philo);
		    break ; // Simulation ended during eating attempt
		}
		release_eating_permission(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int request_eating_permission(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->eating_permission);
    if (philo->data->simulation_end)
	{
        pthread_mutex_unlock(&philo->data->eating_permission);
        return 0;
    }
    if (philo->data->competing_philos >= philo->data->num_philos - 1)
	{
        pthread_mutex_unlock(&philo->data->eating_permission);
        return 0;
    }
    philo->data->competing_philos++;
    pthread_mutex_unlock(&philo->data->eating_permission);
    return (1); 
}

void release_eating_permission(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->eating_permission);
    philo->data->competing_philos--;
    pthread_mutex_unlock(&philo->data->eating_permission);
}
