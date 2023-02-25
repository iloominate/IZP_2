#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct set_str {
    int position;
    char **set;
    int max_y_size;
    int max_x_size;

} set_str;

typedef struct relacie_str {
    int position;
    char ***relacie;
    int max_z_size;
    int max_x_size;
} relacie_str;

typedef struct all_str {
    set_str *s;
    relacie_str *r;
} all_str;

void set_pars(char *line, all_str *a, int set_num){
    enum{
        stage_0,
        stage_1,
    };
    int x = 0;
    int y = 0;
    int i = 0;
    int stage = stage_0;
    while(1){
        if (line[i] == '\0')
            break;
        switch (stage) {
            case stage_0:
            {
                if (line[i] != ' ')
                {
                    (a+set_num)->s->max_x_size = x;
                    (a+set_num)->s->set = realloc((a+set_num)->s->set, sizeof(char) * ((a+set_num)->s->max_x_size+1) *
                    ((a+set_num)->s->max_y_size+1));
                    (a+set_num)->s->set[x][y] = line[i];
                    y++;
                    if (y > (a+set_num)->s->max_y_size)
                        (a+set_num)->s->max_y_size = y;
                } else
                    stage = stage_1;
                break;
            }
            case stage_1:
            {
                if (line[i+1] != ' ') {
                    stage = stage_0;
                    x++;
                }
                break;
            }
        }
        i++;
    }

}


void rel_pars(char *line, all_str *a, int rel_num){
    enum{
        stage_0,
        stage_1,
        stage_2,
    };
    int x = 0;
    int z = 0;
    int y = 0;
    int i = 0;
    int stage = stage_0;
    while(1){
        if (line[i] == '\0')
            break;
        switch (stage) {
            case stage_0:
            {
                (a+rel_num)->r->max_x_size = x;
                if (line[i] == '(')
                    stage = stage_1;
                break;
            }
            case stage_1:
            {
                if (line[i] != ' ') {
                    (a+rel_num)->r->relacie = realloc((a+rel_num)->r->relacie, sizeof(char) * ((a+rel_num)->r->max_x_size + 1) *
                    2 * ((a+rel_num)->r->max_z_size + 1));
                    (a+rel_num)->r->relacie[x][y][z] = line[i];
                    z++;
                    if ((a+rel_num)->r->max_z_size< z)
                        (a+rel_num)->r->max_z_size = z;
                } else {
                    stage = stage_2;
                    z = 0;
                }
                break;
            }
            case stage_2:
            {
                y++;
                if ((line[i] != ' ') && line[i] !=')')
                {
                    if ((a+rel_num)->r->max_z_size < z) {
                        (a+rel_num)->r->max_z_size = z;
                        (a+rel_num)->r->relacie = realloc((a+rel_num)->r->relacie, sizeof(char) * ((a+rel_num)->r->max_x_size + 1) *
                        2 * ((a+rel_num)->r->max_z_size + 1));
                    }
                    (a+rel_num)->r->relacie[x][y][z] = line[i];
                    z++;
                }
                else if (line[i] == ')')
                {
                    stage = stage_0;
                    y = 0;
                    z = 0;
                    x++;
                }
                break;


            }
        }
        i++;
    }

}


char** operation_pars(char *line){
    char **tokens;
    int size_x = 0;
    int size_y = 0;

    for (int i =2; line[i]; i++)
    {
        tokens = realloc(tokens, sizeof(char) * (size_x+1) * (size_y+1));
        if (line[i]!=' ')
        {
            tokens[size_x][size_y] = line[i];
            size_y++;
        }
        else {
            size_x++;
            size_y = 0;
        }
    }
    return tokens;
}


int get_operation_num (char **tokens)
{
    char all_operation[][31] = {
            "empty", "card", "complement", "union", "intersect",
            "minus", "subseteq", "subset", "equals",
            "reflexive", "symmetric", "antisymmetric",  "transitive",
            "function", "domain", "codomain", "injective", "surjective", "bijective"

    };

    for (int j = 0; all_operation[j]; j++){
        if (strcmp(tokens[1], all_operation[j]))
            return 1;
    }

    return 0;
}


