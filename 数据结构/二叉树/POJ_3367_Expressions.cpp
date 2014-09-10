#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    char ch;
    struct Node *lChild, *rChild;
} *root, nodes[10010];
stack<Node*> s, ans;
queue<Node*> q;
string line;
int nCase, cnt;

void init() {
    cnt = 0;
}

void buildTree() {
    for (int i = 0; i < line.length(); i++) {
        if (line[i] >= 'a' && line[i] <= 'z') {
            //Node *node = (Node*)malloc(sizeof(Node*));
            Node *node = &nodes[cnt++];
            node->ch = line[i];
            node->lChild = node->rChild = NULL;
            s.push(node);
        } else if (line[i] >= 'A' && line[i] <= 'Z') {
            //Node *node = (Node*)malloc(sizeof(Node*));
            Node *node = &nodes[cnt++];
            node->rChild = s.top();  s.pop();
            node->lChild = s.top();  s.pop();
            node->ch = line[i];
            s.push(node);
        }
    }
    root = s.top();
    s.pop();
}

void bfs() {
    q.push(root);

    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();

        ans.push(cur);

        if (cur->lChild != NULL) q.push(cur->lChild);
        if (cur->rChild != NULL) q.push(cur->rChild);
    }
}

void output() {
    while (!ans.empty()) {
        cout << ans.top()->ch;
        ans.pop();
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        cin >> line;
        buildTree();
        bfs();
        output();
    }
    return 0;
}
