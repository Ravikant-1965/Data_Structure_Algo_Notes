#include <iostream>
using namespace std;

#define ALPHABET_SIZE 26

// Trie Node structure
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord; // True if the node represents the end of a word

	// constructor
    TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++){
			children[i] = nullptr;
		}
        isEndOfWord = false;
    }
};

// Trie class
class Trie {
	private:
		TrieNode* root;

	public:
		// Constructor
		Trie(){
			root = new TrieNode();
		}

		// In insert function  : We are not actually storing the character itself.
		// Instead, we are using the position in the children array to represent the character.
		// Let’s break this down in more detail.

		// Each TrieNode has an array , This means:
			// Each index (0 to 25) implicitly represents a character ('a' to 'z').
			// The existence of a pointer at children[index] means that the corresponding character is part of a word.
			// We don’t store the actual character explicitly.

		// Insert a word into the Trie
		// See Striver to understand
		void insert(string word) {
			TrieNode* node = root;
			for (char ch : word) {
				int index = ch - 'a';
				if (!node->children[index]){   // character is yet not present
					node->children[index] = new TrieNode();   // see how trie is implemented pic..
				}
				node = node->children[index];
			}
			node->isEndOfWord = true;
		}

		// Search for a word in the Trie
		bool search(string word) {
			TrieNode* node = root;
			for (char ch : word) {
				int index = ch - 'a';
				if (!node->children[index]){   // if any character is missing, return false
					return false;
				}
				node = node->children[index];
			}
			return node->isEndOfWord; // if false, word is a prefix(prefix hua toh uska isEndOfWord false hogga) but not a complete word.
		}

		// Check if a prefix exists in the Trie
		bool startsWith(string prefix) {
			TrieNode* node = root;
			for (char ch : prefix) {
				int index = ch - 'a';
				if (!node->children[index]){  // if any character is missing, return false (prefix not found).
					return false;
				}
				node = node->children[index];
			}
			return true;  // If we reach here, it means the prefix exists in the Trie.
		}

		void deleteWord(string word) {
			TrieNode* node = root;
			TrieNode* stack[word.length()]; // Stack to track nodes
			int indices[word.length()]; // Track indices of the word's characters
			int depth = 0;
	
			// Step 1: Traverse to the end of the word
			for (char ch : word) {
				int index = ch - 'a';
				if (!node->children[index]) {
					return; // Word does not exist
				}
				stack[depth] = node;
				indices[depth] = index;
				node = node->children[index];
				depth++;
			}
	
			// Step 2: Mark end of word as false
			node->isEndOfWord = false;
	
			// Step 3: Backtrack and delete nodes if necessary
			for (int i = depth - 1; i >= 0; i--) {
				TrieNode* parent = stack[i];
				int index = indices[i];
	
				if (!node->isEndOfWord) {
					bool hasChildren = false;
					for (int j = 0; j < ALPHABET_SIZE; j++) {
						if (node->children[j]) {
							hasChildren = true;
							break;
						}
					}
	
					if (!hasChildren) { // Delete node if it has no children
						delete node;
						parent->children[index] = nullptr;
					} else {
						break; // Stop deleting if a node has children
					}
				}
				node = parent;
			}
		}
};



// Driver Code
int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("apex");
	trie.deleteWord("apple");

	cout << "Search apple: " << (trie.search("apple") ? "Found" : "Not Found") << endl;
	cout << "Search app: " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "Search apex: " << (trie.search("apex") ? "Found" : "Not Found") << endl;
    cout << "Search ape: " << (trie.search("ape") ? "Found" : "Not Found") << endl;

    cout << "Prefix 'ap' exists? " << (trie.startsWith("ap") ? "Yes" : "No") << endl;
    cout << "Prefix 'bat' exists? " << (trie.startsWith("bat") ? "Yes" : "No") << endl;

    return 0;
}
