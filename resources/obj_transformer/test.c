#include "libft/includes/libft.h"
#include <math.h>
int main()
{
	char *final = ft_strdup("");
	char *current = ft_strdup("");
	char *line;
	int rd = open("towers.obj", O_RDONLY);
	int wt = open("res.obj", O_WRONLY | O_APPEND | O_CREAT);
	float temp = 0;
	float temp1 = 0;
	float temp2 = 0;


	while (get_next_line(rd, &line) > 0) {
		// printf("line: %s\n", line);
		if (*line && *line == 'v' && line[1] && line[1] != 'n') {
			line++;
			line++;
			temp = atof(line);
			while (*line && *line != ' ')
				line++;
			line++;
			temp1 = atof(line);
			while (*line && *line != ' ')
				line++;
			line++;
			temp2 = atof(line);
			while (*line && *line != ' ')
				line++;
			dprintf(wt, "v %1.f,%1.f,%1.f\n", roundf(temp), roundf(temp1), roundf(temp2));
		}
		//f 1//1 2//1 3//1
		if (*line == 'f') {
			line++;
			line++;
			temp = (float)atoi(line);
			while (*line && *line != ' ')
				line++;
			line++;
			temp1 = (float)atoi(line);
			while (*line && *line != ' ')
				line++;
			line++;
			temp2 = (float)atoi(line);
			while (*line && *line != ' ')
				line++;
			dprintf(wt, "f %1.f,%1.f,%1.f\n", temp, temp1, temp2);
		}
	}
}
