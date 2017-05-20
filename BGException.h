#ifndef BG_EXCEPTION_H
#define BG_EXCEPTION_H

#include <exception>
#include <ctime>
#include <string>

class BGException : public std::exception
{
private:
    int m_errorNumber;
    std::string m_description;
    char m_date[30];

public:
    BGException(int = -1, std::string = "Erreur inconnue !");
    virtual const char* what() const throw();
    virtual ~BGException() throw(); //Ne sert pas à grand chose ici pour l'instant mais à ne pas oublier si l'on est amenés à utiliser des pointeurs
};


#endif
