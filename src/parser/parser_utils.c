/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 12:29:45 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 12:32:52 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"
#include <stdio.h>

t_ast	*init_tree(t_ast *tree, t_token *tokens)
{
	int	n_args;
	int	i;

	i = 0;
	tree = malloc(sizeof(t_ast));
	if (!tree)
		exit(EXIT_FAILURE);
	tree->cmd_number = calculate_n_cmd(tokens);
	n_args = calculate_n_args(tokens);
	tree->args = malloc(sizeof(t_args *) * (n_args + 1));
	if (!(tree->args))
		exit(EXIT_FAILURE);
	while (i < n_args)
	{
		tree->args[i] = malloc(sizeof(t_args));
		if (!(tree->args[i]))
			exit(EXIT_FAILURE);
		i++;
	}
	return (tree);
}

void	print_tree(t_ast *tree, t_token *tokens)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
	printf("total command number: %d\n", tree->cmd_number);
	printf("total arg number: %d\n", calculate_n_args(tokens));
	{
		printf("tree->args[0]->type: %d\n", tree->args[0]->type);
		printf("tree->args[0]->data[0]: echo? %s\n", tree->args[0]->data[0]);
		printf("tree->args[0]->data[1]: idil? %s\n", tree->args[0]->data[1]);
		printf("tree->args[0]->data[2]: null? %s\n", tree->args[0]->data[2]);
		printf("tree->args[1]->type: %d\n", tree->args[1]->type);
		printf("tree->args[1]->data[0]: file? %s\n", tree->args[1]->data[0]);
		printf("tree->args[1]->data[1]: null? %s\n", tree->args[1]->data[1]);
		printf("tree->args[2]->type: %d\n", tree->args[2]->type);
		printf("tree->args[2]->data[0]: file? %s\n", tree->args[2]->data[0]);
		printf("tree->args[2]->data[1]: null? %s\n", tree->args[2]->data[1]);
		printf("tree->args[3]->type: %d\n", tree->args[3]->type);
		printf("tree->args[3]->data[0]: file? %s\n", tree->args[3]->data[0]);
		printf("tree->args[3]->data[1]: null? %s\n", tree->args[3]->data[1]);
		// printf("tree->args[2]->data[2]: null? %s\n", tree->args[2]->data[2]);
	}
}
