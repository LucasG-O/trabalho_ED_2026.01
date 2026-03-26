#include "ReservationSystem.hpp"
#include <iostream>

ReservationSystem::ReservationSystem(int room_count, int* room_capacities) {
    this->room_count = room_count;
    this->room_capacities = new int[room_count];
    for (int i = 0; i < room_count; i++) {
        this->room_capacities[i] = room_capacities[i];
    }
    this->room_schedules = new ReservaNode*[room_count];
    for (int i = 0; i < room_count; i++) {
        this->room_schedules[i] = nullptr; 
    }

}

// Essa função confere se a sala está livre naquele dia e horário
bool ReservationSystem::isAvailable(int room_index, std::string weekday, int start_hour, int end_hour) {
    
    // Pega a primeira reserva da sala que queremos testar
    ReservaNode* atual = this->room_schedules[room_index];
    
    // Olhamos todas as reservas da sala, uma por uma, para ver se alguma bate com o horário que queremos
    while (atual != nullptr) {
        
        // Só importa se for no mesmo dia da semana
        if (atual->requisicao.getWeekday() == weekday) {
            
            int inicio_existente = atual->requisicao.getStartHour();
            int fim_existente = atual->requisicao.getEndHour();
            
            // Confere se o horário que queremos reservar bate com o horário da reserva atual.
            if (start_hour < fim_existente && end_hour > inicio_existente) {
                return false;
            }
        }
        
        atual = atual->proximo; // Pula para a proxima reserva
    }
    
    // Se o while rodou inteiro e não bateu com nenhum horário, a sala está livre!
    return true; 
}

bool ReservationSystem::reserve(ReservationRequest request){
    for (int i = 0; i < room_count; i++){
        if (request.getStudentCount() <= room_capacities[i]){
            if (isAvailable(i, request.getWeekday(), request.getStartHour(), request.getEndHour())){
                // Criar uma possivel nova reserva
                ReservaNode* nova_reserva = new ReservaNode{request, nullptr};
                
                // Inserir no início da lista de reservas da sala
                nova_reserva->proximo = room_schedules[i];
                room_schedules[i] = nova_reserva;
                
                return true; // Reserva feita com sucesso
            }
        }
    }
    return false; // Não foi possível fazer a reserva

}

bool ReservationSystem::cancel(std::string course_name){


}

void ReservationSystem::printSchedule(){


}



