# Projeto: Cálculo de Autovalores por Power Iteration e QR Iteration

## Descrição

Este projeto em C implementa métodos numéricos para cálculo de autovalores de matrizes quadradas reais, utilizando duas técnicas principais:

- **Power Iteration com deflation**: método iterativo focado na obtenção dos maiores autovalores e seus autovetores correspondentes.
- **QR Iteration (com e sem deslocamento)**: método clássico que permite calcular todos os autovalores de uma matriz.

---

## Funcionamento do Programa

O programa realiza o cálculo dos autovalores a partir de matrizes armazenadas em arquivos de texto (.txt) localizados na pasta `input/`. Ele oferece os seguintes métodos:

### Power Iteration com Deflation
- Encontra iterativamente os maiores autovalores em módulo e seus autovetores.
- Após identificar o maior autovalor, aplica a técnica de deflation para "remover" sua influência da matriz, possibilitando a descoberta dos próximos autovalores mais relevantes.
- O programa calcula os três maiores autovalores usando essa técnica.


### QR Iteration (com e sem deslocamento)
- Método clássico que decompõe a matriz em produtos QR (Q ortogonal e R triangular superior).
- Ao multiplicar R por Q em ordem invertida e iterar, a matriz converge para uma forma quase triangular, revelando os autovalores na diagonal.
- A versão com deslocamento acelera a convergência usando valores de deslocamento apropriados.

---

## Como Utilizar

1. Prepare suas matrizes em arquivos `.txt` e coloque-os na pasta `input/`.
2. Execute o programa:
   - Linux/macOS: `./eigenvalues`
   - Windows: `eigenvalues.exe`
3. O programa listará automaticamente os arquivos `.txt` disponíveis para seleção.
4. Escolha a matriz desejada digitando o número correspondente.
5. O programa calculará os autovalores usando os três métodos mencionados e exibirá os resultados, tempos e iterações.
6. Ao final, você poderá optar por calcular autovalores para outra matriz ou encerrar o programa.

---

## Tecnologias Utilizadas

- Linguagem C (padrão C99)

---

## Instalação e Execução

### Pré-requisitos

- Compilador C instalado (ex: GCC)
- Ambiente configurado para compilação C

### Passo a passo

1. Clone ou baixe este repositório.
2. Navegue até a pasta do projeto pelo terminal.
3. Compile o programa com o comando:

```bash
gcc src/main.c src/matrix.c src/io.c src/power_iteration.c src/qr.c -I include -o eigenvalues -lm
