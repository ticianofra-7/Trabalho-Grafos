#ifndef NO_H
#define NO_H

class No
{
    public:
        int coluna;
        int valor;
        No* prox;

        No(int c, int v) : coluna(c), valor(v), prox(nullptr){}
};

#endif // NO_H