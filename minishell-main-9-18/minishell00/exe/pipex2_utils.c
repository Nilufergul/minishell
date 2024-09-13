#include "../minishell.h"

void	restore_fds(int input, int output)
{
	dup2(input, 0);
	close(input);
	dup2(output, 1);
	close(output);
}

int	handle_input_fd(t_line *command, t_pipe_info *pipe_info)
{
	int	fd;

	if (fd_len(&(command->left)) != 0)
	{
		fd = open_lefts(command->left);
		if (fd == -1)
		{
			fd = open("/dev/null", O_RDONLY);
			free(command->env[0][0]);
			command->env[0][0] = ft_strdup("?=1");
			return (-1);
		}
		dup2(fd, 0);
		pipe_info->input = 0;
	}
	return (0);
}

void	handle_output_fd(t_line *command, t_pipe_info *pipe_info, int *ret)
{
	int	fd;

	if (*ret != -1 && fd_len(&(command->right)) != 0)
	{
		fd = open_rights(command->right);
		if (fd != -1)
		{
			dup2(fd, 1);
			pipe_info->output = 0;
		}
	}
}
