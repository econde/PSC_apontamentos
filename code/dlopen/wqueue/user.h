#ifndef USER_H
#define USER_H

struct user {
	struct user *next, *prev;
	char *name;
};

#endif
