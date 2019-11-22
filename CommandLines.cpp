#include "CommandLines.h"
#include <stdlib.h>
#include <stdio.h>
#include "ketopt.h"
#include <sys/time.h>


char* read_file_name = NULL;
char* output_file_name = NULL;
int thread_num = 1;
int k_mer_length = 40;
int coverage = -1;
//int k_mer_min_freq = 9;
int k_mer_min_freq = 3;
//int k_mer_min_freq = 2;
int k_mer_max_freq = 66;
int load_index_from_disk = 0;
int write_index_to_disk = 0;
int number_of_round = 1;
int read_graph = 0;
int c_round = 4;
int adapterLen = 0;
char* required_read_name = NULL;

double Get_T(void)
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec+t.tv_usec/1000000.0;
}

void Print_H()
{
    fprintf(stderr, "Incorrect options.\n");
    fprintf(stderr, "./ccs_assembly -w -l -q NA12878_chr1_10M.fq -o output_NA12878_v11_2.fa -c 31 -k 40 -t 32 -r 2 -a 4 -z 0\n");
    
}




int CommandLine_process (int argc, char *argv[])
{

    static ko_longopt_t longopts[] = {
        { "help", ko_no_argument,  100},
        { "seq", ko_required_argument, 101},
        { "output", ko_required_argument, 102},
        { "thread", ko_required_argument, 103},
        { "k_mer_min_freq", ko_required_argument, 104},
        { "k_mer_max_freq", ko_required_argument, 105},
        { "round", ko_required_argument, 106},
        { NULL, 0, 0 }
    };

    ketopt_t opt = KETOPT_INIT;

    int i, c;
    while ((c = ketopt(&opt, argc, argv, 1, "ht:o:q:k:lwm:n:r:c:a:b:z:", longopts)) >= 0) {
        if (c == 100 || c == 'h') Print_H();
        else if (c == 103 || c == 't') thread_num = atoi(opt.arg); 
        else if (c == 102 || c == 'o') output_file_name = opt.arg;
        else if (c == 101 || c == 'q') read_file_name = opt.arg;
        else if (c == 104 || c == 'n') k_mer_min_freq = atoi(opt.arg);
        else if (c == 105 || c == 'm') k_mer_max_freq = atoi(opt.arg);
        else if (c == 106 || c == 'r') number_of_round = atoi(opt.arg);
        else if (c == 'k') k_mer_length = atoi(opt.arg); 
        else if (c == 'l') load_index_from_disk = 1; 
        else if (c == 'w') write_index_to_disk = 1; 
        else if (c == 'c') coverage = atoi(opt.arg);
        else if (c == 'a') c_round = atoi(opt.arg);
        else if (c == 'z') adapterLen = atoi(opt.arg);
        else if (c == 'b') required_read_name = opt.arg;
        else if (c == '?') printf("unknown opt: -%c\n", opt.opt? opt.opt : ':');
        else if (c == ':') printf("missing arg: -%c\n", opt.opt? opt.opt : ':');
    }


    if (argc == 1)
    {
        Print_H();
        return 0;
    }

    if(coverage == -1)
    {
        fprintf(stdout, "Please set -c!\n");
        Print_H();
        return 0;
    }


    return 1;
}