int check_operation_num(int i, char **tokens, int operation_number, char **all_lines)
{
    int arg_1 = atoi(tokens[2]);
    if ((arg_1 < 1)  || (arg_1 > i))
        return 0;
    int arg_2 = atoi(tokens[2]);
    if ((arg_2 < 1) || (arg_2 > i))
        return 0;
    int arg_3 = atoi(tokens[3]);
    if ((arg_3 < 1) || (arg_3 > i))
        return 0;
    if ((operation_number<18) &&(arg_3))
        return 0;
    if (operation_number > 4 && operation_number < 11 && (!arg_2))
        return 0;
    if ((all_lines[operation_number][0] != 'S') || (all_lines[operation_number][0] !='U') && ((arg_1 > 10)
                                                                                              || arg_2 > 10))
        return 0;
    if ((all_lines[operation_number][0] != 'R') && ((arg_1 <= 10)
                                                    || arg_2 > 10))
        return 0;
    return 1;
}


void get_line_num (int i, char **tokens, int operation_number){
    int arg_1 = atoi(tokens[2]);
    int arg_2 = atoi(tokens[3]);
    int arg_3 = atoi(tokens[3]);
}


int line_pars(char *line, int size){
    int i = 0;
    while (line[i] != ('\n' || NULL )) {
        switch (line[0]) {
            case 'U':
            {
                break;
            }
            case 'S':
            {
                break;
            }
            case 'R':
            {
                break;
            }
            case 'C':
            {
                break;
            }
            default:
            {
                return -1;
            }

        }
        i++;
    }
}


bool empty_(all_str *a, char **tokens)
{
    if ((a+atoi(tokens[1]))->s->set == 0) {
        printf("true \n");
        return true;
    }
    printf("false \n");
    return false;
};


void card_(all_str *a, char **tokens)
{
    int amount = (a+atoi(tokens[1]))->s->max_x_size;
    printf("%d\n", amount);
};


void complement_(all_str *a, char** tokens)
{
    bool name_check = false;
    for (int i = 0; a->s->set[i]; i++){
        name_check = false;
        for (int j = 0; (a+atoi(tokens[1]))->s->set[j]; j++)
            if (strcmp(a->s->set[i], (a+atoi(tokens[1]))->s->set[j]) == 0)
                name_check = true;
        if (!name_check)
            printf("%s", a->s->set[i]);
    }

};


void union_(all_str *a, char **tokens)
{
    int tmp = 0;
    bool repeat_check = false;
    for (int i =0; (a+atoi(tokens[1]))->s->set[i]; i++)
        printf("%s", (a+atoi(tokens[1]))->s->set[i]);
    for (int j = 0; (a+atoi(tokens[2]))->s->set[j]; j++){
        repeat_check = false;
        for (int k = 0; (a+atoi(tokens[1]))->s->set[k]; k++)
            if (strcmp((a+atoi(tokens[1]))->s->set[j], (a+atoi(tokens[2]))->s->set[k]) == 0)
                repeat_check = true;
        if (!repeat_check)
            printf("%s", (a+atoi(tokens[2]))->s->set[j]);
}}


void intersect_(all_str *a, char **tokens)
{
    for (int i = 0; (a+atoi(tokens[1]))->s->set[i]; i++)
    {
        for (int j = 0; (a+atoi(tokens[2]))->s->set[j]; j++)
        {
            if (strcmp((a+atoi(tokens[1]))->s->set[i], (a+atoi(tokens[2]))->s->set[j]) == 0) {
                printf("%s", (a + atoi(tokens[2]))->s->set[j]);
                break;
            }
        }
    }
}


void minus_(all_str *a, char **tokens)
{
    bool repeat_check = false;
    for (int i = 0; (a+atoi(tokens[1]))->s->set[i]; i++)
    {
        for (int j = 0; (a+atoi(tokens[2]))->s->set[j]; j++)
        {
            if (strcmp((a+atoi(tokens[1]))->s->set[i], (a+atoi(tokens[2]))->s->set[j]) == 0)
                repeat_check = true;
            if (!repeat_check)
                printf ("%s", (a + atoi(tokens[1]))->s->set[i]);
        }
    }
}


