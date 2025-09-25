/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/25 19:01:58 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	number_exit(char *args)
{
	int	nb;

	nb = ft_atoi((const char *)(args));
	if (nb > 255)
		nb = nb % 256;
	else if (nb < 0)
		nb = 256 + nb;
	return (nb);
}

int	just_nb(char *nb)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (nb[i] != '\0')
	{
		if ((nb[i] > '9' || nb[i] < '0') && (nb[i] != '+' && nb[i] != '-'))
			return (1);
		else if (nb[i] == '+' || nb[i] == '-')
			count++;
		i++;
	}
	if (count > 1)
		return (1);
	return (0);
}

int	exit_cnt(t_biggie *bigs)
{
	int	status;

	status = bigs->exit_status;
	if (just_nb(bigs->cmd->arguments[0]) != 0)
	{
		bigs->exit_status = 2;
		ft_putstr_fd("exit\nminishel: exit: ", 1);
		ft_putstr_fd(bigs->cmd->arguments[0], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
	}
	else if (bigs->cmd->arguments[1] != NULL)
	{
		bigs->exit_status = 1;
		ft_putstr_fd("exit\nminishel: exit: too many arguments\n", 1);
	}
	else
		bigs->exit_status = number_exit(bigs->cmd->arguments[0]);
	status = bigs->exit_status;
	free_big(bigs);
	exit (status);
	return (status);
}

int	run_exit(t_biggie *bigs)
{
	int	status;

	status = bigs->exit_status;
	if (bigs->cmd->arguments == NULL)
	{
		free_big(bigs);
		exit(status);
	}
	status = exit_cnt(bigs);
	return (status);
}
