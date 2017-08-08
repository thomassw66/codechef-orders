#include <iostream>

#define MAX_INPUT_SIZE 200000

struct Node {
        Node * next;
        Node * prev;
        int i;
        int sl;
};

int main(int argc, char const *argv[]) {

        int test_cases;
        int soldiers;
        int output[MAX_INPUT_SIZE+1];
        Node * list;
        Node * l;
        Node * i;
        Node * n;
        std::ios_base::sync_with_stdio(false);

        std::cin >> test_cases;
        while (test_cases) {
                std::cin >> soldiers;
                l = NULL;
                n = NULL;
                i = NULL;
                list = NULL;

                for (int i = 1; i < soldiers+1; i++) {
                        Node * node = (Node *)malloc(sizeof(Node));
                        node->prev = NULL;
                        node->next = NULL;
                        // if (node == NULL) { std::cout<<"fuck this shit"<<std::endl; return 1;}

                        if (list == NULL) {
                                list = node;
                        } else {
                                l->next = node;
                                node->prev = l;
                        }

                        std::cin >> node->sl;
                        node->i = i;

                        l = node;
                }

                for (l = list; l != NULL;) {
                        n = l->next;

                        int steps_left = l->sl;

                        if (steps_left > 0) {
                                i = l;

                                if (l->next != NULL) l->next->prev = l->prev;
                                if (l->prev != NULL) l->prev->next = l->next;

                                for (;steps_left > 0; steps_left--) i = i->prev; // i is not NULL

                                l->next = i;
                                l->prev = i->prev;

                                if (i->prev == NULL) { // we've moved to the head of the list
                                        list = l;
                                } else {
                                        i->prev->next = l;
                                }

                                i->prev = l;
                        }
                        l = n;
                }
                n = list;
                for (int i = 1; i < soldiers+1; i++) {
                        output[n->i] = i;
                        n = n->next;

                        // free(n->prev);
                }
                for (int i = 1; i < soldiers+1; i++) {
                        std::cout << output[i];
                        std::cout << " ";
                }
                std::cout << '\n';
                test_cases--;
        }

        return 0;
}
