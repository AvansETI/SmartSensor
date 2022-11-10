#include <boards/Board.h>
#include <util/Message.h>

class XBeeMessageDeliverer
{
private:
    /* data */
public:
    /**
     * @brief Adds a message to be sent over zigbee
     * 
     * @param message the message to send
     */
    virtual void addXBeeMessage(Message message) = 0;
};
