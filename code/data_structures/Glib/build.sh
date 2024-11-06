gcc -g -Wall -Werror  tree_example.c `pkg-config glib-2.0 --cflags --libs` -o tree_example

gcc -g -Wall -Werror  hashtable_example.c `pkg-config glib-2.0 --cflags --libs` -o hashtable_example
