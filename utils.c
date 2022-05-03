/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:41:05 by bschwitz          #+#    #+#             */
/*   Updated: 2022/05/03 19:18:52 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (1);
}

int	check_arguments(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (error_msg("Wrong number of arguments\n"));
	i = 1;
	while (i < argc)
		if (ft_strisdigit(argv[i++]))
			return (error_msg("Wrong arguments\n"));
	if (ft_atoi(argv[1]) > 1000 || ft_strlen(argv[1]) > 4)
		return (error_msg("Max number of philosophers : 1000\n"));
	if (ft_atoi(argv[2]) > 1000000 || ft_strlen(argv[2]) > 7
		|| ft_atoi(argv[3]) > 1000000 || ft_strlen(argv[3]) > 7
		|| ft_atoi(argv[4]) > 1000000 || ft_strlen(argv[4]) > 7)
		return (error_msg("Max time in ms for args 2/3/4 : 1000000ms\n"));
	if (argv[5] && (ft_atoi(argv[5]) > 1000000 || ft_strlen(argv[5]) > 7))
		return (error_msg("Max nb of time philo can eat : 1000000\n"));
	if (!ft_atoi(argv[2]) || !ft_atoi(argv[3]) || ! ft_atoi(argv[4])
		|| (argv[5] && !ft_atoi(argv[5])))
		return (error_msg("Args must be positive and > 0\n"));
	return (0);
}

long	get_time_ms(void)
{
	struct timeval	tmp_time;
	long			ms;

	gettimeofday(&tmp_time, NULL);
	ms = tmp_time.tv_sec * 1000;
	ms += tmp_time.tv_usec / 1000;
	return (ms);
}

int	print_ms_and_states(int id, int ms, char *str_msg)
{
	int		len_id;
	int		len_ms;
	char	tmp[100];

	len_id = -1;
	while (++len_id <= 99)
		tmp[len_id] = '\0';
	len_id = lennb_for_str(id);
	len_ms = lennb_for_str(ms);
	ft_putnbr_buffer(ms, tmp);
	ft_strlcpy(tmp + len_ms, "ms ", 4);
	ft_putnbr_buffer(id, tmp + len_ms + 3);
	ft_strlcpy(tmp + len_id + len_ms + 3, str_msg, ft_strlen(str_msg) + 1);
	ft_putstr_fd(tmp, 1);
	return (0);
}

int	print_state_msg(t_philo *ph, int id_philo, suseconds_t ms, int type)
{
	pthread_mutex_lock(&(ph->ph_die->mutex));
	if (!ph->ph_die->data && type == EAT)
		print_ms_and_states(id_philo, ms, " is eating\n");
	else if (!ph->ph_die->data && type == FORK)
		print_ms_and_states(id_philo, ms, " has taken a fork\n");
	else if (!ph->ph_die->data && type == SLEEP)
		print_ms_and_states(id_philo, ms, " is sleeping\n");
	else if (!ph->ph_die->data && type == THINK)
		print_ms_and_states(id_philo, ms, " is thinking\n");
	else if (!ph->ph_die->data && type == DIE)
		print_ms_and_states(id_philo, ms, " has died\n");
	pthread_mutex_unlock(&(ph->ph_die->mutex));
	return (0);
}
