/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:38:03 by bschwitz          #+#    #+#             */
/*   Updated: 2022/05/03 19:14:02 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_philo *ph)
{
	int	i;

	i = -1;
	while (ph[++i].id)
		pthread_create(&(ph[i].thread), NULL, &philo_life, &(ph[i]));
}

t_philo	*create_t_philo_array(pthread_mutex_t *mutex, int *nb_ph_fed,
		t_pdata *ph_die, t_info *info)
{
	t_philo	*ph;
	int		nb_ph;
	long	time_start;

	nb_ph = info->nb_ph;
	ph = malloc(sizeof(*ph) * (nb_ph + 1));
	if (!ph)
		return (NULL);
	ph[nb_ph].id = 0;
	time_start = get_time_ms();
	while (nb_ph - 1 >= 0)
	{
		ph[nb_ph - 1].id = nb_ph;
		ph[nb_ph - 1].mutex = mutex;
		ph[nb_ph - 1].info = info;
		ph[nb_ph - 1].time_start = time_start;
		ph[nb_ph - 1].ph_die = ph_die;
		ph[nb_ph - 1].nb_ph_fed = nb_ph_fed;
		nb_ph--;
	}
	return (ph);
}

pthread_mutex_t	*create_forks(int nb_forks)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = malloc(sizeof(*mutex) * (nb_forks));
	if (!mutex)
		return (NULL);
	while (i < nb_forks)
		pthread_mutex_init(&mutex[i++], NULL);
	return (mutex);
}

void	init_t_info(t_info *info, int argc, char **argv)
{
	info->nb_ph = ft_atoi(argv[1]);
	info->t_to_die = ft_atoi(argv[2]);
	info->t_to_eat = ft_atoi(argv[3]);
	info->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->nb_each_ph_eat = ft_atoi(argv[5]);
	else
		info->nb_each_ph_eat = -1;
}
