#ifndef SMART_SENSOR_IXBEEDATA_H
#define SMART_SENSOR_IXBEEDATA_H

#define PACKET_SIZE 255

class IXBeeData {
    public:
        /**
         * Returns the packet
         *
         * @return The generated packet as an char pointer (string)
         */
        virtual char* get_packet() = 0;
};

#endif