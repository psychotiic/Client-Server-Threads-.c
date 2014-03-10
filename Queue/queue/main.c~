#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <pthread.h>

#include "message-queue.h"

messagequeue_t* threadQueue;

void* threadFunc (void* arg) {
  int i;
  message_t msg;
  // 1 extra loop to give a bit of time for main to catch up
  for (i = 0; i < 6; ++i) {
    sleep(1);
    if (MessageQueue.pop(threadQueue, &msg) == ERROR_VAL) {
      if (errno != ENOMSG) {
        perror("Popping from threadQueue failed");
        return (void*)EXIT_FAILURE;
      }
      else {
        continue;
      }
    }
    printf("recieved: %s\n", (const char*)msg.data);
    free(msg.data); // we malloc'd earlier, remember? always free your mallocs!
  }
  return (void*)EXIT_SUCCESS;
}

int main (int argc, char* argv[]) {
  threadQueue = malloc(sizeof(messagequeue_t));

  if (threadQueue == NULL) {
    errno = ENOMEM;
    perror("Allocating threadQueue failed");
    return EXIT_FAILURE;
  }

  if (MessageQueue.new(threadQueue) == ERROR_VAL) {
    perror("Intializing threadQueue failed");
    return EXIT_FAILURE;
  }

  pthread_t thread;
  if (pthread_create(&thread, NULL, threadFunc, NULL) != 0) {
    perror("Creating Thread Failure");
    return EXIT_FAILURE;
  }

  int i;
  const char* text = "I am a message from the client!";
  message_t msg;
  msg.type = 1;
  for (i = 0; i < 5; ++i) {
    sleep(1);
    msg.data = malloc(strlen(text)+1); // we malloc this! don't forget to free!

    if (msg.data == NULL) {
      errno = ENOMEM;
      perror("Allocating message data failed");
      return EXIT_FAILURE;
    }

    // Copy the data to prevent race conditions
    strcpy(msg.data, text);

    if (MessageQueue.push(threadQueue, &msg) == ERROR_VAL) {
      perror(">> Pushing to Queue");
      return EXIT_FAILURE;
    }
  }

  void* retValue;
  if ((errno = pthread_join(thread, &retValue)) != 0) {
    perror(">> Joining Thread Failure");
    return EXIT_FAILURE;
  }

  if (MessageQueue.delete(threadQueue) == ERROR_VAL) {
    perror(">> Deleting Queue Failure");
    return EXIT_FAILURE;
  }
  free(threadQueue);
  threadQueue = NULL;

  if (retValue == (void*)EXIT_FAILURE)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
