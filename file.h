#ifndef _FILE_H_
#define _FILE_H_

#include "utils.h"
#include "config.h"
#include "commands.h"

#include <stdio.h>

// Get vehicle VIN
// Create DIR if none
// Create DIR for trip
int find_dir(char **path, struct environment *env);

// Open file in VIN/TRIP/
// Open file with correct type and place header inside
int get_file(FILE **sens_file, char *path, char *sens_ID, char *mode);

#endif // _FILE_H_