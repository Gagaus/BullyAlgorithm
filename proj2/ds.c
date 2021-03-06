/*
 *  Distributed system implementation using IPC.
 * 
 *  Todos os processos de envio de mensagens usados pelos processos estão
 * neste arquivo. Note que ele controla o envio de mensagens: quando um processo
 * decide comunicar-se com outro usando estas funções, note que o monitor,
 * processo 0, também é avisado. Dessa forma, ele sabe o que imprimir 
 * na tela e no log.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds.h"

int queue_id[N];

/* Get N communication queues. */
void get_queues() {
  int i;
  key_t key;

  for (i = 0, key = QUEUE_KEY_PREFIX; i < N; i++, key++)
    if ((queue_id[i] = msgget(key+i, IPC_CREAT | 0700)) == -1) {
      perror("msgget error");
      exit(2);
    }
}

/* Send a message to Pj */
void send_message(int j, const void* buffer, size_t msgsize) {
  ((Msgbuf*)buffer)->receiver = j;
  if (msgsnd(queue_id[j], buffer, msgsize, 0) == -1) {
    perror("msgsnd error");
    exit(2);
  }
  if (((Msgbuf*)buffer)->c != DEAD_WARNING && msgsnd(queue_id[MONITOR_PID], buffer, msgsize, 0) == -1) {
    perror("msgsnd to monitor error");
    exit(2);
  }  
}

/* Broadcast a message to all processes, including itself */
void broadcast(const void* buffer, size_t msgsize) {
  int i;
  long aux= ((Msgbuf*)buffer)->mtype;
  for (i = 0; i < N; i++){
    ((Msgbuf*)buffer)->mtype = aux;
    if (msgsnd(queue_id[i], buffer, msgsize, 0) == -1) {
      perror("broad-msgsnd error");
      exit(2);
    }  
  }
}

/* Wait for a new message */ 
void receive_message(int pid, void* buffer, size_t msgsize) {
  if (msgrcv(queue_id[pid], buffer, msgsize, 
	     DS_MESSAGE_TYPE, 0) == -1) {
    perror("msgrcv error");
    exit(2);
  }	     
}

/* Return -1 immediately if no message is available in the queue. 
   Return 0 and a new message in buffer otherwise. */
int nowait_receive_message(int pid, void* buffer, size_t msgsize) {
  if (msgrcv(queue_id[pid], buffer, msgsize, 
	     DS_MESSAGE_TYPE, IPC_NOWAIT) == -1) {
    if (errno == ENOMSG)
      return -1;
    perror("nowait msgrcv error");
    exit(2);
  }
  return 0;
}
