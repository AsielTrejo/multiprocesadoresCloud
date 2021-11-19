#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 20

for (int z = 0;i<)
int main()
{ 
    int nthreads;
    FILE *image, *outputImage, *lecturas;
    image = fopen("f1b.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img4_dd.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;
    unsigned char* aux;
    
    int hb[256]; 
    int hg[256];
    int hr[256];
    int hgray[256];


    //Limpiamos arreglos
    for (int i = 0; i<256;i++){
      hb[i]=0;
      hg[i]=0;
      hr[i]=0;
      hgray[i]=0;
    }

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18]; //Original
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22]; //Original
    //ancho = (long)xx[10]*65536+(long)xx[19]*256+(long)xx[18];
    //alto = (long)xx[9]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    unsigned char img[alto][ancho];

    ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));
    aux = ptr;

    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

      hb[(int)b]+=1;
      hg[(int)g]+=1;
      hr[(int)r]+=1;

      unsigned char pixel = 0.21*r+0.72*g+0.07*b;
      hgray[(int)pixel]++;

      ptr[cuenta] = pixel; //b
      ptr[cuenta+1] = pixel; //g
      ptr[cuenta+2] = pixel; //r
      cuenta++;

    }                                  

    //Grises

    //ptr=aux;
    int row=0;
    int column = 0;
    int ac = 0;
    float center = 0.0;
    int number = 9;
    int finishLine= ancho-1;
    int finishRow = alto-1;
    float factor = 1.0/(number*number);

    int baseRow =0;
    int auxrow=0;
    int baseColumn=0;
    int auxcolumn=0;


    omp_set_num_threads(NUM_THREADS);
    const double startTimeP = omp_get_wtime();

  #pragma omp parallel
    {
      #pragma omp for schedule(dynamic)
        for (int i = 0; i < (alto*ancho); i++) {
          row = i/ancho;
          column =i-(row*ancho); 
          img[row][column]=ptr[i];
        }

      //row = number/2;
      //column = -(number/2) ;
      row=0;
      column = 0;

      #pragma omp for schedule(dynamic)     
    for (int p = 0; p < alto*ancho; p++) { 
        row = p/ancho;
        column =p-(row*ancho); 

        fputc(img[row][column], outputImage);
        fputc(img[row][column], outputImage);
        fputc(img[row][column], outputImage);

      } 
    }


    const double endTimeP = omp_get_wtime();
    printf("Tiempo paralelo es %lf\n\n", (endTimeP - startTimeP));

    free(ptr);
    //free(aux);
    fclose(image);
    fclose(outputImage);
    return 0;
}
