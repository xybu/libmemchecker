#define _POSIX_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"list.h"

FILE *sout;
struct lnode *head = NULL;
char *firstW = "first";
char *secondW = "second";
char *thirdW = "third";
struct lnode *firstN = NULL;
struct lnode *secondN = NULL;
struct lnode *thirdN = NULL;

void failInit () {
  fprintf(sout, "\nnewNode: nodes are either in incorrect order, or head or tail are not updated properly (this prevents any further tests from being performed)\n:");
  exit(1);
}

void test_newNodeWorks() {
  struct lnode* node;
  thirdN = newNode(thirdW, 44);
  pushNode (&head, thirdN);
  if (thirdN != head) failInit ();
  secondN = newNode(secondW, 43);
  pushNode (&head, secondN);
  if (secondN != head) failInit ();
  firstN = newNode(firstW, 42);
  pushNode (&head, firstN);
  if (firstN != head) failInit ();
}

/* nodes inserted must exist */
void test_getNode() {
  test_newNodeWorks();

  if (getNode(head, firstW) != firstN)
    fprintf(sout, "\neither newNode or getNode: wrong result on head node\n");
  else putc('@', sout);
  if (getNode(head, secondW) != secondN)
    fprintf(sout, "\neither newNode or getNode: wrong result on node which is neither head nor tail\n");
  else putc('@', sout);
  if (getNode(head, thirdW) != thirdN)
    fprintf(sout, "\neither newNode or getNode: wrong result on tail node\n");
  else putc('@', sout);
  if (getNode(head, "dummy") != NULL)
    fprintf(sout, "\ngetNode: does not return NULL for non-existing node\n");
  else putc('@', sout);
}

void test_getNext() {
  test_newNodeWorks();
  if (nodeGetNext(firstN) != secondN || nodeGetNext(secondN) != thirdN)
    fprintf(sout, "\neither newNode or nodeGetNext: nodes appear out of order\n");
  else putc('@', sout);
}

void test_getWord() {
  test_newNodeWorks();
  if (strcmp(nodeGetWord(firstN), firstW) != 0)
    fprintf(sout, "\neither newNode or nodeGetWord: stored word changed\n");
  else putc('@', sout);
  if (nodeGetWord(firstN) == firstW)
    fprintf(sout, "\nnewNode: stored word in space not allocated by list code\n");
  else putc('@', sout);
}

void test_setCount() {
  test_newNodeWorks();
  nodeSetCount(firstN, 2);
  if (nodeGetCount (firstN) != 2)
    fprintf(sout, "\neither newNode or nodeSetCount: no count update seen\n");
  else putc('@', sout);
}

void test_getCount() {
  test_newNodeWorks();
  /* test if initial count is 1 */
  if (nodeGetCount(firstN) != 1)
    fprintf(sout, "\neither newNode or nodeGetCount: initial count is not 1\n");
  else putc('@', sout);
}

void test_getLine() {
  test_newNodeWorks();
  /* test if line field is updated */
  if (nodeGetLine(firstN) != 42)
    fprintf(sout, "\nnodeGetLine: unexpected return value of line\n");
  else putc('@', sout);
}

/* what if the node is not one on the list?? */
void test_deleteNode() {
  test_newNodeWorks();
  deleteNode(&head, secondN);
  if (nodeGetNext(firstN) != thirdN)
    fprintf(sout, "\neither deleteNode or nodeGetNext: list not in right order after node deletion\n");
  else putc('@', sout);

  deleteNode(&head, firstN);
  if (head != thirdN)
    fprintf(sout, "\ndeleteNode: wrong result after deleting the first node\n");
  else putc('@', sout);

  deleteNode(&head, thirdN);
  if (head != NULL)
    fprintf(sout, "\ndeleteNode: wrong result after deleting the only node in list\n");
  else putc('@', sout);
}

int test_deleteList() {
  test_newNodeWorks();

  deleteList(&head);
  if (head != NULL)
    fprintf(sout, "\ndeleteList: list not empty after deletion\n");
  else putc('@', sout);
}


int main(int argc, char* argv[]) {
  sout = fdopen(dup(17), "w");
  if (argc < 2) {
    fprintf(sout, "tell me which function you want to test\n");
    fclose(sout);
    exit(1);
  }
  char* testee = argv[1];

  if (!strcmp(testee, "newNode"))
    test_newNodeWorks();
  else if (!strcmp(testee, "getNode"))
    test_getNode();
  else if (!strcmp(testee, "nodeGetNext"))
    test_getNext();
  else if (!strcmp(testee, "nodeGetWord"))
    test_getWord();
  else if (!strcmp(testee, "nodeSetCount"))
    test_setCount();
  else if (!strcmp(testee, "nodeGetCount"))
    test_getCount();
  else if (!strcmp(testee, "nodeGetLine"))
    test_getLine();
  else if (!strcmp(testee, "deleteNode"))
    test_deleteNode();
  else if (!strcmp(testee, "deleteList"))
    test_deleteList();
  else {
    fprintf(sout, "unknown function name: %s\n", testee);
    exit(1);
  }

  deleteList(&head);
  putc(':', sout);
  fclose(sout);
  return 0;
}

