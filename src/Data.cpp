#include "Data.h"


Data::Data(MessageType type, Direction dir, int snakeIndex, std::pair<int, int> cor) 
{
    m_type = type;
    m_direction = dir;
    m_snakeIndex = snakeIndex;
    m_snakeCoordinates = cor;
}

Data::Data(MessageType type, Direction dir) 
{
    m_type = type;
    m_direction = dir;
}

Data::Data(MessageType type, std::pair<int, int> cor, int appleIndex) 
{
    m_type = type;
    m_appleCord = cor;
    m_appleIndex = appleIndex;
}
