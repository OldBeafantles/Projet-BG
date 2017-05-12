#include "ELevelButton.h"

ELevelButton::ELevelButton(const QString & levelName) :
    QPushButton(levelName)
{

}

void ELevelButton::changeLevelName(const QString & levelName)
{
    setText(levelName);
}
