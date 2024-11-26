#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct player {
    char nickname[10];
    char mouse_or_tablet[7];
    int dpi_or_height;
    float sens_or_width;
};

struct notebook {
    struct player players[100];
    int n;
};

struct notebook osu_players;

void print_table() {
    printf("_______________________________________________________________________________________________________________________\n");
    printf(" N Nickname              Mouse/Tablet              DPI/Height          Sensitivity/Width\n");
    for (int i = 0; i < osu_players.n; i++) {
        printf("%1i) %-21s %-25s %-19d %3.2f\n", i + 1, osu_players.players[i].nickname, osu_players.players[i].mouse_or_tablet, osu_players.players[i].dpi_or_height, osu_players.players[i].sens_or_width);
    }
    printf("_______________________________________________________________________________________________________________________\n");
}

void print_spec() {
    char device[100];
    char nick[100];
    int dpi_height;
    float sens_width;
    printf("1 - mouse/tablet\n"
           "2 - nickname\n"
           "3 - dpi/height\n"
           "4 - sens/width\n"
           "> ");
    while (getchar() != '\n');
    char c;
    if (scanf("%c", &c) == 0) {
        return;
    }
    switch (c) {
        case '1':
            printf("mouse or tablet > ");
            if (scanf("%s", device) == 0) {
                return;
            }
            device[99] = '\0';
            printf("_______________________________________________________________________________________________________________________\n");
            printf(" N Nickname              Mouse/Tablet              DPI/Height          Sensitivity/Width\n");
            for (int i = 0; i < osu_players.n; i++) {
                if (strcmp(device, osu_players.players[i].mouse_or_tablet) == 0) {
                    printf("%1i) %-21s %-25s %-19d %3.2f\n", i + 1, osu_players.players[i].nickname, osu_players.players[i].mouse_or_tablet, osu_players.players[i].dpi_or_height, osu_players.players[i].sens_or_width);
                }
            }
            break;
        case '2':
            printf("nickname > ");
            if (scanf("%s", nick) == 0) {
                return;
            }
            nick[99] = '\0';
            printf("_______________________________________________________________________________________________________________________\n");
            printf(" N Nickname              Mouse/Tablet              DPI/Height          Sensitivity/Width\n");
            for (int i = 0; i < osu_players.n; i++) {
                if (strcmp(nick, osu_players.players[i].nickname) == 0) {
                    printf("%1i) %-21s %-25s %-19d %3.2f\n", i + 1, osu_players.players[i].nickname, osu_players.players[i].mouse_or_tablet, osu_players.players[i].dpi_or_height, osu_players.players[i].sens_or_width);
                }
            }
            break;
        case '3':
            printf("dpi or height > ");
            if (scanf("%d", &dpi_height) == 0) {
                return;
            }
            printf("_______________________________________________________________________________________________________________________\n");
            printf(" N Nickname              Mouse/Tablet              DPI/Height          Sensitivity/Width\n");
            for (int i = 0; i < osu_players.n; i++) {
                if (dpi_height == osu_players.players[i].dpi_or_height) {
                    printf("%1i) %-21s %-25s %-19d %3.2f\n", i + 1, osu_players.players[i].nickname, osu_players.players[i].mouse_or_tablet, osu_players.players[i].dpi_or_height, osu_players.players[i].sens_or_width);
                }
            }
            break;
        case '4':
            printf("sens or width > ");
            if (scanf("%f", &sens_width) == 0) {
                return;
            }
            printf("_______________________________________________________________________________________________________________________\n");
            printf(" N Nickname              Mouse/Tablet              DPI/Height          Sensitivity/Width\n");
            for (int i = 0; i < osu_players.n; i++) {
                if (sens_width == osu_players.players[i].sens_or_width) {
                    printf("%1i) %-21s %-25s %-19d %3.2f\n", i + 1, osu_players.players[i].nickname, osu_players.players[i].mouse_or_tablet, osu_players.players[i].dpi_or_height, osu_players.players[i].sens_or_width);
                }
            }
            break;
        default:
            printf("try again\n");
       }
        
}

