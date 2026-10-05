#include "histogram.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

// These function prototypes / definitions are suggestions but not required to implement.
// hist_int_t get_max_count(void)
// void output_histogram(FILE* destination_stream)
// void usr1_handler/exit_handler/signal_handler(int signum)

// Note: It is bad practice to use STDIO in signal handlers. 
// For this assignment however, I am guaranteeing that multiple signals will **not** be sent at or near the same time, thus it is __okay__ to use STDIO in your signal handlers.
// That is to say, feel free to use printf, fprintf, etc. in your signal handlers.
// Challenge: For the astute, try to implement the histogram program where your signal handlers have only 1 line of code (setting a global variable/flag). Even better if you use sigaction instead of signal.


//setting the helper functions
hist_int_t get_max_count(void);
void output_histogram(FILE* destination_stream);
void usr1_handler(int signum);
void exit_handler(int signum);
void signal_handler(int signum);


//return the maximum value from histogram
hist_int_t get_max_count(void){
	hist_int_t max = 0;
	//loop for 256 due to the max length of the histogram
	for(int i = 0; i < 256; i++){
		//store a new value is current value is larger than previous stored
		if(histogram[i] > max){
			max = histogram[i];
		}
	}
	//return the find after the loop
	return max;
}

//return the output of the histogram
void output_histogram(FILE* destination_stream){
	//find the maximum in the histogram
	hist_int_t max = get_max_count();
	
	//loop the histogram to set how long are each value
	for(int i = 0; i < 256; i++){
		hist_int_t count = histogram[i];
		//print count and byte in hex
		fprintf(destination_stream, "%20llu 0x%02X |", count, i);
		
		//only for non-zero histogram value
		if(count > 0){
			int length = (int)((count * MAX_BAR_WIDTH) / max);
			//printing out # as the length
			for(int j = 0; j < length; j++){
				fputc('#', destination_stream);
			}
			//end with |
			fputc('|',destination_stream);
		}
		//move to the next line
		fputc('\n', destination_stream);	
	}
}

void usr1_handler(int signum){
	FILE *file = fopen("histo.out", "w");
	//if can't open file, stop the signal handler without terminate the program
	if(file == NULL){
		fprintf(stderr, "FAILED TO OPEN FILE");
		return; 
	}
	//write the histogram to the file
	output_histogram(file);
	//close the file
	fclose(file);
}

void exit_handler(int signum){
	FILE *file = fopen("histo.out", "w");
        //if can't open file, terminate the program
        if(file == NULL){
                fprintf(stderr, "FAILED TO OPEN FILE");
                //terminate the program
		exit(1);
        }
        //write the histogram to the file
        output_histogram(file);
        //close the file and exit the program
        fclose(file);
	exit(0);
}

//react on the program based on the user signal input
void signal_handler(int signum){
	//dump the histogram if call SIGUSR1
	if(signum == SIGUSR1){
		usr1_handler(signum);
	}
	//terminate the program if SIGINT or SIGTERM
	else if(signum == SIGINT || signum == SIGTERM){
		exit_handler(signum);
	}
}

int main(void) {
    // TODO: implement the histogram program
    int byte;
    signal(SIGUSR1, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    //keep reading the byte from stdin until EOF is called
    while((byte = fgetc(stdin)) != EOF){
	//byte only valid between 0 to 255
    	if(byte >= 0 && byte <= 255){
		//record the count of the byte	
		histogram[byte] += 1;
	}
    }
    //output the current histogram and end the program on EOF
    output_histogram(stdout);
    return 0;
}
