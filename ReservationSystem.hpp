#include <string>
#include "ReservationRequest.hpp"


class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    struct ReservaNode {
    ReservationRequest requisicao;
    ReservaNode* proximo;
};

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};