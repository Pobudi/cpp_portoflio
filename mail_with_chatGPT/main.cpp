//////https://tsartsaris.gr/wp/cmake-clion-and-poco-on-linux/
////https://tsartsaris.gr/wp/installing-poco-cpp-on-linux/

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include "mail_handler.h"
#include "Poco/Util/Application.h"
#include "openai/openai.hpp"
#include "openai/nlohmann/json.hpp"

using namespace std;
using namespace Poco::Net;

auto delete_m(){
    MailHandler inbox(getenv("email_bot"),getenv("pass_bot"));
    inbox.get_inbox();
    inbox.print_inbox();
    return inbox.get_queries();
}

auto send_mail(string user, string subject, string content){
    MailHandler mail(getenv("email_bot"), getenv("pass_bot"));
    mail.send_mail(user, subject, content);
}

auto get_data(string& type, string& prompt){
    openai::start(getenv("openai_key"));
    string content;
    if (type == "Obraz" || type == "obraz"){
        auto image = openai::image().create({
            {"prompt", prompt},
            {"n", 1},
            {"size", "512x512"}
        });
        std::cout<<image["data"][0]["url"]<<std::endl;
        content = image["data"][0]["url"];
    }
    else {
        auto completion = openai::completion().create({
          {"model",       "text-davinci-003"},
          {"prompt",      prompt},
          {"max_tokens",  20},
          {"temperature", 0.5},
        });
        std::cout << "Response is:\n" << completion["choices"][0] << '\n';
        std::cout<<completion["choices"][0]["text"];
        content = completion["choices"][0]["text"];
    }
    return content;
}

int main(){
    while (true){
        auto m = delete_m();
        for (auto& i:m) {
            string subject = i.second[0];
            string prompt = i.second[1];
            send_mail(i.first, subject, get_data(i.second[0], i.second[1]));
            sleep(10);
        }
    }
    return 0;
}