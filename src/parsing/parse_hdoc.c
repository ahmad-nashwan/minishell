# include "../../inc/minishell.h"

static void hdoc_eof_error(char *delimeter)
{
    ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
    ft_putstr_fd(delimeter, 2);
    ft_putstr_fd("')\n", 2);
}

static t_code hdoc_append_char(t_shell *shell, t_string *line, t_string *buff, int quoted)
{
    if (peek(line) == '$' && !quoted)
    {
        expand_hdoc(shell, line, buff);
        return (OK);
    }
    return (append(buff, advance(line)));
}

static t_code hdoc_process_line(t_shell *shell, char *input, int *fd, int quoted)
{
    t_string    *buff;
    t_string    *line;

    line = init_string(input);
    if (!line) return (ERR);
    buff = create_empty_string(1024);
    if (!buff)
    {
        free_t_string(line);
        return (ERR);
    }
    while (peek(line) != '\0')
    {
        if (hdoc_append_char(shell, line, buff, quoted) != OK)
        {
            free_t_string(buff);
            free_t_string(line);
            return (ERR);
        }
    }
    write(fd[1], buff->str, ft_strlen(buff->str));
    write(fd[1], "\n", 1);
    free_t_string(buff);
    free_t_string(line);
    return (OK);
}

static t_code  hdoc_reader(t_shell *shell, char *delimeter, int quoted, int *fd)
{
    char        *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            hdoc_eof_error(delimeter);
            break;
        }
        if (ft_strcmp(line, delimeter) == 0)
        {
            free(line);
            break;
        }
        if (hdoc_process_line(shell, line, fd, quoted) != OK)
        {
            free(line);
            return (ERR);
        }
        free(line);
    }
    return (OK);
}

int parse_hdoc(t_shell *shell, char *delimeter, int quoted)
{
    int         fd[2];

    if (pipe(fd) == -1)
    {
        report_error(shell, INTERNAL_ERROR, "Pipe failure");
        return (-1);
    }
    if (hdoc_reader(shell, delimeter, quoted, fd) != OK)
    {
        close(fd[0]);
        close(fd[1]);
        report_error(shell, INTERNAL_ERROR, NULL);
        return (-1);
    }
    close(fd[1]);
    return (fd[0]);
}
