struct lnode;

//List management
struct lnode* newNode     (char* word, int line);
void          pushNode    (struct lnode** head, struct lnode* node);
struct lnode* getNode     (struct lnode* head, char* word);
struct lnode* nodeGetNext (struct lnode* node);
void          deleteNode  (struct lnode** head, struct lnode* node);
void          deleteList  (struct lnode** head);

//Content Management
int   nodeGetCount  (struct lnode*);
void  nodeSetCount  (struct lnode*, int count);
int   nodeGetLine   (struct lnode*);
void  nodeSetLine   (struct lnode*, int line);
char* nodeGetWord   (struct lnode*);
