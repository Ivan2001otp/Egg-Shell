#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

std::string eggShellCout()
{
    std::string s;
    std::cout << "Egg-Shell > ";
    std::getline(std::cin, s);
    std::cout << "You typed : " << s << std::endl;
    return s;
}

std::vector<std::string> splitTokens(std::string s)
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

void processPipe(std::string s)
{
    size_t pipe_position = s.find("|");

    std::string str_left = s.substr(0, pipe_position);
    std::string str_right = s.substr(pipe_position + 1);
    std::vector<std::string> left_tokens = splitTokens(str_left);
    std::vector<std::string> right_tokens = splitTokens(str_right);

    
}

void processNonPipeCommands(std::string buffer)
{

    std::vector<std::string> tokens = splitTokens(buffer);

    std::vector<char *> argv;
    for (auto &it : tokens)
    {
        // store the mutable char pointer
        argv.push_back(&it[0]);
    }

    argv.push_back(NULL); // add null to terminate the execution of execvp systemcall

    // fork the process...
    pid_t pid = fork();

    if (pid == 0)
    {
        // child process.
        execvp(argv[0], argv.data());
        perror("exec failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        perror("fork failed !");
    }
    execvp(argv[0], argv.data());
}

int main()
{
    while (true)
    {
        std::string buffer = eggShellCout();
        if (buffer == "slurp")
        {
            break;
        }
        if (std::string::npos != buffer.find("|"))
        {
            processPipe(buffer);
            continue;
        }
        else
        {
            processNonPipeCommands(buffer);
        }
    }

    std::cout << "exited" << std::endl;
}