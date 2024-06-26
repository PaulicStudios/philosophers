/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:20:28 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 21:18:09 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_default_philo(t_info *info, t_philo **first,
							t_philo **prev, unsigned int millis)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!*first)
		*first = philo;
	if (!philo)
		return (ft_error("malloc failed", *first), NULL);
	if (*prev)
		(*prev)->next = philo;
	philo->time_last_meal = millis;
	philo->nbr_meals = 0;
	philo->info = info;
	philo->is_allowed_to_eat = false;
	philo->ate = false;
	if (pthread_mutex_init(&philo->m_fork, NULL) != 0)
		return (ft_error("mutex init failed", info->first_philo), NULL);
	if (pthread_mutex_init(&philo->m_philo, NULL) != 0)
		return (ft_error("mutex init failed", info->first_philo), NULL);
	philo->prev = *prev;
	return (philo);
}

t_philo	*ft_create_philos(unsigned int nb_philo, t_info *info)
{
	t_philo			*first;
	t_philo			*prev;
	t_philo			*philo;
	unsigned int	id;
	unsigned int	millis;

	first = NULL;
	prev = NULL;
	millis = ft_get_millis();
	id = 0;
	while (id++ < nb_philo)
	{
		philo = ft_default_philo(info, &first, &prev, millis);
		if (!philo)
			return (NULL);
		philo->id = id;
		prev = philo;
	}
	philo->next = first;
	first->prev = philo;
	return (first);
}
