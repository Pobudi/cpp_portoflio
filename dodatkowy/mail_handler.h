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
    Poco::Net::POP3ClientSession pop3session = Poco::Net::POP3ClientSession("pop3.poczta.onet.pl");

    Poco::Net::POP3ClientSession::MessageInfoVec messages;
    std::multimap<std::string, std::vector<std::string>> queries;

public:
    // constructor loggs in to the session
    MailHandler(const char * userName, const char * password){
        pop3session.login( userName, password );
    }
    // destructor closes connection
    ~MailHandler(){
        pop3session.close();
    }
    // returns multimap that holds <sender, {subject, content}>
    auto get_queries(){
        return queries;
    }
    // updates messages
    void get_inbox(){
        pop3session.listMessages( messages );
    }
    // retrieves messages and prints them
    void print_inbox();

    // handles multipart messages
    std::string get_multipart(const Poco::Net::MailMessage & message)const;

    // sends mail
    int send_mail(const std::string& u_mail, const std::string& subject, const std::string& content);
};



#endif //DODATKOWY_MAIL_HANDLER_H
