#include "ReservationRequest.hpp"
#include <iostream> 

ReservationRequest::ReservationRequest(std::string nm_curso, std::string dia, int s_hr, int e_hr, int qtd_alunos){ 
    this->course_name = nm_curso;
    this->weekday = dia;
    this->start_hour = s_hr;
    this->end_hour = e_hr;
    this->student_count = qtd_alunos;
}
ReservationRequest::~ReservationRequest() = default;

int ReservationRequest::getStartHour() {
    return this->start_hour;
}
int ReservationRequest::getEndHour() {
    return this->end_hour;
}
std::string ReservationRequest::getCourseName() {
    return this->course_name;
}
std::string ReservationRequest::getWeekday() {
    return this->weekday;
}
int ReservationRequest::getStudentCount() {
    return this->student_count;
}




