/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:49:19 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/17 12:53:00 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_infile(char **arr, int *i)
{
	if (arr[*i][1])
	{
		if (vars()->infile)
		{
			close(vars()->fd_in);
			free(vars()->infile);
		}
		vars()->infile = ft_strdup(&arr[*i][1]);
		(vars())->fd_in = open(vars()->infile, O_RDONLY);
	}
	else
	{
		(*i)++;
		if (vars()->infile)
		{
			close(vars()->fd_in);
			free(vars()->infile);
		}
		vars()->infile = ft_strdup(arr[*i]);
		(vars())->fd_in = open(vars()->infile, O_RDONLY);
	}
	// if (vars()->fd_in < 0)
		// error_handle(BLA);
	(*i)++;
}

void	process_outfile(char **arr, int *i)
{
	if (vars()->outfile)
		{
			close(vars()->fd_out);
			free(vars()->outfile);
		}
	if (!arr[*i][1]/*  || (arr[*i][1] == '>' && !arr[*i][2]) */)
	{
		(*i)++;
		vars()->outfile = ft_strdup(arr[*i]);
	}
	else
		vars()->outfile = ft_strdup(&arr[*i][1 /* + (arr[*i][1] == '>') */]);
	(vars())->fd_out = open(vars()->outfile, \
		O_RDWR | O_CREAT | O_TRUNC, 0666);
	/* if (arr[*i][1])
	{
		if (vars()->outfile)
		{
			close(vars()->fd_out);
			free(vars()->outfile);
		}
		vars()->outfile = ft_strdup(&arr[*i][1]);
		(vars())->fd_out = open(vars()->outfile, \
			O_RDWR | O_CREAT | O_TRUNC, 0666);
	}
	else
	{
		(*i)++;
		if (vars()->outfile)
		{
			close(vars()->fd_out);
			free(vars()->outfile);
		}
		vars()->outfile = ft_strdup(arr[*i]);
		(vars())->fd_out = open(vars()->outfile, \
			O_RDWR | O_CREAT | O_TRUNC, 0666);
		// printf("out is %d\n", vars()->fd_out);
	} */
	// if (vars()->fd_in < 0)
		// error_handle(BLA);
	(*i)++;
}

void	redirection(char **arr, int *i)
{
	if (arr[*i][0] == '<')
		process_infile(arr, i);
	else
		process_outfile(arr, i);
}
