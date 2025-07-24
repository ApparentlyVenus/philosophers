/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:34:13 by odana             #+#    #+#             */
/*   Updated: 2025/07/24 13:54:01 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


void *philosopher_routine(void *arg)
{
	t_philo *philo;
	int		should_continue;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		philo_think(philo);
		usleep(1);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->death);
		should_continue = !philo->data->simulation_end;
		pthread_mutex_unlock(&philo->data->death);
		if (!should_continue)
			break;
		// if (philo->data->meals_required != -1 && 
		// philo->meals_eaten >= philo->data->meals_required)
		// 	break ;
		if (!philo_eat(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
		// if (philo->data->num_philos == 2)
		// {
		// 	if (!philo_eat(philo))
		// 		break;
		// 	philo_sleep(philo);
		// 	philo_think(philo);
		// }
		// else
		// {
		// 	if (!request_eating_permission(philo))
		// 	{
		// 	    philo_think(philo);
		// 	    continue ;
		// 	}
		// 	if (!philo_eat(philo))
		// 	{
		// 	    release_eating_permission(philo);
		// 	    break ;
		// 	}
		// 	release_eating_permission(philo);
		// 	philo_sleep(philo);
		// 	philo_think(philo);
		// }
	}
	return (NULL);
}

// int request_eating_permission(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data->eating_permission);
//     if (philo->data->simulation_end)
// 	{
//         pthread_mutex_unlock(&philo->data->eating_permission);
//         return 0;
//     }
//     if (philo->data->competing_philos >= philo->data->num_philos - 1)
// 	{
//         pthread_mutex_unlock(&philo->data->eating_permission);
//         return 0;
//     }
//     philo->data->competing_philos++;
//     pthread_mutex_unlock(&philo->data->eating_permission);
//     return (1); 
// }

// void release_eating_permission(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data->eating_permission);
//     philo->data->competing_philos--;
//     pthread_mutex_unlock(&philo->data->eating_permission);
// }
