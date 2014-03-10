#include "message-queue.h"

typedef struct message_node_s {
  void* next;
  message_t data;
} message_node_t;

typedef struct {
  pthread_mutex_t* mutex;
  message_node_t* head;
} messagequeue_p;

int messagequeue_new (messagequeue_t* self) {
  if (self == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  self->private = malloc(sizeof(messagequeue_p));

  if (self->private == NULL) {
    errno = ENOMEM;
    return ERROR_VAL;
  }

  messagequeue_p* private = self->private;

  private->mutex = malloc(sizeof(pthread_mutex_t));

  if (self->private == NULL) {
    free(private);
    self->private = NULL;

    errno = ENOMEM;
    return ERROR_VAL;
  }

  if ((errno = pthread_mutex_init(private->mutex, NULL)) != 0) {
    free(private->mutex);
    private->mutex = NULL;

    free(private);
    self->private = NULL;

    return ERROR_VAL;
  }

  private->head = NULL;

  return SUCCESS_VAL;
}

int messagequeue_delete (messagequeue_t* self) {
  if (self->private != NULL) {
    messagequeue_p* private = self->private;

    if (private->mutex != NULL) {
      if (pthread_mutex_destroy(private->mutex) == EBUSY) {
        errno = EBUSY;
        return ERROR_VAL;
      }
      free(private->mutex);
      private->mutex = NULL;
    }

    if (private->head != NULL) {
      message_node_t* conductor = private->head;
      while (conductor != NULL) {
        message_node_t* next = conductor->next;
        free(conductor);
        conductor = next;
      }

      private->head = NULL;
    }

    free(private);
    self->private = NULL;
  }

  return SUCCESS_VAL;
}

int messagequeue_push_p (messagequeue_t* self, const message_t* msg) {
  messagequeue_p* private = self->private;

  message_node_t* node = malloc(sizeof(message_node_t));

  if (node == NULL) {
    errno = ENOMEM;
    return ERROR_VAL;
  }

  node->next = (message_node_t*)private->head;
  node->data.type = msg->type;
  node->data.data = msg->data;

  private->head = node;

  return SUCCESS_VAL;
}

int messagequeue_push (messagequeue_t* self, const message_t* msg) {
  if (self == NULL || self->private == NULL || msg == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  messagequeue_p* private = self->private;

  if (private->mutex == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  if ((errno = pthread_mutex_lock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  int ret = messagequeue_push_p(self, msg);
  int errno_save = errno;

  if ((errno = pthread_mutex_unlock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  errno = errno_save;
  return ret;
}

int messagequeue_trypush (messagequeue_t* self, const message_t* msg) {
  if (self == NULL || self->private == NULL || msg == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  messagequeue_p* private = self->private;

  if (private->mutex == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  if ((errno = pthread_mutex_trylock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  int ret = messagequeue_push_p(self, msg);
  int errno_save = errno;

  if ((errno = pthread_mutex_unlock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  errno = errno_save;
  return ret;
}

int messagequeue_pop_p (messagequeue_t* self, message_t* msg) {
  messagequeue_p* private = self->private;

  if (private->head == NULL) {
    errno = ENOMSG;
    return ERROR_VAL;
  }

  message_node_t* head = private->head;
  msg->type = head->data.type;
  msg->data = head->data.data;

  message_node_t* next = head->next;
  free(head);
  private->head = next;

  return SUCCESS_VAL;
}

int messagequeue_pop(messagequeue_t* self, message_t* msg) {
  if (self == NULL || self->private == NULL || msg == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  messagequeue_p* private = self->private;

  if (private->mutex == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  if ((errno = pthread_mutex_lock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  int ret = messagequeue_pop_p(self, msg);
  int errno_save = errno;

  if ((errno = pthread_mutex_unlock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  errno = errno_save;
  return ret;
}

int messagequeue_trypop(messagequeue_t* self, message_t* msg) {
  if (self == NULL || self->private == NULL || msg == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  messagequeue_p* private = self->private;

  if (private->mutex == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  if ((errno = pthread_mutex_trylock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  int ret = messagequeue_pop_p(self, msg);
  int errno_save = errno;

  if ((errno = pthread_mutex_unlock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  errno = errno_save;
  return ret;
}

bool messagequeue_empty_p (messagequeue_t* self) {
  messagequeue_p* private = self->private;

  if (private->head == NULL) {
    return true;
  }

  return false;
}

bool messagequeue_empty(messagequeue_t* self) {
  if (self == NULL || self->private == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  messagequeue_p* private = self->private;

  if (private->mutex == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  if ((errno = pthread_mutex_lock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  bool ret = messagequeue_empty_p(self);
  int errno_save = errno;

  if ((errno = pthread_mutex_unlock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  errno = errno_save;
  return ret;
}

bool messagequeue_tryempty(messagequeue_t* self) {
  if (self == NULL || self->private == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  messagequeue_p* private = self->private;

  if (private->mutex == NULL) {
    errno = EINVAL;
    return ERROR_VAL;
  }

  if ((errno = pthread_mutex_trylock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  bool ret = messagequeue_empty_p(self);
  int errno_save = errno;

  if ((errno = pthread_mutex_unlock(private->mutex)) != 0) {
    return ERROR_VAL;
  }

  errno = errno_save;
  return ret;
}
