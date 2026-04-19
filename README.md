# Simple Simon (SDL2)

Este projeto foi iniciado no dia **6 de abril de 2026** e consiste na implementação de um jogo em C inspirado no clássico *Simple Simon*.

O jogo utiliza a biblioteca **SDL2** e extensões associadas para criar uma aplicação gráfica em janela, com suporte a imagens, áudio e texto.

## Tecnologias Utilizadas

* Linguagem: **C**
* Bibliotecas:

  * SDL2
  * SDL2_image
  * SDL2_mixer
  * SDL2_ttf

## Estrutura do Projeto
```bash
.
├── src/        # Código fonte (.c)
├── sfx/        # Ficheiros de áudio utilizados
├── musica/     # Música que implementamos para tocar ao longo do jogo
├── include/    # Headers (.h)
├── assets/     # Imagens e fontes necessárias ao projeto
├── build/      # Ficheiros objeto (.o) (gerado automaticamente)
├── Makefile
├── simpleSimon # Executável final (gerado automaticamente)
├── TestesSimpleSimon # Alguns testes de funções utilizando CUnit
└── README.md
```

## Assets

As texturas utilizadas no projeto foram inspiradas no jogo *Balatro*.
Todos os recursos utilizados são devidamente referenciados dentro do jogo, com indicação dos respetivos autores.

## Compilação

Para compilar o projeto, utilize o `make simpleSimon`:

```bash
make
```

O executável gerado será:

```
simpleSimon
```

### Verificar dependências

Antes de compilar, pode verificar se todas as dependências estão instaladas:

```bash
make check
```

### Limpar ficheiros compilados

```bash
make clean
```

## Execução

Após compilação:

```bash
./simpleSimon
```