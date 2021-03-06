# MC714 - UNICAMP - Projeto 2
## Eleição de Líder - Algoritmo do Bully

* Cristina Freitas Bazzano - RA 135368
* Gabriel Militao Vinhas Lopes - RA 135801
* Flavio Altinier Maximiano da Silva - RA 135749
* Guilherme Bueno Andrade - RA 135939
* Marcos Massayuki Kobuchi, RA 136823

O algoritmo escolhido para implementação usando IPC foi o de eleição de líder, especificamente o Algoritmo do Bully.

Todos os arquivos para execução estão na pasta proj2 (Makefile incluso). Para executar, abra em um terminal o monitor:

$ ./monitor

E em terminais diferentes os processos (ou no mesmo terminal concatenados por &)

$ ./processo 1 & ./processo 2 & ./processo 3 & ./processo 4 & ./processo 5 & ./processo 6

Inicie os processos com 1, para nós o processo 0 é o monitor. Lembre-se do comando útil para matar os processos, já que todos estão em loop infinito:

$ pkill -9 processo

Note que para iniciar mais processos é preciso alterar a constante N no código-fonte; porém, para o monitor visual funcionar, é obrigatório que sejam 6 processos.

O monitor visual mostra cada um dos 6 processos como um vértice de um "hexágono" na tela. O processo lider é indicado com colchetes []. Quando um processo morre, ele é retirado da tela; ao reviver, volta no mesmo lugar. O monitor também mostra todas as trocas de mensagens entre processos para eleição de líderes, conforme as regras do algoritmo.

O algoritmo é executado de forma rápida; por isso, às vezes não é possível verificar sua corretude facilmente. Por esse motivo, além do auxílio visual, ao ser fechado o monitor salva num arquivo "log.txt" todas as mensagens enviadas no sistema, além de mortes e renascimentos de processos. Analisando-se esse log pode-se comprovar a crretude do algoritmo implementado.

----------------------------------------------------
