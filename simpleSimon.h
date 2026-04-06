typedef int numCarta;

typedef struct ultimaJogada{
    numCarta carta;
    int novaPos;
    int antigaPos;
}lastMove;
typedef struct reverterJogada{
    int isp;
    lastMove ultimasJogadas[250];
}undoMove;

typedef struct str{
    char str[20];
}string;
