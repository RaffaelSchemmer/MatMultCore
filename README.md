Assume-se para este tutorial que o computador configurado possui arquitetura de máquina multicore de 64bits (x86-64).

C:
========

Configurar o ambiente:
--------

1. Donwload Ubuntu 10.04 LTS : http://releases.ubuntu.com/lucid/ubuntu-10.04.4-server-amd64.iso

2. Em Update Manager instalar todos os Updates disponíveis.

Execução da aplicação (matrix.c):
--------

1. Definir nas constantes dentro do fonte:

  1.1. O tamanho da matriz TAM (linha 15).
  
  1.2. O número de threads numCores (linha 21). Leia as restrições aplicadas as limitações quanto a estas entradas.

2. Compilando o fonte: gcc -lpthread -w -O2 -o matrix matrix.c
3. Executando o fonte: ./matrix

4. Dica: Descomente a linha 122 para visualização dos dados da aplicação.