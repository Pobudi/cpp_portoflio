# Chat with ChatGPT via mail

## This project allows to chat and generate images by sending mails to a specified host. Examples:

#### By writing "Image" as the subject of the mail:
![image](https://user-images.githubusercontent.com/92460956/234002256-7f4e586c-0d18-4400-88a6-006f6cd27fde.png)

#### Answer (link to the image will be sent in a mail from the host):
![image](https://user-images.githubusercontent.com/92460956/233999042-60ac6b84-c2a0-49ba-9a9b-315e766c897a.png)

#### For every other subject a text based answer will be generated:
![image](https://user-images.githubusercontent.com/92460956/234002334-d7c165ed-7eb6-4146-a290-e81033f304f8.png)

#### Answer:
![image](https://user-images.githubusercontent.com/92460956/234002087-587b9e03-6d55-484a-aba1-606a94368d20.png)


### Requirements if someone would like to try it out. Project is not live right now as every query sent to the host costs openai tokens.

* libcurl
* Poco::Net
* openai library (https://github.com/olrea/openai-cpp)
* And also a premium account on Openai (https://openai.com/pricing)
* An email account to become host. It has to be from email provider that allows smtp and pop3 protocol. (will not work on gmail)
 After cloning this repository remember to insert your credentials where it is needed (look for getenv() or std::getenv()). 


