//
// Created by bartosz on 28.03.23.
//

#include "mail_handler.h"

#include "Poco/Net/POP3ClientSession.h"
#include "Poco/Net/MailMessage.h"

void MailHandler::print_inbox() {
    for (auto& i:messages){
        std::string content;
        const Poco::Net::POP3ClientSession::MessageInfo & currentMessage=i;
        Poco::Net::MailMessage message;
        pop3session.retrieveMessage(currentMessage.id, message);
        //parsing so that only mail address will be left
        std::string s_mail;
        s_mail = message.getSender();
        auto where_del = s_mail.find('<');
        s_mail = s_mail.substr(where_del+1, s_mail.length() - where_del-2);

        if (message.isMultipart()) content = get_multipart(message);
        else content = message.getContent();

        queries.insert({s_mail, {message.getSubject(), content}});
       pop3session.deleteMessage(currentMessage.id);
    }
    messages.erase(messages.begin(), messages.end());
}

std::string MailHandler::get_multipart(const Poco::Net::MailMessage &message) const {
    const Poco::Net::MailMessage::PartVec & parts = message.parts();
    std::string content;
    const Poco::Net::MailMessage::Part p = parts[0];
    std::istream& m = p.pSource->stream();
    getline(m, content);
    return content;
}


int MailHandler::send_mail(const std::string &u_mail, const std::string &subject, const std::string &content) {
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
