#trie_serializable

This is a library for the trie data structure which can be converted to/from a list of strings. A user can do the following:

1. Create a trie using a list of words or an empty trie.
2. Insert words to the trie.
3. Convert the trie to a list of words.
4. Check how many words in the trie have a given prefix.
5. Check if a given word is present in the trie.
6. Convert the trie to a string i.e. serialize the trie.
7. Create a trie using a string representing the trie.
8. Find total number of words present in a trie.

Note: Serialization of the trie to a string makes use of special characters '>' and ']'. The user is expected to not use these symbols in words that are to be inserted to the trie.
Test data taken from https://github.com/dwyl/english-words

written in c++.
