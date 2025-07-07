#include <bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>


std::string eggShellCout()
{
    std::string s;
    std::cout << "Egg-Shell > ";
    std::getline(std::cin, s);
    std::cout << "You typed : " << s << std::endl;
    return s;
}

std::vector<std::string> splitCmdToTokens(std::string s)
{
    std::vector<std::string> tokens;

    std::stringstream ss(s);
    std::string t;
    while (getline(ss, t, ' '))
    {
        tokens.push_back(t);
    }

    return tokens;
}

int main()
{
    std::string buffer = eggShellCout();
    while(buffer != "slurp") {
        std::vector<std::string>tokens = splitCmdToTokens(buffer);

        std::vector<char*> argv;
        for(auto &it : tokens) {
            // store the mutable char pointer
            argv.push_back(&it[0]);
        }

        argv.push_back(NULL);// add null to terminate the execution of execvp systemcall
        

        // fork the process...
        pid_t pid = fork();

        if (pid==0) {
            // child process.
            execvp(argv[0], argv.data());
            perror("exec failed");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("fork failed !");
        }
        execvp(argv[0], argv.data());
    }
    
    cout<<"exited"<<endl;
}