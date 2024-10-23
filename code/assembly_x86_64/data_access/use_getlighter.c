#include <stddef.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a)[0])

typedef struct person {
    char name[20];
    int age;
    int weight;
    float height;
} Person;

Person *get_lighter(Person *people, size_t n_people);

Person people[] = {
	{"Ana", 30, 60, 1.75},
	{"Manuel", 30, 70, 2.0}
};

int main() {
    char *lighter_name = get_lighter(
               people, ARRAY_SIZE(people))->name;
}
