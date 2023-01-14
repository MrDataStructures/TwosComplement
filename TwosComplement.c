#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vertex{
    long num;
    struct vertex* next;
}vertex;

vertex* enqueue(vertex* root, long n){
    vertex* newVert = malloc(sizeof(vertex));
    newVert->next = NULL;
    newVert->num = n;
    if(root == NULL){
        root = newVert;
    }else{
        vertex* start = root;
        while(start->next != NULL){
            start = start->next;
        }
        start->next = newVert;
    }
    return root;
}

void toBinary(long num, long bits){
    for (int i = bits-1; i >= 0; i--){
        int mask = (1 << i);
        if (num & mask){
           printf("1"); 
        }else{
            printf("0");
        } 
    }
}

long power(long base, long exponent){
    long powerValue = 1;
    for(long i=0; i < exponent; i++){
        powerValue = powerValue * base;
    }
    return powerValue;
}

void traverse(vertex* root){ // traverse through the linked list and print out each vertex name
    if(root != NULL){
        for(vertex* printing = root; printing!=NULL; printing = printing->next){
            printf("%li ", printing->num);
        }
    }
    printf("\n");
}

vertex* tooBinary(long num, long bits){
    vertex* first = NULL;
    long one = 1;
    long zero = 0;
    for (int i = bits-1; i >= 0; i--){
        long mask = (1 << i);
        if (num & mask){
            first = enqueue(first, one);
        }else{
            first = enqueue(first, zero);
        } 
    }
    return first;
}

int main(int argc, char* argv[argc+1]){     //(power(2, bits)-1) < num
    long num;
    long bits;
    FILE* fp = fopen(argv[1], "r");
    while(fscanf(fp, "%li %li\n", &num, &bits) != EOF){
        if((num >= 0) && (num > power(2, bits-1)-1)){
            toBinary((power(2,bits-1)-1), bits);
            printf("\n");
        }else if(num < 0 && (num < -1*(power(2,bits-1)))){
            toBinary(power(2,bits-1), bits);
            printf("\n");
        }else if(num >= 0){
            toBinary(num, bits);
            printf("\n");
        }else if(num < 0){
            long number = -1*num;
            vertex* ptr = NULL;
            ptr = tooBinary(number, bits);  // linked list of the binary representation of it with that many bits               good
            
            long arr[bits];
            vertex* curr = ptr;
            for(long i=0;i<bits;i++){
                arr[i] = curr->num;     // now the binary representation of it has been put in an array              good
                curr = curr->next;
            }

            long index;
            for(long j=bits-1;j>=0;j--){   // finds the first occurance of a 1 from the right of the array           good
                if(arr[j]==1){
                    index = j;
                    break;
                }
            }
            for(long z = 0; z < index; z++){
                if(arr[z]==1 && z!=index){
                    arr[z]=0;
                }else if(arr[z]==0 && z!=index){  // finds the complement of everything to the left of that first 1 from the right
                    arr[z]=1;
                }
            }
            
            for(long b=0;b<bits;b++){  // finally, we get the two's complement
                printf("%li", arr[b]);
            }
            printf("\n");

            while(ptr!=NULL){
                vertex* nex = ptr->next;
                free(ptr);
                ptr = nex;
            }

        }
    }
    fclose(fp);
    return 0;
}
