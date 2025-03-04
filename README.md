# minihell

libft updates:

    Free and set null the product of ft_split (null terminated char **)
    void	ft_cleanstrarr(char **arr);

    Free and set null a variable amount of variables
    void	ft_terminate(int count, ...);

    Flag return 1 on success, returns 0 on error. Set it to -1 and call gnl to free static buffer.
    char	*get_next_line(int fd, int *flag);


    Im working on this right now so it can separate strings based on a charset, not only a single char
    ft_split()

