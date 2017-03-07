// Example program:
// Using SDL2 to create an application window

#include <SDL.h>
#include <stdio.h>
#include <time.h>


volatile char quit = 0;
SDL_Renderer *renderer;

void event_loop();

int init_array(int arr[],int len);
void quick_sort(int arr[],int len);
void selection_sort(int arr[], int len);
void insertion_sort(int arr[], int len);
void bubble_sort(int arr[], int len);

void reset();
void clear_screen();
void draw_chart(int arr[],int len);

void update_chart();

//Dsets g_sets[50];
int g_arr[50];
int g_arr_bck[50];
int g_len = 50;

int main(int argc, char* argv[]) 
{
    int i ;

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())


    renderer = SDL_CreateRenderer(window, -1, 0);
    clear_screen();

    init_array(g_arr,g_len);
    memcpy(g_arr_bck,g_arr,g_len*sizeof(int));

    draw_chart(g_arr, g_len);
    
    SDL_RenderPresent(renderer);
   
	event_loop();

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}

void event_loop()
{

    SDL_Event e;

    while (!quit){
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                        quit = 1;
                }
                if (e.type == SDL_KEYDOWN){
                        //quit = 1;
                    clock_t chartStart = clock();
                    switch(e.key.keysym.sym) {
                        case SDLK_F1:
                            quick_sort(g_arr,g_len);
                            break;
                        case SDLK_F2:
                            selection_sort(g_arr,g_len);
                            break;
                        case SDLK_F3:
                            insertion_sort(g_arr,g_len);
                            break;
                        case SDLK_F4:
                            bubble_sort(g_arr, g_len);
                            break;
                        case SDLK_F10:
                            reset();
                            break;
                        default:
                            
                            break;
                    }
                    clock_t chartend = clock();
                    float ts = (float)(chartend - chartStart) /CLOCKS_PER_SEC;
                    printf("times:%f\n",ts);
                    
                }
                if (e.type == SDL_MOUSEBUTTONDOWN){
                        //quit = 1;
                }
               
            }
    }

}

void shuffle(int arr[],int len)
{
    int i=len;
    int tmp,n;
    while(i>1){
        n = rand()%i;
        tmp = arr[i-1];
        arr[i-1]=arr[n];
        arr[n]=tmp;
        i--;
    }
}

int init_array(int arr[],int len)
{
    int i ;
    if(arr == NULL) return -1;
    for(i=0;i<len;i++){
            arr[i]=i;
    }

    shuffle(arr,len);
    return len;
}

void reset()
{
    memcpy(g_arr,g_arr_bck,g_len*sizeof(int));
    update_chart();

}

void clear_screen()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
}

#define ORI_X 30
#define ORI_Y 200
#define ORI_W 10
#define ORI_H 3
void draw_chart(int arr[],int len)
{
    int i;
    clear_screen();
   
    for(i=0;i<len;i++){
        SDL_Rect rect;
        rect.x=ORI_X+i*ORI_W;
        rect.y=ORI_Y;
        rect.w=ORI_W-2;
        rect.h=arr[i]*ORI_H+1;
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
        SDL_RenderFillRect(renderer,&rect);

    }
}



void update_chart()
{

    draw_chart(g_arr,g_len);
    SDL_RenderPresent(renderer);
    SDL_Delay(20);

}


//sorting
void swap(int *s,int *d)
{
        int tmp=*s;
        *s=*d;
        *d=tmp;
}

void quick_sort_recursive(int arr[],int start,int end)
{
        if(start>=end)
                return ;

        int mid=arr[end];
        int left=start,right=end-1;

        while(left<right){
            while(arr[left]<mid && left<right)
                left++;
            while(arr[right]>=mid && left<right)
                right--;
            swap(&arr[left],&arr[right]);
            update_chart();

        }

        if(arr[left]>=arr[end]){
            swap(&arr[left],&arr[end]);
            update_chart();
        }else
            left++;

        if(left)
            quick_sort_recursive(arr,start,left-1);

        quick_sort_recursive(arr,left+1,end);

}

void  quick_sort(int arr[],int len)
{
    //printf("quick_sort beging...\n");
    quick_sort_recursive(arr,0,len-1);
    printf("quick_sort over...\n");
}

void selection_sort(int arr[], int len)
{
    int i, j, min, temp;
    for (i = 0; i < len - 1; i++) {
        min = i;
        for (j = i + 1; j < len; j++)
            if (arr[min] > arr[j])
                min = j;
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
        update_chart();
    }
}

void insertion_sort(int arr[], int len)
{
    int i, j;
    int temp;
    for (i = 1; i < len; i++) {
        temp = arr[i];
        j = i - 1;
        
        for (; j >= 0 && arr[j] > temp; j--) {
            arr[j + 1] = arr[j];
            update_chart();
        }
        arr[j + 1] = temp; 
        
    }
}

void bubble_sort(int arr[], int len)
{
    int i, j, temp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                update_chart();
            }
}
