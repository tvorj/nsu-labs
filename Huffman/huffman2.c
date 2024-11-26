#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define input_length 2000000
typedef int ll;
typedef struct ALPH
{
    long long int weight;
    unsigned char arr[256];
    unsigned char now;
    struct ALPH* left;
    struct ALPH* right;
    struct ALPH* parent;
}alph;

typedef struct char_count
{
    long long int count;
    unsigned char now;
}char_count;

void text_fill(FILE* fi, unsigned char* text, char_count* mas, ll* dif)
{
    ll count = fread(text, 1, input_length, fi);
    for (ll i = 0; i < count; i++)
    {
        if (!mas[(int)text[i]].count)
        {
            mas[(int)text[i]].now = text[i];
            (*dif)++;
        }
        mas[(int)text[i]].count++;
    }
}

void gr_free(alph* haf_tree)
{
    if (haf_tree->now == 0 || haf_tree->now == 1)
    {
        if (haf_tree->left != NULL)
            gr_free(haf_tree->left);
        if (haf_tree->right != NULL)
            gr_free(haf_tree->right);
    }
    free(haf_tree);
}

void define_node(alph* new_node, alph* x1, alph* x2)
{
    new_node->parent = NULL;
    new_node->now = 0;
    new_node->left = x1;
    new_node->right = x2;
    new_node->weight = x1->weight;
    new_node->weight += x2->weight;
}

alph* create_tree(char_count* mas, ll dif, alph* kost)
{
    alph* arr[dif];
    ll ind = 0;
    for (ll i = 0; i < dif; i++)
    {
        for (ll l = ind; l < 256; l++)
        {
            if (mas[l].count != 0)
            {
                ind = l + 1;
                break;
            }
        }
        alph* new_node = (alph*)malloc(sizeof(alph));
        new_node->now = mas[ind - 1].now;
        new_node->weight = mas[ind - 1].count;
        new_node->parent = kost;
        new_node->left = new_node->right = NULL;
        arr[i] = new_node;
    }
    ll ind_start = 0, len = dif;
    while (dif != 1)
    {
        for (ll i = 0; i < dif; i++)
        {
            for (ll l = len - dif; l < len - 1; l++)
                if (arr[l]->weight > arr[l + 1]->weight)
                {
                    alph* buf = arr[l];
                    arr[l] = arr[l + 1];
                    arr[l + 1] = buf;
                }
        }
        alph* new_node = (alph*)malloc(sizeof(alph));
        define_node(new_node, arr[ind_start], arr[ind_start + 1]);
        arr[ind_start + 1] = new_node;
        arr[ind_start]->weight = 0;
        ind_start++;
        dif--;
    }
    alph* answer_node = arr[ind_start];
    return answer_node;
}

void coding_to_char(unsigned char* mas, FILE* fo)
{
    ll res = 0, pow = 1;
    for (ll i = 7; i >= 0; i--)
    {
        if (mas[i] == '1')
            res += pow;
        pow *= 2;
    }
    fputc((unsigned char)res, fo);
}

void decode_digit(char* buf, unsigned char now)
{
    ll res = (int)now;
    for (ll i = 7; i >= 0; i--)
    {
        if (res % 2)
            buf[i] = '1';
        else buf[i] = '0';
        res /= 2;
    }
}

void dfs(alph* haf_tree, ll arr_len, alph* map, FILE* fo, unsigned char* buf, ll* index, alph* stop)
{
    if (haf_tree->parent == NULL)
    {
        for (ll i = 0; i < arr_len; i++)
        {
            haf_tree->left->arr[i] = haf_tree->arr[i];
            haf_tree->right->arr[i] = haf_tree->arr[i];
        }
        haf_tree->left->arr[arr_len] = '0';
        haf_tree->right->arr[arr_len] = '1';

        buf[*index] = '0';
        (*index)++;
        if ((*index) == 8)
        {
            (*index) = 0;
            coding_to_char(buf, fo);
        }
        dfs(haf_tree->left, arr_len + 1, map, fo, buf, index, stop);
        dfs(haf_tree->right, arr_len + 1, map, fo, buf, index, stop);
    }
    else
    {
        buf[(*index)] = '1';
        (*index)++;
        if ((*index) == 8)
        {
            coding_to_char(buf, fo);
            (*index) = 0;
        }
        char to_buf[8];
        unsigned char to_coded = haf_tree->now;
        decode_digit(to_buf, to_coded);
        ll to_buf_ind = 0;
        for (ll i = (*index); i < 8; i++)
        {
            buf[i] = to_buf[to_buf_ind];
            (*index)++;
            to_buf_ind++;
        }
        coding_to_char(buf, fo);
        (*index) = 0;
        ll maxi = 8 - to_buf_ind;
        for (ll i = 0; i < maxi; i++)
        {
            buf[i] = to_buf[to_buf_ind];
            (*index)++;
            to_buf_ind++;
        }
        if (haf_tree == stop)
        {
            for (ll i = (*index); i < 8; i++)
                buf[i] = '0';
            (*index) = 0;
            coding_to_char(buf, fo);
        }
        for (ll i = 0; i < arr_len; i++)
            map[(int)haf_tree->now].arr[i] = haf_tree->arr[i];
        map[(int)haf_tree->now].weight = arr_len;
    }
}