void add() {
    char mouse[6] = "mouse";
    char tablet[7] = "tablet";
    if (osu_players.n == 99) {
        fprintf(stderr, "table is full \n");
        return;
    }
    printf("nickname - ");
    if (scanf("%s", osu_players.players[osu_players.n].nickname) == 0) {
        return;
    }
    printf("mouse/tablet - ");
    if (scanf("%s", &osu_players.players[osu_players.n].mouse_or_tablet) == 0) {
        return;
    }
    if (strcmp(mouse, osu_players.players[osu_players.n].mouse_or_tablet) != 0 && strcmp(mouse, osu_players.players[osu_players.n].mouse_or_tablet) != 0) {
        printf("^enter mouse or tablet\n");
        return;
    }
    printf("dpi/height - ");
    if (scanf("%i", &osu_players.players[osu_players.n].dpi_or_height) == 0) {
        printf("^wrong input\n");
        return;
    }
    printf("sensitivity/width - ");
    if (scanf("%f", &osu_players.players[osu_players.n].sens_or_width) == 0) {
        printf("^wrong input\n");
        return;
    }
    osu_players.n++;
    printf("..............added\n");
}

void delete_player() {
    int i;
    printf("number to delete > ");
    if (scanf("%d", &i) == 0) {
        return;
    }
    if (i < 1 || i > osu_players.n) {
        fprintf(stderr, "there is no such number\n");
        return;
    }
    for (i--; i < osu_players.n - 1; i++) {
        osu_players.players[i] = osu_players.players[i + 1];
    }
    osu_players.n--;
    printf("..............deleted\n");
}

void save() {
    FILE* F = fopen("osuplayers.txt", "wt");
    if (F == NULL) {
        fprintf(stderr, "cant find this file to write\n");
        return;
    }
    fprintf(F, "%i\n", osu_players.n);
    for (int i = 0; i < osu_players.n; i++) {
        fprintf(F, "%s %s %d %f\n", osu_players.players[i].nickname, osu_players.players[i].mouse_or_tablet, osu_players.players[i].dpi_or_height, osu_players.players[i].sens_or_width);
    }
    fclose(F);
    printf("..............saved\n");
}

void load() {
    FILE* F = fopen("osuplayers.txt", "rt");
    if (F == NULL) {
        fprintf(stderr, "can find this file to read\n");
        return;
    }
    if (fscanf(F, "%i", &osu_players.n) == 0) {
        return;
    }
    for (int i = 0; i < osu_players.n; i++) {
        if (fscanf(F, "%s%s%d%f", osu_players.players[i].nickname, osu_players.players[i].mouse_or_tablet, &osu_players.players[i].dpi_or_height, &osu_players.players[i].sens_or_width) == 0) {
            return;
        }
    }
    fclose(F);
    printf("..............loaded\n");
}

int main() {
    int key = 1;
    while (key == 1) {
        printf("_______________________________________________________________________________________________________________________\n"
            "MENU\n"
            "//TYPE NUMBER TO CALL FUNC//\n"
            "(0) exit\n"
            "(1) add\n"
            "(2) save\n"
            "(3) load\n"
            "(4) print\n"
            "(5) print special\n"
            "(6) delete\n"
            "> ");
        char c;
        if (scanf("%c", &c) == 0) {
            return 0;
        }
        switch (c) {
            case '1':
                add();
                while (getchar() != '\n');
                continue;
            case '2':
                save();
                while (getchar() != '\n');
                continue;
            case '3':
                load();
                while (getchar() != '\n');
                continue;
            case '4':
                print_table();
                while (getchar() != '\n');
                continue;
            case '5':
                print_spec();
                while (getchar() != '\n');
                continue;
            case '6':
                delete_player();
                while (getchar() != '\n');
                continue;
            case '0':
                break;
        }
    }
    return 0;
}













































   /* void sort() {
        struct player t;
        for (int i = 0; i < osu_players.n - 1; i++) {
            for (int j = 0; j < osu_players.n - 1; j++) {
                if (osu_players.players[j].sens_or_width < osu_players.players[j + 1].sens_or_width) {
                    t = osu_players.players[j];
                    osu_players.players[j] = osu_players.players[j + 1];
                    osu_players.players[j + 1] = t;
                }
            }
        }
    }*/
//int menu() {
//    int c = 0;
//    while ((c < '0' || c > '7') && c != 27) {
//        printf("MENU\n"
//            "//TYPE NUMBER TO CALL FUNC//\n"
//            "(0) exit\n"
//            "(1) add\n"
//            "(2) save\n"
//            "(3) load\n"
//            "(4) print\n"
//            "(5) print devices\n"
//            "(6) delete\n"
//            "> ");
//        c = _getch();
//        printf("%c\n", c);
//    }
//    return c;
//}