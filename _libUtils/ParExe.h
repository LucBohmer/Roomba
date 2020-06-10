#ifndef PARWAIT_H
#define PARWAIT_H

#include <atomic>
//#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/// ParExe forks #command_ in a detached thread.
/// Redirects the output of #command_ to #output_.
/// Reeds maximal #MAX_LINES from output of executed command.
class ParExe
{
public:
   ParExe(const std::string &command,
          const std::string& args,
          const std::string& input = ""):
      command_{command},
      args_{args},
      input_{input},
      output_{},
      par_{&ParExe::execute, this}
   {
      par_.detach();
   }
   ParExe(const ParExe &other) = delete;
   ParExe& operator=(const ParExe &other) = delete;
   ~ParExe() = default;
   std::string output() const { return output_; }
private:
   static const int MAX_LINES_ = 20;
   std::string command_;
   std::string args_;
   std::string input_;
   std::string output_;
   std::thread par_;
   int fdX[2];

   void execute()
   {
      char *command = const_cast<char*>(command_.data());
      char *args = const_cast<char*>(args_.data());
      char *allArgs[]={command, args, NULL};

      if (pipe(fdX) == -1)
      {
         printf("Error: could not create pipe!\n");
         exit(0);
      }

      pid_t pid = fork();
      switch (pid)
      {
         case -1:
            perror("fork Python execution");
            break;
         case 0:
            // Child process
            dup2(fdX[1], STDOUT_FILENO);
            close(fdX[0]);
            close(fdX[1]);
            execvp(command, allArgs);
            perror("Python execution");
            break;
         default:
            // Parent process
            dup2(fdX[0], STDIN_FILENO);
            close(fdX[0]);
            close(fdX[1]);
            std::cerr << "Waiting\n";
            wait(NULL);
            std::cerr << "Ready waiting\n";

            std::string message;
            int countLines = 0;
            while(countLines < MAX_LINES_)
            {
               getline(std::cin, message);
               if (message == "PAREXE-READY") break;
               std::cerr << " Message = " << message << std::endl;
               output_ += message;
               ++countLines;
            }
            if (countLines >= MAX_LINES_)
            {
               std::cerr << "Ready reading, but MAX_LINES_ = "
                         << MAX_LINES_ << " exceeded\n";
            }
            else
            {
               std::cerr << "Ready reading\n";
            }
      }
   }
};

#endif
