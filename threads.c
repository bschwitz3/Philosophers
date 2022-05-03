/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:22:31 by bschwitz          #+#    #+#             */
/*   Updated: 2022/05/03 19:44:45 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo_is_fed(t_philo *ph, int *nb_of_time_ph_ate)
{
	pthread_mutex_lock(&(ph->ph_die->mutex));
	if (++(*nb_of_time_ph_ate) == ph->info->nb_each_ph_eat)
	{
		if (++(*(ph->nb_ph_fed)) == ph->info->nb_ph)
		{
			if (!(ph->ph_die->data))
				ft_putstr_fd("All philosophers have eaten enough\n", 1);
			ph->ph_die->data = 1;
		}
	}
	pthread_mutex_unlock(&(ph->ph_die->mutex));
}

void	philo_eat(t_philo *ph, int *nb_of_time_ph_ate)
{
	int	right_f;
	int	left_f;

	right_f = ph->id - 1;
	if (right_f != 0)
		left_f = right_f - 1;
	else
		left_f = ph->info->nb_ph - 1;
	if ((ph->id % 2 == 0 && !pthread_mutex_lock(&((ph->mutex)[left_f]))) ||
			!pthread_mutex_lock(&((ph->mutex)[right_f])))
		print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, FORK);
	if ((ph->id % 2 == 0 && !pthread_mutex_lock(&((ph->mutex)[right_f]))) ||
			!pthread_mutex_lock(&((ph->mutex)[left_f])))
		print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, FORK);
	ph->time_last_meal = get_time_ms();
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, EAT);
	check_philo_is_fed(ph, nb_of_time_ph_ate);
	better_sleep(ph->info->t_to_eat * 1000);
	pthread_mutex_unlock(&((ph->mutex)[left_f]));
	pthread_mutex_unlock(&((ph->mutex)[right_f]));
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, SLEEP);
	better_sleep(ph->info->t_to_sleep * 1000);
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, THINK);
	usleep(100);
}

void	*check_philo_alive(void *tmp)
{
	t_philo	*ph;
	long	time_death;

	ph = (t_philo *)tmp;
	while (1)
	{
		time_death = get_time_ms();
		pthread_mutex_lock(&(ph->ph_die->mutex));
		if ((time_death - ph->time_last_meal) > ph->info->t_to_die)
		{
			if (!ph->ph_die->data)
				print_ms_and_states(ph->id, time_death - ph->time_start,
					" has died\n");
			ph->ph_die->data = 1;
			pthread_mutex_unlock(&(ph->ph_die->mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(ph->ph_die->mutex));
		if (ph->ph_die->data)
			return (NULL);
	}
}

void	*philo_life(void *ph)
{
	pthread_t	control_die;
	int			nb_of_time_ph_ate;

	nb_of_time_ph_ate = 0;
	((t_philo *)ph)->time_last_meal = get_time_ms();
	pthread_create(&control_die, NULL, &check_philo_alive, ph);
	while (1)
	{
		philo_eat((t_philo *)ph, &nb_of_time_ph_ate);
		if (((t_philo *)ph)->ph_die->data)
		{
			pthread_join(control_die, NULL);
			return (ph);
		}
	}
	return (ph);
}

void	join_all_threads(t_philo *ph)
{
	int	i;

	i = -1;
	while (ph[++i].id)
		pthread_join(ph[i].thread, NULL);
}
