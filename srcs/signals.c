/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-faqu <mel-faqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:43:31 by mel-faqu          #+#    #+#             */
/*   Updated: 2023/07/17 08:43:31 by mel-faqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_handler(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_global.error_num = 1;
}

static void	ctrl_c_handler(int sig)
{
	(void) sig;
	ft_putendl_fd("^C", 1);
	g_global.error_num = 130;
}

static void	back_slash_handler(int sig)
{
	ft_putstr_fd("^\\Quit: ", 1);
	ft_putnbr_fd(sig, 1);
	ft_putchar_fd('\n', 1);
	g_global.error_num = 131;
}

void	init_signals(int process)
{
	struct termios	term;

	if (process == 0)
	{
		signal(SIGINT, reset_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (process == 1)
	{
		signal(SIGINT, ctrl_c_handler);
		signal(SIGQUIT, back_slash_handler);
	}
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
