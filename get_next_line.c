/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:55:52 by lsabik            #+#    #+#             */
/*   Updated: 2022/11/08 11:55:54 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
#include<stdio.h>

char	*extract_line(char **static_buff)
{
	char	*tmp;
	char	*line;
	int		i;
	if (*static_buff == 0 || **static_buff ==0)
		return 0;
	i = 0;
	i = ft_strchr(*static_buff, '\n');
		line = ft_substr(*static_buff, 0, i + 1);
		tmp = ft_strdup(&(*static_buff)[i + 1]);
		free(*static_buff);
		*static_buff = tmp;
	return (line);
}

int		read_lines(int fd, char **static_buff)
{
	int		readed;
	char	*tmp;
	char	*buff;

	readed = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	while (ft_strchr(*static_buff, '\n') == -1 && readed)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed <= 0)
			return (0);
		buff[readed] = '\0';
		tmp = ft_strjoin(*static_buff, buff);
		*static_buff = tmp;
	}
	free(buff);
	return (readed);
}

char	*get_next_line(int fd)
{
	char	*line;
	int		readed;
	static char	*static_buff;
	char 	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//read and save
	readed = read_lines(fd,&static_buff);
	//extract line
	line = extract_line(&static_buff);
	if (!readed)
	{
		tmp = static_buff;
		static_buff = 0;
		return tmp;
	}
	return (line);
}

int main()
{
	int fd = open("test", O_RDONLY);
	char *str;
	while((str = get_next_line(fd)))
	{
		printf("%s",str);
		free(str);
	}
	system("leaks a.out");
}