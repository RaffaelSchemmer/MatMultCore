__Assume-se para este tutorial que o computador configurado possui arquitetura de máquina multicore de 64bits (x86-64).__

C (POSIX Threads):
========

Configurar o ambiente:
--------

1. Donwload Ubuntu 10.04 LTS: http://releases.ubuntu.com/lucid/ubuntu-10.04.4-server-amd64.iso

2. Em Update Manager instalar todos os Updates disponíveis.

Execução da aplicação (matrix.c):
--------

1. Definir nas constantes dentro do fonte:
  1.1. O tamanho da matriz TAM (linha 15).
  1.2. O número de threads numCores (linha 21). Leia as restrições aplicadas as limitações quanto a estas entradas.
2. Compilando o fonte: gcc -pthread -w -O2 -o matrix matrix.c
3. Executando o fonte: ./matrix
4. Dica: Descomente a linha 122 para visualização dos dados da aplicação.

Go:
========

Configurar o ambiente:
--------

1. Donwload Ubuntu 10.04 LTS: http://releases.ubuntu.com/lucid/ubuntu-10.04.4-server-amd64.iso
2. Em Update Manager instalar todos os Updates disponíveis.
3. Download do ambiente Go: http://code.google.com/p/go/downloads/detail?name=go1.2rc5.linux-amd64.tar.gz&can=2&q=
4. Extrair o pacote utilizando: tar -xvf go1.2rc5.linux-amd64.tar.gz
5. Mover a pasta extraida (go) para o diretório $HOME: mv ./go /home/userhere
6. Definir as seguintes variáveis de ambientes no $PATH (Via .bashrc), executando os comandos a seguir no diretório $HOME(/home/userhere):
  gedit .bashrc
  No fim do arquivo adicione as 2 linhas abaixo:
    export GOROOT=$HOME/go
    export PATH=$PATH:$GOROOT/bin
    Salve o arquivo.
    source .bashrc

Execução da aplicação (matrix.go):
--------

1. Definir nas constantes dentro do fonte do arquivo:
  1.1. O tamanho da matriz TAM (linha 23)
  1.2. O número de threads numCores (linha 21).
  1.3. Leia as restrições aplicadas as limitações quanto a estas entradas.
2. Compilando e disparando o fonte: go run matrix.go
3. Dica: Descomente a linha 172 para visualização dos dados da aplicação.

Cilk:
========

Configurar o ambiente:
--------

1. Donwload Ubuntu 10.04 LTS: http://releases.ubuntu.com/lucid/ubuntu-10.04.4-server-amd64.iso
2. Em Update Manager instalar todos os Updates disponíveis.
3. Download do SDK Cilk (Site da Intel): https://secure-software.intel.com/en-us/system/files/article/164673/cilk-8503-x86-64.release.tar.gz
4. Extrair o pacote utilizando: tar -xvf cilk-8503-x86-64.release.tar.gz
5. Mover a pasta extraida (cilk) para o diretório $HOME: mv ./cilk /home/userhere
6. Definir as seguintes variáveis de ambientes no $PATH (Via .bashrc), executando os comandos a seguir no diretório $HOME(/home/userhere):
   gedit .basrch
   No fim do arquivo adicione as 2 linhas abaixo:
      export CILK=/home/usercilk/cilk
      export PATH=$PATH:$CILK/bin
      Salve o arquivo.
      source .bashrc

Execução da aplicação (matrix.cpp):
--------

1. Definir nas constantes dentro do fonte o tamanho da matriz TAM (linha 13).
2. Compilando o fonte: cilk++ -o matrix matrix.cpp
3. Executando o fonte: ./matrix -cilk_set_worker_count 4 
   cilk_set_worker_count 4 define o número de threads que a estrutura cilk_for irá executar.
4. Dica: Descomente a linha 88 para visualização dos dados da aplicação.

UPC:
========

Configurar o ambiente:
--------

1. Donwload Ubuntu 12.04 LTS: http://mirror.pop-sc.rnp.br/mirror/ubuntu//precise/ubuntu-12.04.3-desktop-amd64.iso
2. Em Update Manager instalar todos os Updates disponíveis.
3. Download do compilador GNU UPC: http://www.gccupc.org/downloads/upc/rls/upc-4.9.0.1/upc-4.9.0.1-x86_64-linux-ubuntu12.4.tar.gz
4. Extrair o pacote utilizando: tar -xvf upc-4.9.0.1-x86_64-linux-ubuntu12.4.tar.gz
5. Mover a pasta extraida (cilk) para o diretório $HOME: mv ./usr /home/userhere
6. Definir as seguintes variáveis de ambientes no $PATH (Via .bashrc), executando os comandos a seguir no diretório $HOME(/home/userhere):
   gedit .basrch
   No fim do arquivo adicione as 5 linhas abaixo:
      LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/
      C_INCLUDE_PATH=/usr/include/x86_64-linux-gnu
      CPLUS_INCLUDE_PATH=/usr/include/x86_64-linux-gnu
      export UPC=/home/userhere/usr/local/gupc
      export PATH=$PATH:$UPC/bin
      Salve o arquivo.
      source .bashrc
7. Instalação da biblioteca lnuma (Necessária para compilação dos fontes): sudo su apt-get install libnuma-dev

Execução da aplicação (matrix.upc):
--------

1. Definir nas constantes dentro do fonte o tamanho da matriz TAM (linha 14).
2. Compilando o fonte: gupc -fupc-threads-2 -o matrix matrix.upc
   fupc-threads-4 que define o número de processos que o compilador UPC deverá gerar da aplicação:
3. Executando o fonte: ./matrix 
4. Dica: Descomente a linha 97 para visualização dos dados da aplicação.
