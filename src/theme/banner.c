
#include "minishell.h"

/* ==================== THE DREAM REALM PALETTE ==================== */
#define CLEAR       "\033[2J\033[H"
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"

/* Structure & Input */
#define BORDER    "\033[38;5;195m"   /* Steel Blue Frame */
#define PRISM       "\033[38;5;111m"  /* Soft Glowing Blue */
#define TITLE       "\033[38;5;255m"   /* Pure White */
#define AUTHORS     "\033[38;5;253m" /* Ice Blue */
#define INPUT       "\033[38;5;15m"   /* Pure White input beam */

/* The Fractured Light (Cool-Toned Spectrum) */
#define C_1         "\033[38;5;195m"  /* 1. Ice White */
#define C_2         "\033[38;5;159m"  /* 2. Pale Cyan */
#define C_3         "\033[38;5;87m"   /* 3. Bright Cyan */
#define C_4         "\033[38;5;111m"  /* 4. Mid Blue */
#define C_5         "\033[38;5;147m"  /* 5. Pale Violet */
#define C_6         "\033[38;5;141m"  /* 6. Dream Purple */
#define C_7         "\033[38;5;99m"   /* 7. Deep Indigo */
/* ================================================================= */

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
    printf(BORDER "    ┌──────────────── The Dark Side Of The Shell ────────────────┐\n" RESET);

    P("                                                          ");
    P(PRISM "                           /\\" RESET "                             ");
    P(PRISM "                          /  \\" RESET "                            ");
    P(PRISM "                         /    \\" RESET "                           ");
    P(PRISM "                        /   " C_1 "·" PRISM "  \\" RESET "  " C_1 "·  tokenization" RESET "         ");
    P(PRISM "                       /   " C_2 "· ·" PRISM "  \\" RESET "  " C_2 "· ·  parsing" RESET "           ");
    P(PRISM "                      /   " C_3 "· · ·" PRISM "  \\" RESET "  " C_3 "· · ·  expansion" RESET "      ");
    P(INPUT "     input · · · · · " PRISM "/   " C_4 "· · · ·" PRISM "  \\" RESET "  " C_4 "· · · ·  builtins" RESET "    ");
    P(PRISM "                    /       " C_5 "· · ·" PRISM "  \\" RESET "  " C_5 "· · ·  signals" RESET "      ");
    P(PRISM "                   /           " C_6 "· ·" PRISM "  \\" RESET "  " C_6 "· ·  pipes" RESET "         ");
    P(PRISM "                  /               " C_7 "·" PRISM "  \\" RESET "  " C_7 "·  execution" RESET "      ");
    P(PRISM "                 /                    \\" RESET "                   ");
    P(PRISM "                /______________________\\" RESET "                  ");
    
    P("                                                          ");
    
    P(TITLE "                                   ▄▄          ▄▄ ▄▄      " RESET);
    P(TITLE "               ▀▀        ▀▀        ██          ██ ██      " RESET);
    P(TITLE "      ███▄███▄ ██  ████▄ ██  ▄█▀▀▀ ████▄ ▄█▀█▄ ██ ██      " RESET);
    P(TITLE "      ██ ██ ██ ██  ██ ██ ██  ▀███▄ ██ ██ ██▄█▀ ██ ██      " RESET);
    P(TITLE "      ██ ██ ██ ██▄ ██ ██ ██▄ ▄▄▄█▀ ██ ██ ▀█▄▄▄ ██ ██      " RESET);
    
    P("                                                          ");
    
    P("                   " DIM AUTHORS "anashwan  ×  masad" RESET "                     ");
    
    P("                                                          ");

    /* Bottom border: 58 horizontal bars */
    printf(BORDER "    └──────────────────────── 42 Amman ──────────────────────────┘\n" RESET);

    printf("\n\n");
}