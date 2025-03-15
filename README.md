# minihell

libft updates:

    Free and set null the product of ft_split (null terminated char **)
    void	ft_cleanstrarr(char **arr);

    Free and set null a variable amount of variables
    void	ft_terminate(int count, ...);

    Flag return 1 on success, returns 0 on error. Set it to -1 and call gnl to free static buffer.
    char	*get_next_line(int fd, int *flag);

    It can now separate a string with a set of delimeter charachters
    char	**ft_split(char const *s, char *charset)

