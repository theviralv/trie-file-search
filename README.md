## File Auto-Search Engine
• Trie based file search engine using C++ and linux shell.

• User inputs the file name to be searched and matching filenames in the current directory are returned.
 
 C++ — Trie — Shell — String Manipulation — Data Structures — Algorithms
 
Save the following function in the .bashrc (located in the home directory) file of thet terminal:
```
search(){
  g++ -std=c++14 -c /path/to/search.cpp -o /path/to/search.o && /path/to/a.out
}
```
[Do not forget to change the paths]

Now type in `search` command in your shell and the cpp program is compiled and executed.

The engine waits for the user string input, on input it finds the matching file names (autocompleted file names) in current directory.
