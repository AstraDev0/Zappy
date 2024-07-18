/*
** EPITECH PROJECT, 2023
** Server
** File description:
** node_queue
*/

#include "../include/zappy.h"

void remove_queues(queue_s *queue)
{
    queue_s *queue_tmp;

    if (!queue)
        return;
    queue_tmp = queue->next;
    table_free(queue->cmd_args);
    free(queue);
    remove_queues(queue_tmp);
}

queue_s *add_queue(queue_s *queue, command_t cmd, char **cmd_args)
{
    queue_s *queue_tmp = malloc(sizeof(queue_s));
    queue_s *save = queue;

    queue_tmp->cmd = cmd;
    queue_tmp->next = NULL;
    queue_tmp->prec = NULL;
    queue_tmp->cmd_args = copy_table(cmd_args);
    clock_gettime(4, &queue_tmp->startTime);
    if (!queue)
        return queue_tmp;
    while (queue->next)
        queue = queue->next;
    queue->next = queue_tmp;
    queue_tmp->prec = queue;
    return save;
}

queue_s *remove_queue(queue_s *queue, queue_s *queue_to_delete)
{
    queue_s *save = queue_to_delete;

    if (queue == queue_to_delete && !queue_to_delete->next) {
        table_free(queue_to_delete->cmd_args);
        free(queue_to_delete);
        return NULL;
    }
    if (queue == queue_to_delete && queue_to_delete->next) {
        queue = queue_to_delete->next;
        table_free(queue_to_delete->cmd_args);
        free(queue_to_delete);
        return queue;
    }
    save = queue_to_delete->prec;
    save->next = queue_to_delete->next;
    table_free(queue_to_delete->cmd_args);
    free(queue_to_delete);
    return save;
}
