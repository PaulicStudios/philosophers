/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:10 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 16:41:34 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free(t_philo *first_philo)
{
	t_philo	*philo;
	t_philo	*next;
	char	*sem_meals_name;

	free(first_philo->info);
	philo = first_philo;
	while (philo)
	{
		next = philo->next;
		sem_close(philo->sem_meals);
		sem_meals_name = ft_strjoin("sem_philo_", ft_itoa(philo->id));
		sem_unlink(sem_meals_name);
		free(sem_meals_name);
		free(philo);
		philo = next;
		if (philo == first_philo)
			break ;
	}
	sem_close(first_philo->info->sem_forks);
	sem_close(first_philo->info->sem_log);
	sem_unlink("sem_forks");
	sem_unlink("sem_log");
}

bool	ft_error(char *msg, t_philo *first_philo)
{
	ft_free(first_philo);
	printf("Error: %s\n", msg);
	return (false);
}

void	ft_error_exit(char *msg, t_philo *first_philo)
{
	ft_free(first_philo);
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_join_threads(t_philo *first_philo)
{
	t_philo	*philo;

	philo = first_philo;
	while (philo)
	{
		pthread_join(philo->monitor_alive_thread, NULL);
		philo = philo->next;
		if (philo == first_philo)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = ft_parse_args(argc, argv);
	if (!info)
		return (1);
	if (!ft_start_routines(info))
		return (1);
	ft_join_threads(info->first_philo);
	ft_free(info->first_philo);
	return (0);
}