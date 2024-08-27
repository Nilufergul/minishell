# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

typedef enum type {
	EXEC = 0,
	HEREDOC = 1,
	PIPE = 2,
	GREAT = 3,
	GREATER = 4,
	LESS = 5,
} type;

typedef enum file_des {
	STDINN = 0,
	STDOUT = 1,
	STDERR = 2
} file_des;

typedef struct s_ty
{
	int type;
	struct s_ty *next;
}				t_ty;

typedef struct s_arg
{
	int *arg;
	struct s_arg *next;
}				t_arg;

typedef struct s_split
{
	int meta;
	char *node;
	struct s_split *next;
}				t_split;

typedef struct s_fd
{
	int fd;
	int	type;
	char *name;
	struct s_fd *next;
}				t_fd;

typedef struct  s_line
{
	char	*cmd;
	char	**arg;
	struct	s_ty    *type;
	struct  s_fd    *fd;
	struct  t_mini  *minis;
	struct  s_line  *next;
}				t_line;
