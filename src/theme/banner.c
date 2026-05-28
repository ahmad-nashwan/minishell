#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

/* ==================== DEEP SPACE PALETTE ==================== */
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
    printf(BORDER "    │ " RESET "%s" BORDER " │\n" RESET, line); \
    fflush(stdout); \
    usleep(25000); \
} while(0)

void    print_banner(void)
{
    printf("\n\n");

    /* Top border: 56 horizontal bars */
    printf(BORDER "    ┌──────────────────────────────────────────────────────────┐\n" RESET);

    P("                                                        ");

    /* * The Prism: EVERY space on the right side of the RESET code is mathematically 
     * calculated to hit exactly 56 characters. Do not add or remove spaces!
     */
    P(PRISM "                          /\\" RESET "                            ");
    P(PRISM "                         /  \\" RESET "                           ");
    P(PRISM "                        /    \\" RESET "                          ");
    P(PRISM "                       /   " DOTS "·" PRISM "  \\" RESET "  " DOTS "·  " LABEL "tokenization" RESET "        ");
    P(PRISM "                      /   " DOTS "· ·" PRISM "  \\" RESET "  " DOTS "· ·  " LABEL "parsing" RESET "          ");
    P(PRISM "                     /   " DOTS "· · ·" PRISM "  \\" RESET "  " DOTS "· · ·  " LABEL "expansion" RESET "     ");
    P(INPUT "    input · · · · · " PRISM "/   " DOTS "· · · ·" PRISM "  \\" RESET "  " DOTS "· · · ·  " LABEL "builtins" RESET "   ");
    P(PRISM "                   /       " DOTS "· · ·" PRISM "  \\" RESET "  " DOTS "· · ·  " LABEL "signals" RESET "     ");
    P(PRISM "                  /           " DOTS "· ·" PRISM "  \\" RESET "  " DOTS "· ·  " LABEL "pipes" RESET "        ");
    P(PRISM "                 /               " DOTS "·" PRISM "  \\" RESET "  " DOTS "·  " LABEL "execution" RESET "     ");
    P(PRISM "                /                    \\" RESET "                  ");
    P(PRISM "               /   " BOLD TITLE "m i n i s h e l l" RESET PRISM "  \\" RESET "                 ");
    P(PRISM "              /________________________\\" RESET "                ");

    P("                                                        ");

    /* Hardcoded spacing to perfectly center 18 and 8 character strings */
    P("                 " DIM AUTHORS "anashwan  ×  masad" RESET "                     ");
    P("                      " DIM INPUT "@42 amman" RESET "                         ");

    P("                                                        ");

    /* Bottom border: 56 horizontal bars */
    printf(BORDER "    └──────────────────────────────────────────────────────────┘\n" RESET);

    printf("\n\n");
}