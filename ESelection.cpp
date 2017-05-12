#include "ESelection.h"

ESelection::ESelection() :
    m_posValid      (false)
{
    //Should initially be calling setNoneValue()
    setValue(0);
}

ESelection::ESelection(int x, int y)
{
    setPosition(x, y);
    //Should initially be calling setNoneValue()
    setValue(0);
}

/*void ESelection::setNoneValue()
{
    m_value.object = nullptr;
    m_type = ESelectionType::NONE;
}*/

void ESelection::setValue(int n)
{
    m_value.integer = n;
    m_type = ESelection::INT;
}

/*void ESelection::setValue(BGObject *object)
{
    m_value.object = object;
    m_type = ESelectionType::SINGLE;
}*/

/*void ESelection::setValue(BGGroup *group)
{
    m_value.object = group;
    m_type = ESelectionType::GROUP;
}*/

void ESelection::setPosition(int x, int y)
{
    m_posValid = true;
    m_x = x;
    m_y = y;
}

void ESelection::setNoPosition()
{
    m_posValid = false;
}

bool ESelection::isPositionOk() const
{
    return m_posValid;
}

int ESelection::getX() const
{
    return m_x;
}

int ESelection::getY() const
{
    return m_y;
}

int ESelection::toInt() const
{
    if (m_type == ESelectionType::INT)
        return m_value.integer;
    //else péter un câble
    //Throw an exception here ?
    //For now, what it's doing is not logic.
    else
        return 0;
}
