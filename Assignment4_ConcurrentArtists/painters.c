

// ===================== Include Libraries =====================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
// ===================== Setup our Canvas =====================
#define CANVAS_WIDTH 256
#define CANVAS_HEIGHT 256

typedef struct pixel{
    int r,g,b;
    pthread_mutex_t lock;
}pixel_t;

pixel_t canvas[CANVAS_WIDTH][CANVAS_HEIGHT];

typedef struct artist{
    int x,y;    // Store the position of where an artist is painting
    int r,g,b;    // The color an artist paints in.
}artist_t;

const int moves = 8;
const int movement[][2] ={
    {-1, 0}, // to the left
    {-1, 1}, // to the left and down
    {0, 1}, // down
    {1, 1}, // to the right and down
    {1, 0}, // to the right
    {1, -1}, // to the right and up
    {0, -1}, // up
    {-1, -1} // to the left and up
};


void initCanvas(){
    for(int x =0; x < CANVAS_WIDTH; ++x){
        for(int y =0; y < CANVAS_HEIGHT; ++y){
            canvas[x][y].r = 255;
            canvas[x][y].g = 255;
            canvas[x][y].b = 255;
            pthread_mutex_init(&canvas[x][y].lock, NULL);
        }
    }
}


void save(){
    FILE *fp;
    fp = fopen("./canvas.ppm","w+");
    fputs("P3\n",fp);
    fputs("256 256\n",fp);
    fputs("255\n",fp);
    for(int x =0; x < CANVAS_WIDTH; ++x){
        for(int y =0; y < CANVAS_HEIGHT; ++y){
            fprintf(fp,"%d",canvas[x][y].r);
            fputs(" ",fp);
            fprintf(fp,"%d",canvas[x][y].g);
            fputs(" ",fp);
            fprintf(fp,"%d",canvas[x][y].b);
            fputs(" ",fp);
        }
        fputs("\n",fp);
    }
    fclose(fp);
}


void paint(void* args){
    int i;
    artist_t* painter = (artist_t*)args;
    
    // Our artist will now attempt to paint 5000 strokes of paint
    // on our shared canvas
    for(i =0; i < 10000; ++i){
        
        // Store our initial position
        int currentX = painter->x;
        int currentY = painter->y;
        // Generate a random number from 0-7
        int roll = (rand()%8);
        painter->x += movement[roll][0];
        painter->y += movement[roll][1];
        // Clamp the range of our movements so we only
        // paint within our 256x256 canvas.
        if(painter->x < 0) { painter->x = 0; }
        if(painter->x > CANVAS_WIDTH-1) { painter->x  = CANVAS_WIDTH-1; }
        if(painter->y < 0) { painter->y = 0; }
        if(painter->y > CANVAS_HEIGHT-1) { painter->y = CANVAS_HEIGHT-1; }
        
        if( canvas[painter->x][painter->y].r == 255 && canvas[painter->x][painter->y].g == 255 && canvas[painter->x][painter->y].b == 255){
            canvas[painter->x][painter->y].r = painter->r;
            canvas[painter->x][painter->y].g = painter->g;
            canvas[painter->x][painter->y].b = painter->b;
        }else{
            // If we cannot paint the pixel, then we backtrack
            // to a previous pixel that we own.
            painter->x = currentX;
            painter->y = currentY;
        }
    }
}

void samePositionMichaelangeloOne(){
//for(i = 0 ; i > 3 ; i++){
//if(((Michaelangelo->x == Donatello->r) || (Michaelangelo->x == Raphael->r) || (Michaelangelo->x == Leonardo->r))  || (Michaelangelo->y == Donatello->r) || (Michaelangelo->y == Raphael->r) || (Michaelangelo->y == Leonardo->r))  
}

// ================== Program Entry Point ============
int main(){
    // Initialize our 'blank' canvas
    initCanvas();
    int size = 255;
    // Our four expert artists
    artist_t* Michaelangelo = malloc(sizeof(artist_t));
    artist_t* Donatello  = malloc(sizeof(artist_t));
    artist_t* Raphael = malloc(sizeof(artist_t));
    artist_t* Leonardo = malloc(sizeof(artist_t));
    
    Michaelangelo->x = 0;
    Michaelangelo->y = 0;
    Michaelangelo->r = 255;
    Michaelangelo->g = 0;
    Michaelangelo->b = 165;
    // Fill in the artist attributes
    Donatello->x = CANVAS_WIDTH-1;
    Donatello->y = 0;
    Donatello->r = 128;
    Donatello->g = 0;
    Donatello->b = 128;
    // Fill in the artist attributes
    Raphael->x = CANVAS_WIDTH-1;
    Raphael->y = CANVAS_HEIGHT-1;
    Raphael->r = 255;
    Raphael->g = 0;
    Raphael->b = 0;
    // Fill in the artist attributes
    Leonardo->x = 0;
    Leonardo->y = CANVAS_HEIGHT-1;
    Leonardo->r = 0;
    Leonardo->g = 0;
    Leonardo->b = 255;
    
    // Hold our thread id's
    pthread_t Michaelangelo_tid;
    pthread_t Donatello_tid;
    pthread_t Raphael_tid;
    pthread_t Leonardo_tid;
    srand(time(NULL));
    
   
    pthread_create(&Michaelangelo_tid,NULL,(void*)paint,Michaelangelo);
    pthread_create(&Donatello_tid,NULL,(void*)paint,Donatello);
    pthread_create(&Raphael_tid,NULL,(void*)paint,Raphael);
    pthread_create(&Leonardo_tid,NULL,(void*)paint,Leonardo);
    int rookieArtists = 50;
    pthread_t moreArtists_tid[rookieArtists];
    artist_t* moreArtists = malloc(sizeof(moreArtists_tid) * rookieArtists);
    
    for (int i = 0; i < rookieArtists; i++){
        moreArtists[i].x = (rand() * i) % size;
        moreArtists[i].y = (rand() * i) % size;
        moreArtists[i].r = (rand() * i) % size;
        moreArtists[i].g = (rand() * i) % size;
        moreArtists[i].b = (rand() * i) % size;
        pthread_create(&moreArtists_tid[i], NULL,(void *) paint, &moreArtists[i]);
    }
    pthread_join(Michaelangelo_tid, NULL);
    pthread_join(Donatello_tid, NULL);
    pthread_join(Raphael_tid, NULL);
    pthread_join(Leonardo_tid, NULL);
    
    for(int i =0; i < rookieArtists; i++){
        pthread_join(moreArtists_tid[i], NULL);
    }
    save();
   
    free(Leonardo);
    free(Raphael);
    free(Donatello);
    free(Michaelangelo);  
    return 0;
}

