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

std::vector<char *> convertToMutableCharPointer(std::vector<std::string> tokens)
{
    std::vector<char *> argv;
    for (auto &it : tokens)
    {
        // store the mutable char pointer
        argv.push_back(&it[0]);
    }

    argv.push_back(NULL);

    return argv;
}

std::vector<std::string> splitTokens(std::string s)
{
    std::vector<std::string> tokens;

    std::stringstream ss(s);
    std::string t;
    while (ss >> t)
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

    
    // create pipe
    int pipeline[2]; // 0th for read end, 1st for write-end
    if (pipe(pipeline) == -1)
    {
        perror("pipe creation failed");
        return;
    }

    // create the fork for producer
    size_t pid1 = fork();
    if (pid1 == 0)
    {

        // direct the output to pipe's write-end.
        dup2(pipeline[1], STDOUT_FILENO);

        // after connecting pipes ,close the pipes.
        close(pipeline[0]);
        close(pipeline[1]);

        std::vector<char *> argv = convertToMutableCharPointer(left_tokens);
        execvp(argv[0], argv.data());

        perror("could not execute left cmd");
        exit(1);
    }

    // second fork for consumer process
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        dup2(pipeline[0], STDIN_FILENO);
        close(pipeline[1]);
        close(pipeline[0]);

        std::vector<char *> argv = convertToMutableCharPointer(right_tokens);
        execvp(argv[0], argv.data());

        perror("execvp failed for right-cmd");
        exit(1);
    }

    close(pipeline[0]);
    close(pipeline[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void processNonPipeCommands(std::string buffer)
{

    std::vector<std::string> tokens = splitTokens(buffer);

    std::vector<char *> argv = convertToMutableCharPointer(tokens);

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
        // parent process waits for child to finish its task.
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