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
    std::multimap<std::string, std::string> queries;

public:
    // constructor loggs in to the session
    MailHandler(const char * userName, const char * password){
        pop3session.login( userName, password );
//        smtpsession.login(Poco::Net::SMTPClientSession::AUTH_PLAIN, userName, password);
    }
    // destructor cleses connection
    ~MailHandler(){
        pop3session.close();
    }
    auto get_queries(){
        return queries;
    }
    // updates messages
    void get_inbox(){
        pop3session.listMessages( messages );
    }
    //retrieves messages and prints them
    void print_inbox(){
        for (auto& i:messages){
            const Poco::Net::POP3ClientSession::MessageInfo & currentMessage=i;
            Poco::Net::MailMessage message;
            pop3session.retrieveMessage(currentMessage.id, message);
            //parsing so that only mail address will be left
            std::string s_mail;
            s_mail = message.getSender();
            auto where_del = s_mail.find('<');
            s_mail = s_mail.substr(where_del+1, s_mail.length() - where_del-2);
            queries.insert({s_mail, message.getSubject()});
//            session.deleteMessage(currentMessage.id);
        }
        messages.erase(messages.begin(), messages.end());
    }
//
    static auto send_mail(const std::string& u_mail, const std::string& subject, const std::string& content){
        //creating message
        Poco::Net::MailMessage msg;
        Poco::Net::MailRecipient rec(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, u_mail);
        msg.setRecipients({rec});
        msg.setSender(std::getenv("email_bot"));
        msg.setSubject(subject);
        msg.setContent(content);
        // creating smtp session, logging in, sending message
        try {
            Poco::Net::SMTPClientSession smtpsession("smtp.poczta.onet.pl", 587);
            smtpsession.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, std::getenv("email_bot"),
                              std::getenv("pass_bot"));
            smtpsession.sendMessage(msg);
        }
        catch(Poco::Exception& e) {
            std::cout << "Error: " << e.displayText() << std::endl;
            return -1;
        }
        return 0;
    }

    static void print( const Poco::Net::MailMessage & message ){
        time_t receivedTime = message.getDate().epochTime();
        std::cout << "date:    " << ctime( & receivedTime ) << std::endl;
        std::cout << "subject: " << message.getSubject() << std::endl;
        std::cout << "sender:  " << message.getSender() << std::endl;
    }

};



#endif //DODATKOWY_MAIL_HANDLER_H
