#include "BGException.h"
#include <ctime>
#include <iostream>
#include <ctime>

BGException::BGException(int _errorNumber, std::string _description)
{
    m_errorNumber = _errorNumber;
    struct tm timeinfo;
    time_t date = time(NULL);
    localtime_s(&timeinfo, &date);
    strftime(m_date, 18, "%d-%m-%Y %Hh-%Mm", &timeinfo);
    puts(m_date);
    m_description = _description;
}

const char* BGException::what() const throw()
{
    return ("Erreur n°" + std::to_string(m_errorNumber) + ", le " + std::string(m_date) + " : " + m_description).c_str();
    //Rajouter une boîte de dialogue pour prévenir l'utilisateur de l'erreur
}

BGException::~BGException() throw()
{}
