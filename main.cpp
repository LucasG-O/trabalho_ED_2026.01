#include <iostream> 
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"
#include <string>

int main(){
    int qtd_salas = 3;
    int capacidade_salas[] = {30, 50, 100};
    ReservationSystem sistema(qtd_salas, capacidade_salas);

    ReservationRequest req1("Matematica","segunda" , 9, 11, 25);
    ReservationRequest req2("Fisica","segunda", 10, 12, 20);
    ReservationRequest req3("Quimica","terca", 14, 16, 40);
    ReservationRequest req4("Biologia","quarta", 8, 10, 35);
    ReservationRequest req5("Historia","quinta", 13, 15, 45);
    ReservationRequest req6("Geografia","sexta", 9, 11, 30);

    sistema.reserve(req1);
    sistema.reserve(req2);
    sistema.reserve(req3);
    sistema.reserve(req4);
    sistema.reserve(req5);
    sistema.reserve(req6);

    std::cout << "Horario antes do cancelamento:" << std::endl;
    sistema.printSchedule();

    sistema.cancel("Fisica");

    std::cout << "Horario depois do cancelamento:" << std::endl;
    sistema.printSchedule();

}