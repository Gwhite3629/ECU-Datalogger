#include "config.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(FILE* fd, fpos_t* prof_start, fpos_t* prof_end, const char *locator)
{
    int ret = SUCCESS;
	unsigned int flag = 0;
	unsigned int found = 0;
	char* buffer = NULL;

	MEM(buffer, strlen(locator), char);

	buffer[strlen(locator) - 1] = '\0';
	
	do {
		buffer[flag] = fgetc(fd);
		HANDLE(buffer[flag] == EOF, 0)
		if (buffer[flag] == locator[flag])
		{
			if (flag == strlen(locator) - 1)
			{
                if (found == 0)
				    fgetpos(fd, prof_start);
                else if (found == 1)
                    fgetpos(fd, prof_end);
				found++;
			} else
			{
				flag++;
			}
		}
		else
		{
			flag = 0;
		}
	} while (found < 2);

exit:
	SFREE(buffer);

	return ret;
}

int read_config(struct sensor **user_table, size_t *size, char *conf_name)
{
    int ret = SUCCESS;
    FILE *conf = NULL;
    fpos_t pstart = 0;
    fpos_t pend = 0;
    char **lines = NULL;
    int ltracker = 0;
    int j = 0;
    int l = 0;
    char t = 'N';
    struct sensor temp;

    conf = fopen("config", "r");
    VALID(conf, FILE_CODE, FILE_OPEN);
    CHECK(search(conf, &pstart, &pend, conf_name));
    fsetpos(conf, &pstart);
    MEM(lines, 1, char*);
    MEM(lines[0], 50, char);
    for (int i = 0; i < (int)(pend - pstart); i++) {
        lines[l][j] = fgetc(conf);
        if (lines[l][j] == '\n') {
            if (j != 0) {
                MEM_(lines[l], j, char);
                j = 0;
                l++;
                MEM_(lines, l+1, char *);
                MEM(lines[l], 50, char);
            }
        } else {
            j++;
        }
    }
    MEM_(lines, l, char *);

    MEM((*user_table), l/5, struct sensor);

    for (int i = 0; i < l/5; i++) {
        ltracker++;
        sscanf(lines[ltracker], "\n<SENSOR_ID>: %s", (*user_table)[i].ID); ltracker++;
        sscanf(lines[ltracker], "\n<TIME>: %c", &t); ltracker++;
        sscanf(lines[ltracker], "\n<POLL>: %f", &((*user_table)[i]).poll); ltracker++;
        ltracker++;
        if (t == 'Y') {
            (*user_table)[i].time = 1;
        } else {
            (*user_table)[i].time = 0;
        }

        (*user_table)[i].hash = (int)(hash((*user_table)[i].ID) % (INT_MAX));
        temp = lookup((*user_table)[i].ID);
        (*user_table)[i].PID = temp.PID;
        (*user_table)[i].width = temp.width;
    }

    (*size) = (size_t)l/5;
    
	qsort(*user_table, *size, sizeof(struct sensor), &cmp);
exit:
    for (int i = 0; i < l; i++) {
        SFREE(lines[i]);
    }
    SFREE(lines);
    SCLOSE(conf);
    return ret;
}