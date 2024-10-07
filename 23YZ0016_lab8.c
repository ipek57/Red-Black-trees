#include <stdio.h>
#include <stdlib.h>

struct RedBlackTreeNode {
    struct RedBlackTreeNode *left;
    int data;
    struct RedBlackTreeNode *right;
    char colour;
    struct RedBlackTreeNode *parent;
};

struct RedBlackTreeNode *root = NULL;

struct RedBlackTreeNode *grand_parent(struct RedBlackTreeNode *ptr);
struct RedBlackTreeNode *uncle(struct RedBlackTreeNode *ptr);
void Lrotation(struct RedBlackTreeNode *x);
void Rrotation(struct RedBlackTreeNode *x);
void durum1(struct RedBlackTreeNode *ptr);
void durum2(struct RedBlackTreeNode *ptr);
void durum3(struct RedBlackTreeNode *ptr);
void durum4(struct RedBlackTreeNode *ptr);
void durum5(struct RedBlackTreeNode *ptr);

struct RedBlackTreeNode *grand_parent(struct RedBlackTreeNode *ptr) {
    if (ptr != NULL && ptr->parent != NULL)
        return ptr->parent->parent;
    else
        return NULL;
}

struct RedBlackTreeNode *uncle(struct RedBlackTreeNode *ptr) {
    struct RedBlackTreeNode *gp = grand_parent(ptr);
    if (gp == NULL)
        return NULL;

    if (ptr->parent == gp->left)
        return gp->right;
    else
        return gp->left;
}

void Lrotation(struct RedBlackTreeNode *x) {
    struct RedBlackTreeNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Rrotation(struct RedBlackTreeNode *x) {
    struct RedBlackTreeNode *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void durum1(struct RedBlackTreeNode *ptr) {
    if (ptr->parent == NULL) {
        ptr->colour = 'B';
    } else {
        durum2(ptr);
    }
}

void durum2(struct RedBlackTreeNode *ptr) {
    if (ptr->parent->colour == 'B') {
        return;
    } else {
        durum3(ptr);
    }
}

void durum3(struct RedBlackTreeNode *ptr) {
    struct RedBlackTreeNode *uncleNode = uncle(ptr);
    struct RedBlackTreeNode *grandparent = grand_parent(ptr);

    if (uncleNode != NULL && uncleNode->colour == 'R') {
        ptr->parent->colour = 'B';
        uncleNode->colour = 'B';
        grandparent->colour = 'R';
        durum1(grandparent);
    } else {
        durum4(ptr);
    }
}

void durum4(struct RedBlackTreeNode *ptr) {
    struct RedBlackTreeNode *grandparent = grand_parent(ptr);

    if ((ptr == ptr->parent->right) && (ptr->parent == grandparent->left)) {
        Lrotation(ptr->parent);
        ptr = ptr->left;
    } else if ((ptr == ptr->parent->left) && (ptr->parent == grandparent->right)) {
        Rrotation(ptr->parent);
        ptr = ptr->right;
    }
    durum5(ptr);
}

void durum5(struct RedBlackTreeNode *ptr) {
    struct RedBlackTreeNode *grandparent = grand_parent(ptr);

    ptr->parent->colour = 'B';
    grandparent->colour = 'R';

    if (ptr == ptr->parent->left) {
        Rrotation(grandparent);
    } else {
        Lrotation(grandparent);
    }
}

struct RedBlackTreeNode *insert(struct RedBlackTreeNode *root, int data) {
    struct RedBlackTreeNode *newnode = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    newnode->data = data;
    newnode->colour = 'R';
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;

    if (root == NULL) {
        newnode->colour = 'B'; 
        return newnode;
    }

    struct RedBlackTreeNode *current = root;
    struct RedBlackTreeNode *parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newnode->parent = parent;

    if (data < parent->data)
        parent->left = newnode;
    else
        parent->right = newnode;

    durum1(newnode);

    while (root->parent != NULL) {
        root = root->parent;
    }

    return root;
}

int height(struct RedBlackTreeNode* root) {
    if (root == NULL)
        return 0;
    else {

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
 
        if (leftHeight > rightHeight)
            return(leftHeight + 1);
        else return(rightHeight + 1);
    }
}

void printGivenLevel(struct RedBlackTreeNode* root, int level, int isLastLevel) {
    if (root == NULL)
        return;
    if (level == 1) {
        if (root->parent) {
            printf("%d %c (%d %c) ", root->data, root->colour, root->parent->data, (root == root->parent->left) ? 'L' : 'R');
        } else {
            printf("%d %c ", root->data, root->colour);
        }
    } else if (level > 1) {
        printGivenLevel(root->left, level-1, 0);
        printGivenLevel(root->right, level-1, 0);
    }
}

void levelOrderTraversal(struct RedBlackTreeNode* root) {
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++) {
        printGivenLevel(root, i, i == h);
        printf("\n");
    }
}

void inOrderTraversal(struct RedBlackTreeNode *n) {
    if (n == NULL) {
        return;
    }

    inOrderTraversal(n->left);
    printf("%d\n", n->data);
    inOrderTraversal(n->right);
}

int main() {
    int data;
    while (1) {
        scanf("%d", &data);
        if (data == -1) {
            break;
        }
        root = insert(root, data);
    }
    inOrderTraversal(root);
	printf("\n");
    levelOrderTraversal(root);

    return 0;
}

