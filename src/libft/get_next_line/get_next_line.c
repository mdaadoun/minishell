/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 07:45:21 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/06/29 14:42:00 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

/*
	get the string to append from str until '\n'
	join content of line to this pointer
	free to_append and line string before to return new_string
*/
char	*append_to_line(char *line, char *str)
{
	char	*to_append;
	char	*new_string;

	to_append = (void *)0;
	new_string = (void *)0;
	to_append = ft_substr_gnl(str, 0, eol_or_length(str, 0) + 1);
	if (!to_append)
		return (NULL);
	new_string = ft_strjoin_gnl(line, to_append);
	if (!new_string)
		return (NULL);
	free(to_append);
	free(line);
	(void) line;
	(void) str;
	return (new_string);
}

/*
	create a new empty line
	check if the storage is empty
	if empty, create an empty storage
	if not empty, add the content to a new line
*/
char	*check_storage_and_set_line(char **storage)
{
	char	*new_string;

	new_string = (void *)0;
	new_string = (char *)malloc(1 * sizeof(char));
	new_string[0] = '\0';
	if (!new_string)
		return (NULL);
	if (*storage)
		new_string = append_to_line(new_string, *storage);
	return (new_string);
}

/*
	read file until eol or eof
	append the buffer to line
	return the reading status
*/
int	read_next_bytes(int fd, char **line, char **buffer)
{
	ssize_t	bytes;

	bytes = 0;
	*buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (0);
	while (!bytes || bytes == (ssize_t)eol_or_length(*buffer, 0))
	{
		bytes = read(fd, *buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (0);
		buffer[0][bytes] = '\0';
		*line = append_to_line(*line, *buffer);
		if (!*line)
			return (0);
	}
	return (bytes);
}

/*
	Create a new string for storage with the content of the given string
		past the next '\n' char
	free storage before to return it the new string
*/
char	*save_to_storage(char **storage, char **string)
{
	char	*new_string;
	size_t	start;

	start = 0;
	start = eol_or_length(*string, 0) + 1;
	new_string = (void *)0;
	if (start - 1 == eol_or_length(*string, 1))
		start = 0;
	new_string = ft_substr_gnl(*string, start, \
	eol_or_length(*string, 1) - start);
	if (!new_string)
		return (NULL);
	if (*storage)
		free(*storage);
	return (new_string);
}

/*
	1. first check if storage is empty, create storage and line
	2. check if line is complete with '\n' char, save storage, return line
	3. read the file to a buffer while appending line until eol of eof
		1. return NULL if read status give 0 or -1
	4. save the left content of the buffer to storage, free buffer
	5. return line
*/
char	*get_next_line(int fd)
{
	static char	*storage[MAX_FD];
	char		*buffer;
	char		*line;
	int			read_status;

	buffer = (void *)0;
	line = (void *)0;
	read_status = 0;
	line = check_storage_and_set_line(&storage[fd]);
	if (!line)
		return (NULL);
	if (eol_or_length(line, 1) > eol_or_length(line, 0))
	{
		storage[fd] = save_to_storage(&storage[fd], &storage[fd]);
		return (line);
	}
	read_status = read_next_bytes(fd, &line, &buffer);
	if (!read_status)
		return (free_and_return(&storage[fd], &line, &buffer));
	storage[fd] = save_to_storage(&storage[fd], &buffer);
	free(buffer);
	return (line);
}
