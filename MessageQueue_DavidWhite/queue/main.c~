#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include "msgQueue.h"

messagequeue_t* Queue;

void* threadFucntion (void* arg) {
  int i;
  message_t msg;
  // 1 extra loop to give a bit of time for main to catch up
  for (i = 0; i < 6; ++i) {
    sleep(1);
	printf(">> Queue Initializing\n");
	printf(">> Please Wait...\n");
	
    if (MessageQueue.pop(Queue, &msg) == ERROR_VAL) {
      if (errno != ENOMSG) {
        perror(">> Pop - Thread Queue Failure\n");
        return (void*)EXIT_FAILURE;
      }
      else {
        continue;
      }
    }
    printf("Client Says: %s\n\n", (const char*)msg.data);
    free(msg.data); // free malloc
  }
  return (void*)EXIT_SUCCESS;
}

int main (int argc, char* argv[]) {
FILE *file; 
file = fopen("logFile.xml","rw+"); /* apend file (add text to 
a file or create a file if it does not exist.*/ 

printf(">> Server Client Queue Starting Up...\n");
  Queue = malloc(sizeof(messagequeue_t));

  if (Queue == NULL) {
    errno = ENOMEM;
    perror(">> Allocating Queue Failure\n");
    return EXIT_FAILURE;
  }

  if (MessageQueue.new(Queue) == ERROR_VAL) {
    perror("Intializing Queue failed");
    return EXIT_FAILURE;
  }

  pthread_t thread;
printf(">> Thread Created...\n");
  if (pthread_create(&thread, NULL, threadFucntion, NULL) != 0) {
    perror("Creating Thread Failure\n");
    return EXIT_FAILURE;
  }
 

  int i;
  const char* text = "I am a message from the client!";
  message_t msg;
  msg.type = 1;
  for (i = 1; i < 6; ++i) {
    sleep(1);
    msg.data = malloc(strlen(text)+1); 
fprintf(file,"%s","<xml>\n");
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","0\n");
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","<command>\n");
fprintf(file,"%s","Write\n");
fprintf(file,"%s","</command\n");
fprintf(file,"%s","<key>\n");
fprintf(file,"%d\n",i); // this is the data's key
fprintf(file,"%s","</key>\n");
fprintf(file,"%s","<data>\n");
fprintf(file,"%s",text);
fprintf(file,"%s","</data>\n");
fprintf(file,"%s","</xml>\n");

fprintf(file,"%s","<xml>\n");  // this is the reads command
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","0\n");
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","<command>\n");
fprintf(file,"%s","Read\n");
fprintf(file,"%s","</command\n");
fprintf(file,"%s","<key>\n");
fprintf(file,"%d\n",i); // this is the data's key
fprintf(file,"%s","</key>\n");
fprintf(file,"%s","</xml>\n");

fprintf(file,"%s","<xml>\n");  // writes reply
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","0\n");
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","<reply>\n");
fprintf(file,"%s","Write\n");
fprintf(file,"%s","</reply\n");
fprintf(file,"%s","<key>\n");
fprintf(file,"%d\n",i); // this is the data's key
fprintf(file,"%s","</key>\n");
fprintf(file,"%s","</xml>\n");

fprintf(file,"%s","<xml>\n");
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","0\n");
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","<command>\n");
fprintf(file,"%s","Read\n");
fprintf(file,"%s","</command\n");
fprintf(file,"%s","<key>\n");
fprintf(file,"%d\n",i); // this is the data's key
fprintf(file,"%s","</key>\n");
fprintf(file,"%s","<data>\n");
fprintf(file,"%s",text);
fprintf(file,"%s","</data>\n");
fprintf(file,"%s","</xml>\n");
    if (msg.data == NULL) {
      errno = ENOMEM;
      perror(">> Allocating message data failed\n");
      return EXIT_FAILURE;
    }
    strcpy(msg.data, text);

    if (MessageQueue.push(Queue, &msg) == ERROR_VAL) {
      perror(">> Pushing to Queue\n");
      return EXIT_FAILURE;
free(msg.data);
    }



  }

  void* retValue;
  if ((errno = pthread_join(thread, &retValue)) != 0) {
    perror(">> Joining Thread Failure\n");
    return EXIT_FAILURE;
  }

  if (MessageQueue.delete(Queue) == ERROR_VAL) {
    perror(">> Deleting Queue Failure\n");
    return EXIT_FAILURE;
  }
  free(Queue);
  printf(">> Queue was Released from Memory\n");
  Queue = NULL;
fprintf(file,"%s","<xml>\n");
fprintf(file,"%s","<ARQ>\n");
fprintf(file,"%s","0\n");
fprintf(file,"%s","</ARQ>\n");
fprintf(file,"%s","<command>\n");
fprintf(file,"%s","Shutdown\n");
fprintf(file,"%s","</commmand>\n");
fprintf(file,"%s","<key>\n");
fprintf(file,"%s","Shutdown\n");
fprintf(file,"%s","</key>\n");
fprintf(file,"%s","<xml>\n");

  if (retValue == (void*)EXIT_FAILURE)
    return EXIT_FAILURE;

printf(">> Program Shutting Down...\n\n");
fclose(file); /*done!*/ 
	
  return EXIT_SUCCESS;
}
