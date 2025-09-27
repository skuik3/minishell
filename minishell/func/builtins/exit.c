/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/27 13:43:43 by skuik            ###   ########.fr       */
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

int	validate_exit_args(t_biggie *bigs)
{
	if (bigs->cmd->arguments[0] == NULL
		||ft_strlen (bigs->cmd->arguments[0]) == 0)
	{
		bigs->exit_status = 2;
		ft_putstr_fd("minishell: exit: : numeric argument required\n",
			STDERR_FILENO);
		return (1);
	}
	else if (just_nb(bigs->cmd->arguments[0]) != 0)
	{
		bigs->exit_status = 2;
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(bigs->cmd->arguments[0], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (1);
	}
	else if (bigs->cmd->arguments[1] != NULL)
	{
		bigs->exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	exit_cnt(t_biggie *bigs)
{
	int	status;

	if (!validate_exit_args(bigs))
	{
		ft_putstr_fd("exit\n", bigs->cmd->orig_stdout);
		bigs->exit_status = number_exit(bigs->cmd->arguments[0]);
	}
	status = bigs->exit_status;
	free_big(bigs);
	exit(status);
	return (status);
}

int	run_exit(t_biggie *bigs)
{
	int	status;

	status = bigs->exit_status;
	if (bigs->cmd->arguments == NULL)
	{
		ft_putstr_fd("exit\n", bigs->cmd->orig_stdout);
		free_big(bigs);
		exit(status);
	}
	status = exit_cnt(bigs);
	return (status);
}
