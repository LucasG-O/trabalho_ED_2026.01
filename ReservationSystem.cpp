#include "ReservationSystem.hpp"
#include <iostream>

ReservationSystem::ReservationSystem(int qtd_salas, int* capacidade_salas) {
    this->qtd_salas = qtd_salas;
    this->capacidade_salas = new int[qtd_salas];
    for (int i = 0; i < qtd_salas; i++) {
        this->capacidade_salas[i] = capacidade_salas[i];
    }
    this->reservas_salas = new ReservaNode*[qtd_salas];
    for (int i = 0; i < qtd_salas; i++) {
        this->reservas_salas[i] = nullptr; 
    }

}

// Essa função confere se a sala está livre naquele dia e horário
bool ReservationSystem::isAvailable(int sala_idx, std::string weekday, int start_hour, int end_hour) {
    
    // Pega a primeira reserva da sala que queremos testar
    ReservaNode* atual = this->reservas_salas[sala_idx];


    // Olhamos todas as reservas da sala, uma por uma, para ver se alguma bate com o horário que queremos
    while (atual != nullptr) {
        
        // Só importa se for no mesmo dia da semana
        if (atual->reserva.getWeekday() == weekday) {
            
            int inicio_existente = atual->reserva.getStartHour();
            int fim_existente = atual->reserva.getEndHour();
            
            // Confere se o horário que queremos reservar bate com o horário da reserva atual.

        }
        
        atual = atual->proximo; // Pula para a proxima reserva
    }
    
    // Se o while rodou inteiro e não bateu com nenhum horário, a sala está livre!
    return true; 
}

// Função auxiliar para ajudar na ordenação
int ReservationSystem::Dia_to_Num(std::string dia) {
    if (dia == "segunda") return 1;
    else if (dia == "terca")   return 2;
    else if (dia == "quarta")  return 3;
    else if (dia == "quinta")  return 4;
    else if (dia == "sexta")   return 5;
    return 0; // dia inválido
}

bool ReservationSystem::reserve(ReservationRequest request){
    if (request.getStartHour() >= request.getEndHour()) {
        std::cout << " Reserva do curso " << request.getCourseName() << " nao foi possivel por apresentar horario invalido" << std::endl;
        return false; // Horário inválido
    }
    for (int i = 0; i < qtd_salas; i++){
        if (request.getStudentCount() <= capacidade_salas[i]){
            if (isAvailable(i, request.getWeekday(), request.getStartHour(), request.getEndHour())){
                // Criar uma possivel nova reserva
                ReservaNode* nova_reserva = new ReservaNode{request, nullptr};
                
                int dia_novo = Dia_to_Num(request.getWeekday());
                int hora_nova = request.getStartHour();

                ReservaNode* atual = this->reservas_salas[i];
                ReservaNode* anterior = nullptr;

                while (atual != nullptr) {
                    int dia_atual = Dia_to_Num(atual->reserva.getWeekday());
                    int hora_atual = atual->reserva.getStartHour();

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
            nova_reserva->proximo = this->reservas_salas[i];
            this->reservas_salas[i] = nova_reserva;
        } 
        // caso 2: A reserva entra no meio ou no fim
        else {
            nova_reserva->proximo = atual;
            anterior->proximo = nova_reserva;
        }

        return true; // Reserva feita e ja ordenada
            }
        }
    }
    
        std::cout << " Reserva do curso " << request.getCourseName() 
                    << " nao foi possivel pois nao foi encontrada sala com capacidade suficiente" 
                    << std::endl;

    return false; // Não foi possível fazer a reserva

}

bool ReservationSystem::cancel(std::string course_name){
    for (int i = 0; i < qtd_salas; i++){
        ReservaNode* atual = reservas_salas[i];
        ReservaNode* anterior = nullptr;

        while(atual != nullptr){
            if (atual->reserva.getCourseName() == course_name){
                // Encontramos a reserva a ser cancelada
                if (anterior == nullptr) {
                    // A reserva a ser cancelada é a primeira da lista
                    reservas_salas[i] = atual->proximo;
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
    }
    return false; // Não foi possível encontrar a reserva para cancelar
}

void ReservationSystem::printSchedule(){
    // percorremos de sala em sala
    for (int i = 0; i < qtd_salas; i++){
        std::cout << "Sala " << i << "\n" <<std::endl;

        ReservaNode* atual = this->reservas_salas[i]; 
        if (atual != nullptr){
            std::cout << atual->reserva.getWeekday() << ": " << std::endl;
        }
        // percorremos de reserva em reserva
        while (atual != nullptr) {

            std::cout <<"    " << atual->reserva.getStartHour() << "h~" 
            << atual->reserva.getEndHour() << "h: " 
            << atual->reserva.getCourseName() << std::endl; 
            

            if (atual->proximo != nullptr){
                std::string dia_atual = atual->reserva.getWeekday();
                std::string dia_proximo = atual->proximo->reserva.getWeekday(); 
                if (dia_atual != dia_proximo) {
                    std::cout << std::endl;
                    std::cout << dia_proximo << ": " << std::endl;
        
            }
            }
            
           
            atual = atual->proximo; // vai para a proxima reserva

        }
        std::cout << std::endl;
    }

}