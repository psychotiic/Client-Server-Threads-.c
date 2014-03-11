//Thread Safe Message Queue
#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "error.h"

// Message struct
// Make sure that `data` is either copied or implements a locking mechanism to
// prevent race conditions. The usage of `type` is user-defined.
typedef struct {
  long type;
  void* data;
} message_t;

// No public members, use methods
typedef struct {
  void* private;
} messagequeue_t;

int messagequeue_new(messagequeue_t* self);
int messagequeue_delete(messagequeue_t* self);

// Pushes a new message onto the queue. Blocks if mutex is locked
int messagequeue_push(messagequeue_t* self, const message_t* msg);
// Nonblocking version of messagequeue_push
int messagequeue_trypush(messagequeue_t* self, const message_t* msg);

// Pops a message from the queue and puts it in msg. Blocks if mutex is locked
int messagequeue_pop(messagequeue_t* self, message_t* msg);
// Nonblocking version of messagequeue_pop
int messagequeue_trypop(messagequeue_t* self, message_t* msg);

// Determines if the queue is empty. Blocks if mutex is locked.
bool messagequeue_empty(messagequeue_t* self);
// Nonblocking version of messagequeue_empty
bool messagequeue_tryempty(messagequeue_t* self);

static const struct {
  int (*new)(messagequeue_t*);
  int (*delete)(messagequeue_t*);

  int (*push)(messagequeue_t*, const message_t*);
  int (*tryPush)(messagequeue_t*, const message_t*);

  int (*pop)(messagequeue_t*, message_t*);
  int (*tryPop)(messagequeue_t*, message_t*);

  bool (*empty)(messagequeue_t*);
  bool (*tryEmpty)(messagequeue_t*);
} MessageQueue = {
  .new = &messagequeue_new,
  .delete = &messagequeue_delete,
  .push = &messagequeue_push,
  .tryPush = &messagequeue_trypush,
  .pop = &messagequeue_pop,
  .tryPop = &messagequeue_trypop,
  .empty = &messagequeue_empty,
  .tryEmpty = &messagequeue_tryempty
};

#endif // MESSAGEQUEUE_H
