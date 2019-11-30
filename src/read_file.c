#include "lem_in.h"

int		read_ants(int fd, s_info *info)
{
	char	*line;
	int		ants;

	ants = 0;
	line = NULL;
	while(get_next_line(fd, &line))
	{
		if (line != NULL && line[0] != '#')
		{
			if (ft_thisnum(line))
			{
				ants = ft_atoi(line);
				ft_strdel(&line);
				return (ants);
			}
			ft_strdel(&line);
			return (FORMAT_E);
		}
		else if (ft_strcmp(line, "##start") == 0 || ft_strcmp(line, "##end") == 0)
		{
			ants = line[2] == 's' ? START_1_E : END_1_E;
			ft_strdel(&line);
			return (ants);
		}
		info->input = ft_strjoinendl(info->input, line);
		ft_strdel(&line);
	}
	return (NO_ANTS_E);
}

int		add_rooms(s_info *info, const char *line, int type)
{
	s_rooms *rooms;
	char **param;

	rooms = info->rooms;
	param = ft_strsplit(line, ' ');
	if (rooms == NULL)
	{
		info->rooms = (s_rooms *)malloc(sizeof(s_rooms));
		info->rooms->name = param[0];
		info->rooms->type = type;
		info->rooms->next = NULL;
	}
	else
	{
		while(rooms->next != NULL)
			rooms = rooms->next;
		rooms->next = (s_rooms *)malloc(sizeof(s_rooms));
		rooms->next->name = param[0];
		rooms->next->type = type;
		rooms->next->next = NULL;
	}
	param = delete_ar(param, 2);
	return (1);
}

int		add_links(s_info *info, const char *line)
{
	s_links *links;
	char **param;

	links = info->links;
	param = ft_strsplit(line, '-');
	if (links == NULL)
	{
		info->links = (s_links *)malloc(sizeof(s_links));
		info->links->room1 = param[0];
		info->links->room2 = param[1];
		info->links->next = NULL;
	}
	else
	{
		while (links->next)
			links = links->next;
		links->next = (s_links *)malloc(sizeof(s_links));
		links->next->room1 = param[0];
		links->next->room2 = param[1];
		links->next->next = NULL;
	}
	param = delete_ar(param, 1);
	return (1);
}

int		read_main(s_info *info, int fd)
{
	char		*line;
	int			num;
	s_read_main	srm;

	srm.type = TUNNEL;
	srm.start = 0;
	srm.end = 0;
	num = EMPTY_LINE_E;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		num = 1;
		if (line[0] == '\0')
			error_processing(EMPTY_LINE_E, &info);
		else if (line[0] == '#')
		{
			if (ft_strcmp(line, "##start") == 0)
			{
				srm.type = START;
				srm.start += 1;
			}
			else if (ft_strcmp(line, "##end") == 0)
			{
				srm.type = END;
				srm.end += 1;
			}
		}
		else
		{
			num = valid_format(line, info);
			if (num == 1)
				info->c_rooms += add_rooms(info, line, srm.type);
			else if (num == 2)
				info->c_links += add_links(info, line);
			srm.type = TUNNEL;
		}
		info->input = ft_strjoinendl(info->input, line);
		ft_strdel(&line);
		if (srm.start > 1 || srm.end > 1)
			error_processing(srm.start > 1 ? START_2_E : END_2_E, &info);
		if (num < 1)
			break;
	}
	if (srm.start != 1 || srm.end != 1)
		num = START_2_E;
	return (num > 0 ? 1 : num);
}

s_info	*read_file()
{
	int		fd;
	int		finish;
	s_info	*info;

	fd = 0;
	finish = 0;
	if (!(info = (s_info *)malloc(sizeof(s_info))))
		error_processing(MALLOC_E, &info);
	info->input = (char *)malloc(1);
	info->input[0] = '\0';
	info->rooms = NULL;
	info->links = NULL;
	info->c_rooms = 0;
	info->c_links = 0;
	info->c_path = 0;
	info->c_ants = read_ants(fd, info);
	if (info->c_ants < 1)
		error_processing(info->c_ants, &info);
	finish = read_main(info, fd);
	if ((finish < 1))
		error_processing(finish, &info);
	close(fd);
	return (info);
}