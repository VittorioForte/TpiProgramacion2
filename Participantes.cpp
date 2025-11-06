#include <cstdio>
#include "Participantes.h"

bool Participantes::escribirDisco(int pos) {
    FILE *p;
    if (pos == -1)
        p = fopen("participantes.dat", "ab");
    else
        p = fopen("participantes.dat", "rb+");

    if (p == NULL) return false;

    if (pos != -1)
        fseek(p, pos * sizeof(Participantes), 0);

    bool ok = fwrite(this, sizeof(Participantes), 1, p);
    fclose(p);
    return ok;
}


bool Participantes::leerDisco(int pos) {
    FILE *p = fopen("participantes.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Participantes), 0);
    bool ok = fread(this, sizeof(Participantes), 1, p);
    fclose(p);
    return ok;
}