bool subseteq_(all_str *a, char **tokens)
{
    bool repeat_check = false;
    for (int i = 0; (a+atoi(tokens[1]))->s->set[i]; i++)
    {
        repeat_check = false;
        for (int j = 0; (a+atoi(tokens[2]))->s->set[j]; j++)
        {
            if (strcmp((a+atoi(tokens[1]))->s->set[i], (a+atoi(tokens[2]))->s->set[j]) == 0)
                repeat_check = true;

        }
        if (!repeat_check)
            return false;
    }
    return true;

}


bool subset_(all_str *a, char **tokens)
{
    if (subseteq_(a, tokens)){
        if ((a+atoi(tokens[1]))->s->max_x_size != (a + atoi(tokens[2]))->s->max_x_size)
            return true;
    }
    return false;
}


bool equals_(all_str *a, char **tokens) 
{
    if (subseteq_(a, tokens)) {
        if ((a + atoi(tokens[1]))->s->max_x_size == (a + atoi(tokens[2]))->s->max_x_size)
            return true;
    }
    return false;
}


bool reflexive_(all_str *a, char **tokens)
{
    int repeat_amount = 0;
    for (int i = 0; (a+atoi(tokens[1]))->r->relacie[i]; i++)
    {
        for (int j = 0; (a+atoi(tokens[1]))->r->relacie[i][j]; j++)
        {
            for (int k = 0; (a+atoi(tokens[1]))->r->relacie[k]; k++)
            {
                repeat_amount = 0;
                for (int l = 0; (a+atoi(tokens[1]))->r->relacie[k][l]; l++)
                {
                    if (strcmp((a+atoi(tokens[1]))->r->relacie[i][j], (a+atoi(tokens[1]))->r->relacie[k][l]))
                        repeat_amount++;

                }
                if (repeat_amount == 2)
                    break;
            }
            if (repeat_amount != 2)
            {
                return false;
            }
        }
    }
    return true;
}


bool symmetric_(all_str *a, char **tokens)
{
    int symm_check = 0;
    for (int i = 0; (a+atoi(tokens[1]))->r->relacie[i]; i++)
    {
        symm_check = 0;
        for (int j = 0; (a+atoi(tokens[1]))->r->relacie[j]; j++)
        {
            if (strcmp((a+atoi(tokens[1]))->r->relacie[i][0], (a+atoi(tokens[1]))->r->relacie[j][1]) == 0)
            {
                symm_check = 1;
                if (strcmp((a+atoi(tokens[1]))->r->relacie[i][1], (a+atoi(tokens[1]))->r->relacie[j][0]) == 0)
                    symm_check = 2;
            }
            if (symm_check == 2)
                break;
        }
        if (symm_check != 2)
        {
            return false;
        }
    }
    return true;
}


bool antisymmetric_(all_str *a, char **tokens)
{
    int symm_check = 0;
    for (int i = 0; (a+atoi(tokens[1]))->r->relacie[i]; i++)
    {
        symm_check = 0;
        for (int j = 0; (a+atoi(tokens[1]))->r->relacie[j]; j++)
        {
            if (strcmp((a+atoi(tokens[1]))->r->relacie[i][0], (a+atoi(tokens[1]))->r->relacie[j][1]) == 0)
            {
                symm_check = 1;
                if (strcmp((a+atoi(tokens[1]))->r->relacie[i][1], (a+atoi(tokens[1]))->r->relacie[j][0]) == 0)
                    symm_check = 2;
            }
            if (symm_check == 2)
                return false;
        }
    }
    return true;
}


