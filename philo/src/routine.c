/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:48:08 by odana             #+#    #+#             */
/*   Updated: 2025/07/24 15:19:05 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
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
			break ;
		if (!philo_eat(philo))
			break ;
		philo_sleep(philo);
		if (philo->data->num_philos % 2 == 1)
			philo_think(philo);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal = get_time();
	safe_log(philo->data, philo->id, "is eating");
	pthread_mutex_unlock(&philo->data->meal);
	precise_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal);
	release_forks(philo);
	return (1);
}

void	philo_sleep(t_philo *philo)
{
	safe_log(philo->data, philo->id, "is sleeping");
	precise_sleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	safe_log(philo->data, philo->id, "is thinking");
	precise_sleep((philo->data->time_to_eat * 2)
		- philo->data->time_to_sleep, philo->data);
}
