#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

int main() {
    char buf[4096];
    printf("input str: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return INVALID_INPUT;
    }

    buf[strcspn(buf, "\n")] = '\0';

    return_codes status;

    status = check_brackets(buf);
    err_status(status);
    return status;
}



// qwertyu(1+2*[65-34i(ttdyofyifkf{jdhfhkdf})dnfdj             876tudsyfyiunefhsidfkjshd kfj dsfsd hfks            ]87783648w76r8w736r83w78r37 wd fusid f 79eiuwfh sdiuyf {dhfgdyfgsduyfgs} uh fsfgsgf) sfsdhfkhsdhfshf