bool transitive_(all_str *a, char **tokens)
{
    bool transitive_check = false;
    for (int i = 0; (a+atoi(tokens[1]))->r->relacie[i]; i++)
    {
        for (int j = 0; (a + atoi(tokens[1]))->r->relacie[j]; j++)
        {
            if (strcmp((a + atoi(tokens[1]))->r->relacie[i][1], (a + atoi(tokens[1]))->r->relacie[j][0]) == 0)
            {
                for (int k = 0; (a + atoi(tokens[1]))->r->relacie[k]; k++)
                {
                    if ((strcmp((a + atoi(tokens[1]))->r->relacie[k][0], (a + atoi(tokens[1]))->r->relacie[i][0]) ==
                         0) &&
                        (strcmp((a + atoi(tokens[1]))->r->relacie[k][1], (a + atoi(tokens[1]))->r->relacie[j][1]) == 0))
                        transitive_check = true;

                }
                if (!transitive_check)
                {
                    return false;
                }
            }
        }
    }
    return true;
}


bool function_(all_str *a, char **tokens)
{
    for (int i = 0; (a+atoi(tokens[1]))->r->relacie[i]; i++)
    {
        for (int j = 0; (a + atoi(tokens[1]))->r->relacie[j]; j++)
        {
            if ((strcmp((a+atoi(tokens[1]))->r->relacie[i][0], (a+atoi(tokens[1]))->r->relacie[j][0])) == 0)
            {
                if ((strcmp((a+atoi(tokens[1]))->r->relacie[i][1], (a+atoi(tokens[1]))->r->relacie[j][1])) != 0)
                    return false;
            }
        }
    }
    return true;

}


bool domain_(all_str *a, char **tokens)
{
    if (!function_(a, tokens)) {
        return false;
    }
    bool repeat_check = false;
    for (int i = 0; (a+atoi(tokens[1]))->r->relacie[i]; i++)
    {
        repeat_check = false;
        for (int j = 0; j<i-1; j++)
        {
            if (strcmp((a + atoi(tokens[1]))->r->relacie[i][0], (a + atoi(tokens[1]))->r->relacie[j][0]) == 0)
                repeat_check = true;
        }
        if (!repeat_check)
            printf("%s \n",  (a+atoi(tokens[1]))->r->relacie[i][0]);
    }
}


bool codomain_(all_str *a, char **tokens)
{
    if (!function_(a, tokens)) {
        return false;
    }
    bool repeat_check = false;
    for (int i = 0; (a+atoi(tokens[1]))->r->relacie[i]; i++)
    {
        repeat_check = false;
        for (int j = 0; j<i-1; j++)
        {
            if (strcmp((a + atoi(tokens[1]))->r->relacie[i][1], (a + atoi(tokens[1]))->r->relacie[j][1]) == 0)
                repeat_check = true;
        }
        if (!repeat_check)
            printf("%s \n",  (a+atoi(tokens[1]))->r->relacie[i][1]);

    }
    return true;
}


