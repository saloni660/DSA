#include <bits/stdc++.h>
using namespace std;
#define MAX 50

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

Node* construct(int r[][MAX], int i, int j) {
    if (i > j) return NULL;
    int rootIdx = r[i][j];
    Node* root = new Node(rootIdx);
    root->left = construct(r, i, rootIdx - 1);
    root->right = construct(r, rootIdx + 1, j);
    return root;
}

Node* optimalbst(int p[], int q[], int n, int w[][MAX], int c[][MAX], int r[][MAX]) {
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            c[i][j] = INT_MAX;
            for (int k = i + 1; k <= j; k++) {
                int cost = c[i][k - 1] + c[k][j] + w[i][j];
                if (cost < c[i][j]) {
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
        }
    }

    cout << "\nCost of optimal BST is: " << c[0][n] << endl;
    return construct(r, 1, n);
}

void preorder(string words[], Node* node) {
    if (!node) return;
    cout << words[node->data] << " ";
    preorder(words, node->left);
    preorder(words, node->right);
}

void printMatrix(string name, int m[][MAX], int n) {
    cout << "\n" << name << " Matrix:\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (j < i) cout << " - ";
            else cout << setw(3) << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    string words[MAX];
    int p[MAX], q[MAX];

    cout << "Enter " << n << " keys in sorted order:\n";
    for (int i = 1; i <= n; i++) {
        cout << "k" << i << ": ";
        cin >> words[i];
    }

    cout << "\nEnter search probabilities (p[1] to p[" << n << "]) for each key:\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

    cout << "\nEnter dummy key probabilities (q[0] to q[" << n << "]):\n";
    for (int i = 0; i <= n; i++) {
        cout << "q[" << i << "]: ";
        cin >> q[i];
    }

    int w[MAX][MAX], c[MAX][MAX], r[MAX][MAX];
    Node* root = optimalbst(p, q, n, w, c, r);

    printMatrix("Weight", w, n);
    printMatrix("Cost", c, n);
    printMatrix("Root", r, n);

    cout << "\nPreorder traversal of Optimal BST:\n";
    preorder(words, root);
    cout << endl;

    return 0;
} 