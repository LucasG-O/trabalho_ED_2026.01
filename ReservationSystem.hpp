#ifndef RESERVATIONSYSTEM_HPP
#define RESERVATIONSYSTEM_HPP

#include <string>
#include "ReservationRequest.hpp"


class ReservationSystem {

private:
    int qtd_salas;
    int* capacidade_salas;
    struct ReservaNode {
    ReservationRequest reserva;
    ReservaNode* proximo;
};
    ReservaNode** reservas_salas; // Array de ponteiros para listas encadeadas de reservas por sala
    
    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int qtd_salas, int* capacidade_salas);

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);
    bool isAvailable(int room_index, std::string weekday, int start_hour, int end_hour);
    int Dia_to_Num(std::string dia);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

#endif
