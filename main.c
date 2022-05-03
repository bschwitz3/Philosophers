/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:46:12 by bschwitz          #+#    #+#             */
/*   Updated: 2022/05/03 19:16:27 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*ph;
	t_pdata			ph_die;
	int				nb_ph_fed;
	pthread_mutex_t	*mutex;
	t_info			info;

	if (check_arguments(argc, argv))
		return (1);
	pthread_mutex_init(&(ph_die.mutex), NULL);
	ph_die.data = 0;
	nb_ph_fed = 0;
	init_t_info(&info, argc, argv);
	if (info.nb_ph < 2)
		return (error_msg("Not enough philosophers (min. 2)\n"));
	mutex = create_forks(info.nb_ph);
	if (!mutex)
		return (error_msg("Malloc error\n"));
	ph = create_t_philo_array(mutex, &nb_ph_fed, &ph_die, &info);
	if (!ph)
		return (error_msg("Malloc error\n"));
	launch_threads(ph);
	join_all_threads(ph);
	clean_exit(ph);
	return (0);
}
