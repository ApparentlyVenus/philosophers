/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:30:06 by odana             #+#    #+#             */
/*   Updated: 2025/07/23 14:00:21 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    if (philo->data->simulation_end) {
        pthread_mutex_unlock(philo->left_fork);
        return (0);
    }
    safe_log(philo->data, philo->id, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    if (philo->data->simulation_end) {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return (0);
    }
    safe_log(philo->data, philo->id, "has taken a fork");
    return (1);
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}