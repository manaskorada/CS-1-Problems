#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node {
    Node * children[26];
    int flag; // number of words at this particular location
    int subTrieCount; // stores the number of words in the subtrie
};

Node * createNode() {
    Node * res = (Node *) malloc(sizeof(Node));
    res->flag = 0;
    res->subTrieCount = 0;
    for(int i = 0; i < 26; i++) {
        res->children[i] = NULL;
    }
    return res;
}

Node * insert(Node * root, char * word) {
    if (root == NULL) {
        root = createNode();
    }
    root->subTrieCount++; // KEY
    if (word[0] == '\0') {
        root->flag++;
        return root;
    }
    root->children[word[0] - 'a'] = insert(root->children[word[0] - 'a'], word + 1);
    return root;
}

// Finds the k-th word in a subtrie
// if none exists returns 0
// if one exists returns 1
int getKth(Node * root, int k, char * res) {
    if (root == NULL) return 0;
    if (root->subTrieCount <= k) return 0;
    if (k == 0 && root->flag) {
        res[0] = '\0';
        return 1;
    }
    k -= root->flag;
    for (int i = 0; i < 26; i++) {
        res[0] = i + 'a';
        if (getKth(root->children[i], k, res + 1)) return 1;
        if (root->children[i])
        k -= root->children[i]->subTrieCount;
    }
    return 0;
}

void swap(Node * root, char a, char b) {
    if (!root) return;
    Node * tmp = root->children[a-'a'];
    root->children[a-'a'] = root->children[b-'a'];
    root->children[b-'a'] = tmp;
    for (int i = 0; i < 26; i++) {
        swap(root->children[i], a, b);
    }

}

int main(int argc, char ** argv) {
    Node * root = NULL;
    FILE * ifp = fopen(argv[1], "r");
    char word[1000];
    while (EOF != fscanf(ifp, "%s", word)) {
        fprintf(stderr, "INSERTING %s...\n", word);
        fflush(stderr);
        root = insert(root, word);
    }
    fprintf(stderr, "FINISHED READING...\n");
    fflush(stderr);
    fclose(ifp);
    ifp = fopen(argv[2], "r");
    while (EOF != fscanf(ifp, "%s", word)) {
        if (!strcmp(word, "READ")) {
            int index;
            fscanf(ifp, "%d", &index);
            fprintf(stderr, "READ %d...\n", index);
            fflush(stderr);
            getKth(root, index, word);
            printf("%s ", word);
        } else {
            char a, b;
            fscanf(ifp, " %c %c", &a, &b);
            swap(root, a, b);
        }
    }
    printf("\n");
    fclose(ifp);
    return 0;
}