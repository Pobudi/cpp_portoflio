//////https://tsartsaris.gr/wp/cmake-clion-and-poco-on-linux/
////https://tsartsaris.gr/wp/installing-poco-cpp-on-linux/

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/AcceptCertificateHandler.h>

#include "Poco/Net/POP3ClientSession.h"
#include "Poco/Net/MailMessage.h"
#include "mail_handler.h"
#include "Poco/Util/Application.h"
#include "Poco/Net/SecureSMTPClientSession.h"

using namespace std;
using namespace Poco::Net;

auto delete_m(){
    MailHandler inbox;
    inbox.scan_inbox();
    return inbox.get_queries();
}

auto send_mail(const string& user, const string& subject, const string& content){
    MailHandler mail;
    mail.send_mail(user, subject, content);
}


int main(){
    while (true){
        auto m = delete_m();
        for (auto& i:m) {
            send_mail(i.first, i.second, "jakies dane");
            sleep(10);
        }
    }
    return 0;
}



