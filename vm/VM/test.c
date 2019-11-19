#include <ncurses.h>

int main(void) {
    WINDOW *haut, *bas;

    initscr();
    haut= subwin(stdscr, LINES / 2, COLS, 0, 0);        // Créé une fenêtre de 'LINES / 2' lignes et de COLS colonnes en 0, 0
    bas= subwin(stdscr, LINES / 2, COLS, LINES / 2, 0); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent

    box(haut, ACS_VLINE, ACS_HLINE);
    box(bas, ACS_VLINE, ACS_HLINE);

    mvwprintw(haut, 1, 1, "Ceci est la fenetre du haut");
    mvwprintw(bas, 1, 1, "Ceci est la fenetre du bas");

    wrefresh(haut);
    wrefresh(bas);

    getch();
    endwin();

    free(haut);
    free(bas);

    return 0;
}
