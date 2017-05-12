#ifndef ESELECTION_H
#define ESELECTION_H


class ESelection
{
public :

    ESelection();
    ESelection(int x, int y);

    enum ESelectionType : long int
    {
        NONE = 0,
        INT = 1,

        //Are the following ones really relevant ? Is BGOBJECT not enough to handle all cases ?
        GROUP = 2,
        SINGLE = 4,
        BGOBJECT = GROUP | SINGLE
    };

    //There should also be two methods for one setter for one particular type, to initialize position directly.
    //The idea is getting a correct initialization in one call, to avoid errors as much as possible.
    //void setNoneValue();
    void setValue(int n);
    //void setValue(BGObject *object);
    //Will this work ? Lulz
    //void setValue(BGGroup *group);
    //If the pointer is null, then set the value to NONE

    //Position setters and getters
    void setPosition(int x, int y);
    void setNoPosition();
    bool isPositionOk() const;
    int getX() const;
    int getY() const;


    int toInt() const;
    //BGObject* toBGObject() const;
    //BGGroup* toBGGroup() const;

private :

    union ESelectionUnion
    {
        int integer;
        //BGObject *object;
        //BGGroup *group;
    };

    ESelectionUnion m_value;
    ESelectionType m_type;

    //Maybe this will change after. What about giving also a QWidget pointer, so you can know the exact location of selection ?
    bool m_posValid; //A boolean that is used to know if position attributes aren't invalid, because not initialized. Maybe not relevant.
    int m_x;
    int m_y;
};

#endif // ESELECTION_H
