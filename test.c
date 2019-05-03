#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "get_next_line.h"

int open_file(const char *file)
{
	int fd;
	if (strcmp(file, "stdin") == 0)
	{
		printf("Reading from the standard input...\n");
		return (0);
	}
	else
	{
		printf("Reading %s...\n", file);
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			write(1, "Error opening file.\n", 20);
			return (-1);
		}
		return (fd);
	}
}

void read_file(const char *file)
{
	int fd = open_file(file);
	if (fd == -1)
		return;
	char *line;
	while (1)
	{
		int status = get_next_line(fd, &line);
		if (status == 1)
			printf("\t%s\n", line);
		else if (status == 0)
		{
			printf("End of file (%d) reached.\n", fd);
			break;
		}
		else if (status == -1)
		{
			printf("An error occured in getting the next line.\n");
			break;
		}
	}
	close(fd);
}

void read_files(int num_files, const char **files)
{
	for(int i = 0; i < num_files; i++)
		read_file(files[i]);
}

void interread_files(int num_files, const char **files)
{
	int fds[1024];

	for (int i = 0; i < num_files; i++)
	{
		fds[i] = open_file(files[i]);
		if (fds[i] == -1)
			num_files--;
	}

	char *line;
	int i = 0;
	int files_left = num_files;
	while (files_left > 0)
	{
		if (fds[i] != -1)
		{
			int status = get_next_line(fds[i], &line);
			if (status == 1)
				printf("\t%s\n", line);
			else if (status == 0)
			{
				printf("EOF%d\n", i);
				close(fds[i]);
				fds[i] = 0;
				files_left--;
			}
			else if (status == -1)
			{
				printf("An error occured in getting the next line.\n");
				close(fds[i]);
				fds[i] = 0;
				files_left--;
			}
		}
		i++;
		if (i >= num_files)
			i = 0;
	}
}

void binary_test()
{
	int fd = open_file("test6.txt");
	if (fd == -1)
		return;
	char *line;
	while (1)
	{
		int status = get_next_line(fd, &line);
		if (status == 1)
		{
			write(1, "\t", 1);
			while (*line != 'E')
			{
				write(1, line, 1);
				line++;
			}
			write(1, "\n", 1);
		}
		else if (status == 0)
		{
			printf("End of file (%d) reached.\n", fd);
			break;
		}
		else if (status == -1)
		{
			printf("An error occured in getting the next line.\n");
			break;
		}
	}
	close(fd);
}

void bad_fd_test()
{
	char *line;
	int arr[] = {16, 64, 1024, 65536, -1, -2};
	for(int i = 0; i < 6; i++)
	{
		printf("Trying file descriptor %d...\n", arr[i]);
		printf("Returned %d\n", get_next_line(arr[i], &line));
	}
	printf("Trying line = NULL...\n");
	printf("Returned %d\n", get_next_line(0, 0));
}

int	main(int argc, const char **argv)
{
	if (argc == 2)
	{
		if (strcmp(argv[1], "-b") == 0)
			binary_test();
		else if (strcmp(argv[1], "-f") == 0)
			bad_fd_test();
		else
			for (int i = 1; i < argc; i++)
				read_file(argv[i]);
	}
	else if (argc > 2)
	{
		if (strcmp(argv[1], "-m") == 0)
			interread_files(argc - 2, argv + 2);
		else
			read_files(argc - 1, argv + 1);
	}
	else
		read_file("test1.txt");
	return (0);
}