bool set_in_relation_check(all_str *a, char **tokens)
{
    int rel_num = atoi(tokens[1]);
    int set_1_num = atoi(tokens[2]);
    int set_2_num = atoi(tokens[3]);
    bool found = false;
    bool sets_are_in_relation = false;
    for (int i = 0; (a+set_1_num)->s->set[i]; i++)
    {
        found = false;
        for (int j = 0; (a+rel_num)->r->relacie[j]; j++)
        {
            if (strcmp((a+set_1_num)->s->set[i], ((a+rel_num)->r->relacie[j][0])) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            fprintf(stderr, "ERROR: set doesn't match with relation \n");
            return false;
        }
    }
    for (int i = 0; (a+set_2_num)->s->set[i]; i++)
    {
        found = false;
        for (int j = 0; (a + rel_num)->r->relacie[j]; j++) {
            if (strcmp((a + set_2_num)->s->set[i], ((a + rel_num)->r->relacie[j][1])) == 0){
                found = true;
                break;
            }
        }
        if (!found) {
            fprintf(stderr, "ERROR: set doesn't match with relation \n");
            return false;
        }
    }
    for (int i = 0; (a+rel_num)->r->relacie[i]; i++)
    {
        for (int j = 0; (a+set_1_num)->s->set[j]; j++)
        {
            if (strcmp((a + rel_num)->r->relacie[i][0], (a + set_1_num)->s->set[j]) == 0)
            {
                sets_are_in_relation = false;
                for (int k = 0; (a+set_2_num)->s->set[k]; k++)
                {
                    if (strcmp((a + rel_num)->r->relacie[i][1], (a + set_2_num)->s->set[k]) == 0)
                    {
                        sets_are_in_relation = true;
                        break;
                    }
                }
                if (!sets_are_in_relation)
                {
                    fprintf(stderr, "Sets are not in relation \n");
                    return false;
                }
            }
        }
    }
    return true;
}


bool injective_ (all_str *a, char **tokens)
{
    int rel_num = atoi(tokens[1]);
    int set_1_num = atoi(tokens[2]);
    int set_2_num = atoi(tokens[3]);
    if (!set_in_relation_check(a, tokens))
        return false;
    int repeat_in_rel = 0;
    for (int i = 0; (a+rel_num)->r->relacie[i]; i++)
    {
        for (int j = 0; (a+set_2_num)->s->set[j]; j++)
        {
            if (strcmp((a+rel_num)->r->relacie[i][1], (a + set_2_num)->s->set[j]) == 0)
            {
                repeat_in_rel = 0;
                for (int k = 0; (a+set_1_num)->s->set[k]; k++)
                {
                    if (strcmp((a+rel_num)->r->relacie[i][0], (a + set_1_num)->s->set[k]) == 0)
                        repeat_in_rel++;
                }
                if (repeat_in_rel > 1)
                {
                    printf("false \n");
                    return false;
                }
            }
        }
    }
    printf("true \n");
    return true;
}


bool surjective_(all_str *a, char **tokens)
{
    int rel_num = atoi(tokens[1]);
    int set_1_num = atoi(tokens[2]);
    int set_2_num = atoi(tokens[3]);
    if (!set_in_relation_check(a, tokens))
        return false;
    int repeat_in_rel = 0;
    for (int i = 0; (a+rel_num)->r->relacie[i]; i++)
    {
        for (int j = 0; (a+set_2_num)->s->set[j]; j++)
        {
            if (strcmp((a+rel_num)->r->relacie[i][1], (a + set_2_num)->s->set[j]) == 0)
            {
                repeat_in_rel = 0;
                for (int k = 0; (a+set_1_num)->s->set[k]; k++)
                {
                    if (strcmp((a+rel_num)->r->relacie[i][0], (a + set_1_num)->s->set[k]) == 0)
                        repeat_in_rel++;
                }
                if (repeat_in_rel > 1)
                {
                    printf("true \n");
                    return true;
                }
            }
        }
    }
    printf("false \n");
    return false;
}


bool bijective_(all_str *a, char **tokens)
{
    int rel_num = atoi(tokens[1]);
    int set_1_num = atoi(tokens[2]);
    int set_2_num = atoi(tokens[3]);
    if (!set_in_relation_check(a, tokens))
        return false;
    int repeat_in_rel = 0;
    for (int i = 0; (a+rel_num)->r->relacie[i]; i++)
    {
        for (int j = 0; (a+set_2_num)->s->set[j]; j++)
        {
            if (strcmp((a+rel_num)->r->relacie[i][1], (a + set_2_num)->s->set[j]) == 0)
            {
                repeat_in_rel = 0;
                for (int k = 0; (a+set_1_num)->s->set[k]; k++)
                {
                    if (strcmp((a+rel_num)->r->relacie[i][0], (a + set_1_num)->s->set[k]) == 0)
                        repeat_in_rel++;
                }
                if (repeat_in_rel != 1)
                {
                    printf("false \n");
                    return false;
                }
            }
        }
    }
    printf("true \n");
    return true;
}


void call_function (all_str *a, char **tokens)
{
    if (strcmp(tokens[0], "empty") == 0)
        empty_(a, tokens);
    else if (strcmp(tokens[0], "card") == 0)
        card_(a, tokens);
    else if (strcmp(tokens[0], "complement") == 0)
        complement_(a, tokens);
    else if (strcmp(tokens[0], "union") == 0)
        union_(a, tokens);
    else if (strcmp(tokens[0], "intersect") == 0)
        intersect_(a, tokens);
    else if (strcmp(tokens[0], "minus") == 0)
        minus_(a, tokens);
    else if (strcmp(tokens[0], "subseteq") == 0)
        subseteq_(a, tokens);
    else if (strcmp(tokens[0], "subset") == 0)
        subset_(a, tokens);
    else if (strcmp(tokens[0], "equals") == 0)
        equals_(a, tokens);
    else if (strcmp(tokens[0], "reflexive") == 0)
        reflexive_(a, tokens);
    else if (strcmp(tokens[0], "symmetric") == 0)
        symmetric_(a, tokens);
    else if (strcmp(tokens[0], "antisymmetric") == 0)
        antisymmetric_(a, tokens);
    else if (strcmp(tokens[0], "transitive") == 0)
        transitive_(a, tokens);
    else if (strcmp(tokens[0], "function") == 0)
        function_(a, tokens);
    else if (strcmp(tokens[0], "domain") == 0)
        domain_(a, tokens);
    else if (strcmp(tokens[0], "codomain") == 0)
        codomain_(a, tokens);
    else if (strcmp(tokens[0], "injective") == 0)
        injective_(a, tokens);
    else if (strcmp(tokens[0], "surjective") == 0)
        surjective_(a, tokens);
    else if (strcmp(tokens[0], "bijective") == 0)
        bijective_(a, tokens);
    else
        fprintf(stderr, "Invalid operation name \n");
}


void struct_memory_free(all_str *a, int counter) {
    for (int i = 0; i < counter; i++)
    {
        if ((a + i)->r->relacie != NULL)
        {
            for (int j = 0; (a + i)->r->relacie[i]; i++)
            {
                for (int k = 0; (a + i)->r->relacie[j][k]; k++)
                    free((a + i)->r->relacie[j][k]);
                free((a + i)->r->relacie[j]);
            }
            free((a + i)->r->relacie);
            free((a + i)->r);
        }
        if ((a + i)->s->set != NULL)
        {
            for (int j = 0; (a + i)->s->set[i]; i++)
            {
                free((a + i)->s->set[i]);
            }
            free((a + i)->s->set);
            free((a + i)->s);
        }
        free(a + 1);
    }
    free(a);
}


int main (int argc, char* argv[])
{
    FILE *fp = fopen("sets.txt", "r+");
    char **all_lines;
    int i = 0;
    struct all_str *a;
    char c;
    int j = 0;
    int k = 0;

    all_lines = calloc(1000, sizeof(char*));
    for (int i = 0; i <1000; i++)
        all_lines[i] = calloc(30, sizeof(char));
    while ((c = getc(fp)) != EOF)
    {
        all_lines[j][k] = c;
        k++;
        if (k > 30)
            realloc(all_lines, sizeof(char) * k * 1000);
        if (c == '\n')
            j++;
    }

    while (all_lines[i][0] != EOF)
    {
        if (a == NULL)
            a = calloc(1, sizeof(all_str));
        else
            a = realloc(a, sizeof(all_str) * (i +1));
        switch(all_lines[i][0])
        {
            case 'U':
            {
                (a+i)->s = calloc(1, sizeof(set_str));
                if (i != 0) {
                    fprintf(stderr, "Invalid order \n");
                    return EXIT_FAILURE;
                }
                set_pars(all_lines[i], a, i);
                printf ("%s \n", all_lines[i]);
                break;
            }
            case 'S':
            {
                (a+i)->s = calloc(1, sizeof(set_str));
                if (i == 0) {
                    fprintf(stderr, "Invalid order \n");
                    return EXIT_FAILURE;
                }
                set_pars(all_lines[i], a, i);
                printf ("%s \n", all_lines[i]);
                break;
            }
            case 'R':
            {
                (a+i)->r = calloc(1, sizeof(set_str));
                if (i == 0) {
                    fprintf(stderr, "Invalid order \n");
                    return EXIT_FAILURE;
                }
                rel_pars(all_lines[i], a, i);
                printf("%s \n", all_lines[i]);
                break;
            }
            case 'C':
            {
                if (i == 0) {
                    fprintf(stderr, "Invalid order \n");
                    return EXIT_FAILURE;
                }
                char **tokens = operation_pars(all_lines[i]);
                call_function(a, tokens);
                break;
            }
        }
        i++;
    }

    return 0;
}
