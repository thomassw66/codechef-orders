// #include <stdlib.h>
#include <iostream>

#define BLACK 0
#define RED 1
#define MAX_INPUT_SIZE 200000

struct tree {
        int info;
        int children;
        int color;
        struct tree *p;
        struct tree *left;
        struct tree *right;
};

struct tree *nil;
struct tree * rt;

int counter;

struct tree *stree(struct tree *root, struct tree *r, int info, int steps_left);
struct tree *stree2(struct tree *root, int info, int steps_left);
void right_rotate(struct tree *y);
void left_rotate(struct tree *x);
void tree_insert(int info, int steps_left);
void inorder(struct tree *r, int *buffer);
void rb_tree_insert_fixup(struct tree *l);
void print_tree(struct tree *root, int l);

int main(int argc, char const *argv[]) {
        int i;
        int test_cases;
        int soldiers;
        int input[MAX_INPUT_SIZE+1];
        int output[MAX_INPUT_SIZE+1];

        std::cin >> test_cases;
        while (test_cases) {
                std::cin >> soldiers;
                for (i=1; i<soldiers+1; i++) {
                        std::cin >> input[i];
                }
                rt = NULL;
                for(i=1; i<soldiers+1; ++i) {
                        tree_insert(i, input[i]);
                }
                counter = 1;
                inorder(rt, output);
                for (i=1; i<soldiers+1; ++i) {
                        std::cout << output[i] << " ";
                }

                std::cout << std::endl;

                test_cases--;
        }
        return 0;
}

struct tree *stree2(struct tree *root, int info, int steps_left) {
        struct tree *r;

        if (!nil) {
                nil = (struct tree *) malloc(sizeof(struct tree));
                nil->color = BLACK;
                nil->info = NULL;
                nil->p = NULL;
                nil->left = NULL;
                nil->right = NULL;
                nil->children = -1;
        }
        if (!root || root == nil) {
                r = (struct tree *) malloc(sizeof(struct tree));
                if (!r) {
                        printf("Out of memory\n");
                        exit(0);
                }
                r->left = nil;
                r->right = nil;
                r->info = info;
                r->children = 0;
                r->color = BLACK;
                r->p = nil;
                return r;
        }
        r = root;
        while (1) {
                r->children++;
                // printf("steps_left: %d\tr->children: %d\tr->r->children: %d\n", steps_left, r->children-1, r->right->children);
                if (steps_left > r->right->children + 1) {
                        steps_left = steps_left - (r->right->children + 2); // right children & r
                        if (r->left == nil) {
                                struct tree *n = (struct tree*) malloc(sizeof(struct tree));
                                if (!n) {
                                        printf("Out of memory\n");
                                        exit(0);
                                }
                                n->left = nil;
                                n->right = nil;
                                n->info = info;
                                n->children = 0;
                                n->color = RED;
                                n->p = r;
                                r->left = n;
                                return n;
                        }
                        r = r->left;
                } else {
                        if (r->right == nil) {
                                struct tree *n = (struct tree*) malloc(sizeof(struct tree));
                                if (!n) {
                                        printf("Out of memory\n");
                                        exit(0);
                                }
                                n->left = nil;
                                n->right = nil;
                                n->info = info;
                                n->children = 0;
                                n->color = RED;
                                n->p = r;
                                r->right = n;
                                return n;
                        }
                        r = r->right;
                }
        }
}

void tree_insert(int info, int steps_left) {
        if (!rt) {
                // rt = stree(rt, rt, info, steps_left);
                rt = stree2(rt, info, steps_left);
                // inorder(rt); printf("\n");
                return;
        }
        // struct tree *leaf = stree2(rt, rt, info, steps_left);
        struct tree *leaf = stree2(rt, info, steps_left);
        rb_tree_insert_fixup(leaf);
        // inorder(rt); printf("\n");
}

void rb_tree_insert_fixup(struct tree *z) {
        struct tree *y;
        while (z->p->color == RED) {
                if (z->p == z->p->p->left) {
                        y = z->p->p->right;
                        if (y->color == RED) { // CASE 1
                                z->p->color = BLACK;
                                y->color = BLACK;
                                z->p->p->color = RED;
                                z = z->p->p;
                        } else {
                                if (z == z->p->right) { // CASE 2
                                        z = z->p;
                                        left_rotate(z);
                                }
                                // CASE 2 & 3
                                z->p->color = BLACK;
                                z->p->p->color = RED;
                                right_rotate(z->p->p);
                        }
                } else {
                        y = z->p->p->left;
                        if (y->color == RED) { // CASE 1
                                z->p->color = BLACK;
                                y->color = BLACK;
                                z->p->p->color = RED;
                                z = z->p->p;
                        } else {
                                if (z == z->p->left) { // CASE 2
                                        z = z->p;
                                        right_rotate(z);
                                }
                                // CASE 2 & 3
                                z->p->color = BLACK;
                                z->p->p->color = RED;
                                left_rotate(z->p->p);
                        }
                }
        }
        rt->color = BLACK;
}

void left_rotate(struct tree *x) {
        struct tree *y = x->right;

        int alpa_children = x->left->children;
        int beta_children = y->left->children;
        int gamma_children = y->right->children;

        x->right = y->left;
        if (y->left != nil) y->left->p = x;
        y->p = x->p;
        if (x->p == nil) rt = y;
        else if (x == x->p->left) x->p->left = y;
        else x->p->right = y;
        y->left = x;
        x->p = y;

        // update children count
        x->children = alpa_children + beta_children + 2;
        y->children = x->children + gamma_children + 2;
}

void right_rotate(struct tree *y) {
        struct tree *x = y->left;

        int alpa_children = x->left->children;
        int beta_children = x->right->children;
        int gamma_children = y->right->children;

        y->left = x->right;
        if (x->right != nil) x->right->p = y;
        x->p = y->p;
        if (y->p == nil) rt = x;
        else if (y == y->p->right) y->p->right = x;
        else y->p->left = x;
        x->right = y;
        y->p = x;

        // update children count
        y->children = beta_children + gamma_children + 2;
        x->children = y->children + alpa_children + 2;
}

void print_tree (struct tree *r, int l) {
        int i;
        if (!r || r == nil) return;

        print_tree(r->left, l+1);
        printf("%d ", r->children);
        for(i=0; i<l; ++i) printf("  ");
        printf("%d\n", r->info);
        print_tree(r->right, l+1);
}

void inorder(struct tree *r, int *buffer) {
        if (!r || r == nil) return;
        inorder(r->left, buffer);
        buffer[r->info] = counter++;
        inorder(r->right, buffer);
}

/// modified binary tree
//  property:
//  the number of elements in the left subtree must be greater than or equal to steps_left at the end of the algorithm
// if we add Node n to the left subtree and steps
// there will never b more steps left than nodes in the tree
// KNOW:
// if steps left = 0 put n at the rightmost part of the tree
// if steps left = number of elements in tree put n at the leftmost part
// if
