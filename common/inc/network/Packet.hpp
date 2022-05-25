/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <vector>
#include <cstring>
#include <memory>
#include <iostream>
#include <iomanip>

class AClient;

template <typename T_Protocol>
struct PacketHeader {
    T_Protocol id{};
    uint32_t size = 0;
};

template <typename T_Protocol>
class Packet {
public:
    Packet(void) = default;
    Packet(const T_Protocol &id)
    {
        m_header.id = id;
    }
    Packet(const Packet<T_Protocol> &other)
    {
        m_header = other.m_header;
        m_body = other.m_body;
        m_client = other.m_client;
        m_isFromDisconnect = other.m_isFromDisconnect;
    }
    Packet &operator=(const Packet<T_Protocol> &other)
    {
        m_header = other.m_header;
        m_body = other.m_body;
        m_client = other.m_client;
        m_isFromDisconnect = other.m_isFromDisconnect;
        return *this;
    }

    void reset(void)
    {
        m_header.id = {};
        m_header.size = 0;
        this->clear();
    }

    void clear(void)
    {
        m_body.clear();
        m_header.size = 0;
    }

    void resizeBody(const size_t &newSize)
    {
        m_body.resize(newSize);
        m_header.size = static_cast<uint32_t>(newSize);
    }

    char *getContent(void)
    {
        char *content = (char *)malloc(sizeof(getTotalSize()));

        if (content == nullptr) {
            return nullptr;
        }
        std::memset(content, 0, getTotalSize());
        std::memcpy(content, &m_header, getHeaderSize());
        std::memcpy(content + getHeaderSize(), m_body.data(), getBodySize());
        return content;
    }

    const char *getContent(void) const
    {
        char *content = (char *)malloc(sizeof(getTotalSize()));

        if (content == nullptr) {
            return nullptr;
        }
        std::memset(content, 0, getTotalSize());
        std::memcpy(content, &m_header, getHeaderSize());
        std::memcpy(content + getHeaderSize(), m_body.data(), getBodySize());
        return content;
    }

    void setContent(char *content)
    {
        std::memcpy(&m_header, content, getHeaderSize());
        size_t newBodySize = getExpectedBodySize();
        m_body.resize(newBodySize);
        std::memcpy(m_body.data(), content + getHeaderSize(), newBodySize);
    }

    struct PacketHeader<T_Protocol> &getHeader(void)
    {
        return m_header;
    }

    const struct PacketHeader<T_Protocol> &getHeader(void) const
    {
        return m_header;
    }

    // Returns the fixed size of the struct header
    size_t getHeaderSize(void) const
    {
        return sizeof(m_header.id) + sizeof(m_header.size);
    }

    // Returns the size of the body to read
    uint32_t getExpectedBodySize(void) const
    {
        return m_header.size;
    }

    size_t getBodySize(void) const
    {
        return m_body.size();
    }

    size_t getTotalSize(void) const
    {
        return getHeaderSize() + getBodySize();
    }

    std::vector<uint8_t> &getBody(void)
    {
        return m_body;
    }

    const std::vector<uint8_t> &getBody(void) const
    {
        return m_body;
    }

    std::shared_ptr<AClient> getClient(void) const
    {
        return m_client;
    }

    T_Protocol getId(void) const
    {
        return m_header.id;
    }

    void setId(const T_Protocol &id)
    {
        m_header.id = id;
    }

    void setId(const int &id)
    {
        m_header.id = static_cast<T_Protocol>(id);
    }

    void setExpectedBodySize(const uint32_t size)
    {
        m_header.size = size;
    }

    void setClient(std::shared_ptr<AClient> client)
    {
        m_client = client;
    }

    // Returns true if the packet signals a disconnection, false otherwise
    bool isFromDisconnect(void) const
    {
        return m_isFromDisconnect;
    }

    void setIsFromDisconnect(bool isFromDisconnect)
    {
        m_isFromDisconnect = isFromDisconnect;
    }

private:
    struct PacketHeader<T_Protocol> m_header{};
    std::vector<uint8_t> m_body;
    std::shared_ptr<AClient> m_client = nullptr;
    bool m_isFromDisconnect = false;

public:
    friend std::ostream& operator << (std::ostream& os, const Packet<T_Protocol>& msg) {
        std::ios_base::fmtflags f(std::cout.flags());
        os << "Header : "
            << "ID:" << int(msg.getId())
            << ", size:" << msg.getExpectedBodySize() << std::endl
            << "Body : [";
        for (const uint8_t byte : msg.getBody()) {
            os << '\\' << std::hex << std::showbase << int(byte);
        }
        os << "]";
        std::cout.flags(f);
        return os;
    }

    template<typename DataType>
    friend Packet<T_Protocol> &operator<<(Packet<T_Protocol> &msg, const DataType &data)
    {
        static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");
        size_t i = msg.getBodySize();
        msg.resizeBody(i + sizeof(DataType));
        std::memcpy(msg.getBody().data() + i, &data, sizeof(DataType));
        return msg;
    }

    friend Packet<T_Protocol> &operator <<(Packet<T_Protocol> &msg, const bool &isTrue)
    {
        msg.m_body.push_back(static_cast<uint8_t>(isTrue));
        msg.m_header.size += 1;
        return msg;
    }

    template<typename DataType>
    friend Packet<T_Protocol>& operator >> (Packet<T_Protocol>& msg, DataType& data)
    {
        static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");
        size_t i = msg.getBodySize() - sizeof(DataType);
        std::memcpy(&data, msg.getBody().data() + i, sizeof(DataType));
        msg.resizeBody(i);
        return msg;
    }

    friend Packet<T_Protocol> &operator >>(Packet<T_Protocol> &msg, bool &isTrue)
    {
        if (msg.getBody()[msg.getBodySize() - 1] == 1) {
            isTrue = true;
        } else {
            isTrue = false;
        }
        msg.resizeBody(msg.getBodySize() - 1);
        return msg;
    }
};

#endif /* !PACKET_HPP_ */
