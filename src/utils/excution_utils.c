#include "../../inc/minishell.h"

char *get_current_path()
{
	char *path = getenv("PATH");
    
    if (path != NULL) {
        return(path);
    } else {
        return (NULL);
    }

}

int main ()
{
	printf ("%s",get_current_path());

	return 0;
}