void find_trash(FILE* fi, alph* map, unsigned char* buf, ll* index)
{
    unsigned char* text = (unsigned char*)malloc(input_length);
    while (!feof(fi))
    {
        ll count = fread(text, 1, input_length, fi);
        for (ll i = 0; i < count; i++)
        {
            ll num = (int)text[i];
            for (ll i = 0; i < map[num].weight; i++)
            {
                buf[*index] = map[num].arr[i];
                (*index)++;
                if ((*index) == 8)
                    (*index) = 0;
            }
        }
    }
    ll ind = 8 - (*index);
    for (ll i = 0; i < ind - 1; i++)buf[i] = '0';
    buf[ind - 1] = '1';
    (*index) = ind;
    free(text);
}

void coding(FILE* fi, alph* map, FILE* fo, unsigned char* buf, ll* index)
{
    unsigned char* text = (unsigned char*)malloc(input_length);
    while (!feof(fi))
    {
        ll count = fread(text, 1, input_length, fi);
        for (ll i = 0; i < count; i++)
        {
            ll num = (int)text[i];
            for (ll i = 0; i < map[num].weight; i++)
            {
                buf[(*index)] = map[num].arr[i];
                (*index)++;
                if ((*index) == 8)
                {
                    (*index) = 0;
                    coding_to_char(buf, fo);
                }
            }
        }
    }
    free(text);
}

void compr_no_dif(FILE* fi, FILE* fo)
{
    unsigned char* text = (unsigned char*)malloc(input_length);
    unsigned char buf[8] = { 0 };
    ll index = 0;
    while (!feof(fi))
    {
        ll count = fread(text, 1, input_length, fi);
        for (ll i = 0; i < count; i++)
        {
            buf[index] = '1';
            index++;
            if (index == 8)
            {
                index = 0;
                coding_to_char(buf, fo);
            }
        }
    }
    if (index)
    {
        for (ll i = index; i < 8; i++)
            buf[i] = '0';
        coding_to_char(buf, fo);
    }
    free(text);
}

void gr_pr(alph* now, ll count)
{
    if (now->parent != NULL)
    {
        printf("%c %d\n", now->now, count);
        return;
    }
    gr_pr(now->left, count + 1);
    gr_pr(now->right, count + 1);
}

void compress(FILE* fi)
{
    unsigned char* text = (unsigned char*)malloc(input_length);
    char_count mas[256];
    for (ll i = 0; i < 256; i++)mas[i].count = 0;
    ll dif = 0;
    while (!feof(fi))
        text_fill(fi, text, mas, &dif);
    free(text);
    fseek(fi, 1, SEEK_SET);
    FILE* fo = fopen("out.txt", "wb");
    if (dif < 256)fputc(0, fo);
    if (dif > 1)
    {
        alph map[256];

        for (ll i = 0; i < 256; i++)map[i].weight = 0;
        alph* kost = (alph*)malloc(sizeof(alph));
        alph* haf_tree = create_tree(mas, dif, kost);
        if (dif == 256)
        {
            fputc(128, fo);
            fputc(128, fo);
        }
        else
            fputc((unsigned char)dif, fo);
        unsigned char buf[8] = { 0 };
        ll index = 0;

        //gr_pr(haf_tree,0);
        alph* stop = haf_tree;
        while (stop->right != NULL)
            stop = stop->right;
        dfs(haf_tree, 0, map, fo, buf, &index, stop);
        index = 0;
        for (ll i = 0; i < 8; i++)buf[i] = 0;
        find_trash(fi, map, buf, &index);
        fseek(fi, 1, SEEK_SET);

        if (index == 8)
        {
            index = 0;
            coding_to_char(buf, fo);
        }
        coding(fi, map, fo, buf, &index);
        gr_free(haf_tree);
        free(kost);
    }
    else
    {
        if (dif)
        {
            char def = 0;
            for (ll i = 0; i < 256; i++)
                if (mas[i].count)
                {
                    def = mas[i].now;
                    break;
                }
            fputc((unsigned char)dif, fo);
            fputc((unsigned char)def, fo);
            compr_no_dif(fi, fo);
        }
        else
            fputc((unsigned char)dif, fo);
    }
    fclose(fo);
    fclose(fi);
}

void fill_dif(FILE* fi, ll* dif)
{
    unsigned char buf;
    buf = fgetc(fi);
    if ((int)buf == 0)
    {
        buf = fgetc(fi);
        (*dif) = (int)buf;
    }
    else
    {
        buf = fgetc(fi);
        if (((int)buf) == 128)
            (*dif) = 256;
    }
}

void fill_nodes(alph* now)
{
    alph* x_node = (alph*)malloc(sizeof(alph));
    x_node->now = 0;
    x_node->left = x_node->right = NULL;
    now->left = x_node;
    x_node->parent = now;
    x_node = (alph*)malloc(sizeof(alph));
    x_node->now = 0;
    x_node->left = x_node->right = NULL;
    now->right = x_node;
    x_node->parent = now;
}

