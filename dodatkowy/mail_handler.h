//
// Created by bartosz on 28.03.23.
//

#ifndef DODATKOWY_MAIL_HANDLER_H
#define DODATKOWY_MAIL_HANDLER_H

#include "Poco/Net/POP3ClientSession.h"
#include "Poco/Net/MailMessage.h"
#include <map>
#include <string>
#include <Poco/Net/SMTPClientSession.h>


class MailHandler{
private:
    Poco::Net::POP3ClientSession::MessageInfoVec messages;
    std::multimap<std::string, std::string> queries;

public:
    auto get_queries(){
        return queries;
    }
    ////retrieves messages and prints them
    void scan_inbox();
    ////sends mails
    static int send_mail(const std::string& u_mail, const std::string& subject, const std::string& content);

    static void print( const Poco::Net::MailMessage & message ){
        time_t receivedTime = message.getDate().epochTime();
        std::cout << "date:    " << ctime( & receivedTime ) << std::endl;
        std::cout << "subject: " << message.getSubject() << std::endl;
        std::cout << "sender:  " << message.getSender() << std::endl;
    }

};



#endif //DODATKOWY_MAIL_HANDLER_H
