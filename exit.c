/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:40:48 by bschwitz          #+#    #+#             */
/*   Updated: 2022/05/03 19:43:46 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_exit(t_philo *ph)
{
	int	i;

	i = -1;
	while (ph[++i].id)
		pthread_mutex_destroy(&((ph[i].mutex)[i]));
	pthread_mutex_destroy(&(ph->ph_die->mutex));
	free(ph->mutex);
	free(ph);
}
