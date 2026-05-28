#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

/* ==================== DEEP SPACE PALETTE ==================== */
#define CLEAR       "\033[2J\033[H"
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define BORDER      "\033[38;5;27m"
#define PRISM       "\033[38;5;69m"
#define DOTS        "\033[38;5;105m"
#define LABEL       "\033[38;5;147m"
#define TITLE       "\033[38;5;39m"
#define AUTHORS     "\033[38;5;183m"
#define INPUT       "\033[38;5;60m"
/* ============================================================ */

/* * Placed outside the function.
 * Hardcodes the left and right border walls, dumping the line perfectly inside.
 */
#define P(line) do { \
    printf(RESET); \
    printf(BORDER "    │ " RESET "%s" BORDER " │\n" RESET, line); \
    fflush(stdout); \
    usleep(25000); \
} while(0)

void    print_banner(void)
{
    /* Instantly wipe terminal */
    printf(CLEAR);
    fflush(stdout);
    usleep(100000);

    printf("\n\n");

    /* Top border: 58 horizontal bars */
    printf(BORDER "    ┌────────────────────────────────────────────────────────────┐\n" RESET);

    /* The mathematically audited 58-character lines */
    P("                                                          ");
    P(PRISM "                           /\\" RESET "                             ");
    P(PRISM "                          /  \\" RESET "                            ");
    P(PRISM "                         /    \\" RESET "                           ");
    P(PRISM "                        /   " DOTS "·" PRISM "  \\" RESET "  " DOTS "·  " LABEL "tokenization" RESET "         ");
    P(PRISM "                       /   " DOTS "· ·" PRISM "  \\" RESET "  " DOTS "· ·  " LABEL "parsing" RESET "           ");
    P(PRISM "                      /   " DOTS "· · ·" PRISM "  \\" RESET "  " DOTS "· · ·  " LABEL "expansion" RESET "      ");
    P(INPUT "     input · · · · · " PRISM "/   " DOTS "· · · ·" PRISM "  \\" RESET "  " DOTS "· · · ·  " LABEL "builtins" RESET "    ");
    P(PRISM "                    /       " DOTS "· · ·" PRISM "  \\" RESET "  " DOTS "· · ·  " LABEL "signals" RESET "      ");
    P(PRISM "                   /           " DOTS "· ·" PRISM "  \\" RESET "  " DOTS "· ·  " LABEL "pipes" RESET "         ");
    P(PRISM "                  /               " DOTS "·" PRISM "  \\" RESET "  " DOTS "·  " LABEL "execution" RESET "      ");
    P(PRISM "                 /                    \\" RESET "                   ");
    
    /* Prism closes cleanly */
    P(PRISM "                /______________________\\" RESET "                  ");
    
    P("                                                          ");
    
    /* The new heavy block logo, flawlessly centered in 58 chars */
    P(TITLE "                                   ▄▄          ▄▄ ▄▄      " RESET);
    P(TITLE "               ▀▀        ▀▀        ██          ██ ██      " RESET);
    P(TITLE "      ███▄███▄ ██  ████▄ ██  ▄█▀▀▀ ████▄ ▄█▀█▄ ██ ██      " RESET);
    P(TITLE "      ██ ██ ██ ██  ██ ██ ██  ▀███▄ ██ ██ ██▄█▀ ██ ██      " RESET);
    P(TITLE "      ██ ██ ██ ██▄ ██ ██ ██▄ ▄▄▄█▀ ██ ██ ▀█▄▄▄ ██ ██      " RESET);
    
    P("                                                          ");
    
    /* Hardcoded spacing to perfectly center 18 and 9 character strings */
    P("                    " DIM AUTHORS "anashwan  ×  masad" RESET "                    ");
    P("                        " INPUT "42 amman" RESET "                         ");
    
    P("                                                          ");

    /* Bottom border: 58 horizontal bars */
    printf(BORDER "    └────────────────────────────────────────────────────────────┘\n" RESET);

    printf("\n\n");
}