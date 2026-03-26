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

// Função auxiliar para ajudar na ordenação
int ReservationSystem::valorDoDia(std::string dia) {
    if (dia == "segunda") return 1;
    if (dia == "terca")   return 2;
    if (dia == "quarta")  return 3;
    if (dia == "quinta")  return 4;
    if (dia == "sexta")   return 5;
    return 6;
}

bool ReservationSystem::reserve(ReservationRequest request){
    for (int i = 0; i < room_count; i++){
        if (request.getStudentCount() <= room_capacities[i]){
            if (isAvailable(i, request.getWeekday(), request.getStartHour(), request.getEndHour())){
                // Criar uma possivel nova reserva
                ReservaNode* nova_reserva = new ReservaNode{request, nullptr};
                
                int dia_novo = valorDoDia(request.getWeekday());
                int hora_nova = request.getStartHour();

                ReservaNode* atual = this->room_schedules[i];
                ReservaNode* anterior = nullptr;

                while (atual != nullptr) {
                    int dia_atual = valorDoDia(atual->requisicao.getWeekday());
                    int hora_atual = atual->requisicao.getStartHour();

                    // A regra de ordenação:
                    // Se o dia do novo for menor, OU (se for no mesmo dia E a hora for menor)...
                    if (dia_novo < dia_atual || (dia_novo == dia_atual && hora_nova < hora_atual)) {
                        break; // achamos o lugar, o loop para aqui.
                    }
            
                    // Continua andando
                    anterior = atual;
                    atual = atual->proximo;
                }

        //caso 1: A reserva entra no comeco
        if (anterior == nullptr) {
            nova_reserva->proximo = this->room_schedules[i];
            this->room_schedules[i] = nova_reserva;
        } 
        // caso 2: A reserva entra no meio ou lá no final
        else {
            nova_reserva->proximo = atual;
            anterior->proximo = nova_reserva;
        }

        return true; // Reserva feita e ja ordenada
            }
        }
    }
    return false; // Não foi possível fazer a reserva

}

bool ReservationSystem::cancel(std::string course_name){
    for (int i = 0; i < room_count; i++){
        ReservaNode* atual = room_schedules[i];
        ReservaNode* anterior = nullptr;

        while(atual != nullptr){
            if (atual->requisicao.getCourseName() == course_name){
                // Encontramos a reserva a ser cancelada
                if (anterior == nullptr) {
                    // A reserva a ser cancelada é a primeira da lista
                    room_schedules[i] = atual->proximo;
                } else {
                    // A reserva a ser cancelada está no meio ou no final da lista
                    anterior->proximo = atual->proximo;
                }
                delete atual; // Libera a memória da reserva cancelada
                return true; // Cancelamento bem-sucedido
            }
            anterior = atual;
            atual = atual->proximo; // Pula para a próxima reserva
        }
    return false; // Não foi possível encontrar a reserva para cancelar
    }

}

void ReservationSystem::printSchedule(){
    for (int i = 0; i < room_count; i++){
        std::cout << "Sala " << i << std::endl;
        int contador = 0;
        ReservaNode* atual = this->room_schedules[0]; 

    // percorremos de reserva em reserva
        while (atual != nullptr) {
            contador++;
            atual = atual->proximo; // vai para a proxima reserva
        }
            
    }

}



