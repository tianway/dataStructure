//双链表（带头结点）
#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int data;
    struct DNode *prior, *next;
} DNode, *DLinkList;

bool InitDLinkList(DLinkList &L) {
    L = (DNode *) malloc(sizeof(DNode));
    if (L == NULL) {
        return false;
    }
    L->next = NULL;
    L->prior = NULL;
    return true;
}

bool IsEmpty(DLinkList L) {
    return L->next == NULL;
}

bool DestroyList(DLinkList &L) {
    while (L->next != NULL) {
        DNode *p = L->next;
        L->next = p->next;
        free(p);
    }
    free(L);
    L = NULL;
    return true;
}

DNode *LocateElem(DLinkList L, int e) {
    DNode *p = L->next;
    while (p != NULL && p->data != e) {
        p = p->next;
    }
    return p;
}

DNode *GetElem(DLinkList L, int i) {
    if (i < 0) {
        printf("查找位序不合法！\n");
        return NULL;
    }
    DNode *p = L;
    int j = 0;
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

bool InsertNextNode(DNode *p, int e) {
    if (p == NULL) {
        return false;
    }
    DNode *s = (DNode *) malloc(sizeof(DNode));
    if (s == NULL) {
        return false;
    }
    s->data = e;
    s->next = p->next;
    if (p->next != NULL) {
        p->next->prior = s;
    }
    p->next = s;
    s->prior = p;
    return true;
}

bool InsertPriorNode(DNode *p, int e) {
    if (p == NULL || p->prior == NULL) {
        return false;
    }
    DNode *s = (DNode *) malloc(sizeof(DNode));
    if (s == NULL) {
        return false;
    }
    s->data = e;
    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;
    return true;
}

bool ListInsert(DLinkList &L, int i, int e) {
    DNode *p = GetElem(L, i - 1);
    return InsertNextNode(p, e);
}

bool ListInsert_Prior(DLinkList &L, int i, int e) {
    DNode *p = GetElem(L, i);
    return InsertPriorNode(p, e);
}

bool DeleteNextNode(DNode *p, int &e) {
    if (p == NULL || p->next == NULL) {
        return false;
    }
    DNode *q = p->next;
    e = q->data;
    p->next = q->next;
    if (q->next != NULL) {
        q->next->prior = p;
    }
    free(q);
    return true;
}

bool DeletePriorNode(DNode *p, int &e) {
    if (p == NULL || p->prior == NULL || p->prior->prior == NULL) {
        return false;
    }
    DNode *q = p->prior;
    e = q->data;
    p->prior = q->prior;
    if (q->prior != NULL) {
        q->prior->next = p;
    }
    free(q);
    return true;
}

bool ListDelete(DLinkList &L, int i, int &e) {
    if (i < 1) {
        printf("删除的位置不合法！\n");
        return false;
    }
    DNode *p = GetElem(L, i - 1);
    return DeleteNextNode(p, e);
}

bool ListDelete_Prior(DLinkList &L, int i, int &e) {
    if (i < 1) {
        printf("删除的位置不合法！\n");
        return false;
    }
    DNode *p = GetElem(L, i + 1);
    return DeletePriorNode(p, e);
}

DLinkList ListCreate_HeadInsert(DLinkList &L) {
    int x;
    InitDLinkList(L);
    scanf("%d", &x);
    while (x != 0) {
        InsertNextNode(L, x);
        scanf("%d", &x);
    }
    return L;
}

DLinkList ListCreate_TailInsert(DLinkList &L) {
    int x;
    InitDLinkList(L);
    DNode *r = L;
    scanf("%d", &x);
    while (x != 0) {
        InsertNextNode(r, x);
        r = r->next;
        scanf("%d", &x);
    }
    return L;
}

void PrintList(DLinkList L) {
    DNode *p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    DLinkList L;
    int e;

    // InitDLinkList(L);
    // ListInsert(L, 1, 1);
    // ListInsert(L, 2, 2);
    // ListInsert(L, 3, 3);
    // ListInsert_Prior(L, 2, 4);
    // PrintList(L);
    // ListDelete(L, 2, e);
    // ListDelete_Prior(L, 2, e);
    // PrintList(L);

    // ListCreate_HeadInsert(L);
    // PrintList(L);

    ListCreate_TailInsert(L);
    PrintList(L);

    DestroyList(L);
    return 0;
}
