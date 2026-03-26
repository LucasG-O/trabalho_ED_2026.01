#ifndef RESERVATIONSYSTEM_HPP // Boa prática para evitar erro de compilação
#define RESERVATIONSYSTEM_HPP

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
    ReservaNode** room_schedules;
    
    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);
    bool isAvailable(int room_index, std::string weekday, int start_hour, int end_hour);
    int valorDoDia(std::string dia);
    
    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

#endif;