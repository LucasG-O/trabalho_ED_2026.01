# Room Reservation System

## 1. Descrição do Projeto
Este projeto é um sistema em C++ desenvolvido para gerenciar a alocação de disciplinas em salas de aula durante os dias úteis da semana (segunda a sexta-feira). O sistema é capaz de processar solicitações de reserva, garantindo que não haja conflito de horários (sobreposições) e alocando automaticamente a primeira sala disponível que possua capacidade suficiente para o número de alunos da turma. O sistema também permite o cancelamento de reservas e a exibição ordenada da grade horária de todas as salas.

## 2. Instruções de Compilação
O projeto não utiliza bibliotecas externas e deve ser compilado utilizando o `g++`. Para compilar o código fonte e gerar o executável, abra o terminal na pasta raiz do projeto e execute o seguinte comando:

```bash
g++ main.cpp ReservationSystem.cpp ReservationRequest.cpp -o reservation_system
```

## 3. Instruções de Execução
Após a compilação bem-sucedida, um arquivo executável será gerado na mesma pasta. Para iniciar o programa com os casos de teste definidos no arquivo principal, utilize o comando correspondente ao seu sistema operacional:

* **No Windows (PowerShell/CMD):**
  ```bash
  .\reservation_system.exe
  ```

* **No Linux ou macOS:**
  ```bash
  ./reservation_system
  ```

## 4. Organização Interna dos Dados
Para cumprir a restrição de não utilizar a biblioteca padrão de templates do C++ (STL, como `std::vector` ou `std::list`), as estruturas de dados foram implementadas manualmente:

* **Requisições de Reserva:** Os dados de cada alocação (nome da disciplina, dia da semana, hora de início, hora de término e quantidade de alunos) são encapsulados em instâncias da classe `ReservationRequest`.
* **Gerenciamento de Salas (Array Dinâmico):** As salas do sistema são representadas por índices de um array alocado dinamicamente. Isso permite acesso em tempo constante O(1) a qualquer sala específica.
* **Armazenamento de Horários (Lista Encadeada Simples):** Cada índice do array de salas contém um ponteiro para a "cabeça" de uma lista encadeada (`ReservaNode`). Cada nó dessa lista armazena uma reserva daquela sala. 
* **Ordenação:** Sempre que o método `reserve` é chamado e encontra uma sala viável, o nó é inserido na lista encadeada da respectiva sala de forma **cronologicamente ordenada** (primeiro pelo dia da semana, depois pelo horário de início). Isso otimiza a verificação de conflitos e torna a função de exibir a grade horária (`printSchedule`) extremamente eficiente.