unsigned char translate(char* mas)
{
    ll res = 0, pow = 1;
    for (ll i = 7; i >= 0; i--)
    {
        if (mas[i] == '1')
            res += pow;
        pow *= 2;
    }
    return (unsigned char)res;
}

ll read_bit(char* buf, ll pos)
{
    return buf[pos] == '1';
}

alph* uncompr_tree(FILE* fi, ll dif)
{

    alph* start_node = (alph*)malloc(sizeof(alph));
    start_node->parent = NULL;
    start_node->now = 0;
    alph* now_node = start_node;

    unsigned char c;
    char buf[8] = { 0 };
    ll index_buf = 0, state = 0;
    while (dif != 0)
    {
        ll key = 0;
        while (!key)
        {
            index_buf = index_buf % 8;
            if (!index_buf)
            {
                c = fgetc(fi);
                decode_digit(buf, c);
            }
            if (!read_bit(buf, index_buf))
            {
                fill_nodes(now_node);
                now_node = now_node->left;
            }
            else
            {
                key = 1;
                state = 8;
            }
            index_buf++;
        }
        if (key)
        {
            dif--;
            char answer[8];
            ll ind_answ = 0;

            while (state)
            {
                index_buf = index_buf % 8;
                if (!index_buf)
                {
                    c = fgetc(fi);
                    decode_digit(buf, c);
                }
                if (read_bit(buf, index_buf))
                    answer[ind_answ] = '1';
                else answer[ind_answ] = '0';
                ind_answ++;
                index_buf++;
                state--;
            }
            now_node->now = translate(answer);
            if (now_node == now_node->parent->left)
                now_node = now_node->parent->right;
            else
            {
                while (now_node->now)
                {
                    if (now_node == now_node->parent->right)
                        now_node->parent->now = 1;
                    now_node = now_node->parent;
                    if (now_node == start_node && start_node->now == 1)
                        break;
                }
                now_node = now_node->right;
            }
        }
    }
    return start_node;
}

void decoding(alph* haf_tree, FILE* fi, FILE* fo)
{
    alph* now_node = haf_tree;
    unsigned char* text = (unsigned char*)malloc(input_length);
    char buf[8];
    unsigned char tail = fgetc(fi);
    decode_digit(buf, tail);
    ll num_tail = 0;
    for (ll i = 0; i < 8; i++)
    {
        if (buf[i] == '1')
        {
            num_tail = i;
            break;
        }
    }
    for (ll l = num_tail + 1; l < 8; l++)
    {
        if (buf[l] == '0')
        {
            now_node = now_node->left;
            if ((now_node->now != 0 && now_node->now != 1) || (now_node->left == NULL && now_node->right == NULL))
            {
                fputc((unsigned char)now_node->now, fo);
                now_node = haf_tree;
            }
        }
        else
        {
            now_node = now_node->right;
            if ((now_node->now != 0 && now_node->now != 1) || (now_node->left == NULL && now_node->right == NULL))
            {
                fputc((unsigned char)now_node->now, fo);
                now_node = haf_tree;
            }
        }
    }
    while (!feof(fi))
    {
        ll count = fread(text, 1, input_length, fi);
        for (ll i = 0; i < count; i++)
        {
            decode_digit(buf, text[i]);
            for (ll l = 0; l < 8; l++)
            {
                if (buf[l] == '0')
                {
                    now_node = now_node->left;
                    if ((now_node->now != 0 && now_node->now != 1) || (now_node->left == NULL && now_node->right == NULL))
                    {
                        fputc((unsigned char)now_node->now, fo);
                        now_node = haf_tree;
                    }
                }
                else
                {
                    now_node = now_node->right;
                    if ((now_node->now != 0 && now_node->now != 1) || (now_node->left == NULL && now_node->right == NULL))
                    {
                        fputc((unsigned char)now_node->now, fo);
                        now_node = haf_tree;
                    }
                }
            }
        }
    }
    free(text);
}

void uncompr_no_dif(FILE* fi, FILE* fo)
{
    unsigned char answ = 0;
    answ = fgetc(fi);
    while (!feof(fi))
    {
        unsigned char enter = fgetc(fi);
        if (!feof(fi))
        {
            char buf[8] = { 0 };
            decode_digit(buf, enter);
            for (ll i = 0; i < 8; i++)
                if (buf[i] == '1')
                    fputc(answ, fo);
        }
    }
}

void uncompress(FILE* fi)
{
    ll dif = 0;
    FILE* fo = fopen("out.txt", "wb");
    fill_dif(fi, &dif);
    if (dif > 1)
    {
        alph* haf_tree = uncompr_tree(fi, dif);

        decoding(haf_tree, fi, fo);
        gr_free(haf_tree);
        fclose(fi);
        fclose(fo);
    }
    else
    {
        if (dif)
            uncompr_no_dif(fi, fo);
        fclose(fi);
        fclose(fo);
    }
}

int main()
{
    FILE* fi = fopen("in.txt", "rb");
    char orient;
    orient = fgetc(fi);
    if (orient == 'c')
        compress(fi);
    else
        uncompress(fi);

}
