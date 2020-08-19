#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;
static const int MAX_NUMBER_LEAFS = 255;

struct TrieNode {
    char c;
    unordered_map<char, TrieNode*> next_nodes;
    bool end = false;
    
    TrieNode(char c) {
        this->c = c;
        this->next_nodes.reserve(MAX_NUMBER_LEAFS);
    }
};

class Trie {
    private:
        TrieNode* head;

        void destruct_Trie(TrieNode* node) {
            if (node->next_nodes.size()) {
                for (auto it = node->next_nodes.begin(); it != node->next_nodes.end(); ++it) {
                    destruct_Trie(it->second);
                }
            }
            cout << node->c << endl;
            delete node;
        }

        void insert_Trie(string str, TrieNode* node) {
            if (!str.length()) {
                node->end = true;
                return;
            }
            if (node->next_nodes.find(str[0]) == node->next_nodes.end()) {
                node->next_nodes[str[0]] = new TrieNode(str[0]);
            }
            insert_Trie(str.substr(1), node->next_nodes[str[0]]);
        }

        void traverse_Trie(vector<string>& strings, TrieNode* node, string str) {
            if (node->next_nodes.empty()) {
                strings.push_back(str);
                return;
            }
            if (node->end) strings.push_back(str);
            for (auto it = node->next_nodes.begin(); it != node->next_nodes.end(); ++it) {
                traverse_Trie(strings, it->second, str + it->first);
            }
        }

        bool find_Trie(string str, TrieNode* node) {
            if (!str.length()) {
                if (node->end) return true;
                else return false;
            }
            if (node->next_nodes.find(str[0]) == node->next_nodes.end()) return false;
            return find_Trie(str.substr(1), node->next_nodes[str[0]]);
        }

    public:
        Trie() {
            this->head = new TrieNode(' ');
        }

        Trie(string str) {
            this->head = new TrieNode(' ');
            insert(str);
        }

        ~Trie() {
            destruct_Trie(this->head);
        }

        void insert(string str) {
            insert_Trie(str, this->head);
        }

        vector<string> all_words() {
            vector<string> strings;
            traverse_Trie(strings, this->head, "");
            return strings;
        }

        bool find(string str) {
            return find_Trie(str, this->head);
        }
};

int main() {
    int n;
    Trie trie;
    cout << "How many words to insert: ";
    while (cin >> n) {
        if (!n) break;
        for (int i = 0; i < n; ++i) {
            string s;
            cout << "Insert: ";
            cin >> s;
            trie.insert(s);
            cout << "Inserted: " << s << endl;
        }
        vector<string> strs = trie.all_words();
        for (auto str : strs) {
            cout << str << endl;
        }
        string q;
        cout << "Find: ";
        cin >> q;
        bool find_result = trie.find(q);
        cout << ((find_result) ? "true" : "false") << endl;
        cout << "How many words to insert: ";
    }
}