#include "config.h"
#include "commands.h"
#include "utils.h"

#include <stdio.h>
#include <pthread.h>

int main(void)
{
    int ret = SUCCESS;
    char conf[20] = "DEFAULT";
    struct sensor *user_table = NULL;
    struct environment *env = NULL;
    pthread_t thr;

    init_table();

    MEM(env, 1, struct environment);

    env->user_table = &user_table;
    env->update = 0;
    env->print = 0;
    env->exit = 0;
    pthread_spin_init(&env->lock, 0);
    
    CHECK(read_config(&user_table, &(env->size), conf));

    HANDLE_ERR(pthread_create(&thr, NULL, &input, &env), "pthread_create");

    while(!(env->exit));

    HANDLE_ERR(pthread_join(thr, NULL), "pthread_join");

exit:
    SFREE(user_table);
    SFREE(env);
    return ret;
}