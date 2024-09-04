/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   struct_utils.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: selmandemir <selmandemir@student.42.fr>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/21 16:27:25 by muhademi		  #+#	#+#			 */
/*   Updated: 2024/09/03 23:37:44 by selmandemir	  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

t_line	*create_new_line(char *cmd_str, char **env)
{
	t_line	*new_line;

	new_line = (t_line *)malloc(sizeof(t_line));
	if (new_line == NULL)
		return (0);
	new_line->cmd = ft_strdup(cmd_str);
	if (new_line->cmd == NULL)
	{
		free(new_line);
		return (0);
	}
	new_line->env = env;
	new_line->arg = NULL;
	new_line->right = NULL;
	new_line->left = NULL;
	new_line->next = NULL;
	return (new_line);
}

t_fd	*create_new_fd(char *name, int type)
{
	t_fd	*new_fd;

	new_fd = (t_fd *)malloc(sizeof(t_fd));
	if (new_fd == NULL)
		return (0);
	new_fd->fd = -1;
	new_fd->name = ft_strdup(name);
	new_fd->type = type;
	if (new_fd->name == NULL)
	{
		free(new_fd);
		return (0);
	}
	new_fd->next = NULL;
	return (new_fd);
}

t_ty	*create_new_ty(int type)
{
	t_ty	*new_ty;

	new_ty = (t_ty *)malloc(sizeof(t_ty));
	if (new_ty == NULL)
		return (0);
	new_ty->type = type;
	new_ty->next = NULL;
	return (new_ty);
}

void	append_line(t_line **head, t_line *new_line)
{
	t_line	*current;

	if (*head == NULL)
		*head = new_line;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_line;
	}
}

void	append_fd(t_fd **head, t_fd *new_fd)
{
	t_fd	*current;

	if (*head == NULL)
		*head = new_fd;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_fd;
	}
}
