// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NTHREADS 64

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int colors[64][64*3];
int counter = 0;

void save(){
FILE *fp;
	fp = fopen("threads.ppm","w+");
	fputs("P3\n",fp);
	fputs("64 64\n",fp);
	fputs("255\n",fp);
	int i;
	int j;
	for(i =0; i < 64;i++){
		for(j =0; j < 64*3; j++){
			fprintf(fp,"%d",colors[i][j]);
			fputs(" ",fp);		
		}
		fputs("\n",fp);
	}
	fclose(fp);
}




// Paint function called from each child
void paint(int workID){
   
        printf("Artist %d is painting\n",workID);
        int newColor = 0;
	// workID corresponds to the 'artist'
	// Each artist owns one row to paint on.
	// An artist paints along each pixel 1 at a time, painting an
	// R,G,B value (that is why it is 64*3)
	int i;
        for( i =0; i < 64*3; i++){
                colors[workID][i] = workID * i; // Try doing something more interesting with the colors!
        }

}

void *thread(void *varg){
    pthread_mutex_lock(&mutex1);
    paint(counter);
    ++counter;
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

int main() {
    //Store Pthread ID
    pthread_t tids[NTHREADS];

    //Create and execute multiple threads
    int i;
    for ( i =0;i< NTHREADS;++i) {
        pthread_create(&tids[i], NULL, thread, NULL);
    }
	
    int j;	
    for (j =0;j<NTHREADS;++j) {
        pthread_join(tids[j],NULL);
    }
    save();
    return 0;
}
