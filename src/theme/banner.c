#include "minishell.h"

#define P(line) do { \
    printf(RESET); \
    printf(BORDER "    │ " RESET "%s" BORDER " │\n" RESET, line); \
    fflush(stdout); \
    usleep(25000); \
} while(0)

void    print_banner(void)
{
    printf(CLEAR);
    fflush(stdout);
    usleep(100000);
    printf("\n");
    printf(BORDER "    ┌────────────────── The Dark Side Of The Shell ──────────────────┐\n" RESET);
    P("                                                              ");
    P(PRISM "                             /\\" RESET "                               ");
    P(PRISM "                            /  \\" RESET "                              ");
    P(PRISM "                           /    \\" RESET "                             ");
    P(PRISM "                          /   " C_1 "·" PRISM "  \\" RESET "  " C_1 "·  tokenization" RESET "           ");
    P(PRISM "                         /   " C_2 "· ·" PRISM "  \\" RESET "  " C_2 "· ·  parsing" RESET "             ");
    P(PRISM "                        /   " C_3 "· · ·" PRISM "  \\" RESET "  " C_3 "· · ·  expansion" RESET "        ");
    P(INPUT "       input · · · · · " PRISM "/   " C_4 "· · · ·" PRISM "  \\" RESET "  " C_4 "· · · ·  builtins" RESET "      ");
    P(PRISM "                      /       " C_5 "· · ·" PRISM "  \\" RESET "  " C_5 "· · ·  signals" RESET "        ");
    P(PRISM "                     /           " C_6 "· ·" PRISM "  \\" RESET "  " C_6 "· ·  pipes" RESET "           ");
    P(PRISM "                    /               " C_7 "·" PRISM "  \\" RESET "  " C_7 "·  execution" RESET "        ");
    P(PRISM "                   /                    \\" RESET "                     ");
    P(PRISM "                  /______________________\\" RESET "                    ");
    P("                                                              ");
    P(TITLE "                   ____  ____ _ _____ / /_                    " RESET);
    P(TITLE "                  / __ \\/ __ `// ___// __ \\                   " RESET);
    P(TITLE "                 / / / / /_/ /(__  )/ / / /                   " RESET);
    P(TITLE "                /_/ /_/\\__,_//____//_/ /_/                    " RESET);
    P("                                                              ");
    // P("                    " DIM AUTHORS "anashwan  ×  masad" RESET "                        ");
    P("                                                              ");
    printf(BORDER "    └────────────────────────── 42 Amman ────────────────────────────┘\n" RESET);
    printf("\n");
}